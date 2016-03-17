czy_posortowane([], 'N'). %sprawdzenie czy tablica pusta
czy_posortowane([_], 'T'). %jezeli jeden element to tablica posortowana
czy_posortowane([A,B], ODP) :- A=<B -> ODP='T'; ODP='N'. %sprawdzenie czy tablica z dwoma znakami jest posortowana
czy_posortowane([A,B|OGON], ODP) :- A=<B, czy_posortowane([B|OGON], ODP). %sprawdzenie czy 2 i 3 sa posortowane



%gracz wygrywa gdy wystapi ktoras z ponizszych sytuacji
czy_wygrywa(0,0,0).
czy_wygrywa(1,1,0).
czy_wygrywa(1,0,1).
czy_wygrywa(0,1,1).
czy_wygrywa(1,1,1).

czy_wygrywa(A,B,C) :- A>0, D is A-1, not(czy_wygrywa(D,B,C)). %zdejmuj z A
czy_wygrywa(A,B,C) :- B>0, D is B-1, not(czy_wygrywa(A,D,C)). %zdejmuj z B
czy_wygrywa(A,B,C) :- C>0, D is C-1, not(czy_wygrywa(A,B,D)). %zdejmuj z C
czy_wygrywa(A,B,C) :- A>0, B>0, D is A-1, E is B-1, not(czy_wygrywa(D,E,C)). %zdejmuj z A i B
czy_wygrywa(A,B,C) :- A>0, C>0, D is A-1, E is C-1, not(czy_wygrywa(D,B,E)). %zdejmuj z A i C
czy_wygrywa(A,B,C) :- B>0, C>0, D is B-1, E is C-1, not(czy_wygrywa(A,D,E)). %zdejmuj z B i C



czy_graficzny(Listawpisana, ODP) :- graficzny(Listawpisana) -> ODP = 'Lista jest ciagiem graficznym.'; ODP = 'To nie jest ciag graficzny.'.

graficzny([]) :- !, false.
graficzny(Listawpisana) :- sortujnierosnaco(Listawpisana, [H|T]),(czylistazer([H|T]); zmniejszliste([H|T], Nowalista), graficzny(Nowalista)).

sortujnierosnaco(LW, Sortowana) :-
        zamien(LW, LW2), !,
        sortujnierosnaco(LW2, Sortowana).
sortujnierosnaco(Sortowana, Sortowana).

zamien([X,Y|T], [Y,X|T]) :- X < Y.	%sortuje 2 pierwsze elementy obok siebie
zamien([Z|T], [Z|U]) :- zamien(T, U).	%jesli 2 pierwsze elementy sa posortowane, obcina pierwszy element

czylistazer([]) :- true.
czylistazer([H|_]) :- H==0, true.	%jesli zostaly same zera - jest graficzny

zmniejszliste([H|T],Wynikowa) :- pomniejszojeden(T,H,Wynikowa),!.
pomniejszojeden(X,0,X).	%gdy licznik jest zerem, wrzucamy pozostale elementy listy wpisanej do listy wynikowej
pomniejszojeden([H|T],Licznik,Wynikowa) :- H>0,L is Licznik -1, pomniejszojeden(T,L,Tymczasowa), X is H-1, Wynikowa = [X|Tymczasowa].