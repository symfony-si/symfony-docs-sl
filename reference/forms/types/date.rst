.. index::
   single: Forms; Fields; date

date tip polja
==============

Polje, ki omogoča uporabniku spremeniti informacije datuma preko raznovrstnosti
različnih HTML elementov.

Osnovni podatki uporabljeni za ta tip polja so lahko ``DateTime`` objekt,
niz, časovna znamka ali polje. Dokler je opcija `input`_ nastavljena
pravilno, bo polje poskrbelo za vse podrobnosti.

Polje je lahko izpisano kot en tekstovni kvadratek, trije tekstovni kvadratki
(mesec, dan in leto) ali trije izbirni kvadratki (glejte `widget`_ opcijo).

+------------------------+---------------------------------------------------------------------------------+
| Osnovni podatkovni tip | lahko je ``DateTime``, niz, časovni podpis, ali polje (glejte opcijo ``input``) |
+------------------------+---------------------------------------------------------------------------------+
| Izpisano kot           | single text box or three select fields                                          |
+------------------------+---------------------------------------------------------------------------------+
| Opcije                 | - `widget`_                                                                     |
|                        | - `input`_                                                                      |
|                        | - `empty_value`_                                                                |
|                        | - `years`_                                                                      |
|                        | - `months`_                                                                     |
|                        | - `days`_                                                                       |
|                        | - `format`_                                                                     |
|                        | - `model_timezone`_                                                             |
|                        | - `view_timezone`_                                                              |
+------------------------+---------------------------------------------------------------------------------+
| Prepisane opcije       | - `by_reference`_                                                               |
|                        | - `error_bubbling`_                                                             |
+------------------------+---------------------------------------------------------------------------------+
| Podedovane             | - `data`_                                                                       |
| opcije                 | - `invalid_message`_                                                            |
|                        | - `invalid_message_parameters`_                                                 |
|                        | - `read_only`_                                                                  |
|                        | - `disabled`_                                                                   |
|                        | - `mapped`_                                                                     |
|                        | - `inherit_data`_                                                               |
|                        | - `error_mapping`_                                                              |
+------------------------+---------------------------------------------------------------------------------+
| Starševski tip         | :doc:`form </reference/forms/types/form>`                                       |
+------------------------+---------------------------------------------------------------------------------+
| Razred                 | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\DateType`              |
+------------------------+---------------------------------------------------------------------------------+

Osnovna uporaba
---------------

To polje je zelo konfigurabilno, vendar enostavno za uporabo. Najpomembnejše
opcije so ``input`` in ``widget``.

Predpostavimo, da imate ``publishedAt`` polje, katerega osnovni datum je
objekt ``DateTime``. Sledeče nastavi tip ``date`` za to
polje kot tri različna polja izbire:

.. code-block:: php

    $builder->add('publishedAt', 'date', array(
        'input'  => 'datetime',
        'widget' => 'choice',
    ));

Opcija ``input`` *mora* biti spremenjena, da se ujame s tipom osnovnega
podatka date. Na primer, če podatek polja ``publishedAt``, kjer je unix timestamp,
boste potrebovali nastaviti ``input`` na ``timestamp``:

.. code-block:: php

    $builder->add('publishedAt', 'date', array(
        'input'  => 'timestamp',
        'widget' => 'choice',
    ));

Polje tudi podpira ``array`` in ``string`` kot veljavno opcijo ``input``
vrednosti.

Opcije polja
------------

.. include:: /reference/forms/types/options/date_widget.rst.inc

.. _form-reference-date-input:

.. include:: /reference/forms/types/options/date_input.rst.inc

empty_value
~~~~~~~~~~~

**tip**: ``string`` ali ``array``

Če je vaša widget opcija nastavljena na ``choice``, potem bo to polje predstavljeno
kot serija ``select`` kvadratkov. Opcija ``empty_value`` je lahko uporabljena, da
doda "prazen" vnos na vrh vsakega select kvadratka::

    $builder->add('dueDate', 'date', array(
        'empty_value' => '',
    ));

Alternativno lahko določite niz, ki je prikazan za "prazno" vrednost::

    $builder->add('dueDate', 'date', array(
        'empty_value' => array('year' => 'Year', 'month' => 'Month', 'day' => 'Day')
    ));

.. include:: /reference/forms/types/options/years.rst.inc

.. include:: /reference/forms/types/options/months.rst.inc

.. include:: /reference/forms/types/options/days.rst.inc

.. _reference-forms-type-date-format:

.. include:: /reference/forms/types/options/date_format.rst.inc

.. include:: /reference/forms/types/options/model_timezone.rst.inc

.. include:: /reference/forms/types/options/view_timezone.rst.inc

Prepisane opcije
----------------

by_reference
~~~~~~~~~~~~

**privzeto**: ``false``

Razredi ``DateTime`` so tretirani kot nespremenljivi objekti.

error_bubbling
~~~~~~~~~~~~~~

**privzeto**: ``false``

Podedovane opcije
-----------------

Te opcije dedujejo iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/data.rst.inc

.. include:: /reference/forms/types/options/invalid_message.rst.inc

.. include:: /reference/forms/types/options/invalid_message_parameters.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. include:: /reference/forms/types/options/inherit_data.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

Spremenljivke polja
-------------------

+---------------+------------+-----------------------------------------------------------------------+
| Spremenljivka | Tip        | Uporaba                                                               |
+===============+============+=======================================================================+
| widget        | ``mixed``  | Vrednost opcije `widget`_.                                            |
+---------------+------------+-----------------------------------------------------------------------+
| type          | ``string`` | Samo predstavlja, ko je widget ``single_text`` in HTML5 je aktiviran, |
|               |            | vsebuje vnosni tip za uporabo (``datetime``, ``date`` ali ``time``).  |
+---------------+------------+-----------------------------------------------------------------------+
| date_pattern  | ``string`` | Niz z obliko datuma za uporabo.                                       |
+---------------+------------+-----------------------------------------------------------------------+
