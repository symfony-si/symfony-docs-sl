.. index::
   single: Page creation

Izdelava strani v Symfony2
==========================

Izdelava nove strani v Symfony2 je enostaven proces v dveh korakih:

* *Izdelajte usmeritev*: Usmeritev definira URL (npr. ``/about``) na vašo stran
  in določa krmilnik (ki je PHP funkcija), ki bi jo moral Symfony2
  izvršiti, ko se URL prihajajočega zahtevka ujema s potjo usmeritve;

* *Izdelajte krmilnik*: Krmilnik je PHP funkcija, ki sprejme prihajajoči
  zahtevek in ga pretvori v Symfony2 ``Response`` objekt, ki je
  vrnjen uporabniku.

Ta pristop je lep, ker se ujema z načinom, kako splet deluje.
Vsaka interakcija na spletu je izvedena s HTTP zahtevkom. Naloga
vaše aplikacije je enostavno interpretacija zahtevka in vračanje ustreznega
HTTP odziva.

Symfony2 sledi tej filozofiji in vam ponuja orodja in konvencije,
da obdržite vašo aplikacijo organizirano, kot raste v uporabnikih in kompleksnosti.

.. index::
   single: Page creation; Environments & Front Controllers

.. _page-creation-environments:

Okolja & prednji krmilniki
~~~~~~~~~~~~~~~~~~~~~~~~~~

Vsaka Symfony aplikacija se poganja znotraj :term:`okolja`. Okolje
je določen skupek nastavitev in naloženih paketov, predstavljenih z nizom.
Enaka aplikacija je lahko pognana z različnimi nastavitvami s poganjanjem
aplikacije v različnih okoljih. Symfony2 prihaja s tremi definiranimi
okolji - ``dev``, ``test`` in ``prod`` - vendar lahko ustvarite tudi vaše lastno.

Okolja so uporabna, ker omogočajo eni aplikaciji, da ima dev okolje
zgrajeno za razhroščevanje in produkcijsko okolje optimizirano za hitrost. Lahko
tudi naložite določene pakete na osnovi izbranega okolja. Na primer
Symfoyn2 prihaja z WebProfileBundle (opisan spodaj), omogočen samo
v ``dev`` in ``test`` okoljih.

Symfony2 prihaja z dvema spletno dostopnima prednjima krmilnikoma: ``app_dev.php``
ponuja ``dev`` okolje in ``app.php`` ponuja ``prod`` okolje.
Vsi spletni dostopi v Symfony2 gredo običajno skozi enega od teh prednjih krmilnikov.
(Okolje ``test`` je običajno uporabljeno samo, ko poganjate teste enot in tako
nima namenskega prednjega krmilnika. Orodje konzole tudi ponuja
prednji krmilnik, ki je lahko uporabljen v kateremkoli okolju.)

Ko prednji krmilnik inicializira jedro, tudi ponuja dva parametra:
okolje in tudi ali naj bo jedro pognano v razhroščevalnem načinu.
Da naredite vašo aplikacijo hitreje odzivno, Symfony2 vzdržuje predpomnilnik pod
direktorijem ``app/cache``. Ko je omogočen način rahroščevanja (kot ga ima ``app_dev.php``
privzeto), je ta predpomnilnik avtomatsko spraznjen, kadarkoli naredite spremembe
v katerikoli kodi ali nastavitvi. Ko poganjate v razhroščevalnem načinu, se Symfony2 poganja
počasneje, vendar vaše spremembe so odražane brez, da morate ročno počistiti
predpomnilnik.

.. index::
   single: Page creation; Example

Stran "Hello Symfony!"
----------------------

Pričnite z gradnjo začetka klasične "Hello World!" aplikacije. Ko
ste končali, bo uporabnik zmožen dobiti osebni pozdrav (npr. "Hello Symfony"),
da obišče sledeči URL:

.. code-block:: text

    http://localhost/app_dev.php/hello/Symfony

Dejansko boste sposobni zamenjati ``Symfony`` s katerimkoli drugim imenom,
da vas pozdravi. Da naredite stran, sledite enostavnemu procesu dveh korakov.

.. note::

    Vodič predvideva, da ste že prenesli Symfony2 in nastavili
    vaš spletni strežnik. Zgornji URL predpostavlja, da ``localhost`` kaže
    v ``web`` direktorij vašega novega Symfony2 projekta. Za podrobne informacije
    na tem procesu, glejte dokumentacijo na spletnem strežniku, ki ga uporabljate.
    Tu je relevantna stran dokumentacije za nek spletni strežnik, ki ga morda uporabljate:

    * Za Apache HTTP strežnik, se sklicujte na `Apache DirectoryIndex dokumentacijo`_
    * Za Nginx se sklicujte na `Nginx HttpCoreModule lokacijo dokumentacije`_

Preden pričnete: Ustvarite paket
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Preden pričnete, boste morali ustvariti *paket*. V Symfoyn2 je :term:`paket`
kot vtičnik, razen da se bo vsa koda v vaši aplikacijii nahajala
znotraj paketa.

Paket ni nič več kot direktorij, ki vsebuje vse povezano
z določeno lastnostjo, vključno s PHP razredi, nastavitvami in celo stili
in JavaScript datotekami (glejte :ref:`page-creation-bundles`).

Da ustvarite paket imenovan ``AcmeHelloBundle`` (paket za igranje, ki ga boste
zgradili v tem poglavju) poženite sledeči ukaz in sledite navodilom
na zaslonu (uporabite vse privzete opcije):

.. code-block:: bash

    $ php app/console generate:bundle --namespace=Acme/HelloBundle --format=yml

V zakulisju je ustvarjen direktorij za paket v ``src/Acme/HelloBundle``.
Vrstica je tudi avtomatsko dodana v ``app/AppKernel.php`` datoteko, da
je paket registriran z jedrom::

    // app/AppKernel.php
    public function registerBundles()
    {
        $bundles = array(
            ...,
            new Acme\HelloBundle\AcmeHelloBundle(),
        );
        // ...

        return $bundles;
    }

Sedaj ko imate nastavitev paketa, lahko pričnete graditi vašo aplikacijo
znotraj paketa.

Korak 1: Izdelajte usmeritev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Privzeto datoteka nastavitev usmerjanja v Symfony2 aplikaciji je
locirana v ``app/config/routing.yml``. Kot vse nastavitve v Symfony2,
lahko tudi izberete uporabo XML ali PHP privzeto, da nastavite usmeritve.

Če pogledate glavno usmerjevalno datoteko, boste videli, da je Symfony že dodal
vnos, ko ste generirali ``AcmeHelloBundle``:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        acme_hello:
            resource: "@AcmeHelloBundle/Resources/config/routing.yml"
            prefix:   /

    .. code-block:: xml

        <!-- app/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <import resource="@AcmeHelloBundle/Resources/config/routing.xml"
                prefix="/" />
        </routes>

    .. code-block:: php

        // app/config/routing.php
        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->addCollection(
            $loader->import('@AcmeHelloBundle/Resources/config/routing.php'),
            '/'
        );

        return $collection;

Ta vnos je precej enostave: Symfony-ju pove, naj naloži nastavitve usmerjanja
iz ``Resources/config/routing.yml`` datoteke, ki živi znotraj ``AcmeHelloBundle``.
To pomeni, da ste dali nastavitve usmerjanja direktno v ``app/config/routing.yml``
ali organizirali vaše usmeritve preko vaše aplikacije in jih uvozili iz tam.

Sedaj, ko je ``routing.yml`` datoteka iz paketa uvožena, dodajte
novo usmeritev, ki definira URL strani, ki jo boste naredili:

.. configuration-block::

    .. code-block:: yaml

        # src/Acme/HelloBundle/Resources/config/routing.yml
        hello:
            path:     /hello/{name}
            defaults: { _controller: AcmeHelloBundle:Hello:index }

    .. code-block:: xml

        <!-- src/Acme/HelloBundle/Resources/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="hello" path="/hello/{name}">
                <default key="_controller">AcmeHelloBundle:Hello:index</default>
            </route>
        </routes>

    .. code-block:: php

        // src/Acme/HelloBundle/Resources/config/routing.php
        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('hello', new Route('/hello/{name}', array(
            '_controller' => 'AcmeHelloBundle:Hello:index',
        )));

        return $collection;

Usmerjanje sestoji iz dveh osnovnih delov: ``path``, ki je URL, s katerim
se bo ta usmeritev ujemala in polja ``defaults``, ki določa
krmilnik, ki bi moral biti izvršen. Sintaksa označbe mesta je pot
(``name``), ki je nadomestni znak. To pomeni, da se bo ``/hello/Ryan``, ``/hello/Fabien``
ali katerikoli podobni URL ujemal s to potjo. Označba mesta parametra ``{name}``
bo tudi poslana krmilniku, da lahko uporabite njegovo vrednost
za osebni pozdrav uporabnika.

.. note::

  Sistem usmerjanja ima mnoge odlične lastnosti za izdelavo fleksibilnih
  in močnih URL struktur v vaši aplikaciji. Za več podrobnosti, glejte
  poglavje vse o :doc:`Usmerjanju </book/routing>`.

Step 2: Izdelajte krmilnik
~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko je URL, kot je ``/hello/Ryan`` upravljan s strani aplikacije, se ``hello``
usmeritev ujema in krmilnik ``AcmeHelloBundle:Hello:index`` je izvršen
s strani ogrodja. Drugi korak procesa izdelave strnai je izdelava
tega krmilnika.

Krmilnik - ``AcmeHelloBundle:Hello:index`` je *logično* ime
krmilnika in ga preslika v ``indexAction`` metodo PHP razreda
imenovanega ``Acme\HelloBundle\Controller\HelloController``. Začnite z izdelavo te datoteke
znotraj vašega ``AcmeHelloBundle``::

    // src/Acme/HelloBundle/Controller/HelloController.php
    namespace Acme\HelloBundle\Controller;

    class HelloController
    {
    }

V realnosti ni krmilnik nič več kot PHP metoda, ki jo izdelate
in Symfony izvrši. Tu vaša koda uporabi informacije iz zahtevka
za gradnjo in pripravo vira, ki se zahteva. Razen v nekih naprednih
primerih, končni produkt krmilnika je vedno enak: Symfony2 ``Response``
objekt.

Izdelajte metodo ``indexAction``, ki jo bo Symfony izvršil, ko se ``hello``
usmeritev ujema::

    // src/Acme/HelloBundle/Controller/HelloController.php
    namespace Acme\HelloBundle\Controller;

    use Symfony\Component\HttpFoundation\Response;

    class HelloController
    {
        public function indexAction($name)
        {
            return new Response('<html><body>Hello '.$name.'!</body></html>');
        }
    }

