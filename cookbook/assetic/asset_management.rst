.. index::
   single: Assetic; Introduction

Kako uporabiti Assetic za upravljanje s sredstvi
================================================

Assetic združuje dve glavni ideji: :ref:`sredstva <cookbook-assetic-assets>` in
:ref:`filtre <cookbook-assetic-filters>`. Sredstva so datoteke kot so CSS,
JavaScript in slike. Filtri so stvari, ki jih je mogoče uporabiti na
teh datotekah preden so poslana brskalniku. To omogoča ločitev
med datotekami sredstev shranjenimi v aplikaciji in datotekami dejansko predstavljenimi
uporabniku.

Brez Assetic-a samo pošiljate datoteke shranjene v aplikaciji
direktno:

.. configuration-block::

    .. code-block:: html+jinja

        <script src="{{ asset('js/script.js') }}" type="text/javascript"></script>

    .. code-block:: php

        <script src="<?php echo $view['assets']->getUrl('js/script.js') ?>" type="text/javascript"></script>

Vendar *z* Assetic-om lahko upravljate ta sredstva, kakor želite (ali
jih naložite iz kjerkoli) preden jih pošljete. To pomeni, da lahko:

* Minimirate ali združite vse vaše CSS in JS datoteke

* Poženete vse (ali samo nekatere) vaših CSS ali JS datotek skozi neke vrste prevajalnik,
  kot je LESS, SASS ali CoffeeScript

* Poženete optimizacije slik na vaših slikah

.. _cookbook-assetic-assets:

Sredstva
--------

Uporaba Assetic-a ponuja mnoge prednosti pred direktnim pošiljanjem datotek.
Datoteke niso nujno shranjene, iz kjer so poslane in so lahko
potegnjene iz različnih virov kot na primer iz paketa.

Lahko uporabite Assetic za procesiranje tako :ref:`CSS stilov <cookbook-assetic-including-css>`
in :ref:`JavaScript datotek <cookbook-assetic-including-javascript>`. Filozofija
za dodajanje katerihkoli je v osnovi enaka, vendar z malenkost drugačno sintakso.

.. _cookbook-assetic-including-javascript:

