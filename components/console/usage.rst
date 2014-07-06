.. index::
    single: Console; Usage

Uporaba konzolnih ukazov, bližnjic in vgrajenih ukazov
======================================================

Kot dodatek opcijam, ki jih specificirate za vaše ukaze, je na voljo nekaj
vgrajenih opcij, kot tudi nekaj vgrajenih ukazov za konzolno komponento.

.. note::

    Te primeri predvidevajo, da ste dodali datoteko ``application.php`` za pogon
    v vmesniku ukazne vrstice (cli)::

        #!/usr/bin/env php
        <?php
        // application.php

        use Symfony\Component\Console\Application;

        $application = new Application();
        // ...
        $application->run();

Vgrajeni ukazi
~~~~~~~~~~~~~~

Na voljo je vgrajeni ukaz ``list``, ki izpiše vse standardne opcije
in registrirane ukaze:

.. code-block:: bash

    $ php application.php list

Lahko dobite tudi enak izpis s pogonom brez ukaza:

.. code-block:: bash

    $ php application.php

Ukaz help izpiše informacije pomoči za določen ukaz. Na primer, da dobite
pomoč za ukaz ``list``:

.. code-block:: bash

    $ php application.php help list

Pogon ``help`` brez specificiranja ukaza bo izpisalo globalne opcije:

.. code-block:: bash

    $ php application.php help

globalne opcije
~~~~~~~~~~~~~~~

Lahko dobite informacije pomoči za katerikoli ukaz z opcijo ``--help``. Da
dobite pomoč za ukaz list:

.. code-block:: bash

    $ php application.php list --help
    $ php application.php list -h

Lahko tudi zatrete izpis z:

.. code-block:: bash

    $ php application.php list --quiet
    $ php application.php list -q

Lahko dobite bolj opisna sporočila (če je to podprto za ukaz) z:

.. code-block:: bash

    $ php application.php list --verbose
    $ php application.php list -v

Zastavita verbose lahko opcijsko vzame vrednost med 1 (privzeto) in 3, da
izpiše še bolj opisna sporočila:

.. code-block:: bash

    $ php application.php list --verbose=2
    $ php application.php list -vv
    $ php application.php list --verbose=3
    $ php application.php list -vvv

Če nastavite opcijske argumente, da date vaši aplikaciji ime in verzijo::

    $application = new Application('Acme Console Application', '1.2');

potem lahko uporabite:

.. code-block:: bash

    $ php application.php list --version
    $ php application.php list -V

da dobite ta izpis informacij:

.. code-block:: text

    Acme Console Application version 1.2

Če ne ponudite obeh argumentov, potem bo samo izpisalo:

.. code-block:: text

    console tool

Lahko tudi prisilite vključitev ANSI izpisa barv z:

.. code-block:: bash

    $ php application.php list --ansi

ali ga izključite z:

.. code-block:: bash

    $ php application.php list --no-ansi

Lahko tudi zatrete katerakoli interaktivna vprašanja iz ukaza, ki ga poganjate z:

.. code-block:: bash

    $ php application.php list --no-interaction
    $ php application.php list -n

Sintaksa bližnjice
~~~~~~~~~~~~~~~~~~

Ne potrebujete vpisovati celotnega imena ukaza. Lahko samo vtipkate
najkrajše nedvoumno ime, da poženete ukaz. Torej, če so na voljo ne-spopadljivi
ukazi, potem lahko poženete ``help`` takole:

.. code-block:: bash

    $ php application.php h

Če imate ukaze, ki uporabljajo ``:`` za imenske prostore ukazov, potem morate
vpisati samo najkrajši nedvoumen tekst za vsak del. Če ste izdelali
``demo:greet`` kot je prikazano v :doc:`/components/console/introduction` potem ga
lahko poženete z:

.. code-block:: bash

    $ php application.php d:g Fabien

Če vnesete kratek ukaz, ki je dvoumen (to pomeni, da se ujema z več kot enim
ukazom), potem ne bo noben ukaz poganjan in nekaj predlogov možnih
ukazov na izbiro bo izpisanih.
