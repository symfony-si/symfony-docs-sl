.. index::
   single: Security; Configuration reference

Referenca za nastavitve varnosti
================================

Varnostni sistem je eden najmočnejših delov Symfony2 in je lahko
večinoma kontroliran preko njegovih nastavitev.

Celotne privzete nastavitve
---------------------------

Spodaj so celotne privzete nastavitve za varnostni sistem.
Vsak del bo razložen v naslednji sekciji.

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            access_denied_url:    ~ # Example: /foo/error403

            # strategy can be: none, migrate, invalidate
            session_fixation_strategy:  migrate
            hide_user_not_found:  true
            always_authenticate_before_granting:  false
            erase_credentials:    true
            access_decision_manager:
                strategy:             affirmative
                allow_if_all_abstain:  false
                allow_if_equal_granted_denied:  true
            acl:

                # any name configured in doctrine.dbal section
                connection:           ~
                cache:
                    id:                   ~
                    prefix:               sf2_acl_
                provider:             ~
                tables:
                    class:                acl_classes
                    entry:                acl_entries
                    object_identity:      acl_object_identities
                    object_identity_ancestors:  acl_object_identity_ancestors
                    security_identity:    acl_security_identities
                voter:
                    allow_if_object_identity_unavailable:  true

            encoders:
                # Examples:
                Acme\DemoBundle\Entity\User1: sha512
                Acme\DemoBundle\Entity\User2:
                    algorithm:           sha512
                    encode_as_base64:    true
                    iterations:          5000

                # PBKDF2 encoder
                # see the note about PBKDF2 below for details on security and speed
                Acme\Your\Class\Name:
                    algorithm:            pbkdf2
                    hash_algorithm:       sha512
                    encode_as_base64:     true
                    iterations:           1000

                # Example options/values for what a custom encoder might look like
                Acme\DemoBundle\Entity\User3:
                    id:                   my.encoder.id

            providers:            # Required
                # Examples:
                my_in_memory_provider:
                    memory:
                        users:
                            foo:
                                password:           foo
                                roles:              ROLE_USER
                            bar:
                                password:           bar
                                roles:              [ROLE_USER, ROLE_ADMIN]

                my_entity_provider:
                    entity:
                        class:              SecurityBundle:User
                        property:           username
                        manager_name:       ~

                # Example custom provider
                my_some_custom_provider:
                    id:                   ~

                # Chain some providers
                my_chain_provider:
                    chain:
                        providers:          [ my_in_memory_provider, my_entity_provider ]

            firewalls:            # Required
                # Examples:
                somename:
                    pattern: .*
                    request_matcher: some.service.id
                    access_denied_url: /foo/error403
                    access_denied_handler: some.service.id
                    entry_point: some.service.id
                    provider: some_key_from_above
                    # manages where each firewall stores session information
                    # See "Firewall Context" below for more details
                    context: context_key
                    stateless: false
                    x509:
                        provider: some_key_from_above
                    http_basic:
                        provider: some_key_from_above
                    http_digest:
                        provider: some_key_from_above
                    form_login:
                        # submit the login form here
                        check_path: /login_check

                        # the user is redirected here when he/she needs to log in
                        login_path: /login

                        # if true, forward the user to the login form instead of redirecting
                        use_forward: false

                        # login success redirecting options (read further below)
                        always_use_default_target_path: false
                        default_target_path:            /
                        target_path_parameter:          _target_path
                        use_referer:                    false

                        # login failure redirecting options (read further below)
                        failure_path:    /foo
                        failure_forward: false
                        failure_path_parameter: _failure_path
                        failure_handler: some.service.id
                        success_handler: some.service.id

                        # field names for the username and password fields
                        username_parameter: _username
                        password_parameter: _password

                        # csrf token options
                        csrf_parameter: _csrf_token
                        intention:      authenticate
                        csrf_provider:  my.csrf_provider.id

                        # by default, the login form *must* be a POST, not a GET
                        post_only:      true
                        remember_me:    false

                        # by default, a session must exist before submitting an authentication request
                        # if false, then Request::hasPreviousSession is not called during authentication
                        # new in Symfony 2.3
                        require_previous_session: true

                    remember_me:
                        token_provider: name
                        key: someS3cretKey
                        name: NameOfTheCookie
                        lifetime: 3600 # in seconds
                        path: /foo
                        domain: somedomain.foo
                        secure: false
                        httponly: true
                        always_remember_me: false
                        remember_me_parameter: _remember_me
                    logout:
                        path:   /logout
                        target: /
                        invalidate_session: false
                        delete_cookies:
                            a: { path: null, domain: null }
                            b: { path: null, domain: null }
                        handlers: [some.service.id, another.service.id]
                        success_handler: some.service.id
                    anonymous: ~

                # Default values and options for any firewall
                some_firewall_listener:
                    pattern:              ~
                    security:             true
                    request_matcher:      ~
                    access_denied_url:    ~
                    access_denied_handler:  ~
                    entry_point:          ~
                    provider:             ~
                    stateless:            false
                    context:              ~
                    logout:
                        csrf_parameter:       _csrf_token
                        csrf_provider:        ~
                        intention:            logout
                        path:                 /logout
                        target:               /
                        success_handler:      ~
                        invalidate_session:   true
                        delete_cookies:

                            # Prototype
                            name:
                                path:                 ~
                                domain:               ~
                        handlers:             []
                    anonymous:
                        key:                  4f954a0667e01
                    switch_user:
                        provider:             ~
                        parameter:            _switch_user
                        role:                 ROLE_ALLOWED_TO_SWITCH

            access_control:
                requires_channel:     ~

                # use the urldecoded format
                path:                 ~ # Example: ^/path to resource/
                host:                 ~
                ip:                   ~
                methods:              []
                roles:                []
            role_hierarchy:
                ROLE_ADMIN:      [ROLE_ORGANIZER, ROLE_USER]
                ROLE_SUPERADMIN: [ROLE_ADMIN]

