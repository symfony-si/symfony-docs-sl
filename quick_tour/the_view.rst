Pogled
======

Po branju prvega dela tega vodiča, ste se odločili, da je Symfony2
vreden dodatnih 10 minut. Odlična izbira! V drugem delu, se boste naučili
več o Symfony2 motorju predlog, `Twig`_. Twig je fleksibilen,
hiter in varen motor predlog za PHP. Vaše predloge naredi bolj bralne in
jedrnate; naredi jih tudi bolj prijazne za spletne oblikovalce.

.. note::

    Namesto Twig-a lahko uporabite tudi :doc:`PHP </cookbook/templating/PHP>`
    za vaše predloge. Oba motorja predlog sta podprta v Symfony2

Spozavanje Twig-a
-----------------

.. tip::

    Če se želite naučiti o Twig-u, je zelo priporočljivo, da najprej preberete
    njegovo uradno `dokumentacijo`_. Ta sekcija je samo hiter pregled glavnih
    konceptov.

Twig predloga je tekstovna datoteka, ki lahko generira kakršen koli tip vsebine
(HTML, XML, CSV, LaTeX, ...). Twig definira dve vrsti ločil:

* ``{{ ... }}``: Izpiše spremenljivko ali rezultat izraza;

* ``{% ... %}``: Krmili logiko predloge; uporabljen je za izvajanje
  ``for`` zank in ``if`` stavkov, na primer.

Spodaj je minimalna predloga, ki ilustrira nekaj osnov z uporabo dveh spremenljivk
``page_title`` in ``navigation``, kateri bi bili poslani v predlogo:

.. code-block:: html+jinja

    <!DOCTYPE html>
    <html>
        <head>
            <title>My Webpage</title>
        </head>
        <body>
            <h1>{{ page_title }}</h1>

            <ul id="navigation">
                {% for item in navigation %}
                    <li><a href="{{ item.href }}">{{ item.caption }}</a></li>
                {% endfor %}
            </ul>
        </body>
    </html>

.. tip::

   Komentarji so lahko vključeni znotraj predloge z uporabo ``{# ... #}`` ločila.

Za izpis predloge v Symfony-ju, uporabite metodo ``render`` znotraj krmilnika
in mu podajte katerokoli spremenljivko potrebujete v predlogi::

    $this->render('AcmeDemoBundle:Demo:hello.html.twig', array(
        'name' => $name,
    ));

Spremenljivke podane predlogi so lahko nizi, polja ali celo objekti. Twig
povzema razlike med njimi in vam omogoča dostop "atributov" spremenljivke
z notacijo pike (``.``):

.. code-block:: jinja

    {# array('name' => 'Fabien') #}
    {{ name }}

    {# array('user' => array('name' => 'Fabien')) #}
    {{ user.name }}

    {# force array lookup #}
    {{ user['name'] }}

    {# array('user' => new User('Fabien')) #}
    {{ user.name }}
    {{ user.getName }}

    {# force method name lookup #}
    {{ user.name() }}
    {{ user.getName() }}

    {# pass arguments to a method #}
    {{ user.date('Y-m-d') }}

.. note::

    Pomembno je, da veste, da zaviti oklepaji niso del spremenljivke vendar
    stavka izpisa. Če dostopate do spremenljivke znotraj značk, ne pustite
    okrog oklepajev.

Dekoracija predlog
------------------

Pogosteje, predloge v projektu delijo skupne elemente, kot sta
dobro znana glava in noga. V Symfony2, razmišljate o problemu drugače:
predloga je lahko dekorirana s pomočjo druge. To deluje točno tako kot pri
PHP razredih: dedinjenje predlog vam omogoča gradnjo osnovne predloge "postavitve"
("layout"), ki vsebuje vse skupne elemente vaše strani in definira bloke, ki jih
lahko podrejene predloge prepišejo.

Predloga ``hello.html.twig`` podeduje iz ``layout.html.twig``, zahvaljujoč
znački ``extends``:

.. code-block:: html+jinja

    {# src/Acme/DemoBundle/Resources/views/Demo/hello.html.twig #}
    {% extends "AcmeDemoBundle::layout.html.twig" %}

    {% block title "Hello " ~ name %}

    {% block content %}
        <h1>Hello {{ name }}!</h1>
    {% endblock %}

Notacija ``AcmeDemoBundle::layout.html.twig`` zveni znano, kajne?
Je enaka notacija uporabljena za sklicevanje običajne predloge. Del ``::``
enostavno pomeni, da je element krmilnik prazen, torej je ustrezna datoteka
direktno shranjena pod ``Resources/views/`` direktorijem.

Sedaj poglejmo poenostavljen ``layout.html.twig``:

.. code-block:: jinja

    {# src/Acme/DemoBundle/Resources/views/layout.html.twig #}
    <div class="symfony-content">
        {% block content %}
        {% endblock %}
    </div>

Značka ``{% block %}`` definira bloke, ki jih podrejene predloge lahko izpolnijo.
Vse kar značke block naredijo je, da povejo motorju predlog, da podrejena predloga
lahko prepiše te dele predloge.

V tem primeru predloga ``hello.html.twig`` prepiše ``content``
block, kar pomeni, da "Hello Fabien" je tekst izpisan znotraj ``div.symfony-content``
elementa.

Uporaba značk, filtrov in fukcij
--------------------------------

Eden najboljših lastnosti Twig-a je njegova razširljivost preko značk, filtrov in
funkcij. Symfony2 prihaja zapakiran z mnogo od teh že vgrajenih, da poenostavi
delo oblikovalcu predloge.

Vključevanje drugih predlog
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Najboljša pot za deljenje odrezkov kode med večimi različnimi predlogami je,
da se naredi novo predlogo, ki je lahko potem vključena iz drugih predlog.

Izdelajte predlogo ``embedded.html.twig``:

.. code-block:: jinja

    {# src/Acme/DemoBundle/Resources/views/Demo/embedded.html.twig #}
    Hello {{ name }}

In spremenite predlogo ``index.html.twig``, da jo vsebuje:

.. code-block:: jinja

    {# src/Acme/DemoBundle/Resources/views/Demo/hello.html.twig #}
    {% extends "AcmeDemoBundle::layout.html.twig" %}

    {# override the body block from embedded.html.twig #}
    {% block content %}
        {{ include("AcmeDemoBundle:Demo:embedded.html.twig") }}
    {% endblock %}

Vključevanje drugih krmilnikov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

In kaj, če želite vključiti rezultat drugega krmilnika v predlogo?
To je zelo uporabno, ko delate z Ajax-om ali ko vključena predloga potrebuje
neko spremenljivko, ki ni na voljo v glavni predlogi.

Predpostavimo, da ste izdelali ``fancyAction`` metodo krmilnika in jo želite
"izpisati" znotraj ``index`` predloge, kar pomeni vključevanje rezultata
(npr. ``HTML``) krmilnika. Da to naredite, uporabite ``render`` funkcijo

.. code-block:: jinja

    {# src/Acme/DemoBundle/Resources/views/Demo/index.html.twig #}
    {{ render(controller("AcmeDemoBundle:Demo:fancy", {'name': name, 'color': 'green'})) }}

Tu je ``AcmeDemoBundle:Demo:fancy`` niz, ki se sklicuje na ``fancy`` akcijo
``Demo`` krmilnika. Argumenti (``name`` in ``color``) se obnašajo podobno kot
simulirane spremenljivke zahtevka (kot če bi ``fancyAction`` upravljala celoten nov
zahtevek) in so na voljo krmilniku::

    // src/Acme/DemoBundle/Controller/DemoController.php

    class DemoController extends Controller
    {
        public function fancyAction($name, $color)
        {
            // create some object, based on the $color variable
            $object = ...;

            return $this->render('AcmeDemoBundle:Demo:fancy.html.twig', array(
                'name' => $name,
                'object' => $object,
            ));
        }

        // ...
    }

Izdelava povezav med stranmi
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko govorimo o spletnih aplikacijah, je izdelava povezav med stranmi obveza. Namesto
vpisovanja URL-jev v predloge, funkcija ``path`` ve, kako generirati
URL-je na osnovi routing nastavitev. Na ta način so lahko vsi vaši URL-ji
posodobljeni s samo spremembo nastavitev:

.. code-block:: html+jinja

    <a href="{{ path('_demo_hello', { 'name': 'Thomas' }) }}">Greet Thomas!</a>

Funkcija ``path`` vzame ime poti in polje parametrov kot argumente. Ime
poti je glavni ključ pod katerim so navedene poti in parametri so vrednosti
lokacije definirane v vzorcu poti::

    // src/Acme/DemoBundle/Controller/DemoController.php
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;

    // ...

    /**
     * @Route("/hello/{name}", name="_demo_hello")
     * @Template()
     */
    public function helloAction($name)
    {
        return array('name' => $name);
    }

.. tip::

    The ``url`` function generates *absolute* URLs: ``{{ url('_demo_hello', {
    'name': 'Thomas'}) }}``.

Vključevanje sredstev: slike, JavaScripts in stili
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kaj bi bil internet brez slik, JavaScript-a in stilov?
Symfony2 ponuja funkcijo ``asset``, da ravna z njimi na enostaven način:

.. code-block:: jinja

    <link href="{{ asset('css/blog.css') }}" rel="stylesheet" type="text/css" />

    <img src="{{ asset('images/logo.png') }}" />

Glavna naloga funkcije ``asset`` je narediti aplikacijo bolj prenosno.
Zahvaljujoč tej funkciji, lahko premaknete vrhnji direktorij aplikacije kamorkoli
pod vašim vrhnjim spletnim direktorijem brez da bi spremenili karkoli v vaši kodi
predloge.

Čiščenje spremenljivk
---------------------

Twig je nastavljen, da privzeto avtomatsko počisti ves izpis. Preberite Twig
`dokumentacijo`_ da izveste več o čiščenju izpisa in o Escaper razširitvi.

Zaključne misli
---------------

Twig je enostaven vendar močen. Zahvaljujoč vključenim postavitvam, blokom, predlogam in
akcijam, je zelo enostavno organizirati vaše predloge na logičen in razširljiv način.
Čeprav, če se ne počutite udobno s Twig-om, lahko vedno uporabite
PHP predloge znotraj Symfony-ja brez kakršnih koli težav.

S Symfony2 ste delali samo približno 20 minut, vendar lahko z njim že delate
precej neverjetne stvari. To je moč Symfony2. Učenje osnov je enostavno in se boste
kmalu naučili, da je ta enostavnost skrita pod zelo fleksibilno arhitekturo.

Vendar že malo prehitevam samega sebe. Prvo, se boste morali naučiti o krmilniku
in ravno to je tema :doc:`naslednjega dela tega vodiča <the_controller>`.
Pripravljeni na naslednjih 10 minut s Symfony2?

.. _Twig:          http://twig.sensiolabs.org/
.. _dokumentacijo: http://twig.sensiolabs.org/documentation
