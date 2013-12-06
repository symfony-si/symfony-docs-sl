.. index::
   single: Event Dispatcher
   single: Components; EventDispatcher

Komponenta Event Dispatcher
===========================

Uvod
----

Objektno orientirana koda je prišla dovolj daleč, da zagotavlja razširljivost kode. Z
izdelavo razredov, ki imajo dobro definirane odgovornosti vaša koda postane
bolj fleksibilna in razvijalec jo lahko razširi s pod razredi, da spremeni njeno
obnašanje. Vendar, če želi deliti svoje spremembe z ostalimi razvijalci, ki so
tudi naredili svoje lastne podrazrede, dedovanje kode ni več odgovor.

Razmislite o realnem primeru, kjer želite ponuditi sistem vtičnikov za
vaš projekt. Vtičnik bi moral biti zmožen dodati metode ali narediti nekaj pred
ali po izvršitvi metode brez vmešavanja z ostalimi vtičniki. To ni
enostaven problem za rešiti s posameznim dedovanjem in več dedovanj
(je možno s PHP) ima svoje slabe strani.

Symfony2 Event Dispatcher komponenta implementira `Mediator`_ vzorec na
enostaven in efektiven način, da naredi vse te stvari možne in naredi vaše
projekte resnično razširljive.

Vzamimo enostaven primer iz :doc:`/components/http_kernel/introduction`. Enkrat ko
je ``Response`` objekt ustvarjen, je lahko uporabno omogočiti drugim elementom
v sistemu, da ga spremenijo (npr. dodajanje nekaterih glav predpomnilnika) preden je dejansko
uporabljen. Da naredimo to možno, Symfony2 jedro vrže dogodek (event) -
``kernel.response``. Deluje sledeče:

* T.i. *listener* (PHP objekt) pove centralnemu *dispatcher* objektu, da želi
  poslušati dogodek ``kernel.response``;

* Na neki točki, Symfony2 jedro pove t.i. *dispatcher* objektu, da razpošlje
  dogodek ``kernel.response``, ki ga poda z objektom ``Event``, ki ima
  dostop do ``Response`` objekta;

* Razpošiljatelj obvesti (t.j. pokliče metodo na) vse poslušalce
  dogodka ``kernel.response``, kar omogoča vsakemu od njih, da naredijo spremembe
  na objektu ``Response``.

.. index::
   single: Event Dispatcher; Events

Namestitev
----------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestitev preko Composer-ja </components/using_components>` (``symfony/event-dispatcher`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/EventDispatcher).

Uporaba
-------

Dogodki
~~~~~~~

Ko je dogodek razposlan, je identificiran z unikatnim imenom (npr.
``kernel.response``), katerega poljubno število poslušalcev lahko posluša.
:class:`Symfony\\Component\\EventDispatcher\\Event` instanca je tudi ustvarjena
in poslana vsem poslušalcem. Kot boste videli kasneje, ``Event`` objekt
sam po sebi pogosto vsebuje podatke o dogodki, ki je razposlan.

.. index::
   pair: Event Dispatcher; Naming conventions

Konvencije poimenovanja
.......................

Unikatno ime dogodka je lahko katerikoli niz, vendar opcijsko sledi nekaj enostavnim
konvencijam poimenovanja:

* uporabite samo manjhne črke, številke, pike (``.``), in podčrtaje (``_``);

* imenom dodajte predpono imenskega prostora, ki mu sledi pika (npr. ``kernel.``);

* končajte imena z glagolom, ki indicira, katero akcijo je treba upoštevati (npr.
  ``request``).

Tu je nekaj primerov dobrih imenov dogodkov:

* ``kernel.response``
* ``form.pre_set_data``

.. index::
   single: Event Dispatcher; Event subclasses

Imena dogodkov in objekti dogodkov
..................................

Ko razpošiljatelj obvesti poslušalce, poda dejanski ``Event`` objekt
tem poslušalcem. Osnovni ``Event`` razred je zelo enostaven: vsebuje
metodo za ustavitev :ref:`razmnoževanja
dogodka <event_dispatcher-event-propagation>`, vendar niti nič več.

Pogostokrat podatki o določenih dogodki potrebujejo biti podani skupaj z
objektom ``Event``, da imajo poslušalci potrebne informacije. V primeru
dogodka ``kernel.response`` je ustvarjen objekt ``Event`` in podan
vsakemu poslušalcu, ki je dejansko tipa
:class:`Symfony\\Component\\HttpKernel\\Event\\FilterResponseEvent`,
podrazred osnovnega objekta ``Event``. Ta razred vsebuje metode kot so
``getResponse`` in ``setResponse``, ki omogočajo poslušalcem, da dobijo ali celo zamenjajo
objekt ``Response``.

