Varnostne težave
================

Ta dokument razlaga, kako se ravna s Symfony varnostnimi težavami s strani
jedra ekipe Symfony (Symfony koda je gostovana na glavnem ``symfony/symfony``
`Git repozitoriju`_).

Poročanje o varnostni težavi
----------------------------

Če mislite, da ste našli varnostno težavo v Symfony, ne uporabite
dopisnega seznama ali sledilnika hroščev in ne objavite tega javno. Namesto tega
morajo biti vse varnostne težave poslane na **security [at] symfony.com**. E-pošta
poslana na ta naslov je posredovana na zasebni dopisni seznam jedra ekipe Symfony.

Proces reševanja
----------------

Za vsako poročilo najprej poskušamo potrditi ranljivost. Ko je to
potrjeno, jedro ekipe dela na rešitvi po sledečih korakih:

1. Pošlje se priznanje najditelju;
2. Delo na popravku;
3. Pridobitev CVE identifikatorja iz mitre.org;
4. Napiše se varnostna objava za uradni Symfony `blog`_ o
   ranljivosti. Ta objava bi morala vsebovati sledeče infomracije:

   * naslov, ki vedno vključuje "Security release" niz;
   * opis ranljivosti;
   * prizadete verzije;
   * možna izkoriščanja;
   * kako popraviti/nadgraditi/obiti vplivane aplikacije;
   * CVE identifikator;
   * zasluge.
5. Pošlje se popravek in obvestilo najditelju za pregled;
6. Uporaba popravka v vseh vzdrževanih verzijah Symfony-ja;
7. Zapakiranje novih verzij za vse prizadete verzije;
8. Objava obvestila na uradni Symfony `blog`_ strani (dodana mora biti tudi
   v "`Security Advisories`_" kategorijo);
9. Posodobitev seznama varnostnih svetovanj (glejte spodaj).

.. note::

    Izdaje, ki vključujejo varnostne težave ne bi smele biti urejene v soboto ali
    nedeljo, razen če je ranljivost bila javno objavljena.

.. note::

    Medtem ko delamo na popravku, prosimo, ne razkrivajte težave javno.

.. note::

    Resolucija vzame med nekaj dni do meseca, odvisno od njene kompleksnosti in
    koordinacije z podrejenimi projekti (glejte naslednji
    odstavek).

Sodelovanje s podrejenimi odprtokodnimi projekti
------------------------------------------------

Kot je Symfony uporabljen s strani veliko odprto kodnih projektov, smo standardizirali
način, kako Symfony varnostna ekipa sodeluje na varnostnih težavah s podrejenimi
projekti. Proces deluje sledeče:

1. Ko Symfony varnostna ekipa potrdi varnostno težavo, nemudoma
pošlje e-pošto podrejenim projektnim ekipam, da jih obvesti o težavi;

2. Symfony varnostna ekipa izdela zasebni Git repozitorij za enostavnejše
sodelovanje na težavi in dostop do tega repozitorija je dan Symfony varnostni
ekipi, Symfony uporabnikom, ki prispevajo in so pod vplivom te težave in
enemu izmed reprezentativnih oseb vsakega podrejenega projekta;

3. Vsi ljudje z dostopom do zasebnega repozitorija delajo na reševanju, da
se težava odpravi preko "pull request-ov", pregleda kode in komentarjev;

4. Ko je popravek najden, vsi vključeni projekti sodelujejo, da najdejo
najboljši datum za skupno izdajo (ni garancije, da bodo vse izdaje na voljo
istočasno, vendar se trudimo, da so na voljo približno istočasno). Ko
težava ni znana, da bo izkoriščena v javnosti, obdobje dveh tednov deluje
kot razumen obseg časa.

Seznam podrejenih projektov, ki sodelujejo v tem procesu, je skrbovan čimmanjše
možno, da je možno bolje upravljati proces zaupnih informacij prioritetno glede
na razkritje. Tako se vključi projekte po lastni presoji Symfony varnostne ekipe.

Od danes, sledeči projekti so potrjeni za ta proces in so del
podrejenih projektov, vključenih v ta proces:

* Drupal (izdaje se običajno zgodijo ob sredah)
* eZPublish

Varnostna opozorila
-------------------

Ta sekcija indeksira varnostne ranljivosti, ki so bile popravljene v Symfony
izdajah z začetkom od Symfony 1.0.0:

* October 10, 2013: `Security releases: Symfony 2.0.25, 2.1.13, 2.2.9, and 2.3.6 released <http://symfony.com/blog/security-releases-cve-2013-5958-symfony-2-0-25-2-1-13-2-2-9-and-2-3-6-released>`_ (`CVE-2013-5958 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2013-5958>`_)
* August 7, 2013: `Security releases: Symfony 2.0.24, 2.1.12, 2.2.5, and 2.3.3 released <http://symfony.com/blog/security-releases-symfony-2-0-24-2-1-12-2-2-5-and-2-3-3-released>`_ (`CVE-2013-4751 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2013-4751>`_ and `CVE-2013-4752 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2013-4752>`_)
* January 17, 2013: `Security release: Symfony 2.0.22 and 2.1.7 released <http://symfony.com/blog/security-release-symfony-2-0-22-and-2-1-7-released>`_ (`CVE-2013-1348 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2013-1348>`_ and `CVE-2013-1397 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2013-1397>`_)
* December 20, 2012: `Security release: Symfony 2.0.20 and 2.1.5 <http://symfony.com/blog/security-release-symfony-2-0-20-and-2-1-5-released>`_  (`CVE-2012-6431 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2012-6431>`_ and `CVE-2012-6432 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2012-6432>`_)
* November 29, 2012: `Security release: Symfony 2.0.19 and 2.1.4 <http://symfony.com/blog/security-release-symfony-2-0-19-and-2-1-4>`_
* November 25, 2012: `Security release: symfony 1.4.20 released  <http://symfony.com/blog/security-release-symfony-1-4-20-released>`_ (`CVE-2012-5574 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2012-5574>`_)
* August 28, 2012: `Security Release: Symfony 2.0.17 released <http://symfony.com/blog/security-release-symfony-2-0-17-released>`_
* May 30, 2012: `Security Release: symfony 1.4.18 released <http://symfony.com/blog/security-release-symfony-1-4-18-released>`_ (`CVE-2012-2667 <http://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2012-2667>`_)
* February 24, 2012: `Security Release: Symfony 2.0.11 released <http://symfony.com/blog/security-release-symfony-2-0-11-released>`_
* November 16, 2011: `Security Release: Symfony 2.0.6 <http://symfony.com/blog/security-release-symfony-2-0-6>`_
* March 21, 2011: `symfony 1.3.10 and 1.4.10: security releases <http://symfony.com/blog/symfony-1-3-10-and-1-4-10-security-releases>`_
* June 29, 2010: `Security Release: symfony 1.3.6 and 1.4.6 <http://symfony.com/blog/security-release-symfony-1-3-6-and-1-4-6>`_
* May 31, 2010: `symfony 1.3.5 and 1.4.5 <http://symfony.com/blog/symfony-1-3-5-and-1-4-5>`_
* February 25, 2010: `Security Release: 1.2.12, 1.3.3 and 1.4.3 <http://symfony.com/blog/security-release-1-2-12-1-3-3-and-1-4-3>`_
* February 13, 2010: `symfony 1.3.2 and 1.4.2 <http://symfony.com/blog/symfony-1-3-2-and-1-4-2>`_
* April 27, 2009: `symfony 1.2.6: Security fix <http://symfony.com/blog/symfony-1-2-6-security-fix>`_
* October 03, 2008: `symfony 1.1.4 released: Security fix <http://symfony.com/blog/symfony-1-1-4-released-security-fix>`_
* May 14, 2008: `symfony 1.0.16 is out  <http://symfony.com/blog/symfony-1-0-16-is-out>`_
* April 01, 2008: `symfony 1.0.13 is out  <http://symfony.com/blog/symfony-1-0-13-is-out>`_
* March 21, 2008: `symfony 1.0.12 is (finally) out ! <http://symfony.com/blog/symfony-1-0-12-is-finally-out>`_
* June 25, 2007: `symfony 1.0.5 released (security fix) <http://symfony.com/blog/symfony-1-0-5-released-security-fix>`_

.. _Git repozitoriju:      https://github.com/symfony/symfony
.. _blog:                http://symfony.com/blog/
.. _Security Advisories: http://symfony.com/blog/category/security-advisories
