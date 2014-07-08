method
~~~~~~

.. versionadded:: 2.3
    Opcija ``method`` je bila predstavljena v Symfony 2.3.

**type**: ``string`` **default**: ``POST``

Ta opcija določa metodo HTTP uporabljeno za pošiljanje podatkov obrazca. Njena
vrednost je izpisana kot atribut ``method`` na elementu ``form`` in je
uporabljena za odločanje ali naj procesira pošiljanja obrazca v
metodi ``handleRequest()`` po pošiljanju. Možne vrednosti so:

* POST
* GET
* PUT
* DELETE
* PATCH

.. note::

    Ko je metoda PUT, PATCH ali DELETE, bo Symfony avtomatično
    izpisal skrito polje ``_method`` v vašem obrazcu. To je uporabljeno za "fake-anje"
    teh metod HTTP, saj niso podprte na standardnih brskalnikih. Za
    več informacij glejte :doc:`/cookbook/routing/method_parameters`.

.. note::

    Metoda PATCH omogoča pošiljanje delnih podatkov. Z drugimi besedami, če
    poslani podatki obrazca nimajo določenih polj, bodo le-ta ignorirana
    in uporabljene bodo privzete vrednosti (če so kakšne). Z vsemi ostalimi metodami HTTP,
    če poslani podatki obrazca nimajo kakšnih polj, so ta polja nastavljena
    na ``null``.
