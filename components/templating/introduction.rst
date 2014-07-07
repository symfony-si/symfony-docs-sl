.. index::
   single: Templating
   single: Components; Templating

Komponenta Templating
=====================

    Komponenta Templating ponuja vsa orodja potrebna za gradnjo kakršnegakoli
    sistema predlog.

    Ponuja infrastrukturo za nalaganje datotek predlo in jih opcijsko
    nadzira za spremembami. Ponuja tudi konkretno implementacijo motorja predlog,
    ki uporablja PHP z dodatnimi orodji za spreminjanje (escaping) in ločevanje
    predlog v bloke in postavitve.

Namestitev
----------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestite jo preko Composer-ja </components/using_components>` (``symfony/templating`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Templating).

Uporaba
-------

Razred :class:`Symfony\\Component\\Templating\\PhpEngine` je vstopna točka
komponente. Potrebuje
razčlenjevalnik imen predlog (:class:`Symfony\\Component\\Templating\\TemplateNameParserInterface`)
za pretvorbo imena predloge v
sklic predloge (:class:`Symfony\\Component\\Templating\\TemplateReferenceInterface`).
Potrebuje tudi nalagalnik predlog (:class:`Symfony\\Component\\Templating\\Loader\\LoaderInterface`),
ki uporablja sklic predloge, da dejansko najde in naloži predlogo::

    use Symfony\Component\Templating\PhpEngine;
    use Symfony\Component\Templating\TemplateNameParser;
    use Symfony\Component\Templating\Loader\FilesystemLoader;

    $loader = new FilesystemLoader(__DIR__.'/views/%name%');

    $templating = new PhpEngine(new TemplateNameParser(), $loader);

    echo $templating->render('hello.php', array('firstname' => 'Fabien'));

.. code-block:: html+php

    <!-- views/hello.php -->
    Hello, <?php echo $firstname ?>!

Metoda :method:`Symfony\\Component\\Templating\\PhpEngine::render` razčleni
datoteko ``views/hello.php`` in vrne izhodni tekst. Drugi argument
za ``render`` je polje spremenljivk, ki jih uporabljate v predlogi. V tem
primeru bo rezultat ``Hello, Fabien!``.

.. note::

    Predloge bodo predpomnjene v spominu motorja. To pomeni, da če
    izpišete enako predlogo večkrat v istem zahtevku, bo
    predloga naložena samo enkrat iz datotečnega sistema.

Spremenljivka ``$view``
-----------------------

V vseh predlogah razčlenjenih s ``PhpEngine`` dobite dostop do skrivnostne
spremenljivke imenovane ``$view``. Ta spremenljivka vsebuje trenutno instanco ``PhpEngine``.
To pomeni, da dobite dostop do veliko metod, ki naredijo vaše življenje
enostavnejše.

Vključevanje predlog
--------------------

Najboljši način za deljenje dela kode predloge je izdelava predloge, ki
je lahko nato vključena v druge predloge. Kot spremenljivka ``$view`` je
instanca od ``PhpEngine``, lahko uporabite metodo ``render`` (ki je bila uporabljena
za izpis predloge originalno) znotraj predloge za izpis druge predloge::

    <?php $names = array('Fabien', ...) ?>
    <?php foreach ($names as $name) : ?>
        <?php echo $view->render('hello.php', array('firstname' => $name)) ?>
    <?php endforeach ?>

Globalne spremenljivke
----------------------

Včasih morate nastaviti spremenljivko, ki je na voljo v vseh predlogah
izpisanih s strani motorja (kot spremenljivka ``$app``, ko uporabljate ogrodje Symfony2).
Te spremenljivke so lahko nastavljene z uporabo
metode :method:`Symfony\\Component\\Templating\\PhpEngine::addGlobal` in so
lahko dostopane v predlogi kot običajne spremenljivke::

    $templating->addGlobal('ga_tracking', 'UA-xxxxx-x');

V predlogi:

.. code-block:: html+php

    <p>The google tracking code is: <?php echo $ga_tracking ?></p>

