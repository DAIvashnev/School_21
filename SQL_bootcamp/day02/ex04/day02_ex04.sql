WITH pz AS (SELECT *
		   FROM pizzeria),
	 mn AS (SELECT *
		  FROM menu
		  WHERE pizza_name IN ('mushroom pizza','pepperoni pizza')
		   )
SELECT mn.pizza_name AS pizza_name,
	   pz.name AS pizzeria_name,
	   mn.price AS price
FROM pz
JOIN mn ON pz.id = mn.pizzeria_id
ORDER BY pizza_name, pizzeria_name;