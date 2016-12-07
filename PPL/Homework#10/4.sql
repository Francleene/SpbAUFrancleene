SELECT
 Country.Name,
 COUNT(bCities.bCountryCode)
FROM
 Country
INNER JOIN
(
	SELECT 
 	 City.CountryCode AS bCountryCode
	FROM
	 City
	WHERE
	 City.Population >= 1000000
) bCities
ON Country.Code = bCities.bCountryCode
GROUP BY 
 CountryCode;