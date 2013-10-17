.. index::
   single: Debugging

Kako optimizirati vaše razvojno okolje za razhroščevanje
========================================================

Ko delate na Symfony projektu na vaši lokalni napravi, bi morali uporabiti
``dev`` okolje (``app_dev.php`` prednji krmilnik). Ta nastavitev okolja
je optimizirana za dva glavna razloga:

* Razvijalcu da točne povratne informacije, kadarkoli gre kaj narobe (spletna
  razhroščevalna vrstica, lepe strani napak, profiler, ...);

* Je kolikor je le možno podobno produkcijskemu okolju, da se izognete problemom
  ko postavljate projekt.

.. _cookbook-debugging-disable-bootstrap:

Onemogočanje datoteke za samozagon in razreda predpommnilnika
-------------------------------------------------------------

Ter da se naredi produkcijsko okolje, kakor hitro je le mogoče, Symfony izdela
velike PHP datoteke v vašem predpomnilniku, ki vsebuje agregacijo PHP razredov, ki
jih vaš projekt potrebuje na vsakem zahtevku. Čeprav to obnašanje lahko zmede vaš
IDE ali vaš razhroščevalnik. Ta recept vam prikazuje, kako lahko optimizirate ta
predpomnilni mehanizem, da ga naredite prijaznejšega, ko potrebujete razhroščevati
kodo, ki vključuje Symfony razrede.

Prednji krmilnik ``app_dev.php`` je privzeto sledečit::

    // ...

    $loader = require_once __DIR__.'/../app/bootstrap.php.cache';
    require_once __DIR__.'/../app/AppKernel.php';

    $kernel = new AppKernel('dev', true);
    $kernel->loadClassCache();
    $request = Request::createFromGlobals();

Da naredite vaš razhroščevalnik srečnejši, onemogočite vse PHP razrede predpomnilnika z odstranitvijo
klica na ``loadClassCache()`` in z zamenjavo require stavka kot je spodaj::

    // ...

    // $loader = require_once __DIR__.'/../app/bootstrap.php.cache';
    $loader = require_once __DIR__.'/../app/autoload.php';
    require_once __DIR__.'/../app/AppKernel.php';

    use Symfony\Component\HttpFoundation\Request;

    $kernel = new AppKernel('dev', true);
    // $kernel->loadClassCache();
    $request = Request::createFromGlobals();

.. tip::

    Če onemogočite PHP predpomnilnike, jih ne pozabite povrniti ko končate razhroščevalno
    sejo.

Nekateri IDE-ji ne marajo dejstva, da so nekateri razredi shranjeni na različnih lokacijah.
Da se izognete problemom, lahko ali poveste vašemu IDE-ju, da ignorirate PHP datoteke
predpomnilnika, ali pa spremenite končnico uporabljeno s strani Symfony-ja za te datoteke::

    $kernel->loadClassCache('classes', '.php.cache');
