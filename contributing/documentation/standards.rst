Standardi dokumentacije
=======================

Da bi pomagali bralcu, kakor je mogoče in izdelati primere kode, ki
izgledajo in dajejo občutek znanosti, bi morali slediti tem standardom.

Sphinx
------

* Sledeči znaki so izbrani za različne nivoje naslovov: nivo 1
  je ``=``, nivo 2 ``-``, nivo 3 ``~``, nivo 4 ``.`` in nivo 5 ``"``;
* Vsaka vrstica bi morala bit prelomljena po prvi besedi, ki prekorači
  72-i znak (torej večina vrstic se konča pri 72-78 znaku);
* Okrajšava ``::`` je *prednostna* nad ``.. code-block:: php`` za pričetek PHP
  kodnega bloka (preberite `Sphinx dokumentacijo`_ da pogledate, kdaj bi morali uporabiti
  okrajšavo);
* Medvrstične hiperpovezave se **ne** uporablja. Ločena povezava in njena definicija
  cilja, ki jo dodate na konec strani.
* Medvrstično označevanje bi moralo biti končano na isti vrstici, kjer je bilo začeto;

Example
~~~~~~~

.. code-block:: text

    Example
    =======

    When you are working on the docs, you should follow the `Symfony Documentation`_
    standards.

    Level 2
    -------

    A PHP example would be::

        echo 'Hello World';

    Level 3
    ~~~~~~~

    .. code-block:: php

        echo 'You cannot use the :: shortcut here';

    .. _`Symfony Documentation`: http://symfony.com/doc/current/contributing/documentation/standards.html

Primeri kode
------------

* Koda sledi :doc:`Symfony kodnim standardom </contributing/code/standards>`
  kot tudi `Twig kodnim standardom`_;
* Da se izognete horizontalnem pomikanju na blokih kode, raje prelomimo vrstico
  pravilno, če preseže 85 znakov;
* Ko zložite eno ali več vrstic kode, postavite ``...`` v komentar na točki
  zlaganja. Te komentarji so: ``// ...`` (php), ``# ...`` (yaml/bash), ``{# ... #}``
  (twig), ``<!-- ... -->`` (xml/html), ``; ...`` (ini), ``...`` (text);
* Ko zlagate del vrstice, npr. vrednost spremenljivke, dodajte ``...`` (brez komentarja)
  na mesto zlaganja;
* Opis zložene kode: (opcijsko)
  Če zložite nekaj vrstic: opis zlaganja je lahko postavljen za ``...``
  Če zlagate samo del vrstice: opis je lahko postavljen pred vrstico;
* Če je za bralca uporabno, se bi moral primer PHP kode začeti z deklaracijo imenskega
  prostora;
* Pri sklicevanju razredov, poskrbite, da prikažete ``use`` stavke na
  vrhu vašega bloka kode. Ne potrebujete prikazati *vseh* ``use`` stavkov
  v vsakem primeru, samo prikažite, kaj se dejansko uporablja v bloku kode;
* Če je uporabno ``codeblock`` bi se moral začeti s komentarjem, ki vključuje ime
  datoteke v bloku kode. Ne postavljajte prazne vrstice za tem komentarjem,
  razen če je naslednja vrstica tudi komentar;
* Morali bi postaviti ``$`` pred vsako konzolno vrstico.

Oblike
~~~~~~

Primeri nastavitev bi morali prikazati vse podprte oblike z uporabo
:ref:`nastavitveni bloki <docs-configuration-blocks>`. Podprte oblike
(in njihov vrstni red) so:

* **Configuration** (vključujoč storitve in usmerjanje): Yaml, Xml, Php
* **Validation**: Yaml, anotacije, Xml, Php
* **Doctrine Mapping**: anotacije, Yaml, Xml, Php

Primer
~~~~~~

.. code-block:: php

    // src/Foo/Bar.php
    namespace Foo;

    use Acme\Demo\Cat;
    // ...

    class Bar
    {
        // ...

        public function foo($bar)
        {
            // set foo with a value of bar
            $foo = ...;

            $cat = new Cat($foo);

            // ... check if $bar has the correct value

            return $cat->baz($bar, ...);
        }
    }

.. caution::

    V Yaml bi morali postaviti presledek za ``{`` in pred ``}`` (npr. ``{ _controller: ... }``),
    vendar to ne bi smelo biti urejeno v Twig-u (npr.  ``{'hello' : 'value'}``).

Standardi jezika
----------------

* Za sekcije uporabite sledeča pravila za rabo velikih začetnic:
  `Raba velikih začetnic prve besede in vseh ostalih besed razen za besede zaprtih razredov`_:
  The Vitamins are in my Fresh California Raisins
* Ne uporabite t.i. `serifnih (Oxford) vejic`_;
* Morali bi uporabiti obliko *vi* namesto *mi* (t.j. izogibanje prve osebe:
  namesto tega uporabite drugo osebo).

.. _`Sphinx dokumentacijo`: http://sphinx-doc.org/rest.html#source-code
.. _`Twig kodnim standardom`: http://twig.sensiolabs.org/doc/coding_standards.html
.. _`Raba velikih začetnic prve besede in vseh ostalih besed razen za besede zaprtih razredov`: http://en.wikipedia.org/wiki/Letter_case#Headings_and_publication_titles
.. _`serifnih (Oxford) vejic`: http://en.wikipedia.org/wiki/Serial_comma
