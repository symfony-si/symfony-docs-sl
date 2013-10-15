.. index::
   single: Forms; Fields; search

search tip polja
================

Izpisano je kot ``<input type="search" />`` polje, ki je tekstovni kvadratek s
posebnimi funkcionalnostmi podprtimi s strani nekaterih brskalnikov.

Preberite več o vnosnem iskalnem polju na `DiveIntoHTML5.info`_

+----------------+----------------------------------------------------------------------+
| Izpisan kot    | ``input search`` polje                                               |
+----------------+----------------------------------------------------------------------+
| Podedovane     | - `max_length`_                                                      |
| opcije         | - `required`_                                                        |
|                | - `label`_                                                           |
|                | - `trim`_                                                            |
|                | - `read_only`_                                                       |
|                | - `disabled`_                                                        |
|                | - `error_bubbling`_                                                  |
|                | - `error_mapping`_                                                   |
|                | - `mapped`_                                                          |
+----------------+----------------------------------------------------------------------+
| Starševski tip | :doc:`text </reference/forms/types/text>`                            |
+----------------+----------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\SearchType` |
+----------------+----------------------------------------------------------------------+

Podedovane opcije
-----------------

Te opcije so podedovane iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/max_length.rst.inc

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/trim.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. _`DiveIntoHTML5.info`: http://diveintohtml5.info/forms.html#type-search
