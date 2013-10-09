Arhitektura
===========

Ste moj junak! Kdo bi si mislil, da boste tu še vedno po prvih treh delih?
Vaši dosežki bodo kmalu dobro nagrajeni. Prvi trije deli niso podrobno
pogledali v arhitekturo ogrodja. Ker le ta naredi Symfony2 izstopajočega
iz množice ogrodij, si sedaj poglejmo arhitekturo.

Razumevanje strukture direktorijev
----------------------------------

Struktura direktorijev Symfony2 :term:`application` je nekoliko fleksibilna,
vendar struktura direktorijev distribucija *standardne izdaje* odraža
tipično in priporočeno strukturo Symfony2 aplikacije:

* ``app/``:    Nastavitve aplikacije;
* ``src/``:    PHP koda projekta;
* ``vendor/``: Odvisnosti tretjih oseb;
* ``web/``:    Vrhovni spletni direktorij.

Direktorij ``web/``
~~~~~~~~~~~~~~~~~~~

Vrhovni direktorij web je dom za vse javne in statične datoteke kot so slike,
stili in JavaScript datoteke. Je tudi lokacija, kjer se nahaja vsak
term:`front controller`::

    // web/app.php
    require_once __DIR__.'/../app/bootstrap.php.cache';
    require_once __DIR__.'/../app/AppKernel.php';

    use Symfony\Component\HttpFoundation\Request;

    $kernel = new AppKernel('prod', false);
    $kernel->loadClassCache();
    $kernel->handle(Request::createFromGlobals())->send();

Jedro (Kernel) najprej zahteva ``bootstrap.php.cache`` datoteko, ki začetno naloži
ogrodje in registrira avtomatski nalagalnik (glejte spodaj).

Kot vsak prednji krmilnik, ``app.php`` uporablja Kernel razred, ``AppKernel``, da
samozažene aplikacijo.

.. _the-app-dir:

Direktorij ``app/``
~~~~~~~~~~~~~~~~~~~

``AppKernel`` razred je glavna vstopna točka nastavitev aplikacije in kot tak
je shranjen v direktoriju ``app/``.

Ta razred mora implementirati dve metodi:

* ``registerBundles()`` mora vrniti polje vseh paketov potrebnih za zagon
  aplikacije;

* ``registerContainerConfiguration()`` naloži nastavitve aplikacije
  (več o tem kasneje).

Avtomatsko nalaganje je urejeno avtomatsko preko orodja `Composer`_, kar pomeni, da
lahko uporabite katerikoli PHP razred brez, da bi morali narediti karkoli! Če potrebujete
več fleksibilnosti, lahko razširite avtomatski nalagalnik v ``app/autoload.php`` datoteki.
Vse odvistnosti so shranjene pod direktorijem ``vendor/``, vendar to je samo konvencija.
Lahko jih shranite kamorkoli želite, globalno na vaš strežnik ali lokalno v vaše projekte.

.. note::

    Če se želite naučiti več o Composer-jevem avtomatskem nalagalniku, preberite `Composer-Autoloader`_.
    Symfony ima tudi avtomatsko nalagalno komponento - preberite ":doc:`/components/class_loader/class_loader`".

Razumevanje sistema paketov
---------------------------

Ta sekcija uvaja eno izmed najboljših in najmočnejših lastnosti Symfony2
This section introduces one of the greatest and most powerful features of,
sistem :term:`bundle`-ov.

Paket (bundle) je neke vrste vtičnik v drugo programsko opremo. Torej zakaj
se imenuje *paket* in ne *vtičnik*? To je zato, ker je *vse* paket v Symfony2,
od lastnosti jedra ogrodja do kode, ki jo pišete za vašo aplikacijo. Paketi so
prvorazredni elementi v Symfony2. To vam ponuja fleksibilnost, da uporabite
vnaprej zgrajene lastnosti zapakirane v tretje osebne pakete ali za distribuiranje
vaših lastnih paketov. Omogoča vam, da enostavno uporabite in izberete katere
lastnosti bodo omogočene v vaši aplikaciji in jih optimizirati, kot želite.
Na koncu dneva, je koda vaše aplikacije prav tako *pomembna* kot je samo jedro
ogrodja.

Registracija paketa
~~~~~~~~~~~~~~~~~~~

Aplikacija je narejena iz paketov, ki so definirani v ``registerBundles()``
metodi razreda ``AppKernel``. Vsak paket je direktorij, ki vsebuje en razred
``Bundle``, ki ga opisuje::

    // app/AppKernel.php
    public function registerBundles()
    {
        $bundles = array(
            new Symfony\Bundle\FrameworkBundle\FrameworkBundle(),
            new Symfony\Bundle\SecurityBundle\SecurityBundle(),
            new Symfony\Bundle\TwigBundle\TwigBundle(),
            new Symfony\Bundle\MonologBundle\MonologBundle(),
            new Symfony\Bundle\SwiftmailerBundle\SwiftmailerBundle(),
            new Symfony\Bundle\DoctrineBundle\DoctrineBundle(),
            new Symfony\Bundle\AsseticBundle\AsseticBundle(),
            new Sensio\Bundle\FrameworkExtraBundle\SensioFrameworkExtraBundle(),
        );

        if (in_array($this->getEnvironment(), array('dev', 'test'))) {
            $bundles[] = new Acme\DemoBundle\AcmeDemoBundle();
            $bundles[] = new Symfony\Bundle\WebProfilerBundle\WebProfilerBundle();
            $bundles[] = new Sensio\Bundle\DistributionBundle\SensioDistributionBundle();
            $bundles[] = new Sensio\Bundle\GeneratorBundle\SensioGeneratorBundle();
        }

        return $bundles;
    }

Kot dodatek za ``AcmeDemoBundle``, o katerem je bilo že govora, bodite pozorni,
da jedro tudi omogoči ostale pakete kot so ``FrameworkBundle``,
``DoctrineBundle``, ``SwiftmailerBundle``, in ``AsseticBundle`` paket.
Vsi so del jedra ogrodja.

Nastavitev paketa
~~~~~~~~~~~~~~~~~

Vsak paket je možno prilagoditi preko nastavitvenih datotek napisanih v YAML, XML ali
PHP. Poglejte si privzete nastavitve:

.. code-block:: yaml

    # app/config/config.yml
    imports:
        - { resource: parameters.yml }
        - { resource: security.yml }

    framework:
        #esi:             ~
        #translator:      { fallback: "%locale%" }
        secret:          "%secret%"
        router:
            resource: "%kernel.root_dir%/config/routing.yml"
            strict_requirements: "%kernel.debug%"
        form:            true
        csrf_protection: true
        validation:      { enable_annotations: true }
        templating:      { engines: ['twig'] } #assets_version: SomeVersionScheme
        default_locale:  "%locale%"
        trusted_proxies: ~
        session:         ~

    # Twig Configuration
    twig:
        debug:            "%kernel.debug%"
        strict_variables: "%kernel.debug%"

    # Assetic Configuration
    assetic:
        debug:          "%kernel.debug%"
        use_controller: false
        bundles:        [ ]
        #java: /usr/bin/java
        filters:
            cssrewrite: ~
            #closure:
            #    jar: "%kernel.root_dir%/Resources/java/compiler.jar"
            #yui_css:
            #    jar: "%kernel.root_dir%/Resources/java/yuicompressor-2.4.7.jar"

    # Doctrine Configuration
    doctrine:
        dbal:
            driver:   "%database_driver%"
            host:     "%database_host%"
            port:     "%database_port%"
            dbname:   "%database_name%"
            user:     "%database_user%"
            password: "%database_password%"
            charset:  UTF8

        orm:
            auto_generate_proxy_classes: "%kernel.debug%"
            auto_mapping: true

    # Swiftmailer Configuration
    swiftmailer:
        transport: "%mailer_transport%"
        host:      "%mailer_host%"
        username:  "%mailer_user%"
        password:  "%mailer_password%"
        spool:     { type: memory }

Vsak vnos kot ``framework`` definira nastavitev za določen paket.
Na primer, ``framework`` nastavi ``FrameworkBundle`` med tem ko ``swiftmailer``
nastavi ``SwiftmailerBundle``.

Vsaka nastavitev :term:`environment` lahko prepiše privzete nastavitve z zagotovitvijo
določene nastavitvene datoteke. Na primer, ``dev`` okolje naloži
``config_dev.yml`` datoteko, ki naloži glavno nastavitev (t.j. ``config.yml``)
in jo potem spremeni za dodajanje nekaterih razhroščevalnih orodij:

.. code-block:: yaml

    # app/config/config_dev.yml
    imports:
        - { resource: config.yml }

    framework:
        router:   { resource: "%kernel.root_dir%/config/routing_dev.yml" }
        profiler: { only_exceptions: false }

    web_profiler:
        toolbar: true
        intercept_redirects: false

    monolog:
        handlers:
            main:
                type:  stream
                path:  "%kernel.logs_dir%/%kernel.environment%.log"
                level: debug
            firephp:
                type:  firephp
                level: info

    assetic:
        use_controller: true

Razširitev paketa
~~~~~~~~~~~~~~~~~

Kot dodatek za lep način organizacije in nastavitve vaše kode, paket lahko
razširi drug paket. Dedinjenje paketov vam omogoča prepis kateregakoli obstoječega
paketa za prilagoditev njegovih krmilnikov, predlog, ali katerekoli od njegovih datotek.
Tu pridejo prav logična imena (npr. ``@AcmeDemoBundle/Controller/SecuredController.php``):
povzemajo, kje je vir dejansko shranjen.

Logična imena datotek
.....................

Ko želite referenco datoteke iz paketa, uporabite ta zapis:
``@BUNDLE_NAME/path/to/file``; Symfony2 bo rešil ``@BUNDLE_NAME``
v pravo pot do paketa. Na primer, logična pot
``@AcmeDemoBundle/Controller/DemoController.php`` bi bila pretvorjena v
``src/Acme/DemoBundle/Controller/DemoController.php``, ker Symfony ve
lokacijo ``AcmeDemoBundle``.

Logična imena krmilnikov
........................

Za krmilnike, potrebujete ime referenčne metode z uporabo oblike
``BUNDLE_NAME:CONTROLLER_NAME:ACTION_NAME``. Na primer,
``AcmeDemoBundle:Welcome:index`` se poveže z ``indexAction`` metodo iz
``Acme\DemoBundle\Controller\WelcomeController`` razreda.

Logična imena predlog
.....................

Za predloge je logično ime ``AcmeDemoBundle:Welcome:index.html.twig``
pretvorjeno v pot datoteke ``src/Acme/DemoBundle/Resources/views/Welcome/index.html.twig``.
Predloge postanejo še bolj zanimive, ko ugotivite, da ne potrebujejo biti shranjene
na datotečnem sistemu. Lahko jih enostavno shranite v tabelo podatkovne baze na primer.

Razširitev paketov
..................

Če sledite tem konvencijam, potem lahko uporabite :doc:`dedinjenje paketov</cookbook/bundles/inheritance>`
za "prepis" datotek, krmilnikov ali predlog. Na primer, lahko naredite
paket - ``AcmeNewBundle`` - in določite, da prepiše ``AcmeDemoBundle``.
Ko Symfony naloži ``AcmeDemoBundle:Welcome:index`` krmilnik, bo
najprej pogledal za ``WelcomeController`` razred v ``AcmeNewBundle`` in če
ne obstaja, potem pogleda znotraj ``AcmeDemoBundle``. To pomeni, da en paket
lahko prepiše skoraj katerikoli del drugega paketa!

Sedaj razumete zakaj je Symfony2 tako fleksibilen? Delite vaše pakete med aplikacijami,
shranite jih lokalno ali globalno, vaša izbira.

.. _using-vendors:

Uporaba izdelovalcev (vendors)
------------------------------

Možnosti so, da bo vaša aplikacija odvisna od tretje-osebnih knjižnic. Te
bi morale biti shranjene v ``vendor/`` direktoriju. Ta direktorij že vsebuje
Symfony2 knjižnice, knjižnico SwiftMailer, Doctrine ORM, Twig sistem predlog in
nekatere ostale knjižnice tretjih oseb in paketov.

Razumevanje predpomnilnika in dnevnikov
---------------------------------------

Symfony2 je verjetno eno najhitrejših celotnih ogrodij naokrog. Vendar kako
je lahko tako hitro, če pa razčlenjuje in interpretira desetine YAML in XML datotek
za vsak zahtevek? Hitros je delno zaradi njegovega sistema predpomnilnika. Aplikacijske
nastavitve so samo razčlenjene za prvi zahtevek in potem prevedene v enostavno
PHP kodo shranjeno v ``app/cache`` direktoriju. V razvojnem okolju je Symfony2 dovolj
pameten, da sprazni predpomnilnik, ko spremenite datoteko. Vendar v produkcijskem okolju,
je vaša dolžnost, da počistite predpomnilnik, ko posodobite vašo kodo ali spremenite njene
nastavitve.

Ko razvijate spletno aplikacijo, gredo stvari lahko narobe v mmnogih pogledih. Dnevniške
datoteke v ``app/logs/`` direktoriju vam povedo vse o zahtevkih in vam hitro pomagajo
popraviti problem.

Uporaba vmesnika ukazne vrstice
-------------------------------

Vsaka aplikacija pride z orodjem vmesnika ukazne vrstive (``app/console``)
kar vam pomaga vzdrževati vašo aplikacijo. Ponuja ukaze, ki pohitrijo vašo
produktivnost z avtomatizacijo dolgočasnih in ponovljivih nalog.

Poženite brez kakršnih koli argumentov, da izveste več o njenih zmožnostih:

.. code-block:: bash

    $ php app/console

Opcija ``--help`` vam pomaga odkriti uporabo ukaza:

.. code-block:: bash

    $ php app/console router:debug --help

Zaključne misli
---------------

Recite, da sem nor, vendar po prebranju tega dela, bi vam moralo biti že udobno
s premikanjem stvari okrog in narediti, da Symfony dela za vas. Vse v Symfony2
je načrtovano, da vam ne hodi v napoto. Torej, imejte proste roke pri preimenovanju,
premikanju direktorijev okoli, da bo ustrezno.

In to je vse za hiter pregled. Iz testiranja do pošiljanja mailov, se morate še vedno
naučiti veliko, da postanete Symfony2 mojster. Pripravljeni, da se zakopljete v te teme
zdaj? Ne glejte več - pojdite na uradno :doc:`/book/index` in izberite katerokoi
temo želite.

.. _standards:  http://symfony.com/PSR0
.. _convention: http://pear.php.net/
.. _Composer:   http://getcomposer.org
.. _`Composer-Autoloader`: http://getcomposer.org/doc/01-basic-usage.md#autoloading
