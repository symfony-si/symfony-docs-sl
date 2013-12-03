Symfony2 napram samo PHP
========================

**Zakaj je Symfony2 boljši kot samo odprtje datoteke in pisanje samo PHP-ja?**

Če še nikoli niste uporabljali PHP ogrodja, ste seznanjeni z MVC filozofijo,
ali se samo sprašujete, kaj je ves ta t.i. *hype* okrog Symfony2, to poglavje je za
vas. Namesto, da vam *povemo*, da vam Symfony2 omogoča razvijati hitrejšo in
boljšo programsko opremo, kot samo s PHP, boste to videli sami.

V tem poglavju, boste napisali preprosto aplikacijo samo v PHP in jo nato
pretvorili, da bo bolj organizirana. Potovali boste skozi čas, videli
odločitve za tem, zakaj se je spletni razvoj razvil tekom nekaj zadnjih let
do tega kar je sedaj.

Do konca, boste videli, kako vas Symfony2 lahko reši iz vsakdanjih opravil in
vam omogoča dobiti nazaj kontrolo nad vašo kodo.

Enostaven blog samo v PHP
-------------------------

V tem poglavju, boste zgradili simbolično blog aplikacijo z uporabo samo PHP-ja.
Da pričnete, ustvarite eno stran, ki prikaže vnose bloga, ki so bili
dodani v podatkovno bazo. Pisanje samo v PHP je hitro in grdo:

.. code-block:: html+php

    <?php
    // index.php
    $link = mysql_connect('localhost', 'myuser', 'mypassword');
    mysql_select_db('blog_db', $link);

    $result = mysql_query('SELECT id, title FROM post', $link);
    ?>

    <!DOCTYPE html>
    <html>
        <head>
            <title>List of Posts</title>
        </head>
        <body>
            <h1>List of Posts</h1>
            <ul>
                <?php while ($row = mysql_fetch_assoc($result)): ?>
                <li>
                    <a href="/show.php?id=<?php echo $row['id'] ?>">
                        <?php echo $row['title'] ?>
                    </a>
                </li>
                <?php endwhile; ?>
            </ul>
        </body>
    </html>

    <?php
    mysql_close($link);
    ?>

To je hitro za napisati, hitro za izvršiti in kot bo vaša aplikacija rasla nemogoče
vzdrževati. Obstaja nekaj problemov, ki jih je potrebno izpostaviti:

* **Ni preverjanja napak**: Kaj če povezava s podatkovno bazo ne uspe?

* **Slaba organizacija**: Če aplikacija zraste, bo ta ena datoteka postala
  naraščajoče nevzdržljiva. Kam bi morali dati kodo za upravljanje pošiljanja
  obrazca? Kako lahko potrdite podatke? Kam bi morala iti koda za pošiljanje
  e-pošte?
  emails?

* **Otežena ponovna uporaba kode**: Ker je vse v eni datoteki, ni
  načina za ponovno uporabo kateregakoli dela aplikacije za ostale strani bloga.

.. note::

    Drug problem, ki ni tu omenjen je dejstvo, da je podatkovna baza
    vezana na MySQL. Čeprav to ni tu pokrito, Symfony2 v celoti integrira `Doctrine`_,
    knjižnico namenjeno abstrakciji podatkovne baze in preslikavam.

Pojdimo na delo reševanja teh problemov in več.

Izolacija predstavitve
~~~~~~~~~~~~~~~~~~~~~~

Koda lahko takoj pridobi iz ločitve aplikacijske "logike" iz
kode, ki prirpavi HTML "predstavitev":

.. code-block:: html+php

    <?php
    // index.php
    $link = mysql_connect('localhost', 'myuser', 'mypassword');
    mysql_select_db('blog_db', $link);

    $result = mysql_query('SELECT id, title FROM post', $link);

    $posts = array();
    while ($row = mysql_fetch_assoc($result)) {
        $posts[] = $row;
    }

    mysql_close($link);

    // include the HTML presentation code
    require 'templates/list.php';

HTML koda je sedaj shranjena v ločeni datoteki (``templates/list.php``), ki
je v osnovi HTML datoteka, ki uporablja PHP sintakso podobno predlogam:

