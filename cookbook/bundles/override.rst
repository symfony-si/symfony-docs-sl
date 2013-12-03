.. index::
   single: Bundle; Inheritance

Kako povoziti katerikoli del paketa
===================================

Ta dokument je hitra referenca, kako povoziti različne dele
tretje osebnih paketov.

Predloge
--------

Za informacije kako povoziti predloge, glejte

* :ref:`overriding-bundle-templates`.
* :doc:`/cookbook/bundles/inheritance`

Usmerjanje
----------

Usmerjanje ni nikoli avtomatsko uvoženo v Symfony2. Če želite vključiti
usmeritve iz kateregakoli paketa, potem morajo biti ročno uvožene nekje iz
v vaši aplikaciji (npr. ``app/config/routing.yml``).

Najenostavnejši način, da "povozite" usmerjanje paketa je, da ga nikoli ne uvozite
sploh. Namesto uvoza usmerjanja tretje osebnega paketa enostavno kopirajte
datoteko usmerjanja v vašo aplikacijo, jo spremenite in jo uvozite.

Krmilniki
---------

Ob predpostavki, da vključeni tretje osebni paket uporablja krmilnike nepovezane s storitvami (kar
je skoraj vedno primer), lahko enostavno povozite krmilnike preko dedovanja
paketa. Za več infomracij, glejte :doc:`/cookbook/bundles/inheritance`.
Če je krmilnik storitev, glejte naslednjo sekcijo, kako ga povoziti.

Storitve & konfiguracija
------------------------

Da povozite/razširite storitev, sta na voljo dve opciji. Najprej lahko
nastavite parameter, ki drži ime razreda storitve v vaš lastni razred z njegovo
nastavitvijo v ``app/config/config/.yml``. To je seveda možno samo, če je ime razreda
definirano kot parameter v nastavitvah storitve paketa, ki vključuje
storitev. Na primer, da prepišete uporabljeni razred za Symfony-jevo storitev
``translator``, bi morali povoziti parameter ``translator.class``. Vedenje točnega
parametra za povoziti lahko vzame nekaj raziskovanja. Za translator je
parameter definiran in uporabljen v ``Resources/config/translation.xml`` datoteki
v jedru FrameworkBundle paketa:

.. configuration-block::

    .. code-block:: yaml

        # app/config/config.yml
        parameters:
            translator.class:      Acme\HelloBundle\Translation\Translator

    .. code-block:: xml

        <!-- app/config/config.xml -->
        <parameters>
            <parameter key="translator.class">Acme\HelloBundle\Translation\Translator</parameter>
        </parameters>

    .. code-block:: php

        // app/config/config.php
        $container->setParameter('translator.class', 'Acme\HelloBundle\Translation\Translator');

Naslednje, če razred ni na voljo kot parameter, boste želeli zagotoviti, da
je razred vedno prepisan, ko je vaš paket uporabljen, ali pa morate spremeniti
nekaj, kar presega samo ime razreda, bi morali uporabiti t.i. compiler pass::

    // src/Acme/DemoBundle/DependencyInjection/Compiler/OverrideServiceCompilerPass.php
    namespace Acme\DemoBundle\DependencyInjection\Compiler;

    use Symfony\Component\DependencyInjection\Compiler\CompilerPassInterface;
    use Symfony\Component\DependencyInjection\ContainerBuilder;

    class OverrideServiceCompilerPass implements CompilerPassInterface
    {
        public function process(ContainerBuilder $container)
        {
            $definition = $container->getDefinition('original-service-id');
            $definition->setClass('Acme\DemoBundle\YourService');
        }
    }

V tem primeru lovite definicijo storitve originalne storitve in nastavljate
njegovo ime razreda na vaš lastni razred.

Glejte :doc:`/cookbook/service_container/compiler_passes` za informacije kako uporabiti
compiler pass-e. Če želite narediti nekaj, kar presega samo povoziti razred -
kot je dodajanje klica metode - lahko samo uporabite compiler pass metodo.

Entitete in preslikanje entitet
-------------------------------

Zaradi načina, kako Doctrine deluje, ni možno prepisati preslikanja entitete
paketa. Vendar, če paket ponuja super razred preslikav (kot je
``User`` entiteta v FOSUserBundle), lahko povozite atribute in
asociacije. Izvedite več o tej lastnosti in njenih pomankljivostih v
`dokumentaciji Doctrine`_.

Obrazci
-------

Da povozite tip obrazca, mora biti registriran kot storitev (kar pomeni
da je označen kot "form.type"). Nato ga lahko povozite, kakor bi povozili katerokoli
storitev, kot je razloženo v poglavju `Storitve & konfiguracija`_. To bo seveda
delovalo samo, če je tip sklican po svojem aliasu namesto, da je instantiziran,
npr.::

    $builder->add('name', 'custom_type');

namesto tega::

    $builder->add('name', new CustomType());

.. _override-validation:

Potrjevanje meta podatkov
-------------------------

Symfony naloži vse nastavitvene datoteke potrjevanja iz vsakega paketa in
jih kombinira v eno potrditveno metadata drevo. To pomeni, da lahko
dodate nove omejitve lastnosti, vendar jih ne morete povoziti.

Da to povozite, mora imeti tretje osebni paket nastavitev za
:ref:`potrjevalne skupine <book-validation-validation-groups>`. Na primer
FOSUserBundle ima te nastavitve. Da izdelate svojo lastno potrjevanje, dodajte
omejitve v novo potrjevalno skupino:

.. configuration-block::

    .. code-block:: yaml

        # src/Acme/UserBundle/Resources/config/validation.yml
        Fos\UserBundle\Model\User:
            properties:
                plainPassword:
                    - NotBlank:
                        groups: [AcmeValidation]
                    - Length:
                        min: 6
                        minMessage: fos_user.password.short
                        groups: [AcmeValidation]

    .. code-block:: xml

        <!-- src/Acme/UserBundle/Resources/config/validation.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <constraint-mapping xmlns="http://symfony.com/schema/dic/constraint-mapping"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/dic/constraint-mapping http://symfony.com/schema/dic/constraint-mapping/constraint-mapping-1.0.xsd">

            <class name="Fos\UserBundle\Model\User">
                <property name="password">
                    <constraint name="Length">
                        <option name="min">6</option>
                        <option name="minMessage">fos_user.password.short</option>
                        <option name="groups">
                            <value>AcmeValidation</value>
                        </option>
                    </constraint>
                </property>
            </class>
        </constraint-mapping>

Sedaj, posodobite FOSUserBundle nastavitve, da uporablja vaše potrjevalne skupine
namesto originalnih.

.. _override-translations:

Prevodi
-------

Prevodi se ne tičejo paketov, vendar domen. To pomeni, da
lahko povozite prevode iz katerekoli datoteke prevodov, dokler je v
:ref:`pravilni domeni <using-message-domains>`.

.. caution::

    Zadnji prevod vedno zmaga. To pomeni, da potrebujete zagotoviti,
    da paket, ki vsebuje *vaše* prevode, je naložen za katerimkoli
    paketom, katerega prevode povozite. To je narejeno v ``AppKernel``.

    Datoteka, ki vedno zmaga, je tista, ki je dana v
    ``app/Resources/translations``, saj se te datoteke vedno naložijo zadnje.

.. _`dokumentaciji Doctrine`: http://docs.doctrine-project.org/projects/doctrine-orm/en/latest/reference/inheritance-mapping.html#overrides
