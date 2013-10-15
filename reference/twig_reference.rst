.. index::
    single: Symfony2 Twig extensions

Symfony2 Twig razširitve
========================

Twig je privzet motor predlog za Symfony2. Vsebuje že veliko vgrajenih funkcij,
filtrov, značk in testov (`http://twig.sensiolabs.org/documentation`_
nato se pomaknite na dno).

Symfony2 dodaja več raširitev po meni na Twig za integracijo nekaterih komponent
v Twig predloge. Spodaj so informacije o vseh funkcijah po meri, filtrih, značkah
in testih, ki so dodani, ko se uporablja jedro Symfony2 ogrodja.

Na voljo so lahko tudi značke v paketih, ki jih uporabljate, ki tu niso
navedene.

Funkcije
--------

.. versionadded:: 2.2
    Funkciji ``render`` in ``controller`` sta novi v Symfoyn 2.2. Pred tem
    je bila uporabljana značka ``{% render %}`` in je imela različen podpis.

+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| Sintaksa funkcij                                   | Uporaba                                                                                    |
+====================================================+============================================================================================+
| ``render(uri, options = {})``                      | To bo izpisalo fragment za dani krmilnik ali URL                                           |
| ``render(controller('B:C:a', {params}))``          | Za več informacij, glejte :ref:`templating-embedding-controller`.                          |
| ``render(path('route', {params}))``                |                                                                                            |
| ``render(url('route', {params}))``                 |                                                                                            |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``render_esi(controller('B:C:a', {params}))``      | To bo generiralo ESI značko, ko je mogoče ali se drugače vrnilo na ``render``              |
| ``render_esi(url('route', {params}))``             | obnašanje. Za več informacij, glejte :ref:`templating-embedding-controller`.               |
| ``render_esi(path('route', {params}))``            |                                                                                            |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``render_hinclude(controller(...))``               | To bo generiralo Hinclude značko za dani krmilnik ali URL.                                 |
| ``render_hinclude(url('route', {params}))``        | Za več informacij, glejte :ref:`templating-embedding-controller`.                          |
| ``render_hinclude(path('route', {params}))``       |                                                                                            |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``controller(attributes = {}, query = {})``        | Uporabljen skupaj z ``render`` značko za sklicevanje na krmilnik, ki ga želite izpisati.   |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``asset(path, packageName = null)``                | Dobite javno pot do sredstva, več informacij v                                             |
|                                                    | ":ref:`book-templating-assets`".                                                           |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``asset_version(packageName = null)``              | Dobite trenutno verzijo paketa, več informacij v                                           |
|                                                    | ":ref:`book-templating-assets`".                                                           |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form(view, variables = {})``                     | To bo izpisalo HTML celotnega obrazca, več informacij v                                    |
|                                                    | :ref:`Referenci Twig obrazcev<reference-forms-twig-form>`.                                 |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_start(view, variables = {})``               | To bo izpisalo začetno HTML značko obrazca, več informacij                                 |
|                                                    | v :ref:`referencu Twig obrazcev<reference-forms-twig-start>`.                              |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_end(view, variables = {})``                 | To bo izpisalo končno HTML značko obrazca skupaj z vsemi polji, ki                         |
|                                                    | morda še niso bila izpisana, več informacij                                                |
|                                                    | v :ref:`referenci Twig obrazcev<reference-forms-twig-end>`.                                |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_enctype(view)``                             | To bo izpisalo zahtevan ``enctype="multipart/form-data"`` atribut,                         |
|                                                    | če obrazec vsebuje vsaj eno polje za nalaganje datotek, več informacij v                   |
|                                                    | :ref:`referenci Twig obrazrev <reference-forms-twig-enctype>`.                             |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_widget(view, variables = {})``              | To bo izpisalo celoten obrazec ali določen HTML widget polja,                              |
|                                                    | več informacij v :ref:`referenci Twig obrazcev <reference-forms-twig-widget>`.             |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_errors(view)``                              | To bo izpisalo kakršnekoli napake za dano polje ali "globalne" napake,                     |
|                                                    | več infomracij v :ref:`referenci Twig obrazcev <reference-forms-twig-errors>`.             |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_label(view, label = null, variables = {})`` | To bo izpisalo oznako danega polja, več informacij v                                       |
|                                                    | :ref:`referenci Twig obrazcev <reference-forms-twig-label>`.                               |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_row(view, variables = {})``                 | To bo izpisalo vrstico (oznake polja, napake in widget-e) danega                           |
|                                                    | polja, več informacij v :ref:`referenci Twig obrazcev <reference-forms-twig-row>`.         |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``form_rest(view, variables = {})``                | To bo izpisalo vsa polja, ki še morda niso bila izpisana, več                              |
|                                                    | informacij v :ref:`referenci Twig obrazcev <reference-forms-twig-rest>`.                   |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``csrf_token(intention)``                          | To bo izpisalo CSRF žeton. Uporabite to funkcijo, če želite CSRF zaščito brez              |
|                                                    | izdelave obrazca                                                                           |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``is_granted(role, object = null, field = null)``  | To bo vrnilo ``true``, če ima trenutni uporabnik potrebne vloge, več                       |
|                                                    | informacij v ":ref:`book-security-template`"                                               |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``logout_path(key)``                               | To bo generiralo relativni odjavni URL za dani požarni zid                                 |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``logout_url(key)``                                | Enako ``logout_path(...)`` vendar to generira absolutni url                                |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``path(name, parameters = {})``                    | Dobite relativni url za dano smer, več informacij v                                        |
|                                                    | ":ref:`book-templating-pages`".                                                            |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+
| ``url(name, parameters = {})``                     | Enako ``path(...)`` vendar to generira absolutni url                                       |
+----------------------------------------------------+--------------------------------------------------------------------------------------------+

