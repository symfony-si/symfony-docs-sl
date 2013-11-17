.. index::
   single: Doctrine; ORM configuration reference
   single: Configuration reference; Doctrine ORM

Nastavitve za Doctrine ("doctrine")
===================================

.. configuration-block::

    .. code-block:: yaml

        doctrine:
            dbal:
                default_connection:   default
                types:
                    # A collection of custom types
                    # Example
                    some_custom_type:
                        class:                Acme\HelloBundle\MyCustomType
                        commented:            true

                connections:
                    default:
                        dbname:               database

                    # A collection of different named connections (e.g. default, conn2, etc)
                    default:
                        dbname:               ~
                        host:                 localhost
                        port:                 ~
                        user:                 root
                        password:             ~
                        charset:              ~
                        path:                 ~
                        memory:               ~

                        # The unix socket to use for MySQL
                        unix_socket:          ~

                        # True to use as persistent connection for the ibm_db2 driver
                        persistent:           ~

                        # The protocol to use for the ibm_db2 driver (default to TCPIP if omitted)
                        protocol:             ~

                        # True to use dbname as service name instead of SID for Oracle
                        service:              ~

                        # The session mode to use for the oci8 driver
                        sessionMode:          ~

                        # True to use a pooled server with the oci8 driver
                        pooled:               ~

                        # Configuring MultipleActiveResultSets for the pdo_sqlsrv driver
                        MultipleActiveResultSets:  ~
                        driver:               pdo_mysql
                        platform_service:     ~
                        logging:              %kernel.debug%
                        profiling:            %kernel.debug%
                        driver_class:         ~
                        wrapper_class:        ~
                        options:
                            # an array of options
                            key:                  []
                        mapping_types:
                            # an array of mapping types
                            name:                 []
                        slaves:

                            # a collection of named slave connections (e.g. slave1, slave2)
                            slave1:
                                dbname:               ~
                                host:                 localhost
                                port:                 ~
                                user:                 root
                                password:             ~
                                charset:              ~
                                path:                 ~
                                memory:               ~

                                # The unix socket to use for MySQL
                                unix_socket:          ~

                                # True to use as persistent connection for the ibm_db2 driver
                                persistent:           ~

                                # The protocol to use for the ibm_db2 driver (default to TCPIP if omitted)
                                protocol:             ~

                                # True to use dbname as service name instead of SID for Oracle
                                service:              ~

                                # The session mode to use for the oci8 driver
                                sessionMode:          ~

                                # True to use a pooled server with the oci8 driver
                                pooled:               ~

                                # Configuring MultipleActiveResultSets for the pdo_sqlsrv driver
                                MultipleActiveResultSets:  ~

            orm:
                default_entity_manager:  ~
                auto_generate_proxy_classes:  false
                proxy_dir:            %kernel.cache_dir%/doctrine/orm/Proxies
                proxy_namespace:      Proxies
                # search for the "ResolveTargetEntityListener" class for a cookbook about this
                resolve_target_entities: []
                entity_managers:
                    # A collection of different named entity managers (e.g. some_em, another_em)
                    some_em:
                        query_cache_driver:
                            type:                 array # Required
                            host:                 ~
                            port:                 ~
                            instance_class:       ~
                            class:                ~
                        metadata_cache_driver:
                            type:                 array # Required
                            host:                 ~
                            port:                 ~
                            instance_class:       ~
                            class:                ~
                        result_cache_driver:
                            type:                 array # Required
                            host:                 ~
                            port:                 ~
                            instance_class:       ~
                            class:                ~
                        connection:           ~
                        class_metadata_factory_name:  Doctrine\ORM\Mapping\ClassMetadataFactory
                        default_repository_class:  Doctrine\ORM\EntityRepository
                        auto_mapping:         false
                        hydrators:

                            # An array of hydrator names
                            hydrator_name:                 []
                        mappings:
                            # An array of mappings, which may be a bundle name or something else
                            mapping_name:
                                mapping:              true
                                type:                 ~
                                dir:                  ~
                                alias:                ~
                                prefix:               ~
                                is_bundle:            ~
                        dql:
                            # a collection of string functions
                            string_functions:
                                # example
                                # test_string: Acme\HelloBundle\DQL\StringFunction

                            # a collection of numeric functions
                            numeric_functions:
                                # example
                                # test_numeric: Acme\HelloBundle\DQL\NumericFunction

                            # a collection of datetime functions
                            datetime_functions:
                                # example
                                # test_datetime: Acme\HelloBundle\DQL\DatetimeFunction

                        # Register SQL Filters in the entity manager
                        filters:
                            # An array of filters
                            some_filter:
                                class:                ~ # Required
                                enabled:              false

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:doctrine="http://symfony.com/schema/dic/doctrine"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/doctrine http://symfony.com/schema/dic/doctrine/doctrine-1.0.xsd">

            <doctrine:config>
                <doctrine:dbal default-connection="default">
                    <doctrine:connection
                        name="default"
                        dbname="database"
                        host="localhost"
                        port="1234"
                        user="user"
                        password="secret"
                        driver="pdo_mysql"
                        driver-class="MyNamespace\MyDriverImpl"
                        path="%kernel.data_dir%/data.sqlite"
                        memory="true"
                        unix-socket="/tmp/mysql.sock"
                        wrapper-class="MyDoctrineDbalConnectionWrapper"
                        charset="UTF8"
                        logging="%kernel.debug%"
                        platform-service="MyOwnDatabasePlatformService"
                    >
                        <doctrine:option key="foo">bar</doctrine:option>
                        <doctrine:mapping-type name="enum">string</doctrine:mapping-type>
                    </doctrine:connection>
                    <doctrine:connection name="conn1" />
                    <doctrine:type name="custom">Acme\HelloBundle\MyCustomType</doctrine:type>
                </doctrine:dbal>

                <doctrine:orm default-entity-manager="default" auto-generate-proxy-classes="false" proxy-namespace="Proxies" proxy-dir="%kernel.cache_dir%/doctrine/orm/Proxies">
                    <doctrine:entity-manager name="default" query-cache-driver="array" result-cache-driver="array" connection="conn1" class-metadata-factory-name="Doctrine\ORM\Mapping\ClassMetadataFactory">
                        <doctrine:metadata-cache-driver type="memcache" host="localhost" port="11211" instance-class="Memcache" class="Doctrine\Common\Cache\MemcacheCache" />
                        <doctrine:mapping name="AcmeHelloBundle" />
                        <doctrine:dql>
                            <doctrine:string-function name="test_string">Acme\HelloBundle\DQL\StringFunction</doctrine:string-function>
                            <doctrine:numeric-function name="test_numeric">Acme\HelloBundle\DQL\NumericFunction</doctrine:numeric-function>
                            <doctrine:datetime-function name="test_datetime">Acme\HelloBundle\DQL\DatetimeFunction</doctrine:datetime-function>
                        </doctrine:dql>
                    </doctrine:entity-manager>
                    <doctrine:entity-manager name="em2" connection="conn2" metadata-cache-driver="apc">
                        <doctrine:mapping
                            name="DoctrineExtensions"
                            type="xml"
                            dir="%kernel.root_dir%/../vendor/gedmo/doctrine-extensions/lib/DoctrineExtensions/Entity"
                            prefix="DoctrineExtensions\Entity"
                            alias="DExt"
                        />
                    </doctrine:entity-manager>
                </doctrine:orm>
            </doctrine:config>
        </container>

Pregled nastavitev
------------------

Naslednji primer nastavitev prikazuje vse privzete nastavitve, katere
ORM nastavlja:

.. code-block:: yaml

    doctrine:
        orm:
            auto_mapping: true
            # the standard distribution overrides this to be true in debug, false otherwise
            auto_generate_proxy_classes: false
            proxy_namespace: Proxies
            proxy_dir: "%kernel.cache_dir%/doctrine/orm/Proxies"
            default_entity_manager: default
            metadata_cache_driver: array
            query_cache_driver: array
            result_cache_driver: array

Na voljo je tudi veliko ostalih nastavitvenih opcij, ki jih lahko uporabite za
prepis določenih razredov, vendar te so samo za zelo napredne primere uporab.

Predpomnenje gonilnikov
~~~~~~~~~~~~~~~~~~~~~~~

Za predpomnenje gonilnikov lahko specificirate vrednosti "array", "apc", "memcache", "memcached"
"xcache" ali "service".

Sledeči primer kaže pregled nastavitev predpomnenja:

.. code-block:: yaml

    doctrine:
        orm:
            auto_mapping: true
            metadata_cache_driver: apc
            query_cache_driver:
                type: service
                id: my_doctrine_common_cache_service
            result_cache_driver:
                type: memcache
                host: localhost
                port: 11211
                instance_class: Memcache

Nastavitve preslikav
~~~~~~~~~~~~~~~~~~~~

Eksplicitne definicije vseh preslikanih entitet je edina potrebna
nastavitev za ORM in na voljo je kar nekaj nastavitvenih opcij, ki jih
lahko kontrolirate. Sledeče nastavitvene opcije obstajajo za preslikave:

* ``type`` Ena izmed ``annotation``, ``xml``, ``yml``, ``php`` ali ``staticphp``.
  To specificira, kateri tip meta podatkov vaša preslikava uporablja.

* ``dir`` Pot do preslikave ali datotek entitet (odvisno od gonilnika). Če
  je ta pot relativna, se predpostavlja, da je relativna glede na vrh paketa.
  To deluje samo, če je ime vaše preslikave ime paketa. Če želite uporabiti
  to opcijo za specifikacijo absolutnih poti, bi morali dodati poti predpono
  s parametri jedra, ki obstaja v DIC (Dependency Injection Container), npr.
  %kernel.root_dir%.

* ``prefix`` Pogosti imenski prostor, ki ga vse entitete te preslikave delijo.
  Ta predpona ne bi smela nikoli biti v konfliktu s predponami drugih definiranih
  preslikah, drugače nekaterih vaših entitet ni mogoče najti s strani Doctrine. Ta
  opcija je privzeto imenski prostor paketa + ``Entity``, na primer za
  aplikacijski paket imenovan ``AcmeHelloBundle`` bi bila predpona
  ``Acme\HelloBundle\Entity``.

* ``alias`` Doctrine ponuja način za izdelavo aliasa imenskih prostorov entitet v
  enostavnejša, krajša imena uporabljena v DQL poizvedbah ali za dostop do Repository
  razredov. Ko uporabljate paket je alias privzeto ime paketa.

* ``is_bundle`` Ta opcija izhaja iz vrednosti ``dir`` in privzeto je
  nastavljena na true, če je dir relativno izkazan s strani ``file_exists()`` preverjanja,
  ki vrne false. Je false, če preverjanje obstoja vrne true. V tem primeru je
  bila specificirana absolutna pot in datoteke meta podatkov so najverjetneje v
  direktoriju izven paketa.

.. index::
    single: Configuration; Doctrine DBAL
    single: Doctrine; DBAL configuration

.. _`reference-dbal-configuration`:

Nastavitve Doctrine DBAL
-------------------------

DoctrineBundle podpira vse parametre, ki jih privzeti Doctrine gonilniki
sprejemajo, pretvorjene v XML ali YAML imenske standarde, ki jih Symfony
uveljavlja. Glejte Doctrine `DBAL dokumentacijo`_ za več informacij.
Sledeči blok kaže vse možne nastavitvene ključe:

.. configuration-block::

    .. code-block:: yaml

        doctrine:
            dbal:
                dbname:               database
                host:                 localhost
                port:                 1234
                user:                 user
                password:             secret
                driver:               pdo_mysql
                # the DBAL driverClass option
                driver_class:         MyNamespace\MyDriverImpl
                # the DBAL driverOptions option
                options:
                    foo: bar
                path:                 "%kernel.data_dir%/data.sqlite"
                memory:               true
                unix_socket:          /tmp/mysql.sock
                # the DBAL wrapperClass option
                wrapper_class:        MyDoctrineDbalConnectionWrapper
                charset:              UTF8
                logging:              "%kernel.debug%"
                platform_service:     MyOwnDatabasePlatformService
                mapping_types:
                    enum: string
                types:
                    custom: Acme\HelloBundle\MyCustomType
                # the DBAL keepSlave option
                keep_slave:           false

    .. code-block:: xml

        <!-- xmlns:doctrine="http://symfony.com/schema/dic/doctrine" -->
        <!-- xsi:schemaLocation="http://symfony.com/schema/dic/doctrine http://symfony.com/schema/dic/doctrine/doctrine-1.0.xsd"> -->

        <doctrine:config>
            <doctrine:dbal
                name="default"
                dbname="database"
                host="localhost"
                port="1234"
                user="user"
                password="secret"
                driver="pdo_mysql"
                driver-class="MyNamespace\MyDriverImpl"
                path="%kernel.data_dir%/data.sqlite"
                memory="true"
                unix-socket="/tmp/mysql.sock"
                wrapper-class="MyDoctrineDbalConnectionWrapper"
                charset="UTF8"
                logging="%kernel.debug%"
                platform-service="MyOwnDatabasePlatformService"
            >
                <doctrine:option key="foo">bar</doctrine:option>
                <doctrine:mapping-type name="enum">string</doctrine:mapping-type>
                <doctrine:type name="custom">Acme\HelloBundle\MyCustomType</doctrine:type>
            </doctrine:dbal>
        </doctrine:config>

Če želite nastaviti več povezav v YAML, jih dajte pod ključ
``connections`` in jim dajte unikatno ime:

.. code-block:: yaml

    doctrine:
        dbal:
            default_connection:       default
            connections:
                default:
                    dbname:           Symfony2
                    user:             root
                    password:         null
                    host:             localhost
                customer:
                    dbname:           customer
                    user:             root
                    password:         null
                    host:             localhost

Storitev ``database_connection`` se vedno sklicuje na *privzeto* povezavo,
ki je prva definirana ali tista nastavljena preko
``default_connection`` parametera.

Vsaka povezava je tudi dostopna preko ``doctrine.dbal.[name]_connection``
storitve, kjer ``[name]`` je ime povezave.

.. _DBAL dokumentacijo: http://docs.doctrine-project.org/projects/doctrine-dbal/en/latest/reference/configuration.html
