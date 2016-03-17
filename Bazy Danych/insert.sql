/*1) Linie lotnicze*/
insert into LINIALOTNICZA
	(nazwa)
	values ('Lot');
insert into LINIALOTNICZA
	(nazwa)
	values ('Lufthansa');
insert into LINIALOTNICZA
	(nazwa)
	values ('Wizzair');
insert into LINIALOTNICZA
	(nazwa)
	values ('Ryanair');
insert into LINIALOTNICZA
	(nazwa)
	values ('Emirates');
insert into LINIALOTNICZA
	(nazwa)
	values ('JanuszPol');
insert into LINIALOTNICZA
	(nazwa)
	values ('EtiAirlines');
insert into LINIALOTNICZA
	(nazwa)
	values ('SwissAir');
insert into LINIALOTNICZA
	(nazwa)
	values ('Airforce');
insert into LINIALOTNICZA
	(nazwa)
	values ('PolskiSamolot');
	

/*2) Warsztat */
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (500, 5, '08:00:00', '19:00:00', 1);
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (300, 3, '07:00:00', '18:00:00', 2);
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (350, 5, '09:30:00', '19:00:00', 3);
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (100, 1, '08:00:00', '15:00:00', 4);
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (200, 3, '08:00:00', '16:00:00', 5);
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (150, 1, '08:00:00', '16:00:00', 6);
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (500, 5, '09:00:00', '19:00:00', 7);
insert into WARSZTAT
	(powierzchnia, iloscmiejsc, openhours, closehours, id)
	values (300, 3, '09:00:00', '21:00:00', 8);


	
/*3) Pasażerowie */
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, nrtel, pesel)
	values ('Patryk', 'Bejgrowicz', 'Mylna', 'Kwidzyn', 17, 783196511, 94110807754);
insert into PASAZER
	(osoba_pesel, email)
	values (94110807754, 'patbejgr@student.pg.gda.pl');

insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Jan', 'Kowalski', 'Warszawska', 'Gdansk', 10, 15 , 100999555, 90111158245);
insert into PASAZER
	(osoba_pesel, email)
	values (90111158245, 'jan@kowalski.pl');

insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, nrtel, pesel)
	values ('Tomek', 'Domek', 'Kartuska', 'Gdansk', 10, 783000511, 94110395847);
insert into PASAZER
	(osoba_pesel, email)
	values (94110395847, 'tomek@domek.pl');
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, nrtel, pesel)
	values ('Zbigniew', 'Bejgrowicz', 'Mylna', 'Kwidzyn', '17', 600700800, 61082899815);
insert into PASAZER
	(osoba_pesel, email)
	values (61082899815, 'zbigniew@student.pg.gda.pl');
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Anna', 'Kowalska', 'Warszawska', 'Gdansk', 10, 15, 783196511, 89120147643);
insert into PASAZER
	(osoba_pesel, email)
	values (89120147643, 'anna@student.pg.gda.pl');



	
/*4) PRACOWNICY TACY ZWYKLI */
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Tomasz', 'Kosasz', 'Gdanska', 'Gdansk', 1, 60 , 100993322, 90119874245);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini, idwarsztatu)
	values (90119874245, 'mechanik', '2000-03-20', 3000, 'Lot', 2);
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Waldek', 'Kiepski', 'Warszawska', 'Gdansk', 3, 10 , 198743322, 90119871234);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini )
	values (90119871234, 'steward', '2010-05-10', 4400, 'Lufthansa');
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, nrtel, pesel)
	values ('Anna', 'Lipska', 'Do studzienki', 'Gdansk', 9, 600987456, 90039584124);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini )
	values (90039584124, 'steward', '2001-09-11', 4400, 'Wizzair');
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Adam', 'Sadam', 'Wolnosci', 'Gdansk', 1, 11 , 783154984, 88110297856);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki )
	values (88110297856, 'kelner', '2006-08-01', 1700);
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, nrtel, pesel)
	values ('Mahomet', 'Aldzazir', 'Rozowa', 'Gdansk', 88, 974513963, 90030311234);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki)
	values (90030311234, 'kierownik', '1998-01-20', 15000);
	
/*5) PILOCI */
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Tomasz', 'Problem', 'Pilotow', 'Gdansk', 10, 10, 777888123, 90012345624);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini )
	values (90012345624, 'pilot', '2000-09-11', 8800, 'Wizzair');
insert into PILOT
	values (90012345624, 'PL-98-1043', 50);
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Zygmunt', 'Hajzer', 'Startowa', 'Gdansk', 17, 10, 777888321, 90065432124);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini )
	values (90065432124, 'pilot', '2012-08-01', 12000, 'Lot');
