.. index::
    single: Class Loader; DebugClassLoader
    
Razhroščevanje komponente Class Loader
======================================

:class:`Symfony\\Component\\ClassLoader\\DebugClassLoader` poskuša
vrniti več pomagalnih izjem, ko razred ni najden v registriranih
avtomatskih nalagalnikih. Vsi avtomatski nalagalniki, ki implementirajo
metodo ``findFile()`` so zamenjani z ``DebugClassLoader`` ovojem.

Uporaba ``DebugClassLoader`` je tako enostavna kot klicanje njene statične
metode :method:`Symfony\\Component\\ClassLoader\\DebugClassLoader::enable`::

    use Symfony\Component\ClassLoader\DebugClassLoader;
    
    DebugClassLoader::enable();
