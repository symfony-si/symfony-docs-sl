.. index::
   single: Symfony2 Fundamentals

Symfony2 in HTTP temelji
========================

Čestitamo! Z učenjem o Symfony2 ste dobro na vaši poti, da postanete
bolj *produktivni*, *dobro zastavljeni* in *popularni* spletni razvijalec (pravzaprav,
ste na svojem za zadnji del). Symfony2 je zgrajen, da se vrnete k osnovam:
razviti orodja, ki vam pomagajo razvijati hitreje in graditi bolj robustne
aplikacije, medtem ko vam ni v napoto. Symfony je zgrajen na najboljših idejah
iz mnogih tehnologij: orodja in koncepti, ki se jih boste naučili, predstavljajo
prizadevanja tisočih ljudi skozi mnogo let. V drugih besedah, ne učite se samo
"Symfony", učite se temelje spleta, najboljših razvojnih praks in kako uporabiti
mnoge odlične PHP knjižnice znotraj ali neodvisno od Symfony2. Torej, pripravite se.

Kot velja za Symfony2 filozofijo, se to poglavje pričenja z razlago temeljnih
konceptov, ki so skupn spletnemu razvoju: HTTP. Ne glede na vaše ozadje ali prednostni
programski jezik, to poglavje je **must-read** za vsakogar.

HTTP je enostaven
-----------------

HTTP (Hypertext Transfer Protocol za "geek-e") je tekstovni jezik, ki omogoča
dvema napravama komunicirati druga z drugo. To je vse! Na primer, ko preverjate
za zadnjim `xkcd`_ stripom, se zgodi sledeči (približen)  pogovor:

.. image:: /images/http-xkcd.png
   :align: center

In medtem ko je uporaba dejanski jezika bolj formalna, je še vedno zelo preprosto.
HTTP je termin uporabljen za opis tega enostavnega tekstovno osnovanega jezika. In
ne glede na to, kako gradite na spletu, cilj vašega strežnika je *vedno* razumevanje
enostavnih tekstovnih zahtevkov in vračati enostavne tekstovne odzive.

Symfony2 je zgrajen od tal do vrha okrog te realnosti. Ali če zavedate ali ne,
HTTP je nekaj kar uporabljate vsak dan. S Symfony2, se boste naučili,
kako ga obvladati.

.. index::
   single: HTTP; Request-response paradigm

Korak 1: Klient pošlje zahtevek
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vsak pogovor na spletu se začne z *zahtevkom*. Zahtevek je tekstovno
sporočilo narejeno s strani klienta (npr. brskalnik, iPhone aplikacija itd) v
posebni obliki znani kot HTTP. Klient pošlje ta zahtevek strežniku in nato
čaka na odziv.

Poglejte si prvi del te interakcije (zahtevek) med brskalnikom in xkcd
spletnim strežnikom:

.. image:: /images/http-xkcd-request.png
   :align: center

V HTTP govoru, ta HTTP zahtevek bi dejansko izgledal nekako takole:

.. code-block:: text

    GET / HTTP/1.1
    Host: xkcd.com
    Accept: text/html
    User-Agent: Mozilla/5.0 (Macintosh)

To enostavno sporočilo skomunicira *vse* potrebno o točem
viru, ki ga klient zahteva. Prva vrstica HTTP zahtevka je najpomembnejša
in vsebuje dve stvari: URI in HTTP metodo.

URI (npr. ``/``, ``/contact`` itd.) je unikaten naslov ali lokacija,
ki identificira vir, ki ga klient želi. HTTP metoda (npr. ``GET``)
definira, kaj žalite *narediti* z odzivom. HTTP metode so
*glagoli* zahtevka in definirajo nekaj pogostih načinov, s katerimi lahko
ravnate z virom:

+----------+---------------------------------------+
| *GET*    | Pridobivanje vira iz strežnika        |
+----------+---------------------------------------+
| *POST*   | Izdelava vira na strežniku            |
+----------+---------------------------------------+
| *PUT*    | Posodobitev vira na strežniku         |
+----------+---------------------------------------+
| *DELETE* | Izbris vira iz strežnika              |
+----------+---------------------------------------+

