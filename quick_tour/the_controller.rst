Krmilnik
========

Še vedno tu po prvih dveh delih? Postajate Symfony2 odvisnik!
Brez odlašanja, odkrijte kaj krmilnik lahko naredi za vas.

Uporaba oblik
-------------

Dandanes bi morale biti spletne aplikacije zmožne dostaviti z več kot
samo HTML stranmi. Od XML za RSS feeds ali spletne storitve, do JSON za
Ajax zahtevke, je na izbiro veliko različnih oblik. Podpora teh oblik
v Symfony2 je enostavna. Uredite pot z dodajanjem privzetih vrednosti za
``xml`` za ``_format`` spremenljivko::

    // src/Acme/DemoBundle/Controller/DemoController.php
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;

    // ...

    /**
     * @Route("/hello/{name}", defaults={"_format"="xml"}, name="_demo_hello")
     * @Template()
     */
    public function helloAction($name)
    {
        return array('name' => $name);
    }

Z uporabo oblike zahtevka (kot je definiran s ``_format`` vrednostjo), Symfony2
tu avtomatsko izbere pravo predlogo ``hello.xml.twig``:

.. code-block:: xml+php

    <!-- src/Acme/DemoBundle/Resources/views/Demo/hello.xml.twig -->
    <hello>
        <name>{{ name }}</name>
    </hello>

To je vse okrog tega. Za standardne oblike, Symfony2 tudi
avtomatsko izbere najboljšo ``Content-Type`` glavo za odziv. Če
želite podpirati različne oblike za eno akcijo, raje uporabite ``{_format}``
lokacijo v usmerni poti::

    // src/Acme/DemoBundle/Controller/DemoController.php
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;

    // ...

    /**
     * @Route("/hello/{name}.{_format}", defaults={"_format"="html"}, requirements={"_format"="html|xml|json"}, name="_demo_hello")
     * @Template()
     */
    public function helloAction($name)
    {
        return array('name' => $name);
    }

Krmilnik bo sedaj klican za URL-je kot je ``/demo/hello/Fabien.xml`` ali
``/demo/hello/Fabien.json``.

Vnos ``requirements`` definira običajne izraze, s katerimi se mora lokacija
ujemati. V tem primeru, če poskusite zahtevati ``/demo/hello/Fabien.js``
vir, boste dobili 404 HTTP napako, saj se ne ujema z zahtevo ``_format``.

Preusmerjanje in posredovanje
-----------------------------

Če želite preusmeriti uporabnika na drugo stran, uporabite metodo ``redirect()``::

    return $this->redirect($this->generateUrl('_demo_hello', array('name' => 'Lucas')));

Metoda ``generateUrl()`` je ista metoda kot je uporabljena funkcija ``path()`` v
predlogah. Potrebuje ime poti in polje parametrov kot argumente in vrne
povezan prijazen URL.

Lahko tudi enostavno posredujete akcijo k drugi z metodo ``forward()``.
Interno, Symfony naredi "pod-zahtevek" in vrne objekt ``Response``
iz tega pod-zahtevka::

    $response = $this->forward('AcmeDemoBundle:Hello:fancy', array('name' => $name, 'color' => 'green'));

    // ... do something with the response or return it directly

Pridobitev informacij iz zahtevka
---------------------------------

Poleg vrednosti poti lokacij, ima krmilnik tudi dostop
do objekta ``Request``::

    $request = $this->getRequest();

    $request->isXmlHttpRequest(); // is it an Ajax request?

    $request->getPreferredLanguage(array('en', 'fr'));

    $request->query->get('page'); // get a $_GET parameter

    $request->request->get('page'); // get a $_POST parameter

V predlogi lahko dostopate do objekta ``Request`` tudi preko
``app.request`` spremenljivke:

.. code-block:: html+jinja

    {{ app.request.query.get('page') }}

    {{ app.request.parameter('page') }}

Pridobitev podatkov v sejo
--------------------------

Tudi če je HTTP protokol brez stanja, Symfony2 ponuja lep objekt za seje,
ki predstavlja klienta (ali pravega uporabnika z brskalnikom, bot-a ali
spletni servis). Med dvema zahtevkoma, Symfony2 shranjuje atribute v piškotek
z uporabo prvotnih PHP sej.

Shranjevanje in branje informacij iz seje je enostavno dosegljivo iz
kateregakoli krmilnika::

    $session = $this->getRequest()->getSession();

    // store an attribute for reuse during a later user request
    $session->set('foo', 'bar');

    // in another controller for another request
    $foo = $session->get('foo');

    // use a default value if the key doesn't exist
    $filters = $session->get('filters', array());

Lahko tudi shranite majhna sporočila, ki bodo na voljo samo za naslednji zahtevek::

    // store a message for the very next request (in a controller)
    $session->getFlashBag()->add('notice', 'Congratulations, your action succeeded!');

    // display any messages back in the next request (in a template)

    {% for flashMessage in app.session.flashbag.get('notice') %}
        <div>{{ flashMessage }}</div>
    {% endfor %}

To je uporabno, ko morate nastaviti uspešno sporočilo pred preusmeritvijo
uporabnika na drugo stran (kar bo potem prikazalo sporočilo). Prosimo, pomnite,
da ko uporabite has() namesto get(), flash sporočilo ne bo razjasnjeno in
zato ostane na voljo med naslednjim zahtevkom.

Varnost virov
-------------

Symfony standardna izdaja prihaja z enostavno varnostno nastavitvijo, ki
ustreza najpogostejšim potrebam:

.. code-block:: yaml

    # app/config/security.yml
    security:
        encoders:
            Symfony\Component\Security\Core\User\User: plaintext

        role_hierarchy:
            ROLE_ADMIN:       ROLE_USER
            ROLE_SUPER_ADMIN: [ROLE_USER, ROLE_ADMIN, ROLE_ALLOWED_TO_SWITCH]

        providers:
            in_memory:
                memory:
                    users:
                        user:  { password: userpass, roles: [ 'ROLE_USER' ] }
                        admin: { password: adminpass, roles: [ 'ROLE_ADMIN' ] }

        firewalls:
            dev:
                pattern:  ^/(_(profiler|wdt)|css|images|js)/
                security: false

            login:
                pattern:  ^/demo/secured/login$
                security: false

            secured_area:
                pattern:    ^/demo/secured/
                form_login:
                    check_path: /demo/secured/login_check
                    login_path: /demo/secured/login
                logout:
                    path:   /demo/secured/logout
                    target: /demo/

Ta nastavitev zahteva, da se uporabniki prijavijo za katerikoli URL,
ki se prične z ``/demo/secured`` in definira dva veljavna uporabnika:
``user`` in ``admin``. Še več, ``admin`` uporabnik ima vlogo ``ROLE_ADMIN``,
ki vključuje tudi vlogo ``ROLE_USER`` (glejte ``role_hierarchy`` nastavitev).

.. tip::

    Za bralnost so gesla shranjena v jasnem tekstu v tej enostavni nastavitvi,
    vendar lahko uporabite katerikoli zgoščevalni algoritem z urejanjem sekcije
    ``encoders``.

Obisk URL-ja ``http://localhost/app_dev.php/demo/secured/hello``
vas bo avtomatsko preusmeril na prijavni obrazec, ker je ta vir varovan s pomočjo
``požarnega zidu``.

.. note::

    Symfony2 varnostna plast je zelo fleksibilna in pride z mnogimi različnimi
    uporabniškimi ponudniki (kot je za Doctrine ORM) in ponudniki preverjanja
    pristnosti (kot so osnovni HTTP, HTTP presnova, ali X509 certifikati). Preberite
    ":doc:`/book/security`" poglavje knjige za več informacij, kako jih uporabiti
    in nastaviti.

Viri predpomnenja
-----------------

Takoj ko vaša spletna stran prične generirati več prometa, si boste želeli
izogniti generiranju istega vira znova in znova. Symfony2 uporablja glave HTTP
predpomnilnika za upravljanje virov predpomnenja. Za enostavne strategije predpomnenja
uporabite uporabno anotacijo ``@Cache()``::

    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Cache;

    /**
     * @Route("/hello/{name}", name="_demo_hello")
     * @Template()
     * @Cache(maxage="86400")
     */
    public function helloAction($name)
    {
        return array('name' => $name);
    }

V tem primeru bo vir predpomnjen za ena dan. Vendar lahko tudi uporabite
veljavnost namesto poteka ali kombinacijo obeh, če to boljše zadosti vašim
potrebam.

Viri predpomnenja so upravljani s Symfony2 vgrajenim povratnim proxy-jem. Vendar
ker je predpomnenje upravljano z uporabo običajnih glav HTTP predpomnilnika, lahko
zamenjate vgrajeni proxy z Varnish-em ali Squid-om in enostavno umerite vašo
aplikacijo.

.. note::

    Vendar kaj če ne morete predpomniti celotne strani? Symfony2 ima še vedno
    rešitev preko Edge Side Includes (ESI), ki je izvorno podprt. Naučite se več
    v ":doc:`/book/http_cache`" poglavju knjige.

Zaključne misli
---------------

To je vse, kar se tega tiče in nisem niti prepričan, da ste porabili celotnih
10 minut. Bili ste na hitro seznanjeni s paketi v prvem delu in vse lastnosti,
o katerih ste se naučili do sedaj, so del paketov jedra ogrodja.
Vendar zahvaljujoč paketov, je vse v Symfony2 možno razširiti in zamenjati.
To je tema :doc:`naslednjega poglavja tega vodiča<the_architecture>`.
