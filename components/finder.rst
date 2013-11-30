.. index::
   single: Finder
   single: Components; Finder

Komponenta Finder
=================

   Komponenta Finder najde datoteke in direktorije preko intiutivnega tekočega
   vmesnika.

Namestitev
----------

Lahko namestite komponento na 2 različna načina:

* :doc:`Namestitev preko Composer-ja </components/using_components>` (``symfony/finder`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Finder).

Uporaba
-------

Razred :class:`Symfony\\Component\\Finder\\Finder` najde datoteke in/ali
direktorije::

    use Symfony\Component\Finder\Finder;

    $finder = new Finder();
    $finder->files()->in(__DIR__);

    foreach ($finder as $file) {
        // Print the absolute path
        print $file->getRealpath()."\n";

        // Print the relative path to the file, omitting the filename
        print $file->getRelativePath()."\n";

        // Print the relative path to the file
        print $file->getRelativePathname()."\n";
    }

``$file`` je instanca :class:`Symfony\\Component\\Finder\\SplFileInfo`,
ki razširi :phpclass:`SplFileInfo`, da ponudi metode za delo z relativnimi
potmi.

Zgornja koda izpiše imena vseh datotek v trenutnem direktoriju
rekurzivno. Finder razred uporablja tekoči vmesnik, da vse metode vrnejo
intanco Finder-ja.

.. tip::

    Finder instanca je PHP :phpclass:`Iterator`. Torej namesto iteracije skozi
    Finder s ``foreach``, ga lahko tudi pretvorite v polje z metodo
    :phpfunction:`iterator_to_array`, ali dobite število elementov z
    :phpfunction:`iterator_count`.

.. caution::

    Ko iščete skozi več lokacij podanih metodi
    :method:`Symfony\\Component\\Finder\\Finder::in`, je ustvarjen ločen iterator
    interno za vsako lokacijo. To pomeni, da imamo več skupkov rezultatov
    združenih v enega.
    Ker :phpfunction:`iterator_to_array` privzeto uporablja ključe skupkov rezultatov,
    ko pretvarjamo v polje, so lahko nekateri ključi podvojeni in njihove vrednosti
    prepisane. Temu se lahko izognemo s podajanjem ``false`` kot drugi parameter
    :phpfunction:`iterator_to_array`.

Kriteriji
---------

Na voljo je veliko načinov za filtriranje in urejanje vaših rezultatov.

Lokacija
~~~~~~~~

Lokacija je edini obvezni kriterij. Finder-ju pove, kateri
direktorij uporabiti za iskanje::

    $finder->in(__DIR__);

Iščite v večih lokacijah z veriženjem klicev metode
:method:`Symfony\\Component\\Finder\\Finder::in`::

    $finder->files()->in(__DIR__)->in('/elsewhere');

.. versionadded:: 2.2
   Podpora za nadomestne znake je bila dodana v verziji 2.2.

Uporabite nadomestne znake za iskanje v direktorijih, ki se ujemao vzorcu::

    $finder->in('src/Symfony/*/*/Resources');

Vsak vzorec mora biti razrešen na vsaj eno pot direktorija.

Izključite direktorije iz ujemanja z metodo
:method:`Symfony\\Component\\Finder\\Finder::exclude`::

    $finder->in(__DIR__)->exclude('ruby');

.. versionadded:: 2.3
   Metoda :method:`Symfony\\Component\\Finder\\Finder::ignoreUnreadableDirs`
   je bila dodana v Symfony 2.3.

Je tudi možno ignorirati direktorije, za katere nimate pravic za branje::

    $finder->ignoreUnreadableDirs()->in(__DIR__);

Ker Finder uporablja PHP iteratorje, lahko podate katerikoli URL s podprtim
`protokolom`_::

    $finder->in('ftp://example.com/pub/');

In tudi deluje z uporabniško definiranimi tokovi::

    use Symfony\Component\Finder\Finder;

    $s3 = new \Zend_Service_Amazon_S3($key, $secret);
    $s3->registerStreamWrapper("s3");

    $finder = new Finder();
    $finder->name('photos*')->size('< 100K')->date('since 1 hour ago');
    foreach ($finder->in('s3://bucket-name') as $file) {
        // ... do something

        print $file->getFilename()."\n";
    }

.. note::

    Preberite `Streams`_ dokumentacijo, da izvedete več, kako narediti vaše lastne tokove.

Datoteke in direktoriji
~~~~~~~~~~~~~~~~~~~~~~~

Privzeto Finder vrne datoteke in direktorije; vendar
:method:`Symfony\\Component\\Finder\\Finder::files` in
:method:`Symfony\\Component\\Finder\\Finder::directories` metodi to krmilita::

    $finder->files();

    $finder->directories();

Če želite slediti povezavam, uporabite ``followLinks()`` metodo::

    $finder->files()->followLinks();

Privzeto iterator ignorira popularne VCS datoteke. To se lahko spremeni z
metodo ``ignoreVCS()``::

    $finder->ignoreVCS(false);

Urejanje
~~~~~~~~

Uredite rezultat po imenu ali tipu (najprej direktoriji nato datoteke)::

    $finder->sortByName();

    $finder->sortByType();

.. note::

    Bodite pozorni, ker ``sort*`` metode potrebujejo dobiti vse elemente, ki se ujemajo, da
    opravijo svojo nalogo. Za velike iteratorje je počasno.

Lahko tudi definirate vaš lastni urejevalni algoritem z metodo ``sort()``::

    $sort = function (\SplFileInfo $a, \SplFileInfo $b)
    {
        return strcmp($a->getRealpath(), $b->getRealpath());
    };

    $finder->sort($sort);

Ime datoteke
~~~~~~~~~~~~

Omejite datoteke po imenu z metodo
:method:`Symfony\\Component\\Finder\\Finder::name`::

    $finder->files()->name('*.php');

Metoda ``name()`` sprejema t.i. glob-e, nize ali regularne izraze::

    $finder->files()->name('/\.php$/');

Metoda ``notName()`` izključuje datoteke, ki se ujemajo vzorcu::

    $finder->files()->notName('*.rb');

Vsebina datoteke
~~~~~~~~~~~~~~~~

Omejite datoteke po vsebini z metodo
:method:`Symfony\\Component\\Finder\\Finder::contains`::

    $finder->files()->contains('lorem ipsum');

Metoda ``contains()`` sprejema nize ali regularne izraze::

    $finder->files()->contains('/lorem\s+ipsum$/i');

Metoda ``notContains()`` izključuje datoteke, ki vsebujejo dani vzorec::

    $finder->files()->notContains('dolor sit amet');

Pot
~~~

.. versionadded:: 2.2
   Metodi ``path()`` in ``notPath()`` sta bili dodani v verziji 2.2.

Omejite datoteke in direktorije glede na pot z metodo
:method:`Symfony\\Component\\Finder\\Finder::path`::

    $finder->path('some/special/dir');

Na vseh platformah bi moral biti uporabljena poševnica (t.j. ``/``) kot ločilo direktorijev.

Metoda ``path()`` sprejema niz ali regularni izraz::

    $finder->path('foo/bar');
    $finder->path('/^foo\/bar/');

Interno so nizi spremenjeni v regularne izraze z zatekanjem poševnic
in dodajanjem ločil:

.. code-block:: text

    dirname    ===>    /dirname/
    a/b/c      ===>    /a\/b\/c/

Metoda :method:`Symfony\\Component\\Finder\\Finder::notPath` izključuje datoteke glede na pot::

    $finder->notPath('other/dir');

Velikost datoteke
~~~~~~~~~~~~~~~~~

Omejite datoteke glede na velikost z metodo
:method:`Symfony\\Component\\Finder\\Finder::size`::

    $finder->files()->size('< 1.5K');

Omejite glede na območje velikosti z veriženjem klicov::

    $finder->files()->size('>= 1K')->size('<= 2K');

Primerjalni operator je lahko katerikoli izmed: ``>``, ``>=``, ``<``, ``<=``,
``==``, ``!=``.

Ciljna vrednost lahko uporablja obsege kilobajtov (``k``, ``ki``), megabajtov
(``m``, ``mi``), ali gigabajtov (``g``, ``gi``). Tisti, ki imajo predpono ``i``, uporabljajo
ustrezne ``2**n`` verzije glede na `IEC standard`_.

Datum datoteke
~~~~~~~~~~~~~~

Omejite datoteke glede na zadnje spremenjene datume z metodo
:method:`Symfony\\Component\\Finder\\Finder::date`::

    $finder->date('since yesterday');

Primerjalni operator je lahko katerikoli izmed sledečih: ``>``, ``>=``, ``<``, '<=',
'=='. Lahko tudi uporabite ``since`` ali ``after`` kot alias za ``>`` in
``until`` ali ``before`` kot alias za ``<``.

Ta ciljna vrednost je lahko katerikoli datum podprt od funkcije `strtotime`_.

Globina direktorija
~~~~~~~~~~~~~~~~~~~

Privzeto Finder rekurzivno prečka direktorije. Omejite globino
prečkanja z metodo :method:`Symfony\\Component\\Finder\\Finder::depth`::

    $finder->depth('== 0');
    $finder->depth('< 3');

Filtriranje po meri
~~~~~~~~~~~~~~~~~~~

Da omejite ujemanje datoteke z vašo lastno strategijo, uporabite
:method:`Symfony\\Component\\Finder\\Finder::filter`::

    $filter = function (\SplFileInfo $file)
    {
        if (strlen($file) > 10) {
            return false;
        }
    };

    $finder->files()->filter($filter);

Metoda ``filter()`` sprejema zaprtje (Closure) kot argument. Za vsako datoteko, ki se ujema,
je klicana z datoteko kot :class:`Symfony\\Component\\Finder\\SplFileInfo`
instanca. Datoteka je izključena iz skupka rezultatov, če zaprtje vrne
``false``.

Branje vsebine vrnjenih datotek
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vsebine vrnjenih datotek se lahko prebere z
:method:`Symfony\\Component\\Finder\\SplFileInfo::getContents`::

    use Symfony\Component\Finder\Finder;

    $finder = new Finder();
    $finder->files()->in(__DIR__);

    foreach ($finder as $file) {
        $contents = $file->getContents();
        ...
    }

.. _strtotime:    http://www.php.net/manual/en/datetime.formats.php
.. _protokolom:   http://www.php.net/manual/en/wrappers.php
.. _Streams:      http://www.php.net/streams
.. _IEC standard: http://physics.nist.gov/cuu/Units/binary.html
.. _Packagist:    https://packagist.org/packages/symfony/finder
