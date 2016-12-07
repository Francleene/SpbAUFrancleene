SELECT 
 City.Name
FROM
 City
INNER JOIN Capital ON City.Id = Capital.CityId
INNER JOIN Country ON Capital.CountryCode = Country.Code
WHERE
 Country.Name = "Malaysia";