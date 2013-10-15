.. index::
    single: Forms; Fields; currency

currency tip polja
==================

Tip ``currency`` je podmnožica
:doc:`tipa choice </reference/forms/types/choice>`, ki omogoča uporabniku, da
izbere iz velikega seznama `3-črkovnih ISO 4217`_ valut.

Za razliko od tipa ``choice`` ne potrebujete določati ``choices`` ali
``choice_list`` opcij, saj tip polja avtomatsko uporablja velik seznam
valut. *Lahko* določite katerokoli izmed teh opcij ročno, vendar potem
bi morali uporabiti samo tip ``choice`` direktno.

+----------------+------------------------------------------------------------------------+
| Izpisan kot    | lahko so različne značkes (glejte :ref:`forms-reference-choice-tags`)  |
+----------------+------------------------------------------------------------------------+
| Prepisane      | - `choices`_                                                           |
| opcije         |                                                                        |
+----------------+------------------------------------------------------------------------+
| Podedovane     | - `multiple`_                                                          |
| opcije         | - `expanded`_                                                          |
|                | - `preferred_choices`_                                                 |
|                | - `empty_value`_                                                       |
|                | - `error_bubbling`_                                                    |
|                | - `required`_                                                          |
|                | - `label`_                                                             |
|                | - `read_only`_                                                         |
|                | - `disabled`_                                                          |
|                | - `mapped`_                                                            |
+----------------+------------------------------------------------------------------------+
| Starševski tip | :doc:`choice </reference/forms/types/choice>`                          |
+----------------+------------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\CurrencyType` |
+----------------+------------------------------------------------------------------------+

Prepisane opcije
----------------

choices
~~~~~~~

**privzeto**: ``Symfony\Component\Intl\Intl::getCurrencyBundle()->getCurrencyNames()``

Opcija ``choices`` je privzeto nastavljena na vse valute.

Podedovane opcije
-----------------

Te opcije dedujejo iz the tipa :doc:`choice</reference/forms/types/choice>`:

.. include:: /reference/forms/types/options/multiple.rst.inc

.. include:: /reference/forms/types/options/expanded.rst.inc

.. include:: /reference/forms/types/options/preferred_choices.rst.inc

.. include:: /reference/forms/types/options/empty_value.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

Te opcije dedujejoiz tipa :doc:`date</reference/forms/types/form>`:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. _`3-črkovnih ISO 4217`: http://en.wikipedia.org/wiki/ISO_4217
