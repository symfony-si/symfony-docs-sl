.. index::
   single: Forms; Fields; number

number tip polja
================

Izpiše vnosno tekstovno polje in specializira ravnanje s številskimi vnosi. Ta
tip nudi različne opcije za natančnost, zaokroževanje in grupiranje, ki
jih želite uporabiti za vašo številko.

+----------------+----------------------------------------------------------------------+
| Izpisan kot    | ``input`` ``text`` polje                                             |
+----------------+----------------------------------------------------------------------+
| Opcije         | - `rounding_mode`_                                                   |
|                | - `precision`_                                                       |
|                | - `grouping`_                                                        |
+----------------+----------------------------------------------------------------------+
| Podedovane     | - `required`_                                                        |
| opcije         | - `label`_                                                           |
|                | - `read_only`_                                                       |
|                | - `disabled`_                                                        |
|                | - `error_bubbling`_                                                  |
|                | - `error_mapping`_                                                   |
|                | - `invalid_message`_                                                 |
|                | - `invalid_message_parameters`_                                      |
|                | - `mapped`_                                                          |
+----------------+----------------------------------------------------------------------+
| Starševski tip | :doc:`form </reference/forms/types/form>`                            |
+----------------+----------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\NumberType` |
+----------------+----------------------------------------------------------------------+

Opcije polja
------------

.. include:: /reference/forms/types/options/precision.rst.inc

rounding_mode
~~~~~~~~~~~~~

**tip**: ``integer`` **privzeto**: ``NumberToLocalizedStringTransformer::ROUND_HALFUP``

Če poslana številka potrebuje biti zaokrožena (na osnovi ``precision``
opcije), imate nekaj nastavitvenih opcij za to zaokroževanje. Vsaka
opcija je konstanta v :class:`Symfony\\Component\\Form\\Extension\\Core\\DataTransformer\\NumberToLocalizedStringTransformer`:
    
* ``NumberToLocalizedStringTransformer::ROUND_DOWN`` Zaokroži proti nič.

* ``NumberToLocalizedStringTransformer::ROUND_FLOOR`` Zaokroži proti negativni
  neskončnosti.

* ``NumberToLocalizedStringTransformer::ROUND_UP`` Zaokroži stran od nič.

* ``NumberToLocalizedStringTransformer::ROUND_CEILING`` Zaokroži proti
  pozitivni neskončnosti.

* ``NumberToLocalizedStringTransformer::ROUND_HALF_DOWN`` Zaokroži proti
  "najbližjemu sosedu". Če oba soseda sta ekvidistančna, zaokroži navzdol.

* ``NumberToLocalizedStringTransformer::ROUND_HALF_EVEN`` Zaokroži proti
  "najbližjemu sosedu. Če sta oba soseda ekvidistančna, zaokroži proti
  celemu sosedu.

* ``NumberToLocalizedStringTransformer::ROUND_HALF_UP`` Zaokroži proti
  "najbližjemu sosedu". Če sta oba soseda ekvidistančna, zaokroži navzgor.

.. include:: /reference/forms/types/options/grouping.rst.inc

Podedovane opcije
-----------------

Te opcije dedujejo iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/invalid_message.rst.inc

.. include:: /reference/forms/types/options/invalid_message_parameters.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc
