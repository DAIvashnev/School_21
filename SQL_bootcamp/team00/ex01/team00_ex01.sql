WITH RECURSIVE all_tours AS (
    SELECT point1 tour, point1, point2, cost, cost as sum
    FROM nodes
    WHERE point1 = 'A'
    UNION ALL
    SELECT parent.tour|| ',' || parent.point2 as tour,
        child.point1,
        child.point2,
        parent.cost,
        parent.sum + child.cost AS sum
    FROM nodes child
    JOIN all_tours parent ON child.point1 = parent.point2
    WHERE tour NOT LIKE '%' || parent.point2 || '%'
)
SELECT sum as total_cost,
       '{' || tour || ',' || point2 || '}' as tour
FROM all_tours
WHERE length(tour) = 7 AND
      point2 = 'A' AND
      sum = (SELECT min(sum) FROM all_tours WHERE length(tour) = 7 AND point2 = 'A')
UNION ALL
SELECT sum as total_cost,
       '{' || tour || ',' || point2 || '}' as tour
FROM all_tours
WHERE length(tour) = 7 AND
      point2 = 'A' AND
      sum = (SELECT max(sum) FROM all_tours WHERE length(tour) = 7 AND point2 = 'A')
ORDER BY total_cost, tour
;