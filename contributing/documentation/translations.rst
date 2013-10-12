Prevajanje
==========

Symfony2 dokumentacija je napisana v angleščini in mnogi ljudje so vključeni
v proces prevajanja.

Prispevanje
-----------

Najprej se seznanite z :doc:`označevalnim jezikom <format>` uporabljenim
za dokumentacijo.

Nato se prijavite na `dopisni seznam Symfony dokumentacije`_, saj se vso sodelovanje
dogaja tam.

Končno najdite *master* repozitorij za jezik h kateremu želite prispevati.
Tu je seznam uradnih *master* repozitorijev:

* *English*:  https://github.com/symfony/symfony-docs
* *French*:   https://github.com/symfony-fr/symfony-docs-fr
* *Italian*:  https://github.com/garak/symfony-docs-it
* *Japanese*: https://github.com/symfony-japan/symfony-docs-ja
* *Polish*:   https://github.com/symfony-docs-pl/symfony-docs-pl
* *Portuguese (Brazilian)*:  https://github.com/andreia/symfony-docs-pt-BR
* *Spanish*:  https://github.com/gitnacho/symfony-docs-es

.. note::

    Če želite prispevati prevode za novi jezik, preberite
    :ref:`namensko sekcijo <translations-adding-a-new-language>`.

Pridružitev prevajalski
-----------------------

Če želite pomagati prevesti nekaj dokumentov za vaš jezik ali popraviti nekaj
hroščev, premislite o pridružitvi; gre za zelo enostaven proces:

* Predstavite se na `dopisnem seznamu Symfony dokumentacije`_;
* *(opcijsko)* Vprašajte na katerih dokumentih lahko delate;
* Kopirajte (fork) *master* repozitorij za vaš jezik (kliknite na "Fork" gumb na
  GitHub strani);
* Prevedite nekaj dokumentov;
* Vprašajte za "pull request" (kliknite na "Pull Request" iz vaše strani na
  GitHub-u);
* Upravitelj ekipe sprejme vaše spremembe in jih združi v master
  repozitorij;
* Spletna stran dokumentacije je posodobljena vsako noč iz master
  repozitorija.

.. _translations-adding-a-new-language:

Dodajanje novega jezika
-----------------------

Ta sekcija vam ponuja nekaj smernic za začetek prevajanja
Symfony2 dokumentacije za nov jezik.

Kot je pričetek prevajanja veliko dela, se pogovorite v vašem načrtu na
`dopisnem seznamu Symfony dokumentacije`_ in poskusite najti motivirane ljudi,
ki so vam pripravljeni pomagati.

Ko je ekipa pripravljena, določite upravitelja ekipe; on bo odgovoren za
*master* repozitorij.

Izdelajte repozitorij in kopirajte *angleške* dokumente.

Ekipa lahko sedaj prične s procesom prevajanja.

Ko je ekipa prepričana, da je repozitorij v konsistentnem in stabilnem
stanju (vse je prevedeno, ali pa so bili ne-prevedeni dokumenti odstranjeni
iz kazal -- datoteke poimenovane ``index.rst`` in ``map.rst.inc``), upravitelj
ekipe lahko zaprosi, da je repozitorij dodan na seznam uradnih *master*
repozitorijev s poslano e-pošto Fabien-u (fabien at symfony.com).

Vzdrževanje
-----------

Prevajanje se ne konča, ko je vse prevedeno. Dokumentacija je premikajoča (
dodajajo se novi dokumenti, popravljajo se hrošči, odstavki se reorganizirajo, ...).
Ekipa za prevajanje mora dobro slediti angleškem repozitoriju in dodati
spremembe prevedenim dokumentom kakor hitro je mogoče.

.. caution::

    Nevzdrževani jeziki so odstranjeni iz uradnega seznama repozitorijev
    saj je zastarela dokumentacija nevarna.

.. _dopisnem seznamu Symfony dokumentacije: http://groups.google.com/group/symfony-docs
.. _dopisni seznam Symfony dokumentacije: http://groups.google.com/group/symfony-docs
