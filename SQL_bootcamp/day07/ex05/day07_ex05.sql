SELECT DISTINCT person.name
FROM person
JOIN person_order ON person.id = person_order.person_id
ORDER BY 1;