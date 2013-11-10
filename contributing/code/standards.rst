Kodni standardi
===============

Ko prispevate kodo za Symfony2, morate slediti njegovim kodnim standardom. Da
naredimo dolgo zgodbo kratko, tu je zlato pravilo: **posnemajte obstoječo
Symfony2 kodo**. Večina odprtokodnih paketov in knjižnici uporabljenih v Symfony2
tudi sledi enakim vodilom in morali bi tudi vi.

Pomnite, da je glavna prednost standardov to, da vsak del kode
zgleda in deluje bolj znano, ne gre za to, da je to ali ono bolj bralno.

Symfony sledi standardom definiranim v `PSR-0`_, `PSR-1`_ in `PSR-2`_
dokumentih.

Odkar je slika - ali nekaj kode - vredna tisoč besed, je tu kratek primer,
ki vsebuje največ lastnosti opisanih spodaj:

.. code-block:: html+php

    <?php

    /*
     * This file is part of the Symfony package.
     *
     * (c) Fabien Potencier <fabien@symfony.com>
     *
     * For the full copyright and license information, please view the LICENSE
     * file that was distributed with this source code.
     */

    namespace Acme;

    /**
     * Coding standards demonstration.
     */
    class FooBar
    {
        const SOME_CONST = 42;

        private $fooBar;

        /**
         * @param string $dummy Some argument description
         */
        public function __construct($dummy)
        {
            $this->fooBar = $this->transformText($dummy);
        }

        /**
         * @param string $dummy Some argument description
         * @param array  $options
         *
         * @return string|null Transformed input
         *
         * @throws \RuntimeException
         */
        private function transformText($dummy, array $options = array())
        {
            $mergedOptions = array_merge(
                array(
                    'some_default' => 'values',
                    'another_default' => 'more values',
                ),
                $options
            );

            if (true === $dummy) {
                return;
            }
            if ('string' === $dummy) {
                if ('values' === $mergedOptions['some_default']) {
                    return substr($dummy, 0, 5);
                }
                
                return ucwords($dummy);
            }
            throw new \RuntimeException(sprintf('Unrecognized dummy option "%s"', $dummy));
        }
    }

Struktura
---------

* Dodajte en presledek za vsakim ločilom vejice;

* Dodajte en presledek okrog operatorjev (``==``, ``&&``, ...);

* Dodajte vejico za vsakim elementom polja v večvrstičnem polju, tudi za
  zadnjim;

* Dodajte prazno vrstico pred ``return`` stavkom, razen če je return stavek sam
  znotraj skupine izrazov (kot v ``if`` stavku);

* Uporabite oklepaje, da označite telo kontrolne strukture ne glede na število
  stavkov, ki jih vključuje;

* Definirajte en razred na datoteko - to ne velja za privatne pomožne razrede (helper classes),
  ki niso namenjeni za instantizacijo iz zunaj in zato ni potrebne skrbi za
  `PSR-0`_ standard;

* Razglasite lastnosti razreda pred metodami;

* Razglasite najprej javne metode (public), nato zaščitene (protected) in na koncu zasebne (private);

* Uporabite oklepaje, ko instantizirate razrede ne glede na število
  argumentov, ki jih ima constructor;

* Nizi sporočil izjeme (Exception) bi morali biti sestavljeni z uporabo :phpfunction:`sprintf`.

Konvencije imen
---------------

* Uporabite camelCase, ne podčrtajev za imena spremenljivk, funkcij, metode in argumentov
  names, arguments;

* Uporabite podčrtaje za imena opcij in imena parametrov;

* Uporabite imenske prostore za vse razrede;

* Abstraktnim razredom dodajte predpono ``Abstract``. Prosimo pomnite, da nekaj zgodnjih Symfony2 razredov
  ne sledi tem konvencijam in niso bili poimenovani zaradi razlogov združljivosti za nazaj.
  Čeprav vsi novi abstraktni razredi morajo slediti tej konvenciji imen;

* Vmesnikom (interfaces) dodajte na koncu pripono ``Interface``;

* Za traits dodajte ``Trait``;

* Za izjeme dodajte ``Exception``;

* Uporabljajte alfanumerične znake in poudarke za imena datotek;

* Ne pozabite pogledati bolj izraznega dokumenta :doc:`conventions` za
  bolj subjektivne premisleke poimenovanja.

Konvencije poimenovanja storitev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

* Ime storitve vsebuje skupine, ločene s pikami;
* Alias DI paketa je prva skupina (npr. ``fos_user``);
* Uporabite manjhne črke za storitve in imena parametrov;
* Ime skupine uporablja notacije podčrtajev;
* Vsaka storitev ima ustrezni parameter, ki vsebuje ime razreda in
  sledi konvenciji ``SERVICE NAME.class``.

Dokumentacija
-------------

* Dodajte PHPDoc bloke za vse razrede, metode in funkcije;

* Izognite se ``@return`` atributu, če metoda nič ne vrne;

* Anotaciji ``@package`` in ``@subpackage`` nista uporabljeni.

Licenca
-------

* Symfony je izdan pod licenco MIT in blok licence mora biti prisoten
  na vrhu vsake PHP datoteke, pred imenskim prostorom.

.. _`PSR-0`: https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-0.md
.. _`PSR-1`: https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-1-basic-coding-standard.md
.. _`PSR-2`: https://github.com/php-fig/fig-standards/blob/master/accepted/PSR-2-coding-style-guide.md
