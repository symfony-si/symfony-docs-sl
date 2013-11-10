.. index::
    single: Components; Class Loader

Komponenta Class Loader
=======================

    Komponenta Class Loader Component zagotavlja orodja za avtomatsko nalaganje vaših razredov
    in predpomni njihove lokacije za učinkovitost.

Uporaba
-------

Kadarkoli se sklicujete na razred, ki še ni bil zahtevan ali vključen,
PHP uporablja `mehanizem avtomatskega nalaganja`_, da prenese nalaganje datoteke,
ki definira razred. Symfony2 ponuja dva avtomatska nalagalnika, ki sta zmožna
naložiti vaše razrede:

* :doc:`/components/class_loader/class_loader`: naloži razrede, ki sledijo
  `PSR-0` standardom poimenovanja razredov;

* :doc:`/components/class_loader/map_class_loader`: naloži razrede z uporabo
  statičnega zemljevida iz imena razreda v pot datoteke.

Dodatno, Symfony-jeva komponenta Class Loader prihaja s skupkom ovojnih
razredov, ki so lahko uporabljeni za dodajanje dodatnih funkcionalnosti na
vrhu obstoječih avtomatskih nalagalnikov (autoloaders):

* :doc:`/components/class_loader/cache_class_loader`
* :doc:`/components/class_loader/debug_class_loader`

Namestitev
----------

Komponento lahko namestite na dva načina:

* :doc:`Namestite jo preko Composer-ja </components/using_components>` (``symfony/class-loader``
  na `Packagist`_).
* Uporabite uradni Git repozitorij (https://github.com/symfony/ClassLoader);

.. _`mehanizem avtomatskega nalaganja`: http://php.net/manual/en/language.oop5.autoload.php
.. _Packagist: https://packagist.org/packages/symfony/class-loader
