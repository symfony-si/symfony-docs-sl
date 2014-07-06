.. index::
    single: Console Helpers; Table Helper

Tabelni pomočnik
================

.. versionadded:: 2.3
    Pomočnik ``table`` je bil predstavljen v Symfony 2.3.

.. caution::

    Table Helper je bil opuščen v Symfony 2.5 in bo odstranjen v
    Symfony 3.0. Sedaj bi morali uporabljati
    namesto tega razred :doc:`Table </components/console/helpers/table>`, ki je
    močnejši.

Ko se gradi konzolno aplikacijo, je lahko uporabno prikazati tabularne podatke:

.. image:: /images/components/console/table.png

Za prikaz tabele, uporabite :class:`Symfony\\Component\\Console\\Helper\\TableHelper`,
nastavite glave, vrstice in izpis::

    $table = $this->getHelperSet()->get('table');
    $table
        ->setHeaders(array('ISBN', 'Title', 'Author'))
        ->setRows(array(
            array('99921-58-10-7', 'Divine Comedy', 'Dante Alighieri'),
            array('9971-5-0210-0', 'A Tale of Two Cities', 'Charles Dickens'),
            array('960-425-059-0', 'The Lord of the Rings', 'J. R. R. Tolkien'),
            array('80-902734-1-6', 'And Then There Were None', 'Agatha Christie'),
        ))
    ;
    $table->render($output);

Postavitev tabele se lahko tudi prilagodi. Na voljo sta dva načina za prilagoditev
izpisa tabele: z uporabo poimenovanih postavitev ali s prilagoditvijo opcij izpisa.

Prilagoditev postavitve tabele z uporabo poimenovanih postavitev
----------------------------------------------------------------

.. versionadded:: 2.4
    Postavitev ``TableHelper::LAYOUT_COMPACT`` je bila predstavljena v Symfony 2.4.

Pomočnik tabel vsebuje tri prednastavljene postavitve tabele:

* ``TableHelper::LAYOUT_DEFAULT``

* ``TableHelper::LAYOUT_BORDERLESS``

* ``TableHelper::LAYOUT_COMPACT``

Postavitev se lahko nastavi z uporabo metode
:method:`Symfony\\Component\\Console\\Helper\\TableHelper::setLayout`.

Prilagoditev postavitve tabele z uporabo opcij izpisa
-----------------------------------------------------

Lahko tudi kontrolirate izpis tabele z nastavitvijo vrednosti opcij izpisa po meri:

*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setPaddingChar`
*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setHorizontalBorderChar`
*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setVerticalBorderChar`
*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setCrossingChar`
*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setCellHeaderFormat`
*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setCellRowFormat`
*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setBorderFormat`
*  :method:`Symfony\\Component\\Console\\Helper\\TableHelper::setPadType`
