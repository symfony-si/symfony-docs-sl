Nastavitve DoctrineMongoDBBundle
================================

Primer nastavitev
-----------------

.. code-block:: yaml

    # app/config/config.yml
    doctrine_mongodb:
        connections:
            default:
                server: mongodb://localhost:27017
                options: {}
        default_database: hello_%kernel.environment%
        document_managers:
            default:
                mappings:
                    AcmeDemoBundle: ~
                filters:
                    filter-name:
                        class: Class\Example\Filter\ODM\ExampleFilter
                        enabled: true
                metadata_cache_driver: array # array, apc, xcache, memcache

.. tip::

    Če vsako okolje zahteva različno MongoDB povezavo URI, jo lahko
    definirate v ločenem parametru in se nanjo sklicujete v nastavitvah paketa:

    .. code-block:: yaml

        # app/config/parameters.yml
        mongodb_server: mongodb://localhost:27017

    .. code-block:: yaml

        # app/config/config.yml
        doctrine_mongodb:
            connections:
                default:
                    server: %mongodb_server%

Če želite uporabiti memcache za predpomnenje vaših metapodatkov, morate nastaviti
instanco ``Memcache``; na primer, lahko naredite sledeče:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        doctrine_mongodb:
            default_database: hello_%kernel.environment%
            connections:
                default:
                    server: mongodb://localhost:27017
                    options: {}
            document_managers:
                default:
                    mappings:
                        AcmeDemoBundle: ~
                    metadata_cache_driver:
                        type: memcache
                        class: Doctrine\Common\Cache\MemcacheCache
                        host: localhost
                        port: 11211
                        instance_class: Memcache

    .. code-block:: xml

        <?xml version="1.0" ?>

        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:doctrine_mongodb="http://symfony.com/schema/dic/doctrine/odm/mongodb"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/doctrine/odm/mongodb http://symfony.com/schema/dic/doctrine/odm/mongodb/mongodb-1.0.xsd">

            <doctrine_mongodb:config default-database="hello_%kernel.environment%">
                <doctrine_mongodb:document-manager id="default">
                    <doctrine_mongodb:mapping name="AcmeDemoBundle" />
                    <doctrine_mongodb:metadata-cache-driver type="memcache">
                        <doctrine_mongodb:class>Doctrine\Common\Cache\MemcacheCache</doctrine_mongodb:class>
                        <doctrine_mongodb:host>localhost</doctrine_mongodb:host>
                        <doctrine_mongodb:port>11211</doctrine_mongodb:port>
                        <doctrine_mongodb:instance-class>Memcache</doctrine_mongodb:instance-class>
                    </doctrine_mongodb:metadata-cache-driver>
                </doctrine_mongodb:document-manager>
                <doctrine_mongodb:connection id="default" server="mongodb://localhost:27017">
                    <doctrine_mongodb:options>
                    </doctrine_mongodb:options>
                </doctrine_mongodb:connection>
            </doctrine_mongodb:config>
        </container>


Nastavitve preslikave
~~~~~~~~~~~~~~~~~~~~~

Eksplicitna definicija vseh preslikanih dokumentov je edina potrebna
nastavitev za ODM in na voljo je nekaj nastavitvenih opcij, ki jih
lahko kontrolirate. Sledeče nastavitvene opcije obstajajo za preslikavo:

- ``type`` Ena izmed ``annotation``, ``xml``, ``yml``, ``php`` ali ``staticphp``.
  Ta specificira, kateri tip tipa meta podatkov vaša preslikava uporablja.

- ``dir`` Pot do preslikave ali datotek entitet (odvisno od gonilnika). Če
  je ta pot relativna, se predpostavlja, da je relativna glede na vrh paketa. To
  deluje samo, če je ime vaše preslikave ime paketa. Če želite uporabiti
  to opcijo za določanje absolutnih poti, bi morali dodati poti predpono s
  parametri jedra, ki obstaja v DIC (na primer %kernel.root.dir%).

- ``prefix`` Pogosti imenski prostor, ki si ga vsi dokumenti te preslikave
  delijo. Ta predpona ne bi nikoli smela biti v konfliktu s predponami drugih definiranih
  preslikav drugače Doctrine ne more najti nekaterih vaših dokumentov. Ta
  opcija je privzeto imenski prostora paketa + ``Document``, na primer
  paket aplikacije imenovan ``AcmeHelloBundle``, bi imel predpono
  ``Acme\HelloBundle\Document``.

- ``alias`` Doctrine ponuja način za dodajanje vzdevkov (alias-ov) imenskim prostorom dokumentov za enostavnejša
  krajša imena, ki so uporabljena v poizvedbah ali za dostop Repozitorija.

- ``is_bundle`` Ta opcija je pridobljena vrednost iz ``dir`` in je privzeto
  nastavljena na true, če je dir relativen, dokazano s preverjanjem ``file_exists()``, ki
  vrne false. False je, če je obstoj preverjanja vrne true. V tem primeru
  je bila določena absolutna pot in meta podatki so zelo verjetno v
  direktoriju izven paketa.

Da se izognete potrebi po nastavljanju veliko informacij za vaše preslikave bi morali
slediti tem konvencijam:

1. Dajte vse vaše dokumente v direktorij ``Document/`` znotraj vašega paketa. Na
   primer ``Acme/HelloBundle/Document/``.

2. Če uproabljate xml, yml, ali php preslikavo dajte vse vaše nastavitvene datoteke
   v direktorij ``Resources/config/doctrine/``, ki ima
   predpono mongodb.xml, mongodb.yml ali mongodb.php.

3. Anotacije so predpostavljene, če je ``Document/`` vendar ni najdenega nobenega
   direktorija ``Resources/config/doctrine/``.

Sledeče nastavitve prikazujejo veliko primerov preslikav:

.. code-block:: yaml

    doctrine_mongodb:
        document_managers:
            default:
                mappings:
                    MyBundle1: ~
                    MyBundle2: yml
                    MyBundle3: { type: annotation, dir: Documents/ }
                    MyBundle4: { type: xml, dir: Resources/config/doctrine/mapping }
                    MyBundle5:
                        type: yml
                        dir: my-bundle-mappings-dir
                        alias: BundleAlias
                    doctrine_extensions:
                        type: xml
                        dir: %kernel.root_dir%/../src/vendor/DoctrineExtensions/lib/DoctrineExtensions/Documents
                        prefix: DoctrineExtensions\Documents\
                        alias: DExt

Filtri
~~~~~~

Razredi filtrov so lahko uproabljeni, da se doda kriterij k ODM poizvedbam, ne glede,
kje so te poizvedbe ustvarjene znotraj vaše aplikacije. Običajno se bodo filtri
omejili na operiranje določenih razredov ali vmesnikov. Filtri
lahko vzamejo parametre, ki so lahko uporabljeni za prilagoditev kriterija injicirane
poizvedbe.

Filtri so lahko registrirani z upravljalnikom dokumentov z uporabo sledeče sintakse:

.. configuration-block::

    .. code-block:: yaml

        doctrine_mongodb:
            document_managers:
                default:
                    filters:
                        basic_filter:
                            class: Vendor\Filter\BasicFilter
                            enabled: true
                        complex_filter:
                            class: Vendor\Filter\ComplexFilter
                            enabled: false
                            parameters:
                                author: bob
                                comments: { $gte: 10 }
                                tags: { $in: [ 'foo', 'bar' ] }

    .. code-block:: xml

        <?xml version="1.0" ?>

        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:doctrine="http://symfony.com/schema/dic/doctrine/odm/mongodb"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/doctrine/odm/mongodb http://symfony.com/schema/dic/doctrine/odm/mongodb/mongodb-1.0.xsd">

            <doctrine:mongodb>
                <doctrine:connection id="default" server="mongodb://localhost:27017" />

                <doctrine:document-manager id="default" connection="default">
                    <doctrine:filter name="basic_filter" enabled="true" class="Vendor\Filter\BasicFilter" />
                    <doctrine:filter name="complex_filter" enabled="true" class="Vendor\Filter\ComplexFilter">
                        <doctrine:parameter name="author">bob</doctrine:parameter>
                        <doctrine:parameter name="comments">{ "$gte": 10 }</doctrine:parameter>
                        <doctrine:parameter name="tags">{ "$in": [ "foo", "bar" ] }</doctrine:parameter>
                    </doctrine:filter>
                </doctrine:document-manager>
            </doctrine:mongodb>
        </container>

.. note::

    Z razliko od ORM so parametri poizvedbe v MongoDB ODM lahko neskalarne vrednosti. Ker
    so take vrednosti težke za izražanje v XML, paket omogoča nize JSON,
    da so uporabljeni v znački ``parameter``. Med procesiranjem nastavitev
    bo paket pognal vsebino značke preko ``json_decode()``, če je niz
    ovit v oglate oklepaje ali zavite oklepaje za polja in
    objekte.

Več povezav
~~~~~~~~~~~

Če potrebujete več povezav in upravljalnikov dokumenta, lahko uporabite
sledečo sintakso:

.. configuration-block::

    .. code-block:: yaml

        doctrine_mongodb:
            default_database: hello_%kernel.environment%
            default_connection: conn2
            default_document_manager: dm2
            metadata_cache_driver: apc
            connections:
                conn1:
                    server: mongodb://localhost:27017
                conn2:
                    server: mongodb://localhost:27017
            document_managers:
                dm1:
                    connection: conn1
                    metadata_cache_driver: xcache
                    mappings:
                        AcmeDemoBundle: ~
                dm2:
                    connection: conn2
                    mappings:
                        AcmeHelloBundle: ~

    .. code-block:: xml

        <?xml version="1.0" ?>

        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:doctrine_mongodb="http://symfony.com/schema/dic/doctrine/odm/mongodb"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/doctrine/odm/mongodb http://symfony.com/schema/dic/doctrine/odm/mongodb/mongodb-1.0.xsd">

            <doctrine_mongodb:config
                    default-database="hello_%kernel.environment%"
                    default-document-manager="dm2"
                    default-connection="dm2"
                    proxy-namespace="MongoDBODMProxies"
                    auto-generate-proxy-classes="true">
                <doctrine_mongodb:connection id="conn1" server="mongodb://localhost:27017">
                    <doctrine_mongodb:options>
                    </doctrine_mongodb:options>
                </doctrine_mongodb:connection>
                <doctrine_mongodb:connection id="conn2" server="mongodb://localhost:27017">
                    <doctrine_mongodb:options>
                    </doctrine_mongodb:options>
                </doctrine_mongodb:connection>
                <doctrine_mongodb:document-manager id="dm1" metadata-cache-driver="xcache" connection="conn1">
                    <doctrine_mongodb:mapping name="AcmeDemoBundle" />
                </doctrine_mongodb:document-manager>
                <doctrine_mongodb:document-manager id="dm2" connection="conn2">
                    <doctrine_mongodb:mapping name="AcmeHelloBundle" />
                </doctrine_mongodb:document-manager>
            </doctrine_mongodb:config>
        </container>

Sedaj lahko pridobite nastavitvene storitve povezave::

    $conn1 = $container->get('doctrine_mongodb.odm.conn1_connection');
    $conn2 = $container->get('doctrine_mongodb.odm.conn2_connection');

In dobite lahko tudi storitev nastavljenega upravljalnika dokumenta, ki uporablja zgornjo
storitev povezave::

    $dm1 = $container->get('doctrine_mongodb.odm.dm1_document_manager');
    $dm2 = $container->get('doctrine_mongodb.odm.dm2_document_manager');

Povezovanje na prostor strežnikov mongodb na povezavi 1
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Možno se je povezati na nekaj mongodb strežnikov na eni povezavi, če
uporabljate repliko nastavljeno z izpisanim seznamom vseh strežnikov znotraj niza
povezave, kot seznam ločen z vejicami.

.. configuration-block::

    .. code-block:: yaml

        doctrine_mongodb:
            # ...
            connections:
                default:
                    server: 'mongodb://mongodb-01:27017,mongodb-02:27017,mongodb-03:27017'

Kjer so mongodb-01, mongodb-02 in mongodb-03 imena gostiteljev naprave. Lahko
uporabite tudi IP naslov, če to želite.

Ponovno poskušanje povezovanja in poizvedb
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Doctrine MongoDB podpira avtomatično ponovno poskušanje povezovanja in poizvedb, ko
naleti na izjemo, kar je v pomoč v situacijah kot so
replike nastavitev preklopov. To olajša veliko potreb po ujetju izjem iz
MongoDB PHP gonilnika v vaši aplikaciji in ročno ponovno poskuša operacije.

Lahko določite tudi število ponovitev povezovanja in poizvedb preko
opcije ``retry_connect`` in ``retry_query`` v nastavitvah upravljalnika dokumenta.
Te opcije so privzeto nič, kar pomeni, da ne bo pridobljena nobena operacija.

Celotne privzete nastavitve
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. configuration-block::

    .. code-block:: yaml

        doctrine_mongodb:
            document_managers:

                # Prototype
                id:
                    connection:           ~
                    database:             ~
                    logging:              true
                    auto_mapping:         false
                    retry_connect:        0
                    retry_query:          0
                    metadata_cache_driver:
                        type:                 ~
                        class:                ~
                        host:                 ~
                        port:                 ~
                        instance_class:       ~
                    mappings:

                        # Prototype
                        name:
                            mapping:              true
                            type:                 ~
                            dir:                  ~
                            prefix:               ~
                            alias:                ~
                            is_bundle:            ~
            connections:

                # Prototype
                id:
                    server:               ~
                    options:
                        connect:              ~
                        persist:              ~
                        timeout:              ~
                        replicaSet:           ~
                        username:             ~
                        password:             ~
                        db:                   ~
            proxy_namespace:      MongoDBODMProxies
            proxy_dir:            %kernel.cache_dir%/doctrine/odm/mongodb/Proxies
            auto_generate_proxy_classes:  false
            hydrator_namespace:   Hydrators
            hydrator_dir:         %kernel.cache_dir%/doctrine/odm/mongodb/Hydrators
            auto_generate_hydrator_classes:  false
            default_document_manager:  ~
            default_connection:   ~
            default_database:     default
