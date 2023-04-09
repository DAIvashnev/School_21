WITH man AS (SELECT name, id
			FROM person
			WHERE gender = 'male' AND address IN ('Moscow','Samara')
			), 
	pizza AS (SELECT id
			 FROM menu
			 WHERE pizza_name IN ('pepperoni pizza', 'mushroom pizza')
			 )
SELECT man.name
FROM man
JOIN person_order ON person_order.person_id = man.id
JOIN pizza ON pizza.id = person_order.menu_id
ORDER BY 1 DESC;