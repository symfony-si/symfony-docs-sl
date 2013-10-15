.. index::
   single: Forms; Fields; money

money tip polja
===============

Izpiše vnostno tekstovno polje in specializira ravnanje vnešenih denarnih ("money")
podatkov.

To polje vam omogoča, da določite valuto, katere simbol je izpisan poleg
tekstovnega polja. Na voljo je tudi nekaj ostalih opcij za prilagajanje,
kako se ravna z vhodom in izhodom podatkov.

+----------------+---------------------------------------------------------------------+
| Izpisan kot    | ``input`` ``text`` polje                                            |
+----------------+---------------------------------------------------------------------+
| Opcije         | - `currency`_                                                       |
|                | - `divisor`_                                                        |
|                | - `precision`_                                                      |
|                | - `grouping`_                                                       |
+----------------+---------------------------------------------------------------------+
| Podedovane     | - `required`_                                                       |
| opcije         | - `label`_                                                          |
|                | - `read_only`_                                                      |
|                | - `disabled`_                                                       |
|                | - `error_bubbling`_                                                 |
|                | - `error_mapping`_                                                  |
|                | - `invalid_message`_                                                |
|                | - `invalid_message_parameters`_                                     |
|                | - `mapped`_                                                         |
+----------------+---------------------------------------------------------------------+
| Starševski tip | :doc:`form </reference/forms/types/form>`                           |
+----------------+---------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\MoneyType` |
+----------------+---------------------------------------------------------------------+

Opcije polja
------------

currency
~~~~~~~~

**tip**: ``string`` **privzeto**: ``EUR``

Določa valuto v kateri je denar določen. To določa
simbol valute, ki bi moral biti prikazan s tekstovnim kvadratkom. Odvisno od
valute - simbol valute je lahko prikazan pred ali za vnosnim tekstovnim poljem.
    
To je lahko katerakoli `3 črkovna ISO 4217 koda`_. To lahko tudi nastavite na
false, da skrijete simbol valute.

divisor
~~~~~~~

**tip**: ``integer`` **privzeto**: ``1``

Če zaradi kakršnega koli razloga potrebujete razdeliti vašo začetno vrednost s
številom pred izpisom uporabniku, lahko uporabite opcijo ``divisor``.
Na primer::

    $builder->add('price', 'money', array(
        'divisor' => 100,
    ));

V tem primeru, če je polje ``price`` nastavljeno na ``9900``, potem bo
vrednost ``99`` dejansko izpisana uporabniku. Ko uporabnik vnese
vrednost ``99``, bo zmnožena s ``100`` in ``9900`` bo na koncu
nastavljena v vašem objektu.

precision
~~~~~~~~~

**tip**: ``integer`` **privzeto**: ``2``

Če zaradi kakšnega razloga potrebujete nekaj preciznosti drugačna kot 2
decimalna mesta, lahko modificirate to vrednost. Verjetno vam tega ne bo treba
narediti, razen če na primer želite zaokrožiti na najbližji dolar (nastavite
precision na ``0``).

.. include:: /reference/forms/types/options/grouping.rst.inc

Podedovane opcije
-----------------

Te opcije dedujejo iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/invalid_message.rst.inc

.. include:: /reference/forms/types/options/invalid_message_parameters.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. _`3 črkovna ISO 4217 koda`: http://en.wikipedia.org/wiki/ISO_4217
