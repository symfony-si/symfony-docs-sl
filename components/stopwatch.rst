.. index::
   single: Stopwatch
   single: Components; Stopwatch

Komponenta Stopwatch
====================

    Komponenta Stopwatch ponuja način profiliranja kode.

Namestitev
----------

Komponento lahko namestite na dva različna načina:

* :doc:`Namestitev preko Composer-ja</components/using_components>` (``symfony/stopwatch`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Stopwatch).

uporaba
-------

Komponenta Stopwatch ponuja enostaven in konsistenten način za merjenje izvrševanja
časa določenih delov kode, da vam ni potrebno konstantno razčlenjevati
mikro časa. Namesto tega uporabite enostaven
razred :class:`Symfony\\Component\\Stopwatch\\Stopwatch`::

    use Symfony\Component\Stopwatch\Stopwatch;

    $stopwatch = new Stopwatch();
    // Start event named 'eventName'
    $stopwatch->start('eventName');
    // ... some code goes here
    $event = $stopwatch->stop('eventName');

.. versionadded:: 2.5
    Metoda ``getEvent()`` je bila predstavljena v Symfony 2.5

Objekt :class:`Symfony\\Component\\Stopwatch\\StopwatchEvent` je lahko pridobljen
iz metod :method:`Symfony\\Component\\Stopwatch\\Stopwatch::start`,
:method:`Symfony\\Component\\Stopwatch\\Stopwatch::stop`,
:method:`Symfony\\Component\\Stopwatch\\Stopwatch::lap` in
:method:`Symfony\\Component\\Stopwatch\\Stopwatch::getEvent`.
Zadnja bi morala biti uporabljena, ko potrebujete pridobiti trajanje dogodka,
ko še vedno teče.

Dogodku lahko ponudite tudi ime kategorije::

    $stopwatch->start('eventName', 'categoryName');

Kategorije lahko smatrate kot način označevanja dogodkov. Na primer,
orodje Symfony Profiler uporablja kategorije za lepe barvno-kodne različne dogodke.

Obdobja
-------

Kot veste iz realnega sveta, vse štoparice prihajajo z dvema gumboma:
eden za pričetek in konec štoparice in drugi za merjenje vmesnega časa.
To je točno to, kar metoda :method:`Symfony\\Component\\Stopwatch\\Stopwatch::lap`
počne::

    $stopwatch = new Stopwatch();
    // Start event named 'foo'
    $stopwatch->start('foo');
    // ... some code goes here
    $stopwatch->lap('foo');
    // ... some code goes here
    $stopwatch->lap('foo');
    // ... some other code goes here
    $event = $stopwatch->stop('foo');

Informacije vmesnih časov so shranjene kot "obdobja" v dogodku. Da dobite informacije vmesnih časov
kličite::

    $event->getPeriods();

Kot dodatek obdobjem, lahko dobite ostale uporabne informacije iz objekta dogodka.
Na primer::

    $event->getCategory();   // Returns the category the event was started in
    $event->getOrigin();     // Returns the event start time in milliseconds
    $event->ensureStopped(); // Stops all periods not already stopped
    $event->getStartTime();  // Returns the start time of the very first period
    $event->getEndTime();    // Returns the end time of the very last period
    $event->getDuration();   // Returns the event duration, including all periods
    $event->getMemory();     // Returns the max memory usage of all periods

Sekcije
-------

Sekcije so način za logično razdelitev časovnice v skupine. Lahko pogledate,
kako Symfony uporablja sekcije za lepo vizualizacijo življenskega cikla ogrodja v
orodju Symfony Profiler. Tu je primer osnovne uporabe z uporabo sekcij::

    $stopwatch = new Stopwatch();

    $stopwatch->openSection();
    $stopwatch->start('parsing_config_file', 'filesystem_operations');
    $stopwatch->stopSection('routing');

    $events = $stopwatch->getSectionEvents('routing');

Zaprto sekcijo lahko ponovno odprete s klicom metode
:method:`Symfony\\Component\\Stopwatch\\Stopwatch::openSection`
in določite id sekcije, ki se naj ponovno odpre::

    $stopwatch->openSection('routing');
    $stopwatch->start('building_config_tree');
    $stopwatch->stopSection('routing');

.. _Packagist: https://packagist.org/packages/symfony/stopwatch
