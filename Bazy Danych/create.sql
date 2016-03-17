CREATE TABLE OSOBA 
(
	imie varchar(40) not null,
	nazwisko varchar(100) not null,
	ulica varchar(255) not null,
	miasto varchar(100) not null,
	numer_domu int not null,
	numer_mieszkania int,
	nrtel int,
	pesel varchar(11) not null PRIMARY KEY
);

CREATE TABLE LINIALOTNICZA
(
	nazwa varchar(255) not null PRIMARY KEY
)

CREATE TABLE WARSZTAT 
(
	powierzchnia int not null,
	iloscmiejsc int check (iloscmiejsc >= 0),
	closehours time(0),
	id int not null PRIMARY KEY
)

ALTER TABLE WARSZTAT
	ADD openhours time(0);


CREATE TABLE PRACOWNIK
(
	osoba_pesel varchar(11) not null REFERENCES OSOBA(pesel) ON DELETE CASCADE,
	PRIMARY KEY(osoba_pesel),
	id int IDENTITY(1,1),
	stanowisko varchar(255) not null,
	datarozp date not null,
	datazako date,
	zarobki int not null check (zarobki > 0),
	idlini varchar(255) REFERENCES LINIALOTNICZA(nazwa),
	idwarsztatu int REFERENCES WARSZTAT(id ),
);

CREATE TABLE PASAZER
(
	osoba_pesel varchar(11) not null REFERENCES OSOBA(pesel) ON DELETE CASCADE,
	PRIMARY KEY(osoba_pesel),
	email varchar(255),
);

CREATE TABLE PILOT
(
	osoba_pesel varchar(11) REFERENCES PRACOWNIK(osoba_pesel) ON DELETE CASCADE,
	PRIMARY KEY(osoba_pesel),
	numerlicencji varchar(20) unique,
	ilosclotow int default 0,
);

CREATE TABLE SAMOLOT(
	nrsamolotu varchar(25) PRIMARY KEY,
	nazwa varchar(255) not null,
	model varchar(255) not null,
	rokprodukcji int check (rokprodukcji >= 1900) not null,
	iloscmiejsc int check (iloscmiejsc >= 0) not null,
	idlini varchar(255) REFERENCES LINIALOTNICZA(nazwa),
	idwarsztatu int REFERENCES WARSZTAT(id)
)

CREATE TABLE LOT
(
	numerlotu varchar(20)PRIMARY KEY,
	dataw date not null,
	datap date not null,
	godzo time(0) not null,
	godzp time(0) not null,
	iloscosob int check (iloscosob >=0),
	miejscew varchar(255) not null,
	miejscep varchar(255) not null,
	idpilota varchar(11) not null REFERENCES PILOT(osoba_pesel),
	idsamolotu varchar(25) not null REFERENCES SAMOLOT(nrsamolotu)
)



CREATE TABLE ZAMOWIENIE 
(
	id int IDENTITY(1,1) PRIMARY KEY,
	datazamowienia date not null ,
	cena int check (cena >= 0) default 0,
	idpasazera varchar(11) not null REFERENCES PASAZER(osoba_pesel),
)

CREATE TABLE URLOP
(
	id int IDENTITY(1,1) PRIMARY KEY,
	datar date not null,
	dataz date not null,
	typ varchar(14) not null check (typ in('zdrowotny','zadanie','przymusowy')),
	idpracownika varchar(11) REFERENCES PRACOWNIK(osoba_pesel)
)



CREATE TABLE LOT_ZAM
(
	lot varchar(20) REFERENCES LOT(numerlotu),
	zam int references ZAMOWIENIE(id),
	Primary key(lot, zam)
)

CREATE TABLE LOT_PAS
(
	lot varchar(20) REFERENCES LOT(numerlotu),
	pas varchar(11) REFERENCES PASAZER(osoba_pesel),
	Primary key(lot, pas)
)

CREATE TABLE SAM_PIL
(
	sam varchar(25) REFERENCES SAMOLOT(nrsamolotu) ON DELETE NO ACTION,
	pil varchar(11) REFERENCES PILOT(osoba_pesel) ON DELETE NO ACTION,
	Primary key(sam, pil)
)
