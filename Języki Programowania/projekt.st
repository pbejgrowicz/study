<?xml version="1.0"?>

<st-source>
<time-stamp>From VisualWorks® Personal Use Edition, 8.1 of 24 lipca 2015 on 12 listopada 2015 at 20:25:04</time-stamp>


<component-created>
<name>projekt</name> <type>package</type>
</component-created><!-- Package projekt* -->


<component-created>
<name>projekt</name> <type>package</type>
</component-created>

<class>
<name>Wielokat</name>
<environment>Smalltalk</environment>
<super>Core.Object</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>wierzcholki nazwa </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category>JezykiProgramowania</category>
<attributes>
<package>projekt</package>
</attributes>
</class>

<comment>
<class-id>Wielokat</class-id>
<body>Wielokat podklasa Object</body>
</comment>

<class>
<name>TrojkatRownoramienny</name>
<environment>Smalltalk</environment>
<super>Wielokat</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>a h </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category>JezykiProgramowania</category>
<attributes>
<package>projekt</package>
</attributes>
</class>

<comment>
<class-id>TrojkatRownoramienny</class-id>
<body>Trojkat Rownoboczny podklasa Wielokatu.</body>
</comment>

<class>
<name>Kwadrat</name>
<environment>Smalltalk</environment>
<super>Wielokat</super>
<private>false</private>
<indexed-type>none</indexed-type>
<inst-vars>bok </inst-vars>
<class-inst-vars></class-inst-vars>
<imports></imports>
<category>JezykiProgramowania</category>
<attributes>
<package>projekt</package>
</attributes>
</class>

<comment>
<class-id>Kwadrat</class-id>
<body>Kwadrat podklasa Wielokatu</body>
</comment>

<methods>
<class-id>Wielokat</class-id> <category>accessing</category>

<body package="projekt" selector="nazwa:">nazwa: nowa_nazwa	"ustawia nowa nazwe wielokata"	nazwa:=nowa_nazwa</body>

<body package="projekt" selector="nazwa">nazwa	"podaje nazwe wielokata"	^nazwa</body>
</methods>

<methods>
<class-id>Wielokat</class-id> <category>printing</category>

<body package="projekt" selector="drukuj">drukuj | iloscwierzcholkow |iloscwierzcholkow:= wierzcholki size.1 to: iloscwierzcholkow do: [:i | Transcript show: '(' , (wierzcholki at: i) x printString, ',' , (wierzcholki at: i) y printString, ')' ;cr].</body>
</methods>

<methods>
<class-id>Wielokat</class-id> <category>actions</category>

<body package="projekt" selector="obrot">obrot| rozwierzch nowewierzch |rozwierzch:= wierzcholki size.nowewierzch:=Array new: rozwierzch.1 to: rozwierzch do: [:i | nowewierzch at: i  put: ((wierzcholki at: i) y)@(((wierzcholki at: i) x ) * (-1))]. " prawo "wierzcholki:= nowewierzch.</body>
</methods>

<methods>
<class-id>Wielokat</class-id> <category>initialize-release</category>

<body package="projekt" selector="initialize:name:">initialize: liczbaWierzcholkow name: nowaNazwa	"konstruktor obiektu - wielokata"	nazwa:=nowaNazwa.	wierzcholki:=Array new: liczbaWierzcholkow.	wierzcholki at: 1 put: 0@0.</body>
</methods>


<methods>
<class-id>TrojkatRownoramienny</class-id> <category>printing</category>

<body package="projekt" selector="drukuj">drukujTranscript show: 'Podstawa trojkata wynosi: ' , a printString; cr; 		show: 'Wysokosc trojkata wynosi:  ' , h printString; cr;		show: 'Pole: ', self pole printString; cr.super drukuj.</body>
</methods>

<methods>
<class-id>TrojkatRownoramienny</class-id> <category>arithmetic</category>

<body package="projekt" selector="+">+ figura	"dodaj 2 figury w sensie pola"	| pole proporcje newa newh |	proporcje:= a/h.	pole:=self pole + figura pole.	newh:= ((2 * pole)/proporcje) sqrt.	newa:= proporcje * newh.	^(TrojkatRownoramienny new) initialize: newa wysokosctroj: newh.</body>
</methods>

<methods>
<class-id>TrojkatRownoramienny</class-id> <category>actions</category>

<body package="projekt" selector="pole">pole	"liczy pole trojkata rownoramiennego"	^(a * h)/2.</body>
</methods>

<methods>
<class-id>TrojkatRownoramienny</class-id> <category>initialize-release</category>

<body package="projekt" selector="initialize:wysokosctroj:">initialize: pods wysokosctroj: wyso	"tworzenie trojkota rownoramiennego"		a:= pods.	h:=wyso.		super initialize: 3 name: 'Trojkat Rownoramienny'.	wierzcholki at: 2 put: a@0.	wierzcholki at: 3 put: (a/2.0)@h.</body>
</methods>


<methods>
<class-id>Kwadrat</class-id> <category>printing</category>

<body package="projekt" selector="drukuj">drukujTranscript show: 'Bok kwadratu wynosi: ' , bok printString; cr;	show: 'Pole: ' , self pole printString; cr.  super drukuj.</body>
</methods>

<methods>
<class-id>Kwadrat</class-id> <category>arithmetic</category>

<body package="projekt" selector="+">+ figura	"dodaj 2 figury w sensie pola"	| p |	p:=self pole + figura pole.	^(Kwadrat new) initialize: p sqrt</body>
</methods>

<methods>
<class-id>Kwadrat</class-id> <category>actions</category>

<body package="projekt" selector="pole">pole	"oblicza bok kwadratu"	^bok squared</body>
</methods>

<methods>
<class-id>Kwadrat</class-id> <category>initialize-release</category>

<body package="projekt" selector="initialize:">initialize: bok1	"tworz kwadrat o podanym boku"	bok:=bok1.		super initialize: 4 name: 'Kwadrat'.	wierzcholki at: 2 put: bok1@0.	wierzcholki at: 3 put: bok1@bok1.	wierzcholki at: 4 put: 0@bok1.</body>
</methods>



</st-source>
