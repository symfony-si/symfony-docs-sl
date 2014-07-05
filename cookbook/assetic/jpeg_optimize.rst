.. index::
   single: Assetic; Image optimization

Kako uporabiti Assetic za optimizacijo slik s Twig funkcijami
=============================================================

Med mnogimi filtri ima Assetic štiri, ki so lahko uporabljeni za takojšnjo
optimizacijo slike. To vam omogoča, da dobite prednosti manjših velikosti datotek
brez, da bi morali uporabiti urejevalnik slik za procesiranje vsake slike. Rezultati
so predpomnjeni in so lahko odloženi za produkcijo, tako da ni udara na zmogljivost
za vaše končne uporabnike.

Uporaba Jpegoptim-a
-------------------

`Jpegoptim`_ je orodje za optimizacijo JPEG datotek. Da ga uporabite z Assetic-om,
dodajte sledeče v Assetic nastavitve:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                jpegoptim:
                    bin: path/to/jpegoptim

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="jpegoptim"
                bin="path/to/jpegoptim" />
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'jpegoptim' => array(
                    'bin' => 'path/to/jpegoptim',
                ),
            ),
        ));

.. note::

    Bodite pozorni, da za uporabo jpegoptim-a, ga morate že imeti nameščenega na vašem
    sistemu. Opcija ``bin`` kaže na lokacijo prevedene binarne datoteke.

Sedaj je lahko uporabljen iz predloge:

.. configuration-block::

    .. code-block:: html+jinja

        {% image '@AcmeFooBundle/Resources/public/images/example.jpg'
            filter='jpegoptim' output='/images/example.jpg' %}
            <img src="{{ asset_url }}" alt="Example"/>
        {% endimage %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->image(
            array('@AcmeFooBundle/Resources/public/images/example.jpg'),
            array('jpegoptim')
        ) as $url): ?>
            <img src="<?php echo $view->escape($url) ?>" alt="Example"/>
        <?php endforeach; ?>

Odstranjevanje vseh EXIF podatkov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Privzeto poganjanje tega filtra samo odstrani nekatere meta informacije
shranjene v datoteki. Kakršnikoli EXIF podatki in komentarji niso odstranjeni, vendar jih
lahko odstranite z uporabo opcije ``strip_all``:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                jpegoptim:
                    bin: path/to/jpegoptim
                    strip_all: true

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="jpegoptim"
                bin="path/to/jpegoptim"
                strip_all="true" />
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'jpegoptim' => array(
                    'bin'       => 'path/to/jpegoptim',
                    'strip_all' => 'true',
                ),
            ),
        ));

Zmanjšanje največje kvalitete
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Nivo JPEG kvalitete privzeto ni pod vplivom. Lahko pridobite
nadaljnja zmanjšanja velikosti datoteke z nastavitvijo največje velikosti
manjše kot je trenutni nivo slik. To seveda bo na račun
kvalitete slike:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                jpegoptim:
                    bin: path/to/jpegoptim
                    max: 70

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="jpegoptim"
                bin="path/to/jpegoptim"
                max="70" />
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'jpegoptim' => array(
                    'bin' => 'path/to/jpegoptim',
                    'max' => '70',
                ),
            ),
        ));

Krajša sintaksa: Twig funkcija
------------------------------

Če uporabljate Twig, je možno doseči vse to s krajšo
sintakso z omogočenjem in uporabo posebne Twig funkcije. Začnite z dodajanjem
sledečih nastavitev:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                jpegoptim:
                    bin: path/to/jpegoptim
            twig:
                functions:
                    jpegoptim: ~

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="jpegoptim"
                bin="path/to/jpegoptim" />
            <assetic:twig>
                <assetic:twig_function
                    name="jpegoptim" />
            </assetic:twig>
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'jpegoptim' => array(
                    'bin' => 'path/to/jpegoptim',
                ),
            ),
            'twig' => array(
                'functions' => array('jpegoptim'),
                ),
            ),
        ));

Twig predloga je sedaj lahko spremenjena na sledeče:

.. code-block:: html+jinja

    <img src="{{ jpegoptim('@AcmeFooBundle/Resources/public/images/example.jpg') }}" alt="Example"/>

Lahko določite izhodni direktorij v nastavitvah na sledeči način:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            filters:
                jpegoptim:
                    bin: path/to/jpegoptim
            twig:
                functions:
                    jpegoptim: { output: images/*.jpg }

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="jpegoptim"
                bin="path/to/jpegoptim" />
            <assetic:twig>
                <assetic:twig_function
                    name="jpegoptim"
                    output="images/*.jpg" />
            </assetic:twig>
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            'filters' => array(
                'jpegoptim' => array(
                    'bin' => 'path/to/jpegoptim',
                ),
            ),
            'twig' => array(
                'functions' => array(
                    'jpegoptim' => array(
                        output => 'images/*.jpg'
                    ),
                ),
            ),
        ));

.. _`Jpegoptim`: http://www.kokkonen.net/tjko/projects.html