.. _reference-security-firewall-form-login:

Nastavitve prijavnega obrazca
-----------------------------

Ko se uporablja ``form_login`` "listener" za preverjanje pristnosti pod
požarnim zidom, je na voljo nekaj pogostih opcij za nastavitev "form login"
izkušnjo.

Za še več podrobnosti, glejte :doc:`/cookbook/security/form_login`.

Prijavni obrazec in proce
~~~~~~~~~~~~~~~~~~~~~~~~~

*   ``login_path`` (tip: ``string``, privzeto: ``/login``)
    To je smet ali pot, kamor bo uporabnik preusmerjen (razen če je
    ``use_forward`` nastavljen na ``true``) ko poskuša dostopati do
    varovanega vira, vendar ni v celoti prijavljen.

    Ta pot **mora** biti dostopna s strani običajnega, neprijavljenega uporabnika,
    drugače lahko naredite preusmeritveno zanko. Za podrobnosti, glejte
    ":ref:`Izognite se pogostim pastem <book-security-common-pitfalls>`".

*   ``check_path`` (tip: ``string``, privzeto: ``/login_check``)
    To je smer ali pot, na katero mora vaš prijavni obrazec poslati podatke. Požarni
    zid bo prestregel katerekoli zahtevke (samo ``POST`` zahtevki privzeto)
    za ta URL in procesiral poslane podatke prijavnih poverilnic.

    Bodite gotovi, da bo ta URL zajet s strani vašega glavnega požarnega zidu (to pomeni,
    da ne izdelujte ločenega požarnega zidu samo za URL ``check_path``)

*   ``use_forward`` (tip: ``Boolean``, privzeto: ``false``)
    Če bi želeli, da je uporabnik posredovan na prijavni obrazec namesto, da je
    preusmerjen, nastavite to opcijo na ``true``.

*   ``username_parameter`` (tip: ``string``, privzeto: ``_username``)
    To je ime polja, ki bi ga morali podati username polju vašega
    prijavnega obrazca. Ko pošljete obrazec na ``check_path``, bo
    varnostni sistem pogledal za parametrom POST s tem imenom.

*   ``password_parameter`` (tip: ``string``, privzeto: ``_password``)
    To je ime polja, ki bi ga morali dati polju geslo vašega prijavnega
    obrazca. Ko pošiljate obrazec na ``check_path``, bo varnostni
    sistem pogledal za parametrom POST s tem imenom.

*   ``post_only`` (tip: ``Boolean``, privzeto: ``true``)
    Privzeto bi morali poslati vaše prijavne podatke na ``check_path`` URL
    kot zahtevek POST. Z nastavitvijo te opcije na ``false``, lahko pošljete
    GET zahtevek na ``check_path`` URL.

Preusmeritev po prijavi
~~~~~~~~~~~~~~~~~~~~~~~

* ``always_use_default_target_path`` (tip: ``Boolean``, privzeto: ``false``)
* ``default_target_path`` (tip: ``string``, privzeto: ``/``)
* ``target_path_parameter`` (tip: ``string``, privzeto: ``_target_path``)
* ``use_referer`` (tip: ``Boolean``, privzeto: ``false``)

.. _reference-security-pbkdf2:

Uporaba enkoderja PBKDF2: Varnost in hitrost
--------------------------------------------

.. versionadded:: 2.2
    Enkoder gesel PBKDF2 je bil dodan v Symfony 2.2.

Enkoder `PBKDF2`_ ponuja visoko nivojsko kriptografsko varnost, kot je
priporočeno s strani Nacionalnega inštituta za standarde in tehnologijo -
National Institute of Standards and Technology (NIST).

Lahko pogledate primer enkoderja ``pbkdf2`` v YAML bloku na tej strani.

