BEGIN TRANSACTION;
UPDATE pizzeria SET rating = 5 WHERE name = 'Pizza Hut';
COMMIT WORK;