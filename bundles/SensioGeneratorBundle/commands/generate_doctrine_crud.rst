Generiranje krmilnika CRUD na osnovi entitete Doctrine
======================================================

Uporaba
-------

``generate:doctrine:crud`` generira osnovni krmilnik za dano entiteto
locirano v danem paketu. Ta krmilnik omogoča izvajati pet osnovnih
operacij na modelu.

* Izpiše seznam vseh vnosov,
* Prikazuje en dani vnos identificiran s svojim primarnim ključem,
* Ustvari nov vnos,
* Uredi obstoječi vnos,
* Izbriše obstoječi vnos.

Privzeto je ukaz pognan v interaktivnem načinu in vpraša vprašanja za
določitev imena entitete, predpone usmeritve ali naj ali ne generira pisalne
akcije:

.. code-block:: bash

    php app/console generate:doctrine:crud

Za deaktivacijo interaktivnega načina, uporabite opcijo ``--no-interaction`` vendar ne
pozabite podati vseh potrebnih opcij:

.. code-block:: bash

    php app/console generate:doctrine:crud --entity=AcmeBlogBundle:Post --format=annotation --with-write --no-interaction

Opcije na voljo
---------------

* ``--entity``: Ime entitete podano kot notacija bližnjice, ki vsebuje
  ime paketa v katerem je entiteta locirana in ime entitete. Na
  primer: ``AcmeBlogBundle:Post``:

  .. code-block:: bash

      php app/console generate:doctrine:crud --entity=AcmeBlogBundle:Post

* ``--route-prefix``: Predpona za uporabo za vsako usmeritev, ki identificira
  akcijo:

  .. code-block:: bash

      php app/console generate:doctrine:crud --route-prefix=acme_post

* ``--with-write``: (**no**) [vrednosti: yes|no] Ali da ali ne generirati
  akcij ``new``, ``create``, ``edit``, ``update`` in ``delete``:

  .. code-block:: bash

      php app/console generate:doctrine:crud --with-write

* ``--format``: (**annotation**) [vrednosti: yml, xml, php ali annotation]
  Določa format za uporabiti za generiranje nastavitvenih datotek kot so
  usmerjanje. Privzeto ukaz uporablja format ``annotation``. Izbira
  formata ``annotation`` pričakuje, da je ``SensioFrameworkExtraBundle``
  že nameščen:

  .. code-block:: bash

      php app/console generate:doctrine:crud --format=annotation

* ``--overwrite``: (**no**) [vrednosti: yes|no] Ali naj ali ne prepiše obstoječe datoteke:

  .. code-block:: bash

       php app/console generate:doctrine:crud --overwrite