Krmilnik je enostaven: izdela nov ``Response`` objekt, katerega prvi
argument je vsebina, ki bi morala biti uporabljena v odzivu (majhna HTML
stran v tem poglavju).

Čestitamo! Po izdelavi samo usmeritve in krmilnika že
imate polno funkcionalno stran! Če ste vse pravilno nastavili, bi vas
vaša aplikacija moral pozdraviti:

.. code-block:: text

    http://localhost/app_dev.php/hello/Ryan

.. _book-page-creation-prod-cache-clear:

.. tip::

    Lahko tudi pogledate vašo aplikacijo v "prod" :ref:`okolju <environments-summary>`
    z obiskom:

    .. code-block:: text

        http://localhost/app.php/hello/Ryan

    Če dobite napako, je to verjetno, ker morate počistiti vaš predpomnilnik
    s pogonom:

    .. code-block:: bash

        $ php app/console cache:clear --env=prod --no-debug

Opcijski vendar pogosti tretji korak v procesu je izdelava predloge.

.. note::

   Krmilniki so glavna vstopna točka za vašo kodo in ključna sestavina,
   ko izdelujete strani. Veliko več informacij se lahko najde v
   :doc:`poglavju krmilnika </book/controller>`.

Opcijski korak 3: Izdelajte predlogo
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Predloge vam omogočajo, da premaknete vso predstavitev (npr. HTML kodo) v
ločeno datoteko in ponovno uporabite različne dele postavitve strani. Namesto
pisanja HTML znotraj krmilnika, namesto tega izpišite predlogo:

.. code-block:: php
    :linenos:

    // src/Acme/HelloBundle/Controller/HelloController.php
    namespace Acme\HelloBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;

    class HelloController extends Controller
    {
        public function indexAction($name)
        {
            return $this->render(
                'AcmeHelloBundle:Hello:index.html.twig',
                array('name' => $name)
            );

            // render a PHP template instead
            // return $this->render(
            //     'AcmeHelloBundle:Hello:index.html.php',
            //     array('name' => $name)
            // );
        }
    }

.. note::

   Da uporabite :method:`Symfony\\Bundle\\FrameworkBundle\\Controller\\Controller::render`
   metodo, mora vaš krmilnik razširiti
   :class:`Symfony\\Bundle\\FrameworkBundle\\Controller\\Controller` razred,
   ki doda bližnjice za opravila, ki so pogosta znotraj krmilnikov. To
   je narejeno v zgornjem primeru z dodajanjem ``use`` stavka v vrstico 4
   in nato razširitvijo ``Controller`` v vrstici 6.

Metoda ``render()`` izdela ``Response`` objekt napolnjen z vsebino
dane izpisane predloge. Kot katerikoli drugi objekt, boste navsezadnje
vrnili ta ``Response`` objekt.

Bodite pozorni, ker sta dva različna primera za izpis predloge.
Privzeto Symfony2 podpira dva različna jezika predlog: klasične
PHP predloge in jedrnate vendar močne `Twig`_ predloge. Ne bodite
zaskrbljeni - lahko prosto izberete kateregakoli ali celo oba v istem projektu.

Krmilnik izpiše predlogo ``AcmeHelloBundle:Hello:index.html.twig``,
ki uporablja sledečo konvencijo poimenovanja:

    **BundleName**:**ControllerName**:**TemplateName**

To je *logično* ime predloge, ki je preslikana v fizično
lokacijo z uporabo sledeče konvencije.

    **/path/to/BundleName**/Resources/views/**ControllerName**/**TemplateName**

V tem primeru, je ``AcmeHelloBundle`` ime paketa, ``Hello`` je
krmilnik in ``index.html.twig`` je predloga:

