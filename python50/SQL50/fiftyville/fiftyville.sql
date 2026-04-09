SELECT DISTINCT p.name
FROM people p
JOIN bank_accounts ba ON p.id = ba.person_id
JOIN atm_transactions atm ON ba.account_number = atm.account_number
JOIN bakery_security_logs bsl 
    ON p.license_plate = bsl.license_plate
JOIN phone_calls pc
    ON p.phone_number = pc.caller
WHERE bsl.day = 28
  AND bsl.month = 7
  AND bsl.hour = 10
  AND bsl.minute BETWEEN 15 AND 25
  AND bsl.activity = 'exit'
  AND atm.day = 28
  AND atm.month = 7
  AND atm.atm_location = 'Leggett Street'
  AND atm.transaction_type = 'withdraw'
  AND pc.day = 28
  AND pc.month = 7
  AND pc.duration <= 60;