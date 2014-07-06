.. index::
   single: ClassLoader; PSR-4 Class Loader

PSR-4 Class Loader
==================

.. versionadded:: 2.5
    :class:`Symfony\\Component\\ClassLoader\\Psr4ClassLoader` je bil
    predstavljen v Symfony 2.5.

Knjižnice, ki sledijo standardu `PSR-4`_ so lahko naložene s ``Psr4ClassLoader``.

.. note::

    Če upravljate vaše odvisnosti preko Composer-ja, dobite PSR-4 kompatibilen
    avtomatski nalagalnik delujoč iz škatle. Uporabite ta nalagalnik v okoljih, kjer Composer
    ni na voljo.

.. tip::

    Vse komponente Symfony sledijo PSR-4.

Uporaba
-------

Sledeči primer demonstrira, kako lahko uporabite
avtomatski nalagalnik :class:`Symfony\\Component\\ClassLoader\\Psr4ClassLoader`, da uporablja
komponento Yaml kot ZIP pakete in jih razpakira v direktorij ``libs``.
Struktura direktorijev bo izgledala takole:

.. code-block:: text

    libs/
        ClassLoader/
            Psr4ClassLoader.php
            ...
        Yaml/
            Yaml.php
            ...
    config.yml
    demo.php

V ``demo.php`` boste razčlenili datoteko ``config.yml``. Da to naredite, morate
najprej nastaviti ``Psr4ClassLoader``:

.. code-block:: php

    use Symfony\Component\ClassLoader\Psr4ClassLoader;
    use Symfony\Component\Yaml\Yaml;

    require __DIR__.'/lib/ClassLoader/Psr4ClassLoader.php';

    $loader = new Psr4ClassLoader();
    $loader->addPrefix('Symfony\\Component\\Yaml\\', __DIR__.'/lib/Yaml');
    $loader->register();

    $data = Yaml::parse(__DIR__.'/config.yml');

Najprej, class loader je naložen ročno z uporabo ``require``
stavka, saj trenutno še ni nobenega mehanizma avtomatskega nalaganja. S
klicem :method:`Symfony\\Component\\ClassLoader\\Psr4ClassLoader::addPrefix`
poveste class loader-ju, kje naj išče razrede s
predpono imenskega prostora ``Symfony\Component\Yaml\``. Po registraciji avtomatskega nalagalnika
je komponenta Yaml pripravljena za uporabo.

.. _PSR-4: http://www.php-fig.org/psr/psr-4/
