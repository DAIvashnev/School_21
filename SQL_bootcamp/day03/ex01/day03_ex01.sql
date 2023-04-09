SELECT menu.id
FROM menu
EXCEPT
SELECT menu_id
FROM person_order
ORDER BY 1