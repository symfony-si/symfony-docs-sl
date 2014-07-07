.. index::
    single: Templating Helpers; Assets Helper

Pomočniki sredstev
==================

Glavni namen pomočnikov sredstev je narediti vašo aplikacijo bolj prenosljivo z
generiranjem poti sredstev:

.. code-block:: html+php

   <link href="<?php echo $view['assets']->getUrl('css/style.css') ?>" rel="stylesheet">

   <img src="<?php echo $view['assets']->getUrl('images/logo.png') ?>">

Pomočniki sredstev so lahko potem nastavljeni, da izpišejo poti v CDN ali spremenijo
poti v primeru vaših sredstev, ki se nnahajajo v pod-direktoriju vašega gostitelja (npr. ``http://example.com/app``).

Nastavitev poti
---------------

Privzeto bo pomočnik sredstev imel predpono vseh poti s poševnico. To lahko
nastavite s podajanjem osnovne poti sredstev kot prvi argument
konstruktorja::

    use Symfony\Component\Templating\Helper\AssetsHelper;

    // ...
    $templateEngine->set(new AssetsHelper('/foo/bar'));

Sedaj, če uporabljate pomočnika, bo vse imelo predpono ``/foo/bar``:

.. code-block:: html+php

   <img src="<?php echo $view['assets']->getUrl('images/logo.png') ?>">
   <!-- renders as:
   <img src="/foo/bar/images/logo.png">
   -->

Absolutni Url-ji
----------------

Lahko tudi določite URL za uporabo v drugem parametru konstruktorja::

    // ...
    $templateEngine->set(new AssetsHelper(null, 'http://cdn.example.com/'));

Sedaj so URL-ji izpisani kot ``http://cdn.example.com/images/logo.png``.

.. versionadded:: 2.5
    Absolutni URL-ji za sredstva so bili predstavljeni v Symfony 2.5.

Lahko tudi uporabite tretji argument pomočnika, da vsilite absolutni URL:

.. code-block:: html+php

   <img src="<?php echo $view['assets']->getUrl('images/logo.png', null, true) ?>">
   <!-- renders as:
   <img src="http://yourwebsite.com/foo/bar/images/logo.png">
   -->

.. note::

    Če ste že nastavili URL v konstruktorju, uporaba tretjega argumenta od
    ``getUrl`` ne bo vplivala na generirani URL.

Verzije
-------

Da se izognete predpomnenju vira po posodobitvi starega vira, lahko
uporabite verzije, ki jih povečate vsakič, ko izdate nov projekt. Verzija
je lahko specificirana v tretjem argumentu::

    // ...
    $templateEngine->set(new AssetsHelper(null, null, '328rad75'));

Sedaj bo vsak URL imel na koncu pripono  ``?328rad75``. Če želite imeti drugačen
format, lahko določite nov format v četrtem argumentu. Je niz, ki
je uporablje v :phpfunction:`sprintf`. Prvi argument je pot in
drugi je verzija. Na primer, ``%s?v=%s`` bo izpisan kot
``/images/logo.png?v=328rad75``.

.. versionadded:: 2.5
    Na zahtevo verzije URL-jev za sredstva so bile predstavljene v Symfony 2.5.

Lahko tudi generirate URL z verzijo na osnovi sredstva-za-sredstvo z uporabo
četrtega argumenta pomočnika:

.. code-block:: html+php

   <img src="<?php echo $view['assets']->getUrl('images/logo.png', null, false, '3.0') ?>">
   <!-- renders as:
   <img src="/images/logo.png?v=3.0">
   -->

Več paketov
-----------

Generiranje poti sredstev je upravljano interno s paketi. Komponenta privzeto ponuja
2 paketa:

* :class:`Symfony\\Component\\Templating\\Asset\\PathPackage`
* :class:`Symfony\\Component\\Templating\\Asset\\UrlPackage`

Lahko tudi uporabite več paketov::

    // ...
    $templateEngine->set(new AssetsHelper());

    $templateEngine->get('assets')->addPackage('images', new PathPackage('/images/'));
    $templateEngine->get('assets')->addPackage('scripts', new PathPackage('/scripts/'));

To bo nastavilo pomočnika sredstev s 3 paketi: privzeti paket, ki
je privzeto ``/`` (nastavljen s konstruktorjem), paket images, ki doda predpone
``/images/`` in paket scripts, ki doda predpone
``/scripts/``.

Če želite nastaviti drug privzeti paket, lahko uporabite
:method:`Symfony\\Component\\Templating\\Helper\\AssetsHelper::setDefaultPackage`.

Lahko specificirate kateri paket želite uporabiti v drugem argumentu od
:method:`Symfony\\Component\\Templating\\Helper\\AssetsHelper::getUrl`:

.. code-block:: html+php

    <img src="<?php echo $view['assets']->getUrl('foo.png', 'images') ?>">
    <!-- renders as:
    <img src="/images/foo.png">
    -->

Paketi po meri
--------------

Ustvarite lahko vaš lasten paket z razširitvijo
:class:`Symfony\\Component\\Templating\\Package\\Package`.