.. code-block:: html+php

    <!DOCTYPE html>
    <html>
        <head>
            <title>List of Posts</title>
        </head>
        <body>
            <h1>List of Posts</h1>
            <ul>
                <?php foreach ($posts as $post): ?>
                <li>
                    <a href="/read?id=<?php echo $post['id'] ?>">
                        <?php echo $post['title'] ?>
                    </a>
                </li>
                <?php endforeach; ?>
            </ul>
        </body>
    </html>

Glede na konvencije datoteka, ki vsebuje vso aplikacijsko logiko - ``index.php`` -
je znana kot "krmilnik". Izraz :term:`krmilnik` je beseda, ki jo boste slišali
velikokrat, ne glede na jezik ali ogrodje, ki ga uporabljate. Nanaša se enostavno na
področje *vaše* kode, ki procesira uporabniški vnos in pripravi odziv.

V tem primeru, krmilnik pripravi podatke iz podatkovne baze in nato vključi
predlogo za predstavitev teh podatkov. Z izoliranim krmilnikom, lahko
enostavno spremenite *samo* predlogo datoteke, če potrebujete izpisati vnose
bloga v drugih formatih (npr. ``list.json.php`` za JSON format).

Izolacija aplikacijske (domenske) logike
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sedaj aplikacija vsebuje samo eno stran. Vendar kaj če je druga stran potrebna
za uporabo iste povezave podatkovne baze, ali celo enakega polja objav
bloga? Pretvarjanje kode, da bodo koda jedra in funkcije dostopanja do podatkov
aplikacije izolirani v novi datoteki imenovani ``model.php``:

.. code-block:: html+php

    <?php
    // model.php
    function open_database_connection()
    {
        $link = mysql_connect('localhost', 'myuser', 'mypassword');
        mysql_select_db('blog_db', $link);

        return $link;
    }

    function close_database_connection($link)
    {
        mysql_close($link);
    }

    function get_all_posts()
    {
        $link = open_database_connection();

        $result = mysql_query('SELECT id, title FROM post', $link);
        $posts = array();
        while ($row = mysql_fetch_assoc($result)) {
            $posts[] = $row;
        }
        close_database_connection($link);

        return $posts;
    }

.. tip::

   Ime datoteke ``model.php`` je uporabljeno, ker logika in dostopanje do podatkov
   aplikacije, glavnina kode ponovno predstavlja vašo "poslovno logiko"
   bi morala obstojati v modelu (nasprotno od obstojanja v krmilniku). In kot ni
   v tem primeru, samo del (ali nič) od modela se dejansko ne tiče
   dostopanja do podatkovne baze.

Krmilnik (``index.php``) je sedaj zelo enostaven:

.. code-block:: html+php

    <?php
    require_once 'model.php';

    $posts = get_all_posts();

    require 'templates/list.php';

Sedaj osnovna naloga krmilnika je dobiti podatke iz nivoja modela
aplikacije (model) in klicati predlogo, da izpiše te podatke.
To je zelo enostaven primer model-ogled-krmilnik (MVC) vzorca.

Izolacija postavitve
~~~~~~~~~~~~~~~~~~~~

Na tej točki je bila aplikacija pretvorjena v tri ločene dele,
ki ponujajo različne prednosti in priložnosti za ponovno uporabo skoraj vsega
na različnih straneh.

Edini del kode, ki *ne more* biti ponovno uporabljen je postavitev strani. Popravimo
to z izdelavo nove ``layout.php`` datoteke:

.. code-block:: html+php

    <!-- templates/layout.php -->
    <!DOCTYPE html>
    <html>
        <head>
            <title><?php echo $title ?></title>
        </head>
        <body>
            <?php echo $content ?>
        </body>
    </html>

Predloga (``templates/list.php``) je sedaj lahko poenostavljena za "razširitev"
postavitve:

.. code-block:: html+php

    <?php $title = 'List of Posts' ?>

    <?php ob_start() ?>
        <h1>List of Posts</h1>
        <ul>
            <?php foreach ($posts as $post): ?>
            <li>
                <a href="/read?id=<?php echo $post['id'] ?>">
                    <?php echo $post['title'] ?>
                </a>
            </li>
            <?php endforeach; ?>
        </ul>
    <?php $content = ob_get_clean() ?>

    <?php include 'layout.php' ?>

Sedaj ste predstavili metodologijo, ki omogoča ponovno uporabo
postavitve. Na žalost, da to dosežemo, ste prisiljeni uporabiti nekaj grdih
PHP funkcij (``ob_start()``, ``ob_get_clean()``) v predlogi. Symfony2
uporablja komponento ``Templating``, ki omogoča to narediti čisteje
in enostavneje. Videli boste to v akciji v kratkem.

Dodajanje "show" blog strani
----------------------------

Blog stran "list" je bila sedaj pretvorjena, da je koda bolje organizirana
in ponovno uporabna. Da to dokažemo, dodajte blog stran "show", ki prikaže individualno
blog objavo identificirano z ``id`` parametrom poizvedbe.

Da pričnete, izdelajte novo funkcijo v ``model.php`` datoteki, ki prinaša
individualne rezultate bloga na osnovi danega id::

    // model.php
    function get_post_by_id($id)
    {
        $link = open_database_connection();

        $id = intval($id);
        $query = 'SELECT date, title, body FROM post WHERE id = '.$id;
        $result = mysql_query($query);
        $row = mysql_fetch_assoc($result);

        close_database_connection($link);

        return $row;
    }

Nato ustvarite novo datoteko imenovano ``show.php`` - krmilnik za to novo
stran:

.. code-block:: html+php

    <?php
    require_once 'model.php';

    $post = get_post_by_id($_GET['id']);

    require 'templates/show.php';

Na koncu ustvarite novo datoteko predloge - ``templates/show.php`` - da izpišete
individualno blog objavo:

.. code-block:: html+php

    <?php $title = $post['title'] ?>

    <?php ob_start() ?>
        <h1><?php echo $post['title'] ?></h1>

        <div class="date"><?php echo $post['date'] ?></div>
        <div class="body">
            <?php echo $post['body'] ?>
        </div>
    <?php $content = ob_get_clean() ?>

    <?php include 'layout.php' ?>

Izdelava druge strani je sedaj zelo enostavna in nobena koda ni duplicirana. Še vedno
ta stran predstavlja celo bolj dolgotrajnih problemov, ki jih ogrodje lahko rešuje
za vas. Na primer manjkajoči ali napačni parameter poizvedbe ``id`` bo povzročil,
da se stran polomi. Boljše bi bilo, če bi to povzročilo, da je 404 stran izpisana,
vendar to v resnici še ne more biti narejeno. Še hujše je, če ste pozabili počistiti
parameter ``id`` preko funkcije ``intval()``, saj bo vaša
celotna podatkovna baza lahko tveganjem pred napadom SQL injiciranja.

Drug glavni problem je, da vsaka datoteka individualnega krmilnika, mora vključiti
datoteko ``model.php``. Kaj če vsaka datotekoa krmilnika nenadoma potrebuje vključevati
dodatno datoteko ali izvesti neko drugo globalno opravilo (npr. vsiliti varnost)?
Kot je izpostavljeno, ta koda bi morala biti dodana k vsaki datoteki krmilnika.
Če pozabite vključiti nekaj v eni datoteki, se na srečo ne nanaša
na varnost ...

"Prednji krmilnik" na pomoč
---------------------------

Rešitev je uporaba :term:`prednjega krmilnika`: ene PHP datoteke skozi
katero so *vsi* zahtevki procesirani. S prednjim krmilnikom, URI-ji za
aplikacijo se malenkost spremenijo, vendar pričnejo postajati bolj fleksibilni:

.. code-block:: text

    Without a front controller
    /index.php          => Blog post list page (index.php executed)
    /show.php           => Blog post show page (show.php executed)

    With index.php as the front controller
    /index.php          => Blog post list page (index.php executed)
    /index.php/show     => Blog post show page (index.php executed)

.. tip::
    Del ``index.php`` URI-ja je lahko odstranjen, če uporabljate Apache-jeva
    prepisovalna pravila (ali podobno). V tem primeru bi bil rezultirajoči URI
    show strani bloga enostavno ``/show``.

Ko uporabljate prednji krmilnik, ena PHP datoteka (``index.php`` v tem primeru)
izpiše *vsak* zahtevek. Za show stran bloga, ``/index.php/show`` bo
dejansko izvedel ``index.php`` datoteko, ki je odgovorna za usmerjanje
zahtevkov interno na osnovi celotnega URI-ja. Kot boste videli, je prednji krmilnik
zelo močno orodje.

Izdelava prednjega krmilnika
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ste pred tem, da naredite **velik** korak z aplikacijo. Z eno datoteko, ki upravlja
vse zahtevke, lahko centralizirate stvari kot so upravljanje varnosti, nalaganje nastavitev
in usmerjanje. V tej aplikaciji, mora ``index.php`` biti dovolj
pameten, da izpiše stran s seznamom objav bloga *ali* stran prikaza objave bloga na osnovi
zahtevanega URI-ja:

.. code-block:: html+php

    <?php
    // index.php

    // load and initialize any global libraries
    require_once 'model.php';
    require_once 'controllers.php';

    // route the request internally
    $uri = $_SERVER['REQUEST_URI'];
    if ('/index.php' == $uri) {
        list_action();
    } elseif ('/index.php/show' == $uri && isset($_GET['id'])) {
        show_action($_GET['id']);
    } else {
        header('Status: 404 Not Found');
        echo '<html><body><h1>Page Not Found</h1></body></html>';
    }

Za organizacijo obeh krmilnikom (prej ``index.php`` in ``show.php``)
so sedaj PHP funkcije in vsaka je bila premaknjena v ločeno datoteko ``controllers.php``:

.. code-block:: php

    function list_action()
    {
        $posts = get_all_posts();
        require 'templates/list.php';
    }

    function show_action($id)
    {
        $post = get_post_by_id($id);
        require 'templates/show.php';
    }

Kot prednji krmilnik, ``index.php`` je prevzel v celoti novo vlogo, prva je ta,
da vključuje nalaganje knjižnic jedra in druga usmerjanje aplikacije, da
je eden izmed dveh krmilnikov (``list_action()`` in ``show_action()``
funkciji) klican. V realnosti je prednji krmilnik pričenja izgledati in
se izvaja precej podobno kot v Symfony2 mehanizmu za upravljanje in usmerjanje zahtevkov.

.. tip::

   Druga prednost prednjega krmilnika je fleksibilnost URL-jev. Bodite pozorni, da
   URL na prikazno stran objave bloga je lahko spremenjen iz ``/show`` v ``/read``
   s spreminjanjem kode na samo eni lokaciji. Preden je celotna datoteka potrebna
   preimenovanja. V Symfony2 so URL-ji celo še bolj fleksibilni.

Do sedaj se je aplikacija razvija iz ene PHP datoteke v strukturo,
ki je organizirana in omogoča ponovno uporabo kode. Morali bi biti bolj veseli, vendar
daleč od zadovoljstva. Na primer, usmerjevalni sistem je pomankljiv in ne bi prepoznal,
da stran s seznamom (``/index.php``) bi morala biti dostopna tudi preko ``/``
(če so dodana Apache-jeva prepisovalna pravila). Tudi namesto razvoja bloga
veliko časa porabljenega na delu "arhitekture" kode (npr.
usmerjanja, klicanja krmilnikov, predloge itd.). Več časa bo potrebnega
porabiti za upravljanje pošiljanja obrazcev, preverjanja vnosov, beleženja in varnosti.
Zakaj bi morali ponovno izumljati rešitve za vse te rutinske probleme?

Dodajte dotik Symfony2
~~~~~~~~~~~~~~~~~~~~~~

Symfony2 na pomoč. Preden dejansko uporabite Symfony, ga morate prenesti.
To se lahko naredi z uporabo Composer-ja, ki poskrbi za prenašanje
ustrezne verzije in vseh njegovih odvisnosti in ponuja avtomatski nalagalnik.
Avtomatski nalagalnik je orodje, ki naredi mogoč začetek uporabe PHP razredov
brez eksplicitnega vključevanja datoteke, ki vsebuje razred.

V vašem vrhnjem direktoriju, izdelajte ``composer.json`` datoteko s sledečo
vsebino:

.. code-block:: json

    {
        "require": {
            "symfony/symfony": "2.3.*"
        },
        "autoload": {
            "files": ["model.php","controllers.php"]
        }
    }

