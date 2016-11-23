head' :: [a] -> a
head' (x : xs) = x

tail' :: [a] -> [a]
tail' [] = []
tail' (x : xs) = xs

take' :: Int -> [a] -> [a]
take' 0 list = []
take' num [] = []
take' num (x : xs) = x : take' (num - 1) xs

length' :: [a] -> Int
length' [] = 0
length' (x : xs) = 1 + length xs

drop' :: Int -> [a] -> [a]
drop' 0 list = list
drop' num [] = []
drop' num (x : xs) = drop' (num - 1) xs

filter' :: (a -> Bool) -> [a] -> [a]
filter' f [] = []
filter' f (x : xs)
    | f x       = x : filter' f xs
    | otherwise = filter' f xs

foldl' :: (a -> b -> a) -> a -> [b] -> a
foldl' func init_value [] = init_value
foldl' func init_value (x : xs) = foldl' func new_value xs
    where new_value = func init_value x

concat' :: [a] -> [a] -> [a]
concat' [] second_list = second_list
concat' (x : xs) second_list = x : concat' xs second_list

quickSort' :: Ord a => [a] -> [a]
quickSort' list
    | len < 2 = list
    | otherwise = concat' sorted_less_part (concat' eq_part sorted_greater_part)
    where len = length' list
          pivot = head' list
          greater_part = filter' (pivot <) list
          less_part = filter' (< pivot) list
          eq_part = filter' (== pivot) list
          sorted_greater_part = quickSort' greater_part
          sorted_less_part = quickSort' less_part
