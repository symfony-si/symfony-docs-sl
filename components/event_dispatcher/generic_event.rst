.. index::
   single: Event Dispatcher

Generični Event objekt
======================

Osnovni razred :class:`Symfony\\Component\\EventDispatcher\\Event` ponujen iz
komponente Event Dispatcher namerno redko omogoča izdelavo
API specifičnih objektov z dedovanjem, ki uporablja OOP. To omogoča elegantno in
bralno kodo v kompleksnih aplikacijah.

Razred :class:`Symfony\\Component\\EventDispatcher\\GenericEvent` je na voljo
za udobje tistih, ki želite uporabljati samo en objekt dogodka skozi svojo
aplikacijo. Primeren je za večino namenov naravnost iz škatle, ker
sledi standardnemu opazovalnemu vzorcu, kjer objekt dogodka
povzema 'subjekt' dogodka, vendar ima dodatek opcijske ekstra
argumente.

Razred :class:`Symfony\\Component\\EventDispatcher\\GenericEvent` ima enostaven API kot
dodatek k osnovnemu razredu :class:`Symfony\\Component\\EventDispatcher\\Event`

* :method:`Symfony\\Component\\EventDispatcher\\GenericEvent::__construct`:
  konstruktor vzame subjekt dogodka in katerekoli argumente;

* :method:`Symfony\\Component\\EventDispatcher\\GenericEvent::getSubject`:
  Dobi subjekt;

* :method:`Symfony\\Component\\EventDispatcher\\GenericEvent::setArgument`:
  Nastavi arugment glede na ključ;

* :method:`Symfony\\Component\\EventDispatcher\\GenericEvent::setArguments`:
  Nastavi polje argumentov;

* :method:`Symfony\\Component\\EventDispatcher\\GenericEvent::getArgument`:
  Dobi argument glede na ključ;

* :method:`Symfony\\Component\\EventDispatcher\\GenericEvent::getArguments`:
  dobi vse argumente;

* :method:`Symfony\\Component\\EventDispatcher\\GenericEvent::hasArgument`:
  Vrne true, če ključ argumenta obstaja;

``GenericEvent`` tudi implementira :phpclass:`ArrayAccess` na dogodku
argumentov, kar naredi zelo priročno podajanje dodatnih argumentov glede na
dogodek subjekta.

Sledeči primeri prikazujejo primere uporabe, da dajo splošno predstavo o fleksibilnosti.
Primeri predpostavljajo, da so bili poslušalci dogodkov dodani razpošiljatelju.

Enostavno podajte subjekt::

    use Symfony\Component\EventDispatcher\GenericEvent;

    $event = new GenericEvent($subject);
    $dispatcher->dispatch('foo', $event);

    class FooListener
    {
        public function handler(GenericEvent $event)
        {
            if ($event->getSubject() instanceof Foo) {
                // ...
            }
        }
    }

Podajanje in procesiranje argumentov z uporabo :phpclass:`ArrayAccess` API-ja za dostopanje
argumentov dogodka::

    use Symfony\Component\EventDispatcher\GenericEvent;

    $event = new GenericEvent(
        $subject,
        array('type' => 'foo', 'counter' => 0)
    );
    $dispatcher->dispatch('foo', $event);

    echo $event['counter'];

    class FooListener
    {
        public function handler(GenericEvent $event)
        {
            if (isset($event['type']) && $event['type'] === 'foo') {
                // ... do something
            }

            $event['counter']++;
        }
    }

Filtriranje podatkov::

    use Symfony\Component\EventDispatcher\GenericEvent;

    $event = new GenericEvent($subject, array('data' => 'foo'));
    $dispatcher->dispatch('foo', $event);

    echo $event['data'];

    class FooListener
    {
        public function filter(GenericEvent $event)
        {
            strtolower($event['data']);
        }
    }
