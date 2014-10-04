Generiranje novega krmilnika
============================

Uporaba
-------

Ukaz ``generate:controller`` generira nov krmilnik vključno z
akcijami, testi, predlogami in usmeritvami.

Privzeto je ukaz pognan v interaktivnem načinu in vpraša vprašanja za
določitev imena paketa, lokacije, formata nastavitev in privzete
strukture:

.. code-block:: bash

    $ php app/console generate:controller

Ukaz je lahko pognan tako v ne interaktivnem načinu z uporabo
opcije ``--no-interaction`` brez, da se pozabi vse potrebne opcije:

.. code-block:: bash

    $ php app/console generate:controller --no-interaction --controller=AcmeBlogBundle:Post

Opcije na voljo
---------------

* ``--controller``: Ime krmilnika dano kot bližnjica notacije, ki vsebuje
  ime paketa v katerem je krmilnik lociran in ime
  krmilnika. Na primer: ``AcmeBlogBundle:Post`` (ustvari ``PostController``
  znotraj paketa ``AcmeBlogBundle``):

    .. code-block:: bash

        $ php app/console generate:controller --controller=AcmeBlogBundle:Post

* ``--actions``: Seznam akcij za generiranje v razredu krmilnika. Ta
  ima format, kot je ``%actionname%:%route%:%template`` (kjer je ``:%template%``
  opcijski):

    .. code-block:: bash

        $ php app/console generate:controller --actions="showPostAction:/article/{id} getListAction:/_list-posts/{max}:AcmeBlogBundle:Post:list_posts.html.twig"

        # or
        $ php app/console generate:controller --actions=showPostAction:/article/{id} --actions=getListAction:/_list-posts/{max}:AcmeBlogBundle:Post:list_posts.html.twig

* ``--route-format``: (**annotation**) [vrednosti: yml, xml, php ali annotation]
  Ta opcija določa format, ki bo uporablje za usmerjanje. Privzeto
  ukaz uporablja format ``annotation``:

    .. code-block:: bash

        $ php app/console generate:controller --route-format=annotation

* ``--template-format``: (**twig**) [vrednosti: twig ali php] Ta opcija določa
  format, ki bo uporabljen za predloge. Privzeto ukaz uporablja format
  ``Twig``:

    .. code-block:: bash

        $ php app/console generate:controller --template-format=twig
