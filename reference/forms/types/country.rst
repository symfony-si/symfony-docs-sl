.. index::
   single: Forms; Fields; country

country tip polja
=================

Tip ``country`` je podmnožica ``ChoiceType``, ki prikaže države
sveta. Kot dodaten bonus, imena držav so napisana na jeziku
uporabnika.

Vrednost ("value") za vsako državo je koda države (dve črki).

.. note::

   Lokalizacija vašega uporabnika je ugotovljena z uporabo :phpmethod:`Locale::getDefault`

Drugače kot tip ``choice``, ne potrebujete specificirati ``choices`` ali
``choice_list`` opcije, saj tip polja avtomatsko uporablja vse od držav sveta.
*Lahko* specificirate katerokoli od teh opcij ročno, vendar potem
bi morali uporabiti samo tip ``choice`` direktno.

+----------------+-----------------------------------------------------------------------+
| Izpisan kot    | lahko so različne značke (glejte :ref:`forms-reference-choice-tags`)  |
+----------------+-----------------------------------------------------------------------+
| Prepisane      | - `choices`_                                                          |
| opcije         |                                                                       |
+----------------+-----------------------------------------------------------------------+
| Podedovane     | - `multiple`_                                                         |
| opcije         | - `expanded`_                                                         |
|                | - `preferred_choices`_                                                |
|                | - `empty_value`_                                                      |
|                | - `error_bubbling`_                                                   |
|                | - `error_mapping`_                                                    |
|                | - `empty_data`_                                                       |
|                | - `required`_                                                         |
|                | - `label`_                                                            |
|                | - `label_attr`_                                                       |
|                | - `data`_                                                             |
|                | - `read_only`_                                                        |
|                | - `disabled`_                                                         |
|                | - `mapped`_                                                           |
+----------------+-----------------------------------------------------------------------+
| Starševski tip | :doc:`choice </reference/forms/types/choice>`                         |
+----------------+-----------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\CountryType` |
+----------------+-----------------------------------------------------------------------+

Prepisane opcije
----------------

choices
~~~~~~~

**privzeto**: ``Symfony\Component\Intl\Intl::getRegionBundle()->getCountryNames()``

Tip country ima privzeto ``choice`` opcijo na celoten seznam držav.
Lokalizacija je uporabljena za prevod imen držav.

Podedovane opcije
-----------------

Te opcije dedujejo iz :doc:`choice </reference/forms/types/choice>` tipa:

.. include:: /reference/forms/types/options/multiple.rst.inc
.. include:: /reference/forms/types/options/expanded.rst.inc

.. include:: /reference/forms/types/options/preferred_choices.rst.inc

.. include:: /reference/forms/types/options/empty_value.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

Te opcije dedujejo iz :doc:`form </reference/forms/types/form>` tipa:

.. include:: /reference/forms/types/options/empty_data.rst.inc

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/label_attr.rst.inc

.. include:: /reference/forms/types/options/data.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc
