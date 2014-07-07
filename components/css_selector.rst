.. index::
   single: CssSelector
   single: Components; CssSelector

Komponenta CssSelector
======================

    Komponenta CssSelector pretvarja CSS izbirnike v izraze XPath.

Namestitev
----------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestite jo preko Composer-ja </components/using_components>` (``symfony/css-selector`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/CssSelector).

Uporaba
-------

Zakaj uporabiti CSS izbirnike?
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko razčlenjujete HTML ali XML dokument, je daleč najmočnejša
metoda XPath.

Izrazi XPath so izjemno fleksibilni, zato je skoraj vedno
izraz XPath, ki bo našel element, ki ga potrebujete. Na žalost
lahko postanejo tudi zelo komplicirani in krivulja učenja je strma. Celo pogoste
operacije (kot je najdenje elementa z določenim razredom) lahko zahteva
dolge in nepriročne izraze.

Mnogi razvijalci -- posebno spletni razvijalci -- so bolj domači
pri uporabi CSS izbirnikov, da najdejo elemente. Kot tudi delo na stilih,
so CSS izbirniki uporabljeni v JavaScript-u s funkcijo ``querySelectorAll``
in v popularnih JavaScript knjižnicah kot je jQuery, Prototype in MooTools.

CSS izbirniki so manj močnejši kot XPath, vendar bolj enostavni za pisanje, branje
in razumevanje. Ker so manj močnejši, so lahko skoraj vsi CSS izbirniki
pretvorjeni v enakovreden XPath. Ta izraz XPath je lahko potem uporabljen
z drugimi funkcijami in razredi, ki uporabljajo XPath, da najdejo elemente v
dokumentu.

Komponenta CssSelector
~~~~~~~~~~~~~~~~~~~~~~

Edini cilj komponente je pretvorba izbirnikov CSS v njihove XPath
ekvivalente::

    use Symfony\Component\CssSelector\CssSelector;

    print CssSelector::toXPath('div.item > h4 > a');

To da sledeči izpis:

.. code-block:: text

    descendant-or-self::div[@class and contains(concat(' ',normalize-space(@class), ' '), ' item ')]/h4/a

Ta izraz lahko uporabite skupaj z, na primer, :phpclass:`DOMCPath` ali
:phpclass:`SimpleXMLElement`, da najdete elemente v dokumentu.

.. tip::

    Metoda :method:`Crawler::filter() <Symfony\\Component\\DomCrawler\\Crawler::filter>`
    uporablja komponento CssSelector, da najde elemente na osnovi niza CSS izbirnika.
    Glejte :doc:`/components/dom_crawler` za več podrobnosti.

Omejitve komponente CssSelector
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vsi izbirniki CSS ne morejo biti pretvorjeni v XPath ekvivalente.

Na voljo je nekaj izbirnikov CSS, ki imajo smisel samo v kontekstu
spletnega brskalnika.

* izbirniki link-state: ``:link``, ``:visited``, ``:target``
* izbirniki na osnovi akcije uporabnika: ``:hover``, ``:focus``, ``:active``
* izbirniki UI-state: ``:invalid``, ``:indeterminate`` (vendar, ``:enabled``, 
  ``:disabled``, ``:checked`` in ``:unchecked`` so na voljo)

Psevdo elementi (``:before``, ``:after``, ``:first-line``,
``:first-letter``) niso podprti, ker izbirajo dele tekstov,
namesto elementov.

Nekaj psevdo-razredov še ni podprtih:

* ``*:first-of-type``, ``*:last-of-type``, ``*:nth-of-type``,
  ``*:nth-last-of-type``, ``*:only-of-type``. (Te delujejo z imenom
  elementa (npr. ``li:first-of-type``) vendar ne z ``*``.

.. _Packagist: https://packagist.org/packages/symfony/css-selector
