.. index::
    single: Console; Usage

Kako uporabljati konzolo
========================

Stran :doc:`/components/console/usage` dokumentacije komponent pogleda
globalne opcije konzole. Ko uporabljate konzolo kot del celotnega ogrodja,
je na voljo še nekaj dodatnih globalnih opcij.

Privzeto, konzolni ukazi se poganjajo v ``dev`` okolju in morda boste to želeli
spremeniti za nek ukaz. Na primer, lahko boste želeli pognati nekaj ukazov
v ``prod`` okolju za razloge uspešnosti. Tudi rezultati nekaj ukazov
bodo drugačni odvisno od okolja. Na primer ukaz ``cache:clear`` bo počistilo in
ogrelo predpomnilnik samo za določeno okolje. Za čiščenje in "gretje" ``prod``
predpomnilnika morate pognati:

.. code-block:: bash

    $ php app/console cache:clear --env=prod

ali ekvivalentno:

.. code-block:: bash

    $ php app/console cache:clear -e prod

Poleg spremembe okolja lahko tudi izberete, da onemogočite način razhroščevanja.
To je lahko uporabno, kjer želite poganjati ukaze v okolju ``dev``, vendar se
izogniti udaru na uspešnost pri zbiranju podatkov razhroščevanja:

.. code-block:: bash

    $ php app/console list --no-debug

Obstaja interaktivna lupina, ki vam omogoča, da vnesete ukaze brez, da bi
vsakič specificirali ``php app/console``, kar je uporabno, če potrebujete pognati
nekaj ukazov. Za vstop v lupino poženite:

.. code-block:: bash

    $ php app/console --shell
    $ php app/console -s

Sedaj lahko poganjate ukate z ukaznim imenom:

.. code-block:: bash

    Symfony > list

Ko uporabljate lupino, lahko izberete za pogon vsak ukaz v ločenem procesu:

.. code-block:: bash

    $ php app/console --shell --process-isolation
    $ php app/console -s --process-isolation

Ko to naredite, izpis ne bo obarvan in interaktivnost ni podprta, tako da boste
potrebovali poslati vse parametre ukazov eksplicitno.

.. note::

    Razen, če uporabljate izolirane procese, čiščenje predpomnilnika v lupini ne bo
    imelo učinka na naknadne ukaze, ki jih poženete. To je zato, ker so originalne
    datoteke predpomnilnika še vedno uporabljene.