S tem v mislih, si lahko predstavljate, kako HTTP zahtevek lahko izgleda, kot
je na primer brisanje določenega vnosa bloga:

.. code-block:: text

    DELETE /blog/15 HTTP/1.1

.. note::

    Obstaja v bistvu devet HTTP metod, definiranih v HTTP specifikaciji,
    vendar mnoge od njih niso širše uporabljene ali podprte. V realnosti
    mnogi moderni brskalniki ne podpirajo ``PUT`` in ``DELETE`` metod.

Kot dodatek prvi vrstici, HTTP zahtevek vedno vsebuje druge vrstice informacij
imenovane glave zahtevka. Te glave lahko dobavljajo široko območje
informacij kot je zahtevan ``Host``, oblike odziva, ki jih klient
sprejema (``Accept``) in aplikacija, ki jo klient uporablja za izdelavo
zahtevka (``User-Agent``). Obstajajo mnoge ostale glave in so lahko najdene na
Wikipedi-jevem članku "`List of HTTP header fields`_".

Korak 2: Strežnik vrne odziv
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko je strežnik prejel zahtevek, ve točno kateri vir klient potrebuje
(preko URI) in kaj klient želi z njim narediti (preko metode). Na primer
pri GET zahtevku, strežnik pripravi vir in vrne HTTP odziv. Premislite
odziv iz xkcd spletnega strežnika:

.. image:: /images/http-xkcd.png
   :align: center

Prevedeno v HTTP, odziv poslan nazaj brskalniku bo izgledal nekako takole:

.. code-block:: text

    HTTP/1.1 200 OK
    Date: Sat, 02 Apr 2011 21:05:05 GMT
    Server: lighttpd/1.4.19
    Content-Type: text/html

    <html>
      <!-- ... HTML for the xkcd comic -->
    </html>

HTTP odziv vsebuje zahtevani vir (HTML vsebino v tem primeru), kot tudi ostale
informacije o tem odzivu. Prve vrstice so poseben pomembne in vsebujejo kodo HTTP
odzivnega statusa (200 v tem primeru). Statusna koda skomunicira skupni rezultat
zahtevka nazaj klientu. Je bil zahtevek uspešen? Je prišlo do napake? Obstajajo
različne statusne kode, ki navajajo uspeh, napako, ali da klient potrebuje nekaj
narediti (npr. preusmeriti na drugo stran). Celotni seznam je mogoče najti
v Wikipedia-jevem članku `List of HTTP status codes`_.

Kot zahtevek, HTTP odziv vsebuje dodatne dele informacij znanih kot
HTTP glave. Na primer, ena pomembna HTTP odzivna glava je
``Content-Type``. Telo istega vira se lahko vrne v večih različnih oblikah
kot HTML, XML ali JSON in ``Content-Type`` glava uporablja
"Internet Media Types" kot je ``text/html``, da sporoči klientu kateri format je
bil vrnjen. Seznam pogostih vrst medijev je mogoče najti v Wikipedia-jevem članku
`List of common media types`_.

Obstajajo mnoge ostale glave, nekatere med njimi so zelo močne, na primer, določene
glave se lahko uporablja za izdelavo močnih predpomnilnih sistemov.

Zahtevki, odzivi in spletni razvoj
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ta zahtevek-odziv konverzacija je osnovni proces, ki poganja vso
komunikacijo na spletu. In kot pomemben in močen je ta proces,
je neizogibno preprost.

Najpomembnejše dejstvo je to: ne glede na jezik, ki ga uporabljate,
tip aplikacije, ki jo gradite (spletna, mobilna, JSON API) ali razvojna
filozofija, ki ji sledite, je končni cilj aplikacije **vedno** razumevanje
vsakega zahtevka in izdelave in vračanja ustreznega odziva.

