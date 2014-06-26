.. index::
   single: Stable API

Symfony2 stabilni API
=====================

Symfony2 stabilni API je podskupek vseh Symfony2 objavljenih javnih metod
(komponent in paket jedra), ki imajo skupne sledeče lastnosti:

* Imenski prostor in ime razreda se ne bosta spremenila;
* Ime metode se ne bo spremenilo;
* Podpis metode (argumenti in tip vrnjenene vrednosti) se ne bodo spremenili;
* Semantika kaj metoda naredi se ne bo spremenila.

Čeprav sama implementacija se lahko spremeni. Edini veljaven primer za spremembo
v stabilnem API-ju je vrstni red za popravek varnostne težave.

Stabilni API je osnovan na ustreznem seznamu, označenem z `@api`. Zato
vse, kar ni označeno eksplicitno ni del stabilnega API-ja.

.. tip::

   Read more about the stable API in :doc:`/contributing/code/bc`.

.. tip::

    Katerekoli tretje osebni paketi bi tudi morali objaviti svoj lastni stabilni API.

Od zadnje stabilne izdaje Symfony imajo sledeče komponente
javno označen API:

* BrowserKit
* ClassLoader
* Console
* CssSelector
* DependencyInjection
* DomCrawler
* EventDispatcher
* Filesystem
* Finder
* HttpFoundation
* HttpKernel
* Process
* Routing
* Templating
* Translation
* Validator
* Yaml
