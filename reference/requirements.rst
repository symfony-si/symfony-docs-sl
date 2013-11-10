.. index::
   single: Requirements
   
Zahteve za poganjanje Symfony2
==============================

Za poganjanje Symfony se mora vaš sistem držati seznama zahtev. Lahko
enostavno pogledate, če vaš sistem prestane vse zahteve s pogonom ``web/config.php``
v vaši Symfony distribuciji. Ker CLI pogosto uporablja različno ``php.ini``
nastavitveno datoteko, je tudi dobra ideja, da preverite vaše zahteve iz
ukazne vrstice preko:

.. code-block:: bash

    $ php app/check.php

Spodaj je seznam zahtevanih in opcijskih zahtev:

Zahtevano
---------

* PHP mora biti minimalne verzije PHP 5.3.3
* JSON mora biti omogočen
* ctype mora biti omogočen
* Vaš ``php.ini`` mora imeti date.timezone nastavitev

Opcijsko
--------

* Nameščen morate imeti modul PHP-XML
* Imeti morate vsaj verzijo 2.6.21 libxml
* PHP tokenizer mora biti omoočen
* mbstring funkcije morajo biti omogočene
* iconv mora biti omogočen
* POSIX mora biti omogočen (samo na \*nix)
* Intl mora biti nameščen z ICU 4+
* APC 3.0.17+ (ali drug opcode predpomnilnik cache mora biti nameščen)
* ``php.ini`` priporočene nastavitve

  * ``short_open_tag = Off``
  * ``magic_quotes_gpc = Off``
  * ``register_globals = Off``
  * ``session.auto_start = Off``

Doctrine
--------

Če želite uporabljati Doctrine, morate imeti nameščen PDO. Dodatno morate
imeti nameščen PDO gonilnik za strežnik podatkovne baze, ki ga želite
uporabljati.
