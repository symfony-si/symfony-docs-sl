.. caution::

    Opcija ``max_length`` je bila opuščena in bo odstranjena v 3.0.
    Namesto uporabite opcijo ``attr`` z nastavitvijo na polje s ključem ``maxlength``.

max_length
~~~~~~~~~~

**tip**: ``integer`` **privzeto**: ``null``

Če ta opcija ni null, je dodan atribut ``maxlength``, ki
je uporabljen s strani nekaterih brskalnikov za omejitev količine teksta v polju.

To je samo brskalniško preverjanje, tako da podatki morajo še vedno biti preverjeni
s strežniške strani.
