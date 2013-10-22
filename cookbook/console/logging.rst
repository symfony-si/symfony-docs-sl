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
    use Symfony\Component\HttpKernel\Log\LoggerInterface;

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
                $logger->warn('Yelled: '.$text);
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

Da omogočite vaši konzolni aplikaciji avtomatsko zapisovanje v dnevnik neujete
izjeme za vse vaše ukaze, boste morali opraviti nekaj več dela.

Najprej izdelajte nov podrazred od :class:`Symfony\\Bundle\\FrameworkBundle\\Console\\Application`
in prepišite njegovo metodo :method:`Symfony\\Bundle\\FrameworkBundle\\Console\\Application::run`,
kjer se mora dogajati ravnanje z izjemami:

.. caution::

    Zaradi narave razreda :class:`Symfony\\Component\\Console\\Application`
    iz jedra, mora biti večina metode :method:`run <Symfony\\Bundle\\FrameworkBundle\\Console\\Application::run>`
    duplicirana in celo privatna lastnost ``originalAutoExit``
    ponovno implementirana. To služi kot primer, kaj *lahko* naredite v vaši
    kodi, čeprav je veliko tveganje, da se lahko kaj zlomi, ko nadgrajujete na
    prihodnje verzije Symfony-ja.

.. code-block:: php

    // src/Acme/DemoBundle/Console/Application.php
    namespace Acme\DemoBundle\Console;

    use Symfony\Bundle\FrameworkBundle\Console\Application as BaseApplication;
    use Symfony\Component\Console\Input\InputInterface;
    use Symfony\Component\Console\Output\OutputInterface;
    use Symfony\Component\Console\Output\ConsoleOutputInterface;
    use Symfony\Component\HttpKernel\Log\LoggerInterface;
    use Symfony\Component\HttpKernel\KernelInterface;
    use Symfony\Component\Console\Output\ConsoleOutput;
    use Symfony\Component\Console\Input\ArgvInput;

    class Application extends BaseApplication
    {
        private $originalAutoExit;

        public function __construct(KernelInterface $kernel)
        {
            parent::__construct($kernel);
            $this->originalAutoExit = true;
        }

        /**
         * Runs the current application.
         *
         * @param InputInterface  $input  An Input instance
         * @param OutputInterface $output An Output instance
         *
         * @return integer 0 if everything went fine, or an error code
         *
         * @throws \Exception When doRun returns Exception
         *
         * @api
         */
        public function run(InputInterface $input = null, OutputInterface $output = null)
        {
            // make the parent method throw exceptions, so you can log it
            $this->setCatchExceptions(false);

            if (null === $input) {
                $input = new ArgvInput();
            }

            if (null === $output) {
                $output = new ConsoleOutput();
            }

            try {
                $statusCode = parent::run($input, $output);
            } catch (\Exception $e) {

                /** @var $logger LoggerInterface */
                $logger = $this->getKernel()->getContainer()->get('logger');

                $message = sprintf(
                    '%s: %s (uncaught exception) at %s line %s while running console command `%s`',
                    get_class($e),
                    $e->getMessage(),
                    $e->getFile(),
                    $e->getLine(),
                    $this->getCommandName($input)
                );
                $logger->crit($message);

                if ($output instanceof ConsoleOutputInterface) {
                    $this->renderException($e, $output->getErrorOutput());
                } else {
                    $this->renderException($e, $output);
                }
                $statusCode = $e->getCode();

                $statusCode = is_numeric($statusCode) && $statusCode ? $statusCode : 1;
            }

            if ($this->originalAutoExit) {
                if ($statusCode > 255) {
                    $statusCode = 255;
                }
                // @codeCoverageIgnoreStart
                exit($statusCode);
                // @codeCoverageIgnoreEnd
            }

            return $statusCode;
        }

        public function setAutoExit($bool)
        {
            // parent property is private, so we need to intercept it in a setter
            $this->originalAutoExit = (Boolean) $bool;
            parent::setAutoExit($bool);
        }

    }

V kodi zgoraj, lahko onemogočite lovljenje izjem, da bo starševska metoda ``run``
vrgla vse izjeme. Ko je izjema ulovljena, jo enostavno zabeležite z dostopanjem
storitve ``logger`` iz storitvenega kontejnerja in nato upravljate
ostalo logiko na enak način kot to dela starševska metoda ``run``
(posebno ker starševska metoda
:method:`run <Symfony\\Bundle\\FrameworkBundle\\Console\\Application::run>`
ne bo upravljala z izpisovanjem izjem in upravljanjem statusov kod, ko je
``catchExceptions`` nastavljeno na false, to mora biti urejeno v prepisani
metodi).

Da razširjen razred Application ustrezno deluje v načinu konzolne lupine,
morate narediti manjši trik, da prestrežete ``autoExit`` podajalca in shranite
nastavitev v različno lastnost, saj je starševska lastnost privatna.

Da bo mogoče uporabiti vaš razširjen razred ``Application`` morate prilagoditi
skripto ``app/console``, da uporabite nov razred namesto privzetega::

    // app/console

    // ...
    // replace the following line:
    // use Symfony\Bundle\FrameworkBundle\Console\Application;
    use Acme\DemoBundle\Console\Application;

    // ...

To je vse! Zahvaljujoč avtomatskemu nalagalniku bo sedaj uporabljen vaš razred namesto
originalnega.

Beleženje ne-0 izhodnih statusov
--------------------------------

Zmožnosti beleženja konzole so lahko nadaljnje razširjene z beleženjem
ne-0 izhodnih statusov. Na ta način boste vedeli, če je imel ukaz kakšne napake,
celo če ni bila vržena nobena izjema.

Da to naredite, boste morali modificirati metodo ``run()`` vašega razširjenega razreda
``Application`` na sledeči način::

    public function run(InputInterface $input = null, OutputInterface $output = null)
    {
        // make the parent method throw exceptions, so you can log it
        $this->setCatchExceptions(false);

        // store the autoExit value before resetting it - you'll need it later
        $autoExit = $this->originalAutoExit;
        $this->setAutoExit(false);

        // ...

        if ($autoExit) {
            if ($statusCode > 255) {
                $statusCode = 255;
            }

            // log non-0 exit codes along with command name
            if ($statusCode !== 0) {
                /** @var $logger LoggerInterface */
                $logger = $this->getKernel()->getContainer()->get('logger');
                $logger->warn(sprintf('Command `%s` exited with status code %d', $this->getCommandName($input), $statusCode));
            }

            // @codeCoverageIgnoreStart
            exit($statusCode);
            // @codeCoverageIgnoreEnd
        }

        return $statusCode;
    }
