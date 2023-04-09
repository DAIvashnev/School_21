SELECT	address,
		pizzeria.name,
		COUNT(pizzeria.name) AS count_of_orders
FROM person
JOIN person_order ON person_order.person_id = person.id
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY 1, 2
ORDER BY 1, 2;