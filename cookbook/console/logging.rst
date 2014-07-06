.. index::
   single: Console; Enabling logging

Kako pri konzolnih ukazih omogočiti beleženje
=============================================

Komponenta za konzolo privzeto ne ponuja nobenih zmožnosti zapisovanja v dnevnik.
Običajno poženete konzolne ukaze ročno in opazujete izpis, zaradi česar
beleženje ni zagotovljeno. Vendar so primeri, ko morda potrebujete
zapisovanje v dnevnik. Na primer, če poženete konzolne ukaze brez nadzora, kot
je iz t.i. "cron jobs" ali postavitvenih skript. Bolj enostavno je lahko uporabiti
Symfony-jeve zmožnosti zapisovanja v dnevnik namesto nastaviti druga orodja, da zberete
izpis konzole ina ga procesirate. To je lahko še poseben priročno, če že imate
nekaj obstoječih nastavitev za združevanje in analizo Symfony dnevnikov.

V osnovi boste potrebovali dva primera zapisovanja v dnevnik:
 * Ročno beleženje nekaj informacij iz vašega ukaza;
 * Beleženje neujetih izjem.

Ročno beleženje iz ukazne konzole
---------------------------------

To je res enostavno. Ko izdelate konzolni ukaz znotraj celotnega
ogrodja kot je opisano v ":doc:`/cookbook/console/console_command`", vaš ukaz
razširi :class:`Symfony\\Bundle\\FrameworkBundle\\Command\\ContainerAwareCommand`.
To pomeni, da lahko enostavno dostopate do standardne storitve beleženja preko
kontejnerja in ga uporabite za beleženje::

    // src/Acme/DemoBundle/Command/GreetCommand.php
    namespace Acme\DemoBundle\Command;

    use Symfony\Bundle\FrameworkBundle\Command\ContainerAwareCommand;
    use Symfony\Component\Console\Input\InputArgument;
    use Symfony\Component\Console\Input\InputInterface;
    use Symfony\Component\Console\Input\InputOption;
    use Symfony\Component\Console\Output\OutputInterface;
    use Psr\Log\LoggerInterface;

    class GreetCommand extends ContainerAwareCommand
    {
        // ...

        protected function execute(InputInterface $input, OutputInterface $output)
        {
            /** @var $logger LoggerInterface */
            $logger = $this->getContainer()->get('logger');

            $name = $input->getArgument('name');
            if ($name) {
                $text = 'Hello '.$name;
            } else {
                $text = 'Hello';
            }

            if ($input->getOption('yell')) {
                $text = strtoupper($text);
                $logger->warning('Yelled: '.$text);
            }
            else {
                $logger->info('Greeted: '.$text);
            }

            $output->writeln($text);
        }
    }

Odvisno od okolja v katerem poganjate vaš ukaz (in vaše nastavitve beleženja),
bi morali videti vnose beleženja v ``app/logs/dev.log`` ali ``app/logs/prod.log``.

Omogočanje avtomatskega beleženja izjem
---------------------------------------

Da naredite, da vaša konzolna aplikacija avtomatsko beleži nezaznane izjeme za
vse vaše ukaze, lahko uporabite :doc:`console events</components/console/events>`.

.. versionadded:: 2.3
    Dogodki konzole so bili predstavljeni v Symfony 2.3.

Najprej nastavite t.i. listener za dogodke konzolnih izjem v storitvenem kontejnerju:

.. configuration-block::

    .. code-block:: yaml

        # app/config/services.yml
        services:
            kernel.listener.command_dispatch:
                class: Acme\DemoBundle\EventListener\ConsoleExceptionListener
                arguments:
                    logger: "@logger"
                tags:
                    - { name: kernel.event_listener, event: console.exception }

    .. code-block:: xml

        <!-- app/config/services.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
                   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
                   xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd">

            <parameters>
                <parameter key="console_exception_listener.class">Acme\DemoBundle\EventListener\ConsoleExceptionListener</parameter>
            </parameters>

            <services>
                <service id="kernel.listener.command_dispatch" class="%console_exception_listener.class%">
                    <argument type="service" id="logger"/>
                    <tag name="kernel.event_listener" event="console.exception" />
                </service>
            </services>
        </container>

    .. code-block:: php

        // app/config/services.php
        use Symfony\Component\DependencyInjection\Definition;
        use Symfony\Component\DependencyInjection\Reference;

        $container->setParameter(
            'console_exception_listener.class',
            'Acme\DemoBundle\EventListener\ConsoleExceptionListener'
        );
        $definitionConsoleExceptionListener = new Definition(
            '%console_exception_listener.class%',
            array(new Reference('logger'))
        );
        $definitionConsoleExceptionListener->addTag(
            'kernel.event_listener',
            array('event' => 'console.exception')
        );
        $container->setDefinition(
            'kernel.listener.command_dispatch',
            $definitionConsoleExceptionListener
        );

