WITH t1 AS (SELECT 	name,
			COUNT(person_id) AS count,
			'visit' AS action_type
			FROM person_visits
			JOIN pizzeria
			ON pizzeria.id = pizzeria_id
			GROUP BY name
			ORDER BY action_type ASC, count DESC
			LIMIT 3
		   ),
	 t2 AS (SELECT 	name,
			COUNT(person_id) AS count,
			'order' AS action_type
			FROM person_order
			JOIN menu
			ON menu.id = menu_id
			JOIN pizzeria
			ON pizzeria.id = pizzeria_id
			GROUP BY name
			ORDER BY action_type ASC, count DESC
			LIMIT 3
		   )
SELECT *
FROM t1
UNION ALL
SELECT *
FROM t2
ORDER BY action_type ASC, count DESC;