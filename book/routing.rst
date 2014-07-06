.. index::
   single: Routing

Usmerjanje
==========

Lepi URL-ji so absolutna zahteva za kakršnokoli resno spletno aplikacijo. To
pomeni zapustiti za sabo grde URL-je kot je ``index.php?article_id=57`` za
nekaj kot je ``/read/intro-to-symfony``.

Imeti fleksibilnost je celo bolj pomembna. Kaj če potrebujete spremeniti
URL strani iz ``/blog`` v ``/news``? Koliko povezav bi potrebovali
poiskati in posodobiti, da naredite to spremembo? Če uporabljate Symfony-jev usmerjevalnik,
je sprememba enostavna.

Symfony2 usmerjevalnik vam omogoča definirati kreativne URL-je, ki jih preslikate v različna
področja vaše aplikacije. Do konca tega poglavja boste sposobni:

* Izdelati kompleksne usmeritve, ki se preslikajo v krmilnike
* Generirati URL-je znotraj predlog in krmilnikov
* Naložiti vire iz paketov (ali kjerkoli drugje)
* Razhroščiti vaše usmeritve

.. index::
   single: Routing; Basics

Usmerjanje v delovanju
----------------------

*Usmeritev* je preslikava iz URL-ja v krmilnik. Na primer, predpostavimo,
da želite ujeti katerikoli URL kot je ``/blog/my-post`` ali ``/blog/all-about-symfony``
in ga poslati h krmilniku, ki ga lahko poiščete in izpišete ta vnos bloga.
Usmeritev je enostavna:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        blog_show:
            path:      /blog/{slug}
            defaults:  { _controller: AcmeBlogBundle:Blog:show }

    .. code-block:: xml

        <!-- app/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="blog_show" path="/blog/{slug}">
                <default key="_controller">AcmeBlogBundle:Blog:show</default>
            </route>
        </routes>

    .. code-block:: php

        // app/config/routing.php
        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('blog_show', new Route('/blog/{slug}', array(
            '_controller' => 'AcmeBlogBundle:Blog:show',
        )));

        return $collection;

Pot definirana z usmeritvami ``blog_show`` deluje kot ``/blog/*``, kjer
je dan nadomestni znak za ime ``slug``. Za URL ``/blog/my-blog-post``,
dobi spremenljivka ``slug`` vrednost ``my-blog-post``, ki je na voljo
za vas, da jo uporabite v vašem krmilniku (nadaljujte branje). ``blog_show`` je
notranje ime usmeritve, ki nima še nobenega pomena in samo potrebuje
biti unikatna. Kasneje jo boste uporabili, da generirate URL-je.

Parameter ``_controller`` je poseben ključ, ki pove Symfony-ju, kateri krmilnik
bi se moral izvesti, ko je URL ujet z usmeritvijo. Niz ``_controller``
se imenuje :ref:`logično ime <controller-string-syntax>`. Sledi
vzorcu, ki kaže na določen PHP razred in metodo::

    // src/Acme/BlogBundle/Controller/BlogController.php
    namespace Acme\BlogBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;

    class BlogController extends Controller
    {
        public function showAction($slug)
        {
            // use the $slug variable to query the database
            $blog = ...;

            return $this->render('AcmeBlogBundle:Blog:show.html.twig', array(
                'blog' => $blog,
            ));
        }
    }

Čestitamo! Ustvarili ste vašo prvo usmeritev in jo povezali s
krmilnikom. Sedaj, ko obiščete ``/blog/my-post`` bo izvršen krmilnik ``showAction``
in spremenljivka ``$slug`` bo enaka ``my-post``.

To je cilj Symfony2 usmerjevalnika: preslikati URL zahtevka v
krmilnik. Tekom poti se boste naučili vse vrste trikov, ki naredijo preslikave
celo bolj kompleksnih URL-jev enostavne.

.. index::
   single: Routing; Under the hood

Usmerjanje: pod pokrovom
------------------------

Ko je ustvarjen zahtevek za vašo aplikacijo, vsebuje naslov do
točnega "vira", ki ga klient zahteva. Ta naslov se imenuje
URL (ali URI) in je lahko ``/contact``, ``/blog/read-me`` ali karkoli
drugega. Vzamite sledeči HTTP zahtevek za primer:

.. code-block:: text

    GET /blog/my-blog-post

Cilj usmerjevalnega sistema Symfony2 je razčlenjevanje tega URL-ja in določanje
kateri krmilnik bi se moral izvršiti. Celoten proces zgleda takole:

#. Zahtevek je upravljan s strani prednjega krmilnika Symfony2 (npr. ``app.php``);

#. Jedro Symfony2 (t.j.. Kernel) vpraša usmerjevalnik, da preveri zahtevek;

#. Usmerjevalnik ujame prihajajoči URL na določeno usmeritev in vrne informacije
   o usmeritvi, vključno s krmilnikom, ki bi moral biti izvršen;

#. Symfony2 jedro izvrši krmilnik, ki na koncu vrne
   objekt ``Response``.

.. figure:: /images/request-flow.png
   :align: center
   :alt: Symfony2 request flow

   Plast usmeritve je orodje, ki prevede prihajajoči URL v določen
   krmilnik za izvršitev.

.. index::
   single: Routing; Creating routes

Ustvarjanje usmeritev
---------------------

Symfony naloži vse usmeritve za vašo aplikacijo iz ene nastavitvene usmeritve
datoteke. Ta datoteka je običajno ``app/config/routing.yml``, vendar je lahko nastavljena,
da je karkoli (vključno z XML ali PHP datoteko) preko datoteke aplikacijskih
nastavitev:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        framework:
            # ...
            router:        { resource: "%kernel.root_dir%/config/routing.yml" }

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:framework="http://symfony.com/schema/dic/symfony"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/symfony http://symfony.com/schema/dic/symfony/symfony-1.0.xsd">

            <framework:config>
                <!-- ... -->
                <framework:router resource="%kernel.root_dir%/config/routing.xml" />
            </framework:config>
        </container>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('framework', array(
            // ...
            'router' => array(
                'resource' => '%kernel.root_dir%/config/routing.php',
            ),
        ));

.. tip::

    Tudi če so vse usmeritve naložene iz ene datoteke, je pogosta praksa
    vključiti dodatne vire usmeritev. Da to naredite, samo pokažite v
    glavno usmeritveno nastavitveno datoteko, katere zunanje datoteke bi morale biti vključene.
    Glejte sekcijo :ref:`routing-include-external-resources` za več
    informacij.

Osnovne nastavitve usmerjanja
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Definiranje usmeritve je enostavno in običajna aplikacija bo imela veliko usmeritev.
Osnovna usmeritev sestoji iz samo dveh delov: ``path``, ki se ujema in
polja ``defaults``:

.. configuration-block::

    .. code-block:: yaml

        _welcome:
            path:      /
            defaults:  { _controller: AcmeDemoBundle:Main:homepage }

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="_welcome" path="/">
                <default key="_controller">AcmeDemoBundle:Main:homepage</default>
            </route>

        </routes>

    ..  code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('_welcome', new Route('/', array(
            '_controller' => 'AcmeDemoBundle:Main:homepage',
        )));

        return $collection;

Ta usmeritev se ujema z domačo stranjo (``/``) in jo preslika v ``AcmeDemoBundle:Main:homepage``
krmilnik. Niz ``_controller`` je preveden s strani Symfony2 v
dejansko PHP funkcijo in izvršen. Ta proces bo razložen v kratkem
v sekciji :ref:`controller-string-syntax`.

.. index::
   single: Routing; Placeholders

Usmerjanje s prostorniki
~~~~~~~~~~~~~~~~~~~~~~~~

Seveda sistem usmerjanja podpira veliko več zanimivih usmeritev. Mnogo
usmeritev bo vsebovalo enega ali več poimenovanih prostornikov "nadomestnih znakov":

.. configuration-block::

    .. code-block:: yaml

        blog_show:
            path:      /blog/{slug}
            defaults:  { _controller: AcmeBlogBundle:Blog:show }

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="blog_show" path="/blog/{slug}">
                <default key="_controller">AcmeBlogBundle:Blog:show</default>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('blog_show', new Route('/blog/{slug}', array(
            '_controller' => 'AcmeBlogBundle:Blog:show',
        )));

        return $collection;

Pot se bo ujemala s čemerkoli, kar izgleda kot ``/blog/*``. Še boljše,
vrednost, ki se ujema s prostornikom ``{slug}`` bo na voljo znotraj vašega
krmilnika. Z drugimi besedami, če je URL ``/blog/hello-world``, spremenljivka
``$slug`` z vrednostjo ``hello-world`` bo na voljo v krmilniku.
To je lahko uporabno na primer za naložiti blog post, ki se ujema z nizom.

Pot se vseeno *ne* bo ujemela enostavno z ``/blog``. To je, ker
privzeto so vsi prostorniki zahtevani. To se lahko spremeni z dodajanjem
vrednosti prostornika polju ``defaults``.

Zahtevani in opcijski prostorniki
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Da naredimo stvari bolj razburljive, dodamo novo usmeritev, ki prikaže seznam vseh
objav bloga, ki so na voljo za to imaginarno blog aplikacijo:

.. configuration-block::

    .. code-block:: yaml

        blog:
            path:      /blog
            defaults:  { _controller: AcmeBlogBundle:Blog:index }

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="blog" path="/blog">
                <default key="_controller">AcmeBlogBundle:Blog:index</default>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('blog', new Route('/blog', array(
            '_controller' => 'AcmeBlogBundle:Blog:index',
        )));

        return $collection;

So sedaj je ta usmeritev kolikor možno enostavna - ne vsebuje prostornikov
in se bo ujemala samo s točnimi URL-ji ``/blog``. Vendar kaj če potrebujete, da ta usmeritev
podpira paginacijo, kjer ``/blog/2`` prikaže drugo stran vnosov
bloga? Posodobite usmeritev, da imate nov prostornik ``{page}``:

.. configuration-block::

    .. code-block:: yaml

        blog:
            path:      /blog/{page}
            defaults:  { _controller: AcmeBlogBundle:Blog:index }

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="blog" path="/blog/{page}">
                <default key="_controller">AcmeBlogBundle:Blog:index</default>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('blog', new Route('/blog/{page}', array(
            '_controller' => 'AcmeBlogBundle:Blog:index',
        )));

        return $collection;

Kot pred tem prostornik ``{slug}``, bo vrednost ujeta s ``{page}``
na voljo znotraj vašega krmilnika. Njegova vrednost je lahko uporabljena za določanje, katerega
seta objav bloga prikazati za dano stran.

Vendar počakajte! Odkar so prostorniki privzeto zahtevani ta usmeritev
ni več ujeta z enostavnim ``/blog``. Namesto, da vidite stran 1 blog-a,
bi morali uporabiti URL ``/blog/1``! Odkar to ni več način za bogate spletne
aplikacije, da se obnašajo, spremenite usmeritev, da naredi parameter ``{page}`` opcijski.
To je narejeno z vključitvijo zbirke ``defaults``:

.. configuration-block::

    .. code-block:: yaml

        blog:
            path:      /blog/{page}
            defaults:  { _controller: AcmeBlogBundle:Blog:index, page: 1 }

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="blog" path="/blog/{page}">
                <default key="_controller">AcmeBlogBundle:Blog:index</default>
                <default key="page">1</default>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('blog', new Route('/blog/{page}', array(
            '_controller' => 'AcmeBlogBundle:Blog:index',
            'page'        => 1,
        )));

        return $collection;

Z dodajanjem ``page`` ključu ``defaults``, prostornik ``{page}`` ni več
zahtevan. URL ``/blog`` se bo ujemal s to usmeritvijo in vrednost
parametra ``page`` bo nastavljena na ``1``. URL ``/blog/2`` se bo tudi
ujemal in dajal parametru ``page`` vrednost ``2``. Odlično.

+--------------------+-----------+-----------------------+
| URL                | usmeritev | parametri             |
+====================+===========+=======================+
| /blog              | blog      | {page} = 1            |
+--------------------+-----------+-----------------------+
| /blog/1            | blog      | {page} = 1            |
+--------------------+-----------+-----------------------+
| /blog/2            | blog      | {page} = 2            |
+--------------------+-----------+-----------------------+

.. caution::

    Seveda imate lahko več kot en opcijski prostornik (npr. ``/blg/{slug}/{page}``),
    vendar vse za opcijskim prostornikom mora biti opcijsko. Na primer,
    ``/{page}/blog`` je veljavna pot, vendar ``page`` bo vedno zahtevana
    (t.j. enostavno ``/blog`` se ne bo ujemal s to usmeritvijo).

.. tip::

    Usmeritve z opcijskimi parametri na koncu se ne bodo ujemale na zahtevkih
    s končno poševnico (t.j. ``/blog/`` se ne bo ujel, ``/blog`` se bo ujel).

.. index::
   single: Routing; Requirements

Dodajanje zahtev
~~~~~~~~~~~~~~~~

Na hitro poglejte usmeritve, ki so bile ustvarjene za vas:

.. configuration-block::

    .. code-block:: yaml

        blog:
            path:      /blog/{page}
            defaults:  { _controller: AcmeBlogBundle:Blog:index, page: 1 }

        blog_show:
            path:      /blog/{slug}
            defaults:  { _controller: AcmeBlogBundle:Blog:show }

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="blog" path="/blog/{page}">
                <default key="_controller">AcmeBlogBundle:Blog:index</default>
                <default key="page">1</default>
            </route>

            <route id="blog_show" path="/blog/{slug}">
                <default key="_controller">AcmeBlogBundle:Blog:show</default>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('blog', new Route('/blog/{page}', array(
            '_controller' => 'AcmeBlogBundle:Blog:index',
            'page'        => 1,
        )));

        $collection->add('blog_show', new Route('/blog/{show}', array(
            '_controller' => 'AcmeBlogBundle:Blog:show',
        )));

        return $collection;

Ali opazite problem? Bodite pozorni, da imata obe usmeritvi vzorce, ki se ujemajo
z URL-ji, ki izgledajo kot ``/blog/*``. Symfony-jev usmerjevalnik bo vedno izbral
**prvo** ujemalno usmeritev, ki jo najde. Z drugimi besedami, usmeritev ``blog_show``
se ne bo nikoli ujemala. Namesto tega, URL kot je ``/blog/my-blog-post`` se bo ujel
s prvo usmeritvijo (``blog``) in vrnil nesmiselno vrednost ``my-blog-post``
parametru ``{page}``.

+--------------------+-----------+-----------------------+
| URL                | usmeritev | parametri             |
+====================+===========+=======================+
| /blog/2            | blog      | {page} = 2            |
+--------------------+-----------+-----------------------+
| /blog/my-blog-post | blog      | {page} = my-blog-post |
+--------------------+-----------+-----------------------+

Odgovor na problem je dodati *zahteve* usmeritve  ali *pogoje* usmeritve
(see :ref:`book-routing-conditions`). Usmeritve v tem primeru bi delovale
odlično, če bi se pot ``/blog/{page}`` ujemala *samo* z URL-ji, kjer je del
``{page}`` celo število. Na srečo, so lahko zahteve splošnih izrazov enostavno
dodane za vsak parameter. Na primer:

.. configuration-block::

    .. code-block:: yaml

        blog:
            path:      /blog/{page}
            defaults:  { _controller: AcmeBlogBundle:Blog:index, page: 1 }
            requirements:
                page:  \d+

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="blog" path="/blog/{page}">
                <default key="_controller">AcmeBlogBundle:Blog:index</default>
                <default key="page">1</default>
                <requirement key="page">\d+</requirement>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('blog', new Route('/blog/{page}', array(
            '_controller' => 'AcmeBlogBundle:Blog:index',
            'page'        => 1,
        ), array(
            'page' => '\d+',
        )));

        return $collection;

Zahteva ``\d+`` je splošni izraz, ki pravi, da vrednost
parametra ``{page}`` mora biti celo število (t.j. številka). Usmeritev ``blog``
se bo še vedno ujemala na URL-jih kot je ``/blog/2`` (ker je 2 številka), vendar
se ne bo več ujemala z URL-ji kot je ``/blog/my-blog-post`` (ker ``my-blog-post``
*ni* številka).

Kot rezultat, URL kot je ``/blog/my-blog-post``, se bo sedaj ustrezno ujemala z
usmeritvijo ``blog_show``.

+----------------------+-----------+-------------------------+
| URL                  | usmeritev | parametri               |
+======================+===========+=========================+
| /blog/2              | blog      | {page} = 2              |
+----------------------+-----------+-------------------------+
| /blog/my-blog-post   | blog_show | {slug} = my-blog-post   |
+----------------------+-----------+-------------------------+
| /blog/2-my-blog-post | blog_show | {slug} = 2-my-blog-post |
+----------------------+-----------+-------------------------+

.. sidebar:: Prejšnje usmeritve vedno zmagajo

    Kaj to vse pomeni je, da je vrstni red usmeritev zelo pomemben.
    Če bi bila usmeritev ``blog_show`` postavljena nad usmeritev ``blog``,
    bi se URL ``/blog/2`` ujemal z ``blog_show`` namesto z ``blog``, ker
    parameter ``{slug}`` od ``blog_show`` nima nobenih zahtev. Z uporabo ustreznega
    vrstnega reda in pametnih zahtev, lahko dosežete karkoli.

Ker so zahteve parametrov splošni izrazi, sta kompleksnost
in fleksibilnost vsakega zahtevka v celoti odvisna od vas. Predpostavimo, da je domača stran
vaše aplikacije na voljo v dveh različnih jezikih, na osnovi
URL-ja:

.. configuration-block::

    .. code-block:: yaml

        homepage:
            path:      /{culture}
            defaults:  { _controller: AcmeDemoBundle:Main:homepage, culture: en }
            requirements:
                culture:  en|fr

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="homepage" path="/{culture}">
                <default key="_controller">AcmeDemoBundle:Main:homepage</default>
                <default key="culture">en</default>
                <requirement key="culture">en|fr</requirement>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('homepage', new Route('/{culture}', array(
            '_controller' => 'AcmeDemoBundle:Main:homepage',
            'culture'     => 'en',
        ), array(
            'culture' => 'en|fr',
        )));

        return $collection;

Za prihajajoče zahtevke, se del ``{culture}`` URL-ja ujema s
splošnimi izrazi ``(en|fr)``.

+-----+--------------------------+
| /   | {culture} = en           |
+-----+--------------------------+
| /en | {culture} = en           |
+-----+--------------------------+
| /fr | {culture} = fr           |
+-----+--------------------------+
| /es | *won't match this route* |
+-----+--------------------------+

.. index::
   single: Routing; Method requirement

Dodajanje zahtev HTTP metod
~~~~~~~~~~~~~~~~~~~~~~~~~~~

V dodatku URL-ja, lahko tudi ujemate na *metodi* prihajajočega
zahtevka (t.j. GET, HEAD, POST, PUT, DELETE). Predpostavimo, da imate kontaktni obrazec
z dvema krmilnikoma - eden za prikaz obrazca (na zahtevku GET) in eden
za procesiranje obrazca, ko je poslan (na zahtevku POST). To je lahko
doseženo s sledečo nastavitvijo usmeritve:

.. configuration-block::

    .. code-block:: yaml

        contact:
            path:     /contact
            defaults: { _controller: AcmeDemoBundle:Main:contact }
            methods:  [GET]

        contact_process:
            path:     /contact
            defaults: { _controller: AcmeDemoBundle:Main:contactProcess }
            methods:  [POST]

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="contact" path="/contact" methods="GET">
                <default key="_controller">AcmeDemoBundle:Main:contact</default>
            </route>

            <route id="contact_process" path="/contact" methods="POST">
                <default key="_controller">AcmeDemoBundle:Main:contactProcess</default>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('contact', new Route('/contact', array(
            '_controller' => 'AcmeDemoBundle:Main:contact',
        ), array(), array(), '', array(), array('GET')));

        $collection->add('contact_process', new Route('/contact', array(
            '_controller' => 'AcmeDemoBundle:Main:contactProcess',
        ), array(), array(), '', array(), array('POST')));

        return $collection;

Kljub dejstvu, da imata ti dve usmeritvi identični poti (``/contact``),
se bo prva usmeritev ujemala samo z zahtevki GET in druga usmeritev se bo ujemala
samo z zahtevki POST. To pomeni, da lahko prikažete obrazec in ga pošljete
preko enakega URL-ja, medtem ko uporabljate različna krmilnika za ti dve akciji.

.. note::

    Če ni specificirana nobena ``method``, se bo usmeritev ujemala z *vsemi* metodami.

Dodajanje zahtev gostitelja
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ujemate lahko tudi HTTP *host* prihajajočega zahtevka. Za več
informacij, glejte :doc:`/components/routing/hostname_pattern` v dokumentaciji Routing
komponente.

.. _book-routing-conditions:

Popolnoma prilagojeno ujemanje usmeritev s pogoji
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.4
    Pogoji usmeritev so bili predstavljeni v Symfony 2.4.

Kot ste videli, je lahko usmeritev narejena, da se ujema samo z določenimi usmeritvenimi nadomestnimi znaki
(preko splošnih izrazov), HTTP metodami ali imeni gostiteljev. Vendar je lahko sistem
usmerjanja razširjen, da ima skoraj neskončno fleksibilnost z uporabo ``pogojev``:

.. configuration-block::

    .. code-block:: yaml

        contact:
            path:     /contact
            defaults: { _controller: AcmeDemoBundle:Main:contact }
            condition: "context.getMethod() in ['GET', 'HEAD'] and request.headers.get('User-Agent') matches '/firefox/i'"

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="contact"
                path="/contact"
                condition="context.getMethod() in ['GET', 'HEAD'] and request.headers.get('User-Agent') matches '/firefox/i'"
            >
                <default key="_controller">AcmeDemoBundle:Main:contact</default>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('contact', new Route(
            '/contact', array(
                '_controller' => 'AcmeDemoBundle:Main:contact',
            ),
            array(),
            array(),
            '',
            array(),
            array(),
            'context.getMethod() in ["GET", "HEAD"] and request.headers.get("User-Agent") matches "/firefox/i"'
        ));

        return $collection;

``condition`` je izraz in lahko se naučite več o njegovi sintaksi
tu: :doc:`/components/expression_language/syntax`. S tem se usmeritev
ne bo ujemala razen, če je HTTP metoda ali GET ali HEAD *in*, če je glava ``User-Agent``
``firefox``.

Lahko naredite katerokoli kompleksno logiko, ki jo potrebujete v izrazu 
You can do any complex logic you need in the expression by leveraging two
variables that are passed into the expression:

* ``context``: An instance of :class:`Symfony\\Component\\Routing\\RequestContext`,
  which holds the most fundamental information about the route being matched;
* ``request``: The Symfony :class:`Symfony\\Component\\HttpFoundation\\Request`
  object (see :ref:`component-http-foundation-request`).

.. caution::

    Conditions are *not* taken into account when generating a URL.

.. sidebar:: Expressions are Compiled to PHP

    Behind the scenes, expressions are compiled down to raw PHP. Our example
    would generate the following PHP in the cache directory::

        if (rtrim($pathinfo, '/contact') === '' && (
            in_array($context->getMethod(), array(0 => "GET", 1 => "HEAD"))
            && preg_match("/firefox/i", $request->headers->get("User-Agent"))
        )) {
            // ...
        }

    Because of this, using the ``condition`` key causes no extra overhead
    beyond the time it takes for the underlying PHP to execute.

.. index::
   single: Routing; Advanced example
   single: Routing; _format parameter

.. _advanced-routing-example:

Advanced Routing Example
~~~~~~~~~~~~~~~~~~~~~~~~

At this point, you have everything you need to create a powerful routing
structure in Symfony. The following is an example of just how flexible the
routing system can be:

.. configuration-block::

    .. code-block:: yaml

        article_show:
          path:     /articles/{culture}/{year}/{title}.{_format}
          defaults: { _controller: AcmeDemoBundle:Article:show, _format: html }
          requirements:
              culture:  en|fr
              _format:  html|rss
              year:     \d+

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="article_show"
                path="/articles/{culture}/{year}/{title}.{_format}">

                <default key="_controller">AcmeDemoBundle:Article:show</default>
                <default key="_format">html</default>
                <requirement key="culture">en|fr</requirement>
                <requirement key="_format">html|rss</requirement>
                <requirement key="year">\d+</requirement>

            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add(
            'article_show',
            new Route('/articles/{culture}/{year}/{title}.{_format}', array(
                '_controller' => 'AcmeDemoBundle:Article:show',
                '_format'     => 'html',
            ), array(
                'culture' => 'en|fr',
                '_format' => 'html|rss',
                'year'    => '\d+',
            ))
        );

        return $collection;

As you've seen, this route will only match if the ``{culture}`` portion of
the URL is either ``en`` or ``fr`` and if the ``{year}`` is a number. This
route also shows how you can use a dot between placeholders instead of
a slash. URLs matching this route might look like:

* ``/articles/en/2010/my-post``
* ``/articles/fr/2010/my-post.rss``
* ``/articles/en/2013/my-latest-post.html``

.. _book-routing-format-param:

.. sidebar:: The Special ``_format`` Routing Parameter

    This example also highlights the special ``_format`` routing parameter.
    When using this parameter, the matched value becomes the "request format"
    of the ``Request`` object. Ultimately, the request format is used for such
    things such as setting the ``Content-Type`` of the response (e.g. a ``json``
    request format translates into a ``Content-Type`` of ``application/json``).
    It can also be used in the controller to render a different template for
    each value of ``_format``. The ``_format`` parameter is a very powerful way
    to render the same content in different formats.

.. note::

    Sometimes you want to make certain parts of your routes globally configurable.
    Symfony provides you with a way to do this by leveraging service container
    parameters. Read more about this in ":doc:`/cookbook/routing/service_container_parameters`.

Special Routing Parameters
~~~~~~~~~~~~~~~~~~~~~~~~~~

As you've seen, each routing parameter or default value is eventually available
as an argument in the controller method. Additionally, there are three parameters
that are special: each adds a unique piece of functionality inside your application:

* ``_controller``: As you've seen, this parameter is used to determine which
  controller is executed when the route is matched;

* ``_format``: Used to set the request format (:ref:`read more <book-routing-format-param>`);

* ``_locale``: Used to set the locale on the request (:ref:`read more <book-translation-locale-url>`);

.. index::
   single: Routing; Controllers
   single: Controller; String naming format

.. _controller-string-syntax:

Controller Naming Pattern
-------------------------

Every route must have a ``_controller`` parameter, which dictates which
controller should be executed when that route is matched. This parameter
uses a simple string pattern called the *logical controller name*, which
Symfony maps to a specific PHP method and class. The pattern has three parts,
each separated by a colon:

    **bundle**:**controller**:**action**

For example, a ``_controller`` value of ``AcmeBlogBundle:Blog:show`` means:

+----------------+------------------+-------------+
| Bundle         | Controller Class | Method Name |
+================+==================+=============+
| AcmeBlogBundle | BlogController   | showAction  |
+----------------+------------------+-------------+

The controller might look like this::

    // src/Acme/BlogBundle/Controller/BlogController.php
    namespace Acme\BlogBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;

    class BlogController extends Controller
    {
        public function showAction($slug)
        {
            // ...
        }
    }

Notice that Symfony adds the string ``Controller`` to the class name (``Blog``
=> ``BlogController``) and ``Action`` to the method name (``show`` => ``showAction``).

You could also refer to this controller using its fully-qualified class name
and method: ``Acme\BlogBundle\Controller\BlogController::showAction``.
But if you follow some simple conventions, the logical name is more concise
and allows more flexibility.

.. note::

   In addition to using the logical name or the fully-qualified class name,
   Symfony supports a third way of referring to a controller. This method
   uses just one colon separator (e.g. ``service_name:indexAction``) and
   refers to the controller as a service (see :doc:`/cookbook/controller/service`).

Route Parameters and Controller Arguments
-----------------------------------------

The route parameters (e.g. ``{slug}``) are especially important because
each is made available as an argument to the controller method::

    public function showAction($slug)
    {
      // ...
    }

In reality, the entire ``defaults`` collection is merged with the parameter
values to form a single array. Each key of that array is available as an
argument on the controller.

In other words, for each argument of your controller method, Symfony looks
for a route parameter of that name and assigns its value to that argument.
In the advanced example above, any combination (in any order) of the following
variables could be used as arguments to the ``showAction()`` method:

* ``$culture``
* ``$year``
* ``$title``
* ``$_format``
* ``$_controller``

Since the placeholders and ``defaults`` collection are merged together, even
the ``$_controller`` variable is available. For a more detailed discussion,
see :ref:`route-parameters-controller-arguments`.

.. tip::

    You can also use a special ``$_route`` variable, which is set to the
    name of the route that was matched.

.. index::
   single: Routing; Importing routing resources

.. _routing-include-external-resources:

Including External Routing Resources
------------------------------------

All routes are loaded via a single configuration file - usually ``app/config/routing.yml``
(see `Creating Routes`_ above). Commonly, however, you'll want to load routes
from other places, like a routing file that lives inside a bundle. This can
be done by "importing" that file:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        acme_hello:
            resource: "@AcmeHelloBundle/Resources/config/routing.yml"

    .. code-block:: xml

        <!-- app/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <import resource="@AcmeHelloBundle/Resources/config/routing.xml" />
        </routes>

    .. code-block:: php

        // app/config/routing.php
        use Symfony\Component\Routing\RouteCollection;

        $collection = new RouteCollection();
        $collection->addCollection(
            $loader->import("@AcmeHelloBundle/Resources/config/routing.php")
        );

        return $collection;

.. note::

   When importing resources from YAML, the key (e.g. ``acme_hello``) is meaningless.
   Just be sure that it's unique so no other lines override it.

The ``resource`` key loads the given routing resource. In this example the
resource is the full path to a file, where the ``@AcmeHelloBundle`` shortcut
syntax resolves to the path of that bundle. The imported file might look
like this:

.. configuration-block::

    .. code-block:: yaml

        # src/Acme/HelloBundle/Resources/config/routing.yml
       acme_hello:
            path:     /hello/{name}
            defaults: { _controller: AcmeHelloBundle:Hello:index }

    .. code-block:: xml

        <!-- src/Acme/HelloBundle/Resources/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="acme_hello" path="/hello/{name}">
                <default key="_controller">AcmeHelloBundle:Hello:index</default>
            </route>
        </routes>

    .. code-block:: php

        // src/Acme/HelloBundle/Resources/config/routing.php
        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('acme_hello', new Route('/hello/{name}', array(
            '_controller' => 'AcmeHelloBundle:Hello:index',
        )));

        return $collection;

The routes from this file are parsed and loaded in the same way as the main
routing file.

Prefixing Imported Routes
~~~~~~~~~~~~~~~~~~~~~~~~~

You can also choose to provide a "prefix" for the imported routes. For example,
suppose you want the ``acme_hello`` route to have a final path of ``/admin/hello/{name}``
instead of simply ``/hello/{name}``:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        acme_hello:
            resource: "@AcmeHelloBundle/Resources/config/routing.yml"
            prefix:   /admin

    .. code-block:: xml

        <!-- app/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <import resource="@AcmeHelloBundle/Resources/config/routing.xml"
                prefix="/admin" />
        </routes>

    .. code-block:: php

        // app/config/routing.php
        use Symfony\Component\Routing\RouteCollection;

        $collection = new RouteCollection();

        $acmeHello = $loader->import(
            "@AcmeHelloBundle/Resources/config/routing.php"
        );
        $acmeHello->addPrefix('/admin');

        $collection->addCollection($acmeHello);

        return $collection;

The string ``/admin`` will now be prepended to the path of each route loaded
from the new routing resource.

.. tip::

    You can also define routes using annotations. See the
    :doc:`FrameworkExtraBundle documentation </bundles/SensioFrameworkExtraBundle/annotations/routing>`
    to see how.

Adding a Host Requirement to Imported Routes
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

You can set the host regex on imported routes. For more information, see
:ref:`component-routing-host-imported`.

.. index::
   single: Routing; Debugging

Visualizing & Debugging Routes
------------------------------

While adding and customizing routes, it's helpful to be able to visualize
and get detailed information about your routes. A great way to see every route
in your application is via the ``router:debug`` console command. Execute
the command by running the following from the root of your project.

.. code-block:: bash

    $ php app/console router:debug

This command will print a helpful list of *all* the configured routes in
your application:

.. code-block:: text

    homepage              ANY       /
    contact               GET       /contact
    contact_process       POST      /contact
    article_show          ANY       /articles/{culture}/{year}/{title}.{_format}
    blog                  ANY       /blog/{page}
    blog_show             ANY       /blog/{slug}

You can also get very specific information on a single route by including
the route name after the command:

.. code-block:: bash

    $ php app/console router:debug article_show

Likewise, if you want to test whether a URL matches a given route, you can
use the ``router:match`` console command:

.. code-block:: bash

    $ php app/console router:match /blog/my-latest-post

This command will print which route the URL matches.

.. code-block:: text

    Route "blog_show" matches

.. index::
   single: Routing; Generating URLs

Generating URLs
---------------

The routing system should also be used to generate URLs. In reality, routing
is a bidirectional system: mapping the URL to a controller+parameters and
a route+parameters back to a URL. The
:method:`Symfony\\Component\\Routing\\Router::match` and
:method:`Symfony\\Component\\Routing\\Router::generate` methods form this bidirectional
system. Take the ``blog_show`` example route from earlier::

    $params = $this->get('router')->match('/blog/my-blog-post');
    // array(
    //     'slug'        => 'my-blog-post',
    //     '_controller' => 'AcmeBlogBundle:Blog:show',
    // )

    $uri = $this->get('router')->generate('blog_show', array('slug' => 'my-blog-post'));
    // /blog/my-blog-post

To generate a URL, you need to specify the name of the route (e.g. ``blog_show``)
and any wildcards (e.g. ``slug = my-blog-post``) used in the path for that
route. With this information, any URL can easily be generated::

    class MainController extends Controller
    {
        public function showAction($slug)
        {
            // ...

            $url = $this->generateUrl(
                'blog_show',
                array('slug' => 'my-blog-post')
            );
        }
    }

.. note::

    In controllers that don't extend Symfony's base
    :class:`Symfony\\Bundle\\FrameworkBundle\\Controller\\Controller`,
    you can use the ``router`` service's
    :method:`Symfony\\Component\\Routing\\Router::generate` method::

        use Symfony\Component\DependencyInjection\ContainerAware;

        class MainController extends ContainerAware
        {
            public function showAction($slug)
            {
                // ...

                $url = $this->container->get('router')->generate(
                    'blog_show',
                    array('slug' => 'my-blog-post')
                );
            }
        }

In an upcoming section, you'll learn how to generate URLs from inside templates.

.. tip::

    If the frontend of your application uses Ajax requests, you might want
    to be able to generate URLs in JavaScript based on your routing configuration.
    By using the `FOSJsRoutingBundle`_, you can do exactly that:

    .. code-block:: javascript

        var url = Routing.generate(
            'blog_show',
            {"slug": 'my-blog-post'}
        );

    For more information, see the documentation for that bundle.

.. index::
   single: Routing; Generating URLs in a template

Generating URLs with Query Strings
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The ``generate`` method takes an array of wildcard values to generate the URI.
But if you pass extra ones, they will be added to the URI as a query string::

    $this->get('router')->generate('blog', array('page' => 2, 'category' => 'Symfony'));
    // /blog/2?category=Symfony

Generating URLs from a Template
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

The most common place to generate a URL is from within a template when linking
between pages in your application. This is done just as before, but using
a template helper function:

.. configuration-block::

    .. code-block:: html+jinja

        <a href="{{ path('blog_show', {'slug': 'my-blog-post'}) }}">
          Read this blog post.
        </a>

    .. code-block:: html+php

        <a href="<?php echo $view['router']->generate('blog_show', array(
            'slug' => 'my-blog-post',
        )) ?>">
            Read this blog post.
        </a>

.. index::
   single: Routing; Absolute URLs

Generating Absolute URLs
~~~~~~~~~~~~~~~~~~~~~~~~

By default, the router will generate relative URLs (e.g. ``/blog``). From
a controller, simply pass ``true`` to the third argument of the ``generateUrl()``
method::

    $this->generateUrl('blog_show', array('slug' => 'my-blog-post'), true);
    // http://www.example.com/blog/my-blog-post

From a template, in Twig, simply use the ``url()`` function (which generates an absolute URL)
rather than the ``path()`` function (which generates a relative URL). In PHP, pass ``true``
to ``generateUrl()``:

.. configuration-block::

    .. code-block:: html+jinja

        <a href="{{ url('blog_show', {'slug': 'my-blog-post'}) }}">
          Read this blog post.
        </a>

    .. code-block:: html+php

        <a href="<?php echo $view['router']->generate('blog_show', array(
            'slug' => 'my-blog-post',
        ), true) ?>">
            Read this blog post.
        </a>

.. note::

    The host that's used when generating an absolute URL is automatically
    detected using the current ``Request`` object. When generating absolute
    URLs from outside the web context (for instance in a console command) this
    doesn't work. See :doc:`/cookbook/console/sending_emails` to learn how to
    solve this problem.

Summary
-------

Routing is a system for mapping the URL of incoming requests to the controller
function that should be called to process the request. It both allows you
to specify beautiful URLs and keeps the functionality of your application
decoupled from those URLs. Routing is a bidirectional mechanism, meaning that it
should also be used to generate URLs.

Learn more from the Cookbook
----------------------------

* :doc:`/cookbook/routing/scheme`

.. _`FOSJsRoutingBundle`: https://github.com/FriendsOfSymfony/FOSJsRoutingBundle
