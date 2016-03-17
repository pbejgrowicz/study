-- 1) Zliczenie powierzchni warsztatów w której mo¿e pracowaæ wiêcej ni¿ 2 osoby 
Select top 1 sum(powierzchnia) as "Suma powierzchni" 
	from WARSZTAT
	where iloscmiejsc > 2 
	group by powierzchnia
	order by sum(powierzchnia) desc


--2) Statystka urlopów
select count(idpracownika) as 'Liczba wykonujacych', typ 
	from URLOP, PRACOWNIK
	where URLOP.idpracownika = PRACOWNIK.osoba_pesel
	group by typ
	order by [Liczba wykonujacych] asc

--3) Pokaz samoloty ktore s¹ w naprawie 

select nrsamolotu as "Numer samolotu", samolot.nazwa, model, linialotnicza.nazwa as "Linia Lotnicza"
	from linialotnicza, samolot 
		join warsztat 
			on samolot.idwarsztatu = warsztat.id
	where samolot.idlini = linialotnicza.nazwa 

--4) Pokaz najstarszy oraz najmlodszy lot pilota ktory wykonal najwiecej lotow
select min(lot.dataw) as "Daty" --, max(lot.dataw) as "Data najm³odsza"
	from pilot, lot
	where lot.idpilota = pilot.osoba_pesel 
	and idpilota in
		(select top 1 lot.idpilota
			from lot
			group by lot.idpilota
			order by count(lot.idpilota) desc)
	group by pilot.osoba_pesel
union 
select  max(lot.dataw) 
	from pilot, lot
	where lot.idpilota = pilot.osoba_pesel 
	and idpilota in
		(select top 1 lot.idpilota
			from lot
			group by lot.idpilota
			order by count(lot.idpilota) desc)
	group by pilot.osoba_pesel


--5) Wyswietl imiona i nazwiska pilotów oraz pasa¿erów oraz numery lotów w których  razem lecieli pomiêdzy 2000 a 2010

select distinct Osoba.imie, Osoba.nazwisko, LOT.numerlotu as "numer lotu"
	from OSOBA, PILOT, PASAZER, LOT, LOT_PAS
	where LOT_PAS.lot = LOT.numerlotu 
	and LOT_PAS.pas = PASAZER.osoba_pesel
	and PASAZER.osoba_pesel = OSOBA.pesel
	and LOT.dataw > '2000-01-01'
	and LOT.datap < '2010-01-01'
union
select distinct Osoba.imie, Osoba.nazwisko, LOT.numerlotu
	from OSOBA inner join LOT on LOT.idpilota = OSOBA.pesel
	where LOT.numerlotu in 
	(select distinct LOT.numerlotu
		from OSOBA, LOT, LOT_PAS, PILOT 
		where LOT_PAS.lot = LOT.numerlotu 
		and LOT_PAS.pas = OSOBA.pesel
		and LOT.idpilota = PILOT.osoba_pesel
		and LOT.dataw > '2000-01-01' 
		and LOT.datap < '2010-01-01')
order by numerlotu


--6) Dla ka¿dego zamowienia po 2000 roku(czyli od 2001), poka¿ imie i nazwisko zamawiajacego, date zamowienia, id zamówienia oraz numer lotu 

select Osoba.imie as "Imiê", Osoba.nazwisko as "Nazwisko", ZAMOWIENIE.id as "Identyfikator zamowienia" , 
	ZAMOWIENIE.datazamowienia as "Data z³o¿enia zamowienia", LOT_ZAM.lot
	from OSOBA, LOT_ZAM, ZAMOWIENIE join PASAZER on ZAMOWIENIE.idpasazera = PASAZER.osoba_pesel
	where OSOBA.pesel = ZAMOWIENIE.idpasazera
	and LOT_ZAM.zam = ZAMOWIENIE.id
	and ZAMOWIENIE.datazamowienia > '2001-01-01'
	order by ZAMOWIENIE.datazamowienia




--7) Ka¿demu pracownikowi przys³uguje 1 urolop na ¿¹danie, wyœwietl pracowników (imiê, nazwisko, idpracownika) którzy jeszcze nie wykorzystali urlopu na ¿¹danie.


select distinct OSOBA.imie, OSOBA.nazwisko, PRACOWNIK.id
	from OSOBA, PRACOWNIK
	where PRACOWNIK.osoba_pesel not in 
	( select idpracownika
		from OSOBA, PRACOWNIK, URLOP
		where PRACOWNIK.osoba_pesel = OSOBA.pesel
		and URLOP.idpracownika = PRACOWNIK.osoba_pesel
		and typ = 'zadanie')
	and PRACOWNIK.osoba_pesel = OSOBA.pesel
	order by id




--8) WIDOK, dla aplikacji klienckiej zawieraj¹ce wszystkie informacje o lotach w tym informacje o samolocie

create view InfoOLotach
	as select LOT.numerlotu, LOT.dataw as "Data Wylotu", LOT.datap as "Data Przylotu",
	LOT.godzo as "Godzina odlotu", LOT.godzp as "Godzina Przylotu", LOT.miejscew as "Lotnisko startowe",
	LOT.miejscep as "Lotnisko koñcowe", SAMOLOT.nazwa as "Marka Samolotu", SAMOLOT.model as "Model Samolotu"
		from LOT, SAMOLOT
		where LOT.idsamolotu = samolot.nrsamolotu


--8a) u¿ytkownik o numerze pesel = 94110807754 dowiedzieæ chce dowiedzieæ siê o swoich lotach
	select InfoOLotach.* 
		from InfoOLotach, PASAZER, LOT_PAS
		where InfoOLotach.numerlotu = LOT_PAS.lot
			and LOT_Pas.pas = PASAZER.osoba_pesel
			and PASAZER.osoba_pesel = '94110807754'

--8b) u¿ytkownik chcê listê wszystkich po³¹czeñ z Gdañska
	select InfoOLotach.[Lotnisko koñcowe]
		from InfoOLotach
		where InfoOLotach.[Lotnisko startowe] = 'Gdansk'
		order by InfoOLotach.[Lotnisko koñcowe]


drop view InfoOLotach

/*

3 sposoby na nie u¿ywanie top 1
select * 
	from Pracownik
	where Pracownik.zarobki in (select min(zarobki) from Pracownik)


select * 
	from Pracownik
	where Pracownik.zarobki in
	(select D.zarobki 
		from PRacownik J, Pracownik D 
		group by D.zarobki
		having D.zarobki = min(J.zarobki))

select * from Pracownik M
	where not exists
		(select * from Pracownik TMP
			where Tmp.zarobki < M.zarobki)


*/

--9 Wypisz loty pilota który ma najmniejsze zarobki 


select Lot.* 
	from LOT, Pracownik M
	where Lot.idpilota = M.osoba_pesel
	and not exists
		(select * from Pracownik TMP
			where Tmp.zarobki < M.zarobki 
			and TMP.stanowisko = 'pilot')
	and M.stanowisko = 'pilot'


--9b Wypisz pasa¿erów którzy lecieli lotami z pilotem o najni¿szych zarobkach
select OSOBA.*, PASAZER.email
	from PASAZER 
		inner join LOT_PAS 
			on Pasazer.osoba_pesel = LOT_PAS.pas
		inner join OSOBA
			on OSOBA.pesel = LOT_PAS.pas
	where LOT_PAS.lot in	(select Lot.numerlotu
								from LOT, Pracownik M
								where Lot.idpilota = M.osoba_pesel
								and not exists
									(select * from Pracownik TMP
										where Tmp.zarobki < M.zarobki 
										and TMP.stanowisko = 'pilot')
								and M.stanowisko = 'pilot')






