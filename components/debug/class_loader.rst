.. index::
    single: Class Loader; DebugClassLoader
    single: Debug; DebugClassLoader

Razhroščevanje Class Loader-ja
==============================

.. versionadded:: 2.4
    ``DebugClassLoader`` komponente Debug je bil predstavljen v Symfony 2.4.
    Pred tem je bil lociran v komponenti ClassLoader.

:class:`Symfony\\Component\\Debug\\DebugClassLoader` poskuša
vreči bolj pomagalne izjeme, ko razred ni najden v registrianih
avtomatskih nalagalnikih. Vsi avtomatski nalagalniki, ki implementirajo metodo ``findFile()``, so zamenjani
z ovitjem ``DebugClassLoader``.

Uporaba ``DebugClassLoader`` je tako enostavna kot klic njene statične
metode :method:`Symfony\\Component\\Debug\\DebugClassLoader::enable`::

    use Symfony\Component\ClassLoader\DebugClassLoader;

    DebugClassLoader::enable();
