Velika slika
============

Pričnite uporabljati Symfony2 v 10-ih minutah! To poglavje vas bo vodilo skozi
nekatere najbolj pomembne koncepte za Symfony2 in vam razložilo, kako lahko
hitro pričnete hitro s prikazon enostavnega projekta v delovanju.

Če ste že uporabljali spletno ogrodje, se boste s Symfony2 počutili kot doma.
Drugače pa dobrodošli v novem načinu razvoja spletnih aplikacij!

.. tip::

    Se želite naučiti, zakaj in kdaj potrebujete uporabiti ogrodje? Preberite
    dokument "`Symfony v 5 minutah`_".

Prenos Symfony2
---------------

Najprej preverite, da imate nameščen in nastavljen spletni strežnik (kot je
Apache) s PHP 5.3.3 ali več.

.. tip::

    Če imate PHP 5.4, lahko uporabite vgrajeni spletni strežnik, da pričnete
    preizkušati zadeve. Povedali vam bomo, kako zagnati vgrajeni spletni strežnik
    :ref:`po prenosu Symfony<quick-tour-big-picture-built-in-server>`.

Pripravljeni? Začnite s prenosom "`Symfony2 standardne izdaje`_": Symfony
:term:`distribution`, ki je prednameščena za najbolj pogoste primere uporabe in
tudi vsebuje nekaj kode, ki demonstrira, kako uporabite Symfony2 (vključen dobite arhiv
z *izdelovalci* za še hitrejši začetek).

Po razpakiranju arhiva pod vašim vrhnjim spletnim direktorijem (če boste
uporabili vgrajeni PHP spletni strežnik, ga lahko razpakirate kjerkoli), bi
morali imeti ``Symfony/`` direktorij, ki izgleda takole:

.. code-block:: text

    www/ <- vaš vrhnji spletni direktorij
        Symfony/ <- razpakiran arhiv
            app/
                cache/
                config/
                logs/
                Resources/
            bin/
            src/
                Acme/
                    DemoBundle/
                        Controller/
                        Resources/
                        ...
            vendor/
                symfony/
                doctrine/
                ...
            web/
                app.php
                ...

.. note::

    Če vam je `Composer`_ že poznan, lahko prenesete Composer in nato
    poženete sledeči ukaz namesto prenosa arhiva (zamenjate
    ``2.3.0`` z najnovejšo Symfony izdajo, npr. ``2.3.1``):

    .. code-block:: bash

        $ php composer.phar create-project symfony/framework-standard-edition Symfony 2.3.0

.. _`quick-tour-big-picture-built-in-server`:

Če imate PHP 5.4, lahko uporabite vgrajeni spletni strežnik:

.. code-block:: bash

    # check your PHP CLI configuration
    $ php app/check.php

    # run the built-in web server
    $ php app/console server:run

Nato bo URL do vaše aplikacije "http://localhost:8000/app_dev.php"

Vgrajeni spletni strežnik se uporabi samo za namene razvoja, vendar
vam lahko pomaga za pričetek vašega projekta hitro in enostavno.

Če uporabljate tradicionalni spletni strežnik kot je Apache, je vaš URL odvisen od
vaših nastavitev. Če se odarhivirali Symfony pod vašim vrhnjim spletnih direktorijem v
``Symfony`` direktorij, potem bo URL do vaše aplikacije:
"http://localhost/Symfony/web/app_dev.php".

.. note::

    Preberite več v naši :doc:`/cookbook/configuration/web_server_configuration`
    sekciji.

Preverjanje nastavitev
----------------------

Symfony2 pride z vizualnim testiranjem strežniških nastavitev, da vam pomaga se izogniti
nekaterim preglavicam, ki izhajajo iz slabih nastavitev spletnega strežnika ali PHP. Uporabite
sledeči URL, da vidite diagnostiko vaše naprave:

.. code-block:: text

    http://localhost/config.php

.. note::

    Vsi primeri URL-jev predvidevajo, da ste nastavili spletni strežnik, da kaže
    direktno v ``web/`` direktorij vašega novega projekta, ki je različen
    in malo bolj napreden kot prikazan proces zgoraj. Torej URL vaše
    naprave bo spremenljiv - npr. ``http://localhost:8000/config.php``
    ali ``http://localhost/Symfony/web/config.php``. Oglejte si
    :ref:`zgornjo sekcijo<quick-tour-big-picture-built-in-server>` za podrobnosti,
    kakšen bi vaš URL moral biti in ga uporabite spodaj v vseh primerih.

Če so napisane izjemne težave, jih popravite. Lahko tudi spremenite
vaše nastavitve z upoštevanjem katerega koli priporočila. Ko je vse urejeno,
kliknite na "*Bypass configuration and go to the Welcome page*" za zahtevek
vaše prve "prave" Symfony2 spletne strani:

.. code-block:: text

    http://localhost/app_dev.php/

Symfony2 bi vas moral pozdraviti in vam čestitati za vaše težko delo do sedaj!

.. image:: /images/quick_tour/welcome.png
   :align: center

Razumevanje osnov
-----------------

Eden glavnih ciljev ogrodja je zagotovitev `Ločitev skrbi`_.
To ohranja vašo kodo organizirano in dovoljuje vaši aplikaciji, da se razvija
enostavno skozi čas z izogibanjem mešanja klicev podatkovne baze, HTML značk in
poslovne logike v isti skripti. Za doseg tega cilja s Symfony-jem, se boste
najprej morali naučiti nekaj fundamentalnih konceptov in terminov.

.. tip::

    Želite dokaz, da je uporaba ogrodja boljša kot mešanje vsega
    v isti skripti? Preberite ":doc:`/book/from_flat_php_to_symfony2`"
    poglavje knjige.

Distribucija vsebuje nekaj primerov kode, ki jih lahko uporabite, da se naučite več
o glavnih Symfony2 konceptih. Pojdite na sledeči URL za pozdravno Symfony2 sporočilo
(zamenjajte *Fabien* z vašim imenom):

.. code-block:: text

    http://localhost/app_dev.php/demo/hello/Fabien

.. image:: /images/quick_tour/hello_fabien.png
   :align: center

Kaj se tu dogaja? Razčlenimo URL:

* ``app_dev.php``: To je :term:`front controller`. Je unikatna vstopna
  točka aplikacije in se odziva na vse uporabniške zahtevke;

* ``/demo/hello/Fabien``: To je *virtualna pot* do vira, do katerega uporabnik
  želi dostopati.

Vaša odgovornost kot razvijalec je napisati kodo, ki se ujema z uporabnikovim
*zahtevkom* (``/demo/hello/Fabien``) v *vir* povezan z njim
(``Hello Fabien!`` HTML stran).

Usmerjanje
~~~~~~~~~~

Symfony2 usmeri zahtevek do kode, ki ga uredi s poskušanjem ujemanja zahtevanega
URL-ja (t.j. virtualna pot) proti nekaterim nastavljenim potem. Privzeto
te poti (imenovane routes) so definirane v ``app/config/routing.yml`` nastavitveni
datoteki. Ko ste v ``dev`` :ref:`okolju<quick-tour-big-picture-environments>` -
označeno z app_**dev**.php prednjim krmilnikom, ``app/config/routing_dev.yml``
je naložena tudi nastavitvena datoteka. V standardni izdaji Symfony-ja, so te poti
"demo" strani uvožene iz te datoteke:

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
        path:  /
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

    Symfony2 standardna izdaja uporablja :doc:`YAML</components/yaml/yaml_format>`
    za njegove nastavitvene datoteke, vendar Symfony2 izvorno podpira tudi XML, PHP, in
    anotacije. Različne oblike so kompatibilne in so lahko uporabljene
    izmenično znotraj aplikacije. Tudi uspešnost vaše aplikacije ni odvisna od nastavitvene
    oblike, ki jo izberete, saj je vse predpomnjeno na prvem zahtevku.

Krmilniki
~~~~~~~~~

Krmilnik je lepo ime za PHP funkcijo ali metodo, ki ravna vnodne
*zahtevke* in vrne *odzive* (pogosto HTML kodo). Namesto uporabe
PHP globalnih spremenljivk in funkcij (kot sta ``$_GET`` ali ``header()``) za upravljanje
teh HTTP sporočil, Symfony uporablja objekte: :ref:`Request<component-http-foundation-request>`
in :ref:`Response<component-http-foundation-response>`. Najenostavnejši možen
krmilnik lahko ustvari odziv ročno, na osnovi zahtevka::

    use Symfony\Component\HttpFoundation\Response;

    $name = $request->query->get('name');

    return new Response('Hello '.$name, Response::HTTP_OK, array('Content-Type' => 'text/plain'));

.. versionadded:: 2.4
    Support for HTTP status code constants was added in Symfony 2.4.

.. note::

    Symfony2 zajema HTTP specifikacijo, kar so pravila, ki urejajo
    vso komunikacijo na spletu. Preberite več ":doc:`/book/http_fundamentals`"
    poglavje knjige, da se naučite več o tem in dodani moči, ki jo to prinese.

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
    ``_controller`` vrednost. Vendar, če sledite nekaterim enostavnim konvencijam,
    potem je logično ime krajše in omogoča več fleksibilnosti.

