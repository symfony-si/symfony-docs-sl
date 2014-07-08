Generiranje novega skeletona paketa
===================================

Uporaba
-------

``generate:bundle`` generira novo paketno strukturo in ga avtomatično
aktivira v aplikaciji.

Privzeto je ukaz pognan v interaktivnem načinu in vpraša vprašanja, da
določi ime paketa, lokacijo, format nastavitev in privzeto
strukturo:

.. code-block:: bash

    php app/console generate:bundle

Za deaktivacijo interaktivnega načina, uporabite opcijo ``--no-interaction`` vendar ne
pozabite podati vseh potrebnih opcij:

.. code-block:: bash

    php app/console generate:bundle --namespace=Acme/Bundle/BlogBundle --no-interaction

Opcije na voljo
---------------

* ``--namespace``: Imenski prostor paketa za ustvariti. Imenski prostor bi se moral
  začeti z imenom "vendor" kot je ime vašega podjetja, ime vašega projekta ali
  ime vašega klienta, sledi mu pa en ali več opcijskih kategoriziranih pod-imenskih prostorov
  ter moral bi se končati z imenom samega paketa (ki mora imeti na koncu Bundle kot
  pripono):

  .. code-block:: bash

        php app/console generate:bundle --namespace=Acme/Bundle/BlogBundle

* ``--bundle-name``: Opcijsko ime paketa. Mora biti niz, ki se konča s
  predpono ``Bundle``:

    .. code-block:: bash

        php app/console generate:bundle --bundle-name=AcmeBlogBundle

* ``--dir``: Direktorij v katerem je paket shranjen. Po konvenciji
  ukaz zazna in uporabi mapo aplikacije ``src/``:

    .. code-block:: bash

        php app/console generate:bundle --dir=/var/www/myproject/src

* ``--format``: (**annotation**) [vrednosti: yml, xml, php ali annotation]
  Določi format, ki bo uporabljen za generiranje nastavitvenih datotek, kot je
  usmerjanje. Privzeto, ukaz uporablja format ``annotation``. Izbira
  formata ``annotation`` pričakuje, da je ``SensioFrameworkExtraBundle``
  že nameščen:

    .. code-block:: bash

        php app/console generate:bundle --format=annotation

* ``--structure``: Če je prisotna, generira
  celotno privzeto strukturo direktorijev vključno s praznimi javnimi direktoriji za
  dokumentacijo, spletna sredstva in slovar prevodov:

    .. code-block:: bash

        php app/console generate:bundle --structure
