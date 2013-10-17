.. index::
   single: Forms; Fields; text

text tip polja
==============

Polje text predstavlja najbolj osnovno tekstovno vnosno polje.

+----------------+--------------------------------------------------------------------+
| Izpisan kot    | ``input`` ``text`` polje                                           |
+----------------+--------------------------------------------------------------------+
| Podedovane     | - `max_length`_                                                    |
| opcije         | - `required`_                                                      |
|                | - `label`_                                                         |
|                | - `trim`_                                                          |
|                | - `read_only`_                                                     |
|                | - `disabled`_                                                      |
|                | - `error_bubbling`_                                                |
|                | - `error_mapping`_                                                 |
|                | - `mapped`_                                                        |
+----------------+--------------------------------------------------------------------+
| Starševski tip | :doc:`form </reference/forms/types/form>`                          |
+----------------+--------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\TextType` |
+----------------+--------------------------------------------------------------------+


Podedovane opcije
-----------------

Te opcije dedujejo iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/max_length.rst.inc

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/trim.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc
