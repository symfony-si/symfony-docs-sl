.. index::
   single: Installation

Namestitev in nastavitev Symfony
================================

Cilj tega poglavja je postavitev delujoče aplikacije
zgrajene na Symfony. Na srečo Symfony ponuja "distribucije", ki
so funkcionalni Symfony "začetni" projekti, ki jih lahko prenesete in pričnete
takoj razvijati.

.. tip::

    Če iščete navodila, kako najboljše ustvariti nov projekt
    in ga shraniti preko kontrole izvorne kode, glejte `Uporaba kontrole izvorne kode`_.

Namestitev Symfony2 distribucije
--------------------------------

.. tip::

    Najprej preverite, da imate nameščen in nastavljen spletni strežnik (kot
    je Apache) s PHP 5.3.8 ali več. Za več informacij o Symfony2
    zahtevah, glejte :doc:`referenca zahtev </reference/requirements>`.

Symfony2 ima zapakirane "distribucije", ki so polno funkcionalne aplikacije,
ki vključujejo Symfony2 knjižnice jedra, izbiro uporabnih paketov,
smiselno datotečno strukturo in nekaj privzetih nastavitev. Ko prenašate
Symfoyn2 distribucijo, prenašate funkcionalno skeletno aplikacijo,
ki se jo lahko nemudoma uporabi za začetek razvijanja vaše aplikacije.

Začnite z obiskom Symfony2 prenosne strani na `http://symfony.com/download`_.
Na tej strani boste videli *Symfony standardno izdajo*, ki je glavna
Symfony2 distribucija. Na voljo sta 2 načina, da začnete z vašim projektom:

Opcija 1) Composer
~~~~~~~~~~~~~~~~~~

`Composer`_ je knjižnica upravljalnika odvisnosti za PHP, s katerim lahko
prenesete Symfony2 standardno izdajo.

Pričnite s `prenosom Composer-ja`_ kjerkoli na vašem lokalnem računalniku. Če
imate nameščen curl, je enostavno kot:

.. code-block:: bash

    curl -s https://getcomposer.org/installer | php

.. note::

    Če vaš računalnik ni pripravljen za uporabo Composer-ja, boste videli nekaj priporočil,
    ko poženete ta ukaz. Sledite tem priporočilom, da naredite Composer
    ustrezno delujoč.

Composer je izvršilna PHAR datoteka, ki jo lahko uporabite za prenos standardne
distribucije:

.. code-block:: bash

    $ php composer.phar create-project symfony/framework-standard-edition /path/to/webroot/Symfony 2.3.0

.. tip::

    Za točno verzijo, zamenjajte "2.3.0" z zadnjo Symfony verzijo.
    Za podrobnosti, glejte `Symfony namestitveno stran`_

.. tip::

    Za prenos vendor datotek hitreje, dodajte opcijo ``--prefer-dist`` na
    konec kateregakoli Composer ukaza.

Ta ukaz lahko traja nekaj minut, da se požene, saj Composer prenaša standardno
distribucijo skupaj z vsemi vendor knjižnicami, ki jih potrebuje. Ko konča,
bi morali imeti direktorij, ki izgleda nekako takole:

.. code-block:: text

    path/to/webroot/ <- your web server directory (sometimes named htdocs or public)
        Symfony/ <- the new directory
            app/
                cache/
                config/
                logs/
            src/
                ...
            vendor/
                ...
            web/
                app.php
                ...

Opcija 2) Prenos arhiva
~~~~~~~~~~~~~~~~~~~~~~~

Lahko tudi prenesete arhiv standardne izdaje. Tu boste
potrebovali narediti dve izbiri:

* Prenesite ali ``.tgz`` ali ``.zip`` arhiv - oba sta ekvivalentna, prenesite
  kateregakoli, s katerim ste bolj domači pri uporabi;

* Prenesite distribucijo z ali brez izdelovalcev (vendors). Če načrtujete
  uporabljati več tretje osebnih knjižnic ali paketov in jih upravljati preko Composer-ja,
  bi morali verjetno prenesti brez izdelovalcev - "without vendors".

