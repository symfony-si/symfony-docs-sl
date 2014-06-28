.. index::
   single: Forms; Fields; button

button tip polja
================

.. versionadded:: 2.3
    Tip ``button`` je bil predstavljen v Symfony 2.3

Enostaven, ne odziven gumb.

+----------------------+----------------------------------------------------------------------+
| Izpisan kot          | ``button`` značka                                                    |
+----------------------+----------------------------------------------------------------------+
| Podedovane           | - `attr`_                                                            |
| opcije               | - `disabled`_                                                        |
|                      | - `label`_                                                           |
|                      | - `translation_domain`_                                              |
+----------------------+----------------------------------------------------------------------+
| Starševski tip       | noben                                                                |
+----------------------+----------------------------------------------------------------------+
| Razred               | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\ButtonType` |
+----------------------+----------------------------------------------------------------------+

Podedovane opcije
-----------------

Sledeče opcije so definirane v
razredu :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\BaseType`.
Razred ``BaseType`` je starševski razred za tako tip ``button`` in
:doc:`tip obrazec </reference/forms/types/form>`, vendar ni del
drevo tipa obrazca (to pomeni, da ne more biti uporabljen kot tip obrazca na svojem).

.. include:: /reference/forms/types/options/button_attr.rst.inc

.. include:: /reference/forms/types/options/button_disabled.rst.inc

.. include:: /reference/forms/types/options/button_label.rst.inc

.. include:: /reference/forms/types/options/button_translation_domain.rst.inc
