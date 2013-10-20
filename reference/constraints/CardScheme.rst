CardScheme
==========

.. versionadded:: 2.2
    Preverjanje CardScheme je novo v Symfony 2.2.

Ta omejitev zagotavlja, da je številka kreditne kartice veljavna za dano podjetje kreditne
kartice. Lahko je uporabljena za preverjanje številke preden se poskuša narediti plačilo
skozi plačilni prehod.

+----------------+--------------------------------------------------------------------------+
| Nanaša se na   | :ref:`lastnost ali metodo <validation-property-target>`                  |
+----------------+--------------------------------------------------------------------------+
| Opcije         | - `schemes`_                                                             |
|                | - `message`_                                                             |
+----------------+--------------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Validator\\Constraints\\CardScheme`          |
+----------------+--------------------------------------------------------------------------+
| Validator      | :class:`Symfony\\Component\\Validator\\Constraints\\CardSchemeValidator` |
+----------------+--------------------------------------------------------------------------+

Osnovna uporaba
---------------

Da uporabite ``CardScheme`` preverjanje, ga enostavno uporabite na lastnosti ali metodi
objekta, ki bo vseboval številko kreditne kartice.

.. configuration-block::

    .. code-block:: yaml

        # src/Acme/SubscriptionBundle/Resources/config/validation.yml
        Acme\SubscriptionBundle\Entity\Transaction:
            properties:
                cardNumber:
                    - CardScheme:
                        schemes: [VISA]
                        message: Your credit card number is invalid.

    .. code-block:: xml

        <!-- src/Acme/SubscriptionBundle/Resources/config/validation.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <constraint-mapping xmlns="http://symfony.com/schema/dic/constraint-mapping"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/dic/constraint-mapping http://symfony.com/schema/dic/constraint-mapping/constraint-mapping-1.0.xsd">

            <class name="Acme\SubscriptionBundle\Entity\Transaction">
                <property name="cardNumber">
                    <constraint name="CardScheme">
                        <option name="schemes">
                            <value>VISA</value>
                        </option>
                        <option name="message">Your credit card number is invalid.</option>
                    </constraint>
                </property>
            </class>
        </constraint-mapping>

    .. code-block:: php-annotations

        // src/Acme/SubscriptionBundle/Entity/Transaction.php
        namespace Acme\SubscriptionBundle\Entity\Transaction;
        
        use Symfony\Component\Validator\Constraints as Assert;

        class Transaction
        {
            /**
             * @Assert\CardScheme(schemes = {"VISA"}, message = "Your credit card number is invalid.")
             */
            protected $cardNumber;
        }

    .. code-block:: php

        // src/Acme/SubscriptionBundle/Entity/Transaction.php
        namespace Acme\SubscriptionBundle\Entity\Transaction;
        
        use Symfony\Component\Validator\Mapping\ClassMetadata;
        use Symfony\Component\Validator\Constraints as Assert;

        class Transaction
        {
            protected $cardNumber;

            public static function loadValidatorMetadata(ClassMetadata $metadata)
            {
                $metadata->addPropertyConstraint('cardNumber', new Assert\CardScheme(array(
                    'schemes' => array(
                        'VISA'
                    ),
                    'message' => 'Your credit card number is invalid.',
                )));
            }
        }

Opcije na voljo
---------------

schemes
-------

**tip**: ``mixed`` [:ref:`default option <validation-default-option>`]

Ta opcija je zahtevana in predstavlja ime uporabljene številske sheme za
preverjanje številke kreditne kartice, lahko je ali niz ali polje. Veljavne
vrednosti so:

* ``AMEX``
* ``CHINA_UNIONPAY``
* ``DINERS``
* ``DISCOVER``
* ``INSTAPAYMENT``
* ``JCB``
* ``LASER``
* ``MAESTRO``
* ``MASTERCARD``
* ``VISA``

Za več informacij o uporabljenih shemah, glejte `Wikipedia: Issuer identification number (IIN)`_.

message
~~~~~~~

**tip**: ``string`` **privzeto**: ``Unsupported card type or invalid card number``

Sporočilo prikazano, ko vrednost ne opravi ``CardScheme`` preverjanja.

.. _`Wikipedia: Issuer identification number (IIN)`: http://en.wikipedia.org/wiki/Bank_card_number#Issuer_identification_number_.28IIN.29
