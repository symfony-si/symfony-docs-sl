.. index::
    single: Console; Events

Uporaba dogodkov
================

.. versionadded:: 2.3
    Konzolni dogodki so bili predstavljeni v Symfony 2.3.

Razred Application komponente Console vam omogoča, da se opcijsko vežete
v življenski cikel konzolne aplikacije preko dogodkov. Namesto ponovnega
izumljanja kolesa, Symfony uporablja komponento EventDispatcher, da opravi delo::

    use Symfony\Component\Console\Application;
    use Symfony\Component\EventDispatcher\EventDispatcher;

    $dispatcher = new EventDispatcher();

    $application = new Application();
    $application->setDispatcher($dispatcher);
    $application->run();

Dogodek ``ConsoleEvents::COMMAND``
----------------------------------

**Običajni nameni**: Delati nekaj preden se požene katerakoli ukaz (kot beleženje,
katerega ukaz se bo izvedel), ali prikaz nečesa o dogodku, ki se bo izvedel.

Ravno pred izvajanjem kateregakoli ukaza, je dogodek ``ConsoleEvents::COMMAND``
odposlan. Poslušalci dobijo dogodek
:class:`Symfony\\Component\\Console\\Event\\ConsoleCommandEvent`::

    use Symfony\Component\Console\Event\ConsoleCommandEvent;
    use Symfony\Component\Console\ConsoleEvents;

    $dispatcher->addListener(ConsoleEvents::COMMAND, function (ConsoleCommandEvent $event) {
        // get the input instance
        $input = $event->getInput();

        // get the output instance
        $output = $event->getOutput();

        // get the command to be executed
        $command = $event->getCommand();

        // write something about the command
        $output->writeln(sprintf('Before running command <info>%s</info>', $command->getName()));

        // get the application
        $application = $command->getApplication();
    });

Dogodek ``ConsoleEvents::TERMINATE``
------------------------------------

**Običajni nameni**: Za opravljanje nekaj akcij čiščenja za ukazom, ki
je bil izveden.

Ko je bil ukaz izvršen, se odpošlje dogodek ``ConsoleEvents::TERMINATE``.
Lahko je uporabljen za katerokole akcije, ki potrebujejo biti izvedene za vse
ukaze ali za čiščenje, kar ste inicializirali v poslušalcu ``ConsoleEvents::COMMAND``
(kot je pošiljanje dnevnikov, zapiranje povezave s podatkovno bazo, pošiljanje e-pošte ...).
Poslušalec lahko tudi spremeni izhodno kodo.

Poslušalci dobijo dogodek
:class:`Symfony\\Component\\Console\\Event\\ConsoleTerminateEvent`::

    use Symfony\Component\Console\Event\ConsoleTerminateEvent;
    use Symfony\Component\Console\ConsoleEvents;

    $dispatcher->addListener(ConsoleEvents::TERMINATE, function (ConsoleTerminateEvent $event) {
        // get the output
        $output = $event->getOutput();

        // get the command that has been executed
        $command = $event->getCommand();

        // display something
        $output->writeln(sprintf('After running command <info>%s</info>', $command->getName()));

        // change the exit code
        $event->setExitCode(128);
    });

.. tip::

    Ta dogodek je tudi odposlan, ko je vržena izjema s strani ukaza.
    Nato je odposlan ravno pred dogodkom ``ConsoleEvents::EXCEPTION``.
    Pridobljena izhodna koda v tem primeru je koda izjeme.

Dogodek ``ConsoleEvents::EXCEPTION``
------------------------------------

**Običajni nameni**: Ravna z izjemami vrženimi med izvajanjem ukaza.

Kadarkoli je vržena izjema s strani ukaza, se odpošlje dogodek
``ConsoleEvents::EXCEPTION``. Poslušalec lahko ovije ali spremeni izjemo
ali opravi karkoli uporabnega preden aplikacija vrže izjemo.

Poslušalci dobijo
:class:`Symfony\\Component\\Console\\Event\\ConsoleExceptionEvent` dogodek::

    use Symfony\Component\Console\Event\ConsoleExceptionEvent;
    use Symfony\Component\Console\ConsoleEvents;

    $dispatcher->addListener(ConsoleEvents::EXCEPTION, function (ConsoleExceptionEvent $event) {
        $output = $event->getOutput();

        $command = $event->getCommand();

        $output->writeln(sprintf('Oops, exception thrown while running command <info>%s</info>', $command->getName()));

        // get the current exit code (the exception code or the exit code set by a ConsoleEvents::TERMINATE event)
        $exitCode = $event->getExitCode();

        // change the exception to another one
        $event->setException(new \LogicException('Caught exception', $exitCode, $event->getException()));
    });
