.. index::
   single: Assetic; YUI Compressor

Kako zmanjšati datoteke JavaScript in stile z YUI Compressor
============================================================

Yahoo! ponuja odlično orodje za zmanjšanje JavaScript in stilskih datotek,
da potujejo po žicah hitreje, t.i. `YUI Compressor`_. Zahvaljujoč Assetic-u,
lahko uporabite prednosti tega orodja zelo enostavno.

.. caution::

    YUI Compressor gre skozi t.i. `deprecation process`_. Vendar ne
    skrbite! Glejte :doc:`/cookbook/assetic/uglifyjs` za alternativo.

Prenesite YUI Compressor JAR
----------------------------

YUI Compressor je napisan v Javi in distribuiran kot JAR. `Prenesite JAR`_
iz Yahoo! strani in ga shranite v ``app/Resources/java/yuicompressor.jar``.

Nastavite YUI filtre
--------------------

Sedaj lahko nastavite dva Assetic filtra v vaši aplikaciji, enega za
zmanjšanje JavaScript-a z YUI Compressor-jem in enega za zmanjšanje
stilov:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        assetic:
            # java: "/usr/bin/java"
            filters:
                yui_css:
                    jar: "%kernel.root_dir%/Resources/java/yuicompressor.jar"
                yui_js:
                    jar: "%kernel.root_dir%/Resources/java/yuicompressor.jar"

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <assetic:config>
            <assetic:filter
                name="yui_css"
                jar="%kernel.root_dir%/Resources/java/yuicompressor.jar" />
            <assetic:filter
                name="yui_js"
                jar="%kernel.root_dir%/Resources/java/yuicompressor.jar" />
        </assetic:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('assetic', array(
            // 'java' => '/usr/bin/java',
            'filters' => array(
                'yui_css' => array(
                    'jar' => '%kernel.root_dir%/Resources/java/yuicompressor.jar',
                ),
                'yui_js' => array(
                    'jar' => '%kernel.root_dir%/Resources/java/yuicompressor.jar',
                ),
            ),
        ));

.. note::

    Windows uporabniki si morajo posodobiti nastavitve na ustrezno java lokacijo.
    V Windows7 x64 bit je privzeto ``C:\Program Files (x86)\Java\jre6\bin\java.exe``.

Sedaj imate dostop do dveh novih Assetic filtrov v vaši aplikaciji:
``yui_css`` in ``yui_js``. Ta bosta uporabljala YUI Compressor za ustrezno zmanjšanje
stilov in JavaScript-a.

Zmanjšajte vaša sredstva
------------------------

Sedaj imate YUI Compressor nastavljen, vendar nič se ne bo zgodilo dokler
ne uporabite enega od teh filtrov na sredstvu. Ker so vaša sredstva del
nivoja pogleda, bo to urejeno v vaših predlogah:

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

.. note::

    Zgornji primer predpostavlja, da imate paket imenovan ``AcmeFooBundle``
    in vaše JavaScript datoteke so v ``Resources/public/js`` direktoriju pod
    vašim paketom. To ni pomembno vendar - lahko vključite vaše JavaScript
    datoteke ne glede na to, kje so.

Z dodatkom filtra ``yui_js`` na znački sredstva zgoraj, bi morali
sedaj videti zmanjšani JavaScript prihajajoč po žici veliko hitreje. Enak proces
se lahko ponovi za zmanjšanje vaših stilov.

.. configuration-block::

    .. code-block:: html+jinja

        {% stylesheets '@AcmeFooBundle/Resources/public/css/*' filter='yui_css' %}
            <link rel="stylesheet" type="text/css" media="screen" href="{{ asset_url }}" />
        {% endstylesheets %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->stylesheets(
            array('@AcmeFooBundle/Resources/public/css/*'),
            array('yui_css')
        ) as $url): ?>
            <link rel="stylesheet" type="text/css" media="screen" href="<?php echo $view->escape($url) ?>" />
        <?php endforeach; ?>

Onemogočite zmanjšanje v razhroščevalnem načinu
-----------------------------------------------

Zmanjšane JavaScript datoteke in stili se zelo težko bere, kaj šele
razhroščuje. Zaradi tega vam Assetic omogoča onemogočiti določen filter, ko je
vaša aplikacija v razhroščevalnem načinu. To lahko storite z dodajanjem predpone
imenu filtra v vaši predlogi z vprašajem: ``?``. To pove Assetic-u, da naj
uporabi ta filter samo, ko je razhroščevalni način onemogočen.

.. configuration-block::

    .. code-block:: html+jinja

        {% javascripts '@AcmeFooBundle/Resources/public/js/*' filter='?yui_js' %}
            <script src="{{ asset_url }}"></script>
        {% endjavascripts %}

    .. code-block:: html+php

        <?php foreach ($view['assetic']->javascripts(
            array('@AcmeFooBundle/Resources/public/js/*'),
            array('?yui_js')
        ) as $url): ?>
            <script src="<?php echo $view->escape($url) ?>"></script>
        <?php endforeach; ?>

.. tip::

    Namesto dodajanja filtra k značkam sredstev, ga lahko tudi globalno
    omogočite z dodatkom t.i. apply-to-attribute v nastavitvah filtra, na primer
    v filtru yui_js ``apply_to: "\.js$"``. Da imate samo filter
    uporabljen v produkciji, dodajte to v config_prod datoteko namesto v skupno
    config datoteko. Za podrobnosti o uporabi filtrov glede na končnico datoteke,
    glejte :ref:`cookbook-assetic-apply-to`.

.. _`YUI Compressor`: http://developer.yahoo.com/yui/compressor/
.. _`Prenesite JAR`: http://yuilibrary.com/projects/yuicompressor/
.. _`deprecation process`: http://www.yuiblog.com/blog/2012/10/16/state-of-yui-compressor/
