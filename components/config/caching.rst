.. index::
   single: Config; Caching based on resources

Predpomnenje osnovano na virih
==============================

Ko so vsi viri nastavitev naloženi, morda želite sprocesirati nastavitvene
vrednosti in jih vse kompinirati v eni datoteki. Ta datoteka se obnaša kot
predpomnilnik. Njena vsebina ni nujno ponovno generirana vsakič, ko se aplikacija
zažene - samo ko so viri nastavitev modificirani.

Na primer, Symfony komponenta Routing vam omogoča, da naložite vse poti
in nato izpustite URL ujemalnik ali URL generator na osnovi teh poti. V
tem primeru, ko je en izmed virov spremenjen (in delate v razvojnem
okolju) bi generirana datoteka morala biti razveljavljena in ponovno
generirana. To je doseženo z ustvarjanjem uporabe razreda
:class:`Symfony\\Component\\Config\\ConfigCache`.

Primer spodaj vam prikazuje, kako zbrati vire in nato generirati nekaj kode
na osnovi virov, ki so naloženi in pisati to kodo predpomnilniku. Predpomnilnik
tudi sprejme zbirko virov, ki so bili uporabljeni za generacijo kode.
Če se pogleda "last modified" časovni žig teh virov, lahko predpomnilnik
pove, če je še vedno sveže ali pa bi morale biti njegove vsebine ponovno
generirane::

    use Symfony\Component\Config\ConfigCache;
    use Symfony\Component\Config\Resource\FileResource;

    $cachePath = __DIR__.'/cache/appUserMatcher.php';

    // the second argument indicates whether or not you want to use debug mode
    $userMatcherCache = new ConfigCache($cachePath, true);

    if (!$userMatcherCache->isFresh()) {
        // fill this with an array of 'users.yml' file paths
        $yamlUserFiles = ...;

        $resources = array();

        foreach ($yamlUserFiles as $yamlUserFile) {
            // see the previous article "Loading resources" to
            // see where $delegatingLoader comes from
            $delegatingLoader->load($yamlUserFile);
            $resources[] = new FileResource($yamlUserFile);
        }

        // the code for the UserMatcher is generated elsewhere
        $code = ...;

        $userMatcherCache->write($code, $resources);
    }

    // you may want to require the cached code:
    require $cachePath;

V načinu razhroščevanja, ``.meta`` datoteka bo ustvarjena v istem direktoriju
kot je sama datoteka predpomnenja. Ta ``meta`` datoteka vsebuje serializirane
vire, katerih časovni žigi so uporabljeni za ugotovitev, če je predpomnilnik še
vedno svež. Ko niste v načinu razhroščevanja, se predpomnilnik šteje za osveženega
("fresh") kakor hitro obstaja in zato ``.meta`` datoteka ne bo ustvarjena.
