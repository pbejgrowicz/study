import Data.List
import Data.Map
import Data.Maybe

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

dodajDoListy (Z x) lista = x:lista
dodajDoListy (N x) lista = dodajDoListy x lista
dodajDoListy (K x y) lista = dodajDoListy y (dodajDoListy x lista)
dodajDoListy (A x y) lista = dodajDoListy y (dodajDoListy x lista)
dodajDoListy (C x y) lista = dodajDoListy y (dodajDoListy x lista)


unikalne (x:[]) = x:[]
unikalne (x:y:lista) = if x==y then (unikalne (x:lista)) else x:(unikalne (y:lista))

wypisz_zmienne x = print $ group $ unikalne $ sort $ dodajDoListy x []

mapa = fromList [('p', False), ('q', True), ('r', False)]

sprawdz (Z x) mapa = mapa!x
sprawdz (N x) mapa = if sprawdz x mapa then False else True
sprawdz (K x y) mapa = if (sprawdz x mapa) && (sprawdz y mapa) then True else False
sprawdz (A x y) mapa = if (sprawdz x mapa) || (sprawdz y mapa) then True else False
sprawdz (C x y) mapa = if (sprawdz x mapa) && (sprawdz y mapa)== False then False else True

tautologia zdanie (x:[]) y = if sprawdz zdanie (fromList ((x,False):y)) && sprawdz zdanie (fromList ((x,True):y)) then True else False
tautologia zdanie (x:lista) y = if (tautologia zdanie lista ((x,False):y)) == False then False else tautologia zdanie lista ((x,True):y)

jest_tautologia x = tautologia x ( unikalne $ sort $ dodajDoListy x [] ) []

main = print $ jest_tautologia (C (A (Z 'p') (Z 'q')) (C (N(Z 'p')) (Z 'q')))