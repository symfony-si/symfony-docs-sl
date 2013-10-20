.. index::
   single: Routing; Allow / in route parameter

Kako dovoliti znak poševnico "/" v parametru smeri
==================================================

Včasih potrebujete sestaviti URL s parametri, ki vsebujejo poševnico
``/``. Na primer, klasična ``/hello/{name}`` smer. Privzeto
``/hello/Fabien`` se bo ujela s to smerjo vendar ne pa ``/hello/Fabien/Kris``.
To je ker Symfony uporablja ta znak kot ločilo med deli smeri.

Ta vodič pokriva, kako lahko modificirate smer, da se bo ``/hello/Fabien/Kris``
ujela s smerjo ``/hello/{name}``, kjer je ``{name}`` enako ``Fabien/Kris``.

Nastavitve smeri
----------------

Privzeto, Symfony usmerjevalna komponenta zahteva, da se parametri ujemajo
sledeči regex poti: ``[^/]+``. To pomeni, da so dovoljeni vsi znaki razen
``/``.

Eksplicitno morate dovoliti, da je ``/`` del vašega parametra z določitvijo
bolj permisivne regex poti.

.. configuration-block::

    .. code-block:: yaml

        _hello:
            path:     /hello/{name}
            defaults: { _controller: AcmeDemoBundle:Demo:hello }
            requirements:
                name: ".+"

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>

        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="_hello" path="/hello/{name}">
                <default key="_controller">AcmeDemoBundle:Demo:hello</default>
                <requirement key="name">.+</requirement>
            </route>
        </routes>

    .. code-block:: php

        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('_hello', new Route('/hello/{name}', array(
            '_controller' => 'AcmeDemoBundle:Demo:hello',
        ), array(
            'name' => '.+',
        )));

        return $collection;

    .. code-block:: php-annotations

        use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;

        class DemoController
        {
            /**
             * @Route("/hello/{name}", name="_hello", requirements={"name" = ".+"})
             */
            public function helloAction($name)
            {
                // ...
            }
        }

To je vse! Sedaj lahko parameter ``{name}`` vsebuje znak ``/``.
