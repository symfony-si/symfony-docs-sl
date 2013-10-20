All
===

Ko je uporabljeno na polju (ali objektu Traversable), vam ta omejitev omogoča
uporabiti zbirko omejitev na vsakem elementu polja.

+----------------+------------------------------------------------------------------------+
| Nanaša se na   | :ref:`lastnost ali metodo <validation-property-target>`                |
+----------------+------------------------------------------------------------------------+
| Opcije         | - `constraints`_                                                       |
+----------------+------------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Validator\\Constraints\\All`               |
+----------------+------------------------------------------------------------------------+
| Validator      | :class:`Symfony\\Component\\Validator\\Constraints\\AllValidator`      |
+----------------+------------------------------------------------------------------------+

Osnovna uporaba
---------------

Predvidevajmo, da imate polje z nizi in želite preveriti vsak
vnos v tem polju:

.. configuration-block::

    .. code-block:: yaml

        # src/UserBundle/Resources/config/validation.yml
        Acme\UserBundle\Entity\User:
            properties:
                favoriteColors:
                    - All:
                        - NotBlank:  ~
                        - Length:
                            min: 5

    .. code-block:: php-annotations

        // src/Acme/UserBundle/Entity/User.php
        namespace Acme\UserBundle\Entity;
        
        use Symfony\Component\Validator\Constraints as Assert;
  
        class User
        {
            /**
             * @Assert\All({
             *     @Assert\NotBlank,
             *     @Assert\Length(min = "5")
             * })
             */
             protected $favoriteColors = array();
        }

    .. code-block:: xml

        <!-- src/Acme/UserBundle/Resources/config/validation.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <constraint-mapping xmlns="http://symfony.com/schema/dic/constraint-mapping"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/dic/constraint-mapping http://symfony.com/schema/dic/constraint-mapping/constraint-mapping-1.0.xsd">

            <class name="Acme\UserBundle\Entity\User">
                <property name="favoriteColors">
                    <constraint name="All">
                        <option name="constraints">
                            <constraint name="NotBlank" />
                            <constraint name="Length">
                                <option name="min">5</option>
                            </constraint>
                        </option>
                    </constraint>
                </property>
            </class>
        </constraint-mapping>

    .. code-block:: php

        // src/Acme/UserBundle/Entity/User.php
        namespace Acme\UserBundle\Entity;
       
        use Symfony\Component\Validator\Mapping\ClassMetadata;
        use Symfony\Component\Validator\Constraints as Assert;

        class User
        {
            public static function loadValidatorMetadata(ClassMetadata $metadata)
            {
                $metadata->addPropertyConstraint('favoriteColors', new Assert\All(array(
                    'constraints' => array(
                        new Assert\NotBlank(),
                        new Assert\Length(array('min' => 5)),
                    ),
                )));
            }
        }

Sedaj bo vsak vnos v ``favoriteColors`` polju preverjen, da ni
prazen in da je dolg vsaj 5 znakov.

Opcije
------

constraints
~~~~~~~~~~~

**tip**: ``array`` [:ref:`default option <validation-default-option>`]

Ta zahtevana opcija je polje omejitev potrjevanj, ki jih želite
uporabiti na vsakem elementu osnovnega polja.
