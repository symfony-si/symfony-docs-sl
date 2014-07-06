.. index::
   single: Assetic; UglifyJS

Kako zmanjšati CSS/JS datoteke (z uporabo UglifyJS in UglifyCSS)
================================================================

`UglifyJS`_ je JavaScript prevajalno/stiskalno/olepševalno orodje. Lahko je uporabljen
za združevanje in zmanjšanje JavaScript sredstev, da se porablja manj HTTP zahtevkov
in da se vaša stran naloži hitreje. `UglifyCSS`_ je CSS stiskalnik/olepševalnik,
ki je zelo podoben UglifyJS.

V tem receptu je namestitev, nastavitev in uporaba UglifyJS
prikazana podrobneje. ``UglifyCSS`` deluje na precej podoben način in je
predstavljen samo na kratko.

Namestitev UglifyJS
-------------------

UglifyJS je na voljo kot `Node.js`_ npm modul in se ga lahko namesti z uporabo
npm. Najprej morate `namestiti Node.js`_. Potem lahko namestite UglifyJS
z uporabo npm:

.. code-block:: bash

    $ npm install -g uglify-js

Ta ukaz bo namestil UglifyJS globalno in lahko da ga boste potrebovali pognati
kot vrhovni (root) uporabnik.

.. note::

    Možno je tudi namestiti UglifyJS samo znotraj vašega projekta. Da to naredite,
    ga namestite brez opcije ``-g`` in določite pot, kamor
    se doda modul:

    .. code-block:: bash

        $ cd /path/to/symfony
        $ mkdir app/Resources/node_modules
        $ npm install uglify-js --prefix app/Resources

    Priporočljivo je, da namestite UglifyJS v vaš ``app/Resources`` direktorij
    in dodate ``node_modules`` direktorij v kontrolo verzij. Alternativno
    lahko ustvarite npm `package.json`_ datoteko in določite vaše odvisnosti
    tam.

Odvisno od vaše namestitvene metode bi morali ali uspeti pognati
``uglifyjs`` pogonski ukaz globalno, ali pognati fizično datoteko, ki se nahaja
v ``node_modules`` direktoriju:

.. code-block:: bash

    $ uglifyjs --help

    $ ./app/Resources/node_modules/.bin/uglifyjs --help

Nastavitev filtra ``uglifyjs2``
-------------------------------

Sedaj potrebujemo nastaviti Symfony2, da bo uporabil ``uglifyjs2`` filter, ko procesira
vaše JavaScript-e:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                uglifyjs2:
                    # the path to the uglifyjs executable
                    bin: /usr/local/bin/uglifyjs

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <!-- bin: the path to the uglifyjs executable -->
            <assetic:filter
                name="uglifyjs2"
                bin="/usr/local/bin/uglifyjs" />
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'uglifyjs2' => array(
                    // the path to the uglifyjs executable
                    'bin' => '/usr/local/bin/uglifyjs',
                ),
            ),
        ));

.. note::

    Pot, kjer je UglifyJS nameščen, se lahko spreminja odvisno od vašega sistema.
    Da ugotovite, kje npm shranjuje ``bin`` direktorij, lahko uporabite sledeči
    ukaz:

    .. code-block:: bash

        $ npm bin -g

    Moral bi izpisati direktorij na vašem sistemu, znotraj katerega bi morali najti
    UglifyJS izvršljivo datoteko.

    Če ste namestili UglifyJS lokalno, lahko najdete ``bin`` direktorij znotraj
    ``node_modules`` direktorija. V tem primeru je poimenovan ``.bin``.

Sedaj imate dostop do ``uglifyjs2`` filtra v vaši aplikaciji.

Zmanjšajte vaša sredstva
------------------------

Da uporabite UglifyJS na vaših sredstvih, ga morate uporabiti na njih. Ker
so vaša sredstva del nivoja pogleda, je to opravljeno v vaših predlogah:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/*' filter='uglifyjs2' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/*'),
            array('uglifyj2s')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

.. note::

    Zgornji primer predpostavlja, da imate paket imenovan ``AcmeFooBundle``
    in vaše JavaScript datoteke so v ``Resources/public/js`` direktoriju pod
    vašim paketom. To sicer ni pomembno - lahko vključite vaše JavaScript
    datoteke ne glede na to, kje so.

Z dodajanjem filtra ``uglifyjs2`` značkam sredstev zgoraj, bi morali
sedaj videti zmanjšane JavaScript-e, ki se pošiljajo preko žice veliko hitreje.

Onemogočite zmanjšanje v razhroščevalnem načinu
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Zmanjšani JavaScript-i so zelo težki za branje, kot tudi razhroščevanje. Zato
vam Assetic omogoča onemogočiti določen filter, ko je vaša aplikacija v
razhroščevalnem (npr. ``app_dev``) načinu. To lahko storite z dodajanjem predpone
imenu filtra v vaši predlogi z vprašajem: ``?``. To pove Assetic-u, da
uporabi filter samo, ko je razhroščevalni način izključen (npr. ``app.php``):

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/*' filter='?uglifyjs2' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/*'),
            array('?uglifyjs2')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

Da to preskusite, preklopite v vaše ``prod`` okolje (``app.php``). Vendar preden
to naredite, ne pozabite :ref:`sprazniti vašega predpomnilnika <book-page-creation-prod-cache-clear>`
in :ref:`odložiti vaših assetic sredstev <cookbook-asetic-dump-prod>`.

.. tip::

    Namesto dodajanja filtra k znački sredstva, ga lahko tudi globalno
    omogočite z dodajanjem ``apply-to-attribute`` k nastavitvam filtra, na primer
    v ``uglifyjs2`` filtru ``apply_to: "\.js$"``. Da imate
    filter uporabljen samo v produkciji, dodajte to v ``config_prod`` datoteko
    namesto v skupno config datoteko. Za podrobnosti glede uporabe filtrov glede na
    končnico datoteke, glejte :ref:`cookbook-assetic-apply-to`.

Namestite, nastavite in uporabite UglifyCSS
-------------------------------------------

Uporaba UglifyCSS deluje na enak način kot UglifyJS. Najprej zagotovite,
da je node paket nameščen:

.. code-block:: bash

    $ npm install -g uglifycss

Nato dodajte nastavitve za ta filter:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                uglifycss:
                    bin: /usr/local/bin/uglifycss

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="uglifycss"
                bin="/usr/local/bin/uglifycss" />
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'uglifycss' => array(
                    'bin' => '/usr/local/bin/uglifycss',
                ),
            ),
        ));

Da uporabite filter za vaše CSS datoteke, dodajte filter v Assetic ``stylesheets``
pomočnik:

.. configuration-block::

    .. code-block:: html+jinja

        {% stylesheets 'bundles/AcmeFoo/css/*' filter='uglifycss' filter='cssrewrite' %}
             <link rel="stylesheet" href="{{ asset_url }}" />
        {% endstylesheets %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->stylesheets(
            array('bundles/AcmeFoo/css/*'),
            array('uglifycss'),
            array('cssrewrite')
        ) as $url): ?>
            <link rel="stylesheet" href="<?php echo $view->escape($url) ?>" />
        <?php endforeach; ?>

Tako kot z ``uglifyjs2`` filtrom, če dodate predpono imenu filtra z
``?`` (t.j. ``?uglifycss``), se bo zmanjšanje zgodilo, ko niste
v razhroščevalnem načinu.

.. _`UglifyJS`: https://github.com/mishoo/UglifyJS
.. _`UglifyCSS`: https://github.com/fmarcia/UglifyCSS
.. _`Node.js`: http://nodejs.org/
.. _`namestiti Node.js`: http://nodejs.org/
.. _`package.json`: http://package.json.nodejitsu.com/
