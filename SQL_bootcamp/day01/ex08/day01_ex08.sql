SELECT person_order.order_date, CONCAT(person.name, ' (Age:', person.age, ')') AS person_information
FROM person_order
NATURAL JOIN (SELECT id AS person_id, name, age FROM person) AS person
ORDER BY order_date, person_information;