Vendar uporaba PBKDF tudi nalaga opozorilo: z njegovo uporabo (z velikim
število iteracij) upočasni proces. Zato bi PBKDF2 moral biti uporabljen
s previdnostjo in skrbnostjo.

Ustrezne nastavitve ležijo okrog vsaj 1000 iteracij in sha512
za njihov razpršilni algoritem.

.. _reference-security-bcrypt:

Uporaba enkoderja gesel BCrypt
------------------------------

.. caution::

    To use this encoder, you either need to use PHP Version 5.5 or install
    the `ircmaxell/password-compat`_ library via Composer.

.. versionadded:: 2.2
    The BCrypt password encoder was added in Symfony 2.2.

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...

            encoders:
                Symfony\Component\Security\Core\User\User:
                    algorithm: bcrypt
                    cost:      15

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <!-- ... -->
            <encoder
                class="Symfony\Component\Security\Core\User\User"
                algorithm="bcrypt"
                cost="15"
            />
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            // ...
            'encoders' => array(
                'Symfony\Component\Security\Core\User\User' => array(
                    'algorithm' => 'bcrypt',
                    'cost'      => 15,
                ),
            ),
        ));

Nastavitev ``cost`` je lahko v rangu med ``4-31`` in določa kako dolgo
bo geslo enkodirano. Vsak inkrement vrednosti ``cost`` *podvoji* čas, ki
je potreben za enkodiranje gesla.

Če ne ponudite opcije ``cost``, je privzeta uporabljena nastavitev ``13``.

.. note::

    Lahko spremenite nastavitev cost kadarkoli - tudi, če že imate nekaj
    gesel enkodiranih z uporabljeno drugačno nastavitvijo cost. Nova gesla
    bodo enkodirana z uporabo nove nastavitve cost, medtem ko že obstoječa
    bodo preverjana z uporabo nastavitve cost, ki je bila uporabljena pri
    enkodiranju.

Za vsako geslo se generira avtomatsko tudi t.i. salt in ne nujno pridobljeno.
Ker enkodirano geslo vsebuje "salt", ki je bila uporabljena pri njegovem
enkodiranju, je pridobivanje samega enkodiranega gesla dovolj.

.. note::

    Vsa enkodirana gesla so dolga ``60`` znakov, torej poskrbite, da je na voljo
    dovolj prostora za njihovo shranjevanje.

    .. _reference-security-firewall-context:

Contekst požarnega zidu
-----------------------

Večina aplikacij bo samo potrebovala en :ref:`požarni zid <book-security-firewalls>`.
Vendar če vaša aplikacija uporablja več požarnih zidov, boste opazili,
da če ste prijavljeni znotraj enega požarnega zidu, niste avtomatsko prijavljetni
v drugem. Z drugačnimi besedami, sistemi ne delijo skupnega "conteksta": vsak
požarni zdi se obnaša kot ločen varnostni sistem.

Čeprav, vsak požarni zid ima opcijski ključ ``context`` (ki je privzeto nastavljen
na ime požarnega zidu), ki je uporabljen ko se shranjuje in pridobiva varnostne
podatke v in iz seje. Če je ta ključ nastavljen na enako vrednost okrog
večih požarnih zidov, je lahko "context" dejansko deljen:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...

            firewalls:
                somename:
                    # ...
                    context: my_context
                othername:
                    # ...
                    context: my_context

    .. code-block:: xml

       <!-- app/config/security.xml -->
       <security:config>
          <firewall name="somename" context="my_context">
            <! ... ->
          </firewall>
          <firewall name="othername" context="my_context">
            <! ... ->
          </firewall>
       </security:config>

    .. code-block:: php

       // app/config/security.php
       $container->loadFromExtension('security', array(
            'firewalls' => array(
                'somename' => array(
                    // ...
                    'context' => 'my_context'
                ),
                'othername' => array(
                    // ...
                    'context' => 'my_context'
                ),
            ),
       ));

Preverjanje pristnosti HTTP-Digest
----------------------------------

Za uporabo preverjanja pristnosti HTTP-Digest boste morali ponuditi t.i. "realm" in ključ:

.. configuration-block::

   .. code-block:: yaml

      # app/config/security.yml
      security:
         firewalls:
            somename:
              http_digest:
               key: "a_random_string"
               realm: "secure-api"

   .. code-block:: xml

      <!-- app/config/security.xml -->
      <security:config>
         <firewall name="somename">
            <http-digest key="a_random_string" realm="secure-api" />
         </firewall>
      </security:config>

   .. code-block:: php

      // app/config/security.php
      $container->loadFromExtension('security', array(
           'firewalls' => array(
               'somename' => array(
                   'http_digest' => array(
                       'key'   => 'a_random_string',
                       'realm' => 'secure-api',
                   ),
               ),
           ),
      ));

.. _`PBKDF2`: http://en.wikipedia.org/wiki/PBKDF2
.. _`ircmaxell/password-compat`: https://packagist.org/packages/ircmaxell/password-compat
