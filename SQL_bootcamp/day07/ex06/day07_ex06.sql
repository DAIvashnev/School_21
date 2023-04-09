WITH t1 AS (SELECT menu_id,
			COUNT(menu_id) AS orders,
			SUM(price) AS summ,
			MAX(price) AS price
			FROM person_order
			JOIN menu
			ON person_order.menu_id = menu.id
			GROUP BY 1
		   ),
	 t2 AS (SELECT pizzeria.name,
			SUM(orders) AS count_of_orders,
			SUM(summ) AS summ,
			MAX(t1.price) AS max_price,
			MIN(t1.price) AS min_price
			FROM menu JOIN t1
			ON t1.menu_id = menu.id
			JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
			GROUP BY pizzeria.name
		   )
SELECT	name,
		count_of_orders,
		ROUND(summ/count_of_orders) AS average_price,
		max_price,
		min_price
FROM t2
ORDER BY 1;