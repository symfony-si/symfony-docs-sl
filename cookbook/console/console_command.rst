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
``Command`` direktorij znotraj vašega paketa in izdelajte PHP datoteko s predpono
``Command.php`` za vsak ukaz, ki ga želite ponuditi. Na primer, če želite
razširiti AcmeDemoBundle (na voljo v Symfony standardni izdaji), da vas
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

Enako kot krmilniki, so lahko ukazi tudi deklarirani kotstoritve. Glejte
:doc:`namensko poglavje receptov </cookbook/console/commands_as_services>`
za podrobnosti.

Pridobitev storitev iz storitvenega kontejnerja
-----------------------------------------------

Z uporabo :class:`Symfony\\Bundle\\FrameworkBundle\\Command\\ContainerAwareCommand`
kot osnovnega razreda za ukaz (namesto bolj osnovnega
:class:`Symfony\\Component\\Console\\Command\\Command`), imate dostop do
storitvenega kontejnerja. Z drugimi besedami imate dostop do katerihkoli konfiguriranih storitev::

    protected function execute(InputInterface $input, OutputInterface $output)
    {
        $name = $input->getArgument('name');
        $logger = $this->getContainer()->get('logger');

        $logger->info('Executing command for '.$name);
        // ...
    }

Vendar zaradi `obsega kontejnerja </cookbook/service_container/scopes>`_ ta
koda ne deluje za nekatere storitve. Na primer, če poskusite dobiti storitev ``request``
ali katerokoli drugo storitev povezano tej, boste dobili sledečo napako:

.. code-block:: text

    You cannot create a service ("request") of an inactive scope ("request").

Premislite o sledečem primeru, ki uporablja storitev ``translator`` za
prevod nekaterih vsebin z uporabo ukaza konzole::

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

Če se poglobite v razrede komponente Translator, boste videli, da je storitev ``request``
zahtevana za dobiti lokalizacijo v katero so vsebine prevedene::

    // vendor/symfony/symfony/src/Symfony/Bundle/FrameworkBundle/Translation/Translator.php
    public function getLocale()
    {
        if (null === $this->locale && $this->container->isScopeActive('request')
            && $this->container->has('request')) {
            $this->locale = $this->container->get('request')->getLocale();
        }

        return $this->locale;
    }

Zato, ko uporabljate storitev ``translator`` znotraj ukaza, boste dobili
prejšnjo sporočilo napake *"You cannot create a service of an inactive scope"*.
Rešitev v tem primeru je enostavna kot nastavitev vrednosti lokalizacije eksplicitno
pred prevajanjem vsebin::

    protected function execute(InputInterface $input, OutputInterface $output)
    {
        $name = $input->getArgument('name');
        $locale = $input->getArgument('locale');

        $translator = $this->getContainer()->get('translator');
        $translator->setLocale($locale);

        if ($name) {
            $output->writeln($translator->trans('Hello %name%!', array('%name%' => $name)));
        } else {
            $output->writeln($translator->trans('Hello!'));
        }
    }

Vendar za ostale storitve je lahko rešitev bolj kompleksna. Za več podrobnosti
glejte :doc:`/cookbook/service_container/scopes`.

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
                    'name'    => 'Fabien',
                    '--yell'  => true,
                )
            );

            $this->assertRegExp('/.../', $commandTester->getDisplay());

            // ...
        }
    }

.. versionadded:: 2.4
    Od Symfony 2.4, ``CommandTester`` avtomatsko zazna ime
    ukaza za izvajanje. Pred Symfony 2.4 ste ga potrebovali podati preko
    ključa ``command``.


.. note::

    V posebnem primeru zgoraj parameter ``name`` in opcija ``--yell``
    nista obvezna, da ukaz deluje, vendar sta prikazana, da lahko vidite
    kako jih prilagoditi, ko kličete ukaz.

Da lahko uporabite celotno nastavljen storitveni kontejner za vaše konzolne teste,
lahko razširite vaš test iz
:class:`Symfony\\Bundle\\FrameworkBundle\\Test\\KernelTestCase`::

    use Symfony\Component\Console\Tester\CommandTester;
    use Symfony\Bundle\FrameworkBundle\Console\Application;
    use Symfony\Bundle\FrameworkBundle\Test\KernelTestCase;
    use Acme\DemoBundle\Command\GreetCommand;

    class ListCommandTest extends KernelTestCase
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
                    'name'    => 'Fabien',
                    '--yell'  => true,
                )
            );

            $this->assertRegExp('/.../', $commandTester->getDisplay());

            // ...
        }
    }

.. versionadded:: 2.5
    :class:`Symfony\\Bundle\\FrameworkBundle\\Test\\KernelTestCase` je bil
    pridobljen iz :class:`Symfony\\Bundle\\FrameworkBundle\\Test\\WebTestCase`
    v Symfony 2.5. ``WebTestCase`` deduje iz ``KernelTestCase``.
    ``WebTestCase`` ustvari instanco
    :class:`Symfony\\Bundle\\FrameworkBundle\\Client` preko ``createClient()``,
    medtem ko ``KernelTestCase`` ustvari instanco
    :class:`Symfony\\Component\\HttpKernel\\KernelInterface` preko
    ``createKernel()``.
