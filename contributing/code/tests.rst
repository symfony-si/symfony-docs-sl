Poganjanje Symfony2 testov
==========================

Pred pošiljanjem :doc:`popravka <patches>` za vključitev, morate pognati
Symfony2 testno opremo za preverjanje, da niste česa zlomili.

PHPUnit
-------

Za poganjanje Symfoyn2 testne opreme najprej `namestite`_ PHPUnit 3.6.4 ali kasnejši:

.. code-block:: bash

    $ pear config-set auto_discover 1
    $ pear install pear.phpunit.de/PHPUnit

Odvisnosti (opcijsko)
---------------------

Za poganjanje celotne testne opreme, vključujoč teste, ki so odvisni na
zunanjih odvisnostih, mora biti Symfony2 jih zmožen avtomatsko naložiti.
Privzeto so avtomatsko nameščeni iz `vendor/` direktorija pod glavnim
vrhnjim direktorijem (poglejte `autoload.php.dist`).

Testna oprema potrebuje sledeče tretje-osebne knjižnice:

* Doctrine
* Swift Mailer
* Twig
* Monolog

Da jih namestite, uporabite `Composer`_:

Korak 1: Dobite `Composer`_

.. code-block:: bash

    curl -s http://getcomposer.org/installer | php

Prepričajte se, da ste prenesli ``composer.phar`` v isti direktorij,
kjer je locirana ``composer.json`` datoteka.

Korak 2: Namestite izdelovalce (vendors)

.. code-block:: bash

    $ php composer.phar --dev install

.. note::

    Pomnite, da skripta potrebuje nekaj časa za zaključek.

.. note::

    Če nimate nameščenega ``curl`` lahko tudi samo prenesete ``installer``
    datoteko ročno iz http://getcomposer.org/installer. Postavite to datoteko v
    vaš projekt in nato poženite:

    .. code-block:: bash

        $ php installer
        $ php composer.phar --dev install

Po namestitvi lahko posodobite izdelovalce na njihove zadnje verzije s
sledečim ukazom:

.. code-block:: bash

    $ php composer.phar --dev update

Poganjanje
----------

Prvo, posodobite izdelovalce (glejte zgoraj).

Nato, poženite testno opremo iz Symfony2 vrhnjega direktorija s sledečim
ukazom:

.. code-block:: bash

    $ phpunit

Izpis bi moral prikazati `OK`. Drugače potrebujete ugotoviti, kaj se dogaja
in če so testi pokvarjeni zaradi vaših sprememb.

.. tip::

    Če želite testirati eno komponento, vpišite njeno pot za `phpunit`
    ukazom, npr.:

    .. code-block:: bash

        $ phpunit src/Symfony/Component/Finder/

.. tip::

    Poženite testno opremo pred uporabo vaših modifikacij, da preverite, če se
    v redu poženejo na vaših nastavitvah.

Pokritost kode
--------------

Če dodate novo lastnost, morate tudi preveriti pokritost kode z uporabo
opcije `coverage-html`:

.. code-block:: bash

    $ phpunit --coverage-html=cov/

Preverite pokritost kode z odprtjem generirane `cov/index.html` strani v
brskalniku.

.. tip::

    Pokritost kode deluje samo, če imate omogočen XDebug in vse
    odvisnosti nameščene.

.. _namestite: http://www.phpunit.de/manual/current/en/installation.html
.. _`Composer`: http://getcomposer.org/