Symfony je načrtovan, da se ujema s to realnostjo.

.. tip::

    Da izvedete več o HTTP specifikaciji, preberite originalni `HTTP 1.1 RFC`_
    ali `HTTP Bis`_, ki je aktivni trud, da objasni originalno
    specifikacijo. Odlično orodje za preverjanje obeh glav zahtevka in odziva,
    medtem ko brskate, je `Live HTTP Headers`_ razširitev za Firefox.

.. index::
   single: Symfony2 Fundamentals; Requests and responses

Zahtevki in odzivi v PHP
------------------------

Torej kako narediti interakcijo z "zahtevkom" in izdelati "odziv", ko uporabljate
PHP? V realnosti vas PHP malenkost abstraktira od celotnega procesa::

    $uri = $_SERVER['REQUEST_URI'];
    $foo = $_GET['foo'];

    header('Content-type: text/html');
    echo 'The URI requested is: '.$uri;
    echo 'The value of the "foo" parameter is: '.$foo;

Kakor čudno se to sliši, ta majhna aplikacija je v bistvu vzemanje informacij
iz HTTP zahtevka in njegova uporaba za izdelavo HTTP odziva. Namesto
prevajanja surovega HTTP zahtevanega sporočila, PHP pripravi superglobalne spremenljivke
kot sta ``$_SERVER`` in ``$_GET``, ki vključujeta vse informacije iz
zahtevka. Podobno namesto vračanja HTTP oblikovanega tekstovnega odziva
lahko uporabite funkcijo ``header()``, ki naredi odzivne glave in enostavno
izpišejo dejansko sporočilo, ki bo del vsebine odzivnega
sporočila. PHP bo izdelal pravi HTTP odziv in ga vrnil klientu:

.. code-block:: text

    HTTP/1.1 200 OK
    Date: Sat, 03 Apr 2011 02:14:33 GMT
    Server: Apache/2.2.17 (Unix)
    Content-Type: text/html

    The URI requested is: /testing?foo=symfony
    The value of the "foo" parameter is: symfony

Zahtevki in odzivi v Symfony
----------------------------

Symfony ponuja alternativno sorovim PHP pristopom preko dveh razredov, ki
vam omogočata interakcijo s HTTP zahtevkom in odzivom na jasnejši način.
:class:`Symfony\\Component\\HttpFoundation\\Request` razred je enostaven
objektno orientirana reprezentacija HTTP zahtevanega sporočila. Z njim imate
vse informacije zahtevka na dosegu dlani::

    use Symfony\Component\HttpFoundation\Request;

    $request = Request::createFromGlobals();

    // the URI being requested (e.g. /about) minus any query parameters
    $request->getPathInfo();

    // retrieve GET and POST variables respectively
    $request->query->get('foo');
    $request->request->get('bar', 'default value if bar does not exist');

    // retrieve SERVER variables
    $request->server->get('HTTP_HOST');

    // retrieves an instance of UploadedFile identified by foo
    $request->files->get('foo');

    // retrieve a COOKIE value
    $request->cookies->get('PHPSESSID');

    // retrieve an HTTP request header, with normalized, lowercase keys
    $request->headers->get('host');
    $request->headers->get('content_type');

    $request->getMethod();          // GET, POST, PUT, DELETE, HEAD
    $request->getLanguages();       // an array of languages the client accepts

Kot bonus razred ``Request`` ne naredi veliko dela v ozadju, da
vam nikoli ne bo treba skrbeti o tem. Na primer metoda ``isSecure()``
preveri *tri* različne vrednosti v PHP, ki nakazujejo ali se ali ne
uporabnik povezuje preko varne povezave (t.j. ``https``).

.. sidebar:: ParameterBags and Request attributes

    Kot videno zgoraj ``$_GET`` in ``$_POST`` spremenljivke sta tako dostopne preko
    javnih ``query in ``request`` lastnosti. Vsak od
    teh objektov je :class:`Symfony\\Component\\HttpFoundation\\ParameterBag`
    objekt, ki ima metode kot so
    :method:`Symfony\\Component\\HttpFoundation\\ParameterBag::get`,
    :method:`Symfony\\Component\\HttpFoundation\\ParameterBag::has`,
    :method:`Symfony\\Component\\HttpFoundation\\ParameterBag::all` in več.
    V bistvu vsaka javna lastnost uporabljena v prejšnjem primeru je neka instanca
    razreda ParameterBag.

    .. _book-fundamentals-attributes:

    Razred Request ima tudi javno lastnost ``attributes``, ki vsebuje
    posebne podatke povezave s tem, kako aplikacija deluje interno. Za
    Symfony2 ogrodje, ``attributes`` vsebuje vrednosti vrnjene od
    ujemane usmeritve, kot sta ``_controller``, ``id`` (če imate ``{id}``
    nadomestni znak) in celo ime ujemane usmeritve (``_route``). Lastnost
    ``attributes`` obstaja v celoti kot prostor, kjer lahko
    pripravite in shranite vsebinsko specifične informacije o zahtevku.

Symfony tudi ponuja razred ``Response``: enostavno PHP reprezentacijo
sporočila HTTP zahtevka. To omogoča vaši aplikaciji, da uporablja objektno orientiran
vmesnik za izdelavo odziva, ki mora biti vrnjen klientu::

    use Symfony\Component\HttpFoundation\Response;
    $response = new Response();

    $response->setContent('<html><body><h1>Hello world!</h1></body></html>');
    $response->setStatusCode(Response::HTTP_OK);
    $response->headers->set('Content-Type', 'text/html');

    // prints the HTTP headers followed by the content
    $response->send();

Če ne bi Symfony ponudil nič več, bi že imeli orodje za enostavno
dostopanje informacij zahtevka in objektno orientiranega vmesnika za izdelavo
odziva. Celo ko se učite mnoge močne lastnosti v Symfony, imejte
v mislih, da je cilj vaše aplikacije vedno *interpretacija zahtevka
in izdelava ustreznega odziva glede na vašo logiko aplikacije*.

.. versionadded:: 2.4
    Podpora za konstante HTTP statusnih kod je bila dodana v Symfony 2.4.

.. tip::

    Razreda ``Request`` in ``Response`` sta del samostoječe komponente
    vključene v Symfony imenovane ``HttpFoundation``. Ta komponenta je
    lahko v celoti neodvisna od Symfony in tudi ponuja razrede za upravljanje
    sej in nalaganja datotek.

Potovanje od zahtevka do odziva
-------------------------------

Kot sam HTTP sta objekta ``Request`` in ``Responce`` precej enostavna.
Težek del gradnje aplikacije je pisanje, kaj pride vmes.
Z drugimi besedami, pravo delo pride pri pisanju kode, ki tolmači
informacije zahtevka in izdela odziv.

Vaša aplikacija verjetno naredi mnogo stvari, kot je pošiljanje e-pošte, upravljanje
pošiljanja obrazca, shranjevanja stvari v podatkovno bazo, izpisovanje HTML strani in zaščita
vsebine z varnostjo. Kako lahko upravljate vse to in še vedno obdržite vašo
kodo organizirano in vzdrževano?

Symfony je bil izdelan, da rešuje te probleme, da vam to ni treba.

Prednji krmilnik
~~~~~~~~~~~~~~~~

Tradicionalno so bile aplikacije zgrajene, da je bila vsaka "stran" spletne strani
svoja lastna fizična datoteka:

.. code-block:: text

    index.php
    contact.php
    blog.php

Obstaja nekaj problemov s tem pristopom, vključno z nefleksibilnostjo
URL-jev (kaj če ste želeli spremeniti ``blog.php`` v ``news.php`` brez,
da zlomite vse vaše povezave?) in dejstvo, da vsaka datoteka *mora* ročno
vključevati nekaj skupkov datotek jedra, da varnost, povezave s podatkovno bazo in
"izgled" strani lahko ostanejo konsistentni.

