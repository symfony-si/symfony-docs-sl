.. index::
   single: Assetic; Apply filters

Kako uporabiti Assetic Filter na določeni končnici datoteke
===========================================================

Filtri Assetic-a se lahko uporabijo na posameznih datotekah, skupinah datotek ali celo,
kot boste videli tu, datotekah, ki imajo specifično končnico. Za prikaz,
kako se upravlja z vsako opcijo, predpostavimo, da želite uporabiti Assetic-ov CoffeeScript
filter, ki prevede CoffeeScript datoteke v JavaScript.

Glavna nastavitev so samo poti do coffee, node in node_modules.
Primer nastavitve lahko izgleda takole:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                coffee:
                    bin:       /usr/bin/coffee
                    node:       /usr/bin/node
                    node_paths: [/usr/lib/node_modules/]

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="coffee"
                bin="/usr/bin/coffee/"
                node="/usr/bin/node/">
                <assetic:node-path>/usr/lib/node_modules/</assetic:node-path>
            </assetic:filter>
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'coffee' => array(
                    'bin'  => '/usr/bin/coffee',
                    'node' => '/usr/bin/node',
                    'node_paths' => array('/usr/lib/node_modules/'),
                ),
            ),
        ));

Filter nad posamezno datoteko
-----------------------------

Sedaj lahko pošljete eno CoffeeScript datoteko kot JavaScript iz vaših
predlog:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/example.coffee' filter='coffee' %}
            <script src="{{ asset_url }}" type="text/javascript"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/example.coffee'),
            array('coffee')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>" type="text/javascript"></script>
        <?php endforeach; ?>

To je vse, kar je potrebno za prevod te CoffeeScript datoteke in jo ponuditi kot
preveden JavaScript.

Filtriranje večih datotek
-------------------------

Lahko tudi združite več CoffeeScript datotek v eno izhodno datoteko:

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/example.coffee'
                       '@AcmeFooBundle/Resources/public/js/another.coffee'
            filter='coffee' %}
            <script src="{{ asset_url }}" type="text/javascript"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array(
                '@AcmeFooBundle/Resources/public/js/example.coffee',
                '@AcmeFooBundle/Resources/public/js/another.coffee',
            ),
            array('coffee')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>" type="text/javascript"></script>
        <?php endforeach; ?>

Obe datoteki bosta ponujeni kot ena prevedena datoteka v običajnem
JavaScript-u.

.. _cookbook-assetic-apply-to:

Filtriranje na osnovi končnice datoteke
---------------------------------------

Ena izmed odličnih prednosti uporabe Assetic-a je zmanjšanje števila datotek
sredstev na manjše HTTP zahtevke. Za polno uporabo tega bi bilo
dobro združiti *vse* vaše JavaScript in CoffeeScript datoteke skupaj,
saj bodo na koncu poslane kot JavaScript. Na žalost samo
dodajanje JavaScript datotek ne bo prestalo CoffeeScript prevajanja.

Temu problemu se lahko izognemo z uporabo ``apply_to`` opcije v nastavitvah,
kar vam omogoča, da določite, da filter bi moral biti vedno uporabljen na določenih
vrstah datotek. V tem primeru lahko določite, da je filter ``coffee`` uporabljen
na vseh ``.coffee`` datotekah:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                coffee:
                    bin:        /usr/bin/coffee
                    node:       /usr/bin/node
                    node_paths: [/usr/lib/node_modules/]
                    apply_to:   "\.coffee$"

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="coffee"
                bin="/usr/bin/coffee"
                node="/usr/bin/node"
                apply_to="\.coffee$" />
                <assetic:node-paths>/usr/lib/node_modules/</assetic:node-path>
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'coffee' => array(
                    'bin'      => '/usr/bin/coffee',
                    'node'     => '/usr/bin/node',
                    'node_paths' => array('/usr/lib/node_modules/'),
                    'apply_to' => '\.coffee$',
                ),
            ),
        ));

S tem ne potrebujete več določati ``coffee`` filtra v predlogi.
Lahko tudi dodate običajne JavaScript datoteke, vse tiste, ki bodo prevedene
in izpisano kot ena JavaScript datoteka (s tem, da bodo samo ``.coffee`` datoteke
pognane skozi CoffeeScript filter):

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/example.coffee'
                       '@AcmeFooBundle/Resources/public/js/another.coffee'
                       '@AcmeFooBundle/Resources/public/js/regular.js' %}
            <script src="{{ asset_url }}" type="text/javascript"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array(
                '@AcmeFooBundle/Resources/public/js/example.coffee',
                '@AcmeFooBundle/Resources/public/js/another.coffee',
                '@AcmeFooBundle/Resources/public/js/regular.js',
            )
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>" type="text/javascript"></script>
        <?php endforeach; ?>
