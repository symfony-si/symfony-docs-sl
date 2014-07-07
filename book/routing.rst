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

Lahko naredite katerokoli kompleksno logiko, ki jo potrebujete v izrazu s spreminjanem dveh
spremenljivk, ki sta podani v izraz:

* ``context``: Instanca :class:`Symfony\\Component\\Routing\\RequestContext`,
  ki vsebuje najbolj fundamentalne informacije o usmeritvi, ki se ujema;
* ``request``: Symfony-jev objekt :class:`Symfony\\Component\\HttpFoundation\\Request`
  (glejte :ref:`component-http-foundation-request`).

.. caution::

    Pogoji *niso* vzeti v obzir, ko se generira URL.

.. sidebar:: Izrazi so prevedeni v PHP

    Za kulisjem so izrazi prevedeni v surov PHP. Naš primer
    bi generiral sledeči PHP v direktoriju cache::

        if (rtrim($pathinfo, '/contact') === '' && (
            in_array($context->getMethod(), array(0 => "GET", 1 => "HEAD"))
            && preg_match("/firefox/i", $request->headers->get("User-Agent"))
        )) {
            // ...
        }

    Zaradi tega uporaba ključa ``condition`` ne povzroča dodatnih prekoračitev
    preko časa, ki ga vzame za sestavo PHP-ja za izvrševanje.

.. index::
   single: Routing; Advanced example
   single: Routing; _format parameter

.. _advanced-routing-example:

Napreden primer usmerjevanja
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Na tej točki imate vse, kar potrebujete za izdelavo močnih usmeritvenih
struktur v Symfony. Sledeče je primer kako fleksibilen je lahko
usmerjevalni sistem:

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

Kot ste videli, ta usmeritev se bo ujemala samo, če je ``{culture}`` del
URL-ja ali ``en`` ali ``fr`` in če je ``{year}`` številka. Ta
usmeritev tudi prikazuje, kako lahko uporabite piko med prostorniki namesto
poševnice. URL-ji, ki se ujemajo s to usmeritvijo lahko izgledajo takole:

* ``/articles/en/2010/my-post``
* ``/articles/fr/2010/my-post.rss``
* ``/articles/en/2013/my-latest-post.html``

.. _book-routing-format-param:

.. sidebar:: Poseben usmerjevalni parameter ``_format``

    Ta primer tudi ponazarja poseben usmerjevalni parameter ``_format``.
    Ko uporabljate ta parameter, ujeta vrednost psotane "format zahtevka"
    objekta ``Request``. Na koncu je format zahtevka uporabljen za take
    stvari kot so nastavitev ``Content-Type`` odziva (npr. ``json``
    format zahtevka prevede v ``Content-Type`` od ``application/json``).
    Lahko je uporabljen v krmilniku za izpis različne predloge za
    vsako vrednost od ``_format``. Parameter ``_format`` je zelo močan način
    za izpis enake vsebine v različnih formatih.

.. note::

    Včasih želite narediti določene dele vaših usmeritev globalno nastavljive.
    Symfony vam ponuja način, da to naredite s spreminjanjem parametrov storitvenega kontejnerja.
    Preberite več o tem v ":doc:`/cookbook/routing/service_container_parameters`.

Posebni parametri usmerjanja
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kot ste videli, vsak parameter usmerjanja ali privzeta vrednost je na koncu na voljo
kot argument v metodu krmilnika. Dodatno so na voljo trije parametri,
ki so posebni: vsak doda unikaten del funkcionalnosti znotraj vaše aplikacije:

* ``_controller``: Kot ste videli je ta parameter uporabljen za določanje, kateri
  krmilnik je izvršen, ko se usmeritev ujema;

* ``_format``: Uporabljen za nastavitev formata zahtevka (:ref:`preberite več <book-routing-format-param>`);

* ``_locale``: Uporabljen za nastavitev lokalizacije na zahtevku (:ref:`preberite več <book-translation-locale-url>`);

.. index::
   single: Routing; Controllers
   single: Controller; String naming format

.. _controller-string-syntax:

Vzorci poimenovanja krmilnika
-----------------------------

Vsaka usmeritev mora imeti parameter ``_controller``, ki diktira, kateri
krmilnik bi moral biti izvršen, ko je ta usmeritev ujeta. Ta parameter
uporablja enostaven vzorec niza imenovan *logično ime krmilnika*, katerega
Symfony preslika v določeno PHP metodo in razred. Vzorec ima tri dele,
vsak ločen z dvopičjem:

    **bundle**:**controller**:**action**

Na primer, vrednost ``_controller`` od ``AcmeBlogBundle:Blog:show`` pomeni:

+----------------+------------------+-------------+
| Paket          | Razred krmilnika | Ime metode  |
+================+==================+=============+
| AcmeBlogBundle | BlogController   | showAction  |
+----------------+------------------+-------------+

Krmilnik lahko izgleda takole::

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

Bodite pozorni, ker Symfony doda niz ``Controller`` imenu razreda (``Blog``
=> ``BlogController``) in ``Action`` imenu metode (``show`` => ``showAction``).

