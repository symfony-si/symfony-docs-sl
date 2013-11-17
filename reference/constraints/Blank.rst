Blank
=====

Preveri, da je vrednost prazna, definirano kot enako praznemu nizi ali enako
``null``. Da se vsili, da je vrednost striktno enaka ``null``, glejte omejitev
:doc:`/reference/constraints/Null`. Da se vsili, da vrednost *ni*
prazna, glejte :doc:`/reference/constraints/NotBlank`.

+----------------+-----------------------------------------------------------------------+
| Nanaša se na   | :ref:`lastnost ali metodo <validation-property-target>`               |
+----------------+-----------------------------------------------------------------------+
| Opcije         | - `message`_                                                          |
+----------------+-----------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Validator\\Constraints\\Blank`            |
+----------------+-----------------------------------------------------------------------+
| Validator      | :class:`Symfony\\Component\\Validator\\Constraints\\BlankValidator`   |
+----------------+-----------------------------------------------------------------------+

Osnovna uporaba
---------------

Če zaradi kakšnega razloga želite zagotoviti, da je lastnost ``firstName``
razreda ``Author`` prazna, lahko naredite sledeče:

.. configuration-block::

    .. code-block:: yaml

        # src/BlogBundle/Resources/config/validation.yml
        Acme\BlogBundle\Entity\Author:
            properties:
                firstName:
                    - Blank: ~

    .. code-block:: php-annotations

        // src/Acme/BlogBundle/Entity/Author.php
        namespace Acme\BlogBundle\Entity;

        use Symfony\Component\Validator\Constraints as Assert;

        class Author
        {
            /**
             * @Assert\Blank()
             */
            protected $firstName;
        }

    .. code-block:: xml

        <!-- src/Acme/BlogBundle/Resources/config/validation.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <constraint-mapping xmlns="http://symfony.com/schema/dic/constraint-mapping"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/dic/constraint-mapping http://symfony.com/schema/dic/constraint-mapping/constraint-mapping-1.0.xsd">

            <class name="Acme\BlogBundle\Entity\Author">
                <property name="firstName">
                    <constraint name="Blank" />
                </property>
            </class>
        </constraint-mapping>

    .. code-block:: php

        // src/Acme/BlogBundle/Entity/Author.php
        namespace Acme\BlogBundle\Entity;

        use Symfony\Component\Validator\Mapping\ClassMetadata;
        use Symfony\Component\Validator\Constraints as Assert;

        class Author
        {
            public static function loadValidatorMetadata(ClassMetadata $metadata)
            {
                $metadata->addPropertyConstraint('firstName', new Assert\Blank());
            }
        }

Opcije
------

message
~~~~~~~

**tip**: ``string`` **privzeto**: ``This value should be blank.``

To je sporočilo, ki bo prikazano, če vrednost ni prazna.
