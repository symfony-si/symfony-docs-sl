.. index::
   single: Security

Varnost
=======

Varnost je proces v dveh korakih, katerega cilj je preprečiti uporabniku dostop
do vira, ki ga ne smel/a imeti.

V prvem koraku procesa varnostni sistem identificira, kdo uporabnik
je z zahtevkov, da uporabnik pošlje neke vrste identifikacijo. To se imenuje
**preverjanje pristnosti** in pomeni, da sistem poskuša ugotoviti, kdo
ste.

Enkrat ko sistem ve, kdo ste, je naslednji korak določitev, če bi
morali imeti dostop do danega vira. Ta del procesa se imenuje **avtorizacija**
in pomeni, da sistem preverja, da vidi, če imate privilegije za
izvedbo določene akcije.

.. image:: /images/book/security_authentication_authorization.png
   :align: center

Najboljši način učenja je, da videte primer, začnite z zavarovanjem vaše
aplikacije s HTTP osnovninm preverjanjem pristnosti.

.. note::

    :doc:`Symfony-jeva varnostna komponenta </components/security/introduction>` je
    na voljo kot samostoječa PHP knjižnica za uporabo znotraj katerega koli PHP projekta.

Osnovni primer: HTTP preverjanje pristnosti
-------------------------------------------

Varnostno komponento se lahko nastavi preko nastavitev vaše aplikacije.
V bistvu najbolj standardne varnostne nastavitve so samo vprašanje uporabe pravih
nastavitev. Sledeče nastavitve povejo Symfony-ju, da zavaruje katerikoli ULR,
ki se ujema z ``/admin/*`` in vpraša uporabnika za prijavne podatke z uporabo osnovnega HTTP
preverjanja pristnosti (t.j. staro šolski kvadratek z uporabniškim imenom in geslom):

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            firewalls:
                secured_area:
                    pattern:    ^/
                    anonymous: ~
                    http_basic:
                        realm: "Secured Demo Area"

            access_control:
                - { path: ^/admin, roles: ROLE_ADMIN }

            providers:
                in_memory:
                    memory:
                        users:
                            ryan:  { password: ryanpass, roles: 'ROLE_USER' }
                            admin: { password: kitten, roles: 'ROLE_ADMIN' }

            encoders:
                Symfony\Component\Security\Core\User\User: plaintext

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <?xml version="1.0" encoding="UTF-8"?>
        <srv:container xmlns="http://symfony.com/schema/dic/security"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:srv="http://symfony.com/schema/dic/services"
            xsi:schemaLocation="http://symfony.com/schema/dic/services http://symfony.com/schema/dic/services/services-1.0.xsd">

            <config>
                <firewall name="secured_area" pattern="^/">
                    <anonymous />
                    <http-basic realm="Secured Demo Area" />
                </firewall>

                <access-control>
                    <rule path="^/admin" role="ROLE_ADMIN" />
                </access-control>

                <provider name="in_memory">
                    <memory>
                        <user name="ryan" password="ryanpass" roles="ROLE_USER" />
                        <user name="admin" password="kitten" roles="ROLE_ADMIN" />
                    </memory>
                </provider>

                <encoder class="Symfony\Component\Security\Core\User\User"
                    algorithm="plaintext" />
            </config>
        </srv:container>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'firewalls' => array(
                'secured_area' => array(
                    'pattern'    => '^/',
                    'anonymous'  => array(),
                    'http_basic' => array(
                        'realm'  => 'Secured Demo Area',
                    ),
                ),
            ),
            'access_control' => array(
                array('path' => '^/admin', 'role' => 'ROLE_ADMIN'),
            ),
            'providers' => array(
                'in_memory' => array(
                    'memory' => array(
                        'users' => array(
                            'ryan' => array(
                                'password' => 'ryanpass',
                                'roles' => 'ROLE_USER',
                                ),
                            'admin' => array(
                                'password' => 'kitten',
                                'roles' => 'ROLE_ADMIN',
                            ),
                        ),
                    ),
                ),
            ),
            'encoders' => array(
                'Symfony\Component\Security\Core\User\User' => 'plaintext',
            ),
        ));

.. tip::

    Standardna Symfony distribucija ločuje varnostne nastavitve
    v ločeno datoteko (npr. ``app/config/security.yml``). Če nimate
    ločene varnostne datoteke, lahko date nastavitve direktno
    v vašo glavno nastavitveno datoteko (npr. ``app/config/config.yml``).

Končni rezultat teh nastavitev je polno funkcionalni varnosti sistem,
ki izgleda nekako sledeče:

* Na voljo sta dva uporabnika v sistemu (``ryan`` in ``admin``);
* Uporabniki izvedejo preverjanje pristnosti sami preko osnovnega HTTP pozivnika za preverjanje pristnosti
* Katerikoli URL, ki se ujema z ``/admin/*`` je zavarovan in samo ``admin`` uporabnik
  lahko do njega dostopa;
* Vsi URL-ji, ki se *ne* ujemajo z ``/admin/*``, so dostopni za vse uporabnike (in
  uporabnik ni nikoli pozvan k prijavi).

Poglejmo na kratko, kako varnost deluje in kako vsak del nastavitev
pride v igro.

Kako varnost deluje: Preverjanje pristnosti in avtorizacija
-----------------------------------------------------------

Symfony-jev varnostni sistem deluje z določitvijo, kdo je uporabnik (t.j. preverjanje pristnosti)
in nato preveri pogledati, če bi ta uporabnik moral imeti dostop do določenega vira
ali URL-ja.

.. _book-security-firewalls:

Požarni zidovi (preverjanje pristnosti)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Ko uporabnik naredi zahtevek do URL-ja, ki je zavarovan s požarnim zidom,
je aktiviran varnostni sistem. Naloga požarnega zidu je določitev, ali
uporabnik potrebuje biti ali ne pristno preverjen in če mora biti, pošiljanje odziva
nazaj k uporabniku in sproženje procesa preverjanja pristnosti.

Požarni zdi je aktiviran, ko se URL prihajajočega zahtevka ujema z nastavljenim
nastavitveno vrednostjo regularnega izraza požarnega zidu ``pattern``. V tem primeru
se bo ``pattern`` (``^/``) ujemal z *vsakim* prihajajočim zahtevkom. Dejstvo,
da je požarni zid aktiviran, *ne* pomeni, da je okno z uporabniškim imenom in geslom za
HTTP preverjanje pristnosti prikazano za vsak URL. Na primer, katerikoli uporabnik
lahko dostopa do ``/foo`` brez da je pozvan k preverjanju pristnosti.

.. image:: /images/book/security_anonymous_user_access.png
   :align: center

To najprej deluje, ker požarni zid omogoča *anonimnim uporabnikom* preko ``anonymous``
nastavitvenega parametra. Z drugimi besedami, požarni zid ne zahteva, od
uporabnika preveranja pristnosti takoj v celoti. In ker nobena posebna vloga (``role``)
ni potrebna za dostop do ``/foo`` (pod ``access_control`` sekcijo), je lahko zahtevek
izpolnjen brez da se kadarkoli sprašuje uporabnika, da izvede preverjanje pristnosti.

Če odstranite ključ ``anonymous``, bo požarni zid *vedno* naredil uporabnika
v celoti takoj pristno preverjenega.

Dostopne kontrole (avtorizacija)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Če uporabnik vseeno zahteva ``/admin/foo``, se proces obnaša drugače.
To je zaradi nastavitvene sekcije ``access_control``, ki pravi
da vsak URL, ki se ujema z vzorcem regularnega izraza ``^/admin`` (t.j. ``/admin``
ali karkoli kar se ujema z ``/admin/*``) zahteva vlogo ``ROLE_ADMIN``. Vloge
so osnova za večino avtorizacije: uporabnik lahko dostopa do ``/admin/foo`` samo,
če ima vlogo ``ROLE_ADMIN``.

.. image:: /images/book/security_anonymous_user_denied_authorization.png
   :align: center

Kot prej, ko je uporabnik originalno naredil zahtevek, požarni zdi ne
sprašuje za kakršnokoli identifikacijo. Vendar kako hitro nivo dostopne kontrole
zanika uporabnikov dostop (ker anonimni uporabnik nima vloge ``ROLE_ADMIN``),
požarni zid skoči v akcijo in sproži proces proces preverjanja pristnosti.
Proces preverjanja pristnosti zavisi na mehanizmu preverjanja pristnosti, ki
ga uporabljate. Na primer, če uporabljate metodo preverjanja pristnosti prijavnega obrazca,
bo uporabnik preusmerjen na prijavno stran. Če uporabljate HTTP preverjanje pristnosti,
bo uporabnik poslan na HTTP 401 odziv, tako da uporabnik vidi okence z uporabniškim
imenom in geslom.

Uporabnik ima sedaj priložnost poslati svoje prijavne podatke nazaj aplikaciji.
Če so prijavni podatki veljavni, je lahko originalni zahtevek ponovno poskušan.

.. image:: /images/book/security_ryan_no_role_admin_access.png
   :align: center

V tem primeru, uporabnik ``ryan`` je uspešno pristno preverjen s požarnim zidom.
Vendar ker ``ryan`` nima vloge ``ROLE_ADMIN``, ima še vedno zavrnjen
dostop do ``/admin/foo``. Na koncu to pomeni, da bo uporabnik videl neke vrste
sporočilo, ki označuje, da je dostop zavrnjen.

.. tip::

    Ko Symfony zavrne uporabniški dostop, uporabnik vidi ekran z napako in
    prejme 403 HTTP statusno kodo (``Forbidden``). Lahko prilagodite
    ekran z napako dostopa s sledečimi direkcijami v receptu
    :ref:`Strani z napakami <cookbook-error-pages-by-status-code>`
    za prilagoditev strani s 403 napako.

Na koncu če uporabnik ``admin`` zahteva ``/admin/foo``, se zgodi podoben
proces, razen sedaj po preverjanju pristnosti, bo nivo kontrole dostopa
omogočil zahtevek spustiti skozi:

.. image:: /images/book/security_admin_role_access.png
   :align: center

Tok zahtevka, ko uporabnik zahteva zaščitev vir je enostaven,
vendar izjemno fleksibilen. Kot boste kasneje videli, bo preverjanje pristnosti
upravljan na poljubne načine, vključno preko prijavnega obrazca, X.509 certifikata ali
s preverjanjem pristnosti uporabnika preko Twitter-ja. Ne glede na metodo preverjanja pristnosti
je tok zahtevka vedno enak:

#. Uporabnik dostopa do zavarovanega vira;
#. Aplikacija preusmeri uporabnika do prijavnega obrazca;
#. Uporabnik pošlje svoje prijavne podatke (npr. uporabniško ime/geslo);
#. Požarni zid izvede preverjanje pristnosti uporabnika;
#. Pristno preverjen uporabnik ponovno poskuša originalni zahtevek.

.. note::

    *Točni* proces dejansko zavisi malenkost od katerega mehanizma preverjanja pristnosti
    uporablajte. Na primer, ko uporabljate prijavni obrazec, uporabnik pošlje
    svoje prijavne podatke na en URL, ki procesira obrazec (npr. ``/login_check``)
    in nato preusmeri nazaj k originalnem zahtevanem URL-ju (npr. ``/admin/foo``).
    Vendar s HTTP preverjanjem pristnosti uporabnik pošlje svoje prijavne podatke direktno
    originalnem URL-ju (npr. ``/admin/foo``) in nato je stran vrnjena
    uporabniku v enakem zahtevku (t.j. brez preusmerjanja).

    Te čudaški tipi ne bi smeli povzročati kakršnih koli problemov, vendar
    jih je dobro imeti v mislih.

.. tip::

    Naučili se boste tudi, kako je lahko *karkoli* zavarovano v Symfony2, vključno
    z določenimi kontrolerji, objekti ali celo PHP metodami.

.. _book-security-form-login:

Uporaba tradicionalnega prijavnega obrazca
------------------------------------------

.. tip::

    V tej sekciji boste izvedeli, kako izdelati osnovni prijavni obrazec, ki nadaljuje
    z uporabo vkodiranih uporabnikov, ki so definirani v datoteki ``security.yml``.

    Da naložite uporabnike iz podatkovne baze, prosimo preberite :doc:`/cookbook/security/entity_provider`.
    Z branjem tega članka in te sekcije lahko naredite celotni sistem prijavnega
    obrazca, ki naloži uporabnike iz podatkovne baze.

Do sedaj ste videli, kako oviti vašo aplikacijo pod požarnim zidom in
nato zaščititi dostop do določenih območij z vlogami. Z uporabo HTTP preverjanja pristnosti
lahko brez truda vskočite v osnovno okence z uporabniškimi imenom/geslom ponujenim
od vseh brskalnikov Za podrobnosti o vseh njih, glejte
:doc:`Referenca varnostnih nastavitev </reference/configuration/security>`.

V tej sekciji boste okrepili ta proces z omogočanjem uporabnika, da se pristno preveri
preko tradicionalnega HTML prijavnega obrazca.

Najprej omogočite prijavni obrazec v vašem požarnem zidu:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            firewalls:
                secured_area:
                    pattern:    ^/
                    anonymous: ~
                    form_login:
                        login_path:  login
                        check_path:  login_check

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <?xml version="1.0" encoding="UTF-8"?>
        <srv:container xmlns="http://symfony.com/schema/dic/security"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xmlns:srv="http://symfony.com/schema/dic/services"
            xsi:schemaLocation="http://symfony.com/schema/dic/services
                http://symfony.com/schema/dic/services/services-1.0.xsd">

            <config>
                <firewall name="secured_area" pattern="^/">
                    <anonymous />
                    <form-login login_path="login" check_path="login_check" />
                </firewall>
            </config>
        </srv:container>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'firewalls' => array(
                'secured_area' => array(
                    'pattern'    => '^/',
                    'anonymous'  => array(),
                    'form_login' => array(
                        'login_path' => 'login',
                        'check_path' => 'login_check',
                    ),
                ),
            ),
        ));

.. tip::

    Če ne potrebujete prilagodit vaših vrednosti ``login_path`` ali ``check_path``
    (vrednosti uporabljene tu so privzete vrednosti), lahko skrajšate
    vaše nastavitve:

    .. configuration-block::

        .. code-block:: yaml

            form_login: ~

        .. code-block:: xml

            <form-login />

        .. code-block:: php

            'form_login' => array(),

Sedaj ko varnostni sistem sproži proces preverjanja pristnosti, bo
preusmeril uporabnika na prijavni obrazec (``/login`` privzeto). Implementacija
tega prijavnega obrazca vizualno je vaša naloga. Najprej izdelajte dve poti, ki ste jih uporabili v
varnostnih nastavitvah: pot ``login`` bo prikazala prijavni obrazec (t.j.
``/login``) in ``login_check`` pot bo upravljala pošiljanje prijavnega obrazca
(t.j. ``/login_check``):

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        login:
            path:   /login
            defaults:  { _controller: AcmeSecurityBundle:Security:login }
        login_check:
            path:   /login_check

    .. code-block:: xml

        <!-- app/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="login" path="/login">
                <default key="_controller">AcmeSecurityBundle:Security:login</default>
            </route>

            <route id="login_check" path="/login_check" />
        </routes>

    ..  code-block:: php

        // app/config/routing.php
        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('login', new Route('/login', array(
            '_controller' => 'AcmeDemoBundle:Security:login',
        )));
        $collection->add('login_check', new Route('/login_check', array()));

        return $collection;

.. note::

    *Ne* boste potrebovali implementirati krmilnika za ``/login_check``
    URL, saj bo požarni zid avtomatsko ujel in sprocesiral katerikoli obrazec poslan
    na ta URL. Vendar *morate* imeti pot (kot prikazano tu) za ta
    URL, kot tudi enega za vašo odjavno pot (glejte :ref:`book-security-logging-out`).

Bodite pozorni, da se ime poti ``login`` ujema z ``login_path`` nastavitveno
vrednostjo, saj tu bo varnostni sistem preusmeril uporabnike, ki se potrebujejo
prijaviti.

Naslednje izdelajte krmilnik, ki bo prikazal prijavni obrazec::

    // src/Acme/SecurityBundle/Controller/SecurityController.php;
    namespace Acme\SecurityBundle\Controller;

    use Symfony\Bundle\FrameworkBundle\Controller\Controller;
    use Symfony\Component\Security\Core\SecurityContext;

    class SecurityController extends Controller
    {
        public function loginAction()
        {
            $request = $this->getRequest();
            $session = $request->getSession();

            // get the login error if there is one
            if ($request->attributes->has(SecurityContext::AUTHENTICATION_ERROR)) {
                $error = $request->attributes->get(
                    SecurityContext::AUTHENTICATION_ERROR
                );
            } else {
                $error = $session->get(SecurityContext::AUTHENTICATION_ERROR);
                $session->remove(SecurityContext::AUTHENTICATION_ERROR);
            }

            return $this->render(
                'AcmeSecurityBundle:Security:login.html.twig',
                array(
                    // last username entered by the user
                    'last_username' => $session->get(SecurityContext::LAST_USERNAME),
                    'error'         => $error,
                )
            );
        }
    }

Ne pustite temu krmilniku, da vas zavede. Kot boste videli v momentu, ko
uporabnik pošlje obrazec, varnostni sistem avtomatsko upravlja pošiljanje
obrazca za vas. Če je uporabnik poslal napačno uporabniško ime ali geslo,
ta krmilnik prebere napako poslanega obrazca iz varnostnega sistema, da
je lahko prikazan uporabniku.

Z drugimi besedami, vaša naloga je prikazati prijavni obrazec in kakršnekoli napake,
ki se lahko zgodijo, vendar sam varnostni sistem poskrbi za preverjanje
poslanega uporabniškega imena in gesla in preverjanje pristnosti uporabnika.

Na koncu izdelajte ustrezno predlogo:

.. configuration-block::

    .. code-block:: html+jinja

        {# src/Acme/SecurityBundle/Resources/views/Security/login.html.twig #}
        {% if error %}
            <div>{{ error.message }}</div>
        {% endif %}

        <form action="{{ path('login_check') }}" method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="_username" value="{{ last_username }}" />

            <label for="password">Password:</label>
            <input type="password" id="password" name="_password" />

            {#
                If you want to control the URL the user
                is redirected to on success (more details below)
                <input type="hidden" name="_target_path" value="/account" />
            #}

            <button type="submit">login</button>
        </form>

    .. code-block:: html+php

        <!-- src/Acme/SecurityBundle/Resources/views/Security/login.html.php -->
        <?php if ($error): ?>
            <div><?php echo $error->getMessage() ?></div>
        <?php endif; ?>

        <form action="<?php echo $view['router']->generate('login_check') ?>" method="post">
            <label for="username">Username:</label>
            <input type="text" id="username" name="_username" value="<?php echo $last_username ?>" />

            <label for="password">Password:</label>
            <input type="password" id="password" name="_password" />

            <!--
                If you want to control the URL the user
                is redirected to on success (more details below)
                <input type="hidden" name="_target_path" value="/account" />
            -->

            <button type="submit">login</button>
        </form>

.. tip::

    Spremenljivska ``error`` poslana v predlogo je instanca
    :class:`Symfony\\Component\\Security\\Core\\Exception\\AuthenticationException`.
    Lahko vključuje več informacij - ali celo občutljive podatke - o
    neuspešnosti preverjanja pristnosti, torej uporabite jo pametno!

Obrazec ima zelo malo zahtev. Naprej s pošiljanjem obrazca na ``/login_check``
(preko ``login_check`` poti), varnostni sistem bo prestregel pošiljanje
obrazca in procesiral obrazec za vas avtomatsko. Nato varnosti sistem
pričakuje, da se poslana polja imenuje ``_username`` in ``_password``
(ta imena polj so lahko :ref:`nastavljiva <reference-security-firewall-form-login>`).

In to je vse! Ko pošljete obrazec, bo varnostni sistem avtomatsko
preveril uporabnikove prijavne podatke in bodisi pristno preveril uporabnika ali poslal
uporabnika nazaj k prijavnem obrazcu, kjer je prikazana napaka.

Preglejmo celotni proces:

#. Uporabnik poskuša dostopati do vira, ki je zaščiten;
#. Požarni zid sproži proces preverjanja pristnosti s preusmerjanjem
   uporabnika k prijavnem obrazcu (``/login``);
#. Stran ``/login`` izpiše prijavni obrazec preko usmeritve in krmilnika ustvarjenega
   v tem primeru;
#. Uporabnik pošlje prijavni obrazec na ``/login_check``;
#. Varnostni sistem prestreže zahtevek, preveri, poslane uporabnikove
   prijavne podatke, pristno preveri uporabnika, če je pravilen in pošlje
   uporabnika nazaj k prijavnem obrazcu, če ni.

Privzeto, če so poslani prijavni podatki pravilni, bo uporabnik preusmerjen
na originalno stran, ki je bila zahtevana (npr. ``/admin/foo``). Če je uporabnik
originalno šel naravnost na prijavno stran, bo preusmerjen na domačo stran.
To se lahko zelo prilagodi in vam omogoča na primer preusmerjanje
uporabnika na določeni URL.

Za več podrobnosti o tem in kako prilagoditi proces prijavnega obrazca v splošnem,
glejte :doc:`/cookbook/security/form_login`.

.. _book-security-common-pitfalls:

.. sidebar:: Avoid Common Pitfalls

    Ko nastavljate vaš prijavni obrazec, pazite na nekaj pogostih napak.

    **1. Ustvarite ustrezne usmeritve**

    Najprej bodite gotovi, da definirate ``login`` in ``login_check``
    usmeritve ustrezno in da kažejo na ``login_path`` in
    ``check_path`` nastavitvene vrednosti. Napačna konfiguracija tu lahko pomeni, da ste
    preusmerjeni na 404 stran namesto prijavne strani ali da pošiljanje
    prijavnega obrazca ne naredi ničesar (samo vedno znova in znova vidite prijavni
    obrazec).

    **2. Bodite prepričani, da prijavna stran ni zavarovana**

    Tudi bodite prepričani, da prijavna stran *ne* zahteva kakršnih koli vlog, da
    je lahko ogledana. Na primer, sledeče nastavitve - ki zahtevajo
    ``ROLE_ADMIN`` vlogo za vse URL-je (vključno z ``/login`` URL-jem), bodo
    povzročile zanko preusmerjanja:
    cause a redirect loop:

    .. configuration-block::

        .. code-block:: yaml

            access_control:
                - { path: ^/, roles: ROLE_ADMIN }

        .. code-block:: xml

            <access-control>
                <rule path="^/" role="ROLE_ADMIN" />
            </access-control>

        .. code-block:: php

            'access_control' => array(
                array('path' => '^/', 'role' => 'ROLE_ADMIN'),
            ),

    Odstranitev dostopne kontrole na ``/login`` URL-ju popravi problem:

    .. configuration-block::

        .. code-block:: yaml

            access_control:
                - { path: ^/login, roles: IS_AUTHENTICATED_ANONYMOUSLY }
                - { path: ^/, roles: ROLE_ADMIN }

        .. code-block:: xml

            <access-control>
                <rule path="^/login" role="IS_AUTHENTICATED_ANONYMOUSLY" />
                <rule path="^/" role="ROLE_ADMIN" />
            </access-control>

        .. code-block:: php

            'access_control' => array(
                array('path' => '^/login', 'role' => 'IS_AUTHENTICATED_ANONYMOUSLY'),
                array('path' => '^/', 'role' => 'ROLE_ADMIN'),
            ),

    Tudi, če vaš požarni zdi *ne* dovoljuje anonimnih uporabnikov, boste potrebovali
    izdelati posebni požarni zid, ki omogoča anonimnim uporabnikom za prijavno
    stran:

    .. configuration-block::

        .. code-block:: yaml

            firewalls:
                login_firewall:
                    pattern:    ^/login$
                    anonymous:  ~
                secured_area:
                    pattern:    ^/
                    form_login: ~

        .. code-block:: xml

            <firewall name="login_firewall" pattern="^/login$">
                <anonymous />
            </firewall>
            <firewall name="secured_area" pattern="^/">
                <form-login />
            </firewall>

        .. code-block:: php

            'firewalls' => array(
                'login_firewall' => array(
                    'pattern'   => '^/login$',
                    'anonymous' => array(),
                ),
                'secured_area' => array(
                    'pattern'    => '^/',
                    'form_login' => array(),
                ),
            ),

    **3. Bodite prepričani, da je ``/login_check`` za požarnim zidom**

    Naslednje zagotovite, da je vaš ``check_path`` URL (npr. ``/login_check``)
    za požarnim zidom, ki ga uporabljate za vaš prijavni obrazec (v tem primeru,
    se en požarni zid ujema z *vsemi* URL-ji, vključno z ``/login_check``). Če
    se ``/login_check`` ne ujema z nobenim požarnim zidom, boste prejeli ``Unable
    to find the controller for patch "/login_check"`` izjemo.

    **4. Več požarnih zidov si ne deli varnostnega konteksta**

    Če uporabljate več požarnih zidov in izvedete pristno preverjanje proti enem izmed njih
    *ne* boste pristno preverjeni proti kateremkoli drugem požarnem zidu avtomatsko.
    Različni požarni zidovi so kot različni požarni sistemi. Da to naredite, morate
    eksplicitno določiti isto :ref:`reference-security-firewall-context`
    za različne požarne zidove. Vendar običajno za večino aplikacij, je imeti
    glavni požarni zid dovolj.

Avtorizacija
------------

Prvi korak k varnosti je vedno preverjanje pristnosti. Ko je enkrat uporabnik
pristno preverjen, se prične avtorizacija. Avtorizacija ponuja standardni in
močan način, da določi, če uporabnik lahko dostopa do kateregakoli vira (URL, model,
objekt, klic metode, ...). To deluje z dodelitvijo določenih vlog vsakemu
uporabniku in nato zahtevanje različnih vlog za različne vire.

Ta proces avtorizacije ima dve različni strani:

#. Uporabnik ima določen skupek vlog;
#. Vir zahteva določeno vlogo, da je dostopan.

V tej sekciji, se boste osredočili na to, kako zavarovati različne vire (npr. URL-je,
klice metod itd.) z različnimi vlogami. Kasneje se boste naučili več o tem, kako
se vloge izdela in jih dodeli uporabnikom.

Zavarovanje specifičnih URL vzorcev
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Najosnovnejši način zavarovanja dela vaše aplikacije je zavarovanje celotnega
URL vzorca. To ste že videli v prvem primeru tega poglavja,
kjer karkoli, kar se ujema z regularnim izrazom vzorca ``^/admin`` zahteva
vlogo ``ROLE_ADMIN``.

Lahko definirate toliko URL vzorcev, kot jih potrebujete - vsak je regularni izraz.

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...
            access_control:
                - { path: ^/admin/users, roles: ROLE_SUPER_ADMIN }
                - { path: ^/admin, roles: ROLE_ADMIN }

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <!-- ... -->
            <rule path="^/admin/users" role="ROLE_SUPER_ADMIN" />
            <rule path="^/admin" role="ROLE_ADMIN" />
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            // ...
            'access_control' => array(
                array('path' => '^/admin/users', 'role' => 'ROLE_SUPER_ADMIN'),
                array('path' => '^/admin', 'role' => 'ROLE_ADMIN'),
            ),
        ));

.. tip::

    Dodajanje predpone poti z ``^`` zagotavlja, da se ujemajo samo URL-ji, ki se *začnejo* z
    vzorcem. Na primer enostavna pot ``/admin`` (brez
    ``^``) bi se ustrezno ujela z ``/admin/foo``, vendar bi bila tudi ujeta z URL-ji
    kot so ``/foo/admin``.

.. _security-book-access-control-explanation:

Razumevanje kako deluje ``access_control``
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Za vsak prihajajoč zahtevek, Symfony2 preveri vsak ``access_control`` vnos,
da najde *enega*, ki se ujema s trenutnim zahtevkom. Kakor hitro najde ujemanje z
``acceess_controle`` vnos, se ustavi - samo **prvo** ujemanje z ``access_control``
je uporabljeno, da vsili dostop.

Vsak ``access_control`` ima nekaj opcij, ki nastavijo dve različni
stvari:

* (a) :ref:`should the incoming request match this access control entry <security-book-access-control-matching-options>`
* (b) :ref:`once it matches, should some sort of access restriction be enforced <security-book-access-control-enforcement-options>`:

.. _security-book-access-control-matching-options:

(a) Matching Options
....................

Symfony2 creates an instance of :class:`Symfony\\Component\\HttpFoundation\\RequestMatcher`
for each ``access_control`` entry, which determines whether or not a given
access control should be used on this request. The following ``access_control``
options are used for matching:

* ``path``
* ``ip`` or ``ips``
* ``host``
* ``methods``

Take the following ``access_control`` entries as an example:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...
            access_control:
                - { path: ^/admin, roles: ROLE_USER_IP, ip: 127.0.0.1 }
                - { path: ^/admin, roles: ROLE_USER_HOST, host: symfony\.com$ }
                - { path: ^/admin, roles: ROLE_USER_METHOD, methods: [POST, PUT] }
                - { path: ^/admin, roles: ROLE_USER }

    .. code-block:: xml

            <access-control>
                <rule path="^/admin" role="ROLE_USER_IP" ip="127.0.0.1" />
                <rule path="^/admin" role="ROLE_USER_HOST" host="symfony\.com$" />
                <rule path="^/admin" role="ROLE_USER_METHOD" method="POST, PUT" />
                <rule path="^/admin" role="ROLE_USER" />
            </access-control>

    .. code-block:: php

            'access_control' => array(
                array(
                    'path' => '^/admin',
                    'role' => 'ROLE_USER_IP',
                    'ip' => '127.0.0.1',
                ),
                array(
                    'path' => '^/admin',
                    'role' => 'ROLE_USER_HOST',
                    'host' => 'symfony\.com$',
                ),
                array(
                    'path' => '^/admin',
                    'role' => 'ROLE_USER_METHOD',
                    'method' => 'POST, PUT',
                ),
                array(
                    'path' => '^/admin',
                    'role' => 'ROLE_USER',
                ),
            ),

For each incoming request, Symfony will decide which ``access_control``
to use based on the URI, the client's IP address, the incoming host name,
and the request method. Remember, the first rule that matches is used, and
if ``ip``, ``host`` or ``method`` are not specified for an entry, that ``access_control``
will match any ``ip``, ``host`` or ``method``:

+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| **URI**         | **IP**      | **HOST**    | **METHOD** | ``access_control``             | Why?                                                        |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| ``/admin/user`` | 127.0.0.1   | example.com | GET        | rule #1 (``ROLE_USER_IP``)     | The URI matches ``path`` and the IP matches ``ip``.         |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| ``/admin/user`` | 127.0.0.1   | symfony.com | GET        | rule #1 (``ROLE_USER_IP``)     | The ``path`` and ``ip`` still match. This would also match  |
|                 |             |             |            |                                | the ``ROLE_USER_HOST`` entry, but *only* the **first**      |
|                 |             |             |            |                                | ``access_control`` match is used.                           |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| ``/admin/user`` | 168.0.0.1   | symfony.com | GET        | rule #2 (``ROLE_USER_HOST``)   | The ``ip`` doesn't match the first rule, so the second      |
|                 |             |             |            |                                | rule (which matches) is used.                               |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| ``/admin/user`` | 168.0.0.1   | symfony.com | POST       | rule #2 (``ROLE_USER_HOST``)   | The second rule still matches. This would also match the    |
|                 |             |             |            |                                | third rule (``ROLE_USER_METHOD``), but only the **first**   |
|                 |             |             |            |                                | matched ``access_control`` is used.                         |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| ``/admin/user`` | 168.0.0.1   | example.com | POST       | rule #3 (``ROLE_USER_METHOD``) | The ``ip`` and ``host`` don't match the first two entries,  |
|                 |             |             |            |                                | but the third - ``ROLE_USER_METHOD`` - matches and is used. |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| ``/admin/user`` | 168.0.0.1   | example.com | GET        | rule #4 (``ROLE_USER``)        | The ``ip``, ``host`` and ``method`` prevent the first       |
|                 |             |             |            |                                | three entries from matching. But since the URI matches the  |
|                 |             |             |            |                                | ``path`` pattern of the ``ROLE_USER`` entry, it is used.    |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+
| ``/foo``        | 127.0.0.1   | symfony.com | POST       | matches no entries             | This doesn't match any ``access_control`` rules, since its  |
|                 |             |             |            |                                | URI doesn't match any of the ``path`` values.               |
+-----------------+-------------+-------------+------------+--------------------------------+-------------------------------------------------------------+

.. _security-book-access-control-enforcement-options:

(b) Access Enforcement
......................

Once Symfony2 has decided which ``access_control`` entry matches (if any),
it then *enforces* access restrictions based on the ``roles`` and ``requires_channel``
options:

* ``role`` If the user does not have the given role(s), then access is denied
  (internally, an :class:`Symfony\\Component\\Security\\Core\\Exception\\AccessDeniedException`
  is thrown);

* ``requires_channel`` If the incoming request's channel (e.g. ``http``)
  does not match this value (e.g. ``https``), the user will be redirected
  (e.g. redirected from ``http`` to ``https``, or vice versa).

.. tip::

    If access is denied, the system will try to authenticate the user if not
    already (e.g. redirect the user to the login page). If the user is already
    logged in, the 403 "access denied" error page will be shown. See
    :doc:`/cookbook/controller/error_pages` for more information.

.. _book-security-securing-ip:

Securing by IP
~~~~~~~~~~~~~~

Certain situations may arise when you may need to restrict access to a given
path based on IP. This is particularly relevant in the case of
:ref:`Edge Side Includes <edge-side-includes>` (ESI), for example. When ESI is
enabled, it's recommended to secure access to ESI URLs. Indeed, some ESI may
contain some private content like the current logged in user's information. To
prevent any direct access to these resources from a web browser (by guessing the
ESI URL pattern), the ESI route **must** be secured to be only visible from
the trusted reverse proxy cache.

.. versionadded:: 2.3
    Version 2.3 allows multiple IP addresses in a single rule with the ``ips: [a, b]``
    construct.  Prior to 2.3, users should create one rule per IP address to match and
    use the ``ip`` key instead of ``ips``.

Here is an example of how you might secure all ESI routes that start with a
given prefix, ``/esi``, from outside access:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...
            access_control:
                - { path: ^/esi, roles: IS_AUTHENTICATED_ANONYMOUSLY, ips: [127.0.0.1, ::1] }
                - { path: ^/esi, roles: ROLE_NO_ACCESS }

    .. code-block:: xml

            <access-control>
                <rule path="^/esi" role="IS_AUTHENTICATED_ANONYMOUSLY"
                    ips="127.0.0.1, ::1" />
                <rule path="^/esi" role="ROLE_NO_ACCESS" />
            </access-control>

    .. code-block:: php

            'access_control' => array(
                array(
                    'path' => '^/esi',
                    'role' => 'IS_AUTHENTICATED_ANONYMOUSLY',
                    'ips' => '127.0.0.1, ::1'
                ),
                array(
                    'path' => '^/esi',
                    'role' => 'ROLE_NO_ACCESS'
                ),
            ),

Here is how it works when the path is ``/esi/something`` coming from the
``10.0.0.1`` IP:

* The first access control rule is ignored as the ``path`` matches but the
  ``ip`` does not match either of the IPs listed;

* The second access control rule is enabled (the only restriction being the
  ``path`` and it matches): as the user cannot have the ``ROLE_NO_ACCESS``
  role as it's not defined, access is denied (the ``ROLE_NO_ACCESS`` role can
  be anything that does not match an existing role, it just serves as a trick
  to always deny access).

Now, if the same request comes from ``127.0.0.1`` or ``::1`` (the IPv6 loopback
address):

* Now, the first access control rule is enabled as both the ``path`` and the
  ``ip`` match: access is allowed as the user always has the
  ``IS_AUTHENTICATED_ANONYMOUSLY`` role.

* The second access rule is not examined as the first rule matched.

.. _book-security-securing-channel:

Securing by Channel
~~~~~~~~~~~~~~~~~~~

You can also require a user to access a URL via SSL; just use the
``requires_channel`` argument in any ``access_control`` entries:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...
            access_control:
                - { path: ^/cart/checkout, roles: IS_AUTHENTICATED_ANONYMOUSLY, requires_channel: https }

    .. code-block:: xml

            <access-control>
                <rule path="^/cart/checkout" role="IS_AUTHENTICATED_ANONYMOUSLY"
                    requires_channel="https" />
            </access-control>

    .. code-block:: php

            'access_control' => array(
                array(
                    'path' => '^/cart/checkout',
                    'role' => 'IS_AUTHENTICATED_ANONYMOUSLY',
                    'requires_channel' => 'https',
                ),
            ),

.. _book-security-securing-controller:

Securing a Controller
~~~~~~~~~~~~~~~~~~~~~

Protecting your application based on URL patterns is easy, but may not be
fine-grained enough in certain cases. When necessary, you can easily force
authorization from inside a controller::

    // ...
    use Symfony\Component\Security\Core\Exception\AccessDeniedException;

    public function helloAction($name)
    {
        if (false === $this->get('security.context')->isGranted('ROLE_ADMIN')) {
            throw new AccessDeniedException();
        }

        // ...
    }

.. _book-security-securing-controller-annotations:

You can also choose to install and use the optional ``JMSSecurityExtraBundle``,
which can secure your controller using annotations::

    // ...
    use JMS\SecurityExtraBundle\Annotation\Secure;

    /**
     * @Secure(roles="ROLE_ADMIN")
     */
    public function helloAction($name)
    {
        // ...
    }

For more information, see the `JMSSecurityExtraBundle`_ documentation.

Securing other Services
~~~~~~~~~~~~~~~~~~~~~~~

In fact, anything in Symfony can be protected using a strategy similar to
the one seen in the previous section. For example, suppose you have a service
(i.e. a PHP class) whose job is to send emails from one user to another.
You can restrict use of this class - no matter where it's being used from -
to users that have a specific role.

For more information on how you can use the security component to secure
different services and methods in your application, see :doc:`/cookbook/security/securing_services`.

Access Control Lists (ACLs): Securing Individual Database Objects
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Imagine you are designing a blog system where your users can comment on your
posts. Now, you want a user to be able to edit his own comments, but not
those of other users. Also, as the admin user, you yourself want to be able
to edit *all* comments.

The security component comes with an optional access control list (ACL) system
that you can use when you need to control access to individual instances
of an object in your system. *Without* ACL, you can secure your system so that
only certain users can edit blog comments in general. But *with* ACL, you
can restrict or allow access on a comment-by-comment basis.

For more information, see the cookbook article: :doc:`/cookbook/security/acl`.

Users
-----

In the previous sections, you learned how you can protect different resources
by requiring a set of *roles* for a resource. This section explores
the other side of authorization: users.

Where do Users come from? (*User Providers*)
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

