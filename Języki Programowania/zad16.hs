potega x = 2 ^x

grupuj :: Integral x => x -> [x]
grupuj 0 = []
grupuj x = grupuj (x `div` 10) ++ [x `mod` 10]

sumuj :: [Integer] -> Integer
sumuj [] = 0
sumuj (glowa:ogon) = glowa + sumuj ogon

wynik n = sumuj (grupuj (potega n))