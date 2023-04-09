SELECT * FROM (SELECT name AS objec_name FROM person ORDER BY objec_name) person
UNION ALL
SELECT * FROM (SELECT pizza_name FROM menu ORDER BY pizza_name) menu;