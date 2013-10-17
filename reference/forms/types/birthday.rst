.. index::
   single: Forms; Fields; birthday

birthday tip polja
==================

Polje :doc:`date </reference/forms/types/date>`, ki je specializirano za ravnanje s
podatki rojstnih dni.

Lahko se izpiše kot kvadratek za enostaven tekst, trije tekstovni kvadratki (mesec, dan in leto),
ali trije izbirni kvadratki.

Ta tip je v bistvu enak kot :doc:`datum </reference/forms/types/date>`
tip, vendar z več ustreznimi privzetimi vrednostmi za opcijo `years`_. Opcija `years`_
je privzeto nastavljena na 120 let nazaj glede na trenutno leto.

+----------------------+----------------------------------------------------------------------------------------------+
| Osnovni podatkovni   | lahko je ``DateTime``, ``string``, ``timestamp``, ali ``array``                              |
| tip                  | (glejte :ref:`input opcijo <form-reference-date-input>`)                                     |
+----------------------+----------------------------------------------------------------------------------------------+
| Izpisano kot         | lahko so trije izbirni kvadratki ali 1 ali 3 tekstovni kvadratki, na osnovi `widget`_ opcije |
+----------------------+----------------------------------------------------------------------------------------------+
| Prepisane opcije     | - `years`_                                                                                   |
+----------------------+----------------------------------------------------------------------------------------------+
| Podedovane opcije    | - `widget`_                                                                                  |
|                      | - `input`_                                                                                   |
|                      | - `empty_value`_                                                                             |
|                      | - `months`_                                                                                  |
|                      | - `days`_                                                                                    |
|                      | - `format`_                                                                                  |
|                      | - `model_timezone`_                                                                          |
|                      | - `view_timezone`_                                                                           |
|                      | - `invalid_message`_                                                                         |
|                      | - `invalid_message_parameters`_                                                              |
|                      | - `read_only`_                                                                               |
|                      | - `disabled`_                                                                                |
|                      | - `mapped`_                                                                                  |
|                      | - `inherit_data`_                                                                            |
+----------------------+----------------------------------------------------------------------------------------------+
| Starševski tip       | :doc:`date </reference/forms/types/date>`                                                    |
+----------------------+----------------------------------------------------------------------------------------------+
| Razred               | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\BirthdayType`                       |
+----------------------+----------------------------------------------------------------------------------------------+

Prepisane opcije
----------------

years
~~~~~

**tip**: ``array`` **privzeto**: 120 let nazaj od trenutnega leta

Seznam let, ki so na voljo za tip polje leto. Ta opcija je relevantna
samo, ko je ``widget`` opcija nastavljena na ``choice``.

Podedovane opcije
-----------------

Te opcije dedujejo iz :doc:`date </reference/forms/types/date>` tipa:

.. include:: /reference/forms/types/options/date_widget.rst.inc
    
.. include:: /reference/forms/types/options/date_input.rst.inc

.. include:: /reference/forms/types/options/empty_value.rst.inc

.. include:: /reference/forms/types/options/months.rst.inc

.. include:: /reference/forms/types/options/days.rst.inc

.. include:: /reference/forms/types/options/date_format.rst.inc

.. include:: /reference/forms/types/options/model_timezone.rst.inc

.. include:: /reference/forms/types/options/view_timezone.rst.inc

Te opcije dedujejo iz :doc:`form </reference/forms/types/form>` tipa:

.. include:: /reference/forms/types/options/invalid_message.rst.inc

.. include:: /reference/forms/types/options/invalid_message_parameters.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. include:: /reference/forms/types/options/inherit_data.rst.inc
