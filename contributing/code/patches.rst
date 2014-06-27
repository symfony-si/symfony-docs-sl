Pošiljanje popravka
===================

Popravki so najboljši način, da zagotovite popravek hrošča ali predlagate
izboljšavo za Symfony2.

Korak 1: Nastavite vaše okolje
------------------------------

Namestite sklad programske opreme
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pred delo na Symfony2 nastavite prijazno okolje s sledečo programsko
opremo:

* Git;
* PHP verzija 5.3.3 ali več;
* PHPUnit 3.6.4 ali več.

Nastavite Git
~~~~~~~~~~~~~

Nastavite vaše uporabniške informacije z vašim pravim imenom in delujočim e-poštnim naslovom:

.. code-block:: bash

    $ git config --global user.name "Your Name"
    $ git config --global user.email you@example.com

.. tip::

    Če ste novi z Git-omt, je zelo priporočljivo, da preberete odlično in
    brezplačno `ProGit`_ knjigo.

.. tip::

    Če vaš IDE naredi nastavitvene datoteke znotraj direktorija projekta
    lahko uporabite globalno ``.gitignore`` datoteko (za vse projekte) ali
    ``.git/info/exclude`` datoteko (za projekt), da jih ignorirate. Poglejte
    `Github dokumentacijo`_.

.. tip::

    Windows uporabniki: ko nameščate Git, vas bo namestitveni program vprašal, kaj
    narediti z zaključki vrstic in predlagal zamenjavo vseh LF s CRLF. To je napačna
    nastavitev, če želite prispevati Symfony-ju! Izbira "as-is" metode je vaša
    najboljša izbira, saj bo Git pretvoril vaše vrstice v tiste iz repozitorija.
    Če ste že namestili Git, lahko preverite vrednost te nastavitve z vpisom:

    .. code-block:: bash

        $ git config core.autocrlf

    To bo vrnilo ali "false", "input" ali "true"; "true" in "false" sta
    napačni vrednosti. Spremenite jo v "input" z vnosom:

    .. code-block:: bash

        $ git config --global core.autocrlf input

    Zamenjajte --global z --local, če želite to nastaviti samo za aktivni
    repozitorij

Dobite Symfony izvorno kodo
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Dobite Symfony2 izvorno kodo:

* Izdelajte  `GitHub`_ račun in se vpišite;

* Kopirajte (fork) `Symfony2 repozitorij`_ (kliknite na "Fork" gumb);

* Ko je "forking action" končana, klonirajte vaš fork lokalno
  (to bo naredilo ``symfony`` direktorij):

.. code-block:: bash

      $ git clone git@github.com:USERNAME/symfony.git

* In vrhnji (upstream) repozitorij kot oddaljenega (remote):

.. code-block:: bash

      $ cd symfony
      $ git remote add upstream git://github.com/symfony/symfony.git

Preverite, da trenutni testi gredo skozi
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko je Symfony2 nameščen, preverite da vsi testi enot gredo skozi za vaše
okolje, kot je razloženo v posvečenem :doc:`dokumentu <tests>`.

Korak 2: Delo na vašem popravki
-------------------------------

Licenca
~~~~~~~

Preden pričnete morate vedeti, da vsi popravki, ki jih nameravate poslati,
morajo biti izdani pod *licenco MIT*, razen če eksplicitno specificirate v
vaših izročitvah (commits).

Izberite pravo vejo
~~~~~~~~~~~~~~~~~~~

Preden delate na popravku, morate določiti na kateri veji potrebujete
delati. Veja bi morala biti osnovana na ``master`` veji, če želite dodati
novo lastnost. Vendar če želite popraviti hrošč, uporabite najstarejšo vendar
še vedno vzdrževano verzijo Symfony-ja, kjer se hrošč zgodi (kot je ``2.3``).

.. note::

    Vsi popravki hroščev združeni v vzdrževane veje morajo biti združeni tudi
    v bolj zadnje veje na redni osnovi. Na primer, če pošljete popravek za
    ``2.3`` vejo, bo popravek uporabljen tudi s strani jedra ekipe na `master`
    veji.

