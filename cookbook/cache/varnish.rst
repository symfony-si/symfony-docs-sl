.. index::
    single: Cache; Varnish

Kako uporabiti Varnish za pohitritev moje spletne strani
========================================================

Ker predpomnilnik Symfony2 uporablja standardne glave HTTP predpomnilnika,
je :ref:`symfony-gateway-cache` lahko enostavno zamenjan s katerimkoli drugim obratnim
proksijem. `Varnish`_ je močen, odprto kodni HTTP pospeševalnik zmožen streženja
predpomnjene vsebine hitro in vključuje podporo za t.i. :ref:`Edge Side Includes <edge-side-includes>`.

.. index::
    single: Varnish; configuration

Nastavitev
----------

Kot videno prej, je Symfony2 dovolj pameten, da zazna ali govori z obratnim
proksijem, ki razume ESI ali ne. Deluje takoj, ko
uporabite Symfony2 obratni proksi, vendar morate določene nastavitve, da
deluje z Varnish-em. Zahvaljujoče, Symfony2 se zanaša na še drug standard
napisan s strani Akamaï (`Edge Architecture`_), tako da nastavitveni nasveti v
tem poglavju so lahko uporabni tudi če ne uporabljate Symfony2.

.. note::

    Varnish samo podpira atribut ``src`` za značke ESI (``onerror`` in
    ``alt`` atributi so prezrti).

Najprej nastavite Varnish, da oglašuje svojo ESI podporo z dodajanjem
glave ``Surrogate-Capability`` na zahtevke posredovane ozadju
aplikacije:

.. code-block:: text

    sub vcl_recv {
        // Add a Surrogate-Capability header to announce ESI support.
        set req.http.Surrogate-Capability = "abc=ESI/1.0";
    }

Nato optimizirajte Varnish, da samo prevede vsebino odziva, ko je
vsaj ena značka ESI s preverjanjem glave ``Surrogate-Control``, ki
jo Symfony2 doda avtomatsko:

.. code-block:: text

    sub vcl_fetch {
        /*
        Check for ESI acknowledgement
        and remove Surrogate-Control header
        */
        if (beresp.http.Surrogate-Control ~ "ESI/1.0") {
            unset beresp.http.Surrogate-Control;

            // For Varnish >= 3.0
            set beresp.do_esi = true;
            // For Varnish < 3.0
            // esi;
        }
    }

.. caution::

    Stiskanje z ESI ni bilo podprto v Varnish-u do verzije 3.0
    (preberite `GZIP in Varnish`_). Če ne uporabljate Varnish 3.0, dajte spletni
    strežnik pred Varnish za izvajanje stiskanja.

.. index::
    single: Varnish; Invalidation

Razveljavitev predpomnilnika
----------------------------

Nikoli vam ne bi smelo biti potrebno razveljavljati predpomnjenih podatkov, ker je razveljavitev že
izvorno upoštevana v modelih HTTP predpomnilnika (glejte :ref:`http-cache-invalidation`).

Vseeno pa je Varnish možno nastaviti, da sprejema posebno HTTP ``PURGE`` metodo,
ki bo razveljavila predpomnilnik za dani vir:

.. code-block:: text

    /*
     Connect to the backend server
     on the local machine on port 8080
     */
    backend default {
        .host = "127.0.0.1";
        .port = "8080";
    }

    sub vcl_recv {
        /*
        Varnish default behaviour doesn't support PURGE.
        Match the PURGE request and immediately do a cache lookup,
        otherwise Varnish will directly pipe the request to the backend
        and bypass the cache
        */
        if (req.request == "PURGE") {
            return(lookup);
        }
    }

    sub vcl_hit {
        // Match PURGE request
        if (req.request == "PURGE") {
            // Force object expiration for Varnish < 3.0
            set obj.ttl = 0s;
            // Do an actual purge for Varnish >= 3.0
            // purge;
            error 200 "Purged";
        }
    }

    sub vcl_miss {
        /*
        Match the PURGE request and
        indicate the request wasn't stored in cache.
        */
        if (req.request == "PURGE") {
            error 404 "Not purged";
        }
    }

.. caution::

    Nekako morate zaščititi ``PURGE`` HTTP metodo, da se izognete naključnim ljudem,
    ki splaknejo vaše predpomnjene podatke. To lahko naredite z nastavitvijo dostopnega seznama:

    .. code-block:: text

        /*
         Connect to the backend server
         on the local machine on port 8080
         */
        backend default {
            .host = "127.0.0.1";
            .port = "8080";
        }

        // Acl's can contain IP's, subnets and hostnames
        acl purge {
            "localhost";
            "192.168.55.0"/24;
        }

        sub vcl_recv {
            // Match PURGE request to avoid cache bypassing
            if (req.request == "PURGE") {
                // Match client IP to the acl
                if (!client.ip ~ purge) {
                    // Deny access
                    error 405 "Not allowed.";
                }
                // Perform a cache lookup
                return(lookup);
            }
        }

        sub vcl_hit {
            // Match PURGE request
            if (req.request == "PURGE") {
                // Force object expiration for Varnish < 3.0
                set obj.ttl = 0s;
                // Do an actual purge for Varnish >= 3.0
                // purge;
                error 200 "Purged";
            }
        }

        sub vcl_miss {
            // Match PURGE request
            if (req.request == "PURGE") {
                // Indicate that the object isn't stored in cache
                error 404 "Not purged";
            }
        }

Usmerjanje in X-FORWARDED glave
-------------------------------

Za zagotovitev, da Symfony usmerjevalnik generira URL-je pravilno z Varnishem,
morajo biti dodane ustrezne ```X-Forwarded``` glave, da je Symfony seznanjen z
originalno številko porta zahtevka. Točno kako se to naredi, zavisi
na vaših nastavitvah. Kot enostaven primer, Varnish in vaš spletni strežnik sta
na isti napravi in Varnish posluša na enem portu (npr. 80) in Apache
na drugem (npr. 8080) V tem primeru bi Varnish moral dodati ``X-Forwarded-Port``
glavo, da Symfony aplikacija ve, da je originalna številka porta
80 in ne 8080.

Če ta glava ni nastavljena pravilno, Symfony lahko doda ``8080``, ko generira
absolutne URL-je:

.. code-block:: text

    sub vcl_recv {
        if (req.http.X-Forwarded-Proto == "https" ) {
            set req.http.X-Forwarded-Port = "443";
        } else {
            set req.http.X-Forwarded-Port = "80";
        }
    }

.. note::

    Ne pozabite nastaviti :ref:`framework.trusted_proxies <reference-framework-trusted-proxies>`
    v Symfony nastavitvah, da je Varnish viden kot zaupljiv proksi
    in uporabljene so glave ``X-Forwarded-``.

.. _`Varnish`: https://www.varnish-cache.org
.. _`Edge Architecture`: http://www.w3.org/TR/edge-arch
.. _`GZIP in Varnish`: https://www.varnish-cache.org/docs/3.0/phk/gzip.html
