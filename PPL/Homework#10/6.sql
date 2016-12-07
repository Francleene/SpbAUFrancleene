SELECT 
 City.Name,
 City.Population,
 Country.Population
FROM
 City
INNER JOIN Country ON City.CountryCode = Country.Code
ORDER BY
 (0.1 * 10 * City.Population / Country.Population) DESC,
 City.Name DESC
LIMIT 20;