Vključevanje JavaScript datotek
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Da vključite JavaScript datoteke, uporabite ``javascript`` značko v katerikoli predlogi.
To se bo najpogosteje nahajalo v ``javascripts`` bloku, če uporabljate
privzeta imena blokov iz Symfony standardne distribucije:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/*' %}
            <script type="text/javascript" src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/*')
        ) as $url): ?>
            <script type="text/javascript" src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

.. tip::

    Lahko tudi vključite CSS stile: glejte :ref:`cookbook-assetic-including-css`.

V tem primeru, bodo vse datoteke v ``Resources/public/js/`` direktoriju
paketa ``AcmeFooBundle`` naložene in poslane iz različne lokacije.
Dejanska izpisana značka lahko enostavno zgleda kot:

.. code-block:: html

    <script src="/app_dev.php/js/abcd123.js"></script>

To je ključna točka: enkrat ko dovolite Assetic-u upravljati z vašimi sredstvi, so datoteke
poslane iz različne lokacije To *bo* povzročilo probleme s CSS datotekami,
ki se sklicujejo na slike iz njihove relativne poti. Glejte :ref:`cookbook-assetic-cssrewrite`.

.. _cookbook-assetic-including-css:

Vključevanje CSS stilov
~~~~~~~~~~~~~~~~~~~~~~~

Da vključite CSS stile, lahko uporabite enako metadologijo prikazano
zgoraj, razen z značko ``stylesheets``. Če uporabljate privzeta
imena blokov iz Symfony standardne distribucije, se bo to običajno nahajalo
v bloku ``stylesheets``.

.. configuration-block::

    .. code-block:: html+jinja

        {% stylesheets 'bundles/acme_foo/css/*' filter='cssrewrite' %}
            <link rel="stylesheet" href="{{ asset_url }}" />
        {% endstylesheets %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->stylesheets(
            array('bundles/acme_foo/css/*'),
            array('cssrewrite')
        ) as $url): ?>
            <link rel="stylesheet" href="<?php echo $view->escape($url) ?>" />
        <?php endforeach; ?>

Vendar ker Assetic spremeni poti do vaših sredstev, *bo* to pokvarilo kakršnekoli
slike ozadij (ali druge poti), ki uporabljajo relativne poti, razen, če uporabite
filter :ref:`cssrewrite <cookbook-assetic-cssrewrite>`.

.. note::

    Bodite pozorni, da se v originalnem primeru, ki vključuje JavaScript datoteke,
    sklicujete na datoteeke z uporabo poti, kot je ``@AcmeFooBundle/Resources/public/file.js``,
    vendar v tem primeru se sklicujete na CSS datoteke z uporabo njihove dejanske
    javno dostopne poti: ``bundles/acme_foo/css``. Lahko uporabite katerikoli način, s tem
    da obstaja znana težava, ki povzroča da filter ``cssrewrite`` ne deluje,
    ko se uporablja ``@AcmeFooBundle`` sintakso za CSS stile.

.. _cookbook-assetic-cssrewrite:

Popravljanje CSS poti s filtrom ``cssrewrite``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ker Assetic generira nove URL-je za vaša sredstva, se bodo kakršnekoli poti znotraj
vaših CSS datotek pokvarile. Da to popravite, preverite, da uporabljate filter
``cssrewrite`` z vašo značko ``stylesheets``. To izpiše vaše CSS datoteke in popravi
poti interno, da odražajo nove lokacije.

Lahko preverite primer v prejšnji sekciji.

.. caution::

    Ko uporavljate filter ``cssrewrite``, se ne sklicujte na vaše CSS datoteke z uporabo
    ``@AcmeFooBundle`` sintakse. Za podrobnosti glejte opozorilo v zgornji sekciji.

Združevanje sredstev
~~~~~~~~~~~~~~~~~~~~

Ena lastnost Assetic-a je, da združi mnogo datotek v eno. To pomaga
zmanjšati število HTTP zahtevkov, kar je odlično za uspešnost ospredja aplikacije.
Tudi omogoča vam, da vzdržujete datoteke bolj enostavno s cepitvijo njih v
obvladljive dele. To lahko pomaga s ponovno uporabnostjo, saj lahko enostavno
razcepite datoteke specifične za projekt iz tistih, ki so lahko uporabljene v drugih aplikacijah,
vendar jih še vedno pošljete kot eno datoteko:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts
            '@AcmeFooBundle/Resources/public/js/*'
            '@AcmeBarBundle/Resources/public/js/form.js'
            '@AcmeBarBundle/Resources/public/js/calendar.js' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array(
                '@AcmeFooBundle/Resources/public/js/*',
                '@AcmeBarBundle/Resources/public/js/form.js',
                '@AcmeBarBundle/Resources/public/js/calendar.js',
            )
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

V ``dev`` okolju, vsaka datoteka je še vedno poslana individualno, da
lahko razhroščujete probleme bolj enostavno. Čeprav v ``prod`` okolju
(ali bolj specifično, ko je zastavica ``debug`` nastavljena na ``false``), bo to
izpisano kot ena značka ``script``, kar vključuje vsebino vseh
JavaScript datotek.

.. tip::

    Če ste novi v Assetic-u in poskušate uporabiti vašo aplikacijo v ``prod``
    okolju (z uporabo ``app.php`` krmilnika), boste po vsej verjetnosti videli
    vse tiste vaše CSS in JS napake. Ne skrbite! To je namenoma.
    Za podrobnosti, kako uporabljati Assetic v ``prod`` okolju, glejte :ref:`cookbook-assetic-dumping`.

In združevanje datotek ni samo uporabno za *vaše* datoteke. Assetic lahko uporabite tudi za
združevanje tretje osebnih sredstev, kot je jQuery z vašimi lastnimi v eno datoteko:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts
            '@AcmeFooBundle/Resources/public/js/thirdparty/jquery.js'
            '@AcmeFooBundle/Resources/public/js/*' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array(
                '@AcmeFooBundle/Resources/public/js/thirdparty/jquery.js',
                '@AcmeFooBundle/Resources/public/js/*',
            )
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

.. _cookbook-assetic-filters:

Filtri
------

Ko so enkrat upravljana z Assetic-om, lahko uporabite filtre na vaših sredstvih, preden
jih pošljete. To vključuje filtre, ki stisnejo izpis vaših sredstev
za manjše velikosti datotek (in boljšo optimizacijo ospredja). Ostali filtri
lahko prevedejo JavaScript datoteko iz CoffeeScript datotek in procesirajo SASS v CSS.
V bistvu ima Assetic dolg seznam filtrov, ki so na voljo.

Mnogi filtri ne delujejo direktno, vendar uporabljajo tretje osebne
knjižnice, da opravijo težko delo. To pomeni, da boste pogosto potrebovali namestiti
tretje osebno knjižnico za uporabo filtra. Ta odlična prednost uporabe Assetic-a,
da se sklicuje na te knjižnice (z razliko od direktne uporabe) je, da namesto,
da jih poganjate ročno, ko delate na datotekah, bo Assetic za to poskrbel
namesto vas in v celoti odstranil ta korak iz vašega razvojnega in postavitvenega
procesa.

Za uporabo filtra ga morate najprej določiti v Assetic nastavitvah.
Dodajanje filtra tu ne pomeni, da je v uporabi, samo pomeni, da je
na voljo za uporabo (filter boste uporabili spodaj).

Na primer za uporabo JavaScript YUI Compressor-ja je potrebno dodati
sledeče nastavitve:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                yui_js:
                    jar: "%kernel.root_dir%/Resources/java/yuicompressor.jar"

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="yui_js"
                jar="%kernel.root_dir%/Resources/java/yuicompressor.jar" />
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'yui_js' => array(
                    'jar' => '%kernel.root_dir%/Resources/java/yuicompressor.jar',
                ),
            ),
        ));

Sedaj za dejansko *uporabo* filtra na skupini JavaScript datotek, ga dodajte
v vašo predlogo:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/*' filter='yui_js' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/*'),
            array('yui_js')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

Bolj podroben vodič o nastavitvah in uporabi filtrov Assetic-a kot tudi
podrobnosti o Assetic-ovem razhroščevalnem načinu, je moč najti v
:doc:`/cookbook/assetic/yuicompressor`.

Krmiljenje uporabljenega URL-ja
-------------------------------

Če želite, lahko krmilite URL-je, ki jih Assetic proizvede. To je
narejeno v predlogi in je relativno glede na javni vrhnji dokumentni direktorij:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/*' output='js/compiled/main.js' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/*'),
            array(),
            array('output' => 'js/compiled/main.js')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

.. note::

    Symfony tudi vsebuje metodo za *praznjenje* predpomnilnika, kjer končni URL
    generiran s strani Assetic-a vsebuje parameter poizvedbe, ki je lahko povečan
    preko nastavitev pri vsaki postavitvi. Za več informacij glejte
    :ref:`ref-framework-assets-version` nastavitveno opcijo.

.. _cookbook-assetic-dumping:

Odlaganje datotek sredstev
--------------------------

V ``dev`` okolju, Assetic generira poti do CSS in JavaScript
datotek, ki fizično ne obstajajo na vašem računalniku. Vendar so kljub temu izpisane,
ker interni Symfony krmilnik odpre datoteke in ponudi nazaj
vsebino (po pogoniu katerihkoli filtrov).

Ta način dinamičnega ponujanja procesiranih sredstev je odličen, ker to pomeni,
da lahko takoj vidite novo stanje katerekoli datoteke sredstva, ki jo spremenite.
Je tudi slabo, ker je lahko precej počasno. Če uporabljate veliko filtrov,
je lahko zelo frustrirajoče.

Na srečo Assetic ponuja način odlaganja vaših sredstev v realne datoteke namesto,
da so generirane dinamično.

Odlaganje datotek sredstev v ``prod`` okolju
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

V ``prod`` okolju so vaše JS in CSS datoteke predstavljene vsaka kot ena
značka. V drugih besedah namesto, da vidite vsako JavaScript datoteko, ki jo vključujete
v vaši izvorni kodi, boste verjetneje videli samo nekaj takega:

.. code-block:: html

    <script src="/app_dev.php/js/abcd123.js"></script>

Poleg tega ta datoteka **ne** obstaja dejansko, niti ni dinamično izpisana
od Symfony-ja (kakor so datoteke sredstev v ``dev`` okolju). To je
namenoma - omogoča Symfony-ju generiranje teh datotek dinamično v produkcijskem
okolju je samo preveč počasno.

.. _cookbook-asetic-dump-prod:

Namesto da vsakič uporabite vašo aplikacijo v ``prod`` okolju (in zato
vsakič, ko postavljate), bi morali pognati sledeče opravilo:

.. code-block:: bash

    $ php app/console assetic:dump --env=prod --no-debug

To bo fizično generiralo in zapisalo vsako datoteko, ki jo potrebujete (npr. ``/js/abcd123.js``).
Če posodobite katerokoli od vaših sredstev, boste potrebovali pognati to ponovno za
ponovno generariranje datoteke.

Odlaganje datotek sredstev v ``dev`` okolju
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Privzeto vsaka pot sredstva generirana v ``dev`` okolju je upravljana
dinamično v Symfony-ju. To nima slabosti (lahko vidite vaše spremembe
takoj), razen da se sredstva nalagajo očitno počasneje. Če menite,
da se vaša sredstva nalagajo preveč počasno, sledite temu vodiču.

Najprej povejte Symfony-ju, da prenega poskušati procesirati te datoteke dinamično. Naredite
sledeče spremembe v vaši ``config_dev.yml`` datoteki:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config_dev.yml
        assetic:
            use_controller: false

    .. code-block:: xml

        <!-- app/config/config_dev.xml -->
        <assetic:config use-controller="false" />

    .. code-block:: php

        // app/config/config_dev.php
        $container->loadFromExtension('assetic', array(
            'use_controller' => false,
        ));

Nadaljnje, ker Symfony ne generira več teh sredstev za vas, jih boste
morali odložiti ročno. Da to naredite, poženite sledeče:

.. code-block:: bash

    $ php app/console assetic:dump

To fizično zapiše vse datoteke sredstev, ki jih potrebujete za vaše ``dev``
okolje. Glavna slabost je, da morate poganjati to vsakič,
ko posodobite sredstvo. Na srečo, s podajanjem opcije ``--watch``, bo
ukaz avtomatsko ponovno generiral sredstva, *ko se spremenijo*:

.. code-block:: bash

    $ php app/console assetic:dump --watch

Ker poganjanje tega ukaza v ``dev`` okolju lahko generira precej
datotek, je običajno dobra ideja, da pokažete vaše generirane datoteke sredstev
v nek izoliran direktorij (npr. ``/js/compiled``), da so stvari organizirane:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/*' output='js/compiled/main.js' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/*'),
            array(),
            array('output' => 'js/compiled/main.js')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>
