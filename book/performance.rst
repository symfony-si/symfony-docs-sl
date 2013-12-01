.. index::
   single: Tests

Uspešnost
=========

Symfony2 je hiter že takoj, ko ga odprete. Seveda, če res potrebujete hitrost,
je na voljo mnogo načinov, da lahko naredite Symfony še hitrejšega. V tem poglavju,
boste raziskali mnoge teh najpogostejših in močnih načinov, da naredite vašo Symfony
aplikacijo še hitrejšo.

.. index::
   single: Performance; Byte code cache

Uporabite Byte Code predpomnilnik (npr. APC)
--------------------------------------------

Eden najboljših (in enostavnejših) stvari, ki bi jih morali narediti za izboljšanje vaše učinkovitosti,
je, da uporabite t.i. "byte code predpomnilnik". Ideja byte code predpomnilnika je odstraniti
potrebo po nenehnem ponovnem prevajanju PHP izvorne kode. Na voljo je mnogo
`byte code predpomnilnikov`_, nekateri izmed njih so odprto kodni. Najbolj pogosto
uporabljani byte code predpomnilnik je verjetno `APC`_

Uporaba byte code predpomnilnika resnično nima slabosti in Symfoyn2 je bil načrtovan,
za res dobro opravljanje v tem tipu okolja.

Nadaljnje optimizacije
~~~~~~~~~~~~~~~~~~~~~~

Byte code predpomnilniki običajno spremljajo izvorne datoteke za spremembami. To zagotavlja,
da če se izvorna datoteka spremeni, je bajtna koda ponovno prevedena avtomatsko.
To je res priročno, vendar očitno doda stroške.

Zaradi tega razloga nekateri byte code predpomnilniki ponujajo opcijo onemogočiti ta preverjanja.
Očitno ko se onemogoča ta preverjanja, bo odvisno od administratorja strežnika,
da zagotovi, da je predpomnilnik spraznjen kadarkoli se katerakoli izvorna datoteka spremeni. Drugače
posodobitve, ki jih naredite, ne bodo vidne.

Na primer onemogočiti ta preverjanja v APC-ju, enostavno dodajte ``apc.stat=0`` k
vašim nastavitvam ``php.ini``.

.. index::
   single: Performance; Autoloader

Uporabite Composer-jevo Class Map funkcionalnost
------------------------------------------------

Privzeto Symfony2 standardna izdaja uporablja Composerjev avtomatski nalagalnik
v datoteki `autoload.php`_. Ta avtomatski nalagalnik je enostaven za uporabo, saj bo
avtomatsko našel katere koli nove razrede, ki ste jih dali v registrirane
direktorije.

Na žalost ima to svojo ceno, saj nalagalnik izvaja iteracije skozi vse nastavljene
imenske prostore, da najde določeno datoteko in naredi ``file_exists`` klice dokler
končno ne najde datoteke, ki jo išče.

Najenostavnejša rešitev je povedati Composer-ju, da zgradi "class map" (t.j.
veliko polje lokacij vseh razredov). To se lahko naredi iz
ukazne vrstice in lahko postane del vašega postavitvenega procesa:

.. code-block:: bash

    php composer.phar dump-autoload --optimize

Notranje to zgradi veliko polje zemljevida razredov v ``vendor/composer/autoload_classmap.php``.

Predpomnenje avtomatskega nalagalnika z APC
-------------------------------------------

Druga rešitev je predpomnenje lokacije vsakega razreda potem, ko je prvič
lociran. Symfony prihaja z razredom - :class:`Symfony\\Component\\ClassLoader\\ApcClassLoader` -
ki naredi točno to. Da ga uporabite, samo prilagodite vašo datoteko prednjega krmilnika.
Če uporabljate standardno distribucijo, bi ta koda že morala biti na voljo
kot komentarji v tej datoteki::

    // app.php
    // ...

    $loader = require_once __DIR__.'/../app/bootstrap.php.cache';

    // Use APC for autoloading to improve performance
    // Change 'sf2' by the prefix you want in order
    // to prevent key conflict with another application
    /*
    $loader = new ApcClassLoader('sf2', $loader);
    $loader->register(true);
    */

    // ...

Za več podrobnosti, glejte :doc:`/components/class_loader/cache_class_loader`.

.. note::

    Ko uporabljate APC avtomatski nalagalnik in če dodate nove razrede, bodo najdeni
    avtomatsko in vse bo delovalo kot prej (t.j. nobenega
    razloga za "praznenje" predpomnilnika). Vendar če spremenite lokacijo
    določenega imenskega prostora ali predpono, boste morali sprazniti vaš APC predpomnilnik. Drugače
    bo avtomatski nalagalnik še vedno iskal staro lokacijo za vse razrede
    znotraj tega imenskega prostora.

.. index::
   single: Performance; Bootstrap files

Uporabite zagonske (bootstrap) datoteke
---------------------------------------

Za zagotovitev optimalne fleksibilnosti in ponovne uporabe kode, Symfony2 aplikacije dajejo vzvod
različnim razredom in tretje osebnim komponentam. Vendar nalaganje vseh teh razredov
iz različnih datotek na vsakem zahtevku imajo lahko za posledico nekaj stroškov. Za zmanjšanje
teh stroškov Symfony2 standardna izdaja ponuja skripto za generiranje
t.i. `bootstrap datoteke`_, ki je sestavljena iz večih definicij razredov
v eni datoteki. Z vključitvijo te datoteke (ki vsebuje kopije mnogih razredov
jedra), Symfony ne potrebuje več vključevati katerihkoli od teg izvornih datotek,
ki vsebujejo te razrede. To bo precej zmanjšalo vhod in izhod na disku.

Če uporabljate Symfony2 standardno izdajo, potem verjetno že
uporabljate bootstrap datoteko. Da ste prepričani, odprite vaš prednji krmilnik (običajno
``app.php``) in preverite, da sledeča vrstica obstaja::

    require_once __DIR__.'/../app/bootstrap.php.cache';

Bodite pozorni na dve slabosti, ko uporabljate bootstrap datoteko:

* datoteka mora biti ponovno generirana kadarkoli se katerikoli originalnih izvorov spremeni
  (t.j. ko posodabljate Symfony2 izvor ali knjižnice izdelovalcev - vendor);

* ko razhroščujete, bo potrebno dati prelomne točke znotraj bootstrap datoteke.

Če uporabljate Symfony2 standardno izdajo, je bootstrap datoteka avtomatsko
ponovno zgrajena po posodobitvi vendor knjižnic preko ``php composer.phar install``
ukaza.

Bootstrap datoteke in Byte Code predpomnilniki
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Celo ko uporabljate byte code predpomnilnik, bo uspešnost izboljšana, ko uporabljate bootstrap
datoteko, saj bo manj datotek za opazovanje za spremembami. Seveda če je ta lastnost
onemogočena v byte code predpomnilniku (npr. ``apc.stat=0`` v APC), ni
več razloga, da uporabite bootstrap datoteko.

.. _`byte code predpomnilnikov`: http://en.wikipedia.org/wiki/List_of_PHP_accelerators
.. _`APC`: http://php.net/manual/en/book.apc.php
.. _`autoload.php`: https://github.com/symfony/symfony-standard/blob/master/app/autoload.php
.. _`bootstrap datoteke`: https://github.com/sensio/SensioDistributionBundle/blob/master/Composer/ScriptHandler.php