During authentication, the user submits a set of credentials (usually a username
and password). The job of the authentication system is to match those credentials
against some pool of users. So where does this list of users come from?

In Symfony2, users can come from anywhere - a configuration file, a database
table, a web service, or anything else you can dream up. Anything that provides
one or more users to the authentication system is known as a "user provider".
Symfony2 comes standard with the two most common user providers: one that
loads users from a configuration file and one that loads users from a database
table.

Specifying Users in a Configuration File
........................................

The easiest way to specify your users is directly in a configuration file.
In fact, you've seen this already in the example in this chapter.

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...
            providers:
                default_provider:
                    memory:
                        users:
                            ryan:  { password: ryanpass, roles: 'ROLE_USER' }
                            admin: { password: kitten, roles: 'ROLE_ADMIN' }

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <!-- ... -->
            <provider name="default_provider">
                <memory>
                    <user name="ryan" password="ryanpass" roles="ROLE_USER" />
                    <user name="admin" password="kitten" roles="ROLE_ADMIN" />
                </memory>
            </provider>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            // ...
            'providers' => array(
                'default_provider' => array(
                    'memory' => array(
                        'users' => array(
                            'ryan' => array(
                                'password' => 'ryanpass',
                                'roles' => 'ROLE_USER',
                            ),
                            'admin' => array(
                                'password' => 'kitten',
                                'roles' => 'ROLE_ADMIN',
                            ),
                        ),
                    ),
                ),
            ),
        ));

