WITH t1 AS (SELECT menu.id AS menu_id
			FROM menu
			EXCEPT
			SELECT menu_id
			FROM person_order
			ORDER BY 1
		   )
SELECT  pizza_name, price, pizzeria.name AS pizzeria_name
FROM t1
JOIN menu ON t1.menu_id = id
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
ORDER BY 1, 2