Izdelajte tematsko vejo
~~~~~~~~~~~~~~~~~~~~~~~

Vsakič, ko želite delati na popravku za hrošč ali izboljšavo, izdelajte tematsko
vejo:

.. code-block:: bash

    $ git checkout -b BRANCH_NAME master

Ali, če želite zagotoviti popravek hrošča za ``2.3`` vejo, najprej spremljajte oddaljeno (remote)
``2.3`` vejo lokalno:

.. code-block:: bash

    $ git checkout -t origin/2.3

To naredi novo vejo iz ``2.3`` veje, ki dela na popravku hrošča:

.. code-block:: bash

    $ git checkout -b BRANCH_NAME 2.3

.. tip::

    Uporabite opisno ime za vašo vejo (``ticket_XXX``, kjer je ``XXX``
    številka teme hrošča, je dobra konvencija za popravljanje hroščev).

Zgornji "checkout" ukaz avtomatsko preklopi kodo na novo izdelano
vejo (preverite vejo na kateri delate z ukazom ``git branch``).

Delo na vašem popravku
~~~~~~~~~~~~~~~~~~~~~~

Delajte na kodi, kolikor želite in pošljite kolikor hočete; vendar upoštevajte
sledeče:

* Preberite o Symfony :doc:`konvencijah <conventions>` in sledite
  kodnim :doc:`standardom <standards>` (uporabite ``git diff --check`` za preverjanje
  presledkov na koncu -- tudi preberite nasvet spodaj);

* Dodajte teste enot, da dokažete, da je hrošč odpravljen ali da nova lastnost
  dejansko deluje;

* Potrudite se, da ne pokvarite združljivosti za nazaj (če to morate storiti,
  poskusite ponuditi plast združljivosti za podporo na stari način) -- popravki,
  ki zlomijo združljivost za nazaj imajo manj možnosti, da bodo združeni;

* Naredite atomsko in logično ločene izročitve (uporabite moč ``git rebase``, da
  imamo čisto in logično zgodovino);

* Stisnite nerelevantne izročitve, ki so samo o popravku kodnih standardov ali
  popravljajo manjše napake v vaši kodi;

* Nikoli ne popravljajte kodnih standardov v obstoječi kodi, saj naredi pregled kode
  bolj otežen;

* Napišite dobra sporočila izročitev (poglejte nasvet spodaj)

.. tip::

    Ko oddajate zahtevek potega, `fabbot`_ preveri vašo kodo
    za pogostimi tipkarskimi napakami in preveri, da uporabljate PHP kodne standarde
    kot so definirani v `PSR-1`_ in `PSR-2`_.

    Status je izpisan pod opisom zahtevka potega s povzetkom
    kakršnihkoli problemov, ki jih zazna ali katerihkoli napak pri gradnji Travis CI.

.. tip::

    Dobro sporočilo izročitve je sestavljeno iz povzetka (prva vrstica),
    opcijsko ji sledi prazna vrstica in bolj detajlni opis. Povzetek
    bi se moral začeti s komponento na kateri delate v zavitih oklepajih
    (``[DependencyInjection]``, ``[FrameworkBundle]``, ...). Uporabite glagol
    (``fixed ...``, ``added ...``, ...) da začnete povzetek in ne dodajajte pike
    na konec.

Pripravite vaš popravek na predložitev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko vaš popravek ni o popravku hrošča (ko dodajate novo lastnost ali spreminjate
obstoječo naprimer), mora tudi vsebovati sledeče:

* Razlago spremembe v relevantni ``CHANGELOG`` datoteki
  (``[BC BREAK]`` ali ``[DEPRECATION]`` predpona mora biti uporabljena, ko je to relevantno);

* Razlaga, kako nadgraditi obstoječo aplikacijo v relevantni
  ``UPGRADE`` datoteki, če spremembe zlomijo združljivost za nazaj ali če
  opustite nekaj, kar bo na koncu zlomilo zdužljivost za nazaj.

Korak 3: Pošljite vaš popravek
------------------------------

Kadarkoli mislite, da je vaš popravek pripravljen na pošiljanje, sledite sledečim
korakom.

Ponovno bazirajte (rebase) vaš popravek
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Pred pošiljanjem vašega popravka, posodobite vašo vejo (potrebno, če vam vzame
nekaj časa preden končate vaše spremembe):

.. code-block:: bash

    $ git checkout master
    $ git fetch upstream
    $ git merge upstream/master
    $ git checkout BRANCH_NAME
    $ git rebase master

.. tip::

    Zamenjajte ``master`` z vejo, ki ste jo prej izbrali (npr. ``2.3``),
    če delate na popravku hrošča

Ko izvajate ukaz ``rebase``, imate lahko združljivostne konflikte.
``git status`` vam bo pokazal *nezdružene* datoteke. Rešite vse konflikte,
potem nadaljujte s ponovnim baziranjem:

.. code-block:: bash

    $ git add ... # add resolved files
    $ git rebase --continue

Preverite, da vsi testi še vedno gredo skozi in oddaljeno porinite vašo vejo:

.. code-block:: bash

    $ git push --force origin BRANCH_NAME

Naredite "Pull Request"
~~~~~~~~~~~~~~~~~~~~~~~

Sedaj lahko naredite "pull request" na ``symfony/symfony`` Github repozitoriju.

.. tip::

    Poskrbite, da kaže vaš zahtevek proti ``symfony:2.3`` če želite, da
    bo jedro ekipe povleklo popravek hrošla baziran na ``2.3`` veji.

Za poenostavitev dela jedra ekipe, vedno vključite modificirane komponente v
vaših sporočilih poslanih zahtevkov, kot je v:

.. code-block:: text

    [Yaml] fixed something
    [Form] [Validator] [FrameworkBundle] added something

Opis poslanega zahtevka mora vsebovati sledeči kontrolni seznam na vrhu,
za zagotovitev, da so bili prispevki pregledani brez potrebnih zank povratnih
informacij in da so vaši prispevki lahko vključeni v Symfony2 kakor hitro je
mogoče:

.. code-block:: text

    | Q             | A
    | ------------- | ---
    | Bug fix?      | [yes|no]
    | New feature?  | [yes|no]
    | BC breaks?    | [yes|no]
    | Deprecations? | [yes|no]
    | Tests pass?   | [yes|no]
    | Fixed tickets | [comma separated list of tickets fixed by the PR]
    | License       | MIT
    | Doc PR        | [The reference to the documentation PR if any]

Primer poslanega zahtevka lahko sedaj zgledate sledeče:

.. code-block:: text

    | Q             | A
    | ------------- | ---
    | Bug fix?      | no
    | New feature?  | no
    | BC breaks?    | no
    | Deprecations? | no
    | Tests pass?   | yes
    | Fixed tickets | #12, #43
    | License       | MIT
    | Doc PR        | symfony/symfony-docs#123

Celotna tabela mora biti vključena (**ne** odstranjujte vrstic za katere menite,
da so nepotrebne). Za enostavne napake, manjše spremembe v PHPDocs ali spremembe
v datotekah prevodov, uporabite krajšo verzijo kontrolnega seznama:

.. code-block:: text

    | Q             | A
    | ------------- | ---
    | Fixed tickets | [comma separated list of tickets fixed by the PR]
    | License       | MIT

Nekateri odgovori na vprašanja sprožijo več zahtev:

* Če odgovorite z "yes" na "Bug fix?", preverite, če je bil hrošč že naveden
  v Symfony težavah in se sklicujte nanj v "Fixed tickets";

* Če odgovorite z "yes" na "New feature?", morate poslati zahtevek "pull request"
  dokumentaciji in se v njem sklicevati pod "Doc PR" sekcijo;

* Če odgovorite z "yes" na "BC breaks?", mora popravek vsebovati posodobitve
  na ustrezne ``CHANGELOG`` in ``UPGRADE`` datoteke;

* Če odgovorite z "yes" na "Deprecations?", mora popravek vsebovati posodobitve
  na ustrezne ``CHANGELOG`` in ``UPGRADE`` datoteke;

* Če odgovorite z "no" na "Tests pass", morate dodati element na kontrolni seznam
  z akcijami, ki morajo biti opravljene, da se teste popravi;

* Če "license" ni MIT, raje ne pošiljajte zahtevka, saj najverjetneje ne bo
  sprejet.

Če katere prejšnjih zahtev niso zadoščene, naredite todo-list in dodajte relevantne
elemente;

.. code-block:: text

    - [ ] fix the tests as they have not been updated yet
    - [ ] submit changes to the documentation
    - [ ] document the BC breaks

Če koda ni še končana, ali ker nimate časa jo končati ali ker
želite zgodnje povratne informacije na vašem delu, dodajte element na todo-seznamu:

.. code-block:: text

    - [ ] finish the code
    - [ ] gather feedback for my changes

Dokler imate elemente na todo seznamu, prosimo naredite predpono za "pull request"
naslov z "[WIP]".

V opisu "pull request-a" podajte čimveč podrobnosti kolikor je mogoče o vaših
spremembah (ne odlašajte s podajanjem primerov kode, ki ponazarja, da imate prav).
Če je vaš "pull request" o dodajanju nove lastnosti ali spreminjanju obstoječe,
razložite racionalnost za spreminjanje. Pull request opis pomaga pregledu
kode in služi kot referenca, ko je koda zgružena (pull request opis in vsi njegove
povezani komentarji so del združitve "commit" sporočila).

Kot dodatek temu "code" pull request-u, morate tudi poslati zahtevek k
`repozitoriju dokumentacije`_ za posodobitev dokumentacije, ko je to primerno.

Ponovno obdelajte vaš popravek
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Na osnovi povratnih informacij na vašem zahtevku (pull request), boste morali
lahko ponovno obdelati vaš popravek. Pred ponovnim pošiljanjem popravka, ponovno
bazirajte (rebase) z ``upstream/master`` ali
``upstream/2.1``, ne združujte (merge); in vsilite "push" izvoru ("origin"):

.. code-block:: bash

    $ git rebase -f upstream/master
    $ git push --force origin BRANCH_NAME

.. note::

    ko izvajate ``push --force``, vedno označite ime veje eksplicitno,
    da se izognete težavam z drugimi vejami v repozitoriju (``--force`` pove
    Git-u, da res želite se vmešati z drugimi stvarmi, torej delajte previdno).

Pogosto, vas bodo moderatorji vprašali, da stisnete ("squash") vaše izročitve. To
pomeni, da boste pretvorili mnoge izročitve v eno. Da to naredite, uporabite ukaz rebase:

.. code-block:: bash

    $ git rebase -i upstream/master
    $ git push --force origin BRANCH_NAME

Ko vtipkate ta ukaz, se bo prikazal urejevalnik in prikazal seznam poslanih potrditev:

.. code-block:: text

    pick 1a31be6 first commit
    pick 7fc64b4 second commit
    pick 7d33018 third commit

Da stisnete vse izročitve v prvega, odstranite besedi ``pick`` pred drugim in
zadnjim commit-om in ju zamenjajte z besedo ``squash`` ali samo
``s``. Ko boste shranili, bo Git pričel s ponovnim baziranjem (rebasing) in če bo uspešno,
vas bo vprašal za urejanje sporočila izročitve, kar je privzeto seznam vseh dosedanjih
sporočil izročitev. Ko ste zaključili, izvedite ukaz push.

.. _ProGit:                                http://git-scm.com/book
.. _GitHub:                                https://github.com/signup/free
.. _`Github dokumentacijo`:                https://help.github.com/articles/ignoring-files
.. _Symfony2 repozitorij:                  https://github.com/symfony/symfony
.. _dev mailing-list:                      http://groups.google.com/group/symfony-devs
.. _travis-ci.org:                         https://travis-ci.org/
.. _`travis-ci.org status icon`:           http://about.travis-ci.org/docs/user/status-images/
.. _`travis-ci.org Getting Started Guide`: http://about.travis-ci.org/docs/user/getting-started/
.. _`repozitoriju dokumentacije`:          https://github.com/symfony/symfony-docs
.. _`fabbot`:                              http://fabbot.io
.. _`PSR-1`:                               http://www.php-fig.org/psr/psr-1/
.. _`PSR-2`:                               http://www.php-fig.org/psr/psr-2/
