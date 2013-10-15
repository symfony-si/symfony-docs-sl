.. index::
   single: Forms; Fields; checkbox

checkbox tip polja
==================

Izdela eno vnosno polje za potrditev. Ta bi moral biti vedno uporabljen za polje, ki
ima logično vrednost (boolean): če je kvadratek označen, bo polje nastavljeno na true,
če kvadratek ni označen, bo vrednost nastavljena na false.

+----------------+------------------------------------------------------------------------+
| Izpisan kot    | ``input`` ``checkbox`` polje                                           |
+----------------+------------------------------------------------------------------------+
| Opcije         | - `value`_                                                             |
+----------------+------------------------------------------------------------------------+
| Podedovanje    | - `required`_                                                          |
| opcije         | - `label`_                                                             |
|                | - `read_only`_                                                         |
|                | - `disabled`_                                                          |
|                | - `error_bubbling`_                                                    |
|                | - `error_mapping`_                                                     |
|                | - `mapped`_                                                            |
+----------------+------------------------------------------------------------------------+
| Starševski tip | :doc:`form </reference/forms/types/form>`                              |
+----------------+------------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\CheckboxType` |
+----------------+------------------------------------------------------------------------+

Primer uporabe
--------------

.. code-block:: php

    $builder->add('public', 'checkbox', array(
        'label'     => 'Show this entry publicly?',
        'required'  => false,
    ));

Opcije polja
------------

vrednost
~~~~~~~~

**tip**: ``mixed`` **privzeto**: ``1``

Vrednost, ki je dejansko uporabljena kot vrednost potrditvena polja. To
ne vpliva na vrednost, ki je nastavljena na vašem objektu.

Podedovane opcije
-----------------

Te opcije podedujejo iz the tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc
