WITH max_age AS (SELECT	address,
				 MAX(age) AS max_age
				 FROM person
				 GROUP BY 1
				),
	 min_age AS (SELECT	address,
				 MIN(age) AS min_age
				 FROM person
				 GROUP BY 1
				),
	 avg_age AS (SELECT	address,
				 AVG(age) AS avg_age
				 FROM person
				 GROUP BY 1
				)
SELECT DISTINCT	address,
				ROUND(max_age - min_age/CAST(max_age AS NUMERIC), 2) AS formula,
				ROUND(avg_age, 2) AS average,
				max_age - min_age/CAST(max_age AS NUMERIC) > avg_age AS comparison
FROM person
NATURAL JOIN max_age
NATURAL JOIN avg_age
NATURAL JOIN min_age
ORDER BY 1;