insert into PILOT
	values (90065432124, 'PL-00-8451', 90);
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, numer_mieszkania, nrtel, pesel)
	values ('Zbigniew', 'Rakitic', 'Pilotow', 'Gdansk', 9, 17, 775889821, 90088512124);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini )
	values (90088512124, 'pilot', '2012-08-01', 9999, 'Ryanair');
insert into PILOT
	values (90088512124, 'PL-11-4446', 781);
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, nrtel, pesel)
	values ('Cristiano', 'Ronaldo', 'Krakowska', 'Warszawa', 15, 775881111, 87010112124);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini )
	values (87010112124, 'pilot', '2010-08-01', 20000, 'Lufthansa');
insert into PILOT
	values (87010112124, 'PL-01-0152', 300);
	
insert into OSOBA
	(imie, nazwisko, ulica, miasto, numer_domu, nrtel, pesel)
	values ('Leo', 'Messi', 'Warszawska', 'Krakow', 51, 775889999, 78101012124);
insert into PRACOWNIK
	(osoba_pesel, stanowisko, datarozp, zarobki, idlini )
	values (78101012124, 'pilot', '2010-08-01', 19999, 'JanuszPol');
insert into PILOT
	values (78101012124, 'PL-01-0101', 299);
	

/*9) SAMOLOTY */

insert into SAMOLOT
	values ('13DZA', 'cessna', '172c', 2010, 4, 'JanuszPol', NULL);
	
insert into SAMOLOT
	values ('14KZS', 'boeing', '737', 2000, 350, 'Wizzair', 1);

insert into SAMOLOT
	values ('59KZA', 'bell', '1244', 2001, 6, 'Ryanair', 3);
	
insert into SAMOLOT
	values ('90ZAA', 'boeing', '737', 2003, 350, 'Lufthansa', NULL);
	
insert into SAMOLOT
	values ('8789Z', 'boeing', '777', 2015, 400, 'Lot', NULL);
	
insert into SAMOLOT
	values ('PLZ14', 'boeing', '757', 2009, 300, 'EtiAirlines', 4);
	
insert into SAMOLOT
	values ('3213P', 'bell', '3346', 2008, 10, 'EtiAirlines', NULL);
	
insert into SAMOLOT
	values ('134ZS', 'boeing', '737', 2011, 350, 'Airforce', 2);
	
insert into SAMOLOT
	values ('4123Z', 'bell', '444', 2014, 15, 'PolskiSamolot', NULL);
	
insert into SAMOLOT
	values ('41PPP', 'cessna', '172c', 1999, 4, 'Emirates', NULL);


	
	
/*6) LOTY */

insert into LOT
	values ('FJK911', '2000-01-01', '2000-01-01', '12:00', '14:00', 15, 'Gdansk', 'Krakow', 78101012124, '14KZS');
	
insert into LOT
	values ('ABC000', '2001-01-01', '2001-01-01', '13:00', '19:50', 200, 'Warszawa', 'Gdansk', 87010112124,'134ZS');

insert into LOT
	values ('ZKJ987', '2000-03-11', '2000-03-12', '12:00', '14:00', 260, 'Gdansk', 'Sydney', 87010112124, '14KZS');

insert into LOT
	values ('KKK666', '2010-01-07', '2010-01-07', '12:00', '14:00', 15, 'Gdansk', 'Oxford', 78101012124,'PLZ14');

insert into LOT
	values ('FKK000', '2000-11-01', '2000-11-01', '15:00', '16:00', 15, 'Gdansk', 'Kijow', 87010112124, '90ZAA');

insert into LOT
	values ('XKD222', '2011-05-01', '2011-05-01', '20:00', '21:00', 15, 'Gdansk', 'Oslo', 90012345624, '14KZS');
	
insert into LOT
	values ('FKK009', '2009-07-04', '2009-07-05', '08:00', '19:00', 15, 'Gdansk', 'Kuwejt', 90012345624,'8789Z');	

insert into LOT
	values ('BOO911', '2001-09-10', '2001-09-11', '17:00', '18:00', 15, 'Gdansk', 'Nowy Jork', 78101012124, '134ZS');
	
insert into LOT
	values ('TRR112', '1999-07-05', '1999-07-06', '10:00', '14:00', 15, 'Gdansk', 'Los Angeles', 90065432124, '90ZAA');
	
/*7) ZAMOWIENIA */

insert into ZAMOWIENIE 
	values ('2000-01-01',1111, 90111158245);
	
