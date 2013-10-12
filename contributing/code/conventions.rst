Konvencije
==========

Dokument doc:`standards` opisuje kodne standarde za Symfony2
projekte in interne in tretje osebne pakete. Ta dokument opisuje
kodne standarde in konvencije uporabljene v jedru ogrodja, da se ga naredi
bolj konsistentnega in predvidljivega. Spodbujeni ste, da jim sledite v vaši
lastni kodi, vendar ni vam pa obvezno.

Imena metod
-----------

Ko ima objekt "glavne" mnoge relacije s povezanimi "stvarmi"
(objekti, parametri, ...), so imena metod normalizirana:

  * ``get()``
  * ``set()``
  * ``has()``
  * ``all()``
  * ``replace()``
  * ``remove()``
  * ``clear()``
  * ``isEmpty()``
  * ``add()``
  * ``register()``
  * ``count()``
  * ``keys()``

Uporaba teh metod je samo dovoljena, ko je jasno, da gre za glavno
relacijo:

* ``CookieJar`` ima (has) mnogo  ``Cookie`` objektov;

* Service ``Container`` ima mnogo storitev in mnogo parametrov (kot storitve
  v glavni relaciji, konvencije poimenovanja so uporabljene za to relacijo);

* Console ``Input`` ima mnogo argumentov in mnogo opcij. Ne obstaja "glavne"
  relacije in konvencije poimenovanja ne veljajo.

Za mnogo relacij, kjer konvencije ne veljajo, morajo biti uporabljene
sledeče metode namesto tega (kjer je ``XXX`` ime povezane stvari):

+----------------+-------------------+
| Glavna relacija| Ostale relacije   |
+================+===================+
| ``get()``      | ``getXXX()``      |
+----------------+-------------------+
| ``set()``      | ``setXXX()``      |
+----------------+-------------------+
| n/a            | ``replaceXXX()``  |
+----------------+-------------------+
| ``has()``      | ``hasXXX()``      |
+----------------+-------------------+
| ``all()``      | ``getXXXs()``     |
+----------------+-------------------+
| ``replace()``  | ``setXXXs()``     |
+----------------+-------------------+
| ``remove()``   | ``removeXXX()``   |
+----------------+-------------------+
| ``clear()``    | ``clearXXX()``    |
+----------------+-------------------+
| ``isEmpty()``  | ``isEmptyXXX()``  |
+----------------+-------------------+
| ``add()``      | ``addXXX()``      |
+----------------+-------------------+
| ``register()`` | ``registerXXX()`` |
+----------------+-------------------+
| ``count()``    | ``countXXX()``    |
+----------------+-------------------+
| ``keys()``     | n/a               |
+----------------+-------------------+

.. note::

    Medtem ko sta "setXXX" in "replaceXXX" zelo podobna, je ena znana
    razlika: "setXXX" lahko zamenja, ali doda nove elemente relaciji.
    "replaceXXX" po drugi strani ne more dodati novih elementov. Če je
    podan "replaceXXX" neznani ključ mora vrniti izjemno (exception).

.. _contributing-code-conventions-deprecations:

Opuščanja
---------

Občasno so nekateri razredi in/ali metode v ogrodju opuščene;
to se zgodi, ko izvedbe lastnosti ni mogoče spremeniti zaradi
težav združljivosti za nazaj, vendar še vedno hočemo predlagati
"boljšo" alternativo. V tem primeru je lahko stara izvedba enostavno
**opuščena**.

Lastnost je označena kot opuščena z dodajanje ``@deprecated`` phpdoc
v ustreznih razredih, metodah, lastnostih, ...::

    /**
     * @deprecated Deprecated since version 2.X, to be removed in 2.Y. Use XXX instead.
     */

Opuščeno sporočilo bi moralo navajati verzijo, ko je razred/metoda
opuščena, verzijo ko bo odstranjena in kadarkoli možno, kako je bila
lastnost zamenjana.

PHP ``E_USER_DEPRECATED`` napaka mora biti tudi izvedena, da pomaga uporabnikom
z migracijo in se pričeti eno ali dve manjši verziji pred verzijo, kjer bo
lastnost odstranjena (odvisno od kritičnosti odstranitve)::

    trigger_error(
        'XXX() is deprecated since version 2.X and will be removed in 2.Y. Use XXX instead.',
        E_USER_DEPRECATED
    );