Naslednje `prenesite Composer`_ in nato poženite sledeči ukaz, ki bo prenesel Symfony
v vendor/ direktorij:

.. code-block:: bash

    $ php composer.phar install

Poleg prenosa vaših odvisnosti, Composer generira ``vendor/audoload.php`` datoteko,
ki poskrbi za avtomatsko nalaganje vseh datotek v Symfony ogrodju kot tudi
datotek omenjenih v avtomatski sekciji vašega ``composer.json``.

Jedro Symfony filozofije je ideja, da je glavna naloga aplikacije
interpretacija vsakega zahtevka in vračanje odziva. Do tu, Symfony2 ponuja
oba, :class:`Symfony\\Component\\HttpFoundation\\Request` in
:class:`Symfony\\Component\\HttpFoundation\\Response` razred. Te razred so
objektno orientirane reprezentacije surovih HTTP zahtevkov, ki so procesirani in
HTTP odziv vrnjen. Uporabite jih za izboljšavo bloga:

.. code-block:: html+php

    <?php
    // index.php
    require_once 'vendor/autoload.php';

    use Symfony\Component\HttpFoundation\Request;
    use Symfony\Component\HttpFoundation\Response;

    $request = Request::createFromGlobals();

    $uri = $request->getPathInfo();
    if ('/' == $uri) {
        $response = list_action();
    } elseif ('/show' == $uri && $request->query->has('id')) {
        $response = show_action($request->query->get('id'));
    } else {
        $html = '<html><body><h1>Page Not Found</h1></body></html>';
        $response = new Response($html, Response::HTTP_NOT_FOUND);
    }

    // echo the headers and send the response
    $response->send();

.. versionadded:: 2.4
    Podpora za konstante HTTP statusnih kod je bila dodana v Symfony 2.4.

Krmilniki so sedaj odgovorni za vračanje ``Response`` objekta.
Da to naredite enostavnejše, lahko dodate novo ``render_template()`` funkcijo, ki
mimogrede deluje precej podobno kot Symfony2 motor predlog:

.. code-block:: php

    // controllers.php
    use Symfony\Component\HttpFoundation\Response;

    function list_action()
    {
        $posts = get_all_posts();
        $html = render_template('templates/list.php', array('posts' => $posts));

        return new Response($html);
    }

    function show_action($id)
    {
        $post = get_post_by_id($id);
        $html = render_template('templates/show.php', array('post' => $post));

        return new Response($html);
    }

    // helper function to render templates
    function render_template($path, array $args)
    {
        extract($args);
        ob_start();
        require $path;
        $html = ob_get_clean();

        return $html;
    }

S prinesenjem majhnega dela Symfony2 je aplikacija bolj fleksibilna in
zanesljiva. ``Request`` ponuja zanesljiv način dostopanja informacij
o HTTP zahtevku. Posebej ``getPathInfo()`` metoda vrne
očiščen URI (vedno vrača ``/show`` in nikoli ``/index.php/show``).
Torej tudi če uporabnik gre na ``index.php/show``, je aplikacija dovolj inteligentna,
da usmeri zahtevke skozi ``show_action()``.

``Response`` objekt da fleksibilnost, ko se konstruira HTTP odziv,
omogoča HTTP glavam in vsebini, da je dodana preko objektno orientiranega vmesnika.
In medtem ko odzivi v tej aplikaciji so enostavni, se bo ta fleksibilnost
izplačala, ko bo vaša aplikacija zrasla.

Primer aplikacije v Symfony2
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Blog je prišel *daleč*, vendar še vedno vsebuje veliko kode za tako
enostavno aplikacijo. Tekom poti ste naredili enostavni usmerjevalni
sistem in metodo, ki uporablja ``ob_start()`` in ``ob_get_clean()`` za izpis
predlog. Če boste zaradi kakšnega razloga potrebovali nadaljevati gradnjo tega "ogrodja"
od začetka, lahko vsaj uporabite Symfony-jevi samostoječi `Routing`_ in
`Templating`_ komponenti, ki že rešujeta te probleme.

