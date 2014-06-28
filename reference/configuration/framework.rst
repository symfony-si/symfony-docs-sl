.. index::
    single: Configuration reference; Framework

Nastavitve FrameworkBundle ("framework")
========================================

Ta referenčni dokument je delo v teku. Moral bi biti točen, vendar
vse opcije še niso v celoti pokrite.

FrameworkBundle vsebuje večino "osnovnih" lastnosti ogrodja
in se ga lahko nastavi po ključem ``framework`` v vaših nastavitvah aplikacije.
To vključuje nastavitve, ki se tičejo sej, prevodov, obrazcev, preverjanja,
usmerjanja in več.

Nastavitve
----------

* `secret`_
* `http_method_override`_
* `ide`_
* `test`_
* `trusted_proxies`_
* `csrf_protection`_
    * enabled
    * field_name (deprecated)
* `form`_
    * enabled
    * csrf_protection
        * enabled
        * field_name
* `session`_
    * `name`_
    * `cookie_lifetime`_
    * `cookie_path`_
    * `cookie_domain`_
    * `cookie_secure`_
    * `cookie_httponly`_
    * `gc_divisor`_
    * `gc_probability`_
    * `gc_maxlifetime`_
    * `save_path`_
* `serializer`_
    * :ref:`enabled<serializer.enabled>`
* `templating`_
    * `assets_base_urls`_
    * `assets_version`_
    * `assets_version_format`_
* `profiler`_
    * `collect`_
    * :ref:`enabled <profiler.enabled>`

secret
~~~~~~

**type**: ``string`` **required**

To je niz, ki bi moral biti unikaten za vašo aplikacijo. V praksi je
uporabljen za generacijo žetonov CSRF, vendar je lahko uporabljen v kateremkoli
drugem kontekstu, kjer je uporabno imeti unikaten niz. Postane parameter
"service container" imenovan ``kernel.secret``.

.. _configuration-framework-http_method_override:

http_method_override
~~~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.3
    Opcija ``http_method_override`` je bila predstavljena v Symfony 2.3.

**type**: ``Boolean`` **default**: ``true``

To določa ali je parameter zahtevka ``method_`` uporabljen kot nameravana
metoda HTTP na zahtevku POST. Če je omogočen,
se :method:`Request::enableHttpMethodParameterOverride <Symfony\\Component\\HttpFoundation\\Request::enableHttpMethodParameterOverride>`
kliče avtomatsko. Postane parameter "service container" imenovan
``kernel.http_method_override``. Za več informacij, glejte
:doc:`/cookbook/routing/method_parameters`.

ide
~~~

**type**: ``string`` **default**: ``null``

Če uporabljate IDE, kot je TextMate ali Mac Vim, potem Symfony lahko vrne vse
poti datotek v sporočilu izjeme v povezavo, katera bo odprla to
datoteko v vašem IDE-ju.

Symfony vsebuje vnaprej definirane url-je za nekatere popularne IDE-je, lahko jih nastavite
z uporabo sledečih ključev:

* ``textmate``
* ``macvim``
* ``emacs``
* ``sublime``

.. versionadded:: 2.3.14
    Urejevalnika ``emacs`` in ``sublime`` sta bila predstavljena v Symfony 2.3.14.

Lahko tudi specificirate niz url-ja po meri. Če to naredite, vsi znaki za procente
(``%``) morajo biti dvojni za čiščenje tega znaka. Na primer,
če ste namestili `PhpStormOpener`_ in uporabljate PHPstorm, boste naredili nekaj takega:

.. configuration-block::

    .. code-block:: yaml
        framework:
            ide: "pstorm://%%f:%%l"

    .. code-block:: xml

        <?xml version="1.0" charset="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/service"
            xmlns:framework="http://symfony.com/schema/dic/symfony">

            <framework:config ide="pstorm://%%f:%%l" />

        </container>

    .. code-block:: php

        $container->loadFromExtension('framework', array(
            'ide' => 'pstorm://%%f:%%l',
        ));

Seveda, odkar vsak razvijalec uporablja različen IDE, je bolje nastaviti
to na sistemskem nivoju. To se lahko naredi z nastavitvijo ``xdebug.file_link_format``
v ``php.ini`` nastavitvah za niz povezave datoteke. Če ta nastavitvena vrednost ni nastavljena,
potem bo ``ide`` opcija ignorirana.

.. _reference-framework-test:

test
~~~~

**type**: ``Boolean``

Če ta nastavitveni parameter je prisoten (in ni ``false``), potem
so naložene storitve, ki se tičejo testiranju vaše aplikacije (npr. ``test.client``).
Ta nastavitev bi morala biti prisotna v vašem ``test`` okolju (običajno preko
``app/config/config_test.yml``). Za več informacij glejte :doc:`/book/testing`.

.. _reference-framework-trusted-proxies:

trusted_proxies
~~~~~~~~~~~~~~~

**type**: ``array``

Nastavi IP naslov, ki bi moral biti preverjen kot proxi-ji. Za več podrobnosti,
glejte :doc:`/components/http_foundation/trusting_proxies`.

.. versionadded:: 2.3
    Podpora CIDR notacije je bila predstavljena v Symfony 2.3, tako da lahko dodate na seznam
    varnih celotne subnet-e (npr. ``10.0.0.0/8``, ``fc00::/7``).

.. configuration-block::

    .. code-block:: yaml

        framework:
            trusted_proxies:  [192.0.0.1, 10.0.0.0/8]

    .. code-block:: xml

        <framework:config trusted-proxies="192.0.0.1, 10.0.0.0/8">
            <!-- ... -->
        </framework>

    .. code-block:: php

        $container->loadFromExtension('framework', array(
            'trusted_proxies' => array('192.0.0.1', '10.0.0.0/8'),
        ));

.. _reference-framework-form:

form
~~~~

csrf_protection
~~~~~~~~~~~~~~~

session
~~~~~~~

name
....

**type**: ``string`` **default**: ``null``

To specificira ime piškotka seje. Privzeto bo uporabljalo ime piškotka, ki je
definiran v ``php.ini`` z direktivo ``session.name``.

cookie_lifetime
...............

**type**: ``integer`` **default**: ``null``

To določa življensko dobo seje - v sekundah. Privzeto bo uporabljena ``null``,
kar pomeni, da bo uporabljena vredno ``session.cookie_lifetime`` iz ``php.ini``.
Nastavitev te vrednosti na ``0`` pomeni, da je piškotek veljaven za dolžino seje
brskalnika.

cookie_path
...........

**type**: ``string`` **default**: ``/``

To določa pot, ki je nastavljena v seji piškotka. Privzeto bo uporabil ``/``.

cookie_domain
.............

**type**: ``string`` **default**: ``''``

To določa domeno, nastavljeno v seji piškotka. Prizveto je prazno,
kar pomeni ime gostitelja strežnika, ki je generiral piškotek po
specifikaciji piškotkov.

cookie_secure
.............

**type**: ``Boolean`` **default**: ``false``

To določa, ali bi piškotki morali biti poslani samo preko varnih povezav.

cookie_httponly
...............

**type**: ``Boolean`` **default**: ``false``

To določa, ali bi morali biti piškotki dostopni samo preko HTTP protokola.
To pomeni, da piškotek ne bo dostopen za skriptne jezike, kot je JavaScript.
Ta nastavitev lahko efektivno pomaga reducirati krajo identifikacije
preko XSS napadov.

gc_probability
..............

**type**: ``integer`` **default**: ``1``

To definira verjetnost, da bo garbage collector (GC) proces zagnan
na vsaki inicializaciji seje. Verjetnost je zračunana z uporabo
``gc_probability`` / ``gc_divisor``, npr. 1/100 pomeni, da obstaja 1% verjetnost,
da se bo GC proces začel na vsakem zahtevku.

gc_divisor
..........

**type**: ``integer`` **default**: ``100``

Glejte `gc_probability`_.

gc_maxlifetime
..............

**type**: ``integer`` **default**: ``1440``

To določa število sekund, po katerih bodo podatki videni kot "garbage"
in potencialno počiščeni. "Garbage collection" se lahko zgodi med vsakim pričetkom seje
in je odvisen od `gc_divisor`_ in `gc_probability`_.

save_path
.........

**type**: ``string`` **default**: ``%kernel.cache.dir%/sessions``

To določa argument, ki bo poslan handler-ju shranjevanja. Če izberete
privzeti datotečni handler, je to pot, kjer bodo ustvarjene datoteke seje.
Za več informacij, glejte :doc:`/cookbook/session/sessions_directory`.

Lahko tudi nastavite to vrednost na ``save_path`` vaših ``php.ini`` z nastavitvijo
vrednosti na ``null``:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        framework:
            session:
                save_path: null

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <framework:config>
            <framework:session save-path="null" />
        </framework:config>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('framework', array(
            'session' => array(
                'save_path' => null,
            ),
        ));

.. _configuration-framework-serializer:

serializer
~~~~~~~~~~

.. _serializer.enabled:

