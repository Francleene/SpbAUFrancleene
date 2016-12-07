SELECT
 Country.Name
FROM
 Country
INNER JOIN City ON Country.Code = City.CountryCode
GROUP BY 
 Country.Code
HAVING
 SUM(City.Population) > 0.5 * Country.Population
ORDER BY
 Country.Name;