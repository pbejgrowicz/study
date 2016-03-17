wypisz x y = [x,y]

data Zdanie = Z Char
				| N Zdanie
				| K Zdanie Zdanie
				| A Zdanie Zdanie
				| C Zdanie Zdanie
				
drukuj (Z x) = putChar $ x
drukuj (N z) = putStr "~" >> drukuj z
drukuj (K x z) = putStr "(" >> drukuj x >> putStr " & " >> drukuj z >> putStr ")"
drukuj (A x z) = putStr "(" >> drukuj x >> putStr " | " >> drukuj z >> putStr ")"
drukuj (C x z) = putStr "(" >> drukuj x >> putStr " => " >> drukuj z >> putStr ")"