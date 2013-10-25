.. index::
    single: Console Helpers; Formatter Helper

Pomočnik oblike
===============

Pomočnik oblike ponuja funkcije za oblikovanje izpisa z barvami.
S tem pomočnikom lahko naredite bolj napredne stvari, kot v
:ref:`components-console-coloring`.

Vključen je :class:`Symfony\\Component\\Console\\Helper\\FormatterHelper`
v privzetem pomočniškem setu, ki ga lahko dobite s klicom
:method:`Symfony\\Component\\Console\\Command\\Command::getHelperSet`::

    $formatter = $this->getHelperSet()->get('formatter');

Metode vrnejo niz, ki ga boste običajno izpisali v konzoli s
podajanjem v metodo
:method:`OutputInterface::writeln <Symfony\\Component\\Console\\Output\\OutputInterface::writeln>`.

Izpis sporočil v sekcijo
------------------------

Symfony ponuja definiran stil, ko izpisuje sporočilo, ki pripada neki
"sekciji". Sekcijo izpiše v barvi in obkroženo z zavitimi oklepaji in
dejansko sporočilo desno od tega. Brez barve zgleda takole:

.. code-block:: text

    [SomeSection] Here is some message related to that section

Da ponovno sproducirate ta stil, lahko uporabite
:method:`Symfony\\Component\\Console\\Helper\\FormatterHelper::formatSection`
metodo::

    $formattedLine = $formatter->formatSection(
        'SomeSection',
        'Here is some message related to that section'
    );
    $output->writeln($formattedLine);

Izpis sporočila v bloku
-----------------------

Včasih boste želeli zmožnost izpisovanja celotenga bloka teksta z barvo
ozadja. Symfony to uporablja, ko izpisuje sporočila napak.

Če izpišete sporočilo napake na več kot eni vrstici ročno, boste
opazili, da je ozadje samo tako dolgo kot je vsaka individualna vrstica. Uporabite
:method:`Symfony\\Component\\Console\\Helper\\FormatterHelper::formatBlock`
za generaranje izpisa bloka::

    $errorMessages = array('Error!', 'Something went wrong');
    $formattedBlock = $formatter->formatBlock($errorMessages, 'error');
    $output->writeln($formattedBlock);

Kot lahko vidite, podajanje polja sporočil v
:method:`Symfony\\Component\\Console\\Helper\\FormatterHelper::formatBlock`
metodo izdela željeni izpis. Če podate ``true`` kot tretji parameter, bo blok
oblikovan z več zapolnjenosti (padding) (ena prazna vrstica zgoraj in spodaj
sporočila in 2 presledka na levi in desni).

Točen stil, ki ga uporabljate v bloku je odvisno od vas. V tem primeru, uporabljate
vnaprej definiran stil ``error``, vendar so na voljo tudi drugi stili, ali pa lahko
izdelate svoje. Glejte :ref:`components-console-coloring`.
