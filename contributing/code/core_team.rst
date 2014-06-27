Glavna ekipa Symfony
====================

Ta dokument zatrjuje pravila, ki se tičejo glavne skupine Symfony. Ta pravila
so efektivna nad publikacijami tega dokumenta in vsi glavni člani Symfony-ja
se morajo držati povedanih pravil in protokola.

Organizacija jedra
------------------

Glavni člani Symfony-ja so razdeljeni v tri skupine. Vsak član lahko pripada samo
eni skupini naenkrat. Te privilegiji dodeljeni skupini so avtomatično
dodeljeni vsem skupinam višjih prioritet.

Glavne skupine Symfony v padajočem redu prioritet so sledeče:

1. **Vodja projekta**

* Voli člane v katerokoli drugo skupino;
* Združuje poslane zahtevke v vseh Symfony repozitorijih.

2. **Združilci**

* Združijo poslane zahtevke za komponento ali komponente na kateri imajo
  dodeljene privilegije.

3. **Odločilci**

* Odločajo ali združiti ali zavrniti poslani zahtevek.

Aktivni glavni člani
~~~~~~~~~~~~~~~~~~~~

.. role:: leader
.. role:: merger
.. role:: decider

* **Vodja projekta**:

  * **Fabien Potencier** (:leader:`fabpot`).

* **Združilci**:

  * **Bernhard Schussek** (:merger:`webmozart`) lahko združuje v Form_,
    Validator_, Icu_, Intl_, Locale_, OptionsResolver_ in PropertyAccess_
    komponentah;

  * **Tobias Schultze** (:merger:`Tobion`) lahko združuje v Routing_
    komponento;

  * **Romain Neutron** (:merger:`romainneutron`) lahko združuje v
    Process_ komponento;

  * **Nicolas Grekas** (:merger:`nicolas-grekas`) lahko združuje v Debug_
    komponento.

* **Odločilci**:

  * **Christophe Coevoet** (:decider:`stof`);
  * **Jakub Zalas** (:decider:`jakzal`);
  * **Jordi Boggiano** (:decider:`seldaek`);
  * **Lukas Kahwe Smith** (:decider:`lsmith77`).

Vloga za glavno članstvo
~~~~~~~~~~~~~~~~~~~~~~~~

Trenutno nove vloge za glavno članstvo Symfony niso sprejete.

Preklic glavnega članstva
~~~~~~~~~~~~~~~~~~~~~~~~~

Glavno članstvo Symfony-ja je lahko preklicano iz sledečih razlogov:

* Zavračanje sledenja pravilom in politiki povedani v tem dokumentu;
* Pomanjkanje aktivnosti za zadnjih šest mesecev;
* Namerna malomarnost ali namen oškodovati projekt Symfony;
* Glede na odločitev **vodje projekta**.

Ali bi morali sprejemati nove glavne člane Symfony v prihodnosti, preklicani
člani morajo počakati vsaj 12 mesecev preden se ponovno prijavijo.

Pravila razvoja kode
--------------------

Razvoj projekta Symfony je osnovan na poslanih zahtevkih predlaganih s strani kateregakoli člana
skupnosti Symfony. Sprejetje poslanih zahtevkov ali zavrnitev je odločana na osnovi
glasov glavnih članov Symfony.

Glasovalna politika poslanih zahtevkov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* ``-1`` glasovi morajo biti vedno upravičeni s tehničnimi in objektivnimi razlogi;

* ``+1`` glasovi ne potrebujejo upravičenja, razen če je samo en
  ``-1`` glas;

* Glavni člani lahko spremenijo svoje glasove kolikokrat hočejo
  med potekom diskusije poslanega zahtevka;

* Glavni člani ne smejo glasovati na svojih lastnih poslanih zahtevkih.

Politika združevanja poslanih zahtevkov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Poslani zahtevek **je lahko združen** če:

* Je bilo dano dovolj časa za celoten pregled (nekaj minut za napake ali manjše
  spremembe, vsaj 2 dni za "splošne" poslane zahtevke in 4 dni za poslane
  zahtevke z "pomembnim vplivom");

* Je manjša sprememba [1]_, ne glede na število glasov;

* Vsaj **združilec** komponente ali ostala dva glavna člana sta glasovala ``+1``
  in noben glavni član ni glasoval ``-1``.

Proces združevanja poslanih zahtevkov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vsa koda mora biti poslana v repozitorij preko poslanih zahtevkov, razen za
manjše spremembe [1]_, ki so lahko poslane direktno v repozitorij.

**Združilci** morajo vedno uporabljati orodje ukazne vrstice ``gh`` ponujeno s strani
**vodje projekta**, ki združi poslane zahtevke.

Politika izdaj
~~~~~~~~~~~~~~

**Vodja projekta** je tudi upravitelj izdaj za vsako verzijo Symfony.

Glavna pravila Symfony in protokol predlogov sprememb
-----------------------------------------------------

Pravila opisana v tem dokumentu so lahko predlagana kadarkoli
na diskretnost **vodje projekta**.


.. [1] Manjše spremembe vsebujejo napake, popravke DocBlock, kršitve kodnih
       standardov in manjše CSS, JavaScript in HTML spremembe.

.. _Form: https://github.com/symfony/Form
.. _Validator: https://github.com/symfony/Validator
.. _Icu: https://github.com/symfony/Icu
.. _Intl: https://github.com/symfony/Intl
.. _Locale: https://github.com/symfony/Locale
.. _OptionsResolver: https://github.com/symfony/OptionsResolver
.. _PropertyAccess: https://github.com/symfony/PropertyAccess
.. _Routing: https://github.com/symfony/Routing
.. _Process: https://github.com/symfony/Process
.. _Debug: https://github.com/symfony/Debug
