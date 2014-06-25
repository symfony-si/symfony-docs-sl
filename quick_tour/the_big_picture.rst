Velika slika
============

Pričnite uporabljati Symfony2 v 10-ih minutah! To poglavje vas bo vodilo skozi
nekatere najbolj pomembne koncepte za Symfony2 in vam razložilo, kako lahko pričnete
hitro s prikazom enostavnega projekta v delovanju.

Če ste že uporabljali spletno ogrodje, se boste s Symfony2 počutili kot doma.
Drugače pa dobrodošli v novem načinu razvoja spletnih aplikacij.

Namestitev Symfony2
-------------------

Najprej preverite, da verzija PHP nameščena na vašem računalniku zadostuje za zahteve
Symfony2: 5.3.3 ali več. Nato odprite ukazno vrstico in izvršite sledeči
ukaz za namestitev najnovejše verzije Symfony2 v direktorij
``myproject/``:

.. code-block:: bash

    $composer create-project symfony/framework-standard-edition myproject/ ~2.5


.. note::

    `Composer`_ je upravljalnik paketov, ki je uporabljen v modernih PHP aplikacijah in
    edini priporočljivi način za namestitev Symfony2. Za namestitev Composer-ja na vaš
    Linux ali Mac sistem, izvršite sledeče ukaze:

    .. code-block:: bash

        $ curl -sS https://getcomposer.org/installer | php
        $ sudo mv composer.phar /usr/local/bin/composer

    Za namestitev Composer-ja na Windows sistem prenesite `izvršljivi namestitveni program`_.

Bodite pozorni, da ko prvič nameščate Symfony2, lahko traja nekaj minut, da
se prenesejo vse njegove komponente. Na koncu namestitvenega procesa,
vas bo namestitveni program vprašal štiri vprašanja:

1. **Would you like to use Symfony 3 directory structure? [y/N]** Prihajajoča
   verzija Symfony 3 bo spremenila privzeto strukturo direktorijev za aplikacije
   Symfony. Če želite stestirati to novo strukturo, vtipkajte ``y``.
   Da sledite temu vodiču, pritisnite ``<Enter>`` tipko, da sprejmete
   privzeto ``N`` vrednost in uporabljate privzeto Symfoyn2 strukturo.
2. **Would you like to install Acme demo bundle? [y/N]** Symfony verzije pred
   2.5 vključujejo demo aplikacijo za testiranje nekaterih lastnosti
   ogrodja. Vendar ta demo aplikacija je uporabna samo za nove uporabnike,
   njena namestitev pa je opcijska. Da sledite temu vodiču, vtipkajte
   tipko ``y``, da namestite demo aplikacijo.
3. **Some parameters are missing. Please provide them.** Symfony2 vas vpraša za
   vrednost vseh nastavitvenih parametrov. Za ta prvi projekt
   lahko varno ignorirate to nastavitev s ponavljajočim pritiskanjem tipke
   ``<Enter>``.
4. **Do you want to remove the existing VCS (.git, .svn..) history? [Y,n]?**
   Razvojna zgodovina velikih projektov kot je Symfony lahko zavzame veliko
   prostora na disku. Pritisnite tipko ``<Enter>`` za varno odstranitev vseh teh podatkov zgodovine.

Poganjanje Symfony2
-------------------

Preden prvič poženete Symfony2, izvršite sledeči ukaz, da
se prepričate, da vaš sistem zadosti vsem tehničnim zahtevam:

.. code-block:: bash

    $ cd myproject/
    $ php app/check.php

Popravite kakršnekoli napake, ki jih ukaz sporoči in nato uporabite vgrajeni PHP spletni strežnik
za pogon Symfony:

.. code-block:: bash

    $ php app/console server:run

Če dobite napako `There are no commands defined in the "server" namespace.`,
potem verjetno uporabljate PHP 5.3. To je v redu! Vendar vgrajeni spletni strežnik je
na voljo samo za PHP 5.4.0 ali več. Če imate starešo verzijo PHP ali
če imate raje običajni spletni strežnik kot je Apache ali Nginx, preberite
članek :doc:`/cookbook/configuration/web_server_configuration`.

Odprite vaš brskalnik in obiščite URL ``http://localhost:8000``, da vidite
pozdravno stran Symfony2:

.. image:: /images/quick_tour/welcome.png
   :align: center
   :alt:   Symfony2 Welcome Page

Razumevanje osnov
-----------------

Eden glavnih ciljev ogrodja je organizirano ohranjanje vaše kode in omogočanje
vaši aplikaciji, da se skozi čas enostavno razvije z izogibanjem mešanja klicev
podatkovne baze, HTML značk in poslobne logike v isti skripti. Za doseg tega cilja
s Symfony, se boste najprej morali naučiti nekaj osnovnih konceptov in izrazov.

Symfony prihaja z nekaj primerov kode, ki jo lahko uporabite, da se naučite več o njegovih
glavnih konceptih. Pojdite na sledeči URL, da vas Symfony2 pozdravi (zamenjajte
*Fabien* z vašim prvim imenom):

.. code-block:: text

    http://localhost:8000/app_dev.php/demo/hello/Fabien

.. image:: /images/quick_tour/hello_fabien.png
   :align: center

Kaj se tukaj dogaja? Poglejte vsak del URL-ja:

* ``app_dev.php``: To je t.i. :term:`prednji krmilnik`. Je unikatna vnosna
  točka aplikacije in se odziva na vse zahtevke uporabnika;

* ``/demo/hello/Fabien``: To je *virtualna pot* do vira, ki ga uporabnik
  želi dobiti.

Vaša odgovornost kot razvijalec je pisanje kode, ki preslika uporabnikov
*zahtevek* (``/demo/hello/Fabien``) v *vir* povezan s
(HTML stranjo ``Hello Fabien!``).

Usmerjanje
~~~~~~~~~~

Symfony2 usmeri zahtevek do kode, ki ga uredi s poskušanjem ujemanja
zahtevanega URL-ja (t.j. virtualna pot) proti nekaterim nastavljenim potem. Demo
poti so definirane v ``app/config/routing_dev.yml`` nastavitveni datoteki:

.. code-block:: yaml

    # app/config/routing_dev.yml
    # ...

    # AcmeDemoBundle routes (to be removed)
    _acme_demo:
        resource: "@AcmeDemoBundle/Resources/config/routing.yml"

To uvozi ``routing.yml`` datoteko, ki stanuje znotraj AcmeDemoBundle:

.. code-block:: yaml

    # src/Acme/DemoBundle/Resources/config/routing.yml
    _welcome:
        path:     /
        defaults: { _controller: AcmeDemoBundle:Welcome:index }

    _demo:
        resource: "@AcmeDemoBundle/Controller/DemoController.php"
        type:     annotation
        prefix:   /demo

    # ...

Prve tri vrstice (za komentarjem) definirajo kodo, ki se izvede, ko uporabnik
zahteva "``/``" vir (t.j. pozdravno stran, ki ste jo videli prej). Ko je zahtevano,
bo ``AcmeDemoBundle:Welcome:index`` krmilnik izveden. V naslednji sekciji, se boste
naučili točno, kaj to pomeni.

.. tip::

    K dodatku datotekam YAML, so lahko usmeritve nastavljene v XML ali PHP datotekah
    in so celo lahko vključene v PHP anotacijah. Ta fleksibilnost je ena
    glavnih lastnosti Symfony2, ogrodja, ki nikoli ne nalaga določenega
    nastavitvenega formata na vas.

Krmilniki
~~~~~~~~~

Krmilnik je PHP funkcija ali metoda, ki upravlja prihajajoče *zahtevke* in
vrača *odzive* (pogosto HTML kodo). Namesto uporabe globalnih PHP spremenljivk
in funkcij (kot sta ``$_GET`` ali ``header()``) za upravljanje teh HTTP sporočil,
Symfony uporablja objekte: :ref:`Request <component-http-foundation-request>`
in :ref:`Response <component-http-foundation-response>`. Najenostavnejši možen
krmilnik lahko ustvari odziv ročno, na osnovi zahtevka::

    use Symfony\Component\HttpFoundation\Response;

    $name = $request->get('name');

    return new Response('Hello '.$name);

Symfony2 izbere krmilnik na osnovi ``_controller`` vrednosti iz nastavitev poti:
``AcmeDemoBundle:Welcome:index``. Ta niz je
krmilnikovo *logično ime*, in se sklicuje na ``indexAction`` metodo iz
``Acme\DemoBundle\Controller\WelcomeController`` razreda::

    // src/Acme/DemoBundle/Controller/WelcomeController.php
    namespace Acme\DemoBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;

    class WelcomeController extends Controller
    {
        public function indexAction()
        {
            return $this->render('AcmeDemoBundle:Welcome:index.html.twig');
        }
    }

.. tip::

    Lahko bi uporabili celotno ime razreda in metode -
    ``Acme\DemoBundle\Controller\WelcomeController::indexAction`` - za
    ``_controller`` vrednost. Vendar uporaba logičnega imena je krajša in omogoča
    več fleksibilnosti.