Morala zgodbe je ta: Ko ustvarjate poslušalec za dogodek,
objekt ``Event``, ki je poslan poslušalcu je lahko posebni podrazred, ki
ima dodatne metode za pridobivanje informacij in odzivanja
dogodku.

Dispatcher
~~~~~~~~~~

T.i. Dispatcher (razpošiljatelj) je centralni objekt sistema razpošiljanja dogodkov. V
splošnem je ustvarjen posamezen razpošiljatelj, ki vzdržuje register
poslušalcev. Ko je dogodek razposlan preko razpošiljatelja, obvesti vse
poslušalce, ki so registrirani s tem dogodkom::

    use Symfony\Component\EventDispatcher\EventDispatcher;

    $dispatcher = new EventDispatcher();

.. index::
   single: Event Dispatcher; Listeners

Povezovanje poslušalcev
~~~~~~~~~~~~~~~~~~~~~~~

Da izkoristite obstoječi dogodek, morate povezati poslušalca z
razpošiljateljem, da je lahko obveščen, ko je objekt razposlan. Klic
razpošiljateljeve metode ``addListener()`` sodeluje s katerimkoli veljavnim PHP klicajočim (callable) z
dogodkom::

    $listener = new AcmeListener();
    $dispatcher->addListener('foo.action', array($listener, 'onFooAction'));

Metoda ``addListener()`` vzame do tri argumente:

* Ime dogodka (niz), ki ga ta poslušalec želi poslušati;

* PHP callable, ki bo obveščen, ko je objekt vržen, da ga
  posluša;

* Opcijsko prioritetno celo število (večje pomeni pomembnejše in zato
  bo poslušalec sprožen prej), ki določa, kdaj je poslušalec
  sprožen napram ostalim poslušalcem (privzeto je ``0``). Če imata dva poslušalca
  enako prioriteto, sta izvršena v vrstnem redu, ki sta bila dodana
  razpošiljatelju.

.. note::

    `PHP callable`_ je PHP spremenljivka, ki je lahko uporabljena s
    ``call_user_func()`` funkcijo in vrne ``true``, ko je podana
    ``is_callable()`` funckiji. Lahko je ``\Closure`` instanca, objekt,
    ki implementira __invoke metodo (ki je to, kar zaprtje dejansko je),
    niz, ki predstavlja funkcijo ali polje, ki predstavlajjo objektno
    metodo ali metodo razreda.

    Do sedaj ste videli, kako so PHP objekti lahko registrirani kot poslušalci. Lahko
    tudi registrirate PHP `Closures`_ kot poslušalce dogodka::

        use Symfony\Component\EventDispatcher\Event;

        $dispatcher->addListener('foo.action', function (Event $event) {
            // will be executed when the foo.action event is dispatched
        });

Ko je poslušalec registriran z razpošiljateljem, čaka dokler ni dogodek
obveščen. V zgornjem primeru, ko je ``foo.action`` dogodek razposlan,
razpošiljatelj pokliče ``AcmeListener::onFooAction`` metodo in poda
``Event`` objekt kot en argument::

    use Symfony\Component\EventDispatcher\Event;

    class AcmeListener
    {
        // ...

        public function onFooAction(Event $event)
        {
            // ... do something
        }
    }

V mnogih primerih je poseben podrazred ``Event``, ki je specifičen za dani dogodek,
podan poslušalcu. To da poslušalcu dostop do posebnih
informacij o dogodku. Preverite dokumentacijo ali implementacijo vsakega
dogodka za ugotovitev točne instance ``Symfony\Component\EventDispatcher\Event``,
ki je podana. Na primer dogodek ``kernel.response`` podaja
instanco ``Symfony\Component\HttpKernel\Event\FilterResponseEvent``::

    use Symfony\Component\HttpKernel\Event\FilterResponseEvent;

    public function onKernelResponse(FilterResponseEvent $event)
    {
        $response = $event->getResponse();
        $request = $event->getRequest();

        // ...
    }

.. _event_dispatcher-closures-as-listeners:

.. index::
   single: Event Dispatcher; Creating and dispatching an event

Izdelava in razpošiljanje dogodka
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Kot dodatek k registraciji poslušalcev z obstoječimi dogodki lahko ustvarite in
razpošljete vaše lastne dogodke. To je uporabno, ko ustvarjate tretje osebne knjižnice
in tudi ko želite obdržati različne komponente vašega lastnega sistema
fleksibilno in nevezano.

Statični ``Events`` razred
..........................

Predpostavimo, da želite izdelati nov dogodek - ``store.order`` - ki je razposlan
vsakič, ko je vrstni red ustvarjen znotraj vaše aplikacije. Da imamo stvari
organizirane, začnite z izdelavo razreda ``StoreEvents`` znotraj vaše aplikacije,
ki služi definiciji in dokumentaciji vašega dogodka::

    namespace Acme\StoreBundle;

    final class StoreEvents
    {
        /**
         * The store.order event is thrown each time an order is created
         * in the system.
         *
         * The event listener receives an
         * Acme\StoreBundle\Event\FilterOrderEvent instance.
         *
         * @var string
         */
        const STORE_ORDER = 'store.order';
    }

Bodite pozorni, saj ta razred dejansko ne *naredi* ničesar. Razlog
razreda ``StoreEvents`` je samo lokacija, kjer so lahko informacije o pogostih
dogodkih lahko centralizirane. Bodite pozorni tudi, saj bo poseben razred ``FilterOrderEvent``
podan vsakemu poslušalcu tega dogodka.

Izdelava objekta Event
......................

Kasneje, ko boste razposlali ta nov dogodek, boste ustvarili instanco ``Event``
in ga podali razpošiljatelju. Razpošiljatelj nato poda to isto instanco
vsakemu od poslušalcev dogodka. Če ne potrebujete podati nobenih
informacij vašim poslušalcem, lahko uporabite privzeti razred
``Symfony\Component\EventDispatcher\Event``. Večino časa vendar
*boste* morali podati informacij o dogodku vsakemu poslušalcu. Da to
dosežete, boste ustvarili nov razred, ki razširi
``Symfony\Component\EventDispatcher\Event``.

V tem primeru bo vsak poslušalec potreboval dostop do nekega pretvarjanega ``Order``
objekta. Ustvarite razred ``Event``, ki naredi to mogoče::

    namespace Acme\StoreBundle\Event;

    use Symfony\Component\EventDispatcher\Event;
    use Acme\StoreBundle\Order;

    class FilterOrderEvent extends Event
    {
        protected $order;

        public function __construct(Order $order)
        {
            $this->order = $order;
        }

        public function getOrder()
        {
            return $this->order;
        }
    }

Vsak poslušalec ima sedaj dostop do objekta ``Order`` preko ``getOrder``
metode.

Razpošiljanje dogodka
.....................

Metoda :method:`Symfony\\Component\\EventDispatcher\\EventDispatcher::dispatch`
obvesti vse poslušalce danega dogodka. Sprejme dva argumenta:
ime dogodka za razpošiljanje in ``Event`` instanco za podajanje vsakemu
poslušalcu tega dogodka::

    use Acme\StoreBundle\StoreEvents;
    use Acme\StoreBundle\Order;
    use Acme\StoreBundle\Event\FilterOrderEvent;

    // the order is somehow created or retrieved
    $order = new Order();
    // ...

    // create the FilterOrderEvent and dispatch it
    $event = new FilterOrderEvent($order);
    $dispatcher->dispatch(StoreEvents::STORE_ORDER, $event);

Bodite pozorni, da je posebni ``FilterOrderEvent`` objekt ustvarjen in podan
metodi ``dispatch``. Sedaj bo katerikoli poslušalec ``store.order`` dogodka
dobil ``FilterOrderEvent`` in imel dostop do ``Order`` objekta preko
metode ``getOrder``::

    // some listener class that's been registered for "store.order" event
    use Acme\StoreBundle\Event\FilterOrderEvent;

    public function onStoreOrder(FilterOrderEvent $event)
    {
        $order = $event->getOrder();
        // do something to or with the order
    }

.. index::
   single: Event Dispatcher; Event subscribers

.. _event_dispatcher-using-event-subscribers:

Uporaba naročnikov dogodka
~~~~~~~~~~~~~~~~~~~~~~~~~~

Najpogostejši način za poslušanje dogodka je registracija *poslušalca dogodka*
z razpošiljateljem. Ta poslušalec lahko posluša enega ali več dogodkov in je
obveščen vsakič, ko so te dogodki razposlani.

Drug način za poslušanje dogodkov je preko *naročnika dogodka*. Naročnik
dogodka je PHP razred, ki je zmožen povedati razpošiljatelju, točno na katere
dogodke bi moral biti naročen. Implementira
:class:`Symfony\\Component\\EventDispatcher\\EventSubscriberInterface`
vmesnik, ki zahteva eno statično metodo imenovano
``getSubscribedEvents``. Vzemimo sledeči primer naročnika, ki
je naročen na ``kernel.response`` in ``store.order`` dogodka::

    namespace Acme\StoreBundle\Event;

    use Symfony\Component\EventDispatcher\EventSubscriberInterface;
    use Symfony\Component\HttpKernel\Event\FilterResponseEvent;

    class StoreSubscriber implements EventSubscriberInterface
    {
        public static function getSubscribedEvents()
        {
            return array(
                'kernel.response' => array(
                    array('onKernelResponsePre', 10),
                    array('onKernelResponseMid', 5),
                    array('onKernelResponsePost', 0),
                ),
                'store.order'     => array('onStoreOrder', 0),
            );
        }

        public function onKernelResponsePre(FilterResponseEvent $event)
        {
            // ...
        }

        public function onKernelResponseMid(FilterResponseEvent $event)
        {
            // ...
        }

        public function onKernelResponsePost(FilterResponseEvent $event)
        {
            // ...
        }

        public function onStoreOrder(FilterOrderEvent $event)
        {
            // ...
        }
    }

To je zelo podobno razredu poslušalca razen, da razred sam po sebi lahko
pove razpošiljatelju, katere dogodke bi moral poslušati. Da registrate naročnika
z razpošiljateljem, uporabite
:method:`Symfony\\Component\\EventDispatcher\\EventDispatcher::addSubscriber`
metodo::

    use Acme\StoreBundle\Event\StoreSubscriber;

    $subscriber = new StoreSubscriber();
    $dispatcher->addSubscriber($subscriber);

Razpošiljatelj bo avtomatsko registriral naročnika za vsak dogodek, ki je
vrnjen od metode ``getSubscribedEvents``. Ta metoda vrne polje
indeksirano z imeni dogodkov in katere vrednosti so ali imena metod za klicanje ali
polje sestavljeno iz imena metode za klicanje in prioritete. Primer
zgoraj kaže, kako registrirati nekaj poslušalskih metod za isti dogodek v
naročniku in tudi kaže, kako podati prioriteto vsake metode poslušalca.
Višja ko je prioriteta, prej bo metoda klicana. V zgornjem
primeru, ko je sprožen dogodek ``kernel.response``, so metode
``onKernelResponsePre``, ``onKernelResponseMid`` in ``onKernelResponsePost``
klicane v tem vrstnem redu.

.. index::
   single: Event Dispatcher; Stopping event flow

.. _event_dispatcher-event-propagation:

Ustavitev toka/razmnoževanja dogodka
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

V nekaterih primerih je lahko smiselno za poslušalca, da prepreči kateremukoli drugem poslušalcu,
da je klican. Z drugimi besedami poslušalec mora biti sposoben povedati
razpošiljatelju, da ustavi vsa razmnoževanja dogodka za bodoče poslušalce (t.j.
ne obvestiti nobenih poslušalcev več). To se lahko doseže iz znotraj
poslušalca preko metode
:method:`Symfony\\Component\\EventDispatcher\\Event::stopPropagation`::

   use Acme\StoreBundle\Event\FilterOrderEvent;

   public function onStoreOrder(FilterOrderEvent $event)
   {
       // ...

       $event->stopPropagation();
   }

Sedaj katerikoli poslušalci za ``store.order``, ki še morda niso bili klicani, *ne* bodo
klicani.

Možno je odkriti, če je dogodek ustavljen z uporabo
metode :method:`Symfony\\Component\\EventDispatcher\\Event::isPropagationStopped`,
ki vrne logično vrednost::

    $dispatcher->dispatch('foo.event', $event);
    if ($event->isPropagationStopped()) {
        // ...
    }

.. index::
   single: Event Dispatcher; Event Dispatcher aware events and listeners

.. _event_dispatcher-dispatcher-aware-events:

Dogodki in poslušalci, ki se zavedajo EventDispatcher-ja
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``EventDispatcher`` vedno injicira sklic samega sebe v podanem dogodku
objekta. To pomeni, da imajo vsi poslušalci direkten dostop do
``EventDispatcher`` objekta, ki je obvestil poslušalca preko podane metode ``Event``
objekta
:method:`Symfony\\Component\\EventDispatcher\\Event::getDispatcher`.

To lahko vodi do nekaj naprednih aplikacij ``EventDispatcher``, ki vključuje
omogočanje, da poslušalci razpošiljajo druge objekte, veriženje dogodkov ali celo leno nalaganje
več poslušalcev v razposlani objekt. Primeri sledijo:

Leno nalaganje poslušalcev::

    use Symfony\Component\EventDispatcher\Event;
    use Acme\StoreBundle\Event\StoreSubscriber;

    class Foo
    {
        private $started = false;

        public function myLazyListener(Event $event)
        {
            if (false === $this->started) {
                $subscriber = new StoreSubscriber();
                $event->getDispatcher()->addSubscriber($subscriber);
            }

            $this->started = true;

            // ... more code
        }
    }