.. caution::

    Globalne spremenljivke ne morejo biti imenovane ``this`` ali ``view``, saj so
    že uporabljene v PHP motorju.

.. note::

    Globalne spremenljivke so lahko prepisane z lokalnimi spremenljivkami v predlogi
    z enakim imenom.

Spreminjanje izpisa
-------------------

Ko izpisujete spremenljibke, bi jih verjetno morali spremeniti (escaping), tako da HTML ali
JavaScript koda ni izpisana na vašo stran. To se bo izognilo stvarem kot so
XSS napadi. Da to naredite, uporabite
metodo :method:`Symfony\\Component\\Templating\\PhpEngine::escape`::

    <?php echo $view->escape($firstname) ?>

Privzeto metoda ``escape()`` predpostavlja, da je spremenljivka izpisana
znotraj konteksta HTML. Drugi argument vam omogoča spremeniti kontekst. Na
primer za izpis nečesa znotraj JavaScript, uporabite kontekst ``js``::

    <?php echo $view->escape($var, 'js') ?>

Komponenta prihaja s HTML in JS escaper-jem. Lahko registrirate vaš lasten
escaper z uporabo
metode :method:`Symfony\\Component\\Templating\\PhpEngine::setEscaper`::

    $templating->setEscaper('css', function ($value) {
        // ... all CSS escaping

        return $escapedValue;
    });

Pomočniki
---------

Komponenta Templating je lahko enostavno razširjena preko pomočnikov. Komponenta ima
2 vgrajena pomočnika:

* :doc:`/components/templating/helpers/assetshelper`
* :doc:`/components/templating/helpers/slotshelper`

Preden lahko te pomočnike uporabite, jih morate registrirati z uporabo
:method:`Symfony\\Component\\Templating\\PhpEngine::set`::

    use Symfony\Component\Templating\Helper\AssetsHelper;
    // ...

    $templating->set(new AssetsHelper());

Pomočniki po meri
~~~~~~~~~~~~~~~~~

Ustvarite lahko vaše lastne pomočnike z izdelavo razreda, ki implementira
:class:`Symfony\\Component\\Templating\\Helper\\HelperInterface`. Vendar
večino časa boste razširjali
:class:`Symfony\\Component\\Templating\\Helper\\Helper`.

``Helper`` ima eno zahtevano metodo:
:method:`Symfony\\Component\\Templating\\Helper\\HelperInterface::getName`.
To je ime, ki je uporabljeno za dobiti pomočnika iz objekta ``$view``.

Izdelava motorja po meri
------------------------

Poleg ponujanja PHP motorja predlog, lahko tudi ustvarite vaš lastni motor
z uporabo komponente Templating. Da to naredite, ustvarite nov razred, ki
implementira :class:`Symfony\\Component\\Templating\\EngineInterface`. Ta
zahteva 3 metode:

* :method:`render($name, array $parameters = array()) <Symfony\\Component\\Templating\\EngineInterface::render>`
  - Izpiše predlogo
* :method:`exists($name) <Symfony\\Component\\Templating\\EngineInterface::exists>`
  - Preveri, če predloga obstaja
* :method:`supports($name) <Symfony\\Component\\Templating\\EngineInterface::supports>`
  - Preveri, če je dana predloga lahko upravljana s tem motorjem.

Uporaba večih motorjev
----------------------

Možno je uporabiti več motorjev istočasno z uporabo
razreda :class:`Symfony\\Component\\Templating\\DelegatingEngine`. Ta razred
vzame seznam motorjev in deluje samo kot običajni motor predlog. Edina
razlika je, da delegira klice k enemu od drugih motorjev. Da
izberete katerega uporabiti za predlogo, je
uporabljena metoda
:method:`EngineInterface::supports() <Symfony\\Component\\Templating\\EngineInterface::supports>`

.. code-block:: php

    use Acme\Templating\CustomEngine;
    use Symfony\Component\Templating\PhpEngine;
    use Symfony\Component\Templating\DelegatingEngine;

    $templating = new DelegatingEngine(array(
        new PhpEngine(...),
        new CustomEngine(...)
    ));

.. _Packagist: https://packagist.org/packages/symfony/templating
