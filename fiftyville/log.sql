-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports;

-- Basic overview of all the information

SELECT transcript FROM interviews WHERE transcript LIKE "%courthouse%";

-- Get the transcripts mentioned

SELECT * FROM flights WHERE day = 29 ORDER BY hour;

-- Get the flight mentioned id 36

SELECT * FROM passengers WHERE flight_id = 36;

-- Get the passengers

-- 260 | 2020 | 7 | 28 | 10 | 16 | exit | 5P2BI95
-- 261 | 2020 | 7 | 28 | 10 | 18 | exit | 94KL13X
-- 262 | 2020 | 7 | 28 | 10 | 18 | exit | 6P58WS2
-- 263 | 2020 | 7 | 28 | 10 | 19 | exit | 4328GD8
-- 264 | 2020 | 7 | 28 | 10 | 20 | exit | G412CB7
-- 265 | 2020 | 7 | 28 | 10 | 21 | exit | L93JTIZ
-- 266 | 2020 | 7 | 28 | 10 | 23 | exit | 322W7JE
-- 267 | 2020 | 7 | 28 | 10 | 23 | exit | 0NTHK55

SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10;

-- Get the security footage

SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36) ORDER BY license_plate;

-- Check the passports

SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 ORDER BY license_plate;

-- Double check the courthouse logs
-- Down to Evelyn Ernest Roger (499) 555-9472 (367) 555-5533 (130) 555-0289

SELECT * FROM phone_calls WHERE caller IN ("(499) 555-9472", "(367) 555-5533", "(130) 555-0289") AND day = 28 AND duration < 60;

-- Check the phone calls
-- Down to Evelyn and Roger

SELECT * FROM airports WHERE id = 4;

-- Double back for the airport, Heathrow

SELECT * FROM people WHERE people.id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE atm_location LIKE "%Fifer%" AND month = 7 AND day = 28 AND transaction_type = "withdraw"));

-- Check the withdraws, we have our thief Ernest

SELECT name FROM people WHERE phone_number = (SELECT receiver FROM phone_calls WHERE caller  = "(367) 555-5533" AND day = 28 AND duration < 60);

-- Check who he was calling