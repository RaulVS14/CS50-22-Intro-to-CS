window.addEventListener("load", () => {
    const meetingList = document.getElementById("meeting-list");
    const toDoList = document.getElementById("todo-list");
    const dailyList = document.getElementById("daily-list");
    const toDoInput = document.getElementById("to-do-text");
    const toDoBtn = document.getElementById("add-to-do");
    const toDoErrorMsg = document.getElementById("todo-error");
    const calendarLink = document.getElementById("calendar_link");
    calendarLink.addEventListener("click",(el)=>{
        chrome.tabs.create({url: calendarLink.getAttribute("href")});
        return false;
    })

    let todos = [];
    let dailies = [];

    function getFormattedTime(date) {
        function leadingZero(number) {
            return ("0" + number).slice(-2);
        }

        const hours = leadingZero(date.getHours());
        const minutes = leadingZero(date.getMinutes());
        return `${hours}:${minutes}`
    }

    const errorMsg = (msg) => {
        toDoErrorMsg.innerHTML = "";
        toDoErrorMsg.innerHTML = msg;
        setTimeout(() => {
            toDoErrorMsg.innerHTML = "";
        }, 1000);
    }
    const updateToDoView = () => {
        toDoList.innerHTML = "";
        for (let todoIndex in todos) {
            const todo = todos[todoIndex];
            const toDoTask = document.createElement("div");
            if (todo.done) {
                toDoTask.classList.add("todo--done");
            }
            toDoTask.classList.add("todo");
            const toDoTitle = document.createElement("span");
            const toDoElementDone = document.createElement("button");
            const toDoElementRemove = document.createElement("button");
            const toDoControls = document.createElement("div");
            toDoControls.classList.add("todo__controls");
            toDoTitle.innerHTML = todo.label;
            toDoElementDone.innerHTML = "&checkmark;";
            toDoElementDone.addEventListener("click", () => {
                todo.done = !todo.done;
                updateToDoView();
                chrome.storage.sync.set({todos});
            });
            toDoElementRemove.innerHTML = "&#10006;";
            toDoElementRemove.addEventListener("click", () => {
                todos.splice(todoIndex, 1);
                updateToDoView();
                chrome.storage.sync.set({todos});
            });
            toDoTask.append(toDoTitle);
            toDoControls.append(toDoElementDone);
            toDoControls.append(toDoElementRemove);
            toDoTask.append(toDoControls);
            toDoList.appendChild(toDoTask);
        }
    };

    const toDoAdd = (todo) => {
        if (todo) {
            if (!todos.includes(todo)) {
                todos.push({
                    label: todo,
                    done: false
                });
                updateToDoView();
                chrome.storage.sync.set({todos});
            } else {
                errorMsg("Todo already exists");
            }
        } else {
            errorMsg("Can't be empty todo");
        }
    };
    toDoInput.addEventListener("keypress", (ev) => {
        if (ev.key === "Enter") {
            toDoAdd(toDoInput.value);
            toDoInput.value = '';
            toDoInput.focus();
        }
    })
    toDoBtn.addEventListener("click", () => {
        toDoAdd(toDoInput.value);
        toDoInput.value = '';
        toDoInput.focus();
    });
    chrome.storage.local.get('events', (data) => {
        meetingList.innerHTML = ""
        const currentDate = new Date();
        for (let event of data.events) {
            const eventElement = document.createElement("div");
            eventElement.classList.add("event");
            const eventDateStart = new Date(event.schedule.startDate);
            const dateStartString = `${getFormattedTime(eventDateStart)}`;
            const eventDateEnd = new Date(event.schedule.endDate);
            const dateEndString = `${getFormattedTime(eventDateEnd)}`;
            const eventTime = document.createElement("div");
            const eventText = `${dateStartString} - ${dateEndString} ${event.summary ? event.summary : 'Busy'}`;
            if (eventDateEnd < currentDate) {
                const strikethrough = document.createElement("s");
                strikethrough.innerHTML = eventText;
                eventTime.append(strikethrough)
            } else {
                eventTime.innerHTML = eventText;
            }
            eventElement.append(eventTime);
            meetingList.appendChild(eventElement);
        }

    });

    chrome.storage.sync.get('dailies', (data) => {
        console.log(data);
    });

    chrome.storage.sync.get('todos', (data) => {
        todos = data.todos;
        updateToDoView();
    });

});