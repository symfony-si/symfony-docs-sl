.. index::
   single: Forms; Fields; timezone

timezone tip polja
==================

Tip ``timezone`` je podmnožica ``ChoiceType``, ki dovoljuje uporabniku,
da izbere iz vseh možnih časovnih con.

Vrednost ("value") za vsako časovno cono je celotno ime časovne cone, kot je
``America/Chicago`` ali ``Europe/Istanbul``.

Z razliko od ``choice`` tipa, ne potrebujete specificirati ``choices`` ali
``choice_list`` opcije, saj polje avtomatsko uporablja velik seznam
lokalizacij. *Lahko* specificirate katerokoli izmed teh opcij ročno, vendar
potem bi morali samo uporabiti tip ``choice`` direktno.

+----------------+------------------------------------------------------------------------+
| Izpisan kot    | lahko so različne značke (see :ref:`forms-reference-choice-tags`)      |
+----------------+------------------------------------------------------------------------+
| Prepisane      | - `choice_list`_                                                       |
| opcije         |                                                                        |
+----------------+------------------------------------------------------------------------+
| Podedovane     | - `multiple`_                                                          |
| opcije         | - `expanded`_                                                          |
|                | - `preferred_choices`_                                                 |
|                | - `empty_value`_                                                       |
|                | - `required`_                                                          |
|                | - `label`_                                                             |
|                | - `read_only`_                                                         |
|                | - `disabled`_                                                          |
|                | - `error_bubbling`_                                                    |
|                | - `error_mapping`_                                                     |
|                | - `mapped`_                                                            |
+----------------+------------------------------------------------------------------------+
| Starševski tip | :doc:`choice </reference/forms/types/choice>`                          |
+----------------+------------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\TimezoneType` |
+----------------+------------------------------------------------------------------------+

Prepisane opcije
----------------

choice_list
~~~~~~~~~~~

**privzeto**: :class:`Symfony\\Component\\Form\\Extension\\Core\\ChoiceList\\TimezoneChoiceList`

Tip timezone je privzeto choice_list za vse časovne cone, vrnjene od
:phpmethod:`DateTimeZone::listIdentifiers`, razdeljene po kontinentih.

Podedovane opcije
-----------------

Te opcije dedujejo od tipa :doc:`choice </reference/forms/types/choice>`:

.. include:: /reference/forms/types/options/multiple.rst.inc

.. include:: /reference/forms/types/options/expanded.rst.inc

.. include:: /reference/forms/types/options/preferred_choices.rst.inc

.. include:: /reference/forms/types/options/empty_value.rst.inc

Te opcije dedujejo od tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc
