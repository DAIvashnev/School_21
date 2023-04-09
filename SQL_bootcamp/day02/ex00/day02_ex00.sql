SELECT name, rating
FROM pizzeria
LEFT JOIN person_visits ON pizzeria.id = pizzeria_id
WHERE person_visits.id IS NULL;