This user provider is called the "in-memory" user provider, since the users
aren't stored anywhere in a database. The actual user object is provided
by Symfony (:class:`Symfony\\Component\\Security\\Core\\User\\User`).

.. tip::
    Any user provider can load users directly from configuration by specifying
    the ``users`` configuration parameter and listing the users beneath it.

.. caution::

    If your username is completely numeric (e.g. ``77``) or contains a dash
    (e.g. ``user-name``), you should use that alternative syntax when specifying
    users in YAML:

    .. code-block:: yaml

        users:
            - { name: 77, password: pass, roles: 'ROLE_USER' }
            - { name: user-name, password: pass, roles: 'ROLE_USER' }

For smaller sites, this method is quick and easy to setup. For more complex
systems, you'll want to load your users from the database.

.. _book-security-user-entity:

Loading Users from the Database
...............................

If you'd like to load your users via the Doctrine ORM, you can easily do
this by creating a ``User`` class and configuring the ``entity`` provider.

.. tip::

    A high-quality open source bundle is available that allows your users
    to be stored via the Doctrine ORM or ODM. Read more about the `FOSUserBundle`_
    on GitHub.

With this approach, you'll first create your own ``User`` class, which will
be stored in the database.

.. code-block:: php

    // src/Acme/UserBundle/Entity/User.php
    namespace Acme\UserBundle\Entity;

    use Symfony\Component\Security\Core\User\UserInterface;
    use Doctrine\ORM\Mapping as ORM;

    /**
     * @ORM\Entity
     */
    class User implements UserInterface
    {
        /**
         * @ORM\Column(type="string", length=255)
         */
        protected $username;

        // ...
    }

