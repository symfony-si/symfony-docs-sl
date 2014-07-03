.. index::
   single: Forms; Fields; form

form tip polja
==============

Tip ``form`` vnaprej določa nekaj opcij, ki so kasneje na voljo
na vseh tipih za katere je ``form`` starševski tip.

+-----------+--------------------------------------------------------------------+
| Opcije    | - `data`_                                                          |
|           | - `data_class`_                                                    |
|           | - `empty_data`_                                                    |
|           | - `compound`_                                                      |
|           | - `required`_                                                      |
|           | - `label_attr`_                                                    |
|           | - `constraints`_                                                   |
|           | - `cascade_validation`_                                            |
|           | - `read_only`_                                                     |
|           | - `trim`_                                                          |
|           | - `mapped`_                                                        |
|           | - `property_path`_                                                 |
|           | - `max_length`_ (opuščena od 2.5)                                  |
|           | - `by_reference`_                                                  |
|           | - `error_bubbling`_                                                |
|           | - `inherit_data`_                                                  |
|           | - `error_mapping`_                                                 |
|           | - `invalid_message`_                                               |
|           | - `invalid_message_parameters`_                                    |
|           | - `extra_fields_message`_                                          |
|           | - `post_max_size_message`_                                         |
|           | - `pattern`_ (opuščena od 2.5)                                     |
|           | - `action`_                                                        |
|           | - `method`_                                                        |
+-----------+--------------------------------------------------------------------+
| Dedovane  | - `block_name`_                                                    |
| opcije    | - `disabled`_                                                      |
|           | - `label`_                                                         |
|           | - `attr`_                                                          |
|           | - `translation_domain`_                                            |
|           | - `auto_initialize`_                                               |
+-----------+--------------------------------------------------------------------+
| Starš     | none                                                               |
+-----------+--------------------------------------------------------------------+
| Razred    | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\FormType` |
+-----------+--------------------------------------------------------------------+

Opcije polja
------------

.. include:: /reference/forms/types/options/data.rst.inc

.. include:: /reference/forms/types/options/data_class.rst.inc

.. include:: /reference/forms/types/options/empty_data.rst.inc

.. include:: /reference/forms/types/options/compound.rst.inc

.. _reference-form-option-required:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label_attr.rst.inc

.. include:: /reference/forms/types/options/constraints.rst.inc

.. include:: /reference/forms/types/options/cascade_validation.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/trim.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. include:: /reference/forms/types/options/property_path.rst.inc

.. _reference-form-option-max_length:

.. include:: /reference/forms/types/options/max_length.rst.inc

.. include:: /reference/forms/types/options/by_reference.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/inherit_data.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/invalid_message.rst.inc

.. include:: /reference/forms/types/options/invalid_message_parameters.rst.inc

.. include:: /reference/forms/types/options/extra_fields_message.rst.inc

.. include:: /reference/forms/types/options/post_max_size_message.rst.inc

.. _reference-form-option-pattern:

.. include:: /reference/forms/types/options/pattern.rst.inc

.. include:: /reference/forms/types/options/action.rst.inc

.. include:: /reference/forms/types/options/method.rst.inc

Dedovane opcije
---------------

Sledeče opcije so definirane v
razredu :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\BaseType`.
Razred ``BaseType`` je starševski razred za oba ``form`` tip in
:doc:`button tip </reference/forms/types/button>`, vendar ni del
drevesa tipa obrazca (t.j. ne more biti uporabljen kot tip obrazca na svojem).

.. include:: /reference/forms/types/options/block_name.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/attr.rst.inc

.. include:: /reference/forms/types/options/translation_domain.rst.inc

.. include:: /reference/forms/types/options/auto_initialize.rst.inc
