Prispevanje k dokumentaciji
===========================

Dokumentacija je tako pomembna kot koda. Sledi točno enakim principom:
DRY, testi, enostavnost vzdrževanja, razširljivost, optimizacija in t.i. refactoring,
da jih naštejemo samo nekaj. In seveda dokumentacija ima hrošče, tipkarske napake, branju težke
vodiče in več.

Prispevanje
-----------

Preden prispevate, se morate seznaniti z :doc:`označevalnim
jezikom <format>` uporabljenim v dokumentaciji.

Symfony2 dokumentacija je gostovana na GitHub-u:

.. code-block:: text

    https://github.com/symfony/symfony-docs

Če želite poslati popravek, `kopirajte`_ uradni repozitorij na GitHub-u in
nato klonirajte svoj fork:

.. code-block:: bash

    $ git clone git://github.com/YOURUSERNAME/symfony-docs.git

Konsistentno s Symfony izvozno kodo je repozitorij dokumentacije razdeljen v
več vej, ki ustrezajo različnim verzijam samega Symfony-ja.
Veja ``master`` vsebuje dokumentacijo za razvojno vejo kode.

Razen če dokumentirate lastnost, ki je bila predstavljena *po* Symfony 2.3
(npr. v Symfony 2.4), bi vaše spremembe morale biti osnovane na veji 2.3.
Da to naredite, povlecite (checkout) vejo 2.3 pred naslednjim korakom:

.. code-block:: bash

    $ git checkout 2.3

.. tip::

    Vaša osnovna veja (npr. 2.3) bo postala t.i. "Applies to" v :ref:`doc-contributing-pr-format`,
    ki ga boste uporabili kasneje.

Naslednje izdelajte namensko vejo za vaše spremembe (za organizacijo):

.. code-block:: bash

    $ git checkout -b improving_foo_and_bar

Sedaj lahko naredite spremembe direktno na tej veji in jih pošljete (commit). Ko
ste končali, porinite (push) to vejo v *vaš* GitHub fork in inicializirajte zahtevek potega (pull request).

Izdelava zahtevka potega
~~~~~~~~~~~~~~~~~~~~~~~~

Če sledite primeru, bo zahtevek potega privzeto med vašo
``improving_foo_and_bar`` vejo in ``symfony-docs`` ``master`` vejo.

Če ste naredili spremembe osnovane na veji 2.3, potem morate spremeniti,
da je osnovna veja 2.3 na strani predogleda s klikom na ``edit`` gumb
zgoraj levo:

.. image:: /images/docs-pull-request-change-base.png
   :align: center

.. note::

  Vse spremembe narejene na veji (npr. 2.3) bodo združene v vsako "novo"
  vejo (npr. 2.4, master, itd.) za naslednjo izdajo na tedenski osnovi.

GitHub pokriva teme o t.i. `pull requests`_ v podrobnosti.

.. note::

    Symfony2 dokumentacija je licencirana pod Creative Commons
    Attribution-Share Alike 3.0 Unported :doc:`licenco <license>`.

Lahko tudi dodate predpono naslovu vašega zahtevka potega v nekaterih primerih:

* ``[WIP]`` (Work in Progress) je uporabljen, ko še niste končali z vašim
  zahtevkom potega, vendar bi ga radi dali v pregled. Zahtevek potega ne
  bo združen dokler ne rečete, da ste pripravljeni.

* ``[WCM]`` (Waiting Code Merge) je uporabljen, ko dokumentirate novo lastnost
  ali spremembo, ki še ni bila sprejeta v jedro kode. Zahtevek potega
  ne bo združen, dokler ni združeno v jedro kode (ali zaprto, če je sprememba
  zavrnjena).

.. _doc-contributing-pr-format:

Oblika zahtevka potega
~~~~~~~~~~~~~~~~~~~~~~

Razen če popravljate kakšne manjše tipkarske napake, **mora** opis zahtevka potega
vključevati sledeči seznam, da se zagotovi, da bodo prispevki lahko pregledani
brez potrebnih zank povratnih informacij in da so lahko vaši prispeki vključeni
v dokumentacijo kakor hitro je mogoče:

