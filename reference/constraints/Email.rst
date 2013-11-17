Email
=====

Preveri, da je vrednost veljavni e-poštni naslov. Osnovna vrednost je
vezana na niz preden se preverja.

+----------------+---------------------------------------------------------------------+
| Nanaša se na   | :ref:`lastnost ali metodo <validation-property-target>`             |
+----------------+---------------------------------------------------------------------+
| Opcije         | - `message`_                                                        |
|                | - `checkMX`_                                                        |
|                | - `checkHost`_                                                      |
+----------------+---------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Validator\\Constraints\\Email`          |
+----------------+---------------------------------------------------------------------+
| Validator      | :class:`Symfony\\Component\\Validator\\Constraints\\EmailValidator` |
+----------------+---------------------------------------------------------------------+

Osnovna uporaba
---------------

.. configuration-block::

    .. code-block:: yaml

        # src/BlogBundle/Resources/config/validation.yml
        Acme\BlogBundle\Entity\Author:
            properties:
                email:
                    - Email:
                        message: The email "{{ value }}" is not a valid email.
                        checkMX: true

    .. code-block:: php-annotations

        // src/Acme/BlogBundle/Entity/Author.php
        namespace Acme\BlogBundle\Entity;

        use Symfony\Component\Validator\Constraints as Assert;

        class Author
        {
            /**
             * @Assert\Email(
             *     message = "The email '{{ value }}' is not a valid email.",
             *     checkMX = true
             * )
             */
             protected $email;
        }

    .. code-block:: xml

        <!-- src/Acme/BlogBundle/Resources/config/validation.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <constraint-mapping xmlns="http://symfony.com/schema/dic/constraint-mapping"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/dic/constraint-mapping http://symfony.com/schema/dic/constraint-mapping/constraint-mapping-1.0.xsd">

            <class name="Acme\BlogBundle\Entity\Author">
                <property name="email">
                    <constraint name="Email">
                        <option name="message">The email "{{ value }}" is not a valid email.</option>
                        <option name="checkMX">true</option>
                    </constraint>
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
                $metadata->addPropertyConstraint('email', new Assert\Email(array(
                    'message' => 'The email "{{ value }}" is not a valid email.',
                    'checkMX' => true,
                )));
            }
        }

Opcije
------

message
~~~~~~~

**tip**: ``string`` **privzeto**: ``This value is not a valid email address.``

To sporočilo je prikazano, če osnoven podatek ni veljaven e-poštni naslov.

checkMX
~~~~~~~

**tip**: ``Boolean`` **privzeto**: ``false``

Če je true, potem bo uporabljena :phpfunction:`checkdnsrr` PHP funkcija za
preverjanje veljavnosti MX zapisa gostitelja dane e-pošte.

checkHost
~~~~~~~~~

**tip**: ``Boolean`` **privzeto**: ``false``

Če je true, potem bo :phpfunction:`checkdnsrr` PHP funkcija uporabljena za
preverjanje veljavnosti MX *ali* A *ali* AAAA zapisa gostitelja
dane e-pošte.
