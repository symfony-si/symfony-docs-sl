.. index::
   single: Console; Sending emails
   single: Console; Generating URLs

Kako generirati URL-je in pošiljati e-pošto iz konzole
======================================================

Na žalost kontekst ukazne vrstice ne ve o vašem VirtualHost-u ali imenu
domene. To pomeni, da če generirate absolutne URL-je znotraj Console Command
boste najverjetneje končali z nečim kot je ``http://localhost/foo/bar``,
kar ni preveč uporabno.

Da to popravite, morate nastaviti kontekst zahtevka, kar je samo lep način,
da rečete, da potrebujete nastaviti vaše okolje tako, da ve kateri URL
bi moral biti uporabljen, ko se generira URL-je.

Na voljo sta dva načina nastavitve konteksta zahtevka: na nivoju aplikacije
in glede na ukaz.

Nastavitve konteksta zahtevka globalno
--------------------------------------

.. versionadded: 2.2
    Parameter ``base_url`` je na voljo od Symfony 2.2

Za nastavitev konteksta zahtevka - kar je uporabljeno s strani generatorja URL-jev -
lahko ponovno definirate parametre, ki jih uporablja kot privzete vrednosti za spremembo
privzetega gostitelja (localhost) in sheme (http). Od Symfony 2.2 lahko tudi nastavite
osnovno pot, če se Symfony ne poganja znotraj vrhnjega direktorija.

Upoštevajte, da to ne vpliva na generirane URL-je preko običajnih spletnih zahtevko, saj bodo
le-te prepisali privzeto.

.. configuration-block::

    .. code-block:: yaml

        # app/config/parameters.yml
        parameters:
            router.request_context.host: example.org
            router.request_context.scheme: https
            router.request_context.base_url: my/path

    .. code-block:: xml

        <!-- app/config/parameters.xml -->
        <?xml version="1.0" encoding="UTF-8"?>

        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance">

            <parameters>
                <parameter key="router.request_context.host">example.org</parameter>
                <parameter key="router.request_context.scheme">https</parameter>
                <parameter key="router.request_context.base_url">my/path</parameter>
            </parameters>
        </container>

    .. code-block:: php

        // app/config/config_test.php
        $container->setParameter('router.request_context.host', 'example.org');
        $container->setParameter('router.request_context.scheme', 'https');
        $container->setParameter('router.request_context.base_url', 'my/path');

Nastavitve konteksta zahtevkov glede na ukaz
--------------------------------------------

Da ga spremenite samo v enem ukazu lahko enostavno ujamete storitev konteksta zahtevka
in prepišete njegove nastavitve::

   // src/Acme/DemoBundle/Command/DemoCommand.php

   // ...
   class DemoCommand extends ContainerAwareCommand
   {
       protected function execute(InputInterface $input, OutputInterface $output)
       {
           $context = $this->getContainer()->get('router')->getContext();
           $context->setHost('example.com');
           $context->setScheme('https');
           $context->setBaseUrl('my/path');

           // ... your code here
       }
   }

Uporaba spomina v ozadju
------------------------

Pošiljanje e-pošte v konzolnem ukazu deluje na enak način, kot je opisano v
:doc:`/cookbook/email/email` receptu, razen če je uporabljen spomin v ozadju.

Ko uporabljate spomin v ozadju (memory spooling) (glejte :doc:`/cookbook/email/spool` recept
za več informacij), se morate zavedati, da kako Symfony ravna z konzolnimi ukazi,
e-pošta ni avtomatsko poslana. Sami morate poskrbeti za praznenje čakalne vrste.
Uporabite sledečo kodo za pošiljanje e-pošte znotraj vašega konzolnega ukaza::

    $container = $this->getContainer();
    $mailer = $container->get('mailer');
    $spool = $mailer->getTransport()->getSpool();
    $transport = $container->get('swiftmailer.transport.real');

    $spool->flushQueue($transport);

Druga opcija je izdelava okolja, ki je uporabljeno samo s strani konzolnih
ukazov in uporablja različne metode odvijanja v ozadju.

.. note::

    Skrb za odvijanje v ozadju je potrebno samo, ko je uporabljen spomin v ozadju
    Če uporabljate datoteke v ozadju (ali nobenega odvijanja v ozadju), ni potrebe
    po praznenju čakalne vrste ročno znotraj ukaza.