enabled
.......

**type**: ``boolean`` **default**: ``false``

Ali omogočiti ``serializer`` storitev ali ne v "service container".

Za več podrobnosti, glejte :doc:`/cookbook/serializer`.

templating
~~~~~~~~~~

assets_base_urls
................

**default**: ``{ http: [], ssl: [] }``

Ta opcija vam omogoča definirati osnosne URL-je, uporabljene za sredstva, sklicana
iz ``http`` in ``ssl`` (``https``) strani. Vrednost niza je lahko ponujena na lokaciji
eno elementnega polja. Če je ponujenih več osnovnih URL-jev, bo Symfony2
izbral enega v zbirki vsakič, ko generira pot stredstva.

Za enostavnost je lahko ``assets_base_urls`` nastavljen direktno z nizom ali
poljem nizov, ki bodo avtomatsko organizirani v zbirke osnovnih URL-jev za
``http`` in ``https`` zahtevke. Če se URL začne z ``https://`` ali
je `protocol-relative`_ (to pomeni, da se začne z `//`) bo dodan k obema
zbirkama. URL-ji, ki se začnejo s ``http://`` bodo dodani samo k zbirki
``http``.

.. _ref-framework-assets-version:

assets_version
..............

**type**: ``string``

Ta opcija je uporabljena, da sprazni predpomnilnik sredstev z globalnim dodajanjem
poizvedbenega parametra vsem izpisanim potem (npr. ``images/logo?v2``). To
velja samo za sredstva izpisana preko Twig ``asset`` funkcije (ali PHP ekvivaletne)
kot tudi za sredstva izpisana s komponento Assetic.

Na primer, predstavimo, da imate sledeče:

.. configuration-block::

    .. code-block:: html+jinja

        <img src="{{ asset('images/logo.png') }}" alt="Symfony!" />

    .. code-block:: php

        <img src="<?php echo $view['assets']->getUrl('images/logo.png') ?>" alt="Symfony!" />

Privzeto bo to izpisalo pot vaše slike kot je ``/images/logo.png``.
Sedaj, aktivirajte opcijo ``assets_version``:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        framework:
            # ...
            templating: { engines: ['twig'], assets_version: v2 }

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <framework:templating assets-version="v2">
            <framework:engine id="twig" />
        </framework:templating>

    .. code-block:: php

        // app/config/config.php
        $container->loadFromExtension('framework', array(
            ...,
            'templating'      => array(
                'engines'        => array('twig'),
                'assets_version' => 'v2',
            ),
        ));

Sedaj bo enako sredstvo izpisano kot ``/images/logo.png?v2``. Če uporabite
to lastnost, **morate** ročno povečati ``assets_version`` vrednost pred
vsakim nalaganjem, da bodo parametri poizvedbe spremenjeni.

Možno je tudi nastaviti vrednost verzije na osnovi od sredstva do sredstva (namesto
uporabe globalne verzije - npr. ``v2`` - nastavljene tu). Glejte
:ref:`Verzije glede na sredstva <book-templating-version-by-asset>` za podrobnosti.

Kontrolirate lahko, kako deluje niz poizvedbe preko `assets_version_format`_
opcije.

assets_version_format
.....................

**type**: ``string`` **default**: ``%%s?%%s``

To specificira :phpfunction:`sprintf` vzorec, ki bo uporabljen z `assets_version`_
opcijo za sestavo poti sredstva. Privzeto, vzorec doda verzijo sredstva kot niz
poizvedbe. Na primer, če je ``assets_version_format`` nastavljen na
``%%s?version=%%s`` in ``assets_version`` nastavljena na ``5``, potem bo pot sredstva
``/images/logo.png?version=5``.

.. note::

    Vsi znaki za procente (``%``) v obliki niza morajo biti dvojni za čiščenje
    znakov. Brez čiščenja, so lahko vrednosti nehote interpretirane kot
    :ref:`book-service-container-parameters`.

.. tip::

    Nekaj CDN-jev ne podpira praznenja predpomnilnika preko niza poizvedbe, zato je
    injeciranje verzije v dejansko pot datoteke potrebna. K sreči ``assets_version_format``
    ni omejen na produciranje verzij nizov poizvedb.

    Vzorec prejme originalno pot sredstva in verzijo kot svoj prvi in drugi
    parameter. Ker je pot sredstva en parameter, ga lahko modificirate na mestu
    (npr. ``/images/logo-v5.png``); čeprav lahko
    dodate predpono poti sredstva z uporabo vzorca ``version-%%2$s/%%1$s``, kar
    bo imelo za rezultat v poti ``version-5/images/logo.png``.

    Pravila prepisovanj URL-jev so lahko uporabljena za neupoštevanje predpone verzije
    preden se pošlje sredstvo. Namesto tega lahko tudi kopirate sredstva v ustrezne
    poti verzij kot del vašega nalagalnega procesa in pozabite kakršnokoli URL prepisovanje.
    Ta opcija je uporabna, če bi radi, da starejše verzije sredstev ostanejo
    dostopne na njihovih originalnih URL-jih.

profiler
~~~~~~~~

.. _profiler.enabled:

enabled
.......

**default**: ``true`` v ``dev`` in ``test`` okoljih

Profiler je lahko onemogočen z nastavitvijo tega ključa na ``false``.

.. versionadded:: 2.3

    Opcija ``collect`` je bila predstavljena v Symfony 2.3. Pred tem, ko je bil ``profiler.enabled``
    false, je *bil* profiler dejansko omogočen, vendar zbirniki (collectors) so bili
    onemogočeni. Sedaj se lahko profiler in collectors kontrolira neodvisno.

collect
.......

**default**: ``true``

Ta opcija nastavlja način, kako se profiler obnaša, ko je omogočen. Če je nastavljen
na ``true``, profiler zbere podatke za vse zahtevke. Če želite samo zbrati
informacije na zahtevo, lahko nastavite ``collect`` zastavico na ``false``
in aktivirate zbiranje podatkov ročno::

    $profiler->enable();

Celotne privzete nastavitve
---------------------------

.. configuration-block::

    .. code-block:: yaml

        framework:
            secret:               ~
            http_method_override: true
            trusted_proxies:      []
            ide:                  ~
            test:                 ~
            default_locale:       en

            csrf_protection:
                enabled:              false
                field_name:           _token # Deprecated since 2.4, to be removed in 3.0. Use form.csrf_protection.field_name instead

            # form configuration
            form:
                enabled:              false
                csrf_protection:
                    enabled:          true
                    field_name:       ~

            # esi configuration
            esi:
                enabled:              false

            # fragments configuration
            fragments:
                enabled:              false
                path:                 /_fragment

            # profiler configuration
            profiler:
                enabled:              false
                collect:              true
                only_exceptions:      false
                only_master_requests: false
                dsn:                  file:%kernel.cache_dir%/profiler
                username:
                password:
                lifetime:             86400
                matcher:
                    ip:                   ~

                    # use the urldecoded format
                    path:                 ~ # Example: ^/path to resource/
                    service:              ~

            # router configuration
            router:
                resource:             ~ # Required
                type:                 ~
                http_port:            80
                https_port:           443

                # set to true to throw an exception when a parameter does not match the requirements
                # set to false to disable exceptions when a parameter does not match the requirements (and return null instead)
                # set to null to disable parameter checks against requirements
                # 'true' is the preferred configuration in development mode, while 'false' or 'null' might be preferred in production
                strict_requirements:  true

            # session configuration
            session:
                storage_id:           session.storage.native
                handler_id:           session.handler.native_file
                name:                 ~
                cookie_lifetime:      ~
                cookie_path:          ~
                cookie_domain:        ~
                cookie_secure:        ~
                cookie_httponly:      ~
                gc_divisor:           ~
                gc_probability:       ~
                gc_maxlifetime:       ~
                save_path:            %kernel.cache_dir%/sessions

            # serializer configuration
            serializer:
               enabled: false

            # templating configuration
            templating:
                assets_version:       ~
                assets_version_format:  %%s?%%s
                hinclude_default_template:  ~
                form:
                    resources:

                        # Default:
                        - FrameworkBundle:Form
                assets_base_urls:
                    http:                 []
                    ssl:                  []
                cache:                ~
                engines:              # Required

                    # Example:
                    - twig
                loaders:              []
                packages:

                    # Prototype
                    name:
                        version:              ~
                        version_format:       %%s?%%s
                        base_urls:
                            http:                 []
                            ssl:                  []

            # translator configuration
            translator:
                enabled:              false
                fallback:             en

            # validation configuration
            validation:
                enabled:              false
                cache:                ~
                enable_annotations:   false
                translation_domain:   validators

            # annotation configuration
            annotations:
                cache:                file
                file_cache_dir:       %kernel.cache_dir%/annotations
                debug:                %kernel.debug%

.. _`protocol-relative`: http://tools.ietf.org/html/rfc3986#section-4.2
.. _`PhpStormOpener`: https://github.com/pinepain/PhpStormOpener
