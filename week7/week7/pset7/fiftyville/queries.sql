-- Get crime scene report
SELECT description FROM crime_scene_reports WHERE year=2020 AND month=7 AND day=28 AND street = 'Chamberlin Street';

-- Filter for interviews taking place at the courthouse 
SELECT * FROM interviews WHERE year=2020 AND month=7 AND day=28 AND transcript like '%Courthouse%';

-- Filter for names of people who used the ATM
SELECT DISTINCT(name) FROM atm_transactions INNER JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number INNER JOIN people ON bank_accounts.person_id = people.id INNER JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate INNER JOIN phone_calls ON people.phone_number = phone_calls.caller WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_location = 'Fifer Street' AND transaction_type = 'withdraw' AND hour = 10 AND minute > 15 AND minute < 25 AND duration < 60;

-- Filter for flights leaving first thing tomorrow from Fiftyville now that we have narrowed down the list of ATM users
SELECT name, phone_number, city FROM flights INNER JOIN airports ON flights.destination_airport_id = airports.id INNER JOIN passengers ON flights.id = passengers.flight_id INNER JOIN people ON passengers.passport_number = people.passport_number WHERE year=2020 AND month=7 AND day=29 AND name IN ('Ernest', 'Russell') AND hour = (SELECT MIN(hour) FROM flights INNER JOIN airports ON flights.origin_airport_id=airports.id WHERE city='Fiftyville' AND year=2020 AND month=7 AND day=29);

-- Find the accomplice based on phone records now we have the phone number of the thief
select name from phone_calls INNER JOIN people on phone_calls.receiver = people.phone_number WHERE year=2020 AND month=7 AND day=28 AND caller = '(367) 555-5533' AND duration < 60;