Lahko bi se tudi sklicevali na ta krmilnik z uporabo njegovega polno-kvalificiranega imena razreda
in metode: ``Acme\BlogBundle\Controller\BlogController::showAction``.
Vendar, če sledite nekaterim enostavnim konvencijam, je logično ime bolj ustrezno
in omogoča več fleksibilnosti.

.. note::

   Kot dodatek uporabi logičnega imena ali polno-kvalificiranega imena razreda
   Symfony podpira tretji način sklicevanja na krmilnik. Ta metoda
   uporablja samo eno ločilo podpičja (npr. ``service_name:indexAction``) in
   se sklicuje na krmilnik kot storitev (glejte :doc:`/cookbook/controller/service`).

Parametri usmeritve in argumenti krmilnika
------------------------------------------

Parametri usmerjevalnika (npr. ``{slug}``) so posebej pomembni, ker
je vsak na voljo kot argument metodi krmilnika::

    public function showAction($slug)
    {
      // ...
    }

V realnosti je celotna zbirka ``defaults`` združena z vrednostmi
parametrov, da oblikujejo posamezno polje. Vsak ključ tega polja je na voljo kot
argument na krmilniku.

Z drugimi besedami, za vsak argument vaše metode krmilnika, Symfony pogleda
za parametrom usmeritvije tega imena in določi njegovo vrednost temu argumentu.
V naprednem primeru zgoraj, kakršnakoli kombinacija (v kateremkoli vrstnem redu) sledečih
spremenljivk bi lahko bila uporabljena kot argumenti metode ``showAction()``:

* ``$culture``
* ``$year``
* ``$title``
* ``$_format``
* ``$_controller``

Ker so prostorniki in zbirka ``defaults`` združeni skupaj, je na voljo celo
spremenljivka ``$_controller``. Za več podrobnih debat
glejte :ref:`route-parameters-controller-arguments`.

.. tip::

    Lahko uporabite tudi posebno spremenljivko ``$_route``, ki je nastavljena na
    ime usmeritve, ki je bila ujeta.

.. index::
   single: Routing; Importing routing resources

.. _routing-include-external-resources:

Vključevanje zunanjih virov usmerjanja
--------------------------------------

Vse usmeritve so naložene preko ene nastavitvene datoteke - običajno ``app/config/routing.yml``
(glejte `Ustvarjanje usmeritev`_ zgoraj). Pogosto vendar boste oa želeli naložiti usmeritve
iz drugih prostorov, kot je usmeritvena datoteka, ki se nahaja znotraj paketa. To se lahko
naredi z "uvažanjem" te datoteke:

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

   Ko uvažate vire iz YAML, je ključ (npr. ``acme_hello``) nepomemben.
   Bodite samo prepričani, da je unikaten, tako da ga nobene druge vrstice ne prepišeno.

Ključ ``resource`` naloži dani usmeritveni vir. V tem primeru je
vir celotna pot do datoteke, kjer je ``@AcmeHelloBundle`` bližnjica
sintakse, ki rešuje pot tega paketa. Uvožena datoteka lahko izgleda
takole:

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

Usmeritve iz te datoteke so razčlenjene in naložene na enak način kot glavna
usmeritvena datoteka.

Dodajanje predpon uvoženim usmeritvam
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Lahko tudi izberete ponuditi "predpono" za uvožene usmeritve. Na primer
predpostavimo, da želite, da ima usmeritev ``acme_hello`` končno pot ``/admin/hello/{name}``
namesto enostavno ``/hello/{name}``:

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

Niz ``/admin`` bo sedaj pripet poti vsake usmeritve, ki je naložena
iz novega vira usmeritve.

.. tip::

    Usmeritve lahko tudi definirate z uporabo anotacij. Glejte
    :doc:`dokumentacijo FrameworkExtraBundle </bundles/SensioFrameworkExtraBundle/annotations/routing>`,
    da vidite kako.

Dodajanje zahteve gostitelja uvoženim usmeritvam
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Nastavite lahko regex gostitelja na uvoženih usmeritvah. Za več informacij, glejte
:ref:`component-routing-host-imported`.

.. index::
   single: Routing; Debugging

Vizualiziranje & razhroščevanje usmeritev
-----------------------------------------

Medtem ko dodajate in prilagajate usmeritve, je v pomoč zmožnost vizualizirati
in dobiti podrobne informacije o vaših usmeritvah. Odličen način, da vidite vsako usmeritev
v vaši aplikaciji, je preko konzolnega ukaza ``router:debug``. Izvršite
ukaz s pogonom sledečega iz vrha vašega projekta.

.. code-block:: bash

    $ php app/console router:debug

Ta ukaz bo izpisal pomagalen seznam *vseh* nastavljenih usmeritev v
vaši aplikaciji:

.. code-block:: text

    homepage              ANY       /
    contact               GET       /contact
    contact_process       POST      /contact
    article_show          ANY       /articles/{culture}/{year}/{title}.{_format}
    blog                  ANY       /blog/{page}
    blog_show             ANY       /blog/{slug}

