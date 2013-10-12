.. index::
   single: Class Loader; PSR-0 Class Loader

PSR-0 Class Loader
==================

Če vaši razredi in tretje-osebne knjižnice sledijo standardu `PSR-0`_
lahko uporabite razred :class:`Symfony\\Component\\ClassLoader\\ClassLoader`,
da naložite vse vaše projektne razrede.

.. tip::

    Lahko uporabite tako ``ApcClassLoader`` in ``XcacheClassLoader``, da
    :doc:`predpomni </components/class_loader/cache_class_loader>` ``ClassLoader``
    instanco ali ``DebugClassLoader`` za :doc:`razhroščevanje </components/class_loader/debug_class_loader>`
    le tega.

Uporaba
-------

Registracija avtomatskega nalagalnika :class:`Symfony\\Component\\ClassLoader\\ClassLoader`
je enostavna::

    require_once '/path/to/src/Symfony/Component/ClassLoader/ClassLoader.php';

    use Symfony\Component\ClassLoader\ClassLoader;

    $loader = new ClassLoader();

    // to enable searching the include path (eg. for PEAR packages)
    $loader->useIncludePath(true);

    // ... register namespaces and prefixes here - see below

    $loader->register();

.. note::

    Avtomatski nalagalnik je avtomatsko registriran v Symfony2 aplikaciji
    (glejte ``app/autoload.php``).

Uporabite :method:`Symfony\\Component\\ClassLoader\\ClassLoader::addPrefix` ali
:method:`Symfony\\Component\\ClassLoader\\ClassLoader::addPrefixes` metodi za
registracijo vaših razredov::

    // register a single namespaces
    $loader->addPrefix('Symfony', __DIR__.'/vendor/symfony/symfony/src');

    // register several namespaces at once
    $loader->addPrefixes(array(
        'Symfony' => __DIR__.'/../vendor/symfony/symfony/src',
        'Monolog' => __DIR__.'/../vendor/monolog/monolog/src',
    ));

    // register a prefix for a class following the PEAR naming conventions
    $loader->addPrefix('Twig_', __DIR__.'/vendor/twig/twig/lib');

    $loader->addPrefixes(array(
        'Swift_' => __DIR__.'/vendor/swiftmailer/swiftmailer/lib/classes',
        'Twig_'  => __DIR__.'/vendor/twig/twig/lib',
    ));

Razredi iz pod-imenskega prostora ali pod-hierarhičnih `PEAR`_ razredov se lahko
najdejo v seznamu lokacij za enostavnejše izdelovanje pod-skupkov razredov za večje
projekte::

    $loader->addPrefixes(array(
        'Doctrine\\Common'           => __DIR__.'/vendor/doctrine/common/lib',
        'Doctrine\\DBAL\\Migrations' => __DIR__.'/vendor/doctrine/migrations/lib',
        'Doctrine\\DBAL'             => __DIR__.'/vendor/doctrine/dbal/lib',
        'Doctrine'                   => __DIR__.'/vendor/doctrine/orm/lib',
    ));

V tem primeru, če poskusite uporabiti razred v imenskem prostoru ``Doctrine\Common``
ali enem od njegovih otrok, bo avtomatski nalagalnik najprej pogledal za razred pod
direktorijem ``doctrine-common``. Če ni najdem, bo potem vrnjen na privzeti
direktorij ``Doctrine`` (zadnji, ki je nastavljen) preden odneha. Vrstni red
registracije predpon je pomemben v tem primeru.

.. _PEAR:  http://pear.php.net/manual/en/standards.naming.php
.. _PSR-0: http://symfony.com/PSR0
