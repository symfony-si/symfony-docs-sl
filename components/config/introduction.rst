.. index::
   single: Config
   single: Components; Config

Komponenta Config
=================

Uvod
----

Kompomenta Config ponuja nekaj razredov, ki vam pomagajo najdi, naložiti,
kombinirati, avtomatsko izpolniti in preveriti nastavitvene vrednosti katerekoli vrste, kakršenkoli je
njihov vir (YAML, XML, INI datoteke, ali na primer podatkovna baza).

.. caution::

    ``IniFileLoader`` razčlenjuje vsebino datoteke z uporabo
    funkcije :phpfunction:`parse_ini_file` zato, lahko nastavite samo
    parametre na vrednosti nizov. Da nastavite parametre za ostale tipe podatkov
    (npr. logična vrednost, celo število itd.), so priporočljivi ostali nalagalniki.

Namestitev
----------

Komponento lahko namestite na 2 načina:

* :doc:`Namestitev preko Composer-ja </components/using_components>` (``symfony/config`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Config).

Sekcije
-------

* :doc:`/components/config/resources`
* :doc:`/components/config/caching`
* :doc:`/components/config/definition`

.. _Packagist: https://packagist.org/packages/symfony/config
