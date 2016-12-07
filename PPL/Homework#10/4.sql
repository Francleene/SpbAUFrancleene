SELECT
 Country.Name,
 COUNT(City.Id)
FROM
 Country
LEFT JOIN City ON Country.Code = City.CountryCode 
			  AND City.Population >= 1000000
GROUP BY
 Country.Code
ORDER BY 
 2 DESC,
 1 ASC;