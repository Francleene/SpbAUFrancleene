head' :: [a] -> a
head' (head : tail) = head

tail' :: [a] -> [a]
tail' [] = []
tail' (head : tail) = tail

take' :: Int -> [a] -> [a]
take' 0 list = []
take' num [] = []
take' num (head : tail) = head : take' (num - 1) tail

drop' :: Int -> [a] -> [a]
drop' num list
    | len <= num = []
    | otherwise  = reverse . take' (len - num) $ reverse list
    where len = length list

filter' :: (a -> Bool) -> [a] -> [a]
filter' f xs = [elem | elem <- xs, f elem]

foldl' :: (a -> b -> a) -> a -> [b] -> a
foldl' func init_value [] = init_value
foldl' func init_value (head : tail) = func (foldl' func init_value tail) head

concat' :: [a] -> [a] -> [a]
concat' first_list second_list = first_list ++ second_list

quickSort' :: Ord a => [a] -> [a]
quickSort' list
    | len < 2 = list
    | otherwise = sorted_less_part ++ eq_part ++ sorted_greater_part
    where len = length list
          pivot = head' list
          greater_part = filter' (\x -> pivot < x) list
          less_part = filter' (\x -> x < pivot) list
          eq_part = filter' (\x -> x == pivot) list
          sorted_greater_part = quickSort' greater_part
          sorted_less_part = quickSort' less_part