Veliko boljša rešitev je uporaba a t.i. :term:`prednjega krmilnika`: ena PHP
datoteka, ki upravlja vsak zahtevek, ki prihaja v vašo aplikacijo. Na primer:

+------------------------+----------------------+
| ``/index.php``         | izvrši ``index.php`` |
+------------------------+----------------------+
| ``/index.php/contact`` | izvrši ``index.php`` |
+------------------------+----------------------+
| ``/index.php/blog``    | izvrši ``index.php`` |
+------------------------+----------------------+

.. tip::

    Uporaba Apache-jevega ``mod_rewrite`` (ali enakovrednega z ostalimi spletnimi strežniki),
    URL-ji so lahko enostavno očiščeni, da so samo ``/``, ``/contact`` in
    ``/blog``.

Sedaj vsak zahtevek je upravljan točno na enak način. Namesto individualnih URL-jev,
ki izvršujejo različne PHP datoteke, je prednji krmilnik *vedno* izvršen
in usmeritev različnih URL-jev na različne dele vaše aplikacije
je narejena interno. To reši oba problema z originalnim pristopom.
Skoraj vse moderne spletne aplikacije to delajo - vključno z aplikacijami kot je WordPress.

Ostanite organizirani
~~~~~~~~~~~~~~~~~~~~~

Znotraj vašega prednjega krmilnika morate ugotoviti, katera koda bi morala
biti izvršena in katera vsebina bi morala biti vrnjena. Da to ugotovite, boste
morali preveriti prihajajoči URI in izvršiti različne dele vaše kode odvisno
od te vrednosti. To lahko postane hitro grdo::

    // index.php
    use Symfony\Component\HttpFoundation\Request;
    use Symfony\Component\HttpFoundation\Response;

    $request = Request::createFromGlobals();
    $path = $request->getPathInfo(); // the URI path being requested

    if (in_array($path, array('', '/'))) {
        $response = new Response('Welcome to the homepage.');
    } elseif ($path == '/contact') {
        $response = new Response('Contact us');
    } else {
        $response = new Response('Page not found.', Response::HTTP_NOT_FOUND);
    }
    $response->send();

Reševanje tega problema je težko. Na srečo je Symfony *točno*
načrtovan za to.

Tok Symfony aplikacije
~~~~~~~~~~~~~~~~~~~~~~

Ko omogočite, da Symfony upravlja vsak zahtevek je življenje mnogo enostavneje. Symfony sledi
enakemu enostavnemu vzorcu za vsak zahtevek:

.. _request-flow-figure:

.. figure:: /images/request-flow.png
   :align: center
   :alt: Symfony2 request flow

   Prihajajoči zahtevki so interpretirani s strani usmerjevalnika in poslani krmilnikovim
   funkcijam, ki vrnejo ``Response`` objekte.

Vsaka "stran" vaše spletne strani je definirana v datoteki nastavitvah usmerjanja, ki
preslika različne URL-je na različne PHP funkcije. Naloga vsake PHP funkcije,
imenovane a :term:`krmilnik`, je uporaba informacij iz zahtevka - skupaj
z mnogimi ostalimi orodji, ki jih Symfony naredi na voljo - izdelati in vrniti ``Response``
objekt. Z drugimi besedami, krmilnik je tam, kamor gre *vaša* koda: to je tam, kjer
interpretirate zahtevek in izdelave odziv.

Tako enostavno je! Da pregledamo:

* Vsak zahtevek izvrši datoteko prednjega krmilnika;

* Sistem usmerjanja določa, katera PHP funkcija naj bo izvšena na osnovi
  informacij iz zahtevka in nastavitev usmerjanja, ki ste jih izdelali;

* Ustrezna PHP funkcija je izvršena, kjer vaša koda ustvari in vrne
  ustrezen ``Response`` objekt.