Lahko tudi dobite zelo specifične informacije na eni usmeritvi z vključevanjem
imena usmeritve po ukazu:

.. code-block:: bash

    $ php app/console router:debug article_show

Enako, če želite testirati ali se URL ujema z dano usmeritvijo, lahko
uporabite konzolni ukaz ``router:match``:

.. code-block:: bash

    $ php app/console router:match /blog/my-latest-post

Ta ukaz bo izpisal, s katero usmeritvijo se URL ujema.

.. code-block:: text

    Route "blog_show" matches

.. index::
   single: Routing; Generating URLs

Generiranje URL-jev
-------------------

Sistem usmerjanja bi moral biti uporabljen tudi za generiranje URL-jev. V realnosti je usmerjenje
bidirektivni sistem: URL preslika v krmilnik+parametre in
usmeritev+parametre nazaj v URL.
Metodi :method:`Symfony\\Component\\Routing\\Router::match` in
:method:`Symfony\\Component\\Routing\\Router::generate` oblikujeta ta bidirektivni
sistem. Vzamite primer usmeritve ``blog_show`` iz prej::

    $params = $this->get('router')->match('/blog/my-blog-post');
    // array(
    //     'slug'        => 'my-blog-post',
    //     '_controller' => 'AcmeBlogBundle:Blog:show',
    // )

    $uri = $this->get('router')->generate('blog_show', array('slug' => 'my-blog-post'));
    // /blog/my-blog-post

Za generiranje URL-ja, potrebujete določiti ime usmeritve (npr. ``blog_show``)
in katerikoli nadomestni znak (npr. ``slug=my-blog-post``) uporabljen v poti za to
usmeritev. S temi informacijami je lahko katerikoli URL enostavno generiran::

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

    V krmilnikih, ki ne razširjajo Symfony-jevega osnobnega
    :class:`Symfony\\Bundle\\FrameworkBundle\\Controller\\Controller`,
    lahko uporabite ``router`` storitveno
    metodo :method:`Symfony\\Component\\Routing\\Router::generate`::

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

V prihajajoči sekciji se boste naučili kako generirati URL-je iz znotraj predlog.

.. tip::

    Če ospredje vaše aplikacije uporablja zahtevke Ajax, lahko morda želite
    biti zmožni generirati URL-je na JavaScript osnovi na vaši usmeritveni nastavitvi.
    Z uporabo `FOSJsRoutingBundle`_, lahko naredite točno to:

    .. code-block:: javascript

        var url = Routing.generate(
            'blog_show',
            {"slug": 'my-blog-post'}
        );

    Za več informacij, glejte dokumentacijo za ta paket.

.. index::
   single: Routing; Generating URLs in a template

Generiranje URL-jev z nizi poizvedb
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Metoda ``generate`` vzame polje vrednosti nadomestnih znakov, da generira URI.
Vendar če podate dodatno, bodo dodani URI-ju kot niz poizvedbe::

    $this->get('router')->generate('blog', array('page' => 2, 'category' => 'Symfony'));
    // /blog/2?category=Symfony

Generiranje URL-jev iz predloge
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Najpogostejši prostor za generiranje URL-ja je iz znotraj predloge, ko povezujete
med stranmi v vaši aplikaciji. To je lahko narejeno tako kot prej, vendar z uporabo
pomagalne funkcije predloge:

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

Generiranje absolutnh URL-jev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Privzeto bo usmerjevalnik generiral relativne URL-je (npr. ``/blog``). Iz
krmilnika enostavno podajte ``true`` tretjemu argumentu metode
``generateUrl()``::

    $this->generateUrl('blog_show', array('slug' => 'my-blog-post'), true);
    // http://www.example.com/blog/my-blog-post

Iz predloge v Twig-u enostavno uporabite funkcijo ``url()`` (ki generira absolutin URL)
namesto funkcije ``path()`` (ki generira relativni URL). V PHP podajte ``true``
za ``generateUrl()``:

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

    Gostitelj, ki je uporabljen, ko se generira absolutni URL je avtomatično
    najden z uporabo trenutnega objekta ``Request``. Ko generirate absolutne
    URL-je iz zunaj spletnega konteksta (na primer v konzolnem ukazu), to
    ne deluje. Glejte :doc:`/cookbook/console/sending_emails`, da se naučite, kako
    rešiti ta problem.

Povzetek
--------

Usmerjanje je sistem za preslikavo URL-ja prihajajočih zahtevkov v funckijo
krmilnika, ki bi moral biti imenovan za procesiranje zahtevka. Le ta omogoča tako
določanje lepih URL-jev kot tudi obdrži funkcionalnost vaše aplikacije
ločeno od teh URL-jev. Usmerjanje je bidirektivni mehanizem, kar pomeni, da
bi moral biti uporabljen za generiranje URL-jev.

Naučite se več iz knjige receptov
---------------------------------

* :doc:`/cookbook/routing/scheme`

.. _`FOSJsRoutingBundle`: https://github.com/FriendsOfSymfony/FOSJsRoutingBundle
