.. index::
   single: Components; Installation
   single: Components; Usage

Kako namestiti in uporabiti komponente Symfony2
===============================================

Če začenjate z novim projektom (ali že imate projekt), ki bo uporabljal
eno ali več komponent je najenostavnejši način za integracijo vsega s `Composer`_-jem.
Composer je dovolj pameten, da prenese komponente, ki jih potrebujete in
poskrbi za avtomatsko nalaganje, da lahko začnete uporabljati knjižnice takoj.

Ta članek vas bo popeljal skozi uporabo :doc:`components/finder`, čeprav
se to nanaša na uporabo katerekoli komponente.

Uporaba komponente Finder
-------------------------

**1.** Če ustvarjate nov projekt, ustvarite prazen direktorij zanj.

**2.** Ustvarite novo datoteko imenovano ``composer.json`` in prilepite sledeče vanjo:

.. code-block:: json

    {
        "require": {
            "symfony/finder": "2.3.*"
        }
    }

Če že imate datoteko ``composer.json``, samo dodajte to vrstico vanjo.
Lahko boste potrebovali tudi prilagoditi verzijo (npr. ``2.2.2`` ali ``2.3.*``).

Lahko raziščete imena komponent in verzij na `packagist.org`_.

**3.** `Namestite composer`_ če ga še nimate prisotnega na vašem sistemu:

**4.** Prenesite vendor knjižnice in generirajte datoteko ``vendor/autoload.php``:

.. code-block:: bash

    $ php composer.phar install

**5.** Napišite vašo kodo:

Ko je enkrat Composer prenesel komponente, morate vse, kar je za narediti, vključiti
datoteko ``vendor/autoload.php``, ki je bila generirana s Composer-jem. Ta datoteka
poskrbi za avtomatsko nalaganje vseh knjižnic, tako da jih lahko uporabite
takoj::

    // File: src/script.php

    // update this to the path to the "vendor/" directory, relative to this file
    require_once '../vendor/autoload.php';

    use Symfony\Component\Finder\Finder;

    $finder = new Finder();
    $finder->in('../data/');

    // ...

.. tip::

    Če želite uporabiti vse komponente Symfony2, potem namesto dodajanja
    eno po eno:

    .. code-block:: json

        {
            "require": {
                "symfony/finder": "2.3.*",
                "symfony/dom-crawler": "2.3.*",
                "symfony/css-selector": "2.3.*"
            }
        }

    lahko uporabite:

    .. code-block:: json

        {
            "require": {
                "symfony/symfony": "2.3.*"
            }
        }

    To bo vključilo knjižnice Bundle in Bridge, ki jih morda ne
    boste dejansko potrebovali.

Kaj sedaj?
----------

Sedaj ko je komponenta nameščena in avtomatsko naložena, preberite specifično
dokumentacijo komponente, da izveste več o tem, kako jo uporabiti.

In zabavajte se!

.. _Composer: http://getcomposer.org
.. _Namestite composer: http://getcomposer.org/download/
.. _packagist.org: https://packagist.org/