Razred ``WelcomeController`` širi vgrajeni razred ``Controller``,
ki ponuja uporabne bližnjice metod, kot je
:ref:`render()<controller-rendering-templates>` metoda, ki naloži in izpiše
predlogo (``AcmeDemoBundle:Welcome:index.html.twig``). Vrnjena vrednost
je Response objekt, sestavljen z izpisano vsebino. Torej, če nastane potreba,
se lahko Response uredi preden je poslan brskalniku::

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

.. tip::

    Razširitev osnovnega razreda ``Controller`` je opcijska. Pravzaprav je
    krmilnik lahko preprosta PHP funkcija ali celo PHP zaprtje (closure).
    Poglavje knjige ":doc:`Krmilnik</book/controller>`" vam pove vse
    o Symfony2 krmilnikih.

Ime predloge, ``AcmeDemoBundle:Welcome:index.html.twig``, je
*logično ime* predloge in se sklicuje na ``Resources/views/Welcome/index.html.twig``
datoteko znotraj ``AcmeDemoBundle`` (locirana v ``src/Acme/DemoBundle``).
Sekcija  `Bundles`_ spodaj vam bo razložila zakaj je to uporabno.

Sedaj pa ponovno poglejmo nastavitve usmerjanja in najdimo ``_demo``
ključ:

.. code-block:: yaml

    # src/Acme/DemoBundle/Resources/config/routing.yml
    # ...
    _demo:
        resource: "@AcmeDemoBundle/Controller/DemoController.php"
        type:     annotation
        prefix:   /demo

Symfony2 lahko prebere/uvozi usmerjevalne informacije iz različnih datotek napisanih
v YAML, XML, PHP ali celo vgrajene v PHP anotacije. Tu je
*logično ime* datoteke ``@AcmeDemoBundle/Controller/DemoController.php`` in se sklicuje
na datoteko ``src/Acme/DemoBundle/Controller/DemoController.php``. V tej datoteki
so poti definirane kot anotacije na akcijskih metodah::

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

Anotacija ``@Route()`` definira novo usmeritev s potjo
``/hello/{name}``, ki izvede ``helloAction`` metodo, ko se ujame. Priloženi
niz v zavitih oklepajih kot je ``{name}`` se imenuje označba mesta. Kot
lahko vidite, je njegova vrednost lahko vrnjena skozi ``$name`` argument metode.

.. note::

    Tudi če anotacije niso običajno podprte v PHP, jih lahko uporabite
    v Symfony2 kot priročen način za nastavitev obnašanja ogrodja in
    imeti nastavitve poleg kode.

Če pogledate podrobneje kodo krmilnika, lahko vidite, da namesto izpisa
predloge in vrnitve ``Response`` objekta kot prej, vrne samo polje
parametrov. Anotacija ``@Template()`` pove Symfony-ju
naj izpiše predlogo za vas preko podajanja vsake spremenljivke v polju predlogi.
Ime predloge, ki se izpiše sledi imenu krmilnika. Torej v tem primeru
je izpisana ``AcmeDemoBundle:Demo:hello.html.twig`` predloga (locirana v
``src/Acme/DemoBundle/Resources/views/Demo/hello.html.twig``).

.. tip::

    Anotaciji ``@Route()`` in ``@Template()`` sta močnejši kot pa enostavni primeri prikazani
    v tem vodiču. Naučite se več o "`annotations in controllers`_" v uradni
    dokumentaciji.

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
PHP predloge, če to izberete. Naslednje poglavje bo predstavilo, kako predloge delujejo v Symfony2.

Paketi
~~~~~~

Verjetno ste se spraševali, zakaj je beseda paket (:term:`Bundle`) uporabljena v tako veliko
imenih do sedaj. Vsa koda, ki jo pišete za vašo aplikacijo je organizirana v paketih.
V Symfony2 primeru je paket strukturiran skupek datotek (PHP datotek, stilov, JavaScript-a,
slik, ...), ki implementirajo neko lastnost (blog, forum, ...) in ki so lahko enostavno deljene
z drugimi razvijalci. Do sedaj ste ravnali z enim paketom, AcmeDemoBundle. Naučili se boste več
o paketih v :doc:`zadnjem poglavju tega vodiča</quick_tour/the_architecture>`.

.. _quick-tour-big-picture-environments:

Delo z okolji
-------------

Sedaj, ko imate boljše razumevanje, kako Symfony2 deluje, si podrobneje poglejte
na konec katerekoli Symfony2 izpisane strani. Morali bi opaziti majhno vrstico
s Symfony2 logotipom. To je "Web Debug Toolbar" in je najboljši prijatelj Symfony2
razvijalca!

.. image:: /images/quick_tour/web_debug_toolbar.png
   :align: center

Vendar na koncu vidite je samo vrh ledene gore; kliknite na šestnajstiško številko
(žeton seje), da okrijete še eno zelo uporabno Symfony2 razhroščevalno orodje: profiler.

.. image:: /images/quick_tour/profiler.png
   :align: center

.. note::

    Lahko dobite tudi več informacij hitro s pozicijo nad elementi na spletni razhroščevalni
    vrstici, ali če jih kliknete, da greste do njihovih ustreznih strani v profiler-ju.

Ko je naložen in omogočen (privzeto v ``dev`` :ref:`okolju<quick-tour-big-picture-environments-intro>`),
Profiler ponuja spletni vmesnik za *veliko* količino informacij, posnetih
pri vsakem zahtevku, vključno z dnevniki, časovnico zahtevkov, GET ali POST parametri,
varnostnimi podrobnostmi, poizvedbami podatkovne baze in več!

Seveda bi bilo nepametno imeti ta orodja omogočena, ko postavite vašo aplikacijo,
torej je privzeto profiler onemogočen v ``prod`` okolju.

.. _quick-tour-big-picture-environments-intro:

Torej kaj *je* okolje? Termin :term:`Environment` je enostaven niz (npr.
``dev`` ali ``prod``) ki predstavlja skupino nastavitev, ki so uporabljene za poganjanje
vaše aplikacije.

Običajno postavite vaše skupne nastavitve v ``config.yml`` in jih prepišete
kjer je potrebno v nastavitvah za vsako okolje. Na primer:

.. code-block:: yaml

    # app/config/config_dev.yml
    imports:
        - { resource: config.yml }

    web_profiler:
        toolbar: true
        intercept_redirects: false

V tem primeru ``dev`` okolje naloži ``config_dev.yml`` nastavitveno
datoteko, ki sama uvozi globalno datoteko ``config.yml`` in jih nato modificira z omogočanjem
spletne razhroščevalne vrstice.

Ko obiščete ``app_dev.php`` datoteko v vašem brskalniku, izvajate vašo Symfony aplikacijo
v ``dev`` okolju. Za obisk vaše aplikacije
v ``prod`` okolju, namesto tega obiščite ``app.php`` datoteko. Demo usmeritve
v naši aplikaciji so samo na voljo v ``dev`` okolju, vendar
če te poti niso na voljo v ``prod`` okolju, bi jih lahko
obiskalni v ``prod`` okolju z obiskom:

.. code-block:: text

    http://localhost/app.php/demo/hello/Fabien

Če namesto uporabe php-jevega vgrajenega spletnega strežnika, uporabljate Apache z omogočenim ``mod_rewrite``
in uporabljate ``.htaccess`` datoteko, ki jo Symfony2 ponuja
v ``web/``, se lahko celo izognete pisanju ``app.php`` dela v URL-ju. Privzeta datoteka
``.htaccess`` kaže vse zahtevke v ``app.php`` prednji krmilnik:

.. code-block:: text

    http://localhost/demo/hello/Fabien

.. note::

    Opazite, da dva URL-ja zgoraj sta ponujena tu le kot **primera**
    kako URL izgleda, ko je uporabljen ``prod`` prednji krmilnik. Če jih dejansko
    preizkusite v delujoči namestitvi *Symfony standardne izdaje*, boste
    prejeli 404 napako, saj je *AcmeDemoBundle* omogočen samo v
    ``dev`` okolju in njegove usmeritve so uvožene iz ``app/config/routing_dev.yml``.

Za več podrobnosti o okoljih, si oglejte ":ref:`Environments & Front Controllers<page-creation-environments>`".

Zaključne misli
---------------

Čestitamo! Za pokušino ste dobili vašo prvo Symfony2 kodo. Ni bilo tako težko, kaj?
Na voljo za odkriti je še več, vendar bi morali že videti, kako naredi Symfony2 res enostavno
implementacijo spletnih strani boljše in hitrejše. Če ste željni se naučiti več o Symfony2,
se poglobite v naslednjo sekcijo: ":doc:`Pogled<the_view>`".

.. _Symfony2 standardne izdaje:     http://symfony.com/download
.. _Symfony v 5 minutah:            http://symfony.com/symfony-in-five-minutes
.. _`Composer`:                     http://getcomposer.org/
.. _Ločitev skrbi:                  http://en.wikipedia.org/wiki/Separation_of_concerns
.. _annotations in controllers:     http://symfony.com/doc/current/bundles/SensioFrameworkExtraBundle/index.html#annotations-for-controllers
.. _Twig:                           http://twig.sensiolabs.org/
.. _`Symfony Installation Page`:    http://symfony.com/download
