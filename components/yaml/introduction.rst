.. index::
   single: Yaml
   single: Components; Yaml

Komponenta YAML
===============

    Komponenta YAML naloži in izvrže datoteke YAML.

Kaj je?
-------

Komponenta Symfony2 YAML razčleni nize YAML in jih pretvori v PHP polja.
Zmožna je tudi pretvoriti PHP polja v nize YAML.

`YAML`_, *YAML Ain't Markup Language*, je človeku prijazen standard serializacije
podatkov za vse programske jezike. YAML je odličen format za vaše
nastavitvene datoteke. Datoteke YAML so tako izražalne kot datoteke XML in tako bralne
kot datoteke INI.

Komponenta Symfony2 YAML implementira YAML verzijo 1.2
specifikacij.

.. tip::

    Naučite se več o komponenti Yaml v
    članku :doc:`/components/yaml/yaml_format`.

Namestitev
----------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestite jo preko Composer-ja </components/using_components>` (``symfony/yaml`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Yaml).

Zakaj?
------

Hitro
~~~~~

Eden ciljev Symfony YAML je najti pravo razmerje med hitrostjo in
lastnostmi. Podpira samo lastnosti potrebne za upravljanje nastavitvenih datotek.

Pravi razčlenjevalnik
~~~~~~~~~~~~~~~~~~~~~

Podpira pravi razčlenjevalnik in je sposobna razčleniti velik skupek
specifikacije YAML za vse vaše potrebe nastavitev. To tudi pomeni, da je razčlenjevalnik
precej robusten, enostaven za razumeti in dovolj enostaven za razširitev.

Jasna sporočila napak
~~~~~~~~~~~~~~~~~~~~~

Kadarkoli imate problem sintakse z vašimi datotekami YAML, knjižnica izpiše
pomagalna sporočila z imeni datotek in številko vrstice, kjer se je problem
zgodil. Precej poenostavi razhroščevanje.

Podpora odlaganja
~~~~~~~~~~~~~~~~~

Je tudi sposobna odložiti PHP polja v YAML s podporo za objekte in medvrstičnim
nivojem nastavitev za lepe izpise.

Podpora tipov
~~~~~~~~~~~~~

Podpira tudi večino vgrajenih YAML tipov kot so datumi, cela števila, osmiška števila,
logične vrednosti in veliko več ...

Celotna ključna združevalna podpora
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Polna podpora za sklicevanje, aliase in polno ključno združevanje. Ne ponavljajte
se s sklicevanjem na pogoste nastavitvene delce.

Uporaba komponente Symfony2 YAML
--------------------------------

Komponenta Symfony2 YAML je zelo enostavna in sestavljena iz dveh glavnih razredov:
eden razčleni nize YAML (:class:`Symfony\\Component\\Yaml\\Parser`) in
drugi odloži polje PHP v niz YAML
(:class:`Symfony\\Component\\Yaml\\Dumper`).

Povrh teh dveh razredov, razred :class:`Symfony\\Component\\Yaml\\Yaml`
deluje kot lahek ovoj, ki poenostavi pogoste uporabe.

Branje datotek YAML
~~~~~~~~~~~~~~~~~~~

Metoda :method:`Symfony\\Component\\Yaml\\Parser::parse` razčleni niz YAML
in ga pretvori v polje PHP:

.. code-block:: php

    use Symfony\Component\Yaml\Parser;

    $yaml = new Parser();

    $value = $yaml->parse(file_get_contents('/path/to/file.yml'));

Če pride do napake med razčlenjevanjem, razčlenjevalnik vrže
izjemo :class:`Symfony\\Component\\Yaml\\Exception\\ParseException`,
ki nakazuje tip napake in vrstico originalnega niza YAML, kjer se je
napaka zgodila:

.. code-block:: php

    use Symfony\Component\Yaml\Exception\ParseException;

    try {
        $value = $yaml->parse(file_get_contents('/path/to/file.yml'));
    } catch (ParseException $e) {
        printf("Unable to parse the YAML string: %s", $e->getMessage());
    }

.. tip::

    Kot je razčlenjevalnik ponovno vstopen, lahko uporabite isti objekt razčlenjevalnika za nalaganje
    različnih nizov YAML.

Lahko je tudi priročno uporabiti
ovijalno metodo :method:`Symfony\\Component\\Yaml\\Yaml::parse`:

.. code-block:: php

    use Symfony\Component\Yaml\Yaml;

    $yaml = Yaml::parse(file_get_contents('/path/to/file.yml'));

Statična metoda :method:`Symfony\\Component\\Yaml\\Yaml::parse` vzame niz YAML
ali datoteko, ki vsebuje YAML. Notranje pokliče
metodo :method:`Symfony\\Component\\Yaml\\Parser::parse` vendar izboljša
napako, če gre kaj narobe z dodajanjem imena datoteke k sporočilu.

.. caution::

    Ker je trenutno mogoče podati ime datoteke tej metodi,
    morate najpre preveriti vnos. Podajanje imena datoteke je opuščeno v
    Symfony 2.2 in bo odstranjeno v Symfony 3.0.

Pisanje datotek YAML
~~~~~~~~~~~~~~~~~~~~

Metoda :method:`Symfony\\Component\\Yaml\\Dumper::dump` odloži kakršnokoli
polje PHP v njegovo predstavitev YAML:

.. code-block:: php

    use Symfony\Component\Yaml\Dumper;

    $array = array(
        'foo' => 'bar',
        'bar' => array('foo' => 'bar', 'bar' => 'baz'),
    );

    $dumper = new Dumper();

    $yaml = $dumper->dump($array);

    file_put_contents('/path/to/file.yml', $yaml);

.. note::

    Seveda, Symfony2 YAML odložilnik (dumper) ni sposoben odložiti virov. Tudi
    če je odložilnik sposoben odložiti objekte PHP, se smatra, da je to
    nepodprta lastnost.

Če pride do kakršnekoli napake med odlaganjem, razčlenjevalnik vrže
izjemo :class:`Symfony\\Component\\Yaml\\Exception\\DumpException`.

Če samo potrebujete odložiti eno polje, lahko uporabite
bližnjico statične metode :method:`Symfony\\Component\\Yaml\\Yaml::dump`:

.. code-block:: php

    use Symfony\Component\Yaml\Yaml;

    $yaml = Yaml::dump($array, $inline);

Format YAML podpira dve vrsti predstavitve za polja, razširjeno
in medvrstično. Privzeto, odložilnik uporablja medvrstično
predstavitev:

.. code-block:: yaml

    { foo: bar, bar: { foo: bar, bar: baz } }

Drugi argument metode :method:`Symfony\\Component\\Yaml\\Dumper::dump`
prilagodi nivo na katerem izpis prestavlja iz razširjene
predstavitve na medvrstično:

.. code-block:: php

    echo $dumper->dump($array, 1);

.. code-block:: yaml

    foo: bar
    bar: { foo: bar, bar: baz }

.. code-block:: php

    echo $dumper->dump($array, 2);

.. code-block:: yaml

    foo: bar
    bar:
        foo: bar
        bar: baz

.. _YAML: http://yaml.org/
.. _Packagist: https://packagist.org/packages/symfony/yaml