Nato implementirajte dejanski listener::

    // src/Acme/DemoBundle/EventListener/ConsoleExceptionListener.php
    namespace Acme\DemoBundle\EventListener;

    use Symfony\Component\Console\Event\ConsoleExceptionEvent;
    use Psr\Log\LoggerInterface;

    class ConsoleExceptionListener
    {
        private $logger;

        public function __construct(LoggerInterface $logger)
        {
            $this->logger = $logger;
        }

        public function onConsoleException(ConsoleExceptionEvent $event)
        {
            $command = $event->getCommand();
            $exception = $event->getException();

            $message = sprintf(
                '%s: %s (uncaught exception) at %s line %s while running console command `%s`',
                get_class($exception),
                $exception->getMessage(),
                $exception->getFile(),
                $exception->getLine(),
                $command->getName()
            );

            $this->logger->error($message);
        }
    }

V kodi zgoraj, ko katerikoli ukaz vrže izjemo, bo listener
dobil dogodek. Lahko ga enostavno zabeležite s podajanjem storitve logger preko
storitvenih nastavitev. Vaša metoda dobi
objekt :class:`Symfony\\Component\\Console\\Event\\ConsoleExceptionEvent`,
ki ima metode za pridobitev informacij o dogodku in izjemi.

Beleženje ne-0 izhodnih statusov
--------------------------------

Zmožnosti beleženja konzole so lahko nadaljnje razširjene z beleženjem
ne-0 izhodnih statusov. Na ta način boste vedeli, če je imel ukaz kakšne napake,
celo če ni bila vržena nobena izjema.

Najprej nastavite listener za konzolne izključitvene dogodke v storitvenem kontejnerju:

.. configuration-block::

    .. code-block:: yaml

        # app/config/services.yml
        services:
            kernel.listener.command_dispatch:
                class: Acme\DemoBundle\EventListener\ConsoleTerminateListener
                arguments:
                    logger: "@logger"
                tags:
                    - { name: kernel.event_listener, event: console.terminate }

    .. code-block:: xml

        <!-- app/config/services.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
                   xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
                   xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd">

            <parameters>
                <parameter key="console_terminate_listener.class">Acme\DemoBundle\EventListener\ConsoleExceptionListener</parameter>
            </parameters>

            <services>
                <service id="kernel.listener.command_dispatch" class="%console_terminate_listener.class%">
                    <argument type="service" id="logger"/>
                    <tag name="kernel.event_listener" event="console.terminate" />
                </service>
            </services>
        </container>

    .. code-block:: php

        // app/config/services.php
        use Symfony\Component\DependencyInjection\Definition;
        use Symfony\Component\DependencyInjection\Reference;

        $container->setParameter(
            'console_terminate_listener.class',
            'Acme\DemoBundle\EventListener\ConsoleExceptionListener'
        );
        $definitionConsoleExceptionListener = new Definition(
            '%console_terminate_listener.class%',
            array(new Reference('logger'))
        );
        $definitionConsoleExceptionListener->addTag(
            'kernel.event_listener',
            array('event' => 'console.terminate')
        );
        $container->setDefinition(
            'kernel.listener.command_dispatch',
            $definitionConsoleExceptionListener
        );

Nato implementirajte dejanski listener::

    // src/Acme/DemoBundle/EventListener/ConsoleExceptionListener.php
    namespace Acme\DemoBundle\EventListener;

    use Symfony\Component\Console\Event\ConsoleTerminateEvent;
    use Psr\Log\LoggerInterface;

    class ConsoleTerminateListener
    {
        private $logger;

        public function __construct(LoggerInterface $logger)
        {
            $this->logger = $logger;
        }

        public function onConsoleTerminate(ConsoleTerminateEvent $event)
        {
            $statusCode = $event->getExitCode();
            $command = $event->getCommand();

            if ($statusCode === 0) {
                return;
            }

            if ($statusCode > 255) {
                $statusCode = 255;
                $event->setExitCode($statusCode);
            }

            $this->logger->warning(sprintf(
                'Command `%s` exited with status code %d',
                $command->getName(),
                $statusCode
            ));
        }
    }
