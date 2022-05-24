-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1. Look at the crime_scene_reports what incident was reported on Humphrey Street at 28th July
SELECT *
FROM crime_scene_reports
WHERE street="Humphrey Street"
          AND month=7
          AND day=28
          AND year=2021;
--  1.1 Got 2 results. One was theft(at 10:15), the other littering(at 16:30). We look for a theft, so the first one is our choice. Stolen item: CS50 Duck
--  1.2 Look at interviews done at that day - description mentioned 3 witnesses
--  1.2 Description referred to transcripts of interviews that mentioned bakery - might want to look at bakery_security_logs
-- 2. Look at the interviews done on 28th July mentioning bakery
SELECT *
FROM interviews
WHERE month=7
  AND day=28
  AND year=2021
  AND transcript LIKE "%bakery%";
--  2.1 Got three results:
--  2.2 Ruth mentions seeing thief getting into car within ten minutes of the theft[Security from bakery parking lot could be helpful]
--  2.2 Eugene recognized the thief. Thief was withdrawing money from ATM on Leggett Street earlier in the morning.
--  2.3 Raymond mentioned thief calling some one for less than a minute. The thief was planning a earliest flight out tomorrow and requested the call recipient to buy the ticket
-- 3. Look at bakery_security_logs to find car
SELECT * FROM bakery_security_logs WHERE month=7 AND day=28 AND year=2021 AND hour=10;
--  3.1 Around 10 Was lot of activity. Should narrow it down. The witness said that the thief leaving with car was within 10 minutes of the theft.
SELECT * FROM bakery_security_logs WHERE month=7 AND day=28 AND hour=10 AND minute > 15 AND minute < 25;
--  3.2 8 vehicles left at that timeframe. Maybe look at the last 3, which are close to said leaving time 10:15+10
SELECT * FROM bakery_security_logs WHERE month=7 AND day=28 AND hour=10 AND minute > 20 AND minute < 25;
--  3.3 We got 3 license_plates to examine
-- 4. Look to see if any of the car owners withdrew money at Leggett Street ATM in the 28th July morning
--  4.1 Look at bank records types for next query to
SELECT DISCTINCT(transaction_type) FROM atm_transactions;
--   Actions are: deposit and withdraw, we can use it to specify query
--  4.2 Make query across people, bank_accounts and atm_transactions using the car license plates from security cameras
SELECT *
FROM people
         JOIN bank_accounts
              ON people.id=bank_accounts.person_id
         JOIN atm_transactions
              ON bank_accounts.account_number=atm_transactions.account_number
WHERE license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 20
          AND minute < 25)
        AND atm_transactions.month=7
        AND atm_transactions.day=28
        AND atm_transactions.year=2021
        AND atm_transactions.atm_location="Leggett Street"
        AND atm_transactions.transaction_type="withdraw";
--   Got 2 results: Diana[ID: 514354] and Iman[ID: 396669]
-- 5. Look at flights to determine who of them is trying to fly out 29th July from Fiftyville
--  5.1 Check for airports
SELECT * FROM airports WHERE city="Fiftyville";
--   One airport: Fiftyville Regional Airport
--  5.2 Look at the earliest flight leaving from Fiftyville at 29th July
SELECT *
FROM airports
         JOIN flights
              ON airports.id=flights.origin_airport_id
WHERE airports.city="Fiftyville"
  AND flights.month=7
  AND flights.day=29
  AND flights.year=2021
ORDER BY flights.hour ASC, flights.minute ASC;
--   Earliest is Flight leaving Fiftyville is with ID 36 at 8:20 on 29th July;
-- 5.3 Add in passanger and license plate info to filter out flights
SELECT *
FROM airports
         JOIN flights
              ON airports.id=flights.origin_airport_id
         JOIN passengers
              ON flights.id=passengers.flight_id
         JOIN people
              ON passengers.passport_number=people.passport_number
WHERE people.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 20
          AND minute < 25)
    AND airports.city="Fiftyville"
        AND flights.month=7
        AND flights.day=29
        AND flights.year=2021
ORDER BY flights.hour ASC, flights.minute ASC;
--   Got 2 persons: Kelsey at 8:20 and Diana at 16:00.
--   Although Kelsey has earlier flight, she wasn't in the bank records or withdrawing money in Leggett Street street
--   So at two points Diana has appeared in the results. She should be our suspect.
--  6. Next to determine which city did she fly to
SELECT *
FROM airports as origin
         JOIN flights
              ON origin.id=flights.origin_airport_id
         JOIN airports
              ON airports.id=flights.destination_airport_id
         JOIN passengers
              ON flights.id=passengers.flight_id
         JOIN people
              ON passengers.passport_number=people.passport_number
WHERE people.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 20
          AND minute < 25)
    AND origin.city="Fiftyville"
        AND flights.month=7
        AND flights.day=29
        AND flights.year=2021
ORDER BY flights.hour ASC, flights.minute ASC;
--  Table is long to scroll and hard to find correct answer for city. Need to limit columns
SELECT origin.city, people.name, airports.city
FROM airports as origin
         JOIN flights
              ON origin.id=flights.origin_airport_id
         JOIN airports
              ON airports.id=flights.destination_airport_id
         JOIN passengers
              ON flights.id=passengers.flight_id
         JOIN people
              ON passengers.passport_number=people.passport_number
WHERE people.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 20
          AND minute < 25)
    AND origin.city="Fiftyville"
        AND flights.month=7
        AND flights.day=29
        AND flights.year=2021
ORDER BY flights.hour ASC, flights.minute ASC;
--   From results we see that she took flight from Fiftyville to Boston
-- 7. Now we look for the accomplice
--  7.1 We start by considering who did she call to and we can get that info from phone_calls
SELECT from_phone.name, to_phone.name, phone_calls.duration
FROM phone_calls
         JOIN people AS from_phone
              ON phone_calls.caller=from_phone.phone_number
         JOIN people AS to_phone
              ON phone_calls.receiver=to_phone.phone_number
WHERE from_phone.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 20
          AND minute < 25)
        AND phone_calls.year=2021
        AND phone_calls.month=7
        AND phone_calls.day=28
        AND phone_calls.duration<60
        AND from_phone.name="Diana";
---  RESULT: NOT correct
---------------------------------------------------------------------------------------------
------ NEW START
-- 1. Look at the leaving cars at security_logs, this time with names: Iman, Diana, Kelsey
SELECT * FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate=people.license_plate WHERE month=7 AND day=28 AND hour=10 AND minute > 20 AND minute < 25;
-- 2. Look at bank ATM logs:
SELECT *
FROM people
         JOIN bank_accounts
              ON people.id=bank_accounts.person_id
         JOIN atm_transactions
              ON bank_accounts.account_number=atm_transactions.account_number
WHERE license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 20
          AND minute < 25)
        AND atm_transactions.month=7
        AND atm_transactions.day=28
        AND atm_transactions.year=2021
        AND atm_transactions.atm_location="Leggett Street"
        AND atm_transactions.transaction_type="withdraw";
--  Got: Diana and Iman
-- 3. Look at travel data again: again Diana
SELECT origin.city, people.name, airports.city
FROM airports as origin
         JOIN flights
              ON origin.id=flights.origin_airport_id
         JOIN airports
              ON airports.id=flights.destination_airport_id
         JOIN passengers
              ON flights.id=passengers.flight_id
         JOIN people
              ON passengers.passport_number=people.passport_number
WHERE people.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 20
          AND minute < 25)
    AND origin.city="Fiftyville"
        AND flights.month=7
        AND flights.day=29
        AND flights.year=2021
ORDER BY flights.hour ASC, flights.minute ASC;
-- 4. Somewhere I made wrong assumption. Only issue from earliest I noticed that Diana flight was later in the day
--    Issue arises maybe the from the selection of license plates. Expand time limit to 15 - 25
SELECT origin.city, people.name, airports.city, flights.hour, flights.minute
FROM airports as origin
         JOIN flights
              ON origin.id=flights.origin_airport_id
         JOIN airports
              ON airports.id=flights.destination_airport_id
         JOIN passengers
              ON flights.id=passengers.flight_id
         JOIN people
              ON passengers.passport_number=people.passport_number