.. configuration-block::

    .. code-block:: jinja
       :linenos:

        {# src/Acme/HelloBundle/Resources/views/Hello/index.html.twig #}
        {% extends '::base.html.twig' %}

        {% block body %}
            Hello {{ name }}!
        {% endblock %}

    .. code-block:: html+php

        <!-- src/Acme/HelloBundle/Resources/views/Hello/index.html.php -->
        <?php $view->extend('::base.html.php') ?>

        Hello <?php echo $view->escape($name) ?>!

Pojdite skozi Twig predlogo vrstico za vrstico:

* *vrstica 2*: Žeton ``extends`` definira starševsko predlogo. Predloga
  eksplicitno definira postavitveno datoteko znotraj katere bo postavljena.

* *vrstica 4*: Žeton ``block`` pove, da vse znotraj tega mora biti postavljeno
  znotraj bloka imenovanega ``body``. Kot boste videli, je odgovornost
  starševske predloge (``base.html.twig``) konec koncev izpis
  bloka imenovanega ``body``.

Starševska predloga ``::base.html.twig`` nima tako dela **BundleName**, kot tudi
dela **ControllerName** svojega imena (namesto tega ima dvojno podpičje (``::``)
na začetku). To pomeni, da je predloga locirana izven paketa
v direktoriju ``app``:

.. configuration-block::

    .. code-block:: html+jinja

        {# app/Resources/views/base.html.twig #}
        <!DOCTYPE html>
        <html>
            <head>
                <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
                <title>{% block title %}Welcome!{% endblock %}</title>
                {% block stylesheets %}{% endblock %}
                <link rel="shortcut icon" href="{{ asset('favicon.ico') }}" />
            </head>
            <body>
                {% block body %}{% endblock %}
                {% block javascripts %}{% endblock %}
            </body>
        </html>

    .. code-block:: html+php

        <!-- app/Resources/views/base.html.php -->
        <!DOCTYPE html>
        <html>
            <head>
                <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
                <title><?php $view['slots']->output('title', 'Welcome!') ?></title>
                <?php $view['slots']->output('stylesheets') ?>
                <link rel="shortcut icon" href="<?php echo $view['assets']->getUrl('favicon.ico') ?>" />
            </head>
            <body>
                <?php $view['slots']->output('_content') ?>
                <?php $view['slots']->output('javascripts') ?>
            </body>
        </html>

Osnovna datoteka predloge, definira HTML postavitev in izpisuje ``body`` blok,
ki ga definirate v ``index.html.twig`` predlogi. Tudi izpisuje ``title``
blok, ki ga lahko izberete za definicijo v ``index.html.twig`` predlogi.
Ker niste definirali bloka ``title`` v otrokovi predlogi, je privzeto
"Welcome!".

Predloge so močan način za izpis in organizacijo vsebine za vašo
stran. Predloga lahko izpiše karkoli od HTML označevanja, do CSS kode ali česarkoli
drugega, kar mora krmilnik lahko vrniti.

V življenskem ciklu upravljanja zahtevka je motor predlo enostavno
opcijsko orodje. Spomnite se, da je cilj vsakega krmilnika vrniti
``Response`` objekt. Predloge so močna, vendar opcijska orodja za izdelavo
vsebine za ta ``Response`` objekt.

.. index::
   single: Directory Structure

Struktura direktorijev
----------------------

Po samo nekaj kratkih sekcijah, že razumete filozofijo za
izdelavo in izpisom strani v Symfony2. Tudi ste že pričeli videti,
kako so Symfony2 projekti strukturirani in organizirani. Na koncu te sekcije
boste vedeli, kje najti in kam dati različne tipe datotek in zakaj.

Čeprav v celoti fleksibilno privzeto, vsaka Symfony :term:`aplikacija` ima
enako osnovno in priporočeno strukturo direktorijev:

* ``app/``: Ta direktorij vsebuje nastavitve aplikacije;

* ``src/``: Vsa PHP koda projekta je shranjena pod tem direktorijem;

* ``vendor/``: Katerekoli vendor knjižnice so konvencionalno shranjene tu;

* ``web/``: To je vrhnji spletni direktorij in vsebuje kakršnekoli javno dostopne datoteke;

.. _the-web-directory:

Spletni direktorij
~~~~~~~~~~~~~~~~~~

Vrhnji spletni direktorij je dom vseh javnih in statičnih datotek, vključno
s slikami, stili in JavaScript datotekami. To je tudi, kjer domuje
vsak :term:`prednji krmilnik`::

    // web/app.php
    require_once __DIR__.'/../app/bootstrap.php.cache';
    require_once __DIR__.'/../app/AppKernel.php';

    use Symfony\Component\HttpFoundation\Request;

    $kernel = new AppKernel('prod', false);
    $kernel->loadClassCache();
    $kernel->handle(Request::createFromGlobals())->send();

Datoteka prednjega krmilnika (``app.php`` v tem primeru) je dejanska PHP
datoteka, ki je izvršena, ko se uporablja Symfony2 aplikacijo in njena naloga je
uporaba razreda Kernel ``AppKernel`` za zagon aplikacije.

.. tip::

    Imeti prednji krmilnik pomeni različne in bolj fleksibilne URL-je, ki
    so uporabljeni v običajni samo PHP aplikaciji. Ko uporabljate prednji krmilnik,
    so URL-ji oblikovani na sledeči način:

    .. code-block:: text

        http://localhost/app.php/hello/Ryan

    Prednji krmilnik ``app.php`` je izvršen in "interni:" URL
    ``/hello/Ryan`` je usmerjen interno z uporabo nastavitev usmerjanja.
    Z uporabo Apache-jevih ``mod_rewrite`` pravil lahko prisilite datoteko ``app.php``,
    da je izvršena brez potrebe po njenem določanju v URL-ju:

    .. code-block:: text

        http://localhost/hello/Ryan

Čeprav so prednji krmilniki bistveni v upravljanju vsakega zahtevka, boste
redkokdaj morali spremeniti ali celo razmišljati o njih. Omenjeni bodo ponovno
na kratko v sekciji `Okolja`_

Direktorij aplikacije (``app``)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kot ste videli v prednjem krmilniku, je razred ``AppKernel`` glavna vstopna
točka aplikacije in je odgovorna za vse nastavitve. Kot taka
je shranjena v direktoriju ``app/``

Ta razred mora implementirati dve metodi, ki definirata vse, kar mora
Symfony vedeti o vaši aplikaciji. Niti ne potrebujete skrbeti o
teh metodah, ko začenjate - Symfony jih izpolni za vas s smiselnimi
privzetimi vnosi.

* ``registerBundles()``: Vrne polje vseh paketov, ki so potrebni za pogon
  aplikacije (glejte :ref:`page-creation-bundles`);

* ``registerContainerConfiguration()``: Naloži datoteko vira glavnih nastavitev
  aplikacije (glejte sekcijo `Nastavitve aplikacije`_).

V vsakodnevnem razvoju, boste najverjetneje uporabili ``app/`` direktorij za spremembo
datotek nastavitev in usmerjanja v ``app/config/`` direktoriju (glejte
`Nastavitve aplikacije`_). Vsebuje tudi direktorij predpomnilnika
aplikacije (``app/cache``), direktorij dnevnikov (``app/logs``) in direktorij
za datoteke virov aplikacijskih nivojev, kot so predloge (``app/Resources``).
Več o vsakem od teh direktorijev se boste naučili v kasnejših poglavjih.

.. _autoloading-introduction-sidebar:

.. sidebar:: Avtomatsko nalaganje

    Ko se Symfony nalaga, je vključena posebna datoteka - ``vendor/autoload.php``.
    To datoteko ustvari Composer in bo avtomatsko naložila vse
    aplikacijske datoteke, ki domujejo v ``src/`` direktoriju kot tudi vse
    tretje osebne knjižnice omenjene v ``composer.json`` datoteki.

    Zaradi avtomatskega nalagalnika, vam nikoli ni treba skrbeti o uporabi ``include``
    ali ``require`` stavkov. Namesto tega Composer uporablja imenski prostor razreda
    za določanje njegove lokacije in avtomatsko vključi datoteko namesto
    vas takoj, ko razred potrebujete.

    Avtomatski nalagalnik je že nastavljen, da pogleda v ``src/`` direktorij
    za kateregakoli izmed vaših PHP razredov. Da avtomatsko nalaganje deluje, morata ime razreda
    in pot do datoteke slediti enakemu zvorcu:

    .. code-block:: text

        Class Name:
            Acme\HelloBundle\Controller\HelloController
        Path:
            src/Acme/HelloBundle/Controller/HelloController.php

Izvorni direktorij (``src``)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Povedano enostavno, ``src/`` direktorij vsebuje vso dejansko kodo (PHP koda,
predloge, nastavitvene datoteke, stile itd.), ki poganjajo *vašo* aplikacijo.
Ko razvijate, bo glavnina vašega dela narejenega znotraj enega ali
več paketov, ki jih ustvarite v tem direktoriju.

Vendar kaj točno je :term:`paket`?

.. _page-creation-bundles:

Sistem paketov
--------------

Paket je podoben vtičniku v drugih programskih opremah, vendar še boljše. Ključna
razlika je, da je *vse* paket v Symfony2, vključno z
funkcionalnostjo jedra ogrodja in kodo napisano za vašo aplikacijo.
Paketi so prvo razredni občani v Symfony2. To vam da fleksibilnost,
da uporabite vnaprej zgrajene lastnosti zapakirane v `tretje osebnih paketih`_ ali distribuiranje
vaših lastnih paketov. To naredi enostavno za izbrati, katere lastnosti omogočiti
v vaši aplikaciji in jih optimizirati, kakor želite.

.. note::

   Ko se boste tu naučili osnove, je celotna knjiga receptov posvečena
   organizaciji in najboljšim praksam :doc:`paketov </cookbook/bundles/best_practices>`.

Paket je enostavno strukturiran skupek datotek znotraj direktorija, ki implementira
posamezno lastnost. Lahko izdelate ``BlogBundle``, ``ForumBundle`` ali
paket za upravljanje uporabnikov (mnogo paketov že obstaja kot odprto kodni
paketi). Vsak direktorij vsebuje vse povezano s to lastnostjo, vključuje
PHP datoteke, predloge, stile, JavaScript, teste in vse ostalo.
Vsak vidik lastnosti obstaja v paketu in vsaka lastnost živi v
paketu.

Aplikacija je narejena iz paketov, kot definirano v ``registerBundles()``
metodi ``AppKernel`` razreda::

    // app/AppKernel.php
    public function registerBundles()
    {
        $bundles = array(
            new Symfony\Bundle\FrameworkBundle\FrameworkBundle(),
            new Symfony\Bundle\SecurityBundle\SecurityBundle(),
            new Symfony\Bundle\TwigBundle\TwigBundle(),
            new Symfony\Bundle\MonologBundle\MonologBundle(),
            new Symfony\Bundle\SwiftmailerBundle\SwiftmailerBundle(),
            new Symfony\Bundle\DoctrineBundle\DoctrineBundle(),
            new Symfony\Bundle\AsseticBundle\AsseticBundle(),
            new Sensio\Bundle\FrameworkExtraBundle\SensioFrameworkExtraBundle(),
        );

        if (in_array($this->getEnvironment(), array('dev', 'test'))) {
            $bundles[] = new Acme\DemoBundle\AcmeDemoBundle();
            $bundles[] = new Symfony\Bundle\WebProfilerBundle\WebProfilerBundle();
            $bundles[] = new Sensio\Bundle\DistributionBundle\SensioDistributionBundle();
            $bundles[] = new Sensio\Bundle\GeneratorBundle\SensioGeneratorBundle();
        }

        return $bundles;
    }

Z ``registerBundles()`` metodo, imate celotno kontrolo nad tem, kateri paketi
so uporabljeni v vaši aplikaciji (vključno s Symfony paketi jedra).

.. tip::

   Paket lahko domuje *kjerkoli* dokler je lahko avtomatsko naložen (preko
   avtomatskega nalagalnika nastavljenega v ``app/autoload.php``).

Izdelava paketa
~~~~~~~~~~~~~~~

Symfoyn standardna izdaja prihaja s priročno nalogo, ki izdela polno funkcionalni
paket za vas. Seveda izdelava paketa ročno je tudi precej enostavno.

Da vam pokažemo, kako enostaven je sistem paketov, izdelajmo nov paket imenovan
``AcmeTestBundle`` in ga omogočite.

.. tip::

    Del ``Acme`` je samo dummy ime, ki ga bi morali zamenjati z
    nekim "vendor" imenom, ki predstavlja vas ali vašo organizacijo (npr. ``ABCTestBundle``
    za neko podjetje imenovano ``ABC``).

Pričnite izdelovati ``src/Acme/TestBundle/`` direktorij in dodajte novo datoteko
imenovano ``AcmeTestBundle.php``::

    // src/Acme/TestBundle/AcmeTestBundle.php
    namespace Acme\TestBundle;

    use Symfony\Component\HttpKernel\Bundle\Bundle;

    class AcmeTestBundle extends Bundle
    {
    }

.. tip::

   Ime ``AcmeTestBundle`` sledi standardnim :ref:`konvencijam poimenovanja paketov <bundles-naming-conventions>`.
   Lahko tudi izberete skrajšanje imena paketa na enostavno ``TestBundle``
   s poimenovanjem tega razreda ``TestBundle`` (in poimenovanjem datoteke ``TestBundle.php``).

Ta prazen razred je edini del, ki ga potrebujete za izdelavo novega paketa. Čeprav
pogosto prazno, je ta razred močan in lahko uporaben za prilagoditev obnašanja
paketa.

Sedaj ko ste izdelali paket, ga omogočite preko razreda ``AppKernel``::

    // app/AppKernel.php
    public function registerBundles()
    {
        $bundles = array(
            ...,
            // register your bundles
            new Acme\TestBundle\AcmeTestBundle(),
        );
        // ...

        return $bundles;
    }

In medtem ko ne naredi nič več, je sedaj ``AcmeTestBundle`` sedaj pripravljen,
da je uporabljen.

In kakor je enostavno, Symfony tudi ponuja vmesnik ukazne vrstice za
generiranje osnovnega skeletona paketa:

.. code-block:: bash

    $ php app/console generate:bundle --namespace=Acme/TestBundle

Skelet paketa je generiran z osnovnim krmilnikom, predlogo in virom
usmerjanja, ki je lahko prilagojen. Izvedeli boste več o orodju Symfony2 ukazne
vrstice kasneje.

.. tip::

   Kadarkoli izdelujete nov paket ali uporabljate tretje osebni paket, vedno zagotovite,
   da je paket omogočen v ``registerBundles()``. Ko uporabljate
   ukaz ``generate:bundle``, je to narejeno za vas.

Struktura direktorijev paketa
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Struktura direktorijev paketa je enostavna in fleksibilna. Privzeto
sistem paketa sledi skupku konvencij, ki pomagajo obdržati kodo konsistentno
med vsemi Symfony2 paketi. Vzamite za primer ``AcmeHelloBundle``, saj vključuje
nekaj najpogostejših elementov paketa:

* ``Controller/`` vsebuje krmilnike paketa (npr. ``HelloController.php``);

* ``DependencyInjection/`` drži določene razrede razširitve injiciranja odvisnosti,
  ki lahko uvažajo nastavitve storitev, registrirajo prehode prevajalnika in več
  (ta direktorij ni potreben);

* ``Resources/config/`` združuje nastavitve, vključuje nastavitve usmerjanja
  (npr. ``routing.yml``);

* ``Resources/views/`` vsebuje predloge organizirane z imenom krmilnika (npr.
  ``Hello/index.html.twig``);

* ``Resources/public/`` vsebuje spletna sredstva (slike, stile itd.) in je
  kopiran ali simbolično povezan v ``web/`` direktorij projekta preko
  ``assets:install`` konzolnega ukaza;

* ``Tests/`` vsebuje vse teste za paket.

Paket je lahko tako majhen ali velik, kolikor lastnosti implementira. Vsebuje
samo datoteke, ki jih potrebujete in nič več.

Kakor se premikate skozi knjigo, boste izvedeli, kako poslati objekte v podatkovno bazo,
izdelati in potrditi obrazce, izdelati prevode za vašo aplikacijo, napisati
teste in veliko več. Vsak od teh ima svoj lastni prostor in vlogo znotraj
paketa.

Nastavitve aplikacije
---------------------

Aplikacija sestoji iz zbirke paketov, ki predstavljajo vse
lastnosti in zmožnosti vaše aplikacije. Vsak paket se lahko prilagodi
preko nastavitvenih datotek napisanih v YAML, XML ali PHP. Privzeto je glavna
nastavitvena datoteka locirana v ``app/config/`` direktoriju in je imenovana
ali ``config.yml``, ``config.xml`` ali ``config.php`` odvisno od
formata, ki ga imate raje:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        imports:
            - { resource: parameters.yml }
            - { resource: security.yml }

        framework:
            secret:          "%secret%"
            router:          { resource: "%kernel.root_dir%/config/routing.yml" }
            # ...

        # Twig Configuration
        twig:
            debug:            "%kernel.debug%"
            strict_variables: "%kernel.debug%"

        # ...

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:framework="http://symfony.com/schema/dic/symfony"
            xmlns:twig="http://symfony.com/schema/dic/twig"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/symfony http://symfony.com/schema/dic/symfony/symfony-1.0.xsd
                                http://symfony.com/schema/dic/twig http://symfony.com/schema/dic/twig/twig-1.0.xsd">
                                
            <imports>
                <import resource="parameters.yml" />
                <import resource="security.yml" />
            </imports>

            <framework:config secret="%secret%">
                <framework:router resource="%kernel.root_dir%/config/routing.xml" />
                <!-- ... -->
            </framework:config>

            <!-- Twig Configuration -->
            <twig:config debug="%kernel.debug%" strict-variables="%kernel.debug%" />

            <!-- ... -->
        </container>

    .. code-block:: php

        $this->import('parameters.yml');
        $this->import('security.yml');

        $container->loadFromExtension('framework', array(
            'secret'          => '%secret%',
            'router'          => array(
                'resource' => '%kernel.root_dir%/config/routing.php',
            ),
            // ...
            ),
        ));

        // Twig Configuration
        $container->loadFromExtension('twig', array(
            'debug'            => '%kernel.debug%',
            'strict_variables' => '%kernel.debug%',
        ));

        // ...

.. note::

   Izvedeli boste točno, kako naložiti vsako datoteko/format v naslednji sekciji
   `Okolja`_.

Vsak vrhnji vnos kot sta ``framework`` ali ``twig`` definirata nastavitve
za določen paket. Na primer ključ ``framework`` definira nastavitve
za Symfony paket jedra FrameworkBundle in vključuje nastavitve za
usmerjanje, predloge in ostale sisteme jedra.

Za sedaj ne skrbite o specifičnih nastavitvenih opcijah v vsaki sekciji.
Nastavitvena datoteka prihaja s smiselnimi privzetimi vrednostmi. Kot boste prebrali več in
raziskali vsak del Symfony2, se boste naučili o določenih nastavitvenih
opcijah za vsako lastnost.

.. sidebar:: Formati nastavitev

    Skozi poglavja, vsi primeri nastavitev bodo prikazani v vseh
    treh formatih (YAML, XML in PHP). Vsak ima svoje prednosti in
    slabosti. Izbira katerega uporabiti je na vas:

    * *YAML*: Enostaven, jasen in bralen (izvedite več o YAML v
      ":doc:`/components/yaml/yaml_format`");

    * *XML*: Bolj močan kot YAML na trenutke in podpira IDE avtomatsko zaključevanje;

    * *PHP*: Zelo močna vendar manj bralna kot standardni nastavitveni formati.

Odložitev privzetih nastavitev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Lahko odložite privzete nastavitve za paket v YAML v konzolo z uporabo
ukaza ``config:dump-reference``.  Tu je primer odložitve privzetih nastavitev
FrameworkBundle:

.. code-block:: bash

    $ app/console config:dump-reference FrameworkBundle

Razširitveni alias (nastavitveni ključ) je lahko tudi uporabljen:

.. code-block:: bash

    $ app/console config:dump-reference framework

.. note::

    Glejte članek receptov:
    :doc:`Kako izpostaviti semantične nastavitve za paket </cookbook/bundles/extension>`
    za informacije o dodajanju nastavitev za vaš lastni paket.

.. index::
   single: Environments; Introduction

.. _environments-summary:

Okolja
------

Aplikacija se lahko poganja v različnihokoljih. Različna okolja
delijo enako PHP kodo (razen prednjega krmilnika), vendar uporaba različnih
nastavitev. Na primer ``dev`` okolje bo beležilo opozorila in
napake, medtem ko ``prod`` okolje bo beležilo samo napake. Nekatere datoteke so
ponovno zgrajene pri vsakem zahtevku v ``dev`` okolju (za priročnost razvijalca),
vendar predpomnjene v ``prod`` okolju. Vsa okolja obstojajo skupaj na
isti napravi in izvršujejo isto aplikacijo.

Symfony2 projekt se splošno začne s tremi okolji (``dev``, ``test``
in ``prod``), čeprav je izdelava novih okolij enostavna. Lahko pogledate vašo
aplikacijo v različnih okoljih enostavno s spremembo prednjega krmilnika
v vašem brskalniku. Da pogledate aplikacijo v ``dev`` okolju, dostopajte
do aplikacije preko razvojnega prednjega krmilnika:

.. code-block:: text

    http://localhost/app_dev.php/hello/Ryan

Če bi želeli videti kako se bo vaša aplikacija obnašala v produkcijskem okolju,
namesto tega pokličite ``prod`` prednji krmilnik:

.. code-block:: text

    http://localhost/app.php/hello/Ryan

Ker je ``prod`` okolje optimizirano za hitrost; nastavitve,
usmerjanje in Twig predloge so prevedene v samo PHP razrede in predpomnjeni.
Ko gledate spremembe v ``prod`` okolju, boste morali počistiti te
predpomnjene datoteke in jih omogočiti za ponovno gradnjo:

.. code-block:: bash

    $ php app/console cache:clear --env=prod --no-debug

.. note::

   Če odprete datoteko ``web/app.php``, boste ugotovili, da je nastavljena eksplicitno
   za uporabo ``prod`` okolja::

       $kernel = new AppKernel('prod', false);

   Lahko izdelate nov prednji krmilnik za novo okolje s kopiranjem
   te datoteke in spremembo ``prod`` v neko drugo vrednost.

.. note::

    Okolje ``test`` je uporabljeno, ko se poganja avtomatizirane teste in ne
    more biti dostopano direktno preko brskalnika. Glejte :doc:`poglavje testiranje </book/testing>`
    za več podrobnosti.

.. index::
   single: Environments; Configuration

Nstavitve okolja
~~~~~~~~~~~~~~~~

Razred ``AppKernel`` je odgovoren za dejansko nalaganje nastavitvene
datoteke vaše izbire::

    // app/AppKernel.php
    public function registerContainerConfiguration(LoaderInterface $loader)
    {
        $loader->load(
            __DIR__.'/config/config_'.$this->getEnvironment().'.yml'
        );
    }

Sedaj že veste, da se ``.yml`` končnico lahko spremeni v ``.xml`` ali
``.php`` če raje uporabljate ali XML ali PHP za pisanje vaših nastavitev.
Bodite pozorni, da vsako okolje naloži svojo lastno nastavitveno datoteko. Premislite
o nastavitveni datoteki za ``dev`` okolje.

.. configuration-block::

    .. code-block:: yaml

        # app/config/config_dev.yml
        imports:
            - { resource: config.yml }

        framework:
            router:   { resource: "%kernel.root_dir%/config/routing_dev.yml" }
            profiler: { only_exceptions: false }

        # ...

    .. code-block:: xml

        <!-- app/config/config_dev.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:framework="http://symfony.com/schema/dic/symfony"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/symfony http://symfony.com/schema/dic/symfony/symfony-1.0.xsd">

            <imports>
                <import resource="config.xml" />
            </imports>

            <framework:config>
                <framework:router
                    resource="%kernel.root_dir%/config/routing_dev.xml"
                />
                <framework:profiler only-exceptions="false" />
            </framework:config>

            <!-- ... -->

    .. code-block:: php

        // app/config/config_dev.php
        $loader->import('config.php');

        $container->loadFromExtension('framework', array(
            'router'   => array(
                'resource' => '%kernel.root_dir%/config/routing_dev.php',
            ),
            'profiler' => array('only-exceptions' => false),
        ));

        // ...

Ključ ``imports`` je podoben PHP stavku ``include`` in garantira,
da je glavna nastavitvena datoteka (``config.yml``) naložena prva. Ostala
datoteka nastavi privzete nastavitve za izboljšano beleženje in ostale
nastavitve, ki prispevajo razvojnemu okolju.

Tako ``prod`` in ``test`` okolja sledijo enakemu modelu: vsako okolje
uvaža osnovno nastavitveno datoteko in nato spremeni njegove nastavitvene vrednosti,
da se ujemajo potrebam določenega okolja. To je samo konvencija,
vendar taka, ki vam omogoča ponovno uporabo večine vaših nastavitev in prilagoditev
samo njenih delov med okolji.

Povzetek
--------

Čestitke! Sedaj ste videli vsak temeljni vidik Symfony2 in ste,
upajmo, odkrili kako enostaven in fleksibilen je lahko. Medtem ko je
*veliko* lastnosti, ki še pridejo, se prepričajte, da sledite osnovnim točkam
v mislih:

* Izdelava strani je proces v treh korakih, ki vključuje **usmeritev**, **krmilnik**
  in (opcijsko) **predlogo**;

* Vsak projekt vsebuje samo nekaj glavnih direktorijev: ``web/`` (spletna sredstva in
  prednje krmilnike), ``app/`` (nastavitve), ``src/`` (vaše pakete)
  in ``vendor/`` (tretje osebno kodo) (na voljo je tudi ``bin/`` direktorij, ki
  je uporabljen, da pomaga posobiti izdelovalčeve knjižnice);

* Vsaka lastnost v Symfony2 (vključno jedro Symfony2 ogrodja) je organizirano
  v *paket*, ki je strukturiran skupek datotek za to lastnost;

* **Nastavitev** za vsak paket živi v ``Resources/config``
  direktoriju paketa in je lahko določen v YAML, XML ali PHP;

* Globalne **nastaviteve aplikacije** se nahajajo v ``app/config``
  direktoriju;

* Vsako **okolje** je dostopno preko različnega prednjega krmilnika (npr.
  ``app.php`` in ``app_dev.php`` in naloži različno nastavitveno datoteko.

Od tu vam bo vsako poglavje predstavilo več in bolj močna orodja
in naprednje koncepte. Več ko veste o Symfony2, več boste
cenili fleksibilnost njegove arhitekture in moč, ki vam jo da
za hitro gradnjo aplikacij.

.. _`Twig`: http://twig.sensiolabs.org
.. _`tretje osebnih paketih`: http://knpbundles.com
.. _`Symfony Standard Edition`: http://symfony.com/download
.. _`Apache DirectoryIndex dokumentacijo`: http://httpd.apache.org/docs/current/mod/mod_dir.html
.. _`Nginx HttpCoreModule lokacijo dokumentacije`: http://wiki.nginx.org/HttpCoreModule#location
