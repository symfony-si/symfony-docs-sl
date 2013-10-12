.. index::
    single: APC; ApcClassLoader
    single: Class Loader; ApcClassLoader
    single: Class Loader; Cache
    single: Class Loader; XcacheClassLoader
    single: XCache; XcacheClassLoader
    
Predpomnenje nalagalnika razredov
=================================

Uvod
----

Najti datoteko za določen razred je lahko zahtevno opravilo. Na srečo
komponenta Class Loader prihaja z dvema razredoma za predpomnenje ujemanja
iz razreda v njegovo vsebujočo datoteko.
:class:`Symfonfy\\Component\\ClassLoader\\ApcClassLoader`
in :class:`Symfony\\Component\\ClassLoader\\XcacheClassLoader` se ovijata
okrog objekta, ki implementira metodo ``findFile()``, ki najde datoteko za
razred.

.. note::

  Oba, ``ApcClassLoader`` in ``XcacheClassLoader`` sta lahko uporabljena
  za predpomnenje Composer-jevega `autoloader-ja`_.

ApcClassLoader
--------------

``ApcClassLoader`` ovija obstoječi nalagalnik razredov in predpomni klice k njegovi
metodi ``findFile()`` z uporabo `APC`_::

    require_once '/path/to/src/Symfony/Component/ClassLoader/ApcClassLoader.php';
    
    // instance of a class that implements a findFile() method, like the ClassLoader
    $loader = ...;
    
    // my_prefix is the APC namespace prefix to use
    $cachedLoader = new ApcClassLoader('my_prefix', $loader);
    
    // register the cached class loader
    $cachedLoader->register();
    
    // deactivate the original, non-cached loader if it was registered previously
    $loader->unregister();

XcacheClassLoader
-----------------

``XcacheClassLoader`` uporablja `XCache`_ za predpomnenje nalagalnika razredov. Registracija
je enostavna::

    require_once '/path/to/src/Symfony/Component/ClassLoader/XcacheClassLoader.php';
    
    // instance of a class that implements a findFile() method, like the ClassLoader
    $loader = ...;
    
    // my_prefix is the XCache namespace
    $cachedLoader = new XcacheClassLoader('my_prefix', $loader);
    
    // register the cached class loader
    $cachedLoader->register();
    
    // deactivate the original, non-cached loader if it was registered previously
    $loader->unregister();

.. _APC:        http://php.net/manual/en/book.apc.php
.. _autoloader-ja: http://getcomposer.org/doc/01-basic-usage.md#autoloading
.. _XCache:     http://xcache.lighttpd.net
