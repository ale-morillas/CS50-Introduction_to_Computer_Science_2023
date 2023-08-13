-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Find the crime scene report from 7/28/2021 Humphrey Street.
SELECT description FROM crime_scene_reports
WHERE month = 7
AND day = 28
AND street = 'Humphrey Street';

-- Read the interviews that took place in 7/28/2021 and mention the bakery.
SELECT name, transcript FROM interviews
WHERE day = 28
AND month = 7
AND transcript
LIKE '%bakery%';

-- Check the security camera from the bakery parking lot to look for the license plate.
SELECT activity, license_plate, hour, minute FROM bakery_security_logs
WHERE month = 7
AND day = 28
AND hour = 10
AND minute BETWEEN 15 AND 25
AND activity = 'exit';

-- Check the wirthdraws from Laggett Street ATM the day of the crime.
SELECT account_number, atm_location, transaction_type, amount FROM atm_transactions
WHERE month = 7
AND day = 28
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

-- Check the phone calls that last less than a minute on 7/28.
SELECT caller, receiver, duration FROM phone_calls
WHERE month = 7
AND day = 28
AND duration < 60;

-- Look for the drivers that left the bakery between 10:15 and 10:25:
SELECT name, bakery_security_logs.license_plate FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute BETWEEN 15 AND 25
AND bakery_security_logs.activity = 'exit';

-- Check if one of those people made a withdraw from Leggett St ATM the day of the crime:
SELECT name, bank_accounts.account_number FROM people
JOIN bank_accounts ON people.id = person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.month = 7
AND atm_transactions.day = 28
AND atm_transactions.transaction_type = 'withdraw'
AND atm_transactions.atm_location = 'Leggett Street';

-- Look for the people who met the three description from the interviews:
SELECT name FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE bakery_security_logs.month = 7
AND bakery_security_logs.day = 28
AND bakery_security_logs.hour = 10
AND bakery_security_logs.minute BETWEEN 15 AND 25
AND bakery_security_logs.activity = 'exit'
AND people.name IN (
    SELECT name FROM people
    JOIN bank_accounts ON people.id = person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.month = 7
    AND atm_transactions.day = 28
    AND atm_transactions.transaction_type = 'withdraw'
    AND atm_transactions.atm_location = 'Leggett Street')
AND people.name IN (
    SELECT name FROM people
    JOIN phone_calls ON people.phone_number = phone_calls.caller
    WHERE phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60
);

-- Looking for the first flight from 7/29 Fiftyville airport:
SELECT flights.id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE airports.city = 'Fiftyville'
AND flights.month = 7
AND flights.day = 29
ORDER BY flights.hour
LIMIT 1;

-- Check if one of the two suspects take the flight 36 and is the thief:
SELECT name FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE flight_id = 36
AND (people.name = 'Bruce'
OR people.name = 'Diana');

-- Look the city where the thief escaped to:
SELECT city FROM airports
JOIN flights ON airports.id = flights.destination_airport_id
WHERE flights.id = 36;

-- Thief’s accomplice is who helped them escape by looking on the phone calls:
SELECT name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60
AND phone_calls.caller IN (
    SELECT caller FROM phone_calls
    JOIN people ON phone_calls.caller = people.phone_number
    WHERE people.name = 'Bruce'
    AND phone_calls.month = 7
    AND phone_calls.day = 28
    AND phone_calls.duration < 60
);

