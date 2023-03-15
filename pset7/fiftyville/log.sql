-- Keep a log of any SQL queries you execute as you solve the mystery.
.table
.schema

-- TO GET THE CRIME SCENE REPORT DESCRIPTION
SELECT description FROM crime_scene_reports
    WHERE day = 28 AND month = 7 AND year = 2021 AND street = 'Humphrey Street';

-- TO GET THE TRANSCRIPT OF THE INTERVIEWS
SELECT name, transcript FROM interviews
    WHERE day = 28 AND month = 7 AND year = 2021;

-- Getting the names of people who withdraw money from the ATM on Leggett Street on the day of the crime as Eugene said
SELECT people.name from people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions  ON atm_transactions.account_number = bank_accounts.account_number
        WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street'
        AND transaction_type = 'withdraw';

-- Getting names of people who talked on the phone on the day of the crime for less than 10 minutes
SELECT people.name FROM people
    JOIN phone_calls ON phone_calls.caller = people.phone_number
        WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60;

--  Getting names of people who exited the bakery parking sometimes within ten minutes of the theft
SELECT people.name FROM bakery_security_logs
    JOIN people ON people .license_plate = bakery_security_logs.license_plate
        WHERE day = 28 AND month = 7 AND year = 2021 AND activity = 'exit' AND hour = 10 AND minute <= 25;

-- Getting the id of the earliest flight out of Fiftyville of the day after the theft, and the name of the city where the thief escaped to
SELECT flights.id, airports.city FROM airports
    JOIN flights ON airports.id = flights.destination_airport_id
        WHERE day = 29 AND month = 7 AND year = 2021
        AND origin_airport_id = (SELECT id FROM airports WHERE city = 'Fiftyville')
            ORDER BY hour, minute LIMIT 1;

-- Getting the name of the passengers on the earliest flight out of Fiftyville of the day after the theft to New York City
SELECT people.name FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
WHERE flight_id = 36;



-- summing everything up to get the name of the thief
SELECT people.name FROM passengers
JOIN people ON people.passport_number = passengers.passport_number
WHERE flight_id = 36 AND people.name in (
    SELECT people.name from people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions  ON atm_transactions.account_number = bank_accounts.account_number
    WHERE day = 28 AND month = 7 AND year = 2021 AND atm_location = 'Leggett Street'
    AND transaction_type = 'withdraw' AND people.name in (
        SELECT people.name FROM people
        JOIN phone_calls ON phone_calls.caller = people.phone_number
        WHERE day = 28 AND month = 7 AND year = 2021 AND duration < 60 AND people.name in (
            SELECT people.name FROM bakery_security_logs
            JOIN people ON people .license_plate = bakery_security_logs.license_plate
            WHERE day = 28 AND month = 7 AND year = 2021 AND activity = 'exit' AND hour = 10 AND minute <= 25)));


-- Getting the name of the accomplice
SELECT people.name FROM people
    JOIN phone_calls ON phone_calls.receiver = people.phone_number
    WHERE day = 28 AND month = 7 AND year = 2021 AND duration <= 60
    AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce');