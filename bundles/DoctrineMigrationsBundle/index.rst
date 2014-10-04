DoctrineMigrationsBundle
========================

Lastnost migracije podatkovne baze je razširitev nivoja abstrakcije podatkovne
baze in vam ponuja možnost programsko naložiti nove verzije
sheme vaše podatkovne baze na varen, enostaven in standardiziran način.

.. tip::

    Več o migracijah podatkovnih baz Doctrine lahko preberete v projektni
    `dokumentaciji`_.

Namestitev
----------

Migracije Doctrine za Symfony so vzdrževane v `DoctrineMigrationsBundle`_.
Paket uporablja zunanjo knjižnico `Doctrine Database Migrations`_.

Sledite tem korakom, da namestite paket in knjižnico v Symfony
standardno izdajo. Dodajte sledeče v vašo datoteko ``composer.json``:

.. code-block:: json

    {
        "require": {
            "doctrine/migrations": "1.0.*@dev",
            "doctrine/doctrine-migrations-bundle": "2.1.*@dev"
        }
    }

Posodobite knjižnice vendor:

.. code-block:: bash

    $ php composer.phar update

Če je vse delovalo, je ``DoctrineMigrationsBundle`` sedaj na voljo
v ``vendor/doctrine/doctrine-migrations-bundle``.

.. note::

    ``DoctrineMigrationsBundle`` installs
    `Doctrine Database Migrations`_ library. The library can be found
    at ``vendor/doctrine/migrations``.

Na koncu se prepričajte, da ste omogočili paket v ``AppKernel.php`` z vključitvijo
sledečega:

.. code-block:: php

    // app/AppKernel.php
    public function registerBundles()
    {
        $bundles = array(
            //...
            new Doctrine\Bundle\MigrationsBundle\DoctrineMigrationsBundle(),
        );
    }

Nastavitve
----------

Nastavite lahko pot, imenski prostor, ime tabele in ime v vaši ``config.yml``. Primeri spodaj so privzete vrednosti.

.. code-block:: yaml

    // app/config/config.yml
    doctrine_migrations:
        dir_name: %kernel.root_dir%/DoctrineMigrations
        namespace: Application\Migrations
        table_name: migration_versions
        name: Application Migrations

Uporaba
-------

Vsa funkcionalnost migracij je vsebovana v nekaj konzolnih ukazih:

.. code-block:: bash

    doctrine:migrations
      :diff     Generate a migration by comparing your current database to your mapping information.
      :execute  Execute a single migration version up or down manually.
      :generate Generate a blank migration class.
      :migrate  Execute a migration to a specified version or the latest available version.
      :status   View the status of a set of migrations.
      :version  Manually add and delete migration versions from the version table.

Začnite s pridobitvijo statusa migracij v vaši aplikaciji s pogonom
ukaza ``status``:

.. code-block:: bash

    php app/console doctrine:migrations:status

     == Configuration

        >> Name:                                               Application Migrations
        >> Configuration Source:                               manually configured
        >> Version Table Name:                                 migration_versions
        >> Migrations Namespace:                               Application\Migrations
        >> Migrations Directory:                               /path/to/project/app/DoctrineMigrations
        >> Current Version:                                    0
        >> Latest Version:                                     0
        >> Executed Migrations:                                0
        >> Available Migrations:                               0
        >> New Migrations:                                     0

Sedaj lahko začnete delati z migracijami z generiranjem novega praznega migracijskega
razreda. Kasneje se boste naučili, kako lahko Doctrine generira migracije avtomatično
za vas.

.. code-block:: bash

    php app/console doctrine:migrations:generate
    Generated new migration class to "/path/to/project/app/DoctrineMigrations/Version20100621140655.php"

Poglejte novo generirani migracijski razred in videli boste nekaj,
kot je sledeče::

    namespace Application\Migrations;

    use Doctrine\DBAL\Migrations\AbstractMigration,
        Doctrine\DBAL\Schema\Schema;

    class Version20100621140655 extends AbstractMigration
    {
        public function up(Schema $schema)
        {

        }

        public function down(Schema $schema)
        {

        }
    }

Če poženete ukaz ``status`` bo sedaj pokazal, da imate eno novo
migracijo za izvršiti:

.. code-block:: bash

    php app/console doctrine:migrations:status --show-versions

     == Configuration

       >> Name:                                               Application Migrations
       >> Configuration Source:                               manually configured
       >> Version Table Name:                                 migration_versions
       >> Migrations Namespace:                               Application\Migrations
       >> Migrations Directory:                               /path/to/project/app/DoctrineMigrations
       >> Current Version:                                    0
       >> Latest Version:                                     2010-06-21 14:06:55 (20100621140655)
       >> Executed Migrations:                                0
       >> Available Migrations:                               1
       >> New Migrations:                                     1

    == Migration Versions

       >> 2010-06-21 14:06:55 (20100621140655)                not migrated

Sedaj lahko dodate nekaj kode migracije k metodam ``up()`` in ``down()`` ter
končno migrirate, ko ste pripravljeni:

.. code-block:: bash

    php app/console doctrine:migrations:migrate 20100621140655

Za več informacij, kako pisati same migracije (t.j. kako
zapolniti metodi ``up()`` in ``down()``), glejte uradno
`dokumentacijo`_ Doctrine migracije.

Poganjanje migracij med razvojem
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Seveda končni cilj pisanja migracij je, biti jih sposoben uporabiti, da
zanesljivo posodobijo strukturo vaše podatkovne baze, ko nalagate vašo aplikacijo.
S pogonom migracij lokalno (ali na beta strežniku), lahko zagotovite, da
migracije delujejo, kot pričakujete.

Ko končno naložite vašo aplikacijo, si morate samo zapomniti pognati
ukaz ``doctrine:migrations:migrate``. Interno, Doctrine izdela
tabelo ``migration_versions`` znotraj vaše podatkovne baze in beleži katere migracije
so bile tam izvršene. Torej ne glede na to, koliko migracij ste ustvarili
in izvršili lokalno, ko poženete ukaz med razvojem, bo Doctrine
točno vedel, katere migracije še niso bile pognane s pogledom v tabelo
``migration_versions`` vaše produkcijske baze. Ne glede na to, na katerem strežniku ste,
lahko vedno varno poženete ta ukaz, da izvršite samo migracije, ki še niso bile
pognane na *tisti* določeni podatkovni bazi.

Avtomatično generiranje migracij
--------------------------------

V realnosti bi morali redko potrebovati pisati migracije ročno, saj knjižnica
migracij lahko generira razrede migracij avtomatično s primerjanjem vaših informacij Doctrine
preslikav (t.j. kako bi vaša podatkovna baza *morala* izgledati) z vašo
dejansko trenutno strukturo podatke baze.

Na primer, predpostavimo, da ste ustvarili novo entiteto ``User`` in dodali informacije preslikav
za Doctrine-ov ORM:

.. configuration-block::

    .. code-block:: php-annotations

        // src/Acme/HelloBundle/Entity/User.php
        namespace Acme\HelloBundle\Entity;

        use Doctrine\ORM\Mapping as ORM;

        /**
         * @ORM\Entity
         * @ORM\Table(name="hello_user")
         */
        class User
        {
            /**
             * @ORM\Id
             * @ORM\Column(type="integer")
             * @ORM\GeneratedValue(strategy="AUTO")
             */
            protected $id;

            /**
             * @ORM\Column(type="string", length="255")
             */
            protected $name;
        }

    .. code-block:: yaml

        # src/Acme/HelloBundle/Resources/config/doctrine/User.orm.yml
        Acme\HelloBundle\Entity\User:
            type: entity
            table: hello_user
            id:
                id:
                    type: integer
                    generator:
                        strategy: AUTO
            fields:
                name:
                    type: string
                    length: 255

    .. code-block:: xml

        <!-- src/Acme/HelloBundle/Resources/config/doctrine/User.orm.xml -->
        <doctrine-mapping xmlns="http://doctrine-project.org/schemas/orm/doctrine-mapping"
              xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
              xsi:schemaLocation="http://doctrine-project.org/schemas/orm/doctrine-mapping
                            http://doctrine-project.org/schemas/orm/doctrine-mapping.xsd">

            <entity name="Acme\HelloBundle\Entity\User" table="hello_user">
                <id name="id" type="integer" column="id">
                    <generator strategy="AUTO"/>
                </id>
                <field name="name" column="name" type="string" length="255" />
            </entity>

        </doctrine-mapping>

S temi informacijami, Doctrine je sedaj pripravljen, da vam pomaga pridobiti vaš novi
objekt ``User`` v in iz tabele ``hello_user``. Seveda ta tabela
še ne obstaja! Generirajte novo migracijo za to tabelo avtomatično s
pogonom sledečega ukaza:

.. code-block:: bash

    php app/console doctrine:migrations:diff

Sedaj bi morali videti sporočilo, da je bil generiran razred nove migracije na osnovi
razlik sheme. Če odprete to datoteko, boste ugotovili, da ima
kodo SQL, ki je potrebna za ustvariti tabelo ``hello_user``. Naslednje poženite migracijo,
da dodate tabelo vaši podatkovni bazi:

.. code-block:: bash

    php app/console doctrine:migrations:migrate

Morala te zgodbe je: po vsaki spremembi, ki jo naredite vašim informacijam
Doctrine preslikav, poženite ukaz ``doctrine:migrations:diff``, da avtomatično
generirate vaše razrede migracij.

Če to delate od samega začetka vašega projekta (t.j. da celo
ko so naložene prve tabele preko migracijskega razreda), boste vedno sposobni
ustvariti svežo podatkovno bazo in pognati vaše migracije, da dobite shemo
vaše podatkovne baze v celoti posodobljeno. V bistvu je to enostaven in odvisen potek dela
za vaš projekt.

Migracije, ki se zavedajo kontejnerja
-------------------------------------

V nekaterih primerih boste morda potrebovali dostop do kontejnerja, da zagovotite ustrezno posodobitev
strukture vaše podatkovne baze. To je lahko potrebno za posodobitev relacij z nekatero določeno
logiko ali ustvariti nove entitete.

Zato lahko samo implementirate ContainerAwareInterface z njegovimi potrebnimi metodami,
da dobite celotni dostop do kontejnerja.

.. code-block:: php

    // ...
    use Symfony\Component\DependencyInjection\ContainerAwareInterface;
    use Symfony\Component\DependencyInjection\ContainerInterface;

    class Version20130326212938 extends AbstractMigration implements ContainerAwareInterface
    {

        private $container;

        public function setContainer(ContainerInterface $container = null)
        {
            $this->container = $container;
        }

        public function up(Schema $schema)
        {
            // ... migration content
        }

        public function postUp(Schema $schema)
        {
            $em = $this->container->get('doctrine.orm.entity_manager');
            // ... update the entities
        }
    }

Ročne tabele
------------

Pogosti primer uporabe je, da kot dodatek k strukturi vaše generirane podatkovne baze
na osnovi vaših entitet doctrine, lahko potrebujete prilagoditi tabele. Privzeto bodo take
tabele odstranjene z ukazom doctrine:migrations:diff.

Če sledite določeni shemi, lahko nastavite doctrine/dbal, da ignorira te
tabele. Predpostavimo, da bodo vse tabele po meri imele predpono ``t_``. V tem primeru
morate dodati samo naslednjo nastavitveno opcijo v vaše nastavitve doctrine:

.. configuration-block::

    .. code-block:: yaml

        doctrine:
            dbal:
                schema_filter: ~^(?!t_)~

    .. code-block:: xml

        <doctrine:dbal schema-filter="~^(?!t_)~" ... />


    .. code-block:: php

        $container->loadFromExtension('doctrine', array(
            'dbal' => array(
                'schema_filter'  => '~^(?!t_)~',
                // ...
            ),
            // ...
        ));

To ignorira tabele na nivoju DBAL in bodo ignorirane s strani ukaza diff.

Bodite pozorni, da če imate nastavljenih več povezav, potem bodo nastavitve ``schema_filter``
potrebne za postaviti na povezavo.

.. _dokumentacijo: http://docs.doctrine-project.org/projects/doctrine-migrations/en/latest/index.html
.. _dokumentaciji: http://docs.doctrine-project.org/projects/doctrine-migrations/en/latest/index.html
.. _DoctrineMigrationsBundle: https://github.com/doctrine/DoctrineMigrationsBundle
.. _`Doctrine Database Migrations`: https://github.com/doctrine/migrations
