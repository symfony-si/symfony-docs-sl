.. index::
    single: Templating Helpers; Slots Helper

Pomočniki rež
=============

Bolj pogosto kot ne, predloge v projektu delijo skupne elemente, kot
dobro znane glava in noga. Z uporabo tega pomočnika je statična koda HTML lahko
postavljena v postavitveno datoteko skupaj s t.i. režami (slots), ki predstavljajo dinamične
dele, ki se bodo spremenili na osnovi stran-po-stran. Te reže so nato zapolnjene
z različnimi otroškimi predlogami. Z drugimi besedami postavitvena datoteka polepša
otroško predlogo.

Prikaz rež
----------

Te reže so dostopne z uporabo pomočnika rež (``$view['slots']``). Uporabite
:method:`Symfony\\Component\\Templating\\Helper\\SlotsHelper::output`, da
prikažete vsebino reže na tem mestu:

.. code-block:: html+php

    <!-- views/layout.php -->
    <!doctype html>
    <html>
        <head>
            <title>
                <?php $view['slots']->output('title', 'Default title') ?>
            </title>
        </head>
        <body>
            <?php $view['slots']->output('_content') ?>
        </body>
    </html>

Prvi argument metode je ime reže. Metoda ima
opcijski drugi argument, ki je privzeta vrednost za uporabo, če reža ni
na voljo.

Reža ``_content`` je posebna reža nastavljena s ``PhpEngine``. Vsebuje
vsebino podpredloge.

.. caution::

    Če uporabljate samostojno komponento, zagotovite, da ste registrirali
    :class:`Symfony\\Component\\Templating\\Helper\\SlotsHelper`::

        use Symfony\Component\Templating\Helper\SlotsHelper;

        // ...
        $templateEngine->set(new SlotsHelper());

Razširitev predlog
------------------

Metoda :method:`Symfony\\Component\\Templating\\PhpEngine::extend` je klicana v
pod-predlogi, da nastavi njeno starševsko predlogo. Nato
je :method:`$view['slots']->set() <Symfony\\Component\\Translation\\Helper\\SlotsHelper::set>`
lahko uporabljena, da nastavi vsebino reže. Vsa vsebina, ki ni eksplicitno
nastavljena v reži je reža ``_content``.

.. code-block:: html+php

    <!-- views/page.php -->
    <?php $view->extend('layout.php') ?>

    <?php $view['slots']->set('title', $page->title) ?>

    <h1>
        <?php echo $page->title ?>
    </h1>
    <p>
        <?php echo $page->body ?>
    </p>

.. note::

    Možno je več nivojev dedovanja: postavitev lahko razširi drugo
    postavitev.

Za velike reže je na voljo tudi razširjena sintaksa:

.. code-block:: html+php

    <?php $view['slots']->start('title') ?>
        Some large amount of HTML
    <?php $view['slots']->stop() ?>
