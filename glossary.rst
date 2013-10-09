:orphan:

Glossary
========

.. glossary::
   :sorted:

   Distribucija
        *Distribucija* je paket izdelan iz Symfony2 komponent,
        izbire paketov, smiselne strukture direktorijev, privzetih nastavitev
        in opcijskega nastavitvenega sistema.

   Dependency Injection
        Dependency Injection je načrtovalski vzorec, veliko uporabljen v Symfony2 ogrodju.
        Spodbuja ohlapno skupno in bolj trajnostno arhitektur aplikacije.
        Glavni princip tega vzorca je, da dovoljuje razvijalcem *vbrizganje* objektov
        (znanih tudi kot storitve) v druge objekte, v splošnem jih podaja kot parametre.
        Različni nivoji sklapljanja med temi objekti so lahko ustanovljeni
        v odvisnosti od uporabljene metode za vbrizgavanje objektov skupaj.
        Dependency Injection vzorec je bolj pogosto povezan k drugemu
        tipu objekta: :doc:`/book/service_container`.

   Projekt
        *Projekt* je direktorij sestavljen iz aplikacije, skupka paketov
        knjižnic izdelovalcev, automatskega nalagalnika in skripe prednjega
        spletnega krmilnika.

   Aplikacija
        *Aplikacija* je direktorij, ki vsebuje *nastavitve* za
        dani skupek paketov.

   Paket (Bundle)
        *Paket* je direktorij, ki vsebuje skupek datotek (PHP datotek,
        stilskih datotek, JavaScript, slike, ...), ki *implementirajo* eno
        lastnost (blog, forum itd.). V Symfony2, se (*skoraj*) vse
        nahaja znotraj paketa. (see :ref:`page-creating-bundles`)

   Prednji krmilnik
        *Prednji krmilnik* je hitra PHP skripa, ki se nahaja v web direktoriju
        vašega projekta. Običajno so *vse* zahtevki ravnani z izvajanjem
        istega prednjega krmilnika, katerega naloga je zagon Symfony
        aplikacije.

   Krmilnik
        *Krmilnik* je PHP funkcija, ki vsebuje vso potrebno logiko za vračanje
        ``Response`` objekta, ki predstavlja določeno stran. Običajno je pot
        povezana v krmilnik, ki potem uporablja informacije iz zahtevka za procesiranje
        informacij, izvaja akcije in ultimativno sestavi in vrne ``Response`` objekt.

   Service
        *Storitev* je generičen termin za katerokoli PHP objekt, ki izvaja določeno
        opravilo. Storitev je običajno uporabljena "globalno", kot objekt povezave
        podatkovne baze ali objekt, ki dostavlja e-poštna sporočila. V Symfony2 so
        storitve pogosto nastavljene in pridobljene iz storitvenega kontejnerja.
        Aplikacija, ki ima mnoge skupne storitve, pomeni, da sledi
        `service-oriented architecture`_.

   Service Container
        *Service Container*, znan tudi kot *Depencency Injection Container*
        je poseben objekt, ki upravlja instantizacijo storitev znotraj
        aplikacije. Namesto ustvarjanja storitev direktno, razvijalec
        *nauči* storitveni kontejner (preko nastavitev), kako izdelati
        storitve. Storitveni kontejner uredi leno instantizacijo in
        injeciranje odvisnih storitev. Več v :doc:`/book/service_container`
        poglavju.

   HTTP Specifikacija
        *Http Specifikacija*je dokument, ki opisuje Hypertext Transfer Protocol -
        skupek pravil, ki določajo klasično klient-strežnik zahtevek-odziv komunikacijo.
        Specifikacija definira obliko uporabljeno za zahtevek in odziv kot tudi možne
        HTTP glav, ki jih vsaka lahko vsebuje. Za več informacij, preberite
        `Http Wikipedia`_ članek ali `HTTP 1.1 RFC`_.

   Okolje
        Okolje je niz (npr. ``prod`` ali ``dev``), ki ustreza določenemu
        skupku nastavitev. Ista aplikacija se lahko poganja na isti napravi in
        uporablja različne nastavitve s poganjanjem aplikacije v različnih
        okoljih. To je uporabno saj omogoča, da ima ena aplikacija ``dev`` okolje
        zgrajeno za razhroščevanje in ``prod`` okolje, ki je optimizirano za hitrost.

   Izdelovalec (Vendor)
        *Izdelovalec* je ponudnik PHP knjižnic in paketov, kar vključuje tudi sam
        Symfony2. Razen običajnih komercialnih konotacij besede, izdelovalec v Symfony
        pogosto (celo običajno) vključuje brezplačno programsko opremo. Katerakoli
        knjižnica, ki jo dodate v vaš Symfony2 projekt bi morala iti v ``vendor``
        direktorij. Poglejte si še
        :ref:`The Architecture: Using Vendors <using-vendors>`.

   Acme
        *Acme* je vzorčno ime podjetja uporabljenega v Symfony demonstracijah in dokumentaciji.
        Je uporabljen kot imenski prostor, kjer bi običajno uporabili vaše ime podjetja
        (npr. ``Acme\BlogBundle``).

   Akcija
        *Akcija* je PHP funkcija ali metoda, ki se izvaja na primer, ko je podana pot ujeta.
        Termin akcija je sinonim za *krmilnik*, čeprav se lahko krmilnik tudi sklicuje na celoten
        PHP razred, ki vključuje nekaj akcij. Oglejte si več v :doc:`Controller Chapter </book/controller>`.

   Sredstvo (Asset)
        *Sredstvo* je katerakoli neizvedljiva, statična komponenta spletne aplikacije,
        kar vključuje CSS, JavaScript, slike in video. Sredstva so lahko postavljena
        direktno v projektni ``web`` direktorij ali objavljena iz :term:`Bundle`
        v web direktorij z uporabo ``assets:install`` opravila ukazne komande.

   Jedro (Kernel)
        *Jedro* je središče Symfony2. Kernel objekt upravlja HTTP
        zahtevke z uporabo vseh paketov in knjižnic registriranih v njem. Oglejte si
        :ref:`The Architecture: The Application Directory <the-app-dir>` in
        :doc:`/book/internals` poglavje.

   Požarni zid
        V Symfony2, *požarni zid* nima nič opraviti z omrežjem. Namesto tega,
        definira mehanizme preverjanja pristnosti (t.j. ravnanje s procesom
        določanja identifikacije vaših uporabnikov), ali za celo aplikacijo,
        ali samo za del nje. Oglejte si
        :doc:`/book/security` chapters.

   Yaml
        *YAML* je rekurzivna krativa za "YAML Ain't a Markup Language". Gre za
        lahko, človeku prijazen serializacijski jezik, uporabljen obširno v Symfony2
        nastavitvenih datotekah. Oglejte si :doc:`/components/yaml/introduction`
        poglavje.


.. _`service-oriented architecture`: http://wikipedia.org/wiki/Service-oriented_architecture
.. _`HTTP Wikipedia`: http://en.wikipedia.org/wiki/Hypertext_Transfer_Protocol
.. _`HTTP 1.1 RFC`: http://www.w3.org/Protocols/rfc2616/rfc2616.html
