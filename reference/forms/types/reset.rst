.. index::
   single: Forms; Fields; reset

reset tip polja
===============

.. versionadded:: 2.3
    Tip ``reset`` je bil predstavljen v Symfony 2.3

Gumb, ki ponastavi vsa polja na njihove prvotne vrednosti.

+----------------+---------------------------------------------------------------------+
| Izpisan kot    | ``input`` ``reset`` značka                                          |
+----------------+---------------------------------------------------------------------+
| Podedovane     | - `attr`_                                                           |
| opcije         | - `disabled`_                                                       |
|                | - `label`_                                                          |
|                | - `label_attr`_                                                     |
|                | - `translation_domain`_                                             |
+----------------+---------------------------------------------------------------------+
| Starševski tip | :doc:`button</reference/forms/types/button>`                        |
+----------------+---------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\ResetType` |
+----------------+---------------------------------------------------------------------+

Podedovane opcije
-----------------

.. include:: /reference/forms/types/options/button_attr.rst.inc

.. include:: /reference/forms/types/options/button_disabled.rst.inc

.. include:: /reference/forms/types/options/button_label.rst.inc

.. include:: /reference/forms/types/options/label_attr.rst.inc

.. include:: /reference/forms/types/options/button_translation_domain.rst.inc