insert into ZAMOWIENIE 
	values ('2000-01-01',13241,61082899815);

insert into ZAMOWIENIE 
	values ('2000-03-11',2342,90111158245);
             
insert into ZAMOWIENIE 
	values ('2010-01-07',1122,94110807754);

insert into ZAMOWIENIE 
	values ('2000-11-01',5543,61082899815);

insert into ZAMOWIENIE 
	values ('2011-05-01',155,90111158245);

insert into ZAMOWIENIE 
	values ('2009-07-04',2342,94110807754);

insert into ZAMOWIENIE 
	values ('2000-09-01',5432,90111158245);

insert into ZAMOWIENIE 
	values ('2001-09-10',1432,61082899815);

insert into ZAMOWIENIE 
	values ('1999-07-05',155,94110807754);

insert into ZAMOWIENIE 
	(datazamowienia, idpasazera)
	values ('1999-01-20',94110807754);
	
	
/*8) URLOPY */
insert into URLOP
	values ('2015-10-08', '2015-10-10', 'zdrowotny', 90088512124);
	
insert into URLOP
	values ('2015-01-10', '2015-01-17', 'zadanie', 90012345624);
	
insert into URLOP
	values ('2015-02-10', '2015-02-17', 'przymusowy', 87010112124);

insert into URLOP
	values ('2015-03-10', '2015-03-17', 'zadanie', 87010112124);
	
insert into URLOP
	values ('2015-04-10', '2015-04-17', 'zdrowotny', 90012345624);
	
insert into URLOP
	values ('2015-05-10', '2015-05-17', 'zdrowotny', 87010112124);
	
insert into URLOP
	values ('2015-06-10', '2015-06-17', 'przymusowy', 87010112124);
	
insert into URLOP
	values ('2015-07-10', '2015-07-17', 'zdrowotny', 90012345624);
	
insert into URLOP
	values ('2015-08-10', '2015-08-17', 'zdrowotny', 78101012124);
	
insert into URLOP
	values ('2015-09-10', '2015-09-17', 'przymusowy', 78101012124);
		
/*10) ZAMOWIENIA - LOT */

	insert into LOT_ZAM
		values ('FJK911', 1);
		
	insert into LOT_ZAM
		values ('XKD222', 3);
		
	insert into LOT_ZAM
		values ('KKK666', 2);
		
	insert into LOT_ZAM
		values ('FJK911', 5);
		
	insert into LOT_ZAM
		values ('FJK911', 4);
		
	insert into LOT_ZAM
		values ('KKK666', 5);
		
	insert into LOT_ZAM
		values ('XKD222', 1);
		
	insert into LOT_ZAM
		values ('BOO911', 4);

	insert into LOT_ZAM
		values ('FJK911', 6);
		
	insert into LOT_ZAM
		values ('XKD222', 7);
		
	insert into LOT_ZAM
		values ('KKK666', 8);
		
	insert into LOT_ZAM
		values ('FJK911', 9);
		
	insert into LOT_ZAM
		values ('FJK911', 10);
		
	insert into LOT_ZAM
		values ('KKK666', 10);
		
	insert into LOT_ZAM
		values ('XKD222', 9);
		
	insert into LOT_ZAM
		values ('BOO911', 8);
		
		
/*11) LOTY - PASAZEROWIE */ 
	insert into LOT_PAS
		values ('FJK911', 94110807754);
		
	insert into LOT_PAS
		values ('XKD222', 90111158245);
		
	insert into LOT_PAS
		values ('KKK666', 94110807754);
		
	insert into LOT_PAS
		values ('FJK911', 89120147643);
		
	insert into LOT_PAS
		values ('FJK911', 61082899815);
		
	insert into LOT_PAS
		values ('KKK666', 94110395847);
		
	insert into LOT_PAS
		values ('XKD222', 61082899815);
		
	insert into LOT_PAS
		values ('BOO911', 89120147643);
		
		
/*12) SAMOLOT - PILOT */
	insert into SAM_PIL
		values ('13DZA', 90012345624);
	insert into SAM_PIL
		values ('14KZS', 90065432124);
	insert into SAM_PIL
		values ('90ZAA', 87010112124);
	insert into SAM_PIL
		values ('8789Z', 90012345624);
	insert into SAM_PIL
		values ('14KZS', 78101012124);
	insert into SAM_PIL
		values ('90ZAA', 90065432124);
	insert into SAM_PIL
		values ('4123Z', 87010112124);
	insert into SAM_PIL
		values ('8789Z', 78101012124);
	insert into SAM_PIL
		values ('4123Z', 90012345624);
	
	








	
	




	
