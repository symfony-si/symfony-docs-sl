.. index::
   single: Config; Loading resources

Nalaganje virov
===============

Lociranje virov
---------------

Nalaganje nastavitev se običajno začne z iskanjem virov - v
večini primerov: datotek. To je lahko narejeno s :class:`Symfony\\Component\\Config\\FileLocator`::

    use Symfony\Component\Config\FileLocator;

    $configDirectories = array(__DIR__.'/app/config');

    $locator = new FileLocator($configDirectories);
    $yamlUserFiles = $locator->locate('users.yml', null, false);

Locirnik dobi zbirko lokacije, kje naj išče datoteke.
Prvi argument ``locate()`` je ime datoteke, ki jo išče. Drugi
argument je lahko trenutna pot in ko je podana, bo locirnik
iskal najprej v tem direktoriju. Tretji argument označuje ali bi moral ali ne
locirnik vrniti prvo datoteko, ki jo je našel, ali pa polje, ki vsebuje
vse zadetke.

Nalagalniki virov
-----------------

Za vsak tip virov (Yaml, XML, anotacija itd.) mora biti nalagalnik definiran.
Vsak nalagalnik bi moral implementirati :class:`Symfony\\Component\\Config\\Loader\\LoaderInterface`
ali razširiti abstrakni :class:`Symfony\\Component\\Config\\Loader\\FileLoader`
razred, ki omogoča rekurzivno uvažanje ostalih virov::

    use Symfony\Component\Config\Loader\FileLoader;
    use Symfony\Component\Yaml\Yaml;

    class YamlUserLoader extends FileLoader
    {
        public function load($resource, $type = null)
        {
            $configValues = Yaml::parse($resource);

            // ... handle the config values

            // maybe import some other resource:

            // $this->import('extra_users.yml');
        }

        public function supports($resource, $type = null)
        {
            return is_string($resource) && 'yml' === pathinfo(
                $resource,
                PATHINFO_EXTENSION
            );
        }
    }

Najdenje ustreznega nalagalnika
-------------------------------

Razred :class:`Symfony\\Component\\Config\\Loader\\LoaderResolver` dobi kot
svoj prvi konstruktorjev argument zbirko nalagalnikov. Ko bi vir (na
primer XML datoteka) moral biti naložen, gre skozi zanko te zbirke
nalagalnikov in vrne nalagalnik, ki podpira ta določeni tip vira.

Razred :class:`Symfony\\Component\\Config\\Loader\\DelegatingLoader` uporablja
razred :class:`Symfony\\Component\\Config\\Loader\\LoaderResolver`. Ko
je vprašan, da naloži vir, delegira to vprašanje razredu
:class:`Symfony\\Component\\Config\\Loader\\LoaderResolver`. V tem primeru ko je t.i. resolver
našel ustrezni nalagalnik, bo ta nalagalnik vprašan, da naloži vir::

    use Symfony\Component\Config\Loader\LoaderResolver;
    use Symfony\Component\Config\Loader\DelegatingLoader;

    $loaderResolver = new LoaderResolver(array(new YamlUserLoader($locator)));
    $delegatingLoader = new DelegatingLoader($loaderResolver);

    $delegatingLoader->load(__DIR__.'/users.yml');
    /*
    The YamlUserLoader will be used to load this resource,
    since it supports files with a "yml" extension
    */
