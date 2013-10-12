Git
===

Ta dokument razlaga nekatere konvencije in specifikacije na način, s katerim
upravljamo Symfony kodo z Git-om.

Zahtevki potegov
----------------

Karadkoli je zahtevek potega (pull request) združen, vse informacije, ki so vsebovanje
v zahtevku (tudi komentarji) so shranjeni v repozitorij.

Lahko enostavno opazite združitev zahtevka potega, ko poslano sporočilo vedno sledi
temu vzorcu:

.. code-block:: text

    merged branch USER_NAME/BRANCH_NAME (PR #1111)

PR referenca vam omogoča ogled originalnega zahtevka poteka na
Github-u: https://github.com/symfony/symfony/pull/1111. Vendar vse informacije,
ki jih lahko dobite na GitHub-u so tudi na voljo iz samega repozitorija.

Združitveno sporočilo vsebuje originalno sporočilo od avtorja spremembe.
Pogosto to lahko pomaga razumeti, za kaj je šlo pri spremembah in razlog
za spremembami.

Še več, celotna diskusija, ki se je zgodila zadaj je tudi shranjena kot
Git opomba (pred 22. marcem 2013 je bila diskusija del glavnega poslanega sporočila).
Za pridobitev teh opomb, dodajte to vrstico v vašo ``.git/config`` datoteko:

.. code-block:: ini

    fetch = +refs/notes/*:refs/notes/*

Po git pridobitvi (fetch) je dobiti GitHub diskusijo za pošiljanje (commit) samo stvar
dodajanja ``--show-notes=github-comments`` pri ``git show`` ukazu:

.. code-block:: bash

    $ git show HEAD --show-notes=github-comments
