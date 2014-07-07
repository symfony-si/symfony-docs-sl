.. index::
   single: Debug
   single: Components; Debug

Komponenta Debug
================

    Komponenta Debug ponuja orodja za poenostavitev razhroščevanja kode PHP.

.. versionadded:: 2.3
    Komponenta Debug je bila predstavljena v Symfony 2.3. Predtem so bili razredi
    licirani v komponenti HttpKernel.

Namestitev
----------

Komponento lahko namestite na različne načine:

* Uporabite uradni Git repozitorij (https://github.com/symfony/Debug);
* :doc:`Namestite jo preko Composer-ja </components/using_components>` (``symfony/debug`` na `Packagist`_).

Uporaba
-------

Komponenta Debug ponuja nekaj orodij, ki vam pomagajo razhroščevati kodo PHP.
Omogočiti vsa je najenostavnejše kot gre::

    use Symfony\Component\Debug\Debug;

    Debug::enable();

Metoda :method:`Symfony\\Component\\Debug\\Debug::enable` registrira
hendler napak, hendler izjem in
:doc:`posebni nalagalnik razredov </components/debug/class_loader>`.

Preberite sledeče sekcije za več informacij o različnih orodjih
na voljo.

.. caution::

    Nikoli ne bi smeli omogočiti razhroščevalnih orodij v produkcijskem okolju, saj
    lahko razkrijejo občutljive informacije uporabniku.

Omogočanje handlerja napak
--------------------------

Razred :class:`Symfony\\Component\\Debug\\ErrorHandler` ujame napake PHP
in jih spremeni v izjeme (razreda :phpclass:`ErrorException` ali
:class:`Symfony\\Component\\Debug\\Exception\\FatalErrorException` za PHP
kritične napake)::

    use Symfony\Component\Debug\ErrorHandler;

    ErrorHandler::register();

Omogočanje hendlerja izjem
--------------------------

Razred :class:`Symfony\\Component\\Debug\\ExceptionHandler` ujame
neujete izjeme PHP in jih pretvori v lepe odzive PHP. Je uporaben
v razhroščevalnem načinu za zamenjavo privzetega PHP/XDebug izpisa z nekaj lepšega
in bolj uporabnega::

    use Symfony\Component\Debug\ExceptionHandler;

    ExceptionHandler::register();

.. note::

    Če je :doc:`komponenta HttpFoundation </components/http_foundation/introduction>`
    na voljo, hendler uporabi objekt Symfony Response; drugače pade
    nazaj na splošni PHP odziv.

.. _Packagist: https://packagist.org/packages/symfony/debug
