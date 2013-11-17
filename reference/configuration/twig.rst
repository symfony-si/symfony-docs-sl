.. index::
   pair: Twig; Configuration reference

Nastavitve za TwigBundle ("twig")
=================================

.. configuration-block::

    .. code-block:: yaml

        twig:
            exception_controller:  twig.controller.exception:showAction
            form:
                resources:

                    # Default:
                    - form_div_layout.html.twig

                    # Example:
                    - MyBundle::form.html.twig
            globals:

                # Examples:
                foo:                 "@bar"
                pi:                  3.14

                # Example options, but the easiest use is as seen above
                some_variable_name:
                    # a service id that should be the value
                    id:                   ~
                    # set to service or leave blank
                    type:                 ~
                    value:                ~
            autoescape:                ~

            # The following were added in Symfony 2.3.
            # See http://twig.sensiolabs.org/doc/recipes.html#using-the-template-name-to-set-the-default-escaping-strategy
            autoescape_service:        ~ # Example: @my_service
            autoescape_service_method: ~ # use in combination with autoescape_service option
            base_template_class:       ~ # Example: Twig_Template
            cache:                     "%kernel.cache_dir%/twig"
            charset:                   "%kernel.charset%"
            debug:                     "%kernel.debug%"
            strict_variables:          ~
            auto_reload:               ~
            optimizations:             ~

    .. code-block:: xml

        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:twig="http://symfony.com/schema/dic/twig"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd
                                http://symfony.com/schema/dic/twig http://symfony.com/schema/dic/doctrine/twig-1.0.xsd">

            <twig:config auto-reload="%kernel.debug%" autoescape="true" base-template-class="Twig_Template" cache="%kernel.cache_dir%/twig" charset="%kernel.charset%" debug="%kernel.debug%" strict-variables="false">
                <twig:form>
                    <twig:resource>MyBundle::form.html.twig</twig:resource>
                </twig:form>
                <twig:global key="foo" id="bar" type="service" />
                <twig:global key="pi">3.14</twig:global>
            </twig:config>
        </container>

    .. code-block:: php

        $container->loadFromExtension('twig', array(
            'form' => array(
                'resources' => array(
                    'MyBundle::form.html.twig',
                )
             ),
             'globals' => array(
                 'foo' => '@bar',
                 'pi'  => 3.14,
             ),
             'auto_reload'         => '%kernel.debug%',
             'autoescape'          => true,
             'base_template_class' => 'Twig_Template',
             'cache'               => '%kernel.cache_dir%/twig',
             'charset'             => '%kernel.charset%',
             'debug'               => '%kernel.debug%',
             'strict_variables'    => false,
        ));

Nastavitve
----------

.. _config-twig-exception-controller:

exception_controller
....................

**type**: ``string`` **default**: ``twig.controller.exception:showAction``

To je krmilnik, ki je aktiviran, ko je vrnjena izjema kjerkoli
v vaši aplikaiji. Privzeti krmilnik
(:class:`Symfony\\Bundle\\TwigBundle\\Controller\\ExceptionController`)
je kar je odgovorno za izpisovanje določenih predlog pod različnimi pogoji
napak (glejte :doc:`/cookbook/controller/error_pages`). Spreminjanje te
opcije je napredno. Če potrebujete prilagoditi stran z napakami, bi morali
uporabiti prejšnjo povezavo. Če potrebujete opraviti nekaj obnašanja izjeme,
bi morali dodati t.i. "listener" v ``kernel.exception`` dogodek (glejte :ref:`dic-tags-kernel-event-listener`).
