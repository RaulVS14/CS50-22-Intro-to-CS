// Runs on install or refresh
let dailies = [];

const todos = ["Bake cake"];

chrome.runtime.onInstalled.addListener(() => {
    chrome.storage.sync.set({dailies});
    chrome.storage.sync.set({todos});
})

function getAuthToken(options) {
    chrome.identity.getAuthToken({'interactive': options.interactive}, options.callback);
}

function createBasicNotification(options) {

}

function showNotification(error) {
    console.log(error)
    let options = {
        "id": "start-auth",
        'title': 'App notification',
        "message": error.message,
        "iconUrl": "images/calendar.png",
    };
    createBasicNotification(options);
}

async function getAuthTokenCallback(token) {
    if (chrome.runtime.lastError) {
        showNotification(chrome.runtime.lastError);
    } else {
        const calendars = await getCalendars(token);
        chrome.storage.sync.set({'calendars': calendars.items})
        const eventsCollection = {}
        for (let calendar of calendars.items) {
            let events = await getCalendarTodayEvents(token, calendar.id);
            if (!events?.error) {
                for (let event of events.items) {
                    eventsCollection[event.id] = event;
                }
            } else {
                console.log(`${calendar.id} - ${events.error.message}`);
            }
        }
        let events = Object.values(eventsCollection).map((ev) => {
            let currentDate = new Date();
            let startDate = new Date(Date.parse(ev.start.dateTime));
            startDate.setDate(currentDate.getDate());
            startDate.setMonth(currentDate.getMonth());
            startDate.setFullYear(currentDate.getFullYear());
            let endDate = new Date(Date.parse(ev.end.dateTime));
            endDate.setDate(currentDate.getDate());
            endDate.setMonth(currentDate.getMonth());
            endDate.setFullYear(currentDate.getFullYear());
            if(endDate.getHours() < startDate.getHours()){
                endDate = new Date(endDate.getTime() + 1000 * 60 * 60 * 24);
            }
            ev['schedule'] = {
                startDate: startDate.toISOString(),
                endDate: endDate.toISOString()
            }
            return ev;
        }).sort((a, b) => {
            let startDateA = new Date(a.schedule.startDate);
            let startDateB = new Date(b.schedule.startDate);
            if (startDateA > startDateB) {
                return 1;
            }
            if (startDateA < startDateB) {
                return -1;
            }
            return 0;
        })
        chrome.storage.local.set({'events': events});
    }
}

function getAuthSilent() {
    getAuthToken({
        'interactive': false,
        callback: getAuthTokenCallback
    });
}

async function get(options) {
    const response = await fetch(`${options.url}`, {
        headers: {
            'Authorization': `Bearer ${options.token}`,
            'Content-Type': 'application/json'
        }
    });
    return response.json();
}

async function getCalendars(token) {
    return await get(
        {
            url: 'https://www.googleapis.com/calendar/v3/users/me/calendarList',
            token
        }
    );
}

async function getCalendarTodayEvents(token, type = "primary") {
    const startDate = new Date()
    startDate.setHours(0, 0, 0, 0);
    const endDate = new Date();
    endDate.setHours(23, 59, 59, 999);
    return await get({
        url: `https://www.googleapis.com/calendar/v3/calendars/${type}/events?timeMin=${startDate.toISOString()}&timeMax=${endDate.toISOString()}&orderby=startTime`,
        token
    });
}

getAuthSilent()

chrome.action.onClicked.addListener(getAuthTokenCallback);