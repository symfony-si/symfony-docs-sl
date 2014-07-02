.. index::
   single: Controller

Krmilnik
========

Krmilnik je PHP funkcija, ki jo ustvarite, da vzame informacije iz
zahtevka HTTP in konstruira in vrne odziv HTTP (kot objekt Symfony2
``Response``). Odziv je lahko stran HTML, dokument XML,
serializirano polje JSON, slika, preusmeritev, napaka 404 ali karkoli drugega,
kar si zamislite. Krmilnik vsebuje kakršno koli samovoljno logiko *vaša
aplikacija* potrebuje izpisati vsebino strani.

Poglejte, kako enostavno je to, s primerom krmilnika Symfony2 v akciji.
Sledeči krmilnik bi izpisal stran, ki enostavno izpiše ``Hello world!``::

    use Symfony\Component\HttpFoundation\Response;

    public function helloAction()
    {
        return new Response('Hello world!');
    }

Cilj krmilnika je vedno enak: izdelati in vrniti objekt ``Response``.
Tekom poti lahko prebere informacije iz zahtevka, naloži
vire podatkovne baze, pošlje e-pošto ali nastavi informacije uporabnikove seje.
Vendar v vseh primerih bo krmilnik eventuelno vrnil objekt ``Response``,
ki bo dostavljen nazaj h klientu.

Ni čarovnije in nobenih ostalih zahtev o katerih morate skrbeti! Tu je nekaj
pogostih primerov:

* *Krmilnik A* pripravi objekt ``Response``, ki predstavlja vsebino
  za domačo stran spletne strani.

* *Krmilnik B* prebere parameter ``slug`` iz zahtevka, da naloži
  vnos bloga iz podatkovne baze in ustvari objekt ``Response``, ki prikazuje
  ta blog. Če ``slug`` ni najdem v podatkovni bazi, ustvari in
  vrne objekt ``Response`` s statusom 404 kode.

* *Krmilnik C* upravlja pošiljanje obrazca za kontaktni obrazec. Prebere
  obrazec informacij iz zahtevka, shrani kontaktne informacije v
  podatkovno bazo in pošlje e-pošto s kontaktnimi informacijami spletnemu skrbniku. Na koncu
  ustvari objekt ``Response``, ki preusmeri klientov brskalnik na
  zahvalno stran kontaktnega obrazca.

.. index::
   single: Controller; Request-controller-response lifecycle

Zahtevki, krmilnik, življenski cikel odziva
-------------------------------------------

Vsak zahtevek upravljan s projektom Symfony2 gre skozi enak enostaven življenski cikel.
Ogrodje poskrbi za ponovitvena opravila in na koncu izvrši
krmilnik, ki shranjuje vašo kodo aplikacije po meri:

#. Vsak zahtevek je upravljan s strani ene datoteke prednjega krmilnika (npr. ``app.php``
   ali ``app_dev.php``), ki požene aplikacijo;

#. ``Router`` prebere informacije iz zahtevka (npr. URI), najde
   usmeritev, ki se ujema za informacijo in prebere parameter ``_controller``
   iz usmeritve;

#. Krmilnik iz ujete usmeritve je izvršen in koda znotraj
   krmilnika ustvari in vrne objekt ``Response``;

#. Glave HTTP in vsebina objekta ``Response`` so poslane nazaj h
   klientu.

Izdelava strani je enostana kot izdelava krmilnika (#3) in izdelava usmeritve, ki
preslika URL na ta krmilnik (#2).

.. note::

    Čeprav podobno poimenovan "prednji krmilnik", se razlikuje od
    "krmilnikov", o katerih govorimo v tem poglavju. Prednji krmilnik
    je kratka PHP datoteka, ki domuje v vašem spletnem direktoriju in skozi katero
    so usmerjeni vsi zahtevki. Običajna aplikacija bo imela produkcijski
    prednji krmilnik (npr. ``app.php``) in razvojni prednji krmilnik
    (npr. ``app_dev.php``). Verjetno nikoli ne boste potrebovali urediti, pogledati ali skrbeti
    o prednjih krmilnikih v vaši aplikaciji.

.. index::
   single: Controller; Simple example

Enostaven krmilnik
------------------

Medtem ko je lahko krmilnik katerakoli PHP klicajoča (callable) (funkcija, metoda na objektu,
ali ``Closuer``) v Symfony2, je krmilnik običajno ena metoda znotraj
objekta krmilnika. Krmilniki so tudi imenovani *akcije*.

.. code-block:: php
    :linenos:

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

.. tip::

    Bodite pozorni, saj je *krmilnik* metoda ``indexAction``, ki domuje
    znotraj *razreda krmilnika* (``HelloController``). Naj vas ne zmede
    imenovanje: *razred krmilnika* je enostavno prikladen način za grupiranje
    nekaj krmilnikov/akcij skupaj. Običajno bo razred krmilnika
    obsegal nekaj krmilnikov/akcij (npr. ``updateAction``, ``deleteAction``,
    itd).

Ta krmilnik je precej enostaven:

* *vrstica 4*: Symfony2 izkorišča prednosti funkcionalnosti imenskih prostorov PHP 5.3, da
  poimenuje imenski prostor celotnega razreda krmilnika. Ključna beseda ``use`` uvaža
  razred ``Response``, ki ga mora vrniti krmilnik.

* *vrstica 6*: Ime razreda je konkatenacija za ime razreda
  krmilnika (t.j. ``Hello``) in beseda ``Controller``. To je konvencija,
  ki ponuja konsistentnost za krmilnike in jim omogoča, da so sklicani
  samo za prvi del imena (t.j. ``Hello``) v nastavitvah usmeritve.

* *vrstica 8*: Vsaka akcija v razredu krmilnika ima pripono ``Action``
  in je sklicana v nastavitvah usmeritve z imenom akcije (``index``).
  V naslednji sekciji, boste ustvarili usmeritev, ki preslika URI v to akcijo.
  Naučili se boste o tem, kako prostori usmeritve (``{name}``) postanejo argumenti
  za metodo akcije (``$name``).

* *vrstica 10*: Krmilnik ustvari in vrne objekt ``Response``.

.. index::
   single: Controller; Routes and controllers

Preslikava URL-ja v krmilnik
----------------------------

Nov krmilnik vrne enostavno stran HTML. Za dejanski pogled te strani
v vašem brskalniku, morate izdelate usmeritev, ki preslika določeno URL pot
krmilniku:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        hello:
            path:      /hello/{name}
            defaults:  { _controller: AcmeHelloBundle:Hello:index }

    .. code-block:: xml

        <!-- app/config/routing.xml -->
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

        // app/config/routing.php
        $collection->add('hello', new Route('/hello/{name}', array(
            '_controller' => 'AcmeHelloBundle:Hello:index',
        )));

Če obiščete ``/hello/ryan``, sedaj izvrši krmilnik ``HelloController::indexAction()``
in poda ``ryan`` za spremenljivko ``$name``. Izdelava
"strani" enostavno pomeni izdelavo metode krmilnika in povezane usmeritve.

Bodite pozorni na uporabljeno sintakso za sklic krmilnika: ``AcmeHelloBundle:Hello:index``.
Symfony2 uporablja fleksibilno notacijo nizov za sklic različnih krmilnikov.
To je najbolj pogosta sintaksa in pove Symfony2, da poišče razred
krmilnika imenovan ``HelloController`` znotraj paketa imenovanega ``AcmeHelloBundle``. Metoda
``indexAction`` je nato izvršena.

Za več podrobnosti na obliki niza uporabljenega za sklic različnih krmilnikov,
glejte :ref:`controller-string-syntax`.

.. note::

    Ta primer poda nastavitve usmeritve direktno v direktorij ``app/config/``
    Boljši način za organizacijo vaših usmeritev je, da date vsako usmeritev
    v paket, kateremu pripada. Za več informacij o tem, glejte
    :ref:`routing-include-external-resources`.

.. tip::

    Lahko se naučite več o sistemu usmeritev v :doc:`Poglavju usmeritve </book/routing>`.

.. index::
   single: Controller; Controller arguments

.. _route-parameters-controller-arguments:

Parametri usmeritve kot argumenti krmilnika
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Sedaj že veste, da se parameter ``_controller`` ``AcmeHelloBundle:Hello:indexx``
sklicuje na metodo ``HelloController::indexAction()``, ki se nahaja znotraj
paketa ``AcmeHelloBundle``. Kar je bolj zanimivo je, da so argumenti
poslani tej metodi::

    // src/Acme/HelloBundle/Controller/HelloController.php
    namespace Acme\HelloBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;

    class HelloController extends Controller
    {
        public function indexAction($name)
        {
          // ...
        }
    }

Krmilnik ima enostaven argument, ``$name``, ki ustreza
parametru ``{name}`` iz ujete usmeritve (``ryan`` v tem primeru). Dejansko,
ko izvršujete vaš krmilnik, Symfony2 ujema vsak argument
krmilnika s parametrom iz ujete usmeritve. Vzamite sledeči
primer:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        hello:
            path:      /hello/{firstName}/{lastName}
            defaults:  { _controller: AcmeHelloBundle:Hello:index, color: green }

    .. code-block:: xml

        <!-- app/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="hello" path="/hello/{firstName}/{lastName}">
                <default key="_controller">AcmeHelloBundle:Hello:index</default>
                <default key="color">green</default>
            </route>
        </routes>

    .. code-block:: php

        // app/config/routing.php
        $collection->add('hello', new Route('/hello/{firstName}/{lastName}', array(
            '_controller' => 'AcmeHelloBundle:Hello:index',
            'color'       => 'green',
        )));

Krmilnik za to lahko vzame nekaj argumentov::

    public function indexAction($firstName, $lastName, $color)
    {
        // ...
    }

Bodite pozorni, da obe prostorski spremenljivki (``{firstName}``, ``{lastName}``)
kot tudi privzeta spremenljivka ``color`` so na voljo kot argumenti v
krmilniku. Ko je usmeritev ujeta, so prostorske spremenljivke združene
s ``defaults``, da se naredi eno polje, ki je na voljo vašemu krmilniku.

Preslikava parametrov usmeritve argumentom krmilnika je enstavna in fleksibilna. Imejte
sledeče smernice v mislih, medtem ko razvijate.

* **Vrstni red argumentov krmilnika ni važen**

  Symfony je sposoben ujeti imena parametrov iz usmeritve k imenom spremenljivke
  v podpisu metode krmilnika. Z drugimi besedami, se zaveda, da se
  parameter ``{lastName}`` ujema skupaj z argumentom ``$lastName``.
  Argumenti krmilnika bi lahko bili popolnoma v drugačnem vrstnem redu in bi še vedno delovali
  odlično::

      public function indexAction($lastName, $color, $firstName)
      {
          // ...
      }

* **Vsak zahtevani argument krmilnika se mora ujemati s parametri usmeritve**

  Sledeče bi vrglo ``RuntimeException``, ker ni nobenega parametra ``foo``
  definiranega v usmeritvi::

      public function indexAction($firstName, $lastName, $color, $foo)
      {
          // ...
      }

  Izdelava argumenta opcijskega, vendar je čisto v redu. Sledeči
  primer ne bi vrgel izjeme::

      public function indexAction($firstName, $lastName, $color, $foo = 'bar')
      {
          // ...
      }

* **Ne vsi parametri usmeritve morajo biti potrebni argumenti za vaš krmilnik**

  Če na primer, ``lastName`` ne bi bil pomemben za vaš krmilnik,
  bi se ga lahko izognili v celoti::

      public function indexAction($firstName, $color)
      {
          // ...
      }

.. tip::

    Vsaka usmeritev ima tudi poseben parameter ``_route``, ki je enak
    imenu usmeritve s katero se ujema (npr. ``hello``). Čeprav ne običajno
    uporabno, je to enako na voljo kot argument krmilnika.

.. _book-controller-request-argument:

``Request`` kot argument krmilnika
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Za priročnost, lahko tudi pustite, da vam Symfony poda objekt ``Request``
kot argument za vaš krmilnik. To je posebej priročno, ko delate
z obrazci, na primer::

    use Symfony\Component\HttpFoundation\Request;

    public function updateAction(Request $request)
    {
        $form = $this->createForm(...);

        $form->handleRequest($request);
        // ...
    }

.. index::
   single: Controller; Base controller class

Izdelava statičnih strani
-------------------------

Lahko tudi izdelate statično stran brez da bi ustvarili krmilnik (samo usmeritev
in predlogo, ko je potrebno).

Uporabite ga! Glejte :doc:`/cookbook/templating/render_without_controller`.

Osnovni razred krmilnika
------------------------

Zaradi priročnosti gre Symfony2 skupaj z osnovnim razredom ``Controller``, ki asistira
pri nekaterih najbolj pogostih opravilih krmilnika in da vašemu razredu krmilnika
dostop do katerega koli vira, ki ga lahko potrebuje. Z razširitvijo tega razreda ``Controller``
lahko pridobite prednosti nekaj pomagalnih metod.

Dodajte stavek ``use`` na vrh razreda ``Controller`` in nato spremenite
``HelloController``, da ga razširite v::

    // src/Acme/HelloBundle/Controller/HelloController.php
    namespace Acme\HelloBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;
    use Symfony\Component\HttpFoundation\Response;

    class HelloController extends Controller
    {
        public function indexAction($name)
        {
            return new Response('<html><body>Hello '.$name.'!</body></html>');
        }
    }

To dejansko ne spremeni ničesar o tem, kako vaš krmilnik deluje. V
naslednjem poglavju, se boste naučili o pomagalnih metodah, ki naredijo osnovni razred
krmilnika na voljo. Te metode so samo bližnjice za uporabo funkcionalnosti jedra
Symfony2, ki je na voljo za vas z ali brez uporabe osnovnega
razreda ``Controller``. Odličen način, da vidite jedro funkcionalnosti v delovanju,
je pogled v
sam razred :class:`Symfony\\Bundle\\FrameworkBundle\\Controller\\Controller`.

.. tip::

    Razširitev osnovnega razreda je *opcijska* v Symfony; vsebuje uporabne
    bližnjice vendar nič obveznega. Lahko tudi razširite
    :class:`Symfony\\Component\\DependencyInjection\\ContainerAware` ali uporabite
    lastnost class:`Symfony\\Component\\DependencyInjection\\ContainerAwareTrait`
    (če imate PHP 5.4). Objekt storitvenega kontejnerja bo nato dostopen
    preko lastnosti ``container``.

.. versionadded:: 2.4
    ``ContainerAwareTrait`` je bila predstavljena v Symfony 2.4.

.. note::

    Lahko tudi definirate vaše :doc:`krmilnike kot storitve </cookbook/controller/service>`.
    To je opcijsko, vendar vam lahko da več kontrole nad točnimi odvisnostmi,
    ki so injicirane v vaše krmilnike.

.. index::
   single: Controller; Common tasks

Pogosta opravila krmilnika
--------------------------

Čeprav lahko krmilnik naredi virtualno karkoli, bo večina krmilnikov opravila
enako osnovno opravilo vedno znova in znova. Ta opravila, kot je preusmeritev,
posredovanje, izpisovanje predlog in dostopanje do storitev jedra, so zelo enostavna
za upravljati v Symfony2.

.. index::
   single: Controller; Redirecting

Preusmeritve
~~~~~~~~~~~~

Če želite preusmeriti uporabnika k drugi strani, uporabite metodo ``redirect()``::

    public function indexAction()
    {
        return $this->redirect($this->generateUrl('homepage'));
    }

Metoda ``generateUrl()`` je samo pomagalna funkcija, ki generira URL
za dano usmeritev. Za več informacij, glejte poglavje
:doc:`Usmeritve </book/routing>`.

Privzeto metoda ``redirect()`` izvaja 302 (začasno) preusmeritev. Da
izvedete 301 (končno) preusmeritev, spremenite drugi argument::

    public function indexAction()
    {
        return $this->redirect($this->generateUrl('homepage'), 301);
    }

.. tip::

    Metoda ``redirect()`` je enostavno bližnjica, ki ustvari objekt ``Response``,
    ki se specializira v preusmerjanju uporabnika. Je ekvivalentna::

        use Symfony\Component\HttpFoundation\RedirectResponse;

        return new RedirectResponse($this->generateUrl('homepage'));

.. index::
   single: Controller; Forwarding

Posredovanje
~~~~~~~~~~~~

Lahko tudi enostavno posredujete k drugemu krmilniku interno z
metodo
:method:`Symfony\\Bundle\\FrameworkBundle\\Controller\\Controller::forward`
Namesto preusmerjanja uporabnikovega brskalnika, ta naredi notranji pod-zahtevek,
in kliče določeni krmilnik. Metoda ``forward()`` vrne objekt ``Response``,
ki je vrnjen iz tega krmilnika::

    public function indexAction($name)
    {
        $response = $this->forward('AcmeHelloBundle:Hello:fancy', array(
            'name'  => $name,
            'color' => 'green',
        ));

        // ... further modify the response or return it directly

        return $response;
    }

Bodite pozorni, saj metoda ``forward()`` uporablja enak niz, ki predstavlja
krmilnik uporabljen v nastavitvah usmerjanja. V tem primeru bo ciljni
razred krmilnika ``HelloController`` znotraj nekega ``AcmeHelloBundle``.
Polje podano metodi postanejo argumenti na rezultirajočemu krmilniku.
Ta enak vmesnik je uporabljen, ko se vključuje krmilnike v predloge (glejte
:ref:`templating-embedding-controller`). Ciljna metoda krmilnika bi morala
izgledati nekako sledeče::

    public function fancyAction($name, $color)
    {
        // ... create and return a Response object
    }

In samo ko izdelate krmilnik za usmeritev, vrstni red argumentov
za ``fancyAction`` ni pomemben. Symfony2 ujema ključe ime index-a
(npr. ``name``) z metodo imen argumentov (npr. ``$name``). Če
spremenite vrstni red argumentov, bo Symfony2 še vedno poslal pravilno
vrednost vsaki spremenljivki.

.. tip::

    Kot druge osnovne metode za ``Controller``, je metoda ``forward`` samo
    bližnjica za jedro funkcionalnosti Symfony2. Posredovanje je doseženo
    direktno z dupliciranjem trenutnega zahtevka. Ko je ta
    :ref:`pod zahtevek <http-kernel-sub-requests>` izvršen preko ``http_kernel``
    storitve ``HttpKernel`` vrne objekt ``Response``::

        use Symfony\Component\HttpKernel\HttpKernelInterface;

        $path = array(
            '_controller' => 'AcmeHelloBundle:Hello:fancy',
            'name'        => $name,
            'color'       => 'green',
        );
        $request = $this->container->get('request');
        $subRequest = $request->duplicate(array(), null, $path);

        $httpKernel = $this->container->get('http_kernel');
        $response = $httpKernel->handle(
            $subRequest,
            HttpKernelInterface::SUB_REQUEST
        );

.. index::
   single: Controller; Rendering templates

.. _controller-rendering-templates:

Izpisovanje predlog
~~~~~~~~~~~~~~~~~~~

Čeprav ni zahteva, bo večina krmilnikov na koncu izpisala predlogo,
ki ni odgovorna za generiranje HTML (ali druge oblike) za krmilnik.
Metoda ``renderView()`` izpiše predlogo in vrne njeno vsebino.
Vsebina iz predloge je lahko uporabljena za izdelavo objekta ``Response``::

    use Symfony\Component\HttpFoundation\Response;

    $content = $this->renderView(
        'AcmeHelloBundle:Hello:index.html.twig',
        array('name' => $name)
    );

    return new Response($content);

To je lahko narejeno celo v samo enem koraku z metodo ``render()``, ki
vrne objekt ``Response``, ki vsebuje vsebino iz predloge::

    return $this->render(
        'AcmeHelloBundle:Hello:index.html.twig',
        array('name' => $name)
    );

V obeh primerih bo izpisana predloga ``Resources/views/Hello/index.html.twig`` znotraj
``AcmeHelloBundle``.

Symfony motor predlog je razložen v podrobnosti v
poglavju :doc:`Predloge </book/templating>`.

.. tip::

    Lahko se celo izognete klicu metode ``render`` z uporabo anotacije ``@Template``.
    Glejte
    :doc:`dokumentacijo FrameworkExtraBundle </bundles/SensioFrameworkExtraBundle/annotations/view>`
    za več podrobnosti.

.. tip::

    Metoda ``renderView`` je bližnjica za direktno uporabo storitve ``templating``.
    Storitev ``templating`` je lahko tudi direktno uporabljena::

        $templating = $this->get('templating');
        $content = $templating->render(
            'AcmeHelloBundle:Hello:index.html.twig',
            array('name' => $name)
        );

.. note::

    Je tudi možno izpisovati globlje v poddirektorije, vendar
    bodite pozorni, da se izognete težavam izdelave vaše strukture direktorije neupravičeno
    izdelajte::

        $templating->render(
            'AcmeHelloBundle:Hello/Greetings:index.html.twig',
            array('name' => $name)
        );
        // index.html.twig found in Resources/views/Hello/Greetings
        // is rendered.

.. index::
   single: Controller; Accessing services

Dostopanje do drugih storitev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko razširjate osnovni razred krmilnika, lahko dostopate do katerekoli storitve Symfony2
preko metode ``get()``. Tu je na voljo nekaj pogostih storitev, ki jih morda potrebujete::

    $templating = $this->get('templating');

    $router = $this->get('router');

    $mailer = $this->get('mailer');

Obstajajo številne druge storitve, ki so na voljo in ste spodbujemi, da definirate
vašo lastno. Za izpis vseh storitev, ki so na voljo, uporabite ukaz konzole
``container:debug``:

.. code-block:: bash

    $ php app/console container:debug

Za več informacij, glejte poglavje :doc:`/book/service_container`.

.. index::
   single: Controller; Managing errors
   single: Controller; 404 pages

Upravljanje napak in strani 404
-------------------------------

Ko se stvari ne najde, bi se morali dobro igrati s protokolom HTTP in
vrniti odziv 404. Da to naredite, boste vrgli poseben tip izjeme.
Če razširjate osnovni razred krmilnika, naredite sledeče::

    public function indexAction()
    {
        // retrieve the object from database
        $product = ...;
        if (!$product) {
            throw $this->createNotFoundException('The product does not exist');
        }

        return $this->render(...);
    }

Metoda ``createNotFoundException()`` ustvari poseben objekt ``NotFoundHttpException``,
ki na koncu sproži odziv HTTP 404 znotraj Symfony.

Seveda boste svobodni, da vržete katerikoli razred ``Exception`` v vašem krmilniku -
Symfony2 bo avtomatsko vrnil 500 HTTP kodo odziva.

.. code-block:: php

    throw new \Exception('Something went wrong!');

V vsakem primeru je prikazana stilska stran napake končnemu uporabniku in polna razhroščevalna
stran napake je prikazana razvijalcu (ko pogleda stran v razhroščevalnem načinu).
Tako te strani z napakami so lahko prilagojene po meri. Za podrobnosti, preberite
recept ":doc:`/cookbook/controller/error_pages`".

.. index::
   single: Controller; The session
   single: Session

Upravljanje seje
----------------

Symfony2 ponuja lep objekt seje, ki ga lahko uporabite, da shranite informacije
o uporabniku (bodisi prava oseba uporablja brskalnik, bot, ali spletna storitev)
med zahtevki. Privzeto, Symfony2 shranjuje atribute v piškotku
z uporabo prvotne PHP seje.

Shranjevanje in pridobivanje informacij iz seje je lahko enostavno dosežena
iz katerega koli krmilnika::

    use Symfony\Component\HttpFoundation\Request;

    public function indexAction(Request $request)
    {
        $session = $request->getSession();

        // store an attribute for reuse during a later user request
        $session->set('foo', 'bar');

        // get the attribute set by another controller in another request
        $foobar = $session->get('foobar');

        // use a default value if the attribute doesn't exist
        $filters = $session->get('filters', array());
    }

Te atributi bodo ostali uporabniku za preostanek te seje
uporabnika.

.. index::
   single: Session; Flash messages

Bliskovita (flash) sporočila
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Shranite lahko tudi manjša sporočila, ki bodo shranjena na uporabnikovi seji
za točno en dodatni zahtevek. To je uporabno, ko procesirate obrazec:
želite preusmeriti in imeti posebno sporočilo prikazano na *naslednjem* zahtevku.
Ti tipi sporočil so imenovani "bliskovita" sporočila.

Na primer, predstavljajte si, da procesirate pošiljanje obrazca::

    use Symfony\Component\HttpFoundation\Request;

    public function updateAction(Request $request)
    {
        $form = $this->createForm(...);

        $form->handleRequest($request);

        if ($form->isValid()) {
            // do some sort of processing

            $this->get('session')->getFlashBag()->add(
                'notice',
                'Your changes were saved!'
            );

            return $this->redirect($this->generateUrl(...));
        }

        return $this->render(...);
    }

Po proseciranju zahtevka krmilnik nastavi ``notice`` bliskovito sporočilo
in nato preusmeri. Ime (``notice``) ni pomembno - je samo, kar
uporabljate za identifikacijo tipa sporočila.

V predlogi naslednje akcije, bi sledeča koda morala biti uporabljena za izpis
sporočila ``notice``:

.. configuration-block::

    .. code-block:: html+jinja

        {% for flashMessage in app.session.flashbag.get('notice') %}
            <div class="flash-notice">
                {{ flashMessage }}
            </div>
        {% endfor %}

    .. code-block:: html+php

        <?php foreach ($view['session']->getFlash('notice') as $message): ?>
            <div class="flash-notice">
                <?php echo "<div class='flash-error'>$message</div>" ?>
            </div>
        <?php endforeach; ?>

Po načrtu so bliskovita sporočila mišljena, da živijo točno en zahtevek (so
"odstranjena v blisku"). So načrtovana, da so uporabljena med zahtevki točno kot
ste naredili v tem primeru.

.. index::
   single: Controller; Response object

Objekt odziva
-------------

Edina zahteva za krmilnik je, da vrnete objekt ``Response``.
Razred :class:`Symfony\\Component\\HttpFoundation\\Response` je PHP
abstrakcija okrog odziva HTTP - tekstovno osnovano sporočilo zapolnjeno z glavami
HTTP in vsebino, ki je poslana nazaj h klientu::

    use Symfony\Component\HttpFoundation\Response;

    // create a simple Response with a 200 status code (the default)
    $response = new Response('Hello '.$name, Response::HTTP_OK);

    // create a JSON-response with a 200 status code
    $response = new Response(json_encode(array('name' => $name)));
    $response->headers->set('Content-Type', 'application/json');

.. versionadded:: 2.4
    Podpora za statusno kodo HTTP konstant je bila predstavljena v Symfony 2.4.

.. tip::

    Lastnost ``headers`` je
    objekt :class:`Symfony\\Component\\HttpFoundation\\HeaderBag` z nekaj
    uporabnimi metodami za branje in otišanje glav ``Response``.
    Imena glav so normalizirana, da je njihova uporaba ``Content-Type`` ekvivalentna
    ``content-type`` ali celo ``content_type``.

.. tip::

    Na voljo so celo posebni razredi, ki naredijo določene vrste odzivov enostavnejše:

    - For JSON, there is :class:`Symfony\\Component\\HttpFoundation\\JsonResponse`.
      See :ref:`component-http-foundation-json-response`.
    - For files, there is :class:`Symfony\\Component\\HttpFoundation\\BinaryFileResponse`.
      See :ref:`component-http-foundation-serving-files`.

.. index::
   single: Controller; Request object

Objekt zahtevka
---------------

Poleg vrednosti prostorov usmeritve, ima krmilnik tudi dostop do
objekta ``Request``. Ogrodje injicira objekt ``Request`` v
krmilniku, če je spremenljivka namignjena s tipom z
:class:`Symfony\\Component\\HttpFoundation\\Request`::

    use Symfony\Component\HttpFoundation\Request;

    public function indexAction(Request $request)
    {
        $request->isXmlHttpRequest(); // is it an Ajax request?

        $request->getPreferredLanguage(array('en', 'fr'));

        $request->query->get('page'); // get a $_GET parameter

        $request->request->get('page'); // get a $_POST parameter
    }

Kot objekt ``Response``, zahtevke glave so shranjene v ``HeaderBag``
objektu in so enostavno dostopne.

Zaključne misli
---------------

Kadarkoli ustvarjate stran boste na koncu potrebovali napisati nekaj kode, ki
vsebuje logiko za to stran. V Symfony je to imenovan krmilnik,
in njegova PHP funkcija, ki lahko naredi karkoli, potrebuje za vračanje
končni objekt ``Response``, ki bo izpisan uporabniku.

Da naredite življenje enostavnejše, lahko izberete razširitev osnovnega razreda ``Controller``,
ki vsebuje bližnjice metod za mnoga pogosta opravila krmilnika. Na primer,
ker vam ni potrebno dodajati kode HTML v vaš krmilnik, lahko uporabite
metodo ``render()``, da izpišete in vrnete vsebino iz predloge.

V drugih poglavjih boste videli, kako je lahko krmilnik uporabljen, da pošlje in
pridobi objekte iz podatkovne baze, procesira pošiljanje obrazca, upravlja predpomnilnik in
več.

Naučite se več iz knjige receptov
---------------------------------

* :doc:`/cookbook/controller/error_pages`
* :doc:`/cookbook/controller/service`
