Proces izdaj
============

Ta dokument razlaga Symfony proces izdaj (Symfony pomeni kodo
gostovano na glavnem ``symfony/symfony`` `Git repozitoriju`_).

Symfony upravlja svoje izdaje skozi *časovno osnovan model*: nova Symfony
izdaja pride ven vsakih *šest mesecev*: ena v *maju* in ena v *novembru*.

.. note::

    Ta proces izdaj je bil sprejet od Symfony 2.2 in vsa
    "pravila" razložena v tem dokumentu morajo biti striktno sledena od Symfony
    2.4.

.. _contributing-release-development:

Razvoj
------

Šest mesečno obdobje je razdeljeno v dve fazi:

* *Razvoj*: *Štiri mesece* za dodajanje novih lastnosti in izboljšati
  obstoječe;

* *Stabilizacija*: *Dva meseca* za popravek hroščev, pripravo izdaje in počakati celoten
  Symfony ekosistem (tretje osebne knjižnice, pakete in
  projekte, ki uporabljajo Symfony), da dohitijo.

Med razvojno fazo, je katerakoli nova lastnost lahko vrnjena, če ne bo dokončana
v času ali če ne bo dovolj stabilna, da bi bila vključena v trenutno
končno izdajo.

.. _contributing-release-maintenance:

Vzdrževanje
-----------

Vsaka Symfony verzija je vzdrževana za fiksno časovno obdobje, odvisno od
tipa izdaje. Imamo dve vzdrževalni obdobji:

* *Popravki hroščev in varnostni popravki*: Med tem obdobjem, so vse težave lahko popravljene.
  Konec tega obdobja je sklicano kot *konec vzdrževanja*
  izdaje.

* *Samo varnostni popravki*: Med tem obdobjem, so lahko popravljeni samo varnostne
  težave. Konec tega obdobja je sklican kot *konec življenske dobe*
  izdaje.

Standardne izdaje
~~~~~~~~~~~~~~~~~

Standardna izdaja je vzdrževana v obdobju *osmih mesecev* za popravke hroščev,
in v obdobju *štirinajst mesecev* za popravke varnostnih težav.

Izdaje z dolgoročno podporo
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vsaki dve leti je nova izdaja z dolgoročno podporo (znana tudi kot LTS izdaja)
objavljena. Vsaka LTS izdaja je podprta v obdobju *treh let*  za popravke hroščev
in v obdobju *štirih let* za popravke varnostnih težav.

.. note::

    Plačljiva podpora po podpori treh let s strani skupnosti je lahko tudi
    kupljena s strani `SensioLabs`_.

Urnik
-----

Spodaj je urnik za prvih nekaj verzij, ki uporabljajo ta model izdaj:

.. image:: /images/release-process.jpg
   :align: center

* **Rumena** predstavlja razvojno fazo
* **Modra** predstavlja stabilizacijsko fazo
* **Zelena** predstavlja obdobje vzdrževanja

To se odraža v zelo predvidljivih datumih in obdobjih vzdrževanja:

+---------+---------+---------------------+-----------------------+
| Verzija | Izdaja  | Konec vzdrževanja   | Konec življenske dobe |
+=========+=========+=====================+=======================+
| 2.0     | 07/2011 | 03/2013 (20 months) | 09/2013               |
+---------+---------+---------------------+-----------------------+
| 2.1     | 09/2012 | 05/2013 (9 months)  | 11/2013               |
+---------+---------+---------------------+-----------------------+
| 2.2     | 03/2013 | 11/2013 (8 months)  | 05/2014               |
+---------+---------+---------------------+-----------------------+
| **2.3** | 05/2013 | 05/2016 (36 months) | 05/2017               |
+---------+---------+---------------------+-----------------------+
| 2.4     | 11/2013 | 07/2014 (8 months)  | 01/2015               |
+---------+---------+---------------------+-----------------------+
| 2.5     | 05/2014 | 01/2015 (8 months)  | 07/2016               |
+---------+---------+---------------------+-----------------------+
| 2.6     | 11/2014 | 07/2015 (8 months)  | 01/2016               |
+---------+---------+---------------------+-----------------------+
| **2.7** | 05/2015 | 05/2018 (36 months) | 05/2019               |
+---------+---------+---------------------+-----------------------+
| 2.8     | 11/2015 | 07/2016 (8 months)  | 01/2017               |
+---------+---------+---------------------+-----------------------+
| ...     | ...     | ...                 | ...                   |
+---------+---------+---------------------+-----------------------+

.. tip::

    Če želite izvedeti več o časovnici katerekoli dane verzije Symfony
    uporabite `časovni kalkulator`_ na spletu. Lahko dobite tudi vse podatke kot JSON
    niz preko URL-ja kot `http://symfony.com/roadmap.json?version=2.x`.

Združljivost za nazaj
---------------------

Po izdaji Symfony 2.3 bo združjivost za nazaj ohranjena ne glede
na kaj. Če ni možno, bo lastnost, izboljšava ali popravek hrošča
predviden za naslednjo glavno verzijo: Symfony 3.0.

.. note::

    Delo na Symfony 3.0 bo pričeto, kadar bo dovolj glavnih lastnosti, ki pokvarijo
    združljivost za nazaj, čakalo na todo seznamu.

Razvrednotenja
--------------

Ko implementacija lastnosti ne more biti zamenjana z boljšo brez
pokvarjenja zlomljivosti za nazaj, je še vedno možnost razvrednotiti
staro implementacijo in dodati novo prednostno zraven. Preberite
dokument :ref:`konvencije <contributing-code-conventions-deprecations>`, da
izvedete več o tem, kako so razvrednotenja upravljana v Symfony.

Razlog
-------

Ta proces izdaj je bil sprejet, da da več *predvidljivosti* in
*transparentnosti*. Bilo je razpravljano na osnovi sledečih ciljev:

* Skrajšati cikel izdaj (omogoča razvijalcem, da koristijo iz novih
  lastnosti hitreje);
* Dati več vidnosti razvijalcem, ki uporabljajo ogrodje in odprto kodnim
  projektom, ki uporabljajo Symfony;
* Izboljšati izkušnjo ljudem, ki prispevajo Symfony jedru: vsi vedo, ko je
  lastnost na voljo v Symfony;
* Koordinacija Symfony časovnice s popularnimi PHP projekti, ki dobro delujejo
  s Symfony in s projekti, ki uporabljajo Symfony;
* Dati čas Symfony ekosistemu, da dohiti nove verzije
  (avtorji paketov, pisci dokumentacije, prevajalci, ...)

Šest mesečno obdobje je bilo izbrano, saj dve izdaji prideta v leto. Tudi omogoča
dovolj časa za delo na novih lastnostih in omogoča nepripravljenim
lastnostim, da so prestavljene v naslednjo izdajo brez, da morajo čakati predolgo
za naslednji cikel.

Način dvojnega vzdrževanja je bil sprejet, da naredi vsakega Symfony uporabnika srečnega. Hitri
uporabniki, ki želijo delati z zadnjim in najboljšim, uporabijo standardne
izdaje: nova verzija je izdana vsakih šest mesecev in je dvo mesečno časovno
obdobje za nadgradnje. Podjetja, ki želijo več stabilnosti uporabijo LTS
izdaje: nova verzija je objavljena vsaki dve leti in na voljo je leto za
nadgradnje.

.. _Git repozitoriju: https://github.com/symfony/symfony
.. _SensioLabs:     http://sensiolabs.com/
.. _roadmap:        http://symfony.com/roadmap
.. _`časovni kalkulator`: http://symfony.com/roadmap
