.. index::
    single: Event Dispatcher; Immutable

Nespremenljiv razpošiljatelj dogodkov
=====================================

:class:`Symfony\\Component\\EventDispatcher\\ImmutableEventDispatcher` je
zaklenjen ali zmrznjen razpošiljatelj dogodkov. Razpošiljatelj ne more registrirati novih
poslušalcev ali naročnikov.

``ImmutableEventDispatcher`` vzame drug razpošiljatelj dogodkov z vsemi
poslušalci in naročniki. Nespremenljivi razpošiljatelj je samo proksi tega
originalnega razpošiljatelja.

Da ga uporabite najprej izdelajte običajnega razpošiljatelja (``EventDispatcher`` ali
``ContainerAwareEventDispatcher``) in registrirajte nekaj poslušalcev ali
naročnikov::

    use Symfony\Component\EventDispatcher\EventDispatcher;

    $dispatcher = new EventDispatcher();
    $dispatcher->addListener('foo.action', function ($event) {
        // ...
    });

    // ...

Sedaj injicirajte to v ``ImmutableEventDispatcher``::

    use Symfony\Component\EventDispatcher\ImmutableEventDispatcher;
    // ...

    $immutableDispatcher = new ImmutableEventDispatcher($dispatcher);

Morali boste uporabiti ta nov razpošiljatelj v vaš projekt.

Če poskušate izvršiti eno izmed metod, ki modificira razpošiljatelja
(npr. ``addListener``), je vržena ``BadMethodCallException``.
