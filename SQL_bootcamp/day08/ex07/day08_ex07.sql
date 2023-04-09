--Session #1
BEGIN TRANSACTION;							--1
UPDATE person SET age = 77 WHERE id = 1;	--3
UPDATE person SET age = 777 WHERE id = 2;	--5
COMMIT WORK;								--7


--Session #2
BEGIN TRANSACTION;							--2
UPDATE person SET age = 66 WHERE id = 2;	--4
UPDATE person SET age = 666 WHERE id = 1;	--6
COMMIT WORK;								--8