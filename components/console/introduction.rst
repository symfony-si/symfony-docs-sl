.. index::
    single: Console; CLI
    single: Components; Console

Komponenta Console
==================

    Komponenta Console poenostavlja izdelavo lepih in testnih vmesnikov ukazne
    vrstice.

Komponenta Console vam omogoča izdelavo ukazov ukazne vrstice. Vaši konzolni
ukazi so lahko uporabljeni za katerokoli ponavljajoče se opravilo, kot so t.i.
cronjob-i, uvažanja ali ostala serijska opravila.

Namestitev
----------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestitev preko Composer-ja </components/using_components>` (``symfony/console`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Console).

.. note::

    Windows privzeto ne podpira nikakršnih ANSI barv zato komponenta Console odkrije in
    onemogoči barve, kjer Windows nima podpore. Čeprav, če Windows ni nastavljen
    z ANSI gonilnikom in se vaši konzolni ukazi sklicujejo na druge skripte, ki
    oddajajo ANSI barvne sekvence, bodo prikazani kot surovi izmaknjeni znaki.

    Da omogočite ANSI barvno podporo za Windows, prosimo namestite `ANSICON`_.

Izdelava osnovnega ukaza
------------------------

Da naredite konzolni ukaz, ki vas pozdravi iz ukazne vrstice, izdelajte ``GreetCommand.php``
in dodajte vanj sledeče::

    namespace Acme\DemoBundle\Command;

    use Symfony\Component\Console\Command\Command;
    use Symfony\Component\Console\Input\InputArgument;
    use Symfony\Component\Console\Input\InputInterface;
    use Symfony\Component\Console\Input\InputOption;
    use Symfony\Component\Console\Output\OutputInterface;

    class GreetCommand extends Command
    {
        protected function configure()
        {
            $this
                ->setName('demo:greet')
                ->setDescription('Greet someone')
                ->addArgument(
                    'name',
                    InputArgument::OPTIONAL,
                    'Who do you want to greet?'
                )
                ->addOption(
                   'yell',
                   null,
                   InputOption::VALUE_NONE,
                   'If set, the task will yell in uppercase letters'
                )
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

Potrebujete narediti tudi datoteko za pogon ukazne vrstice, ki izdela
``Application`` in doda ukaze vanjo::

    #!/usr/bin/env php
    <?php
    // app/console

    use Acme\DemoBundle\Command\GreetCommand;
    use Symfony\Component\Console\Application;

    $application = new Application();
    $application->add(new GreetCommand);
    $application->run();

Testirajte novi konzolni ukaz s sledečim pogonom:

.. code-block:: bash

    $ app/console demo:greet Fabien

To bo izpisalo sledeče v ukazno vrstico:

.. code-block:: text

    Hello Fabien

Lahko tudi uporabite opcijo ``--yell``, da naredite vse z velikimi črkami:

.. code-block:: bash

    $ app/console demo:greet Fabien --yell

To izpiše::

    HELLO FABIEN

.. _components-console-coloring:

Obarvanje izpisa
~~~~~~~~~~~~~~~~

Kadarkoli izpisujete tekst, ga lahko obdate z značkami, da obarvate njegov
izpis. Na primer::

    // green text
    $output->writeln('<info>foo</info>');

    // yellow text
    $output->writeln('<comment>foo</comment>');

    // black text on a cyan background
    $output->writeln('<question>foo</question>');

    // white text on a red background
    $output->writeln('<error>foo</error>');

Je možno definirate vaše lastne stile z uporabo razreda
:class:`Symfony\\Component\\Console\\Formatter\\OutputFormatterStyle`::

    $style = new OutputFormatterStyle('red', 'yellow', array('bold', 'blink'));
    $output->getFormatter()->setStyle('fire', $style);
    $output->writeln('<fire>foo</fire>');

Barve ospredja in ozadja, ki so na voljo, so: ``black``, ``red``, ``green``,
``yellow``, ``blue``, ``magenta``, ``cyan`` in ``white``.

In opcije, ki so na voljo so: ``bold``, ``underscore``, ``blink``, ``reverse`` in ``conceal``.

Lahko tudi naredite te barve in opcije znotraj imena značke::

    // green text
    $output->writeln('<fg=green>foo</fg=green>');

    // black text on a cyan background
    $output->writeln('<fg=black;bg=cyan>foo</fg=black;bg=cyan>');

    // bold text on a yellow background
    $output->writeln('<bg=yellow;options=bold>foo</bg=yellow;options=bold>');

Nivoji besedičenja
~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.3
   ``VERBOSITY_VERY_VERBOSE`` in ``VERBOSITY_DEBUG`` konstanti sta bili predstavljeni v
   verziji 2.3

Konzola ima 5 nivojev besedičenja. Te so definirani v
:class:`Symfony\\Component\\Console\\Output\\OutputInterface`:

=======================================  ==================================
Način                                    Vrednost
=======================================  ==================================
OutputInterface::VERBOSITY_QUIET         Ne izpiše nobenih sporočil
OutputInterface::VERBOSITY_NORMAL        Privzeti nivo besedičenja
OutputInterface::VERBOSITY_VERBOSE       Povečano besedičenje sporočil
OutputInterface::VERBOSITY_VERY_VERBOSE  Informativna neobvezna sporočila
OutputInterface::VERBOSITY_DEBUG         Razhroščevalna sporočila
=======================================  ==================================

Lahko specificirate nivo tihega besedičenja z opcijo ``--quiet`` ali ``-q``.
Opcija ``--verbose`` ali ``-v`` je uporabljena, ko želite povečan nivo
besedičenja.

.. tip::

    Celotna izjema sledi skladovnice je izpisana, če je nivo ``VERBOSITY_VERBOSE``
    ali več uporabljen.

Možno je izpisati sporočilo v ukazu za samo določen nivo besedičenja.
Na primer::

    if (OutputInterface::VERBOSITY_VERBOSE <= $output->getVerbosity()) {
        $output->writeln(...);
    }

.. versionadded:: 2.4
   Metode :method:`Symfony\\Component\Console\\Output\\Output::isQuiet`,
   :method:`Symfony\\Component\Console\\Output\\Output::isVerbose`,
   :method:`Symfony\\Component\Console\\Output\\Output::isVeryVerbose` in
   :method:`Symfony\\Component\Console\\Output\\Output::isDebug`
   so bile predstavljene v verziji 2.4

Na voljo so tudi bolj semantične metode, ki jih lahko uporabite za testiranje
vsakega nivoja besedičenja::

    if ($output->isQuiet()) {
        // ...
    }

    if ($output->isVerbose()) {
        // ...
    }

    if ($output->isVeryVerbose()) {
        // ...
    }

    if ($output->isDebug()) {
        // ...
    }

Ko je uporabljen quiet nivo, je vec izpis utišan, saj se vrne privzeta metoda
:method:`Symfony\Component\Console\Output::write <Symfony\\Component\\Console\\Output::write>`
brez dejanskega izpisa.

Uporaba argumentov ukazov
-------------------------

Najbolj zanimiv del ukazov so argumenti in opcije, ki
jih lahko naredite na voljo. Argumenti so nizi - ločeni s presledki - ki
pridejo za samim imenom ukaza. So naročeni in so lahko opcijski
ali zahtevani. Na primer dodajte opcijski argument ``last_name`` ukazu
in naredite argument ``name`` zahtevan::

    $this
        // ...
        ->addArgument(
            'name',
            InputArgument::REQUIRED,
            'Who do you want to greet?'
        )
        ->addArgument(
            'last_name',
            InputArgument::OPTIONAL,
            'Your last name?'
        );

Sedaj imate dostop do argumenta ``last_name`` v vašem ukazu::

    if ($lastName = $input->getArgument('last_name')) {
        $text .= ' '.$lastName;
    }

Ukaz je lahko uporabljen na katerikoli izmed sledečin načinov:

.. code-block:: bash

    $ app/console demo:greet Fabien
    $ app/console demo:greet Fabien Potencier

Je tudi možno omogočiti, da argument vzame seznam vrednosti (predstavljajte si,
da želite pozdraviti vse vaše prijatelje). Za to mora biti specificiran na koncu
seznama argumentov::

    $this
        // ...
        ->addArgument(
            'names',
            InputArgument::IS_ARRAY,
            'Who do you want to greet (separate multiple names with a space)?'
        );

Da to uporabite, samo specificirajte kakor veliko imen želite:

.. code-block:: bash

    $ app/console demo:greet Fabien Ryan Bernhard

Do argumenta ``names`` lahko dostopate kot polje::

    if ($names = $input->getArgument('names')) {
        $text .= ' '.implode(', ', $names);
    }

Na voljo so 3 variante argumentov, ki jih lahko uporabite:

===========================  ===============================================================================================================
Način                        Vrednost
===========================  ===============================================================================================================
InputArgument::REQUIRED      Argument je zahtevan
InputArgument::OPTIONAL      Argument je opcijski in zato je lahko izpuščen
InputArgument::IS_ARRAY      Argument lahko vsebuje neskončno število argumentov in mora biti uporabljen na koncu seznama argumentov
===========================  ===============================================================================================================

Lahko kombinirate ``IS_ARRAY`` z ``REQUIRED`` in ``OPTIONAL`` takole::

    $this
        // ...
        ->addArgument(
            'names',
            InputArgument::IS_ARRAY | InputArgument::REQUIRED,
            'Who do you want to greet (separate multiple names with a space)?'
        );

Uporaba opcij ukazov
--------------------

Z razliko argumentov, opcije niso sortirane (kar pomeni, da jih lahko specificirate v
kateremkoli redu) in so specificirane z dvema pomišljajema (npr. ``yell`` - lahko tudi
deklarirate eno-črkovno bližnjico, ki jo lahko kličete z enojnim pomišljajem kot npr.
``-y``). Opcije so *vedno* opcijske in so lahko nastavljene, da sprejmejo vrednost
(npr. ``dir=src``) ali poenostavljeno kot logična zastavica brez vrednosti (npr.
``yell``).

.. tip::

    Je tudi možno narediti, da opcija *opcijsko* sprejme vrednost (tako da
    ``--yell`` ali ``yell=loud`` delujeta). Opcije so lahko tudi konfigurirane,
    da sprejmejo polje vrednosti.

Na primer, dodajte novo opcijo ukazu, ki je lahko uporabljena za specifikacijo,
kolikokrat v vrstici bi moralo biti sporočilo izpisano::

    $this
        // ...
        ->addOption(
            'iterations',
            null,
            InputOption::VALUE_REQUIRED,
            'How many times should the message be printed?',
            1
        );

Nadalje uporabite to v ukazu, da izpišete sporočilo večkrat:

.. code-block:: php

    for ($i = 0; $i < $input->getOption('iterations'); $i++) {
        $output->writeln($text);
    }

Sedaj ko poženete opravilo, lahko opcijsko specificirate zastavico
``--iterations``:

.. code-block:: bash

    $ app/console demo:greet Fabien
    $ app/console demo:greet Fabien --iterations=5

Prvi primer se bo izpisal samo enkrat, saj je ``iterations`` prazna in
privzeto ``1`` (zadnji argument ``addOption``). Drugi primer
se bo izpisal petkrat.

Spomnite se, da opcij ne zanima o njihovem redu. Tako da karkoli od sledečega
bo delovalo:

.. code-block:: bash

    $ app/console demo:greet Fabien --iterations=5 --yell
    $ app/console demo:greet Fabien --yell --iterations=5

Na voljo so 4 opcijske variante, ki jih lahko uporabite:

===========================  =====================================================================================
Opcija                       Vrednost
===========================  =====================================================================================
InputOption::VALUE_IS_ARRAY  Ta opcija sprejme več vrednosti (npr. ``--dir=/foo --dir=/bar``)
InputOption::VALUE_NONE      Ne sprejme vnosa za to opcijo (npr. ``--yell``)
InputOption::VALUE_REQUIRED  Ta vrednost je zahtevana (npr. ``--iterations=5``), sama opcija je še vedno opcijska
InputOption::VALUE_OPTIONAL  Ta opcija lahko ali pa tudi nima vrednosti (npr. ``yell`` ali ``yell=loud``)
===========================  =====================================================================================

Lahko kombinirate ``VALUE_IS_ARRAY`` z ``VALUE_REQUIRED`` ali ``VALUE_OPTIONAL`` takole:

.. code-block:: php

    $this
        // ...
        ->addOption(
            'iterations',
            null,
            InputOption::VALUE_REQUIRED | InputOption::VALUE_IS_ARRAY,
            'How many times should the message be printed?',
            1
        );

Pomočniki konzole
-----------------

Konzolna komponenta lahko vsebuje skupek "helper-jev" - različna majhna
orodja, zmožna vam pomagati pri različnih opravilih:

* :doc:`/components/console/helpers/dialoghelper`: interaktivno vprašajte uporabnika za informacijo
* :doc:`/components/console/helpers/formatterhelper`: prilagodite barve izpisa
* :doc:`/components/console/helpers/progresshelper`: prikaže vrstico napredka
* :doc:`/components/console/helpers/tablehelper`: prikaže tabularne podatke kot tabelo

Ukazi za testiranje
-------------------

Symfony2 ponuja nekaj orodij, ki vam pomagajo testirati vaše ukaze. Najbolj
uporaben je razred :class:`Symfony\\Component\\Console\\Tester\\CommandTester`.
Uporablja posebne razrede vnosa in izpisa za poenostavitev testiranja brez prave
konzole::

    use Symfony\Component\Console\Application;
    use Symfony\Component\Console\Tester\CommandTester;
    use Acme\DemoBundle\Command\GreetCommand;

    class ListCommandTest extends \PHPUnit_Framework_TestCase
    {
        public function testExecute()
        {
            $application = new Application();
            $application->add(new GreetCommand());

            $command = $application->find('demo:greet');
            $commandTester = new CommandTester($command);
            $commandTester->execute(array('command' => $command->getName()));

            $this->assertRegExp('/.../', $commandTester->getDisplay());

            // ...
        }
    }

Metoda :method:`Symfony\\Component\\Console\\Tester\\CommandTester::getDisplay`
vrne, kar bi bilo prikazano med običajnim klicem iz
konzole.

Lahko testirate pošiljanje argumentov in opcij ukazu z njihovim podajanjem
kot polja metodi :method:`Symfony\\Component\\Console\\Tester\\CommandTester::execute`::

    use Symfony\Component\Console\Application;
    use Symfony\Component\Console\Tester\CommandTester;
    use Acme\DemoBundle\Command\GreetCommand;

    class ListCommandTest extends \PHPUnit_Framework_TestCase
    {
        // ...

        public function testNameIsOutput()
        {
            $application = new Application();
            $application->add(new GreetCommand());

            $command = $application->find('demo:greet');
            $commandTester = new CommandTester($command);
            $commandTester->execute(
                array('command' => $command->getName(), 'name' => 'Fabien')
            );

            $this->assertRegExp('/Fabien/', $commandTester->getDisplay());
        }
    }

.. tip::

    Lahko tudi testirate celotno konzolno aplikacijo z uporabo
    :class:`Symfony\\Component\\Console\\Tester\\ApplicationTester`.

Klic obstoječega ukaza
----------------------

Če je ukaz odvisen od drugega, ki se pred njim poganja, namesto spraševanja
uporabnika, da si zapomne vrstni red izvajanja, ga lahko kličete direktno sami.
To je tudi uporabno, če želite izdelati "meta" ukaz, ki samo požene
skupek drugih ukazov (na primer, vsi ukazi, ki potrebujejo biti pognani, ko
se koda projekta spremeni na produkcijskih strežnikih: čiščenje predpomnilnika,
generacija Doctrine2 proksijev, odlaganje Assetic sredstev, ...).

Klicanje ukaza iz drugega je enostavno::

    protected function execute(InputInterface $input, OutputInterface $output)
    {
        $command = $this->getApplication()->find('demo:greet');

        $arguments = array(
            'command' => 'demo:greet',
            'name'    => 'Fabien',
            '--yell'  => true,
        );

        $input = new ArrayInput($arguments);
        $returnCode = $command->run($input, $output);

        // ...
    }

Najprej najdete (:method:`Symfony\\Component\\Console\\Application::find`
ukaz, ki ga želite izvesti s podajanjem imena ukaza.

Potem potrebujete izdelati nov
:class:`Symfony\\Component\\Console\\Input\\ArrayInput` z argumenti in
opcijami, ki jih želite podati ukazu.

Na koncu, klicanje metode ``run()`` dejanstko izvede ukaz in
vrne vrnjeno kodo iz ukaza (vrnjena vrednost iz ukazne metode
``execute()``).

.. note::

    Večino časa, klicanje ukaza iz kode, ki se ne izvaja na
    ukazni vrstici ni dobra ideja iz večih razlogov. Najprej, izpis ukaza
    je optimiziran za konzolo. Vendar bolj pomembno, lahko razmišljate
    o ukazu, da je kot krmilnik; moral bi uporabljati model, da nekaj naredi
    in prikaže povratne informacije uporabniku. Torej namesto klicanja ukaza
    iz spletna, ponovno faktorirajte vašo kodo in premaknite logiko v nov
    razred.

Načite se več!
--------------

* :doc:`/components/console/usage`
* :doc:`/components/console/single_command_tool`

.. _Packagist: https://packagist.org/packages/symfony/console
.. _ANSICON: https://github.com/adoxa/ansicon/downloads
