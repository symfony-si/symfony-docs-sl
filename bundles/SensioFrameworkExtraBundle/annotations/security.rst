@Security
=========

Uporaba
-------

Anotacija ``@Security`` omejuje dostop na krmilnikih::

    use Sensio\Bundle\FrameworkExtraBundle\Configuration\Security;

    class PostController extends Controller
    {
        /**
         * @Security("has_role('ROLE_ADMIN')")
         */
        public function indexAction()
        {
            // ...
        }
    }

Izraz lahko uporablja vse funkcije, ki jih lahko uporabite v
sekciji ``access_control`` nastavitev varnostnega paketa z dodatkom
funkcije ``is_granted()``.

Izraz ima dostop do sledečih spremenljivk:

* ``token``: trenutni varnostni žeton;
* ``user``: Trenutni objekt uporabnika;
* ``request``: Instanca zahtevka;
* ``roles``: Uporabnikove vloge;
* in vsi atributi zahtevka.

Funkcija ``is_granted()`` vam omogoča omejiti dostop na osnovi spremenljivk
podanih krmilniku::

    /**
     * @Security("is_granted('POST_SHOW', post)")
     */
    public function showAction(Post $post)
    {
    }

.. note::

    Definiranje anotacije ``Security`` ima enak učinek, kot definiranje
    pravila kontrole dostopa, vendar je bolj efektivna, saj je preverjanje urejeno samo,
    ko je ta specifična usmeritev dostopana.

.. tip::

    Lahko dodate tudi anotacijo ``@Security`` na razredu krmilnika.