As far as the security system is concerned, the only requirement for your
custom user class is that it implements the :class:`Symfony\\Component\\Security\\Core\\User\\UserInterface`
interface. This means that your concept of a "user" can be anything, as long
as it implements this interface.

.. note::

    The user object will be serialized and saved in the session during requests,
    therefore it is recommended that you `implement the \Serializable interface`_
    in your user object. This is especially important if your ``User`` class
    has a parent class with private properties.

Next, configure an ``entity`` user provider, and point it to your ``User``
class:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            providers:
                main:
                    entity:
                        class: Acme\UserBundle\Entity\User
                        property: username

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <provider name="main">
                <entity class="Acme\UserBundle\Entity\User" property="username" />
            </provider>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'providers' => array(
                'main' => array(
                    'entity' => array(
                        'class' => 'Acme\UserBundle\Entity\User',
                        'property' => 'username',
                    ),
                ),
            ),
        ));

With the introduction of this new provider, the authentication system will
attempt to load a ``User`` object from the database by using the ``username``
field of that class.

.. note::
    This example is just meant to show you the basic idea behind the ``entity``
    provider. For a full working example, see :doc:`/cookbook/security/entity_provider`.

For more information on creating your own custom provider (e.g. if you needed
to load users via a web service), see :doc:`/cookbook/security/custom_provider`.

.. _book-security-encoding-user-password:

Encoding the User's Password
~~~~~~~~~~~~~~~~~~~~~~~~~~~~

So far, for simplicity, all the examples have stored the users' passwords
in plain text (whether those users are stored in a configuration file or in
a database somewhere). Of course, in a real application, you'll want to encode
your users' passwords for security reasons. This is easily accomplished by
mapping your User class to one of several built-in "encoders". For example,
to store your users in memory, but obscure their passwords via ``sha1``,
do the following:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...
            providers:
                in_memory:
                    memory:
                        users:
                            ryan:  { password: bb87a29949f3a1ee0559f8a57357487151281386, roles: 'ROLE_USER' }
                            admin: { password: 74913f5cd5f61ec0bcfdb775414c2fb3d161b620, roles: 'ROLE_ADMIN' }

            encoders:
                Symfony\Component\Security\Core\User\User:
                    algorithm: sha1
                    iterations: 1
                    encode_as_base64: false

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <!-- ... -->
            <provider name="in_memory">
                <memory>
                    <user name="ryan"
                        password="bb87a29949f3a1ee0559f8a57357487151281386"
                        roles="ROLE_USER" />
                    <user name="admin"
                        password="74913f5cd5f61ec0bcfdb775414c2fb3d161b620"
                        roles="ROLE_ADMIN" />
                </memory>
            </provider>

            <encoder class="Symfony\Component\Security\Core\User\User"
                algorithm="sha1"
                iterations="1"
                encode_as_base64="false" />
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            // ...
            'providers' => array(
                'in_memory' => array(
                    'memory' => array(
                        'users' => array(
                            'ryan' => array(
                                'password' => 'bb87a29949f3a1ee0559f8a57357487151281386',
                                'roles' => 'ROLE_USER',
                            ),
                            'admin' => array(
                                'password' => '74913f5cd5f61ec0bcfdb775414c2fb3d161b620',
                                'roles' => 'ROLE_ADMIN',
                            ),
                        ),
                    ),
                ),
            ),
            'encoders' => array(
                'Symfony\Component\Security\Core\User\User' => array(
                    'algorithm'         => 'sha1',
                    'iterations'        => 1,
                    'encode_as_base64'  => false,
                ),
            ),
        ));

By setting the ``iterations`` to ``1`` and the ``encode_as_base64`` to false,
the password is simply run through the ``sha1`` algorithm one time and without
any extra encoding. You can now calculate the hashed password either programmatically
(e.g. ``hash('sha1', 'ryanpass')``) or via some online tool like `functions-online.com`_

If you're creating your users dynamically (and storing them in a database),
you can use even tougher hashing algorithms and then rely on an actual password
encoder object to help you encode passwords. For example, suppose your User
object is ``Acme\UserBundle\Entity\User`` (like in the above example). First,
configure the encoder for that user:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            # ...

            encoders:
                Acme\UserBundle\Entity\User: sha512

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <!-- ... -->

            <encoder class="Acme\UserBundle\Entity\User" algorithm="sha512" />
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            // ...
            'encoders' => array(
                'Acme\UserBundle\Entity\User' => 'sha512',
            ),
        ));

In this case, you're using the stronger ``sha512`` algorithm. Also, since
you've simply specified the algorithm (``sha512``) as a string, the system
will default to hashing your password 5000 times in a row and then encoding
it as base64. In other words, the password has been greatly obfuscated so
that the hashed password can't be decoded (i.e. you can't determine the password
from the hashed password).

.. versionadded:: 2.2
    As of Symfony 2.2 you can also use the :ref:`PBKDF2 <reference-security-pbkdf2>`
    and :ref:`BCrypt <reference-security-bcrypt>` password encoders.

Determining the Hashed Password
...............................

If you have some sort of registration form for users, you'll need to be able
to determine the hashed password so that you can set it on your user. No
matter what algorithm you configure for your user object, the hashed password
can always be determined in the following way from a controller::

    $factory = $this->get('security.encoder_factory');
    $user = new Acme\UserBundle\Entity\User();

    $encoder = $factory->getEncoder($user);
    $password = $encoder->encodePassword('ryanpass', $user->getSalt());
    $user->setPassword($password);

.. caution::

    When you allow a user to submit a plaintext password (e.g. registration
    form, change password form), you *must* have validation that guarantees
    that the password is 4096 characters or less. Read more details in
    :ref:`How to implement a simple Registration Form <cookbook-registration-password-max>`.

Retrieving the User Object
~~~~~~~~~~~~~~~~~~~~~~~~~~

After authentication, the ``User`` object of the current user can be accessed
via the ``security.context`` service. From inside a controller, this will
look like::

    public function indexAction()
    {
        $user = $this->get('security.context')->getToken()->getUser();
    }

In a controller this can be shortcut to:

.. code-block:: php

    public function indexAction()
    {
        $user = $this->getUser();
    }

.. note::

    Anonymous users are technically authenticated, meaning that the ``isAuthenticated()``
    method of an anonymous user object will return true. To check if your
    user is actually authenticated, check for the ``IS_AUTHENTICATED_FULLY``
    role.

In a Twig Template this object can be accessed via the ``app.user`` key,
which calls the :method:`GlobalVariables::getUser() <Symfony\\Bundle\\FrameworkBundle\\Templating\\GlobalVariables::getUser>`
method:

.. configuration-block::

    .. code-block:: html+jinja

        <p>Username: {{ app.user.username }}</p>

    .. code-block:: html+php

        <p>Username: <?php echo $app->getUser()->getUsername() ?></p>

Using Multiple User Providers
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Each authentication mechanism (e.g. HTTP Authentication, form login, etc)
uses exactly one user provider, and will use the first declared user provider
by default. But what if you want to specify a few users via configuration
and the rest of your users in the database? This is possible by creating
a new provider that chains the two together:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            providers:
                chain_provider:
                    chain:
                        providers: [in_memory, user_db]
                in_memory:
                    memory:
                        users:
                            foo: { password: test }
                user_db:
                    entity: { class: Acme\UserBundle\Entity\User, property: username }

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <provider name="chain_provider">
                <chain>
                    <provider>in_memory</provider>
                    <provider>user_db</provider>
                </chain>
            </provider>
            <provider name="in_memory">
                <memory>
                    <user name="foo" password="test" />
                </memory>
            </provider>
            <provider name="user_db">
                <entity class="Acme\UserBundle\Entity\User" property="username" />
            </provider>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'providers' => array(
                'chain_provider' => array(
                    'chain' => array(
                        'providers' => array('in_memory', 'user_db'),
                    ),
                ),
                'in_memory' => array(
                    'memory' => array(
                       'users' => array(
                           'foo' => array('password' => 'test'),
                       ),
                    ),
                ),
                'user_db' => array(
                    'entity' => array(
                        'class' => 'Acme\UserBundle\Entity\User',
                        'property' => 'username',
                    ),
                ),
            ),
        ));

Now, all authentication mechanisms will use the ``chain_provider``, since
it's the first specified. The ``chain_provider`` will, in turn, try to load
the user from both the ``in_memory`` and ``user_db`` providers.

.. tip::

    If you have no reasons to separate your ``in_memory`` users from your
    ``user_db`` users, you can accomplish this even more easily by combining
    the two sources into a single provider:

    .. configuration-block::

        .. code-block:: yaml

            # app/config/security.yml
            security:
                providers:
                    main_provider:
                        memory:
                            users:
                                foo: { password: test }
                        entity:
                            class: Acme\UserBundle\Entity\User,
                            property: username

        .. code-block:: xml

            <!-- app/config/security.xml -->
            <config>
                <provider name=="main_provider">
                    <memory>
                        <user name="foo" password="test" />
                    </memory>

                    <entity class="Acme\UserBundle\Entity\User"
                        property="username" />
                </provider>
            </config>

        .. code-block:: php

            // app/config/security.php
            $container->loadFromExtension('security', array(
                'providers' => array(
                    'main_provider' => array(
                        'memory' => array(
                            'users' => array(
                                'foo' => array('password' => 'test'),
                            ),
                        ),
                        'entity' => array(
                        'class' => 'Acme\UserBundle\Entity\User',
                        'property' => 'username'),
                    ),
                ),
            ));

You can also configure the firewall or individual authentication mechanisms
to use a specific provider. Again, unless a provider is specified explicitly,
the first provider is always used:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            firewalls:
                secured_area:
                    # ...
                    provider: user_db
                    http_basic:
                        realm: "Secured Demo Area"
                        provider: in_memory
                    form_login: ~

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <firewall name="secured_area" pattern="^/" provider="user_db">
                <!-- ... -->
                <http-basic realm="Secured Demo Area" provider="in_memory" />
                <form-login />
            </firewall>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'firewalls' => array(
                'secured_area' => array(
                    // ...
                    'provider' => 'user_db',
                    'http_basic' => array(
                        // ...
                        'provider' => 'in_memory',
                    ),
                    'form_login' => array(),
                ),
            ),
        ));

In this example, if a user tries to log in via HTTP authentication, the authentication
system will use the ``in_memory`` user provider. But if the user tries to
log in via the form login, the ``user_db`` provider will be used (since it's
the default for the firewall as a whole).

For more information about user provider and firewall configuration, see
the :doc:`/reference/configuration/security`.

Roles
-----

The idea of a "role" is key to the authorization process. Each user is assigned
a set of roles and then each resource requires one or more roles. If the user
has the required roles, access is granted. Otherwise access is denied.

Roles are pretty simple, and are basically strings that you can invent and
use as needed (though roles are objects internally). For example, if you
need to start limiting access to the blog admin section of your website,
you could protect that section using a ``ROLE_BLOG_ADMIN`` role. This role
doesn't need to be defined anywhere - you can just start using it.

.. note::

    All roles **must** begin with the ``ROLE_`` prefix to be managed by
    Symfony2. If you define your own roles with a dedicated ``Role`` class
    (more advanced), don't use the ``ROLE_`` prefix.

Hierarchical Roles
~~~~~~~~~~~~~~~~~~

Instead of associating many roles to users, you can define role inheritance
rules by creating a role hierarchy:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            role_hierarchy:
                ROLE_ADMIN:       ROLE_USER
                ROLE_SUPER_ADMIN: [ROLE_ADMIN, ROLE_ALLOWED_TO_SWITCH]

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <role id="ROLE_ADMIN">ROLE_USER</role>
            <role id="ROLE_SUPER_ADMIN">ROLE_ADMIN, ROLE_ALLOWED_TO_SWITCH</role>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'role_hierarchy' => array(
                'ROLE_ADMIN'       => 'ROLE_USER',
                'ROLE_SUPER_ADMIN' => array(
                    'ROLE_ADMIN',
                    'ROLE_ALLOWED_TO_SWITCH',
                ),
            ),
        ));

In the above configuration, users with ``ROLE_ADMIN`` role will also have the
``ROLE_USER`` role. The ``ROLE_SUPER_ADMIN`` role has ``ROLE_ADMIN``, ``ROLE_ALLOWED_TO_SWITCH``
and ``ROLE_USER`` (inherited from ``ROLE_ADMIN``).

.. _book-security-logging-out:

Logging Out
-----------

Usually, you'll also want your users to be able to log out. Fortunately,
the firewall can handle this automatically for you when you activate the
``logout`` config parameter:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            firewalls:
                secured_area:
                    # ...
                    logout:
                        path:   /logout
                        target: /
            # ...

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <firewall name="secured_area" pattern="^/">
                <!-- ... -->
                <logout path="/logout" target="/" />
            </firewall>
            <!-- ... -->
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'firewalls' => array(
                'secured_area' => array(
                    // ...
                    'logout' => array('path' => 'logout', 'target' => '/'),
                ),
            ),
            // ...
        ));

Once this is configured under your firewall, sending a user to ``/logout``
(or whatever you configure the ``path`` to be), will un-authenticate the
current user. The user will then be sent to the homepage (the value defined
by the ``target`` parameter). Both the ``path`` and ``target`` config parameters
default to what's specified here. In other words, unless you need to customize
them, you can omit them entirely and shorten your configuration:

.. configuration-block::

    .. code-block:: yaml

        logout: ~

    .. code-block:: xml

        <logout />

    .. code-block:: php

        'logout' => array(),

Note that you will *not* need to implement a controller for the ``/logout``
URL as the firewall takes care of everything. You *do*, however, need to create
a route so that you can use it to generate the URL:

.. configuration-block::

    .. code-block:: yaml

        # app/config/routing.yml
        logout:
            path:   /logout

    .. code-block:: xml

        <!-- app/config/routing.xml -->
        <?xml version="1.0" encoding="UTF-8" ?>
        <routes xmlns="http://symfony.com/schema/routing"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://symfony.com/schema/routing
                http://symfony.com/schema/routing/routing-1.0.xsd">

            <route id="logout" path="/logout" />
        </routes>

    ..  code-block:: php

        // app/config/routing.php
        use Symfony\Component\Routing\RouteCollection;
        use Symfony\Component\Routing\Route;

        $collection = new RouteCollection();
        $collection->add('logout', new Route('/logout', array()));

        return $collection;

Once the user has been logged out, he will be redirected to whatever path
is defined by the ``target`` parameter above (e.g. the ``homepage``). For
more information on configuring the logout, see the
:doc:`Security Configuration Reference </reference/configuration/security>`.

.. _book-security-template:

Access Control in Templates
---------------------------

If you want to check if the current user has a role inside a template, use
the built-in helper function:

.. configuration-block::

    .. code-block:: html+jinja

        {% if is_granted('ROLE_ADMIN') %}
            <a href="...">Delete</a>
        {% endif %}

    .. code-block:: html+php

        <?php if ($view['security']->isGranted('ROLE_ADMIN')): ?>
            <a href="...">Delete</a>
        <?php endif; ?>

.. note::

    If you use this function and are *not* at a URL where there is a firewall
    active, an exception will be thrown. Again, it's almost always a good
    idea to have a main firewall that covers all URLs (as has been shown
    in this chapter).

Access Control in Controllers
-----------------------------

If you want to check if the current user has a role in your controller, use
the :method:`Symfony\\Component\\Security\\Core\\SecurityContext::isGranted`
method of the security context::

    public function indexAction()
    {
        // show different content to admin users
        if ($this->get('security.context')->isGranted('ROLE_ADMIN')) {
            // ... load admin content here
        }

        // ... load other regular content here
    }

.. note::

    A firewall must be active or an exception will be thrown when the ``isGranted``
    method is called. See the note above about templates for more details.

Impersonating a User
--------------------

Sometimes, it's useful to be able to switch from one user to another without
having to log out and log in again (for instance when you are debugging or trying
to understand a bug a user sees that you can't reproduce). This can be easily
done by activating the ``switch_user`` firewall listener:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            firewalls:
                main:
                    # ...
                    switch_user: true

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <firewall>
                <!-- ... -->
                <switch-user />
            </firewall>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'firewalls' => array(
                'main'=> array(
                    // ...
                    'switch_user' => true
                ),
            ),
        ));

To switch to another user, just add a query string with the ``_switch_user``
parameter and the username as the value to the current URL:

.. code-block:: text

    http://example.com/somewhere?_switch_user=thomas

To switch back to the original user, use the special ``_exit`` username:

.. code-block:: text

    http://example.com/somewhere?_switch_user=_exit

During impersonation, the user is provided with a special role called
``ROLE_PREVIOUS_ADMIN``. In a template, for instance, this role can be used
to show a link to exit impersonation:

.. configuration-block::

    .. code-block:: html+jinja

        {% if is_granted('ROLE_PREVIOUS_ADMIN') %}
            <a href="{{ path('homepage', {'_switch_user': '_exit'}) }}">Exit impersonation</a>
        {% endif %}

    .. code-block:: html+php

        <?php if ($view['security']->isGranted('ROLE_PREVIOUS_ADMIN')): ?>
            <a
                href="<?php echo $view['router']->generate('homepage', array(
                    '_switch_user' => '_exit',
                ) ?>"
            >
                Exit impersonation
            </a>
        <?php endif; ?>

Of course, this feature needs to be made available to a small group of users.
By default, access is restricted to users having the ``ROLE_ALLOWED_TO_SWITCH``
role. The name of this role can be modified via the ``role`` setting. For
extra security, you can also change the query parameter name via the ``parameter``
setting:

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            firewalls:
                main:
                    # ...
                    switch_user: { role: ROLE_ADMIN, parameter: _want_to_be_this_user }

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <firewall>
                <!-- ... -->
                <switch-user role="ROLE_ADMIN" parameter="_want_to_be_this_user" />
            </firewall>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'firewalls' => array(
                'main'=> array(
                    // ...
                    'switch_user' => array(
                        'role' => 'ROLE_ADMIN',
                        'parameter' => '_want_to_be_this_user',
                    ),
                ),
            ),
        ));

Stateless Authentication
------------------------

By default, Symfony2 relies on a cookie (the Session) to persist the security
context of the user. But if you use certificates or HTTP authentication for
instance, persistence is not needed as credentials are available for each
request. In that case, and if you don't need to store anything else between
requests, you can activate the stateless authentication (which means that no
cookie will be ever created by Symfony2):

.. configuration-block::

    .. code-block:: yaml

        # app/config/security.yml
        security:
            firewalls:
                main:
                    http_basic: ~
                    stateless:  true

    .. code-block:: xml

        <!-- app/config/security.xml -->
        <config>
            <firewall stateless="true">
                <http-basic />
            </firewall>
        </config>

    .. code-block:: php

        // app/config/security.php
        $container->loadFromExtension('security', array(
            'firewalls' => array(
                'main' => array('http_basic' => array(), 'stateless' => true),
            ),
        ));

.. note::

    If you use a form login, Symfony2 will create a cookie even if you set
    ``stateless`` to ``true``.

Utilities
---------

.. versionadded:: 2.2
    The ``StringUtils`` and ``SecureRandom`` classes were added in Symfony 2.2

The Symfony Security Component comes with a collection of nice utilities related
to security. These utilities are used by Symfony, but you should also use
them if you want to solve the problem they address.

Comparing Strings
~~~~~~~~~~~~~~~~~

The time it takes to compare two strings depends on their differences. This
can be used by an attacker when the two strings represent a password for
instance; it is known as a `Timing attack`_.

Internally, when comparing two passwords, Symfony uses a constant-time
algorithm; you can use the same strategy in your own code thanks to the
:class:`Symfony\\Component\\Security\\Core\\Util\\StringUtils` class::

    use Symfony\Component\Security\Core\Util\StringUtils;

    // is password1 equals to password2?
    $bool = StringUtils::equals($password1, $password2);

Generating a secure Random Number
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Whenever you need to generate a secure random number, you are highly
encouraged to use the Symfony
:class:`Symfony\\Component\\Security\\Core\\Util\\SecureRandom` class::

    use Symfony\Component\Security\Core\Util\SecureRandom;

    $generator = new SecureRandom();
    $random = $generator->nextBytes(10);

The
:method:`Symfony\\Component\\Security\\Core\\Util\\SecureRandom::nextBytes`
methods returns a random string composed of the number of characters passed as
an argument (10 in the above example).

The SecureRandom class works better when OpenSSL is installed but when it's
not available, it falls back to an internal algorithm, which needs a seed file
to work correctly. Just pass a file name to enable it::

    $generator = new SecureRandom('/some/path/to/store/the/seed.txt');
    $random = $generator->nextBytes(10);

.. note::

    You can also access a secure random instance directly from the Symfony
    dependency injection container; its name is ``security.secure_random``.

Final Words
-----------

Security can be a deep and complex issue to solve correctly in your application.
Fortunately, Symfony's security component follows a well-proven security
model based around *authentication* and *authorization*. Authentication,
which always happens first, is handled by a firewall whose job is to determine
the identity of the user through several different methods (e.g. HTTP authentication,
login form, etc). In the cookbook, you'll find examples of other methods
for handling authentication, including how to implement a "remember me" cookie
functionality.

Once a user is authenticated, the authorization layer can determine whether
or not the user should have access to a specific resource. Most commonly,
*roles* are applied to URLs, classes or methods and if the current user
doesn't have that role, access is denied. The authorization layer, however,
is much deeper, and follows a system of "voting" so that multiple parties
can determine if the current user should have access to a given resource.
Find out more about this and other topics in the cookbook.

Learn more from the Cookbook
----------------------------

* :doc:`Forcing HTTP/HTTPS </cookbook/security/force_https>`
* :doc:`Blacklist users by IP address with a custom voter </cookbook/security/voters>`
* :doc:`Access Control Lists (ACLs) </cookbook/security/acl>`
* :doc:`/cookbook/security/remember_me`

.. _`JMSSecurityExtraBundle`: http://jmsyst.com/bundles/JMSSecurityExtraBundle/1.2
.. _`FOSUserBundle`: https://github.com/FriendsOfSymfony/FOSUserBundle
.. _`implement the \Serializable interface`: http://php.net/manual/en/class.serializable.php
.. _`functions-online.com`: http://www.functions-online.com/sha1.html
.. _`Timing attack`: http://en.wikipedia.org/wiki/Timing_attack
