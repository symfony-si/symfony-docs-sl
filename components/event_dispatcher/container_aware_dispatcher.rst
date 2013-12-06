.. index::
   single: Event Dispatcher; Service container aware

Event Dispatcher, ki se zaveda kontejnerja
==========================================

Uvod
----

Razred :class:`Symfony\\Component\\EventDispatcher\\ContainerAwareEventDispatcher` je
posebna implementacija razpošilja dogodkov, ki je združen v kontejner storitve,
ki je del :doc:`komponente Dependency Injection </components/dependency_injection/introduction>`.
Omogoča, da so storitve specificirane kot poslušatelji dogodkov, kar naredi event dispatcher
zelo močno.

Storitve so leno naložene, kar pomeni, da storitve pripete kot poslušalci, bodo ustvarjene
samo, če je dogodek razposlan, da zahteva te poslušalce.

Nastavitev
----------

Nastavitev je enostavna z injiciranjem a :class:`Symfony\\Component\\DependencyInjection\\ContainerInterface`
v :class:`Symfony\\Component\\EventDispatcher\\ContainerAwareEventDispatcher`::

    use Symfony\Component\DependencyInjection\ContainerBuilder;
    use Symfony\Component\EventDispatcher\ContainerAwareEventDispatcher;

    $container = new ContainerBuilder();
    $dispatcher = new ContainerAwareEventDispatcher($container);

Dodajanje poslušalcev
---------------------

T.i. *Container Aware Event Dispatcher* lahko ali naloži določene storitve
direktno, ali storitve, ki implementirajo :class:`Symfony\\Component\\EventDispatcher\\EventSubscriberInterface`.

Sledeči primeri predpostavljajo, da je kontejner storitev bil naložen s katerimikoli
storitvami, ki so omenjene.

.. note::

    Storitve morajo biti označene kot javne (public) v kontejnerju.

Dodajanje storitev
~~~~~~~~~~~~~~~~~~

Da povežete obstoječe definicije storitev, uporabite
:method:`Symfony\\Component\\EventDispatcher\\ContainerAwareEventDispatcher::addListenerService`
metodo, kjer je ``$callback`` polje ``array($serviceId, $methodName)``::

    $dispatcher->addListenerService($eventName, array('foo', 'logListener'));

Dodajanje naročitvenih storitev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

``EventSubscribers`` so lahko dodani z uporabo
:method:`Symfony\\Component\\EventDispatcher\\ContainerAwareEventDispatcher::addSubscriberService`
metode, kjer je prvi argument ID storitve naročene storitve
in drugi argument je ime razreda storitve (ki mora implementirati)
:class:`Symfony\\Component\\EventDispatcher\\EventSubscriberInterface`) kot sledi::

    $dispatcher->addSubscriberService(
        'kernel.store_subscriber',
        'StoreSubscriber'
    );

``EventSubscriberInterface`` bo točno tak, kot pričakujete::

    use Symfony\Component\EventDispatcher\EventSubscriberInterface;
    // ...

    class StoreSubscriber implements EventSubscriberInterface
    {
        public static function getSubscribedEvents()
        {
            return array(
                'kernel.response' => array(
                    array('onKernelResponsePre', 10),
                    array('onKernelResponsePost', 0),
                ),
                'store.order'     => array('onStoreOrder', 0),
            );
        }

        public function onKernelResponsePre(FilterResponseEvent $event)
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
