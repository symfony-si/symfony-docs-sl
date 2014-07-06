.. index::
    single: Console; Single command application

Gradnja eno-ukazne aplikacije
=============================

Ko gradite orodje za ukazno vrstico, lahko da ne boste potrebovali ponujate nekaj ukazov.
V takem primeru je pošiljanje imena ukaza vsakič lahko naporno. Na srečo
je možno odstraniti to potrebo z razširitvijo aplikacije::

    namespace Acme\Tool;

    use Symfony\Component\Console\Application;
    use Symfony\Component\Console\Input\InputInterface;

    class MyApplication extends Application
    {
        /**
         * Gets the name of the command based on input.
         *
         * @param InputInterface $input The input interface
         *
         * @return string The command name
         */
        protected function getCommandName(InputInterface $input)
        {
            // This should return the name of your command.
            return 'my_command';
        }

        /**
         * Gets the default commands that should always be available.
         *
         * @return array An array of default Command instances
         */
        protected function getDefaultCommands()
        {
            // Keep the core default commands to have the HelpCommand
            // which is used when using the --help option
            $defaultCommands = parent::getDefaultCommands();

            $defaultCommands[] = new MyCommand();

            return $defaultCommands;
        }

        /**
         * Overridden so that the application doesn't expect the command
         * name to be the first argument.
         */
        public function getDefinition()
        {
            $inputDefinition = parent::getDefinition();
            // clear out the normal first argument, which is the command name
            $inputDefinition->setArguments();

            return $inputDefinition;
        }
    }

Ko kličete vašo konzolno skripto, ukaz ``MyCommand`` bo potem vedno
uporabljen, brez da bi morali podajati njegovo ime.

Lahko tudi poenostavite, kako izvajate aplikacijo::

    #!/usr/bin/env php
    <?php
    // command.php
    use Acme\Tool\MyApplication;

    $application = new MyApplication();
    $application->run();