Symfony-jev zahtevek v akciji
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Brez poglabljanja v preveč podrovnosti je tu proces v akciji. Predpostavimo,
da želite dodati stran ``/contact`` v vašo Symfony aplikacijo. Najprej začnite
z dodajanjem vnosa za stran ``/contact`` v vašo datoteko nastavitev usmerjanja:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        contact:
            path:     /contact
            defaults: { _controller: AcmeDemoBundle:Main:contact }

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="contact" path="/contact">
                <default key="_controller">AcmeDemoBundle:Main:contact</default>
            </route>
        </routes>

    .. code-block:: php

        // app/config/routing.php
        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('contact', new Route('/contact', array(
            '_controller' => 'AcmeDemoBundle:Main:contact',
        )));

        return $collection;

.. note::

   Ta primer uporablja :doc:`YAML </components/yaml/yaml_format>` za definiranje usmerjevalnih
   nastavitev. Nastavitve usmerjanja so lahko tudi napisane v ostalih formatih
   kot sta XML ali PHP.

Ko nekdo obišče stran ``/contact``, se ta usmeritev ujema in
izvršen je določen krmilnik. Kot se boste naučili v :doc:`poglavju usmerjevalnika </book/routing>`,
je niz ``AcmeDemoBundle:Main:contact`` kratka sintaksa, ki kaže na
določeno PHP metodo ``contactAction`` znotraj razreda imenovanega ``MainController``::

    // src/Acme/DemoBundle/Controller/MainController.php
    namespace Acme\DemoBundle\Controller;

    use Symfony\Component\HttpFoundation\Response;

    class MainController
    {
        public function contactAction()
        {
            return new Response('<h1>Contact us!</h1>');
        }
    }

V tem zelo enostavnem primeru, krmilnik enostavno izdela
:class:`Symfony\\Component\\HttpFoundation\\Response` objekt s HTML-jem
``<h1>Contact us!</h1>``. V :doc:`poglavju krmilnika </book/controller>`,
se boste naučili, kako krmilnik lahko izpiše predloge, omogoča vaši "predstavitveni"
kodi (t.j. karkoli, ki dejansko izpiše HTML), da obstoja v ločeni
datoteki predloge. To pusti krmilnik, da skrbi samo o težkih
stvareh: interakcija s podatkovno bazo, upravljanje poslanih podatkov ali pošiljanje
e-poštnih sporočil.

Symfony2: Zgradite vašo aplikacijo, ne vaših orodij
---------------------------------------------------

Sedaj veste, da je cilj katerekoli aplikacije interpretacija vsakega prihajajočega zahtevka
in izdelava ustreznega odziva. Kot aplikacija raste, postane bolj
zahtevno obdržati vašo kodo organizirano in možno vzdrževanja. Nespremenljivo enako
kompleksna opravila vedno prihajajo znova in znova: dodajanje stvari v
podatkovno bazo, izpisovanje in ponovna uporaba predlog, upravljanje pošiljanja obrazcev, pošiljanje
e-pošte, potrjevanje uporabnikovega vnosa in upravljanje varnosti.

Dobre novice so, da noben od teh problemov ni enak. Symfony ponuja
ogrodje polno orodij, ki vam omogočajo zgraditi vašo aplikacijo, ne vašega
orodja. S Symfony2 ni vam nič naloženo: ste svobodni, da uporabite celotno
Symfony ogrodje ali samo en del Symfony vsega samega po sebi.

.. index::
   single: Symfony2 Components

Samostoječa orodja: Symfony2 *komponente*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Torej kaj *je* Symfony2? Najprej, Symfony2 je zbirka preko dvajset neodvisnih
knjižnic, ki so lahko uporabljene znotraj *kateregakoli* PHP projekta. Te knjižnice imenovane
*Symfony2 komponente*, vsebujejo nekaj uporabnega za skoraj vsako situacijo
ne glede na to, kako je vaš projekt razvit. Da jih imenujemo nekaj:

* :doc:`HttpFoundation </components/http_foundation/introduction>` - Vsebuje
  ``Request`` in ``Response`` razreda, kot tudi ostale razrede za upravljanje
  sej in nalaganje datotek;

* :doc:`Routing </components/routing/introduction>` - Močan in hiter usmerjevalni sistem, ki
  vam omogoča preslikati določen URI (npr. ``/contact``) v neko informacijo
  o tem, kako naj bo ta zahtevek upravljan (npr. izvršitev ``contactAction()``
  metode);

* `Form`_ - Polno funkcionalno in fleksibilno ogrodje za izdelavo obrazcev in
  upravljanja pošiljanja obrazcev;

* `Validator`_ - Sistem za izdelavo pravil o podatkih in nato potrjevanja
  ali uporabniško-poslani podatki sledijo tem pravilom ali ne;

* :doc:`ClassLoader </components/class_loader/introduction>` - Avtomatsko nalagalna knjižnica, ki omogoča
  PHP razredom, da so uporabljena brez potrebe po ročnem zahtevanju (``require``) datotek,
  ki vsebujejo te razrede;

* :doc:`Templating </components/templating/introduction>` - Orodje za izpis
  predlog, upravljanje dedovanja predlog (t.j. predloga je okrašena s
  postavitvijo) in opravljanjem ostalih skupnih nalog predlog;

* `Security`_ - Močna knjižnica za upravljanje vseh tipov varnosti znotraj
  aplikacije;

* `Translation`_ - Ogrodje za prevajanje nizov v vaši aplikaciji.

Prav vsaka od teh komponent je ločena in je lahko uporabljena v *kateremkoli*
PHP projektu, ne glede na to ali uporabljate Symfony2 ogrodje ali ne.
Vsak del je narejen, da je lahko uporabljen, če je potrebno in zamenjan, ko je potrebno.

Celotna rešitev: Symfony2 *ogrodje*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Torej potem, kaj *je* Symfony2 *ogrodje*? *Symfony2 ogrodje* je
PHP knjižnica, ki dosega dve različni nalogi:

#. Ponuja izbiro komponent (t.j. Symfony2 komponente) in
   tretje-osebne knjižnice (npr. `Swift Mailer`_ za pošiljanje e-pošte);

#. Ponuja smiselne nastavitve in *lepilno* knjižnico, ki povezuje vse od teh
   delov skupaj.

Cilj ogrodja je integracija mnogih neodvisnih orodij, da
ponujajo konsistentno izkušnjo za razvijalca. Celo samo ogrodje
je Symfony2 paket (t.j. vtičnik), ki je lahko nastavljen ali zamenjan
v celoti.

Symfony2 ponuja močan skupek orodij za hitro razvijanje spletnih aplikacij
brez nalaganja na vašo aplikacijo. Običajni uporabniki lahko hitro začnejo razvijati
z uporabo Symfony2 distribucije, ki ponuja skeletni projekt s
smiselnimi privzetostmi. Za bolj napredne uporabnike, je nebo omejitev.

.. _`xkcd`: http://xkcd.com/
.. _`HTTP 1.1 RFC`: http://www.w3.org/Protocols/rfc2616/rfc2616.html
.. _`HTTP Bis`: http://datatracker.ietf.org/wg/httpbis/
.. _`Live HTTP Headers`: https://addons.mozilla.org/en-US/firefox/addon/live-http-headers/
.. _`List of HTTP status codes`: http://en.wikipedia.org/wiki/List_of_HTTP_status_codes
.. _`List of HTTP header fields`: http://en.wikipedia.org/wiki/List_of_HTTP_header_fields
.. _`List of common media types`: http://en.wikipedia.org/wiki/Internet_media_type#List_of_common_media_types
.. _`Form`: https://github.com/symfony/Form
.. _`Validator`: https://github.com/symfony/Validator
.. _`Security`: https://github.com/symfony/Security
.. _`Translation`: https://github.com/symfony/Translation
.. _`Swift Mailer`: http://swiftmailer.org/
