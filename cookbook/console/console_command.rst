.. index::
   single: Console; Create commands

Kako izdelati ukaz za konzolo
=============================

Stran o konzoli sekcije komponent (:doc:`/components/console/introduction`) pokriva
kako izdelati ukaz za konzolo. Ta članek receptov pokriva razlike,
ko izdelujete ukaze za konzolo znotraj Symfony2 ogrodja.

Avtomatska registracija ukazov
------------------------------

Da naredite konzolne ukaze na voljo avtomatsko v Symfony2, izdelajte
``Command`` direktorij znotraj vašega paketa in izdelajte php datoteko s predpono
``Command.php`` za vsak ukaz, ki ga želite ponuditi. Na primer, če želite
razširiti ``AcmeDemoBundle`` (na voljo v Symfony standardni izdaji), da vas
pozdravi iz ukazne vrstice, izdelajte ``GreetCommand.php`` in
dodajte sledeče vanjo::

    // src/Acme/DemoBundle/Command/GreetCommand.php
    namespace Acme\DemoBundle\Command;

    use Symfony\Bundle\FrameworkBundle\Command\ContainerAwareCommand;
    use Symfony\Component\Console\Input\InputArgument;
    use Symfony\Component\Console\Input\InputInterface;
    use Symfony\Component\Console\Input\InputOption;
    use Symfony\Component\Console\Output\OutputInterface;

    class GreetCommand extends ContainerAwareCommand
    {
        protected function configure()
        {
            $this
                ->setName('demo:greet')
                ->setDescription('Greet someone')
                ->addArgument('name', InputArgument::OPTIONAL, 'Who do you want to greet?')
                ->addOption('yell', null, InputOption::VALUE_NONE, 'If set, the task will yell in uppercase letters')
            ;
        }

        protected function execute(InputInterface $input, OutputInterface $output)
        {
            $name = $input->getArgument('name');
            if ($name) {
                $text = 'Hello '.$name;
            } else {
                $text = 'Hello';
            }

            if ($input->getOption('yell')) {
                $text = strtoupper($text);
            }

            $output->writeln($text);
        }
    }

Ta ukaz bo sedaj avtomatsko na voljo za pogon:

.. code-block:: bash

    $ app/console demo:greet Fabien

.. _cookbook-console-dic:

Registracija ukazov v storitvenem kontejnerju
---------------------------------------------

.. versionadded:: 2.4
   Podpora za registracijo ukazov v storitvenem kontejnerju je bila dodana v
   verziji 2.4.

Namesto dodajanja ukaza v direktorij ``Command`` in da jih Symfony
avtomatsko odkriva za vas, lahko registrirate ukaze v storitvenem kontejnerju
z uporabo ``console.command`` značke:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        services:
            acme_hello.command.my_command:
                class: Acme\HelloBundle\Command\MyCommand
                tags:
                    -  { name: console.command }

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd">

            <service id="acme_hello.command.my_command"
                class="Acme\HelloBundle\Command\MyCommand">
                <tag name="console.command" />
            </service>
        </container>

    .. code-block:: php

        // app/config/config.php

        $container
            ->register('acme_hello.command.my_command', 'Acme\HelloBundle\Command\MyCommand')
            ->addTag('console.command')
        ;

.. tip::

    Registracija vašega ukaza kot storitve, vam da več kontrole nad njeno
    lokacijo in storitvami, ki so injicirani v njih. Vendar ni nikakršnih
    funkcionalnostnih prednosti, tako da ne potrebujete registrirati vaših ukazov kot storitev.

Pridobitev storitev iz storitvenega kontejnerja
-----------------------------------------------

Z uporabo :class:`Symfony\\Bundle\\FrameworkBundle\\Command\\ContainerAwareCommand`
kot osnovnega razreda za ukaz (namesto bolj osnovnega
:class:`Symfony\\Component\\Console\\Command\\Command`), imate dostop do
storitvenega kontejnerja. Z drugimi besedami imate dostop do kakršnih koli nastavljenih storitev.
Na primer, lahko bi enostavno razširili opravilo, da je prevedljivo::

    protected function execute(InputInterface $input, OutputInterface $output)
    {
        $name = $input->getArgument('name');
        $translator = $this->getContainer()->get('translator');
        if ($name) {
            $output->writeln($translator->trans('Hello %name%!', array('%name%' => $name)));
        } else {
            $output->writeln($translator->trans('Hello!'));
        }
    }

Testiranje ukazov
-----------------

Ko testirate ukaze uporabljenih kot del celotnega ogrodja
:class:`Symfony\\Bundle\\FrameworkBundle\\Console\\Application <Symfony\\Bundle\\FrameworkBundle\\Console\\Application>` bi moral biti uporabljen
namesto
:class:`Symfony\\Component\\Console\\Application <Symfony\\Component\\Console\\Application>`::

    use Symfony\Component\Console\Tester\CommandTester;
    use Symfony\Bundle\FrameworkBundle\Console\Application;
    use Acme\DemoBundle\Command\GreetCommand;

    class ListCommandTest extends \PHPUnit_Framework_TestCase
    {
        public function testExecute()
        {
            // mock the Kernel or create one depending on your needs
            $application = new Application($kernel);
            $application->add(new GreetCommand());

            $command = $application->find('demo:greet');
            $commandTester = new CommandTester($command);
            $commandTester->execute(
                array(
                    'command' => $command->getName(),
                    'name'    => 'Fabien',
                    '--yell'  => true,
                )
            );

            $this->assertRegExp('/.../', $commandTester->getDisplay());

            // ...
        }
    }

.. note::

    V posebnem primeru zgoraj parameter ``name`` in opcija ``--yell``
    nista obvezna, da ukaz deluje, vendar sta prikazana, da lahko vidite
    kako jih prilagoditi, ko kličete ukaz.

Da lahko uporabite celotno nastavljen storitveni kontejner za vaše konzolne teste,
lahko razširite vaš test iz
:class:`Symfony\\Bundle\\FrameworkBundle\\Test\\WebTestCase`::

    use Symfony\Component\Console\Tester\CommandTester;
    use Symfony\Bundle\FrameworkBundle\Console\Application;
    use Symfony\Bundle\FrameworkBundle\Test\WebTestCase;
    use Acme\DemoBundle\Command\GreetCommand;

    class ListCommandTest extends WebTestCase
    {
        public function testExecute()
        {
            $kernel = $this->createKernel();
            $kernel->boot();

            $application = new Application($kernel);
            $application->add(new GreetCommand());

            $command = $application->find('demo:greet');
            $commandTester = new CommandTester($command);
            $commandTester->execute(
                array(
                    'command' => $command->getName(),
                    'name'    => 'Fabien',
                    '--yell'  => true,
                )
            );

            $this->assertRegExp('/.../', $commandTester->getDisplay());

            // ...
        }
    }