Razred ``WelcomeController`` širi vgrajeni razred ``Controller``,
ki ponuja uporabne bližnjice metod, kot je
:ref:`render()<controller-rendering-templates>` metoda, ki naloži in izpiše
predlogo (``AcmeDemoBundle:Welcome:index.html.twig``). Vrnjena vrednost
je ``Response`` objekt, sestavljen z izpisano vsebino. Torej, če nastane potreba,
se lahko ``Response`` uredi preden je poslan brskalniku::

    public function indexAction()
    {
        $response = $this->render('AcmeDemoBundle:Welcome:index.txt.twig');
        $response->headers->set('Content-Type', 'text/plain');

        return $response;
    }

Ne glede na to, kako to naredite, končni cilj vašega krmilnika je vedno vrniti
``Response`` objekt, ki bi moral biti dostavljen nazaj k uporabniku. Ta ``Response``
objekt je lahko napolnjen s HTML kodo, predstavlja preusmeritev klienta, ali celo
vrne vsebino JPG slike s ``Content-Type`` glavo iz ``image/jpg``.

Ime predloge, ``AcmeDemoBundle:Welcome:index.html.twig``, je
*logično ime* predloge in se sklicuje na ``Resources/views/Welcome/index.html.twig``
datoteko znotraj AcmeDemoBundle (locirana v ``src/Acme/DemoBundle``).
Sekcija  `Paketi`_ spodaj vam bo razložila zakaj je to uporabno.

Sedaj pa ponovno poglejmo nastavitve usmerjanja in najdimo ``_demo``
ključ:

.. code-block:: yaml

    # src/Acme/DemoBundle/Resources/config/routing.yml
    # ...
    _demo:
        resource: "@AcmeDemoBundle/Controller/DemoController.php"
        type:     annotation
        prefix:   /demo

*Logično ime* datoteke, ki vsebuje ``_demo`` usmeritve je
``@AcmeDemoBundle/Controller/DemoController.php`` in se sklicuje
na ``src/Acme/DemoBundle/Controller/DemoController.php`` datoteko. V tej
datoteki so usmeritve definirane kot anotacije na akcijskih metodah::

    // src/Acme/DemoBundle/Controller/DemoController.php
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;

    class DemoController extends Controller
    {
        /**
         * @Route("/hello/{name}", name="_demo_hello")
         * @Template()
         */
        public function helloAction($name)
        {
            return array('name' => $name);
        }

        // ...
    }

The ``@Route()`` annotation creates a new route matching the ``/hello/{name}``
path to the ``helloAction()`` method. Any string enclosed in curly brackets,
like ``{name}``, is considered a variable that can be directly retrieved as a
method argument with the same name.

Anotacija ``@Route()`` ustvarja novo usmeritev, ki se ujema s potjo
``/hello/{name}``, ki izvede ``helloAction`` metodo. Katerikoli niz zaprt v zavitih oklepajih,
kot je ``{name}``, se smatra za spremenljivko, ki je lahko direktno pridobljena kot
argument metode z enakim imenom.

Če pogledate podrobneje kodo krmilnika, lahko vidite, da namesto izpisa
predloge in vrnitve ``Response`` objekta kot prej, vrne samo polje
parametrov. Anotacija ``@Template()`` pove Symfony-ju
naj izpiše predlogo za vas preko podajanja vsake spremenljivke vrnjenega polja.
Ime predloge, ki se izpiše sledi imenu krmilnika. Torej v tem primeru
je izpisana ``AcmeDemoBundle:Demo:hello.html.twig`` predloga (locirana v
``src/Acme/DemoBundle/Resources/views/Demo/hello.html.twig``).

Predloge
~~~~~~~~

Krmilnik izpiše ``src/Acme/DemoBundle/Resources/views/Demo/hello.html.twig``
predlogo (ali ``AcmeDemoBundle:Demo:hello.html.twig`` če uporabljate logično ime):

.. code-block:: jinja

    {# src/Acme/DemoBundle/Resources/views/Demo/hello.html.twig #}
    {% extends "AcmeDemoBundle::layout.html.twig" %}

    {% block title "Hello " ~ name %}

    {% block content %}
        <h1>Hello {{ name }}!</h1>
    {% endblock %}

Privzeto, Symfony2 uporablja `Twig`_ kot svoj motor predlog, vendar lahko uporabite tudi običajne
PHP predloge, če to izberete.
:doc:`Drugi del tega vodiča</quick_tour/the_view>` bo predstavil, kako
predloge delujejo v Symfony2.

Paketi
~~~~~~

Verjetno ste se spraševali, zakaj je beseda paket (:term:`Bundle`) uporabljena v tako veliko
imenih do sedaj. Vsa koda, ki jo pišete za vašo aplikacijo je organizirana v paketih.
V Symfony2 primeru je paket strukturiran skupek datotek (PHP datotek, stilov, JavaScript-a,
slik, ...), ki implementirajo neko lastnost (blog, forum, ...) in ki so lahko enostavno deljene
z drugimi razvijalci. Do sedaj ste ravnali z enim paketom, AcmeDemoBundle. Naučili se boste več
o paketih v :doc:`zadnjem delu tega vodiča</quick_tour/the_architecture>`.

.. _quick-tour-big-picture-environments:

Delo z okolji
-------------

Sedaj, ko imate boljše razumevanje, kako Symfony2 deluje, si podrobneje poglejte
na konec katerekoli Symfony2 izpisane strani. Morali bi opaziti majhno vrstico
s Symfony2 logotipom. To je "Web Debug Toolbar" in je najboljši prijatelj Symfony2
razvijalca!

.. image:: /images/quick_tour/web_debug_toolbar.png
   :align: center

Vendar kar na koncu vidite, je samo vrh ledene gore; kliknite na katerokoli
sekcij profilnega droga, da odprete profiler in dobite veliko več detajlnih informacij o
zahtevku, parametrih poizvedbe, podrobnostih varnosti in poizvedbah podatkovne baze:

.. image:: /images/quick_tour/profiler.png
   :align: center

Seveda bi bilo nepametno imeti ta orodja omogočena, ko postavite vašo
aplikacijo, torej je privzeto profiler onemogočen v ``prod``
okolju.

.. _quick-tour-big-picture-environments-intro:

Kaj je okolje?
~~~~~~~~~~~~~~

Izraz :term:`Okolje` predstavlja skupino nastavitev, ki so uporabljene za poganjanje
vaše aplikacije. Symfony2 privzeto definira dve okolji: ``dev``
(primerno, ko razvijate aplikacijo lokalno) in ``prod`` (optimizirano,
ko izvršujete aplikacijo na produkciji).

Običajno si okolja delijo veliko količino nastavitvenih opcij. Zaradi
tega razloga date vaše skupne nastavitve v ``config.yml`` in prepišete
določene nastavitvene datoteke za vsako okolje, kjer je to potrebno:

.. code-block:: yaml

    # app/config/config_dev.yml
    imports:
        - { resource: config.yml }

    web_profiler:
        toolbar: true
        intercept_redirects: false

V tem primeru ``dev`` okolje naloži ``config_dev.yml`` nastavitveno
datoteko, ki sama po sebi uvozi skupno ``config.yml`` datoteko in jo nato spremeni
z omogočanjem spletne razhroščevalne vrstice.

Ko obiščete datoteko ``app_dev.php`` v vašem brskalniku, izvajate
vašo Symfony aplikacijo v ``dev`` okolju. Da obiščete vašo aplikacijo
v ``prod`` okolju, namesto tega obiščite datoteko ``app.php``.

Demo usmeritve v vaši aplikaciji so na voljo samo v ``dev`` okolju.
Zato, če poskušate dostopati do URL-ja ``http://localhost/app.php/demo/hello/Fabien``,
boste dobili napako 404.

.. tip::

    Če namesto uporabe PHP-jevega vgrajenega spletnega strežnika uporabljate Apache z
    omogočenim ``mod_rewrite`` in izkoristite prednosti datoteke ``.htaccess``,
    ki jo Symfony2 ponuja v ``web/``, lahko celo izpustite del ``app.php``
    URL-ja. Privzeta ``.htaccess`` kaže vse zahtevke v prednji krmilnik
    ``app.php``.

    .. code-block:: text

        http://localhost/demo/hello/Fabien

Za več podrobnosti o okoljih glejte
članek ":ref:`Okolja in prednji krmilniki <page-creation-environments>`".

Zaključne misli
---------------

Čestitamo! Za pokušino ste dobili vašo prvo Symfony2 kodo. Ni bilo tako težko, kaj?
Na voljo za odkriti je še več, vendar bi morali že videti, kako naredi Symfony2 res enostavno
implementacijo spletnih strani boljše in hitrejše. Če ste se željni naučiti več o Symfony2,
se poglobite v naslednjo sekcijo: ":doc:`Pogled<the_view>`".

.. _`Composer`:                      http://getcomposer.org/
.. _izvršljivi namestitveni program: http://getcomposer.org/download
.. _Twig:                            http://twig.sensiolabs.org/
