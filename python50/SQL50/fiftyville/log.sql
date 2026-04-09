-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description
FROM crime_scene_reports
WHERE day = 28 AND month = 7
AND street = 'Humphrey Street';

SELECT name
FROM interviews
WHERE day = 28 AND month = 7
AND transcript LIKE '%bakery%';

SELECT name, transcript
FROM interviews
WHERE day = 28
AND month = 7
AND year = 2024
AND name IN ('Ruth', 'Eugene', 'Raymond')
ORDER BY name;


SELECT license_plate
FROM bakery_security_logs
WHERE day = 28 
AND month = 7
AND hour = 10
AND minute BETWEEN 15 AND 25;    

SELECT account_number, amount
FROM atm_transactions
WHERE day = 28
AND month = 7
AND atm_location = 'Leggett Street'
AND transaction_type = 'withdraw';

SELECT caller
FROM phone_calls
WHERE day = 28
AND month = 7
AND duration <= 60;

SELECT name
FROM people
WHERE license_plate IN 
(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28 
    AND month = 7
    AND hour = 10
    AND minute BETWEEN 15 AND 25 
)
AND phone_number IN 
(
    SELECT caller
    FROM phone_calls    
    WHERE day = 28
      AND month = 7
      AND duration <= 60
);

SELECT name 
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.day = 28
AND atm_transactions.month = 7
AND atm_transactions.atm_location = 'Leggett Street'
AND atm_transactions.transaction_type = 'withdraw';


-- the full answers or something:

SELECT DISTINCT name
FROM people p
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions atm ON ba.account_number = atm.account_number
WHERE p.phone_number IN 
(
    SELECT caller
    FROM phone_calls    
    WHERE day = 28
      AND month = 7
      AND duration <= 60
)
AND p.license_plate IN 
(
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28 
    AND month = 7
    AND hour = 10
    AND minute BETWEEN 15 AND 25
    AND activity = 'exit'
)
AND p.passport_number IN 
(
    SELECT passport_number
    FROM passengers
    WHERE flight_id IN 
    (
        SELECT id
        FROM flights
        WHERE origin_airport_id IN 
        (
            SELECT id
            FROM airports
            WHERE city = 'Fiftyville'
        )
        AND month = 7
        AND day = 29
        ORDER BY hour, minute
        LIMIT 1
    )
)
AND atm.day = 28
AND atm.month = 7
AND atm.atm_location = 'Leggett Street'
AND atm.transaction_type = 'withdraw';



SELECT name
FROM people
WHERE phone_number = 
(
    SELECT receiver
    FROM phone_calls    
    WHERE caller = (SELECT phone_number FROM people WHERE name = 'Bruce')
    AND day = 28
    AND month = 7
    AND duration <= 60
);


SELECT city
FROM airports
WHERE id IN
(
    SELECT destination_airport_id
    FROM flights
    WHERE id = (
        SELECT flight_id
        FROM passengers
        WHERE passport_number = 
        (
            SELECT passport_number
            FROM people
            WHERE name = 'Bruce'
        )
        LIMIT 1
    )
);



