SELECT pizza_name FROM menu
UNION
SELECT pizza_name FROM menu WHERE false
ORDER BY pizza_name DESC;