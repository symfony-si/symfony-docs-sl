.. index::
    single: Configuration reference; Swift Mailer

Nastavitve za SwiftmailerBundle ("swiftmailer")
===============================================

Ta referenčni dokument je delo v teku. Moral bi biti točen, vendar
vse opcije niso še v celoti pokrite. Za celoten seznam privzetih opcij
nastavitev, glejte `Celotne privzete nastavitve`_

Ključ ``swiftmailer`` nastavlja Symfoyn-jevo integracijo s Swift Mailer,
ki je odgovorna za izdelavo in dostavo e-pošnih sporočil.

Sledeča sekcija govori o vseh opcijah, ki so na voljo za nastavitev
mailer-ja. Možno je tudi nastaviti več mailer-jev (glejte `Uporaba večih Mailer-jev`_).

Nastavitve
----------

* `transport`_
* `username`_
* `password`_
* `host`_
* `port`_
* `encryption`_
* `auth_mode`_
* `spool`_
    * `type`_
    * `path`_
* `sender_address`_
* `antiflood`_
    * `threshold`_
    * `sleep`_
* `delivery_address`_
* `disable_delivery`_
* `logging`_

transport
~~~~~~~~~

**tip**: ``string`` **privzeto**: ``smtp``

Točna transportna metoda za uporabo dostave e-pošte. Veljavne vrednosti so:

* smtp
* gmail (glejte :doc:`/cookbook/email/gmail`)
* mail
* sendmail
* null (enako kot nastaviti `disable_delivery`_ na ``true``)

username
~~~~~~~~

**tip**: ``string``

Uporabniško ime, ko se uporablja ``smtp`` kot transport.

password
~~~~~~~~

**tip**: ``string``

Geslo, ko se uporablja ``smtp`` kot transport.

host
~~~~

**tip**: ``string`` **privzeto**: ``localhost``

Gostitelj za povezavo, ko se uporablja ``smtp`` kot transport.

port
~~~~

**tip**: ``string`` **privzeto**: 25 ali 465 (odvisno od `encryption`_)

Port, ko se uporablja ``smtp`` kot transport. To je privzeto na 465 če je enkripcija
``ssl`` ali drugače 25.

encryption
~~~~~~~~~~

**tip**: ``string``

Način enkripcije, ko se uporablja ``smtp`` kot transport. Veljavne vrednosti
so ``tls``, ``ssl``, ali ``null`` (nakazuje, da ni enkripcije).

auth_mode
~~~~~~~~~

**tip**: ``string``

Način preverjanja pristnosti, ko se uporablja ``smtp`` kot transport. Veljavne
vrednosti so ``plain``, ``login``, ``cram-md5``, ali ``null``.

spool
~~~~~

Za podrobnosti glede e-poštnega spooling-a, glejte :doc:`/cookbook/email/spool`.

type
....

**tip**: ``string`` **privzeto**: ``file``

Metoda uporabljena za zhranjevanje "spooled" sporočil. Veljavne vrednosti sta ``memory`` in
``file``. Možen je spool po meri z izdelavo storitve
``swiftmailer.spool.myspool`` in nastavitve te vrednosti na ``myspool``.

path
....

**tip**: ``string`` **privzeto**: ``%kernel.cache_dir%/swiftmailer/spool``

Ko se uporablja ``file`` spool, je to pot, kjer so spooled sporočila shranjena.

sender_address
~~~~~~~~~~~~~~

**tip**: ``string``

Če je nastavljen, bodo vsa sporočila dostavljena s tem naslovom kot "return path"
naslov, kamor morajo iti odbita (bounced) sporočila. To je ravnano interno
s Swift Mailer-jevim razredom ``Swift_Plugins_ImpersonatePlugin``.

antiflood
~~~~~~~~~

threshold
.........

**tip**: ``string`` **privzeto**: ``99``

Uporabljeno s ``Swift_Plugins_AntiFloodPlugin``. To je število sporočil za poslati
preden se transport ponovno zažene.

sleep
.....

**tip**: ``string`` **privzeto**: ``0``

Uporabljeno s ``Swift_Plugins_AntiFloodPlugin``. To je število sekund
za spanje med ponovnim zagonom transporta.

delivery_address
~~~~~~~~~~~~~~~~

**tip**: ``string``

Če je nastavljen, vsa e-poštna sporočila bodo poslana na ta naslov namesto, da
se pošljejo na njihove dejanske prejemnike. To je pogosto uporabno, ko se razvija.
Na primer z nastavitvijo tega v datoteki ``config_dev.yml``, lahko garantirate, da
e-pošta poslana med razvojem gre na en račun.

To uporablja ``Swift_Plugins_RedirectingPlugin``. Originalni prejemniki so na voljo
v ``X-Swift-To``, ``X-Swift-Cc`` in ``X-Swift-Bcc`` glavah.

disable_delivery
~~~~~~~~~~~~~~~~

**tip**: ``Boolean`` **privzeto**: ``false``

Če je true, bo ``transport`` avtomatsko nastavljen na ``null`` in nobena e-poštna
sporočila dejansko ne bodo dostavljena.

logging
~~~~~~~

**tip**: ``Boolean`` **privzeto**: ``%kernel.debug%``

Če je true, bo Symfony-jev zbirnik podatkov aktiviran za Swift Mailer in
informacije na voljo v profiler-ju.

Celotne privzete nastavitve
---------------------------

.. configuration-block::

    .. code-block:: yaml

        swiftmailer:
            transport:            smtp
            username:             ~
            password:             ~
            host:                 localhost
            port:                 false
            encryption:           ~
            auth_mode:            ~
            spool:
                type:                 file
                path:                 "%kernel.cache_dir%/swiftmailer/spool"
            sender_address:       ~
            antiflood:
                threshold:            99
                sleep:                0
            delivery_address:     ~
            disable_delivery:     ~
            logging:              "%kernel.debug%"

    .. code-block:: xml

        <swiftmailer:config
            transport="smtp"
            username=""
            password=""
            host="localhost"
            port="false"
            encryption=""
            auth_mode=""
            sender_address=""
            delivery_address=""
            disable_delivery=""
            logging="%kernel.debug%"
        >
            <swiftmailer:spool
                path="%kernel.cache_dir%/swiftmailer/spool"
                type="file"
            />

            <swiftmailer:antiflood
                sleep="0"
                threshold="99"
            />
        </swiftmailer:config>

Uporaba večih Mailer-jev
------------------------

Lahko tudi nastavite več mailer-jev z njihovim grupiranjem po ključ
``mailers`` (privzeti mailer je identificiran po opciji ``default_mailer``):

.. configuration-block::

    .. code-block:: yaml

        swiftmailer:
            default_mailer: second_mailer
            mailers:
                first_mailer:
                    # ...
                second_mailer:
                    # ...

    .. code-block:: xml

        <?xml version="1.0" encoding="UTF-8" ?>
        <container xmlns="http://symfony.com/schema/dic/services"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:swiftmailer="http://symfony.com/schema/dic/swiftmailer"
            xsi:schemaLocation="http://symfony.com/schema/dic/services
                http://symfony.com/schema/dic/services/services-1.0.xsd
                http://symfony.com/schema/dic/swiftmailer
                http://symfony.com/schema/dic/swiftmailer/swiftmailer-1.0.xsd"
        >
            <swiftmailer:config default-mailer="second_mailer">
                <swiftmailer:mailer name="first_mailer"/>
                <swiftmailer:mailer name="second_mailer"/>
            </swiftmailer:config>
        </container>

    .. code-block:: php

        $container->loadFromExtension('swiftmailer', array(
            'default_mailer' => 'second_mailer',
            'mailers' => array(
                'first_mailer' => array(
                    // ...
                ),
                'second_mailer' => array(
                    // ...
                ),
            ),
        ));

Vsak mailer je registriran kot storitev:

    // ...

    // returns the first mailer
    $container->get('swiftmailer.mailer.first_mailer');

    // also returns the second mailer since it is the default mailer
    $container->get('swiftmailer.mailer');

    // returns the second mailer
    $container->get('swiftmailer.mailer.second_mailer');
