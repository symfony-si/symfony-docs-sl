.. index::
    single: Yaml; YAML Format

Format YAML
===========

Glede na uradno `YAML`_ stran, YAML je "človeku prijazen podatkovni
standard serializacije za vse programske jezike".

Četudi format YAML lahko opisuje kompleksne gnezdene podatkovne strukture, to
poglavje samo opisuje najmanjši skupek lastnosti potrebnih za uporabo YAML kot
formata nastavitvenih datotek.

YAML je enostaven jezik, ki opisuje podatke. Kot PHP ima sintakso za
enostavne tipe kot so nizi, logične vrednosti, števila s plavajočo vejico ali cela števila. Vendar za razliko od PHP
dela razlike med polji (sekvencami) in hash-i (preslikavami).

Skalarji
--------

Sintaksa za skalarje je podobna sintaksi PHP.

Nizi
~~~~

.. code-block:: yaml

    A string in YAML

.. code-block:: yaml

    'A singled-quoted string in YAML'

.. tip::

    In a single quoted string, a single quote ``'`` must be doubled:

    .. code-block:: yaml

        'A single quote '' in a single-quoted string'

.. code-block:: yaml

    "A double-quoted string in YAML\n"

Citirani stili so uporabno, ko se niz začne ali konča z enim ali več
relevantnih presledkov.

.. tip::

    Dvojno citirani stil ponuja način za izražanje arbitrarnih nizov z
    uporabo ``\`` spreminjajočih (escaping) sekvenc. Je zelo uporabna, ko potrebujete vključiti
    ``\n`` ali unikodni znak v niz.

Ko niz vsebuje lom vrstic, lahko uproabite dobesedni stil, označen
z znakom ``|``, za označitev, da bo niz lomljev preko večih vrstic. V
dobesednem navedku so nove vrstice ohranjene:

.. code-block:: yaml

    |
      \/ /| |\/| |
      / / | |  | |__

Alternativno so nizi lahko napisani s pospravljenim stilom, označenim z ``>``,
kjer je zlom vsake vrstice zamenjan s presledkom:

.. code-block:: yaml

    >
      This is a very long sentence
      that spans several lines in the YAML
      but which will be rendered as a string
      without carriage returns.

.. note::

    Bodite pozorni, da dva presledka pred vsako vrstico v prejšnjih primerih.
    Ne bodo se pojavili v končnem nizu PHP.

Številke
~~~~~~~~

.. code-block:: yaml

    # an integer
    12

.. code-block:: yaml

    # an octal
    014

.. code-block:: yaml

    # an hexadecimal
    0xC

.. code-block:: yaml

    # a float
    13.4

.. code-block:: yaml

    # an exponential number
    1.2e+34

.. code-block:: yaml

    # infinity
    .inf

Prazne vrednosti - nulls
~~~~~~~~~~~~~~~~~~~~~~~~

Prazne vrednosti v YAML so lahko izražene z ``null`` ali ``~``.

Logične vrednosti
~~~~~~~~~~~~~~~~~

Logične vrednosti v YAML so izražene s ``true`` in ``false``.

Datumi
~~~~~~

YAML uporablja standard ISO-8601 za izražanje datumov:

.. code-block:: yaml

    2001-12-14t21:59:43.10-05:00

.. code-block:: yaml

    # simple date
    2002-12-14

Zbirke
------

Datoteka YAML je redko uporabljena za opisovanje enostavnih skalarjev. Večino časa
opisuje zbirko. Zbirka je lahko sekvenca ali preslikava
elementov. Obe sekvenci in preslikavi sta pretvorjeni v polja PHP.

Sekvence uporabljajo črto (dash), ki ji sledi presledek:

.. code-block:: yaml

    - PHP
    - Perl
    - Python

Prejšnja datoteka YAML je ekvivalentna sledeči kodi PHP:

.. code-block:: php

    array('PHP', 'Perl', 'Python');

Preslikave uporabljajo dvopičje, ki mu sledi presledek (``:``) za označitev vsakega para ključ/vrednost:

.. code-block:: yaml

    PHP: 5.2
    MySQL: 5.1
    Apache: 2.2.20

kar je ekvivalentno tej PHP kodi:

.. code-block:: php

    array('PHP' => 5.2, 'MySQL' => 5.1, 'Apache' => '2.2.20');

.. note::

    V preslikavi je lahko ključ katerikoli veljaven skalar.

Število presledkov med dvopičjem in vrednostjo ni pomembno:

.. code-block:: yaml

    PHP:    5.2
    MySQL:  5.1
    Apache: 2.2.20

YAML uporablja indentacijo z enim ali več presledkov za opis gnezdenih zbirk:

.. code-block:: yaml

    "symfony 1.0":
      PHP:    5.0
      Propel: 1.2
    "symfony 1.2":
      PHP:    5.2
      Propel: 1.3

Sledeči YAML je ekvivalenten sledeči PHP kodi:

.. code-block:: php

    array(
      'symfony 1.0' => array(
        'PHP'    => 5.0,
        'Propel' => 1.2,
      ),
      'symfony 1.2' => array(
        'PHP'    => 5.2,
        'Propel' => 1.3,
      ),
    );

Obstaja ena pomembna stvar, ki si jo morate zapomniti, ko uporabljate indentacijo v
datoteki YAML: *Indentacija mora biti narejena z enim ali več presledkov, vendar nikoli s
tabulatorji*.

Lahko gnezdite sekvence in preslikave kot želite:

.. code-block:: yaml

    'Chapter 1':
      - Introduction
      - Event Types
    'Chapter 2':
      - Introduction
      - Helpers

YAML lahko uporabi tudi stile poteka za zbirke z uporabo eksplicitnih indikatorjev
naemsto indentacije za označevanje obsega.

Sekvenca je lahko napisana kot seznam ločen z vejicami znotraj oglatih oklepajev
(``[]``):

.. code-block:: yaml

    [PHP, Perl, Python]

Preslikava je lahko napisana kot seznam ključ/vrednosti ločen z vejicami znotraj zavitih
oklepajev (``{}``):

.. code-block:: yaml

    { PHP: 5.2, MySQL: 5.1, Apache: 2.2.20 }

Lahko tudi mešate in ujemate stile za doseg boljše bralnosti:

.. code-block:: yaml

    'Chapter 1': [Introduction, Event Types]
    'Chapter 2': [Introduction, Helpers]

.. code-block:: yaml

    "symfony 1.0": { PHP: 5.0, Propel: 1.2 }
    "symfony 1.2": { PHP: 5.2, Propel: 1.3 }

Komentarji
----------

Komentarji so lahko dodani v YAML s predpono hash znaka (``#``);

.. code-block:: yaml

    # Comment on a line
    "symfony 1.0": { PHP: 5.0, Propel: 1.2 } # Comment at the end of a line
    "symfony 1.2": { PHP: 5.2, Propel: 1.3 }

.. note::

    Komentarji so enostavno ignorirani v razčlenjevalniku YAML in jih ni potrebno
    indentirati glede na trenutni nivo gnezdenja v zbirki.

.. _YAML: http://yaml.org/
