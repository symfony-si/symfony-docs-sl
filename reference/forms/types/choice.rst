.. index::
   single: Forms; Fields; choice

choice tip polja
================

Večnamensko polje uporabljeno za omogočanje uporabniku "izbrati" eno ali več opcij.
Lahko je izpisan kot ``select`` značka, radio button-i ali checkbox-i.

Za uporabo tega polja, morate specificirati *ali* ``choice_list`` ali ``choices``
opcijo.

+----------------+------------------------------------------------------------------------------+
| Izpisan kot    | lahko so različne značke (glejte spodaj)                                     |
+----------------+------------------------------------------------------------------------------+
| Opcije         | - `choices`_                                                                 |
|                | - `choice_list`_                                                             |
|                | - `multiple`_                                                                |
|                | - `expanded`_                                                                |
|                | - `preferred_choices`_                                                       |
|                | - `empty_value`_                                                             |
+----------------+------------------------------------------------------------------------------+
| Podedovane     | - `required`_                                                                |
| opcije         | - `label`_                                                                   |
|                | - `read_only`_                                                               |
|                | - `disabled`_                                                                |
|                | - `error_bubbling`_                                                          |
|                | - `error_mapping`_                                                           |
|                | - `mapped`_                                                                  |
|                | - `inherit_data`_                                                            |
|                | - `by_reference`_                                                            |
|                | - `empty_data`_                                                              |
+----------------+------------------------------------------------------------------------------+
| Starševski tip | :doc:`obrazec </reference/forms/types/form>`                                 |
+----------------+------------------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\ChoiceType`         |
+----------------+------------------------------------------------------------------------------+

Primer uporabe
--------------

Najenostavnejši način za uporabo tega polja je določanje izbir direktno preko
opcije ``choices``. Ključ polja (array) postane vrednost, ki je dejansko
nastavljena na vašem osnovnem objektu (npr. ``m``), medtem ko je vrednost,
kar uporabnik vidi v obrazcu (npr. ``Male``).

.. code-block:: php

    $builder->add('gender', 'choice', array(
        'choices'   => array('m' => 'Male', 'f' => 'Female'),
        'required'  => false,
    ));

Z nastavitvijo ``multiple`` na true, lahko dovoljujete uporabniku izbiro večih
vrednosti. Widget bo izpisan kot ``multiple`` ``select`` značka ali serija
potrditvenih polj odvisno od opcije ``expanded``:

.. code-block:: php

    $builder->add('availability', 'choice', array(
        'choices'   => array(
            'morning'   => 'Morning',
            'afternoon' => 'Afternoon',
            'evening'   => 'Evening',
        ),
        'multiple'  => true,
    ));

Lahko tudi uporabite opcijo ``choice_list``, ki vzame objekt, ki lahko
specificira izbire vašega widget-a.

.. _forms-reference-choice-tags:

.. include:: /reference/forms/types/options/select_how_rendered.rst.inc

Opcije polja
------------

izbire
~~~~~~

**tip**: ``array`` **privzeto**: ``array()``

To je najosnovnejši način za določanje izbir, ki bi morale biti uporabljene
na tem polju. Opcija ``choices`` je polje, kjer je ključ polja
element vrednosti in vrednost polja je oznaka elementa::

    $builder->add('gender', 'choice', array(
        'choices' => array('m' => 'Male', 'f' => 'Female')
    ));

choice_list
~~~~~~~~~~~

**tip**: ``Symfony\Component\Form\Extension\Core\ChoiceList\ChoiceListInterface``

To je en način določanja uporabljenih opcij za to polje.
Opcija ``choice_list`` mora biti instanca ``ChoiceListInterface``.
Za bolj napredne primere, razred po meri, ki implementira vmesnik,
je lahko izdelan za dobavo izbir.

.. include:: /reference/forms/types/options/multiple.rst.inc

.. include:: /reference/forms/types/options/expanded.rst.inc

.. include:: /reference/forms/types/options/preferred_choices.rst.inc

.. include:: /reference/forms/types/options/empty_value.rst.inc

Podedovane opcije
-----------------

Te opcije dedujejo iz tipa :doc:`obrazec </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc

.. include:: /reference/forms/types/options/inherit_data.rst.inc

.. include:: /reference/forms/types/options/by_reference.rst.inc

.. include:: /reference/forms/types/options/empty_data.rst.inc
