SensioGeneratorBundle
=====================

``SensioGeneratorBundle`` razširja privzeti vmesnik ukazne vrstice Symfony2
s ponujanjem novih interaktivnih in intiutivnih ukazov za generiranje
skeletov kode, kot so paketi, razredi obrazcev ali krmilniki CRUD na osnovi
sheme Doctrine 2.

Namestitev
----------

Preden uporabo paketa v vašem projektu, ga dodajte v vašo datoteko ``composer.json``:

.. code-block:: bash

    $ composer require sensio/generator-bundle

Potem ga, kot za vsak paket, vključite v vaš razred Kernel::

    public function registerBundles()
    {
        $bundles = array(
            ...

            new Sensio\Bundle\GeneratorBundle\SensioGeneratorBundle(),
        );

        ...
    }

Seznam ukazov, ki so na voljo
-----------------------------

``SensioGeneratorBundle`` prihaja s štirimi novimi ukazi, ki se jih lahko požene v
interaktivnem načinu ali ne. Interaktivni način vas vpraša nekaj vprašanj za
nastavitev parametrov ukaza za generiranje definitivne kode. Seznam
novih ukazov je izpisan spodaj:

.. toctree::
   :maxdepth: 1

   commands/generate_bundle
   commands/generate_controller
   commands/generate_doctrine_crud
   commands/generate_doctrine_entity
   commands/generate_doctrine_form

.. _Prenesite: http://github.com/sensio/SensioGeneratorBundle

Prepis skeletnih predlog
------------------------

.. versionadded:: 2.3
  Možnost prepisa skeletnih predlog je bila dodana v 2.3.

Vsi generatorji uporabljajo skeletno predlogo za generiranje datotek. Privzeto
ukazi uporabljajo predloge ponujene s strani paketa pod njenim direktorijem
``Resources/skeleton``.

Lahko definirate skelet po meri z izdelavo enake strukture direktorijev in
datotek v ``APP_PATH/Resources/SensioGeneratorBundle/skeleton`` ali
``BUNDLE_PATH/Resources/SensioGeneratorBundle/skeleton``, če želite razširiti
paket generator (da je na primer sposoben deliti vaše datoteke v
večih projektih).

Na primer, če želite prepisati predlogo ``edit`` za generator
CRUD, ustvarite datoteko ``crud/views/edit.html.twig.twig`` pod
``APP_PATH/Resources/SensioGeneratorBundle/skeleton``.

Ko prepisujete predlogo, poglejte v privzete predloge, da izveste več
o predlogah, ki so na voljo, njihovih poteh in spremenljivkah, do katerih imajo dostop.

Namesto kopiranja/prilepljanja originalne predloge, da ustvarite vašo lastno, jo lahko tudi
razširite in samo prepišete relevantne dele:

.. code-block:: jinja

  {# in app/Resources/SensioGeneratorBundle/skeleton/crud/actions/create.php.twig #}

  {# notice the "skeleton" prefix here -- more about it below #}
  {% extends "skeleton/crud/actions/create.php.twig" %}

  {% block phpdoc_header %}
       {{ parent() }}
       *
       * This is going to be inserted after the phpdoc title
       * but before the annotations.
  {% endblock phpdoc_header %}

Kompleksne predloge v privzetem skeletonu so razdeljene v bloke Twig, da omogočajo
enostavno dedovanje in se izognete kopiranju/prilepljanje velikih kosov kode.

V nekaterih primerih predloge v skeletu vključujejo druge, kot
v predlogi ``crud/views/edit.html.twig.twig`` na primer:

.. code-block:: jinja

  {% include 'crud/views/others/record_actions.html.twig.twig' %}

Če ste definirali predlogo po meri za to predlogo, bo
uporabljena namesto privzete. Vendar lahko eksplicitno vključite originalni
skelet predloge z dodajanjem predpone njeni poti s ``skeleton/`` kot smo naredili zgoraj:

.. code-block:: jinja

  {% include 'skeleton/crud/views/others/record_actions.html.twig.twig' %}

Lahko se naučite več o tem lepem "triku" v uradni `dokumentaciji Twig
<http://twig.sensiolabs.org/doc/recipes.html#overriding-a-template-that-also-extends-itself>`_.
