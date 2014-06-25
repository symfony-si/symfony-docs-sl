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

Z uporabo oblike zahtevka (kot je definiran s ``_format`` spremenljivko),
Symfony2 tu avtomatsko izbere pravo predlogo ``hello.xml.twig``:

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
     * @Route(
     *     "/hello/{name}.{_format}",
     *     defaults = { "_format" = "html" },
     *     requirements = { "_format" = "html|xml|json" },
     *     name = "_demo_hello"
     * )
     * @Template()
     */
    public function helloAction($name)
    {
        return array('name' => $name);
    }

Krmilnik se bo sedaj ujemal z URL-ji kot je ``/demo/hello/Fabien.xml`` ali
``/demo/hello/Fabien.json``.

Vnos ``requirements`` definira običajne izraze, s katerimi se morajo spremenljivke
ujemati. V tem primeru, če poskusite zahtevati ``/demo/hello/Fabien.js``
vir, boste dobili 404 HTTP napako, saj se ne ujema z zahtevo ``_format``.

Preusmerjanje in posredovanje
-----------------------------

Če želite preusmeriti uporabnika na drugo stran, uporabite metodo ``redirect()``::

    return $this->redirect($this->generateUrl('_demo_hello', array('name' => 'Lucas')));

Metoda ``generateUrl()`` je ista metoda kot je uporabljena funkcija ``path()`` v
predlogah. Potrebuje ime poti in polje parametrov kot argumente in vrne
povezan prijazen URL.

Lahko tudi interno posredujete akcijo drugi z uporabo ``forward()``
metode:

    return $this->forward('AcmeDemoBundle:Hello:fancy', array(
        'name'  => $name,
        'color' => 'green'
    ));

Prikazovanje strani z napakami
------------------------------

Napake se bodo neizogibno zgodile med izvrševanjem vsake spletne aplikacije.
V primeru napak ``404``, Symfony vključi priročno bljižnico, ki jo lahko
uporabite v vašem krmilniku::

    throw $this->createNotFoundException();

Za napake ``500``, samo izvrzite (throw) splošno PHP izjemo znotraj krmilnika in
Symfony jo bo pretvoril v ustrezno stran z napako ``500``::

    throw new \Exception('Something went wrong!');

Pridobitev informacij iz zahtevka
---------------------------------

Symfony avtomatično injicira objekt ``Request``, ko ima krmilnik
argument, katerega tip je namignjen s ``Symfony\Component\HttpFoundation\Request``::

    use Symfony\Component\HttpFoundation\Request;

    public function indexAction(Request $request)
    {
        $request->isXmlHttpRequest(); // is it an Ajax request?

        $request->getPreferredLanguage(array('en', 'fr'));

        $request->query->get('page');   // get a $_GET parameter

        $request->request->get('page'); // get a $_POST parameter
    }

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

    use Symfony\Component\HttpFoundation\Request;

    public function indexAction(Request $request)
    {
        $session = $this->request->getSession();

        // store an attribute for reuse during a later user request
        $session->set('foo', 'bar');

        // get the value of a session attribute
        $foo = $session->get('foo');

        // use a default value if the attribute doesn't exist
        $foo = $session->get('foo', 'default_value');
    }

Lahko tudi shranite "flash sporočila", ki bodo avtomatsko izbrisana po naslednjem zahtevku.
So uporabna, ko potrebujete nastaviti, uspešno sporočilo pred preusmerjanjem
uporabnika na drugo stran (ki bo nato prikazala sporočilo)::

    // store a message for the very next request (in a controller)
    $session->getFlashBag()->add('notice', 'Congratulations, your action succeeded!');

.. code-block:: html+jinja

    {# display the flash message in the template #}
    <div>{{ app.session.flashbag.get('notice') }}</div>

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

V tem primeru bo vir predpomnjen za en dan (``86400`` sekund).
Predpomnenje vira je upravljano s strani samega Symfony2. Vendar ker je predpomnenje upravljano
z uporabo standardnih HTTP glav predpomnilnika, lahko uporabite Varnish ali Squid brez, da morate
spremeniti eno vrstico kode v vaši aplikaciji.

Zaključne misli
---------------

To je vse, kar se tega tiče in nisem niti prepričan, da ste porabili celotnih
10 minut. Bili ste na hitro seznanjeni s paketi v prvem delu in vse lastnosti,
o katerih ste se naučili do sedaj, so del paketov jedra ogrodja.
Vendar zahvaljujoč paketov, je vse v Symfony2 možno razširiti in zamenjati.
To je tema :doc:`naslednjega poglavja tega vodiča<the_architecture>`.
