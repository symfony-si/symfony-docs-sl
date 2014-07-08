SensioFrameworkExtraBundle
==========================

Privzeti Symfony2 ``FrameworkBundle`` implementira osnovno vendar robustno in
fleksibilno MVC ogrodje. `SensioFrameworkExtraBundle`_ ga razširja in dodaja lepe
konvencije in anotacije. Omogoča bolj jedrnate krmilnike.

Namestitev
----------

`Prenesite`_ paket in ga dajte pod imenski prostor ``Sensio\Bundle\``.
Nato ga, kot vsak drug paket, vključite v vaš razred Kernel::

    public function registerBundles()
    {
        $bundles = array(
            ...

            new Sensio\Bundle\FrameworkExtraBundle\SensioFrameworkExtraBundle(),
        );

        ...
    }

Če planirate uporabiti ali ustvariti anotacije za krmilnike, zagotovite posodobiti
vaš ``autoload.php`` z dodajanjem sledeče vrstice::

    Doctrine\Common\Annotations\AnnotationRegistry::registerLoader(array($loader, 'loadClass'));

Nastavitve
----------

Vse lastnosti ponujene s strani paketa so privzeto omogočene, ko je paket
registriran v vašem Kernel razredu.

Privzete nastavitve so, kot sledi:

.. configuration-block::

    .. code-block:: yaml

        sensio_framework_extra:
            router:   { annotations: true }
            request:  { converters: true, auto_convert: true }
            view:     { annotations: true }
            cache:    { annotations: true }
            security: { annotations: true }

    .. code-block:: xml

        <!-- xmlns:sensio-framework-extra="http://symfony.com/schema/dic/symfony_extra" -->
        <sensio-framework-extra:config>
            <router annotations="true" />
            <request converters="true" auto_convert="true" />
            <view annotations="true" />
            <cache annotations="true" />
            <security annotations="true" />
        </sensio-framework-extra:config>

    .. code-block:: php

        // load the profiler
        $container->loadFromExtension('sensio_framework_extra', array(
            'router'   => array('annotations' => true),
            'request'  => array('converters' => true, 'auto_convert' => true),
            'view'     => array('annotations' => true),
            'cache'    => array('annotations' => true),
            'security' => array('annotations' => true),
        ));

Lahko onemogočite nekatere anotacije in konvencije z definiranjem ene ali več
nastavitev na false.

Anotacije za krmilnike
----------------------

Anotacije so odličen način za enostavno nastavitev vaših krmilnikov iz
usmerjevalnika na nastavitve predpomnilnika.

Tudi če anotacije niso prvotna lastnost PHP, imajo še vedno mnoge
prednosti pred klasičnimi nastavitvenimi metodami Symfony2:

* Koda in nastavitve so na istem mestu (razred krmilnika);
* Enostavne za naučiti in uporabljati;
* Jedrnate za pisanje;
* Naredi vaš krmilnik vitek (saj je njegova izključna odgovornost dobiti podatke iz
  modela).

.. tip::

   Če uporabljate razrede pogleda, so anotacije odličen način, da se izognete izdelavi
   razredov pogleda za enostavne in pogoste primere uporabe.

Sledeče anotacije so definirane s strani paketa:

.. toctree::
   :maxdepth: 1

   annotations/routing
   annotations/converters
   annotations/view
   annotations/cache
   annotations/security

Ta primer prikazuje vse anotacije, ki so na voljo v akciji::

    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Route;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Cache;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Template;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\ParamConverter;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Method;
    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Security;

    /**
     * @Route("/blog")
     * @Cache(expires="tomorrow")
     */
    class AnnotController extends Controller
    {
        /**
         * @Route("/")
         * @Template
         */
        public function indexAction()
        {
            $posts = ...;

            return array('posts' => $posts);
        }

        /**
         * @Route("/{id}")
         * @Method("GET")
         * @ParamConverter("post", class="SensioBlogBundle:Post")
         * @Template("SensioBlogBundle:Annot:show.html.twig", vars={"post"})
         * @Cache(smaxage="15", lastmodified="post.getUpdatedAt()", etag="'Post' ~ post.getId() ~ post.getUpdatedAt()")
         * @Security("has_role('ROLE_ADMIN') and is_granted('POST_SHOW', post)")
         */
        public function showAction(Post $post)
        {
        }
    }

Kot metoda ``showAction`` omogoča nekatere priročne konvencije, lahko nekatere
anotacije izpustite::

    /**
     * @Route("/{id}")
     * @Cache(smaxage="15", lastModified="post.getUpdatedAt()", ETag="'Post' ~ post.getId() ~ post.getUpdatedAt()")
     * @Security("has_role('ROLE_ADMIN') and is_granted('POST_SHOW', post)")
     */
    public function showAction(Post $post)
    {
    }

Usmeritve morajo biti uvožene, da so aktivne kot katerikoli drugi viri usmeritev,
glejte :ref:`Annotated Routes Activation<frameworkextra-annotations-routing-activation>` za
podrobnosti.

.. _`SensioFrameworkExtraBundle`: https://github.com/sensio/SensioFrameworkExtraBundle
.. _`Download`: http://github.com/sensio/SensioFrameworkExtraBundle