Namesto ponovnega reševanja pogostih problemov, lahko pustite Symfony2, da
poskrbi zanje namesto vas. Tu je primer aplikacije, sedaj zgrajene v Symfony2::

    // src/Acme/BlogBundle/Controller/BlogController.php
    namespace Acme\BlogBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;

    class BlogController extends Controller
    {
        public function listAction()
        {
            $posts = $this->get('doctrine')->getManager()
                ->createQuery('SELECT p FROM AcmeBlogBundle:Post p')
                ->execute();

            return $this->render(
                'AcmeBlogBundle:Blog:list.html.php',
                array('posts' => $posts)
            );
        }

        public function showAction($id)
        {
            $post = $this->get('doctrine')
                ->getManager()
                ->getRepository('AcmeBlogBundle:Post')
                ->find($id)
            ;

            if (!$post) {
                // cause the 404 page not found to be displayed
                throw $this->createNotFoundException();
            }

            return $this->render(
                'AcmeBlogBundle:Blog:show.html.php',
                array('post' => $post)
            );
        }
    }

Dva krmilnika sta še vedno lahka. Vsak uporablja :doc:`Doctrine ORM knjižnico </book/doctrine>`
za pridobivanje objektov iz podatkovne baze in komponento ``Templating`` za
izpis in vračanje ``Response`` objekta. Predloga seznama je
sedaj precej bolj enostavna:

.. code-block:: html+php

    <!-- src/Acme/BlogBundle/Resources/views/Blog/list.html.php -->
    <?php $view->extend('::layout.html.php') ?>

    <?php $view['slots']->set('title', 'List of Posts') ?>

    <h1>List of Posts</h1>
    <ul>
        <?php foreach ($posts as $post): ?>
        <li>
            <a href="<?php echo $view['router']->generate(
                'blog_show',
                array('id' => $post->getId())
            ) ?>">
                <?php echo $post->getTitle() ?>
            </a>
        </li>
        <?php endforeach; ?>
    </ul>

Postavitev je skoraj identična:

.. code-block:: html+php

    <!-- app/Resources/views/layout.html.php -->
    <!DOCTYPE html>
    <html>
        <head>
            <title><?php echo $view['slots']->output(
                'title',
                'Default title'
            ) ?></title>
        </head>
        <body>
            <?php echo $view['slots']->output('_content') ?>
        </body>
    </html>

.. note::

    Prikazna predloga je prepuščena vam kot vaja, saj bi morala biti trivialna za
    narediti na osnovi predloge seznama.

Ko se motor Symfony2 (imenovam ``Kernel``) zažene, potrebuje zemljevid, da
ve, katere krmilnike izvršiti na osnovi informacij zahtevka.
Zemljevid nastavitev usmerjanja ponuja te informacije v bralnem formatu:

.. code-block:: yaml

    # app/config/routing.yml
    blog_list:
        path:     /blog
        defaults: { _controller: AcmeBlogBundle:Blog:list }

    blog_show:
        path:     /blog/show/{id}
        defaults: { _controller: AcmeBlogBundle:Blog:show }

Sedaj ko Symfony2 upravlja vse vsakdanje naloge, je prednji krmilnik
popolnoma enostaven. In ker naredi toliko malo, se vam ga nikoli ne bo treba dotakniti,
ko je enkrat narejen (in če uporabljate Symfony2 distribucijo, ga ne boste niti
potrebovali izdelati!)::

    // web/app.php
    require_once __DIR__.'/../app/bootstrap.php';
    require_once __DIR__.'/../app/AppKernel.php';

    use Symfony\Component\HttpFoundation\Request;

    $kernel = new AppKernel('prod', false);
    $kernel->handle(Request::createFromGlobals())->send();

Edina naloga prednjega krmilnika je inicializacija motorja Symfony2 (``Kernel``)
in pošiljanje njega v ``Request`` objekt za upravljanje. Symfony2 jedro nato uporablja
usmerjevalni zemljevid za ugotovitev, kateri krmilnik klicati. Enako kot prej
je metoda krmilnika odgovorna za vračanje končnega ``Response`` objekta.
Res ni veliko drugega k temu.

Za vizualno reprezentacijo kako Symfoyn2 upravlja vsak zahtevek, glejte
:ref:`diagram toka zahtevka <request-flow-figure>`.

