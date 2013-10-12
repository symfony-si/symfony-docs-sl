Referenca omejitve potrjevanja
==============================

.. toctree::
   :maxdepth: 1
   :hidden:

   constraints/NotBlank
   constraints/Blank
   constraints/NotNull
   constraints/Null
   constraints/True
   constraints/False
   constraints/Type

   constraints/Email
   constraints/Length
   constraints/Url
   constraints/Regex
   constraints/Ip

   constraints/Range

   constraints/EqualTo
   constraints/NotEqualTo
   constraints/IdenticalTo
   constraints/NotIdenticalTo
   constraints/LessThan
   constraints/LessThanOrEqual
   constraints/GreaterThan
   constraints/GreaterThanOrEqual

   constraints/Date
   constraints/DateTime
   constraints/Time

   constraints/Choice
   constraints/Collection
   constraints/Count
   constraints/UniqueEntity
   constraints/Language
   constraints/Locale
   constraints/Country

   constraints/File
   constraints/Image

   constraints/CardScheme
   constraints/Currency
   constraints/Luhn
   constraints/Iban
   constraints/Isbn
   constraints/Issn

   constraints/Callback
   constraints/All
   constraints/UserPassword
   constraints/Valid

Validator je načrtovan za potrjevanje objektov napram *omejitvam (contraints)*.
V realnem življenju je omejitev lahko: "Torta ne sme biti zažgana". V
Symfony2 so omejitve podobne: Gre za trditve, kjer je pogoj
"true".

Podprte omejitve
----------------

Sledeče omejitve so originalno na voljo v Symfony2:

.. include:: /reference/constraints/map.rst.inc
