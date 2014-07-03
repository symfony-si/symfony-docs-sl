required
~~~~~~~~

**tip**: ``Boolean`` **privzeto**: ``true``

Če je true, bo izpisan `HTML5 required atribut`_. Pripadajoča
``label`` bo tudi izpisana z razredom ``required``.

To je površno in neodvisno preverjanje obrazca. V najboljšem primeru, če omogočite Symfony-ju
uganiti vaš tip polja, potem bo vrednost te opcije uganjena iz
vaših informacij preverjanja.

.. note::

    Opcija required tudi vpliva, kako so prazni podatki za vsako polje
    upravljani. Za več informacij, glejte opcijo `empty_data`_.

.. _`HTML5 required atribut`: http://diveintohtml5.info/forms.html