Razpošiljanje drugega dogodka iz znotraj poslušalca::

    use Symfony\Component\EventDispatcher\Event;

    class Foo
    {
        public function myFooListener(Event $event)
        {
            $event->getDispatcher()->dispatch('log', $event);

            // ... more code
        }
    }

Medtem ko je zgornje dovolj za večino uporab, če vaša aplikacija uporablja več
instanc ``EventDispatcher``, boste lahko morali posebej injicirati znano
instanco ``EventDispatcher`` v vaše poslušalce.  To je lahko narejeno
z uporabo konstruktorja ali nastavitvene injekcije kot sledi:

Injiciranje konstruktorja::

    use Symfony\Component\EventDispatcher\EventDispatcherInterface;

    class Foo
    {
        protected $dispatcher = null;

        public function __construct(EventDispatcherInterface $dispatcher)
        {
            $this->dispatcher = $dispatcher;
        }
    }

Ali nastavitev injiciranja::

    use Symfony\Component\EventDispatcher\EventDispatcherInterface;

    class Foo
    {
        protected $dispatcher = null;

        public function setEventDispatcher(EventDispatcherInterface $dispatcher)
        {
            $this->dispatcher = $dispatcher;
        }
    }

Izbira med dvema je dejansko stvar okusa. Mnogi imajo raje
injiciranje konstruktorja, saj so objekti v celoti injicirani v času
konstrukcije. Vendar ko imate dolg seznam odvisnosti, je uporaba nastavitve injiciranja
lahko ustrezen način, posebno za opcijske odvisnosti.

.. index::
   single: Event Dispatcher; Dispatcher shortcuts

.. _event_dispatcher-shortcuts:

Bližnjice razpošiljanja
~~~~~~~~~~~~~~~~~~~~~~~

Metoda :method:`EventDispatcher::dispatch <Symfony\\Component\\EventDispatcher\\EventDispatcher::dispatch>`
vedno vrne :class:`Symfony\\Component\\EventDispatcher\\Event`
objekt. To omogoča različne bližnjice. Na primer, če nek ne potrebuje
objekta dogodka po meri, se lahko ta enostavno zanaša na enostaven
:class:`Symfony\\Component\\EventDispatcher\\Event` objekt. Niti ne potrebujete
podati tega razpošiljatelju, saj ga bo ustvaril privzeto razen, če
ga posebej podate::

    $dispatcher->dispatch('foo.event');

Poleg tega EventDispatcher vedno vrne katerikoli objekt dogodka, ki je bil
razposlan, t.j. ali dogodek, ki je bil podan ali dogodek, ki je bil
ustvarjen interno z razpošiljateljem. To omogoča lepe bližnjice::

    if (!$dispatcher->dispatch('foo.event')->isPropagationStopped()) {
        // ...
    }

Ali::

    $barEvent = new BarEvent();
    $bar = $dispatcher->dispatch('bar.event', $barEvent)->getBar();

Ali::

    $bar = $dispatcher->dispatch('bar.event', new BarEvent())->getBar();

in tako naprej...

.. index::
   single: Event Dispatcher; Event name introspection

.. _event_dispatcher-event-name-introspection:

Introspekcija imena dogodka
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ker ``EventDispatcher`` že ve ime dogodka, ko ga razpošilja,
je ime dogodka tudi injicirano v
:class:`Symfony\\Component\\EventDispatcher\\Event` objekte, kar ga naredi na voljo
za poslušalce dogodka preko :method:`Symfony\\Component\\EventDispatcher\\Event::getName`
metode.

Ime dogodka (kot je z ostalimi podatki v objektu dogodka po meri) je lahko uporabljeno kot
del logike procesiranja poslušalca::

    use Symfony\Component\EventDispatcher\Event;

    class Foo
    {
        public function myEventListener(Event $event)
        {
            echo $event->getName();
        }
    }

Ostali razpošiljatelji
----------------------

Poleg pogosto uporabljenega ``EventDispatcher``, komponenta prihaja z 2
drugima razpošiljateljema:

* :doc:`/components/event_dispatcher/container_aware_dispatcher`
* :doc:`/components/event_dispatcher/immutable_dispatcher`

.. _Mediator: http://en.wikipedia.org/wiki/Mediator_pattern
.. _Closures: http://php.net/manual/en/functions.anonymous.php
.. _PHP callable: http://www.php.net/manual/en/language.pseudo-types.php#language.types.callback
.. _Packagist: https://packagist.org/packages/symfony/event-dispatcher