Filtri
------

+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| Sintaksa filtra                                                                 | Uporaba                                                           |
+=================================================================================+===================================================================+
| ``text|humanize``                                                               | Naredi tehnično ime človeku bralno (zamenja podčrtaje s           |
|                                                                                 | presledki in nizu naredi velike črke)                             |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``text|trans(arguments = {}, domain = 'messages', locale = null)``              | To bo prevedlo tekst v trenutni jezik, več                        |
|                                                                                 | informacij v                                                      |
|                                                                                 | :ref:`Filtrih prevodov <book-translation-filters>`.               |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``text|transchoice(count, arguments = {}, domain = 'messages', locale = null)`` | To bo prevedlo tekst z množino, več informacij                    |
|                                                                                 | v :ref:`filtrih prevodov <book-translation-filters>`.             |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``variable|yaml_encode(inline = 0)``                                            | To bo pretvorilo tekst spremenljivke v YAML sintakso.             |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``variable|yaml_dump``                                                          | To bo izpisalo yaml sintakso z njenim tipom.                      |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``classname|abbr_class``                                                        | To bo izpisalo ``abbr`` element s kratkim imenom                  |
|                                                                                 | PHP razreda.                                                      |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``methodname|abbr_method``                                                      | To bo izpisalo PHP metodo znotraj elementa ``abbr``               |
|                                                                                 | (npr. ``Symfony\Component\HttpFoundation\Response::getContent``   |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``arguments|format_args``                                                       | To bo izpisalo niz z argumenti funkcije in njihovimi              |
|                                                                                 | tipi.                                                             |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``arguments|format_args_as_text``                                               | Enako ``[...]|format_args``, vendar počisti značke.               |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``path|file_excerpt(line)``                                                     | To bo izpisalo odlomek datoteke kode okrog dane vrstice.          |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``path|format_file(line, text = null)``                                         | To bo izpisalo pot datoteke v povezavi.                           |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``exceptionMessage|format_file_from_text``                                      | Enako ``format_file`` razen, če je izpiše niz privzete PHP napake |
|                                                                                 | v pot datoteke (t.j. 'in foo.php on line 45')                     |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+
| ``path|file_link(line)``                                                        | This will render a path to the correct file (and line number)     |
+---------------------------------------------------------------------------------+-------------------------------------------------------------------+

Značke
------

.. versionadded:: 2.4
    Značka stopwatch je bila dodana v Symfony 2.4.

+---------------------------------------------------+--------------------------------------------------------------------+
| Sintaksa značke                                   | Uporaba                                                            |
+===================================================+====================================================================+
| ``{% form_theme form 'file' %}``                  | To bo preverilo znotraj dane datoteke za prepisane bloke obrazca,  |
|                                                   | več informacij v :doc:`/cookbook/form/form_customization`.         |
+---------------------------------------------------+--------------------------------------------------------------------+
| ``{% trans with {variables} %}...{% endtrans %}`` | To bo prevedlo in izpisalo tekst, več informacij v                 |
|                                                   | :ref:`book-translation-tags`                                       |
+---------------------------------------------------+--------------------------------------------------------------------+
| ``{% transchoice count with {variables} %}``      | To bo prevedlo in izpisalo tekst z množino, več                    |
| ...                                               | informacij v :ref:`book-translation-tags`                          |
| ``{% endtranschoice %}``                          |                                                                    |
+---------------------------------------------------+--------------------------------------------------------------------+
| ``{% trans_default_domain language %}``           | To bo nastavilo privzeto domeno za katalog sporočil v              |
|                                                   | trenutni predlogi                                                  |
+---------------------------------------------------+--------------------------------------------------------------------+
| ``{% stopwatch 'name' %}...{% endstopwatch %}``   | To bo zagnalo čas izvajanja kode znotraj nje in dodalo na          |
|                                                   | časovnico paketa WebProfilerBundle.                                |
+---------------------------------------------------+--------------------------------------------------------------------+

Testi
-----

+---------------------------------------------------+------------------------------------------------------------------------------+
| Sintaksa testa                                    | Uporaba                                                                      |
+===================================================+==============================================================================+
| ``selectedchoice(choice, selectedValue)``         | Vrne ``true``, če je izbira izbrana za dano vrednost obrazca                 |
+---------------------------------------------------+------------------------------------------------------------------------------+

Globalne spremenljivke
----------------------

+-------------------------------------------------------+------------------------------------------------------------------------------------+
| Spremenljivka                                         | Uporaba                                                                            |
+=======================================================+====================================================================================+
| ``app`` *Attributes*: ``app.user``, ``app.request``   | Spremenljivka ``app`` je navoljo kjerkoli in vam da hiter                          |
| ``app.session``, ``app.environment``, ``app.debug``   | dostop do mnogih pogosto potrebnih objektov. Spremenljivka ``app`` je              |
| ``app.security``                                      | instanca :class:`Symfony\\Bundle\\FrameworkBundle\\Templating\\GlobalVariables`    |
+-------------------------------------------------------+------------------------------------------------------------------------------------+

Razširitve Symfony standardne izdaje
------------------------------------

Symfony standardna izdaja dodaja nekaj paketov v Symfony2 jedro ogrodja.
Te paketi imajo ostale Twig razširitve:

* **Twig Extension** vključuje vse razširitve, ki ne pripadajo
  Twig jedru, vendar so lahko zanimive. Lahko preberete več o tem v
  `uradni dokumentaciji Twig razširitve`_
* **Assetic** dodaja ``{% stylesheets %}``, ``{% javascripts %}`` in
  ``{% image %}`` značke. Lahko preberete več o njih v
  :doc:`dokumentaciji Assetic </cookbook/assetic/asset_management>`;

.. _`uradni dokumentaciji Twig razširitve`: http://twig.sensiolabs.org/doc/extensions/index.html
.. _`http://twig.sensiolabs.org/documentation`: http://twig.sensiolabs.org/documentation
