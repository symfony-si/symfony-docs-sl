.. index::
   single: Forms; Fields; submit

submit tip polja
================

.. versionadded:: 2.3
    Tip ``submit`` je predstavljen v Symfony 2.3

Gumb za pošiljanje.

+----------------------+----------------------------------------------------------------------+
| Izpisan kot          | ``input`` ``submit`` značka                                          |
+----------------------+----------------------------------------------------------------------+
| Podedovane           | - `attr`_                                                            |
| opcije               | - `disabled`_                                                        |
|                      | - `label`_                                                           |
|                      | - `label_attr`_                                                      |
|                      | - `translation_domain`_                                              |
+----------------------+----------------------------------------------------------------------+
| Starševski tip       | :doc:`button</reference/forms/types/button>`                         |
+----------------------+----------------------------------------------------------------------+
| Razred               | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\SubmitType` |
+----------------------+----------------------------------------------------------------------+

Gumb Submit ima dodatne metode
:method:`Symfony\\Component\\Form\\ClickableInterface::isClicked`, ki vam omogočajo
preveriti, ali je bil ta gumb uporabljen za pošiljanje obrazca. To je posebno
uporabno, ko :ref:`ima obrazec več gumbov za pošiljanje <book-form-submitting-multiple-buttons>`::

    if ($form->get('save')->isClicked()) {
        // ...
    }

Podedovane opcije
-----------------

.. include:: /reference/forms/types/options/button_attr.rst.inc

.. include:: /reference/forms/types/options/button_disabled.rst.inc

.. include:: /reference/forms/types/options/button_label.rst.inc

.. include:: /reference/forms/types/options/label_attr.rst.inc

.. include:: /reference/forms/types/options/button_translation_domain.rst.inc

Spremenljivke obrazca
---------------------

============ =========== ==============================================================
Spremenljiva Tip         Uporaba
============ =========== ==============================================================
clicked      ``Boolean`` Ali je gumb kliknjen ali ne.
============ =========== ==============================================================
