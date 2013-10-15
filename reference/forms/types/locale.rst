.. index::
   single: Forms; Fields; locale

locale tip polja
================

Tip ``locale`` je podmnožica ``ChoiceType``, ki omogoča, da uporabnik
izbere iz velikega seznama lokalizacij (jezik+država). Kot dodaten bonus
so imena lokalizacij prikazana v jeziku uporabnika.

Vrednost ("value") za vsako lokalizacijo je ali dvo črkovna IS=639-1 *language* koda
(npr. ``sl``), ali koda jezika, ki ji sledi podčrtaj (``_``) in nato
ISO3166 *country* koda (npr. ``sl_SI`` za Slovenščino/Slovenijo).

.. note::

   Lokalizacija vašega uporabnika je ugotovljena z uporabo :phpmethod:`Locale::getDefault`

Z razliko od tipa ``choice`` ne potrebujete specificirati ``choices`` ali
opcije ``choice_list``, saj tip polja avtomatsko uporablja velik seznam
lokalizacij. *Lahko* določite katerokoli izmed teh opcij ročno, vendar potem
bi morali uporabiti samo tip ``choice`` direktno.

+----------------+------------------------------------------------------------------------+
| Izpisan kot    | lahko so različne značke (glejte :ref:`forms-reference-choice-tags`)   |
+----------------+------------------------------------------------------------------------+
| Prepisane      | - `choices`_                                                           |
| opcije         |                                                                        |
+----------------+------------------------------------------------------------------------+
| Podedovane     | - `multiple`_                                                          |
| opcije         | - `expanded`_                                                          |
|                | - `preferred_choices`_                                                 |
|                | - `empty_value`_                                                       |
|                | - `error_bubbling`_                                                    |
|                | - `error_mapping`_                                                     |
|                | - `required`_                                                          |
|                | - `label`_                                                             |
|                | - `read_only`_                                                         |
|                | - `disabled`_                                                          |
|                | - `mapped`_                                                            |
+----------------+------------------------------------------------------------------------+
| Starševski tip | :doc:`choice </reference/forms/types/choice>`                          |
+----------------+------------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\LanguageType` |
+----------------+------------------------------------------------------------------------+

Prepisane opcije
----------------

choices
~~~~~~~

**privzeto**: ``Symfony\Component\Intl\Intl::getLocaleBundle()->getLocaleNames()``

Opcija choices je privzeto nastavljena na vse lokalizacije. Uporablja privzeto lokalizacijo
za določanje jezika.


Podedovane opcije
-----------------

Te opcije dedujejo iz tipa :doc:`choice </reference/forms/types/choice>`:

.. include:: /reference/forms/types/options/multiple.rst.inc

.. include:: /reference/forms/types/options/expanded.rst.inc

.. include:: /reference/forms/types/options/preferred_choices.rst.inc

.. include:: /reference/forms/types/options/empty_value.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

Te opcije dedujejo iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc
