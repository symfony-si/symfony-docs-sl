DoctrineFixturesBundle
======================

Fiksni podatki (t.i. fixtures) so uporabljeni za nalaganje krmiljenega skupka podatkov v podatkovno bazo. Ti podatki
so lahko uporabljeni za testiranje ali so lahko začetni podatki zahtevani, da
aplikacija tekoče deluje. Symfony2 nima vgrajenega načina za upravljanje fiksnih podatkov,
vendar Doctrine2 ima knjižnico, ki vam pomaga pisati fiksne podatke za Doctrine
:doc:`ORM</book/doctrine>` ali :doc:`ODM</bundles/DoctrineMongoDBBundle/index>`.

Nastavitve in konfiguracija
---------------------------

Doctrine fiksni podatki za Symfony so vzdrževani v `DoctrineFixturesBundle`_.
Ta paket uporablja zunanjo knjižnico `Doctrine Data Fixtures`_.

Sledite tem korakom za namestitev paketa in knjižnice v Symfony
standardno izdajo. Dodajte sledeče v vašo datoteko ``composer.json``:

.. code-block:: json

    {
        "require": {
            "doctrine/doctrine-fixtures-bundle": "2.2.*"
        }
    }

Posodobite knjižnice vendor:

.. code-block:: bash

    $ php composer.phar update doctrine/doctrine-fixtures-bundle

Če je vse delovalo v redu, je lahko sedaj ``DoctrineFixturesBundle`` najden
v ``vendor/doctrine/doctrine-fixtures-bundle``.

.. note::

    ``DoctrineFixturesBundle`` namesti
    knjižnico `Doctrine Data Fixtures`_. Knjižnico je moč najti
    v ``vendor/doctrine/data-fixtures``.

Na koncu registrirajte paket ``DoctrineFixturesBundle`` v ``app/AppKernel.php``.

.. code-block:: php

    // ...
    public function registerBundles()
    {
        $bundles = array(
            // ...
            new Doctrine\Bundle\FixturesBundle\DoctrineFixturesBundle(),
            // ...
        );
        // ...
    }

Pisanje enostavnih fiksnih podatkov
-----------------------------------

Doctrine2 fiksni podatki so razredi PHP, kjer lahko ustvarite objekte in jih podate
v podatkovno bazo. Kot vsi razredi v Symfony2 bi morali fiksni podatki obstojati znotraj
enega izmed vaših paketov aplikacije.

Za paket lociran v ``src/Acme/HelloBundle`` bi se morali razredi fiksnih podatkov
nahajati znotraj ``src/Acme/HelloBundle/DataFixtures/ORM`` ali
``src/Acme/HelloBundle/DataFixtures/MongoDB`` za ORM in ODM.
Ta vodič predpostavlja, da uporabljate ORM - vendar fiksni podatki so lahko dodani
enako enostavno, če uporabljate ODM.

Predstavljajte si, da imate razred ``User`` in bi želeli naložiti eno entiteto
``User``:

.. code-block:: php

    // src/Acme/HelloBundle/DataFixtures/ORM/LoadUserData.php

    namespace Acme\HelloBundle\DataFixtures\ORM;

    use Doctrine\Common\DataFixtures\FixtureInterface;
    use Doctrine\Common\Persistence\ObjectManager;
    use Acme\HelloBundle\Entity\User;

    class LoadUserData implements FixtureInterface
    {
        /**
         * {@inheritDoc}
         */
        public function load(ObjectManager $manager)
        {
            $userAdmin = new User();
            $userAdmin->setUsername('admin');
            $userAdmin->setPassword('test');

            $manager->persist($userAdmin);
            $manager->flush();
        }
    }

V Doctrine2 so fiksni podatki samo objekti, kjer naložite podatke z interakcijo
z vašimi entitetami kot to običajno naredite. To vam omogoča, da ustvarite točne
fiksne podatke, ki jih potrebujete za vašo aplikacijo.

Najresnejša omejitev je, da ne morete deliti objektov med fiksnimi podatki.
Kasneje boste videli, kako to omejitev premagati.

Izvrševanje fiksnih podatkov
----------------------------

Ko so enkrat fiksni podatki bili napisani, jih lahko naložite preko ukazne
vrstice z uporabo ukaza ``doctrine:fixtures:load``:

.. code-block:: bash

    php app/console doctrine:fixtures:load

Če uporabljate ODM, uporabite namesto tega ukaz ``doctrine:mongodb:fixtures:load``:

.. code-block:: bash

    php app/console doctrine:mongodb:fixtures:load

