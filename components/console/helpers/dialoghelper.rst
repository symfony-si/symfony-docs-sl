.. index::
    single: Console Helpers; Dialog Helper

Pomočnik Dialog
===============

:class:`Symfony\\Component\\Console\\Helper\\DialogHelper` ponuja
funkcije, ki vprašajo uporabnika za več informacij. Vključen je v privzeti
skupek pomočnikov (helpers), ki jih lahko dobite s klicom
:method:`Symfony\\Component\\Console\\Command\\Command::getHelperSet`::

    $dialog = $this->getHelperSet()->get('dialog');

Vse metode znotraj Dialog pomočnika imajo
:class:`Symfony\\Component\\Console\\Output\\OutputInterface` kot prvega od
argumentov, vprašanje kot drugi argument in privzeto vrednost kot zadnji
argument.

Vprašanje uporabnika za potrditev
---------------------------------

Predpostavimo, da želite potrditev akcije pred dejanskim izvajanjem. Dodajte
sledeče v vaš ukaz::

    // ...
    if (!$dialog->askConfirmation(
            $output,
            '<question>Continue with this action?</question>',
            false
        )) {
        return;
    }

V tem primeru bo uporabnik vprašan "Continue with this action?" in bo vrnilo
``true``, če uporabnik odgovori z ``y`` ali false v kateremkoli drugem primeru. Tretji
argument v ``askConfirmation`` je privzeta vrednost, ki se vrne, če uporabnik ne
vnese nobenega vnosa.

Vprašanje uporabnika za informacijo
-----------------------------------

Lahko tudi postavite vprašanje z več kot samo enostavnim yes/no odgovorom. Na primer,
če želite vedeti ime paketa, lahko dodate sledeče v vaš ukaz::

    // ...
    $bundle = $dialog->ask(
        $output,
        'Please enter the name of the bundle',
        'AcmeDemoBundle'
    );

Uporabnik bo vprašan "Please enter the name of the bundle". Lahko vpiše
neko ime, ki bo vrnjeno od metode ``ask``. Če pusti prazno, bo vrnjena
privzeta vrednost (``AcmeDemoBundle`` tukaj).

Avtomatsko izpolnjevanje
~~~~~~~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.2
    Avtomatsko izpolnjevanje za vprašanja je bilo dodano v Symfony 2.2.

Lahko tudi specificirate polje možnih odgovorov za dano vprašanje. Te
bodo avtomatsko izpolnjeni, kakor uporabnik vnaša::

    $dialog = $this->getHelperSet()->get('dialog');
    $bundleNames = array('AcmeDemoBundle', 'AcmeBlogBundle', 'AcmeStoreBundle');
    $name = $dialog->ask(
        $output,
        'Please enter the name of a bundle',
        'FooBundle',
        $bundleNames
    );

Skrivanje uporabnikovega odziva
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.2
    Metoda ``askHiddenResponse`` je bila dodana v Symfony 2.2.

Lahko tudi postavite vprašanje in skrijete odziv. To je posebno
priročno za gesla::

    $dialog = $this->getHelperSet()->get('dialog');
    $password = $dialog->askHiddenResponse(
        $output,
        'What is the database password?',
        false
    );

.. caution::

    Ko vprašate za skrit odziv, bo Symfony uporabil ali binarni, spremenljiv
    stty način ali uporabil drug trik, da skrije odziv. Če ni noben na voljo,
    se bo nadomestilo in omogočilo, da bo odziv viden, razen če podate ``false``
    kot tretji argument kot v primeru zgoraj. V tem primeru, bo vržena izjema
    RuntimeException.

Preverjanje odgovora
--------------------

Lahko tudi preverite odgovor. Na primer v zadnjem primeru, ste vprašali
za ime paketa. Če sledimo Symfony2 konvencijam imen, bi moralo imeti
na koncu predpono ``Bundle``. To lahko preverite z uporabo metode
:method:`Symfony\\Component\\Console\\Helper\\DialogHelper::askAndValidate`::

    // ...
    $bundle = $dialog->askAndValidate(
        $output,
        'Please enter the name of the bundle',
        function ($answer) {
            if ('Bundle' !== substr($answer, -6)) {
                throw new \RunTimeException(
                    'The name of the bundle should be suffixed with \'Bundle\''
                );
            }
            return $answer;
        },
        false,
        'AcmeDemoBundle'
    );

Ta metoda ima 2 nova argumenta, celotni podpis je::

    askAndValidate(
        OutputInterface $output,
        string|array $question,
        callback $validator,
        integer $attempts = false,
        string $default = null
    )

``$validator`` je vrnjeni klic, ki ravna s preverjanjem. Moral bi
vreči izjemo, če gre kaj narobe. Sporočilo izjeme je prikazano v konzoli,
tako da je dobra praksa, da se doda nekaj uporabnik informacij vanjo. Funkcija
vrnjenega klica bi morala tudi vrniti vrednost uporabnikovega vnosa, če je
preverjanje uspešno.

