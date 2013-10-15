.. index::
   single: Forms; Fields; email

email tip polja
===============

Polje ``email`` je tekstovno polje, ki je izpisano z uporabo HTML5
``<input type="email" />`` značke.

+----------------+---------------------------------------------------------------------+
| Izpisan kot    | ``input`` ``email`` polje (tekstovni kvadratek)                     |
+----------------+---------------------------------------------------------------------+
| Podedovane     | - `max_length`_                                                     |
| opcije         | - `required`_                                                       |
|                | - `label`_                                                          |
|                | - `trim`_                                                           |
|                | - `read_only`_                                                      |
|                | - `disabled`_                                                       |
|                | - `error_bubbling`_                                                 |
|                | - `error_mapping`_                                                  |
|                | - `mapped`_                                                         |
+----------------+---------------------------------------------------------------------+
| Starševski tip | :doc:`form </reference/forms/types/form>`                           |
+----------------+---------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\EmailType` |
+----------------+---------------------------------------------------------------------+

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