Prenesite enega izmed arhivov nekam pod vaš vrhnji direktorij lokalnega spletnega
strežnika in ga razpakirajte. Iz UNIX ukazne vrstice je to mogoče narediti z
enim izmed sledečih ukazov (zamenjajte ``###`` z vašim dejanskim imenom datoteke):

.. code-block:: bash

    # for .tgz file
    $ tar zxvf Symfony_Standard_Vendors_2.3.###.tgz

    # for a .zip file
    $ unzip Symfony_Standard_Vendors_2.3.###.zip

Če ste prenesli "without vendors", boste zagotovo potrebovali prebrati
naslednjo sekcijo.

.. note::

    Lahko enostavno prepišete privzeto strukturo direktorijev. Glejte
    :doc:`/cookbook/configuration/override_dir_structure` za več
    informacij.

Vse javne datoteke in prednji krmilnik, ki upravljajo prihajajoče zahtevke v
Symfony2 aplikaciji obstojajo v ``Symfony/web`` direktoriju. Torej ob predpostavki,
date ste razpakirali arhiv v vaš vrhnji dokumentni direktorij spletnega strežnika ali virtualnega gostitelja,
se bodo URL-ji vaše aplikacije začeli z ``http://localhost/Symfony/web``.

.. note::

    Sledeči primeri predpostavljajo, da se ne dotikate nastavitev vrhnjega direktorija,
    da se vsi URL-ji začnejo z ``http://localhost/Symfony/web/``

.. _installation-updating-vendors:

Posodobitev izdelovalcev
~~~~~~~~~~~~~~~~~~~~~~~~

Na tej točki ste prenesli celotno funkcionalni Symfony projekt v katerem
boste pričeli razvijati vašo lastno aplikacijo. Symfony projekt je odvisen od
številnih zunanjih knjižnic. Te so prenesene v `vendor/` direktorij
vašega projekta preko knjižnice imenovane `Composer`_.

Odvisno od tega, kako ste prenesli Symfony, boste morali ali po ne posodobiti
vaše izdelovalce takoj. Vendar posodabljanje vaših izdelovalcev je vedno varno in garantira,
da imate vse vendor knjižnice, ki jih potrebujete.

Korak 1: Dobite `Composer`_ (Odlični novi PHP pakirni sistem)

.. code-block:: bash

    curl -s http://getcomposer.org/installer | php

Zagotovite, da ste prenesli ``composer.phar`` v isti direktorij, kjer
je locirana ``composer.json`` datoteka (to je privzeto vrh vašega Symfony
projekta).

Korak 2: Namestitev izdelovalcev

.. code-block:: bash

    $ php composer.phar install

Ta ukaz prenese vse potrebne vendor knjižnice - vključno
sam Symfony - v direktorij ``vendor/``.

.. note::

    Če nimate nameščenega ``curl``, lahko tudi samo prenesete ``installer``
    datoteko ročno iz http://getcomposer.org/installer. Dajte to datoteko v vaš
    projekt in nato poženite:

    .. code-block:: bash

        php installer
        php composer.phar install

.. tip::

    Ko poganjate ``php composer.phar install`` ali ``php composer.phar update``,
    bo composer izvedel post install/update ukaza za spraznenje predpomnilnika
    in namestitev sredstev. Privzeto bodo sredstva kopirana v vaš ``web``
    direktorij.

    Namesto kopiranja Symfony sredstev, lahko izdelate simbolične povezave, če
    vaš operacijski sistem to podpira. To naredi simbolične povezave in doda vnos
    v ``extra`` vozlišče vaše composer.json datoteke s ključem
    ``symfony-assetics-install`` in vrednostjo ``symlink``:

    .. code-block:: json

        "extra": {
            "symfony-app-dir": "app",
            "symfony-web-dir": "web",
            "symfony-assets-install": "symlink"
        }

    Ko podajate ``relative`` namesto ``symlink`` k symfony-assets-install,
    bo ukaz generiral relativne simbolične povezave.

Konfiguratija in namestitev
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Na tej točki sedaj vse potrebne tretje osebne knjižnice domujejo v ``vendor/``
direktoriju. Imate tudi privzeto namestitev aplikacije v ``app/`` in nekaj
vzorčne kode v ``src/`` direktoriju.

Symfony2 prihaja z vizualnim strežnikom konfiguracijskega testerja, da pomaga zagotoviti,
da sta vaš spletni strežnik in PHP nastavljena za uporabo Symfony. Uporabite sledeči URL,
da preverite vaše nastavitve:

.. code-block:: text

    http://localhost/config.php

Če so težave, jih popravite sedaj preden greste naprej.

.. sidebar:: Nastavitev dovoljenj

    Ena pogostejših napak je, da ``app/cache`` in ``app/logs`` direktorija
    morata biti zapisljiva tako za uporabnika spletnega strežnika kot tudi za uporabnika ukazne vrstice. Na
    UNIX sistemih, če je vaš uporabnik spletnega strežnika drugačen od vašega uporabnika
    ukazne vrstice, lahko poženete sledeče ukaze samo enkrat v vašem projektu,
    da zagotovite, da bodo dovoljenja ustrezno nastavljena.

    **1. Uporaba ACL na sistemu, ki podpira chmod +a**

    Mnogo sistemov vam omogoča uporabo ``chmod +a`` ukaza. Najprej poskusite to
    in če dobite napako - poskusite naslednjo metodo. To uporablja ukaz za
    poskus ugotovitve vašega uporabnika spletnega strežnika in ga nastavi kot ``APACHEUSER``:

    .. code-block:: bash

        $ rm -rf app/cache/*
        $ rm -rf app/logs/*

        $ APACHEUSER=`ps aux | grep -E '[a]pache|[h]ttpd' | grep -v root | head -1 | cut -d\  -f1`
        $ sudo chmod +a "$APACHEUSER allow delete,write,append,file_inherit,directory_inherit" app/cache app/logs
        $ sudo chmod +a "`whoami` allow delete,write,append,file_inherit,directory_inherit" app/cache app/logs


    **2. Uporaba ACL na sistemu, ki ne podpira chmod +a**

    Nekateri sistemi ne podpirajo ``chmod +a``, vendar podpirajo drugo orodje
    imenovano ``setfacl``. Lahko boste morali `omogočiti ACL podporo`_ na vaši particiji
    in namestiti setfacl preden ga uporabljate (kot je primer na Ubuntu). To
    uporablja ukaz za poskus ugotovitve vašega uporabnika spletnega strežnika in ga nastavi kot
    ``APACHEUSER``.

    .. code-block:: bash

		$ APACHEUSER=`ps aux | grep -E '[a]pache|[h]ttpd' | grep -v root | head -1 | cut -d\  -f1`
		$ sudo setfacl -R -m u:$APACHEUSER:rwX -m u:`whoami`:rwX app/cache app/logs
		$ sudo setfacl -dR -m u:$APACHEUSER:rwX -m u:`whoami`:rwX app/cache app/logs
		
    **3. Brez uporabe ACL**

    Če nimate dostopa do spreminjanja ACL direktorijev, boste
    morali spremeniti umask, da bosta cache in log direktorija
    skupinsko-zapisljiva ali world-zapisljiva (odvisno če sta uporabnik spletnega strežnika
    in uporabnik ukazne vrstice v isti skupini ali ne). Da to dosežete,
    dodajte sledečo vrstico na začetek ``app/console``,
    ``web/app.php`` in ``web/app_dev.php`` datotek::

        umask(0002); // This will let the permissions be 0775

        // or

        umask(0000); // This will let the permissions be 0777

    Bodite pozorni, da uporaba ACL je priporočljiva, ko imate dostop do njih
    na vašem strežniku, ker sprememba umask ni varna za niti.

Ko je vse v redu, kliknite na "Go to the Welcome page", da zahtevate vašo
prvo "pravo" Symfony2 spletno stran:

.. code-block:: text

    http://localhost/app_dev.php/

Symfony2 bi vas moral pozdraviti in čestitati za težko delo do sedaj!

.. image:: /images/quick_tour/welcome.png

.. tip::

    Da dobite lepe in kratke url-je, bi morali pokazati vaš vrhnji direktorij vašega
    spletnega strežnika ali virtualnega gostitelja v ``Symfony/web`` direktorij. Vendar
    to ni zahtevano za razvoj, priporočljivo je takrat, ko gre vaša
    aplikacija v produkcijo saj vse sistemske in nastavitvene datoteke
    postanejo nedostopne klientom. Za informacije o nastavitvah
    vašega specifičnega vrhnjega direktorija spletnega strežnika preberite
    :doc:`/cookbook/configuration/web_server_configuration`
    ali se posvetujte pri uradni dokumentaciji vašega spletnega strežnika:
    `Apache`_ | `Nginx`_ .

Pričetek razvoja
----------------

Sedaj, ko imate polno funkcionalno Symfony2 aplikacijo, lahko pričnete
razvijati! Vaša distribucija lahko vsebuje nekaj vzorčne kode - preverite
``README.md`` datoteko vključeno v distribuciji (odprite jo kot tekstovno datoteko),
da izvedete o tem, katera vzorčna koda je vključena v vašo distribucijo.

Če ste novi v Symfony, preverite ":doc:`page_creation`", kjer boste
izvedeli, kako ustvariti strani, spremeniti nastavitve in narediti vse ostalo, kar
potrebujete v vaši novi aplikaciji.

Bodite prepričani, da tudi preverite :doc:`Recepte </cookbook/index>`, ki vsebujejo
široko raznolikost člankov o reševanju specifičnih problemov v Symfony.

.. note::

    Če želite odstraniti vzorčno kodo iz vaše distribucije, poglejte
    ta članek: ":doc:`/cookbook/bundles/remove`"

Uporaba kontrole izvorne kode
-----------------------------

Če uporabljate sistem kontrole izvorne kode, kot sta ``Git`` ali ``Subversion``,
lahko nastavite vaš sistem kontrole izvorne kode in pričnete dodajati vaš projekt
vanj kot običajno. Symfony standardna izdaja *je* začetna točka za vaš
novi projekt.

Za specifična navodila kako najboljše nastaviti vaš projekt, da bo shranjen
v git-u, glejte: :doc:`/cookbook/workflow/new_project_git`.

Ignoriranje ``vendor/`` direktorija
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Če ste prenesli arhiv *without vendors*, lahko varno ignorirate
celotni ``vendor/`` direktorij in ga ne dodate v kontrolo izvorne kode. Z
``Git-om`` je to narejeno z ustvarjanjem in dodajanjem sledečega v ``.gitignore``
datoteko:

.. code-block:: text

    /vendor/

Sedaj vendor direktorij ne bo dodan kontroli izvorne kode. To je v redu
(v bistvu je odlično!), ker ko nekdo drug klonira ali preveri
projekt, lahko enostavno požene ``php composer.phar install`` skripto
za namestitev vseh potrebnih projektnih odvisnosti.

.. _`omogočiti ACL podporo`: https://help.ubuntu.com/community/FilePermissionsACLs
.. _`http://symfony.com/download`: http://symfony.com/download
.. _`Git`: http://git-scm.com/
.. _`GitHub Bootcamp`: http://help.github.com/set-up-git-redirect
.. _`Composer`: http://getcomposer.org/
.. _`prenosom Composer-ja`: http://getcomposer.org/download/
.. _`Apache`: http://httpd.apache.org/docs/current/mod/core.html#documentroot
.. _`Nginx`: http://wiki.nginx.org/Symfony
.. _`Symfony namestitveno stran`:    http://symfony.com/download