Lahko nastavite največje število, kolikokrat vprašati v argumentu ``$attempts``.
Če dosežete to največje število, bo uporabljena privzeta vrednost, ki je
dana v zadnjem argumentu. Uporaba ``false`` pomeni, da je število poskusov
neskončno. Uporabnik bo spraševan, dokler ponuja neveljaven odgovor in bo
uspel nadaljevati samo, če je njegov vnos veljaven.

Skrivanje uporabnikovega odziva
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.2
    Metoda ``askHiddenResponseAndValidate`` je bila dodana v Symfony 2.2.

Lahko tudi vprašate in preverite skriti odziv::

    $dialog = $this->getHelperSet()->get('dialog');

    $validator = function ($value) {
        if (trim($value) == '') {
            throw new \Exception('The password can not be empty');
        }
    };

    $password = $dialog->askHiddenResponseAndValidate(
        $output,
        'Please enter your password',
        $validator,
        20,
        false
    );

Če želite dovoliti, da je odziv viden, če ne more biti skrit zaradi
nekega razloga, podajte true kot peti argument.

Omogočite uporabniku, da izbere iz seznama odgovorov
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.2
    Metoda :method:`Symfony\\Component\\Console\\Helper\\DialogHelper::select`
    je bila dodana v Symfony 2.2.

Če imate vnaprej definiran skupek odgovorov, katere lahko uporabnik izbira,
lahko uporabite metodo ``ask`` opisano zgoraj ali za zagotovitev, da je uporabnik
ponudil pravilen odgovor, metodo ``askAndValidate``. Obe imata
slabost, da morate upravljati nepravilne vrednosti sami.

Namesto tega lahko uporabite samo metodo
:method:`Symfony\\Component\\Console\\Helper\\DialogHelper::select`,
ki zagotavlja, da uporabnik lahko vnese samo veljaven niz iz vnaprej
definiranega seznama::

    $dialog = $app->getHelperSet()->get('dialog');
    $colors = array('red', 'blue', 'yellow');

    $color = $dialog->select(
        $output,
        'Please select your favorite color (default to red)',
        $colors,
        0
    );
    $output->writeln('You have just selected: ' . $colors[$color]);

    // ... do something with the color

Opcija, ki bi morala biti privzeto izbrana je ponujena kot četrti
argument. Privzeto je ``null``, kar pomeni, da nobena opcija ni privzeta.

Če uporabnik vnese neveljaven niz, je prikazano sporočilo napake in uporabnika
se vpraša, da ponudi odgovor drugič, dokler vnaša veljaven niz, ali je doseženo
največje število poskusov (kar lahko definirate v petem argumentu).
Privzeta vrednost za poskuse je ``false``, kar pomeni neskončno
poskusov. Lahko definirate vaša lastna sporočila napak v šestem argumentu.

.. versionadded:: 2.3
    Podpora za več izbir je bila dodana v Symfony 2.3.

Več izbir
.........

Včasih se lahko poda več odgovorov. DialogHelper ponuja to
lastnost z uporabo vrednosti ločenih z vejico. To je privzeto onemogočeno,
da to omogočite, nastavite sedmi argument na ``true``::

    // ...

    $selected = $dialog->select(
        $output,
        'Please select your favorite color (default to red)',
        $colors,
        0,
        false,
        'Value "%s" is invalid',
        true // enable multiselect
    );

    $selectedColors = array_map(function($c) use ($colors) {
        return $colors[$c];
    }, $selected);

    $output->writeln('You have just selected: ' . implode(', ', $selectedColors));

Sedaj ko uporabnik vnese ``1,2``, bo rezultat: ``You have just selected: blue, yellow``.

Testiranje ukaza, ki pričakuje vhod
-----------------------------------

Če želite pisati teste enot za ukaz, ki pričakuje nekakšen vnos
iz ukazne vrstice, morate prepisati HelperSet uporabljen s strani ukaza::

    use Symfony\Component\Console\Helper\DialogHelper;
    use Symfony\Component\Console\Helper\HelperSet;

    // ...
    public function testExecute()
    {
        // ...
        $commandTester = new CommandTester($command);

        $dialog = $command->getHelper('dialog');
        $dialog->setInputStream($this->getInputStream('Test\n'));
        // Equals to a user inputing "Test" and hitting ENTER
        // If you need to enter a confirmation, "yes\n" will work

        $commandTester->execute(array('command' => $command->getName()));

        // $this->assertRegExp('/.../', $commandTester->getDisplay());
    }

    protected function getInputStream($input)
    {
        $stream = fopen('php://memory', 'r+', false);
        fputs($stream, $input);
        rewind($stream);

        return $stream;
    }

Z nastavitvijo inputStream od ``DialogHelper``, oponašate, kar bi
konzola naredila interno z vsemi uporabnikovimi vnosi preko cli-ja. Na ta način
lahko testirate katerokoli uporabnikovo interakcijo (celo kompleksne) s podajanjem
primernih vnosnih streamov.
