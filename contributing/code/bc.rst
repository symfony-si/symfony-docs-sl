Naša obljuba združljivosti za nazaj
===================================

Zagotavljanje gladkih nadgradenj vaših projektov je naša glavna prioriteta. Zato
vam obljubljamo združljivost za nazaj (backward compatibility - BC) za vse manjše Symfony izdaje.
Verjetno prepoznate to strategijo kot `semantične verzije`_. Na kratko
semantične verzije pomenijo, da so samo glavne izdaje (kot je 2.0, 30 itd)
dovoljene podreti združljivost za nazaj. Manjše verzije (kot so 2.5, 2.6 itd)
lahko predstavijo nove lastnosti, vendar morajo to narediti brez da podrejo obstoječi API
določene veje izdaje (2.x v prejšnjem primeru).

.. caution::

    Ta obljuba je bila predstavljena s Symfony 2.3 in se ne nanaša na prejšnje
    izdaje Symfony.

Vendar pa združljivost za nazaj prihaja v večih različnih okusih. V bistvu, skoraj
vsaka sprememba, ki jo naredimo na ogrodju, lahko potencialno zlomi aplikacijo.
Na primer, če dodamo novo metodo razredu, bo to zlomilo aplikacijo,
ki razširja ta razred in dodaja enako metodo vendar z različnim
podpisom metode.

Tudi ne vsak zlom združljivosti za nazaj ima enak vpliv na kodo aplikacije. Medtem ko zlomi nekaterih združljivosti
za nazaj zahtevajo od vas, da naredite pomembne spremembe vašim razredom ali vaši
arhitekturi, so ostali popravljeni enostano kot sprememba imena metode.

Zato smo za vas ustvarili to stran. Sekcija "Uporaba kode Symfony" vam bo
povedala, kako lahko zagotovite, da se vaša aplikacija ne bo v celoti zlomila, ko
jo nadgrajujete na novo verzijo iste veje glavne izdaje.

Druga sekcija "Delo na kodi Symfony" cilja na Symfony
prispevalce. Ta sekcija ponuja seznam podrobnih pravil, ki jim morra vsak uporabnik, ki prispeva
slediti, da zagotovimo gladke nadgradnje za naše uporabnike.

Uporaba kode Symfony
--------------------

Če uporabljate Symfony v vaših projektih, vam bodo sledeče smernice pomagale
zagotoviti gladke nadgradnje za vse glavne manjše izdaje vaše verzije
Symfony.

Uporaba naših vmesnikov
~~~~~~~~~~~~~~~~~~~~~~~

Vsi vmesniki dostavljeni s Symfony so lahko uporabljeni pri t.i. namigovanju tipov (type hints). Lahko tudi kličete
katerokoli metodo, ki jo razglašajo. Garantiramo, da ne bomo zlomili kode, ki
se drži teh pravil.

.. caution::

    Izjema temu pravilu so vmesniki označeni z ``@internal``. Taki
    vmesniki ne bi smeli biti uporabljeni ali implementirani.

Če želite implementirati vmesnik, bi morali najprej zagotoviti, da
je vmesnik vmesnik API-ja. Vmesnike API-ja lahko prepoznate po znački ``@api``
v njihovi izvorni kodi::

    /**
     * HttpKernelInterface handles a Request to convert it to a Response.
     *
     * @author Fabien Potencier <fabien@symfony.com>
     *
     * @api
     */
    interface HttpKernelInterface
    {
        // ...
    }

Če implementirate vmesnik API-ja, obljubljamo, da ne bomo nikoli zlomili vaše
kode. Nasprotno pa splošni vmesniki so lahko razširljivi med manjšimi izdajami
na primer z dodajanjem nove metode. Bodite pripravljeni nadgraditi vašo kodo ročno,
če implementirate splošni vmesnik.

.. note::

    Tudi če naredimo spremembe, ki zahtevajo ročno nadgradnjo, se omejujemo na
    spremembe, ki so lahko nadgrajene enostavno. Vedno bomo dokumentirali točna
    navodila nadgradnje v UPGRADE datoteki v vrhovnem direktoriju Symfony-ja.

Sledeča tabela razlaga v podrobnostih, kateri primeri uporabe so pokriti s strani naše
obljube združljivosti za nazaj:

+-----------------------------------------------+---------------+---------------+
| Primer uporabe                                | Splošni       | API           |
+===============================================+===============+===============+
| **Če ...**                                    | **Potem garaniramo BC...**    |
+-----------------------------------------------+---------------+---------------+
| Type hint against the interface               | Da            | Da            |
+-----------------------------------------------+---------------+---------------+
| Call a method                                 | Da            | Da            |
+-----------------------------------------------+---------------+---------------+
| **Če implementirate vmesnik in ...**          | **Potem garaniramo  BC...**   |
+-----------------------------------------------+---------------+---------------+
| Implementirate metodo                         | Ne [1]_       | Da            |
+-----------------------------------------------+---------------+---------------+
| Dodate argument v implementirano metodo       | Ne [1]_       | Da            |
+-----------------------------------------------+---------------+---------------+
| Dodate privzeto vrednost argumentu            | Da            | Da            |
+-----------------------------------------------+---------------+---------------+

.. include:: _api_tagging.rst.inc

Uporaba naših razredov
~~~~~~~~~~~~~~~~~~~~~~

Vsi razredi ponujeni s strani Symfony so lahko instancirani in dostopani preko njihovih
javnih metod in lastnosti.

.. caution::

    Razredi, lastnosti in metode, ki prenašajo značko ``@internal`` kot tudi
    razredi locirani v različnih imenskih prostorih ``*\\Tests\\`` so
    izjema temu pravilu. Mišljeni so samo za interno uporabo in ne bi smeli
    biti dostopani s strani vaše lastne kode.

Kot je z vmesniki, razlikujemo tudi med splošnimi in API razredi.
Kot vmesniki API-ka, so API razredi označeni z značko ``@api``::

    /**
     * Request represents an HTTP request.
     *
     * @author Fabien Potencier <fabien@symfony.com>
     *
     * @api
     */
    class Request
    {
        // ...
    }

Razlika med splošnimi in API razredi je, da garantiramo polno
združljivost za nazaj, če razširite API razred in prepišete njegove metode. Ne
moremo dati enake obljube za splošne razrede, ker lahko bomo na
primer dodali metodi opcijski argument. Posledično se podpis
vaše prepisane metode ne bi več ujemal in generiral usodne napake.

.. note::

    Kot pri vmesnikih, se omejujemo na spremembe, ki so lahko nadgrajene
    enostavno. Dokumentirali bomo točnost navodil nadgradnje v datoteki
    UPGRADE v vrhnjem direktoriju Symfony.

V nekaterih primerih, samo določene lastnosti in metode so označene z značko ``@api``,
četudi njihov razred ni. V teh primerih garantiramo polno združljivost
za nazaj za označene lastnosti in metode (kot je označeno v stolpcu
"API" spodaj), vendar ne za preostanek razreda.

Da ste na varni strani, preverite sledečo tabelo, da veste kateri primeri uporabe so
pokriti s strani naše obljube združljivosti za nazaj:

+----------------------------------------------------+------------------------------+-----+
| Primer uporabe                                     | Splošni                      | API |
+====================================================+==============================+=====+
| **Če ...**                                         | **Potem garantiramo BC ...** |     |
+----------------------------------------------------+------------------------------+-----+
| Namigovanje tipa proti razredu                     | Da                           | Da  |
+----------------------------------------------------+------------------------------+-----+
| Izdelava nove instance                             | Da                           | Da  |
+----------------------------------------------------+------------------------------+-----+
| Razširitev razreda                                 | Da                           | Da  |
+----------------------------------------------------+------------------------------+-----+
| Dostopanje do javne lastnosti                      | Da                           | Da  |
+----------------------------------------------------+------------------------------+-----+
| Klic javne metode                                  | Da                           | Da  |
+----------------------------------------------------+------------------------------+-----+
| **Če razširite razred in ...**                     | **Potem garantiramo BC ...** |     |
+----------------------------------------------------+------------------------------+-----+
| Dostopate do zaščitene lastnosti                   | Ne [1]_                      | Da  |
+----------------------------------------------------+------------------------------+-----+
| Kličete zaščiteno metodo                           | Ne [1]_                      | Da  |
+----------------------------------------------------+------------------------------+-----+
| Prepišete javno lastnost                           | Da                           | Da  |
+----------------------------------------------------+------------------------------+-----+
| Prepišete zaščiteno lastnost                       | Ne [1]_                      | Da  |
+----------------------------------------------------+------------------------------+-----+
| Prepišete javno metodo                             | Ne [1]_                      | Da  |
+----------------------------------------------------+------------------------------+-----+
| Prepišete zaščiteno metodo                         | Ne [1]_                      | Da  |
+----------------------------------------------------+------------------------------+-----+
| Dodate novo lastnost                               | Ne                           | Ne  |
+----------------------------------------------------+------------------------------+-----+
| Dodate novo metodo                                 | Ne                           | Ne  |
+----------------------------------------------------+------------------------------+-----+
| Dodate argument prepisani metodi                   | Ne [1]_                      | Da  |
+----------------------------------------------------+------------------------------+-----+
| Dodate privzeto vrednost argumentu                 | Da                           | Da  |
+----------------------------------------------------+------------------------------+-----+
| Kličete privatno metodo (preko Reflection)         | Ne                           | Ne  |
+----------------------------------------------------+------------------------------+-----+
| Dostopate do privatne lastnosti (preko Reflection) | Ne                           | Ne  |
+----------------------------------------------------+------------------------------+-----+

.. include:: _api_tagging.rst.inc

Delo na kodi Symfony
--------------------

Želite, da vam izboljšamo Symfony? To je odlično! Vendar prosimo, držite
se pravil napisanih spodaj, da zagotovimo gladke nadgradnje za naše uporabnike.

Sprememba vmesnikov
~~~~~~~~~~~~~~~~~~~

Ta tabela vam pove, katere spremembe lahko naredite, ko delate z
vmesniki Symfony:

==============================================  ==============  ==============
Tip spremembe                                   Splošni         API
==============================================  ==============  ==============
Popolna odstranitev                             Ne              Ne
Sprememba imena ali imenskega prostora          Ne              Ne
Dodajanje starševskega vmesnika                 Da [2]_         Da [3]_
Odstranitev starševskega vmesnika               Ne              Ne
**Metode**
Dodajanje metode                                Da [2]_         Ne
Odstranjevanje metode                           Ne              Ne
Sprememba imena                                 Ne              Ne
Premik k starševskemu vmesniku                  Da              Da
Dodajanje argumenta brez privzete vrednosti     Ne              Ne
Dodajanje argumenta s privzeto vrednostjo       Da [2]_         Ne
Odstranjevanje argumenta                        Da [4]_         Da [4]_
Dodajanje privzete vrednosti argumentu          Da [2]_         Ne
Odstranjevanje privzete vrednosti argumenta     Ne              Ne
Dodajanje namiga tipa argumentu                 Ne              Ne
Odstranjevanje namiga tipa argumentu            Da [2]_         Ne
Sprememba tipa argumenta                        Da [2]_ [5]_    Ne
Sprememba vrnjenega tipa                        Da [2]_ [6]_    Ne
==============================================  ==============  ==============

Spreminjanje razredov
~~~~~~~~~~~~~~~~~~~~~

Ta tabela vam pove, katere spremembe lahko naredite, ko delate z
razredi Symfony-ja:

==================================================  ==============  ==============
Tip spremembe                                       Splošni         API
==================================================  ==============  ==============
Popolna odstranitev                                 Ne              Ne
Narediti razred končnega - "final"                  Ne              Ne
Narediti abstraktnega                               Ne              Ne
Sprememba imena ali imenskega prostora              Ne              Ne
Sprememba starševskega razreda                      Da [7]_         Da [7]_
Dodajanje vmesnika                                  Da              Da
Odstranjevanje vmesnika                             Ne              Ne
**Javne lastnosti**
Dodajanje javnih lastnosti                          Da              Da
Odstranjevanje javne lastnosti                      Ne              Ne
Zmanjšanje vidnosti                                 Ne              Ne
Premik k starševskemu razredu                       Da              Da
**Zaščitene lastnosti**
Dodajanje zaščitene lastnosti                       Da              Da
Odstranejvanje zapščitene lastnosti                 Da [2]_         Ne
Zmanjšanje vidnosti                                 Da [2]_         Ne
Premik k starševskemu razredu                       Da              Da
**Privatne lastnosti**
Dodajanje privatnih lastnosti                       Da              Da
Odstranjevanje privatnih lastnosti                  Da              Da
**Konstruktorji**
Dodajanje konstruktorja brez obveznih argumentov    Da [2]_         Da [2]_
Odstranjevanje konstruktorja                        Da [2]_         Ne
Zmanjšanje vidnosti javnega konstruktorja           Ne              Ne
Zmanjšanje vidnosti zaščitenega konstruktorja       Da [2]_         Ne
Premik k starševskemu razredu                       Da              Da
**Javne metode**
Dodajanje javne metode                              Da              Da
Odstranjevanje javne metode                         Ne              Ne
Sprememba imena                                     Ne              Ne
Zmanjšanje vidnosti                                 Ne              Ne
Premik k starševskemu razredu                       Da              Da
Dodajanje argumenta brez privzete vrednosti         Ne              Ne
Dodajanje argumenta s privzeto vrednostjo           Da [2]_         Ne
Odstranjevanje argumenta                            Da [4]_         Da [4]_
Dodajanje privzete vrednosti argumentu              Da [2]_         Ne
odstranjevanje privzete vrednosti argumenta         Ne              Ne
Dodajanje namiga tipa argumentu                     Da [8]_         Ne
Odstranjevanje namiga tipa argumentu                Da [2]_         Ne
Sprememba tipa argumenta                            Da [2]_ [5]_    Ne
Sprememba vrnjenega tipa                            Da [2]_ [6]_    Ne
**Zaščitene metode**
Dodajanje zaščitene metode                          Da              Da
Odstranejvanje zaščitene metode                     Da [2]_         Ne
Sprememba imena                                     Ne              Ne
Zmanjšanje vidnosti                                 Da [2]_         Ne
Premik k starševskemu razredu                       Da              Da
Dodajanje argumenta brez privzete vrednosti         Da [2]_         Ne
Dodajanje argumenta s privzeto vrednostjo           Da [2]_         Ne
Odstranjevanje argumenta                            Da [4]_         Da [4]_
Dodajanje privzete vrednosti argumentu              Da [2]_         Ne
Odstranjevanje privzete vrednosti argumenta         Da [2]_         Ne
Dodajanje namiga tipa argumentu                     Da [2]_         Ne
Odstranjevanje namiga tipa argumentu                Da [2]_         Ne
Sprememba tipa argumenta                            Da [2]_ [5]_    Ne
Sprememba vrnjenega tipa                            Da [2]_ [6]_    Ne
**Privatne metode**
Dodajanje privatne metode                           Da              Da
Odstranjevanje privatne metode                      Da              Da
Sprememba imena                                     Da              Da
Zmanjšanje vidnosti                                 Da              Da
Dodajanje argumenta brez privzete vrednosti         Da              Da
Dodajanje argumenta s privzeto vrednostjo           Da              Da
Odstranjevanje argumenta                            Da              Da
Dodajanje privzete vrednosti argumentu              Da              Da
Odstranjevanje privzete vrednosti argumentu         Da              Da
Dodajanje namiga tipa argumentu                     Da              Da
Odstranjevanje namiga tipa argumentu                Da              Da
Sprememba tipa argumenta                            Da              Da
Sprememba vrnjenega tipa                            Da              Da
==================================================  ==============  ==============

