Pogled
======

Po branju prvega dela tega vodiča ste se odločili, da je Symfony2
vreden dodatnih 10 minut. V tem drugem delu se boste naučili več o
hitrem, fleksibilnem in varnem motorju predlog `Twig_` za PHP. Twig naredi vaše
predloge bolj bralne in jedrnate; naredi jih tudi bolj prijazne za spletne
oblikovalce.

Spozavanje Twig-a
-----------------

Uradna `dokumentacija Twig`_ je najboljši vir za učenje vsega
o tem novem motorju predlog. Ta sekcija vam samo poda hiter pregled
njegovih glavnih konceptov.

Predloga Twig je tekstovna datoteka, ki lahko generira katerikoli tip vsebine (HTML, CSS,
JavaScript, XML, CSV, LaTex, ...). Twig elementi so ločeni od ostale
vsebine predloge z uporabo katerihkoli sledečih ločil:

* ``{{ ... }}``: izpiše vsebine spremenljivke ali rezultata izraza;

* ``{% ... %}``: krmili logiko predloge; uporabljen je na primer, da
  izvrši zanke ``for`` in stavke ``if``;

* ``{# ... #}``: omogoča vključevanje komentarjev znotraj predlog.

Spodaj je minimalna predloga, ki ponazarja nekaj osnov z uporabo dveh spremenljivk
``page_title`` in ``navigation``, ki so podane v predlogo:

.. code-block:: html+jinja

    <!DOCTYPE html>
    <html>
        <head>
            <title>{{ page_title }}</title>
        </head>
        <body>
            <h1>{{ page_title }}</h1>

            <ul id="navigation">
                {% for item in navigation %}
                    <li><a href="{{ item.url }}">{{ item.label }}</a></li>
                {% endfor %}
            </ul>
        </body>
    </html>

Da se izpiše predlogo v Symfony, uporabite ``render`` metodo od znotraj krmilnika
in podajte potrebne spremenljivke kot polje z uporabo opcijskega drugega argumenta::

    $this->render('AcmeDemoBundle:Demo:hello.html.twig', array(
        'name' => $name,
    ));

Spremenljivke podane predlogi, so lahko nizi, polja ali celo objekti. Twig
abstraktira razliko med njimi in vam omogoča dostopati do "atributov"
spremenljivke z notacijo pike (``.``). Sledeči seznam kode prikazuje, kako
prikazati vsebino spremenljivke v odvisnosti od tipa podane spremenljivke
krmilniku::

.. code-block:: jinja

    {# 1. Simple variables #}
    {# array('name' => 'Fabien') #}
    {{ name }}

    {# 2. Arrays #}
    {# array('user' => array('name' => 'Fabien')) #}
    {{ user.name }}

    {# alternative syntax for arrays #}
    {{ user['name'] }}

    {# 3. Objects #}
    {# array('user' => new User('Fabien')) #}
    {{ user.name }}
    {{ user.getName }}

    {# alternative syntax for objects #}
    {{ user.name() }}
    {{ user.getName() }}

Dekoracija predlog
------------------

Bolj pogosto kot ne si predloge v projektu delijo skupne elemente, ko sta
dobro znani glava in noga. Twig rešuje ta problem elegantno s konceptom
imenovanim "dedovanje predlog". Ta lastnost vam omogoča zgraditi osnovno predlogo
"layout", ki vsebuje vse skupne elemente vaše strani in definira "bloke",
ki jih potomci predlog lahko prepišejo.

Predloga ``hello.html.twig`` uporablja značko ``extends``, ki prikazuje, da
deduje iz skupne predloge ``layout.html.twig``:

.. code-block:: html+jinja

    {# src/Acme/DemoBundle/Resources/views/Demo/hello.html.twig #}
    {% extends "AcmeDemoBundle::layout.html.twig" %}

    {% block title "Hello " ~ name %}

    {% block content %}
        <h1>Hello {{ name }}!</h1>
    {% endblock %}

Notacija ``AcmeDemoBundle::layout.html.twig`` zveni znano, kajne?
Je ista notacija uporabljena za sklicevanje splošne predloge. Del ``::``
enostavno pomeni, da je element krmilnika prazen, da je pripadajoča datoteka
direktno shranjena v direktoriju ``Resources/views/`` paketa.

Sedaj poenostavite predlogo ``layout.html.twig``:

.. code-block:: jinja

    {# src/Acme/DemoBundle/Resources/views/layout.html.twig #}
    <div>
        {% block content %}
        {% endblock %}
    </div>

Značka ``{% block %}`` pove motorju predlog, da potomčevska predloga lahko
prepiše te dele predloge. V tem primeru predloga ``hello.html.twig``
prepiše blok ``content``, kar pomeni, da je "Hello Fabien" tekst
izpisan znotraj elementa ``<div>``.

Uporaba značk, filtrov in fukcij
--------------------------------

Ena najboljših lastnosti Twig-a je njegova razširljivost preko značk, filtrov in
funkcij. Poglejte sledeči primer predloge, ki izdatno uporablja filtre
za spremembo informacij pred izpisom uporabniku:

.. code-block:: jinja

    <h1>{{ article.title|trim|capitalize }}</h1>

    <p>{{ article.content|striptags|slice(0, 1024) }}</p>

    <p>Tags: {{ article.tags|sort|join(", ") }}</p>

    <p>Next article will be published on {{ 'next Monday'|date('M j, Y')}}</p>

Ne pozabite pogledati uradne `dokumentacije Twig`_, da izveste vse
o filtrih, funkcijah in značkah.

Vključevanje drugih predlog
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Najboljši način za deljenje dela kode med večimi predlogami je izdelati
nov fragment predloge, ki se jo lahko vključi v druge predloge.

Najprej izdelajte predlogo ``embedded.html.twig``:

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

Predpostavimo, da ste ustvarili metodo krmilnika ``topArticlesAction``, da prikazuje
najbolj popularne članke vaše spletne strani. Če želite "izpisati" rezultat
te metode (npr. ``HTML``) znotraj predloge ``index``, uporabite ``render``
funkcijo:

.. code-block:: jinja

    {# src/Acme/DemoBundle/Resources/views/Demo/index.html.twig #}
    {{ render(controller("AcmeDemoBundle:Demo:topArticles", {'num': 10})) }}

Tu se niz ``AcmeDemoBundle:Demo:topArticles`` sklicuje na
akcijo ``topArticlesAction`` krmilnika ``Demo`` in ``num``
argument je na voljo krmilniku::

    // src/Acme/DemoBundle/Controller/DemoController.php

    class DemoController extends Controller
    {
        public function topArticlesAction($num)
        {
            // look for the $num most popular articles in the database
            $articles = ...;

            return $this->render('AcmeDemoBundle:Demo:topArticles.html.twig', array(
                'articles' => $articles,
            ));
        }

        // ...
    }

Izdelava povezav med stranmi
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Izdelava povezav med stranmi je obveza za spletne aplikacije. Namesto
vpisovanja URL-jev v predloge funkcija ``path`` ve, kako generirati
URL-je osnovane na nastavitvah usmerjanja. Na ta način so lahko, vsi vaši URL-ji enostavno
posodobljeni s samo spremembo nastavitev:

.. code-block:: html+jinja

    <a href="{{ path('_demo_hello', { 'name': 'Thomas' }) }}">Greet Thomas!</a>

Funkcija ``path`` vzame ime usmeritve in polje parametrov kot
argumente. Ime usmeritve je ključ, pod katerim so usmeritve definirane in
parametri so vrednosti spremenljivk definiranih v vzorcu usmeritve::

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

    Funkcija ``url`` je zelo podobna funkciji ``path``, vendar generira
    *absolutne* URL-je, kar je zelo pripročno, ko izpisujete e-pošte in RSS datoteke:
    ``{{ url('_demo_hello', {'name': 'Thomas'}) }}``.

Vključevanje sredstev: slike, JavaScripts in stili
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kaj bi bil internet brez slik, JavaScript-a in stilskih datotek?
Symfoyn2 ponuja funkcijo ``asset``, ki enostavno ravna z njimi:

.. code-block:: jinja

    <link href="{{ asset('css/blog.css') }}" rel="stylesheet" type="text/css" />

    <img src="{{ asset('images/logo.png') }}" />

Glavni namen funkcije ``asset`` je narediti vašo aplikacijo bolj prenosno.
Zahvaljujoč tej funkciji, lahko prenesete vrhovni direktorij aplikacije kamorkoli
pod vaš vrhovni spletni direktorij brez spremembe česarkoli v vaši kodi
predloge.

Zaključne misli
---------------

Twig je enostave a močan. Zahvaljujoč vključevanju postavitev, blokov, predlog in
akcij je zelo enostavno organizirati vaše predloge na logičen in
razširljiv način. Vendar, če vam Twig ni udoben, lahko vedno
uporabite PHP predloge znotraj Symfony brez kakršnih koli težav.

S Symfony2 ste delali samo 20 minut, vendar že lahko
naredite z njim neverjetne stvari. To je moč Symfony2. Učenje osnov je enostavno
in se boste kmalu naučili, da je ta enostavnost skrita
pod zelo fleksibilno arhitekturo.

Vendar že prehitevam samega sebe. Najprej se boste morali naučiti več o krmilniku
in to je točno tema :doc:`naslednjega dela tega vodiča <the_controller>`.
Pripravljeni na novih 10 minut s Symfony2?

.. _Twig:               http://twig.sensiolabs.org/
.. _dokumentacija Twig: http://twig.sensiolabs.org/documentation