.. code-block:: text

    | Q             | A
    | ------------- | ---
    | Doc fix?      | [yes|no]
    | New docs?     | [yes|no] (PR # on symfony/symfony if applicable)
    | Applies to    | [Symfony version numbers this applies to]
    | Fixed tickets | [comma separated list of tickets fixed by the PR]

Primer predložitve sedaj lahko izgleda sledeče:

.. code-block:: text

    | Q             | A
    | ------------- | ---
    | Doc fix?      | yes
    | New docs?     | yes (symfony/symfony#2500)
    | Applies to    | all (or 2.3+)
    | Fixed tickets | #1075

.. tip::

    Prosimo, bodite potrpežljivi. Lahko vzame 15 minut do nekaj dni, da se vaše spremembe
    pokažejo na symfony.com spletni strani, ko ekipa za dokumentacijo združi vaš
    zahtevek potega. Lahko preverite, če vaše spremembe predstavljajo kakšne označevalne težave
    s pregledom strani `Documentation Build Errors`_ (posodobljena je vsako noč ob 3AM po
    franskoskem času, ko strežnik ponovno zgradi dokumentacijo).

Dokumentiranje novih lastnosti ali sprememb obnašanja
-----------------------------------------------------

Če dokumentirate povsem novo lastnost ali spremembo, ki je bila narejena v
Symfony2, morate dodati pred vaš opis spremembe ``.. versionadded:: 2.X``
značko in kratek opis:

.. code-block:: text

    .. versionadded:: 2.3
        The ``askHiddenResponse`` method was introduced in Symfony 2.3.

    You can also ask a question and hide the response. This is particularly...

Če dokumentirate spremembo obnašanja, je lahko v pomoč *kratek* opis,
kako se je obnašanje spremenilo.

.. code-block:: text

    .. versionadded:: 2.3
        The ``include()`` function is a new Twig feature that's available in
        Symfony 2.3. Prior, the ``{% include %}`` tag was used.

Kadarkoli je nova manjša verzija Symfony2 izdaja (npr. 2.4, 2.5 itd.),
je narejena nova veja dokumentacije iz ``master`` veje.
Na tej točki vse značke ``versionadded`` za Symfony2 verzije, ki jih imajo
danes in 2.2 je pred kratkim dosegla konec razvojnega cikla, 2.2 ``versionadded``
značke bodo odstranjene iz nove 2.5 veje.

Standardi
---------

Vsa dokumentacija v Symfony dokumentaciji bi morala slediti
:doc:`standardom dokumentacije <standards>`.

Poročanje težave
----------------

Najenostavnejše prispevanje, ki ga lahko naredite je poročanje o težavi: tipkarska napaka, slovnična
napaka, hrošč v primeru kode, manjkajoča razlaga itd.

Koraki:

* Pošljite hrošč v sledilniku hroščev;

* *(opcijsko)* Pošljite popravek.

Prevajanje
----------

Preberite namenski :doc:`dokument <translations>`.

Upravljanje izdaj
-----------------

Symfony ima zelo standardiziran proces izdaj, o katerem lahko več preberete
v :doc:`/contributing/community/releases` sekciji.

Da se sledi procesu izdaj, naredi ekipa dokumentacije nekaj
sprememb na dokumentaciji na različnih delih življenskega cikla.

Ko izdaja doseže "konec vzdrževanja"
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vsaka izdaja sčasoma doseže svoj "konec vzdrževanja". Za podrobnosti,
glejte :ref:`contributing-release-maintenance`.

Ko izdaja doseže svoj konec vzdrževanja, so narejeni sledeči elementi.
Za ta primer, predpostavimo, da je verzija 2.1 ravnokar dosegla svoj konec vzdrževanja:

* Spremembe in zahtevki potegov niso več združeni v vejo (2.1),
  razen za varnostne posodobitve, ki so združene dokler izdaja ne doseže
  svojega "konca življenske dobe".

* Vse veje, ki so še vedno po vzdrževanjem (npr. 2.2 in več) so posodobljene,
  da odražajo, da bi se zahtevki potegov morali začeti iz sedaj-nove vzdrževane
  verzije (npr. 2.2) - vključno s podrobnostmi v datoteki README.

* Odstranijo se vse ``versionadded`` direktive - in ostali zapiski povezani z lastnostmi
  sprememb ali če so novi - za verzijo (npr. 2.1) iz master veje.
  Rezultat je, da naslednja izdaja (ki je prva, ki prihaja v celoti
  *po* koncu vzdrževanja te veje), ne bo vsebovala omemb o
  stari verziji (npr. 2.1).

Ko je ustvarjena nova veja za izdajo
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Med :ref:`fazo stabilizacije <contributing-release-development>`
je ustvarjena nova veja na dokumentaciji. Na primer, če je bila verzija 2.3
stabilizirana, potem bi bila ustvarjena nova 2.3 veja izdelana zanjo. Ko se to
zgodi, so narejeni sledeči elementi:

* Sprememba vseh verzij in master referenc na pravilne verzijo (npr. 2.3).
  Na primer v namestitvenih poglavjih, se sklicujemo na verzijo, ki bi jo
  morali uporabiti za namestitev. Kot primer, glejte spremembe narejene v `PR #2688`_.

.. _`kopirajte`:                  https://help.github.com/articles/fork-a-repo
.. _`pull requests`:              https://help.github.com/articles/using-pull-requests
.. _`Documentation Build Errors`: http://symfony.com/doc/build_errors
.. _`PR #2688`:                   https://github.com/symfony/symfony-docs/pull/2688