.. [1] Vaša koda je lahko zlomljena zaradi sprememb v kodi Symfony. Take spremembe bodo
       vseeno dokumentirane v datoteki UPGRADE.

.. [2] Bi se morali izogibati. Ko je urejeno, ta sprememba mora biti dokumentirana v
       datoteki UPGRADE.

.. [3] Dodan starševski vmesnik ne sme predstaviti nobenih novih metod, ki že ne
       obstjajo v vmesniku.

.. [4] Samo zadnji argument(i) metode so lahko odstranjeni, saj PHP ne
       zanima o dodatnih argumentih, ki jih podate metodi.

.. [5] Tip argumenta je lahko samo spremenjen v kompatibilen ali manj specifičen
       tip. Sledeči tipi sprememb so dovoljeni:

       ===================  ==================================================================
       Prvotni tip          Nov tip
       ===================  ==================================================================
       logična vrednost     katerikoli `skalarni tip`_ z ekvivalentnimi `logičnimi vrednostmi`_
       niz                  katerikoli `skalarni tip`_ ali objekt z ekvivalentnimi `vrednostmi niza`_
       celo število         katerikoli `skalarni tip`_ z ekvivalentnimi `vrednostmi celega števila`_
       št. s pl. vejico     katerikoli `skalarni tip`_ z ekvivalentnimi `vrednostmi števil s plavajočo vejico`_
       razred ``<C>``       katerikoli super razred ali vmesnik od ``<C>``
       vmesnik ``<I>``      katerikoli super vmesnik od ``<I>``
       ===================  ==================================================================

.. [6] Vrnjeni tip je lahko samo spremenjen na kompatibilno ali bolj specifičen
       tip. Sledeče spremembe tipov so dovoljene:

       ===================  ==================================================================
       Prvotni tip          Novi tip
       ===================  ==================================================================
       logična vrednost     katerikoli `skalarni tip`_ z ekvivalentnimi `logičnimi vrednostmi`_
       niz                  katerikoli `skalarni tip`_ ali objekt z ekvivalentnimi `vrednostmi niza`_
       celo število         katerikoli `skalarni tip`_ z ekvivalentnimi `vrednostmi celega števila`_
       št. s pl. vejico     katerikoli `skalarni tip`_ z ekvivalentnimi `vrednostmi števil s plavajočo vejico`_
       polje                instance of ``ArrayAccess``, ``Traversable`` and ``Countable``
       ``ArrayAccess``      polje
       ``Traversable``      polje
       ``Countable``        polje
       razred ``<C>``       katerikoli podrazred od ``<C>``
       vmesnik ``<I>``      katerikoli podvmesnik ali implementacija razreda ``<I>``
       ===================  ==================================================================

.. [7] Ko spreminjate starševski razred, mora prvotni starševski razred ostati
       prednik razreda.

.. [8] Namig tipa je lahko dodan samo, če podajanje vrednosti z različnim tipom
       pred tem generira usodno napako.

.. _semantične verzije: http://semver.org/
.. _skalarni tip: http://php.net/manual/en/function.is-scalar.php
.. _logičnimi vrednostmi: http://php.net/manual/en/function.boolval.php
.. _vrednostmi niza: http://www.php.net/manual/en/function.strval.php
.. _vrednostmi celega števila: http://www.php.net/manual/en/function.intval.php
.. _vrednostmi števil s plavajočo vejico: http://www.php.net/manual/en/function.floatval.php
