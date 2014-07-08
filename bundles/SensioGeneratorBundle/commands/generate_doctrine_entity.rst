Generiranje novega nastavka entitete Doctrine
=============================================

Uporaba
-------

Ukaz ``generate:doctrine:entity`` generira nov nastavek entitete Doctrine,
ki vključuje definicijo preslikave in lastnosti, getter-je in setter-je razreda.

Privzeto je ukaz pognan v interaktivnem načinu in vpraša vprašanja za
določitev imena paketa, lokacijo, format nastavitev in privzeto
strukturo:

.. code-block:: bash

    php app/console generate:doctrine:entity

Ukaz je lahko pognan v ne interaktivnem načinu z uporabo
opcije ``--no-interaction`` brez, da pozabi vse potrebne opcije:

.. code-block:: bash

    php app/console generate:doctrine:entity --no-interaction --entity=AcmeBlogBundle:Post --fields="title:string(100) body:text" --format=xml

Opcije na voljo
---------------

* ``--entity``: Ime entitete dano ko notacija bližnjice, ki vsebuje
  ime paketa v katerem se nahaja entiteta in ime entitete. Na
  primer: ``AcmeBlogBundle:Post``:

    .. code-block:: bash

        php app/console generate:doctrine:entity --entity=AcmeBlogBundle:Post

* ``--fields``: Seznam polj za generiranje razreda entitete:

    .. code-block:: bash

        php app/console generate:doctrine:entity --fields="title:string(100) body:text"

* ``--format``: (**annotation**) [values: yml, xml, php ali annotation] Ta
  opcija določa format za uporabo generiranih nastavitvenih datotek
  kot je usmerjanje. Privzeto ukaz uporablja format ``annotation``:

    .. code-block:: bash

        php app/console generate:doctrine:entity --format=annotation

* ``--with-repository``: Ta opcija pove ali generirati ali ne
  povezani razred Doctrine ``EntityRepository``:

    .. code-block:: bash

        php app/console generate:doctrine:entity --with-repository