WHERE people.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 15
          AND minute < 25)
    AND origin.city="Fiftyville"
        AND flights.month=7
        AND flights.day=29
        AND flights.year=2021
ORDER BY flights.hour ASC, flights.minute ASC;
--  Now we have more candidates: Exclude Diana, because it was wrong. That leaves Sofia, Bruce, Kelsey and Luca.
-- 5. Look at the ATM transactions again with larger plate size:
SELECT *
FROM people
         JOIN bank_accounts
              ON people.id=bank_accounts.person_id
         JOIN atm_transactions
              ON bank_accounts.account_number=atm_transactions.account_number
WHERE license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 15
          AND minute < 25)
        AND atm_transactions.month=7
        AND atm_transactions.day=28
        AND atm_transactions.year=2021
        AND atm_transactions.atm_location="Leggett Street"
        AND atm_transactions.transaction_type="withdraw";
--   Excluding Diana: We have Bruce, Iman, Luca. Bruce and Luca have flights tomorrow morning, the earliest time.
-- 6. Look at the call data to see who made calls at that time, with expanded license plate size
SELECT from_phone.name, to_phone.name, phone_calls.duration
FROM phone_calls
         JOIN people AS from_phone
              ON phone_calls.caller=from_phone.phone_number
         JOIN people AS to_phone
              ON phone_calls.receiver=to_phone.phone_number
WHERE from_phone.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 15
          AND minute < 25)
        AND phone_calls.year=2021
        AND phone_calls.month=7
        AND phone_calls.day=28
        AND phone_calls.duration<60;
--   We got 5 names - Sofia, Kelsey, Bruce, Diana. Since Diana wasn't correct and Sofia along with Kelsey didn't do withdrawals, it only leaves Bruce. From the result we also see that he called Robin, who must be his accomplice
-- 7. Check escape location from earlier query
SELECT origin.city, people.name, airports.city, flights.hour, flights.minute
FROM airports as origin
         JOIN flights
              ON origin.id=flights.origin_airport_id
         JOIN airports
              ON airports.id=flights.destination_airport_id
         JOIN passengers
              ON flights.id=passengers.flight_id
         JOIN people
              ON passengers.passport_number=people.passport_number
WHERE people.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month=7
          AND day=28
          AND year=2021
          AND hour=10
          AND minute > 15
          AND minute < 25)
    AND origin.city="Fiftyville"
        AND flights.month=7
        AND flights.day=29
        AND flights.year=2021
ORDER BY flights.hour ASC, flights.minute ASC;
--   Bruce flew to New York City
-- 8. Attempt a query that puts all together
SELECT
    DISTINCT (people.name) as thief,
             airports.city as destination,
             in_call.name as accomplice
FROM airports as origin
         JOIN flights
              ON origin.id = flights.origin_airport_id
         JOIN airports
              ON airports.id = flights.destination_airport_id
         JOIN passengers
              ON flights.id = passengers.flight_id
         JOIN people
              ON passengers.passport_number = people.passport_number
         JOIN bank_accounts ON people.id = bank_accounts.person_id
         JOIN atm_transactions ON bank_accounts.account_number
         JOIN phone_calls out_call ON people.phone_number = out_call.caller
         JOIN people in_call ON out_call.receiver = in_call.phone_number
WHERE people.license_plate IN
      (SELECT license_plate
       FROM bakery_security_logs
       WHERE month = 7
          AND day = 28
          AND year = 2021
          AND hour = 10
          AND minute > 15
          AND minute < 25)
    AND origin.city = "Fiftyville"
    AND flights.month = 7
    AND flights.day = 29
    AND flights.year = 2021
    AND atm_transactions.atm_location = "Leggett Street"
    AND out_call.duration < 60
    AND out_call.month = 7
    AND out_call.day = 28
    AND out_call.year = 2021
ORDER BY flights.hour ASC, flights.minute ASC LIMIT 1;