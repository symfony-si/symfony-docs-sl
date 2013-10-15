.. index::
   single: Forms; Fields; hidden

hidden tip polja
================

Tip hidden predstavlja skrito vnosno polje.

+----------------+----------------------------------------------------------------------+
| Izpisan kot    | ``input`` ``hidden`` polje                                           |
+----------------+----------------------------------------------------------------------+
| Prepisane      | - `required`_                                                        |
| opcije         | - `error_bubbling`_                                                  |
+----------------+----------------------------------------------------------------------+
| Inherited      | - `data`_                                                            |
| options        | - `property_path`_                                                   |
|                | - `mapped`_                                                          |
|                | - `error_mapping`_                                                   |
+----------------+----------------------------------------------------------------------+
| Starševski tip | :doc:`form </reference/forms/types/form>`                            |
+----------------+----------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\HiddenType` |
+----------------+----------------------------------------------------------------------+

Prepisane opcije
----------------

required
~~~~~~~~

**privzeto**: ``false``

Skrita polja ne morejo imeti atributa "required".

error_bubbling
~~~~~~~~~~~~~~

**privzeto**: ``true``

Poda napake vrhnjemu obrazcu, drugače ne bodo vidne.

Podedovane opcije
-----------------

Te opcije so podedovane iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/data.rst.inc

.. include:: /reference/forms/types/options/property_path.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc
