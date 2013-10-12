.. index::
    single: Class Loader; MapClassLoader
    
MapClassLoader
==============

Razred :class:`Symfony\\Component\\ClassLoader\\MapClassLoader` vam omogoča
da avtomatsko nalagate datoteke preko statičnega zemljevida iz razredov v datoteke.
To je uporabno, če uporabljate tretje-osebne knjižnice, ki ne sledijo `PSR-0` standardom
in tako ne morejo uporabljati :doc:`PSR-0 nalagalnika razredov </components/class_loader/class_loader>`.

``MapClassLoader`` je lahko uporabljen skupaj z :doc:`PSR-0 nalagalnikom razredov </components/class_loader/class_loader>`
z nastavljanjem in klicanjem ``register()`` metode na obeh.

.. note::

    Privzeto obnašanje je pripenjanje ``MapClassLoader`` na autoload
    skladovnico. Če ga želite uporabiti kot prvi avtomatski nalagalnik, pošljite ``true`` ko
    kličete metodo ``register()``. Vaš nalagalnik razredov bo potem pripet
    na autoload sklad.

Uporaba
-------

Uporaba je tako enostavna kot je pošiljanje vaših povezav njegovim konstruktorjem,
ko se izdela instanca razreda ``MapClassLoader``::

    require_once '/path/to/src/Symfony/Component/ClassLoader/MapClassLoader';
    
    $mapping = array(
        'Foo' => '/path/to/Foo',
        'Bar' => '/path/to/Bar',
    );
    
    $loader = new MapClassLoader($mapping);
    
    $loader->register();

.. _PSR-0: http://symfony.com/PSR0