Kam Symfony2 dostavlja
~~~~~~~~~~~~~~~~~~~~~~

V prihajajočih poglavjih, boste izvedeli več o tem, kako vsak del Symfony-ja
deluje in priporočeno organizacijo projekta. Za sedaj poglejmo, kako
migracija bloga iz samo PHP-ja v Symfony2 izboljša življenje:

* Vaša aplikacija ima sedaj **jasno in konsistentno organizirano kodo** (čeprav
  Symfony vas ne sili v to). To promovira **ponovno uporabo** in
  omogoča novim razvijalcem, da so hitreje produktivni v vašem projektu;

* 100% kode, ki jo napišete je za *vašo* aplikacijo. **Ne potrebujete
  razvijati ali vzdrževati nizko nivojskih orodij** kot je :ref:`avtomatsko nalaganje <autoloading-introduction-sidebar>`,
  :doc:`usmerjanje </book/routing>`, ali izpisovanje :doc:`krmilnikov </book/controller>`;

* Symfony2 vam da **dostop, da odprete izvorna orodja** kot so Doctrine in
  Templating, Security, Form, Validation in Translation komponente (da jih naštejemo
  samo nekaj);

* Aplikacija sedaj uživa **polno-fleksibilne URL-je** zahvaljhujoč ``Routing``
  komponenti;

* HTTP centrična Symfony2 arhitektura vam da dostop do močnih orodij
  kot je **HTTP predpomnenje**, ki ga poganja **Symfony2 interni HTTP predpomnilnik** ali
  bolj močna orodja, kot je `Varnish`_. To je pokrito v kasnejšem poglavju
  vse o :doc:`predpomnenju </book/http_cache>`.

In verjetno najboljše od vsega z uporabo Symfony2 imate sedaj dostop do celotnega
skupka **visoko kvalitetnih odprto kodnih orodij razvitih s strani Symfony2 skupnosti**!
Dobra izbira Symfony2 orodij skupnosti je na voljo na `KnpBundles.com`_.

Boljše predloge
---------------

Če ga izberete za uporabo, Symfony2 prihaja standardno z motorjem predlog
imenovanim `Twig`_, ki naredi predloge hitrejše za pisanje in enostavnejše za branje.
To pomeni, da primer aplikacije lahko vsebuje celo manj kode! Vzemimo
za primer predlogo seznama napisano v Twig-u:

.. code-block:: html+jinja

    {# src/Acme/BlogBundle/Resources/views/Blog/list.html.twig #}
    {% extends "::layout.html.twig" %}

    {% block title %}List of Posts{% endblock %}

    {% block body %}
        <h1>List of Posts</h1>
        <ul>
            {% for post in posts %}
            <li>
                <a href="{{ path('blog_show', {'id': post.id}) }}">
                    {{ post.title }}
                </a>
            </li>
            {% endfor %}
        </ul>
    {% endblock %}

Pripadajoča predloga ``layout.html.twig`` je tudi enostavnejša za pisanje:

.. code-block:: html+jinja

    {# app/Resources/views/layout.html.twig #}
    <!DOCTYPE html>
    <html>
        <head>
            <title>{% block title %}Default title{% endblock %}</title>
        </head>
        <body>
            {% block body %}{% endblock %}
        </body>
    </html>

Twig je dobro podprt v Symfony2. In medtem kot bodo PHP predloge vedno
podprte v Symfony2, bodo mnoge prednosti Twig-a v nadaljevanju
prediskutirane. Za več informacij, glejte :doc:`poglavje predlog </book/templating>`.

Izvedite več iz knjige receptov
-------------------------------

* :doc:`/cookbook/templating/PHP`
* :doc:`/cookbook/controller/service`

.. _`Doctrine`: http://www.doctrine-project.org
.. _`prenesite Composer`: http://getcomposer.org/download/
.. _`Routing`: https://github.com/symfony/Routing
.. _`Templating`: https://github.com/symfony/Templating
.. _`KnpBundles.com`: http://knpbundles.com/
.. _`Twig`: http://twig.sensiolabs.org
.. _`Varnish`: https://www.varnish-cache.org/
.. _`PHPUnit`: http://www.phpunit.de
