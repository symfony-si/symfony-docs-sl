.. index::
   single: Config; Defining and processing configuration values

Opredelitev in procesiranje vrednosti nastavitev
================================================

Potrjevanje vrednosti nastavitev
--------------------------------

Po nalaganju nastavitvenih vrednosti vseh vrst virov, so vrednosti
in njihove strukture lahko potrjene z uporabo t.i. "Definition" dela komponente
Config. Od nastavitvenih vrednosti se običajno pričakuje, da prikažejo neke
vrste hierarhijo. Tudi vrednosti bi morale biti določenega tipa, biti omejene
po številu ali biti ena izmed danih skupkov vrednosti. Na primer, sledeče
nastavitve (v YAML) prikazujejo jasno hierarhijo in nekaj pravil potrjevanja,
ki bi morala biti uporabljena na njih (kot npr. "vrednost za ``auto_connect`` mora biti logična vrednost):

.. code-block:: yaml

    auto_connect: true
    default_connection: mysql
    connections:
        mysql:
            host:     localhost
            driver:   mysql
            username: user
            password: pass
        sqlite:
            host:     localhost
            driver:   sqlite
            memory:   true
            username: user
            password: pass

Ko se nalaga več nastavitvenih datotek, bi moralo biti mogoče združiti
in prepisati nekatere vrednosti. Ostale vrednosti ne bi smele biti združene in ostati
take, kot se nanje prvič naleti. Tudi nekateri ključi so samo na voljo, ko
ima drug ključ določeno vrednost (v primeru nastavitev zgoraj: ključ
``memory`` je smiseln, ko je ``driver`` enak ``sqlite``).

Definiranje hierarhije vrednosti nastavitev z uporabo TreeBuilder-ja
--------------------------------------------------------------------

Vsa pravila, ki se tičejo nastavitvenih vrednosti, so lahko definirana z uporabo
:class:`Symfony\\Component\\Config\\Definition\\Builder\\TreeBuilder`.

Instanca :class:`Symfony\\Component\\Config\\Definition\\Builder\\TreeBuilder`
bi morala biti vrnjena iz po meri narejenega ``Configuration`` razreda, ki implementira
:class:`Symfony\\Component\\Config\\Definition\\ConfigurationInterface`::

    namespace Acme\DatabaseConfiguration;

    use Symfony\Component\Config\Definition\ConfigurationInterface;
    use Symfony\Component\Config\Definition\Builder\TreeBuilder;

    class DatabaseConfiguration implements ConfigurationInterface
    {
        public function getConfigTreeBuilder()
        {
            $treeBuilder = new TreeBuilder();
            $rootNode = $treeBuilder->root('database');

            // ... add node definitions to the root of the tree

            return $treeBuilder;
        }
    }

Dodajanje definicij vozlišč drevesu
-----------------------------------

Spremenljivke vozlišč
~~~~~~~~~~~~~~~~~~~~~

Drevo vsebuje definicije vozlišč, ki so lahko določena na semantični način.
To pomeni, da je z uporabo indentacije in tekočih notacij mogoče
odražati realno strukturo vrednosti nastavitev::

    $rootNode
        ->children()
            ->booleanNode('auto_connect')
                ->defaultTrue()
            ->end()
            ->scalarNode('default_connection')
                ->defaultValue('default')
            ->end()
        ->end()
    ;

Vrhnje vozlišče je samo po sebi vozlišče polje in ima otroke, kot logično
vozlišče ``auto_connect`` in skalarno vozlišče ``default_connection``. Na splošno:
po definiranju vozlišča, klic metode ``end()`` vas premakne en korak naprej v hierarhiji.

Tip vozlišča
~~~~~~~~~~~~

Možno je potrditi tip podane vrednosti z uporabo ustrezne
definicije vozlišča. Tipi vozlišč so na voljo za:

* skalar
* logične vrednosti
* celo število
* število s plavajočo vejico
* enum
* polje
* spremenljivko (ni preverjanja)

in so ustvarjena z ``node($name, $type)`` ali njihovo povezano bližnjično
metodo ``xxxxNode($name)``.

Omejitve numeričnih vozlišč
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Numerična vozlišča (števila s plavajočo vejico in cela števila) ponujajo dve dodatni omejitvi -
:method:`Symfony\\Component\\Config\\Definition\\Builder::min` in
:method:`Symfony\\Component\\Config\\Definition\\Builder::max` -
omogočata potrjevanje vrednosti::

    $rootNode
        ->children()
            ->integerNode('positive_value')
                ->min(0)
            ->end()
            ->floatNode('big_value')
                ->max(5E45)
            ->end()
            ->integerNode('value_inside_a_range')
                ->min(-50)->max(50)
            ->end()
        ->end()
    ;

Enum vozlišča
~~~~~~~~~~~~~

Enum vozlišča ponujajo omejitev, ki se ujema z danim vnosom proti skupku
vrednosti::

    $rootNode
        ->children()
            ->enumNode('gender')
                ->values(array('male', 'female'))
            ->end()
        ->end()
    ;

To bo omejilo opcijo ``gender``, da je ali ``male`` ali ``female``.

Vozlišča polja
~~~~~~~~~~~~~~

Možno je dodati globlji nivo hierarhije z dodajanjem vozlišča
polja. Vozlišče polje ima samo po sebi lahko vnajprej določen skupek vrednosti vozlišč::

    $rootNode
        ->children()
            ->arrayNode('connection')
                ->children()
                    ->scalarNode('driver')->end()
                    ->scalarNode('host')->end()
                    ->scalarNode('username')->end()
                    ->scalarNode('password')->end()
                ->end()
            ->end()
        ->end()
    ;

Ali pa lahko definirate prototip za vsako vozlišče znotraj vozlišča polja::

    $rootNode
        ->children()
            ->arrayNode('connections')
                ->prototype('array')
                    ->children()
                        ->scalarNode('driver')->end()
                        ->scalarNode('host')->end()
                        ->scalarNode('username')->end()
                        ->scalarNode('password')->end()
                    ->end()
                ->end()
            ->end()
        ->end()
    ;

Prototip je lahko uporabljen za dodajanje definicije, ki je lahko ponovoljena mnogokrat
znotraj trenutnega vozlišča. Glede na definicijo prototipa v primeru zgoraj je
možno imeti več povezav polj (vsebujejo ``driver``,
``host`` itd.).

Opcije vozlišla polja
~~~~~~~~~~~~~~~~~~~~~

Pred definicijo otrok vozlišča polja lahko podate opcije kot:

``useAttributeAsKey()``
    Podate ime vozlišča otroka, katerega vrednost bi morala biti uporabljena kot ključ v nastalem polju.
``requiresAtLeastOneElement()``
    Na voljo bi moral biti vsaj en element v polju (deluje samo, ko je ``isRequired()`` tudi
    klicana).
``addDefaultsIfNotSet()``
    Če katerokoli otrokovo vozlišče ima privzete vrednosti, jih uporabite, če eksplicitne vrednosti niso bile podane.

Primer tega::

    $rootNode
        ->children()
            ->arrayNode('parameters')
                ->isRequired()
                ->requiresAtLeastOneElement()
                ->useAttributeAsKey('name')
                ->prototype('array')
                    ->children()
                        ->scalarNode('value')->isRequired()->end()
                    ->end()
                ->end()
            ->end()
        ->end()
    ;

V YAML lahko zgleda nastavitev takole:

.. code-block:: yaml

    database:
        parameters:
            param1: { value: param1val }

V XML vsako vozlišče ``parameters`` bi imelo ``name`` atribut (skupaj z
``value``), ki bi bilo preimenovano in uporabljeno kot ključ za ta element v
končnem polju. ``useAttributeAsKey`` je uporaben za normalizacijo, kako so
polja določena med različnimi formati, kot sta XML in YAML.

Privzete in zahtevane vrednosti
-------------------------------

Za vse tipe vozlišč je mogoče definirati privzete vrednosti in zamenjati
vrednosti v primeru, da
ima vozlišče določeno vrednost:

``defaultValue()``
    Nastavi privzeto vrednost
``isRequired()``
    Mora biti definiran (vendar je lahko prazen)
``cannotBeEmpty()``
    Ne sme vsebovati prazne vrednosti
``default*()``
    (``null``, ``true``, ``false``), bližnjica za ``defaultValue()``
``treat*Like()``
    (``null``, ``true``, ``false``), podaja nadomestljivo vrednost v primeru, da je vrednost ``*.``

.. code-block:: php

    $rootNode
        ->children()
            ->arrayNode('connection')
                ->children()
                    ->scalarNode('driver')
                        ->isRequired()
                        ->cannotBeEmpty()
                    ->end()
                    ->scalarNode('host')
                        ->defaultValue('localhost')
                    ->end()
                    ->scalarNode('username')->end()
                    ->scalarNode('password')->end()
                    ->booleanNode('memory')
                        ->defaultFalse()
                    ->end()
                ->end()
            ->end()
            ->arrayNode('settings')
                ->addDefaultsIfNotSet()
                ->children()
                    ->scalarNode('name')
                        ->isRequired()
                        ->cannotBeEmpty()
                        ->defaultValue('value')
                    ->end()
                ->end()
            ->end()
        ->end()
    ;

Opcijske sekcije
----------------

Če imate celotne sekcije, ki so opcijske in so lahko omogočene/onemogočene,
lahko uporabite prednost bližnjic metod
:method:`Symfony\\Component\\Config\\Definition\\Builder\\ArrayNodeDefinition::canBeEnabled` in
:method:`Symfony\\Component\\Config\\Definition\\Builder\\ArrayNodeDefinition::canBeDisabled`::

    $arrayNode
        ->canBeEnabled()
    ;

    // is equivalent to

    $arrayNode
        ->treatFalseLike(array('enabled' => false))
        ->treatTrueLike(array('enabled' => true))
        ->treatNullLike(array('enabled' => true))
        ->children()
            ->booleanNode('enabled')
                ->defaultFalse()
    ;

Metoda ``canBeDisabled`` deluje enako razen, da sekcija
bi bila privzeto omogočena.

Opcije združevanja
------------------

Podane so lahko dodatne opcije, ki se tičejo procesa združevanja. Za polja:

``performNoDeepMerging()``
    Ko je vrednost tudi definirana v drugem nastavitvenem polju, ne
    poizkušajte združiti polja, vendar jo v celoti prepišite.

Za vsa vozlišča:

``cannotBeOverwritten()``
    ne dopušča ostalim nastavitvenim poljem, da prepišejo obstoječe vrednosti za to vozlišče

Sekcije dodajanja
-----------------

Če imate za potrditi kompleksne nastavitve, potem lahko drevo zraste
zelo veliko in ga boste morali morda razdeliti v sekcije. To lahko naredite
z ustvarjanjem sekcije, ki je ločeno vozlišče in je potem dodano v glavno drevo
z ``append()``::

    public function getConfigTreeBuilder()
    {
        $treeBuilder = new TreeBuilder();
        $rootNode = $treeBuilder->root('database');

        $rootNode
            ->children()
                ->arrayNode('connection')
                    ->children()
                        ->scalarNode('driver')
                            ->isRequired()
                            ->cannotBeEmpty()
                        ->end()
                        ->scalarNode('host')
                            ->defaultValue('localhost')
                        ->end()
                        ->scalarNode('username')->end()
                        ->scalarNode('password')->end()
                        ->booleanNode('memory')
                            ->defaultFalse()
                        ->end()
                    ->end()
                    ->append($this->addParametersNode())
                ->end()
            ->end()
        ;

        return $treeBuilder;
    }

    public function addParametersNode()
    {
        $builder = new TreeBuilder();
        $node = $builder->root('parameters');

        $node
            ->isRequired()
            ->requiresAtLeastOneElement()
            ->useAttributeAsKey('name')
            ->prototype('array')
                ->children()
                    ->scalarNode('value')->isRequired()->end()
                ->end()
            ->end()
        ;

        return $node;
    }

To je tudi uporabno, da vam pomaga se izogniti ponavljanju, če imate sekcije
nastavitev, ki so predstavljene na različnih mestih.

Normalizacija
-------------

Ko so nastavitvene datoteke procesirane, so najprej normalizirane, nato združene
in na koncu je drevo uporabljeno za potrditev končnega polja. Proces normalizacije
je uporabljen za odstranitev nekaj razlik, ki se kažejo v različnih
formatih nastavitev, v glavnem razlike med YAML in XML.

Ločilo uporabljeno v ključih je običajno ``_`` v YAML in ``-`` v XML. Za
primer, ``auto_connect`` v YAML in ``auto-connect`` v XML. Normalizacija bi
naredila oba od teh kot ``auto_connect``.

.. caution::

    Ciljni ključ ne bo spremenjen, če je mešan kot
    ``foo-bar_moo`` ali če že obstaja.

Druga razlika med YAML in XML je v načinu, kako so lahko polja vrednosti
predstavljena. V YAML imate lahko:

.. code-block:: yaml

    twig:
        extensions: ['twig.extension.foo', 'twig.extension.bar']

in v XML:

.. code-block:: xml

    <twig:config>
        <twig:extension>twig.extension.foo</twig:extension>
        <twig:extension>twig.extension.bar</twig:extension>
    </twig:config>

Ta razlika je lahko odstranjena v normalizaciji z množino ključa uporabljenega
v XML. Lahko določite, da želite ključ v množini na ta način z
``fixXmlConfig()``::

    $rootNode
        ->fixXmlConfig('extension')
        ->children()
            ->arrayNode('extensions')
                ->prototype('scalar')->end()
            ->end()
        ->end()
    ;

Če je množina neregularna, lahko določite množino, da je uporabljena kot
drugi argument::

    $rootNode
        ->fixXmlConfig('child', 'children')
        ->children()
            ->arrayNode('children')
        ->end()
    ;

Tako kot tudi popravljanje tega, ``fixXmlConfig`` zagotavlja, da so edninski XML elementi
še vedno spremenjeni v polje. Tako imate lahko:

.. code-block:: xml

    <connection>default</connection>
    <connection>extra</connection>

in včasih samo:

.. code-block:: xml

    <connection>default</connection>

Privzeto bi ``connection`` bilo polje v prvem primeru in niz
v drugem, kar oteži potrjevanje. Lahko zagotovite, da je vedno
polje z ``fixXmlConfig``.

Nadalje lahko kontrolirate proces normalizacije, če ga potrebujete. Na primer,
morda boste želeli dovoliti, da je niz skupek in uporabljen kot določen ključ ali
več ključev, da so nastavljeni eksplicitno. Tako da, če je ločeno od ``name``, je opcijsko
v tej nastavitvi:

.. code-block:: yaml

    connection:
        name:     my_mysql_connection
        host:     localhost
        driver:   mysql
        username: user
        password: pass

lahko dovolite tudi sledeče:

.. code-block:: yaml

    connection: my_mysql_connection

S spreminjanjem vrednosti niza v asociativno polje z ``name`` kot ključem::

    $rootNode
        ->children()
            ->arrayNode('connection')
                ->beforeNormalization()
                    ->ifString()
                    ->then(function($v) { return array('name'=> $v); })
                ->end()
                ->children()
                    ->scalarNode('name')->isRequired()
                    // ...
                ->end()
            ->end()
        ->end()
    ;

Pravila potrjevanja
-------------------

Bolj napredna pravila potrjevanja so lahko podana z uporabo
:class:`Symfony\\Component\\Config\\Definition\\Builder\\ExprBuilder`. Ta
graditelj implementira tekoči vmesnik za dobro znane kontrolne strukture.
Graditelj je uporabljen za dodajanje naprednejših pravil potrjevanja k definicijam vozlišča, kot::

    $rootNode
        ->children()
            ->arrayNode('connection')
                ->children()
                    ->scalarNode('driver')
                        ->isRequired()
                        ->validate()
                        ->ifNotInArray(array('mysql', 'sqlite', 'mssql'))
                            ->thenInvalid('Invalid database driver "%s"')
                        ->end()
                    ->end()
                ->end()
            ->end()
        ->end()
    ;

Pravilo potrjevanja ima vedno "if" del. Lahko določite ta del na
sledeče načine:

- ``ifTrue()``
- ``ifString()``
- ``ifNull()``
- ``ifArray()``
- ``ifInArray()``
- ``ifNotInArray()``
- ``always()``

Pravilo potrjevanja tudi zahteva "then" del:

- ``then()``
- ``thenEmptyArray()``
- ``thenInvalid()``
- ``thenUnset()``

Običajno "tehn" je zaprtje. Njegova vrnjena vrednost bo vedno uporabljena kot nova vrednost
za vozlišče, namesto
originalne vrednosti vozlišča.

Procesiranje nastavitvenih vrednosti
------------------------------------

:class:`Symfony\\Component\\Config\\Definition\\Processor` uporablja drevo
kot je bilo zgrajeno z uporabo :class:`Symfony\\Component\\Config\\Definition\\Builder\\TreeBuilder`
za procesiranje večih polj nastavitvenih vrednosti, ki bi morale biti združene.
Če katerakoli vrednost ni pričakovanega tipa, je obvezna in še nedefinirana,
ali pa če ne more biti potrjena na nek drug način, bo vržena izjema.
Drugače je rezultat čisto polje vrednosti nastavitev::

    use Symfony\Component\Yaml\Yaml;
    use Symfony\Component\Config\Definition\Processor;
    use Acme\DatabaseConfiguration;

    $config1 = Yaml::parse(__DIR__.'/src/Matthias/config/config.yml');
    $config2 = Yaml::parse(__DIR__.'/src/Matthias/config/config_extra.yml');

    $configs = array($config1, $config2);

    $processor = new Processor();
    $configuration = new DatabaseConfiguration();
    $processedConfiguration = $processor->processConfiguration(
        $configuration,
        $configs
    );
