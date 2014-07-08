.. caution::

    Opcija ``pattern`` je bila opuščena in bo odstranjena v 3.0.
    Namesto nje uporabite opcijo ``attr`` z nastavitvijo nje na polju s ključem ``pattern``.

pattern
~~~~~~~

**tip**: ``string`` **privzeto**: ``null``

To doda HTML5 ``pattern`` atribut za omejitev vnosnega polja z
danim splošnim izrazom.

.. caution::

    Atribut ``pattern`` ponuja klientno-stran preverjanja samo zaradi priročnih
    razlogov in ne sme biti uporabljena kot nadomestek za zanesljivo
    preverjanje na strežniški strani.

.. note::

    Ko uporabljate omejitve preverjanja, je ta opcija avtomatično nastavljena
    za nekatere omejitve, da se ujema s preverjanjem na strežniški strani.