Opravilo bo pogledalo znotraj ``DataFixtures/ORM`` (ali ``DataFixtures/MongoDB``
za ODM) direktorij za vsak paket in izvršilo vsak razred, ki implementira
``FixtureInterface``.

Oba ukaza prihajata z nekaj opcijami:

* ``--fixtures=/path/to/fixture`` - Uporabite to opcijo, da ročno določite
  direktorij, kjer bi morali biti naloženi razredi fiksnih podatkov;

* ``--append`` - Uporabite to zastavico, da pripnete podatke namesto brisanja podatkov pred
  nalaganjem (brisanje najprej je privzeto obnašanje);

* ``--em=manager_name`` - Ročno določite upravljalnika entitet za uporabo pri
  nalaganju podatkov.

.. note::

   Če uporabljate opravilo ``doctrine:mongodb:fixtures:load``, zamenjajte opcijo ``--em=``
   z ``--dm=``, da ročno določite upravljalnika dokumenta.

Celotni primer uporabe lahko izgleda takole:

.. code-block:: bash

   php app/console doctrine:fixtures:load --fixtures=/path/to/fixture1 --fixtures=/path/to/fixture2 --append --em=foo_manager

Deljenje objektov med fiksnimi podatki
--------------------------------------

Pisanje osnovnih fiksnih podatkov je enostavno. Vendar kaj, če imate več razredov fiksnih podatkov
in želite biti zmožni se sklicevati na podatke naložene v drugih razredih fiksnih podatkov?
Na primer, kaj če želite naložiti objekt ``User`` v enem fiksnem podatki in nato
se želite sklicevati na njegov sklic v drugem fiksnem podatku, da določite tega uporabnika
določeni skupini?

Knjižnica Doctrine fixtures upravlja s tem enostavno z omogočanjem vam, da določite
vrstni red v katerem so fiksni podatki naloženi.

.. code-block:: php

    // src/Acme/HelloBundle/DataFixtures/ORM/LoadUserData.php
    namespace Acme\HelloBundle\DataFixtures\ORM;

    use Doctrine\Common\DataFixtures\AbstractFixture;
    use Doctrine\Common\DataFixtures\OrderedFixtureInterface;
    use Doctrine\Common\Persistence\ObjectManager;
    use Acme\HelloBundle\Entity\User;

    class LoadUserData extends AbstractFixture implements OrderedFixtureInterface
    {
        /**
         * {@inheritDoc}
         */
        public function load(ObjectManager $manager)
        {
            $userAdmin = new User();
            $userAdmin->setUsername('admin');
            $userAdmin->setPassword('test');

            $manager->persist($userAdmin);
            $manager->flush();

            $this->addReference('admin-user', $userAdmin);
        }

        /**
         * {@inheritDoc}
         */
        public function getOrder()
        {
            return 1; // the order in which fixtures will be loaded
        }
    }

Razred fiksnih podatkov sedaj implementira ``OrderedFixtureInterface``, ki pove
Doctrine, da želite kontrolirati vrstni red vaših fiksnih podatkov. Ustvarite drug
razred fiksnih podatkov in ga naložite za ``LoadUserData`` z vračilom vrstnega reda
2:

.. code-block:: php

    // src/Acme/HelloBundle/DataFixtures/ORM/LoadGroupData.php

    namespace Acme\HelloBundle\DataFixtures\ORM;

    use Doctrine\Common\DataFixtures\AbstractFixture;
    use Doctrine\Common\DataFixtures\OrderedFixtureInterface;
    use Doctrine\Common\Persistence\ObjectManager;
    use Acme\HelloBundle\Entity\Group;

    class LoadGroupData extends AbstractFixture implements OrderedFixtureInterface
    {
        /**
         * {@inheritDoc}
         */
        public function load(ObjectManager $manager)
        {
            $groupAdmin = new Group();
            $groupAdmin->setGroupName('admin');

            $manager->persist($groupAdmin);
            $manager->flush();

            $this->addReference('admin-group', $groupAdmin);
        }

        /**
         * {@inheritDoc}
         */
        public function getOrder()
        {
            return 2; // the order in which fixtures will be loaded
        }
    }

Oba razreda fiksnih podatkov razširjata ``AbstractFixture``, ki vam omogočata
ustvariti objekte in jih nato nastaviti kot sklice, da sta lahko uporabljena
kasneje v drugih fiksnih podatkih. Na primer objekta ``$userAdmin`` in ``$groupAdmin``
sta lahko sklicana kasneje preko sklicev ``admin-user`` in
``admin-group``:

.. code-block:: php

    // src/Acme/HelloBundle/DataFixtures/ORM/LoadUserGroupData.php

    namespace Acme\HelloBundle\DataFixtures\ORM;

    use Doctrine\Common\DataFixtures\AbstractFixture;
    use Doctrine\Common\DataFixtures\OrderedFixtureInterface;
    use Doctrine\Common\Persistence\ObjectManager;
    use Acme\HelloBundle\Entity\UserGroup;

    class LoadUserGroupData extends AbstractFixture implements OrderedFixtureInterface
    {
        /**
         * {@inheritDoc}
         */
        public function load(ObjectManager $manager)
        {
            $userGroupAdmin = new UserGroup();
            $userGroupAdmin->setUser($this->getReference('admin-user'));
            $userGroupAdmin->setGroup($this->getReference('admin-group'));

            $manager->persist($userGroupAdmin);
            $manager->flush();
        }

        /**
         * {@inheritDoc}
         */
        public function getOrder()
        {
            return 3;
        }
    }

Fiksni podatki bodo sedaj izvršeni v naraščajočem vrstnem redu vrnjene vrednosti
z ``getOrder()``. Katerikoli objekt, ki je nastavljen z metodo ``setReference()``
je lahko dostopan preko ``getReference()`` v razredu fiksnih podatkov, ki imajo višji
vrstni red.

Fiksni podatki vam omogočajo ustvariti kakršnikoli tip podatkov potrebujete preko običajnega PHP
vmesnika za izdelavo in pridobivanje objektov. S krmiljenjem vrstnega reda
fiksnih podatkov in nastavitvijo sklicev je lahko skoraj vse upravljano s strani fiksnih podatkov.

Uporaba kontejnerja v fiksnih podatkih
--------------------------------------

V nekaterih primerih boste morda potrebovali dostopati do storitev in naložiti fiksne podatke.
Symfony2 naredi to res enostavno: kontejner bo injiciran v vse
razrede fiksnih podatkov, ki implementirajo :class:`Symfony\\Component\\DependencyInjection\\ContainerAwareInterface`.

Prepišimo prvi fiksni podatek za enkodiranje gesla preden je shranjen
v podatkovno bazo (zelo dobra praksa). To bo uporabilo tovarno enkoder
za enkodiranje gesla in zagotavljalo, da je enkodirano na način uporabljen s strani varnostne
komponente, ko se ga preverja:

.. code-block:: php

    // src/Acme/HelloBundle/DataFixtures/ORM/LoadUserData.php

    namespace Acme\HelloBundle\DataFixtures\ORM;

    use Doctrine\Common\DataFixtures\FixtureInterface;
    use Doctrine\Common\Persistence\ObjectManager;
    use Symfony\Component\DependencyInjection\ContainerAwareInterface;
    use Symfony\Component\DependencyInjection\ContainerInterface;
    use Acme\HelloBundle\Entity\User;

    class LoadUserData implements FixtureInterface, ContainerAwareInterface
    {
        /**
         * @var ContainerInterface
         */
        private $container;

        /**
         * {@inheritDoc}
         */
        public function setContainer(ContainerInterface $container = null)
        {
            $this->container = $container;
        }

        /**
         * {@inheritDoc}
         */
        public function load(ObjectManager $manager)
        {
            $user = new User();
            $user->setUsername('admin');
            $user->setSalt(md5(uniqid()));

            $encoder = $this->container
                ->get('security.encoder_factory')
                ->getEncoder($user)
            ;
            $user->setPassword($encoder->encodePassword('secret', $user->getSalt()));

            $manager->persist($user);
            $manager->flush();
        }
    }

Kot vidite, je vse kar je potrebno dodati, :class:`Symfony\\Component\\DependencyInjection\\ContainerAwareInterface`
razredu in nato ustvariti novo metodo :method:`Symfony\\Component\\DependencyInjection\\ContainerInterface::setContainer`,
ki implementira ta vmesnik. Preden je fiksni podatek izvršen, bo Symfony
poklical metodo :method:`Symfony\\Component\\DependencyInjection\\ContainerInterface::setContainer`
avtomatično. Dokler shranjujete kontejner kot lastnost na
razredu (kot prikazano zgoraj), lahko do njega dostopate v metodi ``load()``.

.. note::

    Če ste preveč leni za implementacijo potrebne metode :method:`Symfony\\Component\\DependencyInjection\\ContainerInterface::setContainer`,
    lahko vaš razred razširite z :class:`Symfony\\Component\\DependencyInjection\\ContainerAware`.

.. _DoctrineFixturesBundle: https://github.com/doctrine/DoctrineFixturesBundle
.. _`Doctrine Data Fixtures`: https://github.com/doctrine/data-fixtures
