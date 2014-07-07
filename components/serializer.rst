.. index::
   single: Serializer
   single: Components; Serializer

Komponenta Serializer
=====================

   Komponenta Serizalizer je mišljena za uporabo spreminjanja objektov v
   specifičen format (XML, JSON, YAML, ...) in obratno.

Da to naredi, komponenta Serializer sledi sledeči
enostavni shemi.

.. _component-serializer-encoders:
.. _component-serializer-normalizers:

.. image:: /images/components/serializer/serializer_workflow.png

Kot vidite na sliki zgoraj, je polje uporabljeno kot posrednik.
Na ta način se bodo enkoderji ukvarjali samo s spreminjanjem specifičnih
**formatov** v **polja** in obratno. Na enak način se bodo normalizatorji
ukvarjali s spreminjanjem specifičnih **objektov** v **polja** in obratno.

Serializacija je komplicirana tema in medtem ko ta komponenta lahko ne deluje
v vseh primerih, je lahko uporabno orodje kot razvijate orodja za serializacijo
in deserializacijo vaših objektov.

Namesitev
---------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestitev preko Composer-ja </components/using_components>` (``symfony/serializer`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Serializer).

Uporaba
-------

Uporaba komponente Serializer je res enostavna. Potrebujete samo nastaviti
:class:`Symfony\\Component\\Serializer\\Serializer` in določiti
kateri enkoderji in normalizator bodo na voljo::

    use Symfony\Component\Serializer\Serializer;
    use Symfony\Component\Serializer\Encoder\XmlEncoder;
    use Symfony\Component\Serializer\Encoder\JsonEncoder;
    use Symfony\Component\Serializer\Normalizer\GetSetMethodNormalizer;

    $encoders = array(new XmlEncoder(), new JsonEncoder());
    $normalizers = array(new GetSetMethodNormalizer());

    $serializer = new Serializer($normalizers, $encoders);

Serializacija objekta
---------------------

Za namen tega primera, predpostavimo, da sledeči razred že
obstoja v vašem projektu::

    namespace Acme;

    class Person
    {
        private $age;
        private $name;
        private $sportsman;

        // Getters
        public function getName()
        {
            return $this->name;
        }

        public function getAge()
        {
            return $this->age;
        }

        // Issers
        public function isSportsman()
        {
            return $this->sportsman;
        }

        // Setters
        public function setName($name)
        {
            $this->name = $name;
        }

        public function setAge($age)
        {
            $this->age = $age;
        }

        public function setSportsman($sportsman)
        {
            $this->sportsman = $sportsman;
        }
    }

Sedaj, če želite serializirati ta objekt v JSON, potrebujete uporabiti samo
storitev Serializer ustvarjeno prej::

    $person = new Acme\Person();
    $person->setName('foo');
    $person->setAge(99);
    $person->setSportsman(false);

    $jsonContent = $serializer->serialize($person, 'json');

    // $jsonContent contains {"name":"foo","age":99,"sportsman":false}

    echo $jsonContent; // or return it in a Response

Prvi parameter od :method:`Symfony\\Component\\Serializer\\Serializer::serialize`
je objekt, ki bo serializiran in drugi je uporabljen za izviro ustreznega enkoderja,
v tem primeru :class:`Symfony\\Component\\Serializer\\Encoder\\JsonEncoder`.

Ignoriranje atributov, ko se serializira
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. versionadded:: 2.3
    Metoda :method:`GetSetMethodNormalizer::setIgnoredAttributes<Symfony\\Component\\Serializer\\Normalizer\\GetSetMethodNormalizer::setIgnoredAttributes>`
    je bila predstavljena v Symfony 2.3.

Kot opcija, obstaja način za ignoriranje atributov iz originalnega objekta, ko
serializate. Da odstranite te atribute, uporabite
metodo :method:`Symfony\\Component\\Serializer\\Normalizer\\GetSetMethodNormalizer::setIgnoredAttributes`
na definiciji normalizatorja::

    use Symfony\Component\Serializer\Serializer;
    use Symfony\Component\Serializer\Encoder\JsonEncoder;
    use Symfony\Component\Serializer\Normalizer\GetSetMethodNormalizer;

    $normalizer = new GetSetMethodNormalizer();
    $normalizer->setIgnoredAttributes(array('age'));
    $encoder = new JsonEncoder();

    $serializer = new Serializer(array($normalizer), array($encoder));
    $serializer->serialize($person, 'json'); // Output: {"name":"foo","sportsman":false}

Deserializacija objekta
-----------------------

Sedaj se boste naučili, kako narediti nasprotno. Tokrat bi bile informacije
razreda ``Perso`` enkodirane v XML formatu::

    $data = <<<EOF
    <person>
        <name>foo</name>
        <age>99</age>
        <sportsman>false</sportsman>
    </person>
    EOF;

    $person = $serializer->deserialize($data,'Acme\Person','xml');

V tem primeru :method:`Symfony\\Component\\Serializer\\Serializer::deserialize`
potrebuje tri parametre:

1. Informacija, ki bo dekodirana
2. Ime razreda v katerega bo ta informacija dekodirana
3. Enkoder uporabljen za pretvarjanje te informacije v polje

Uporaba kamelskih imen metod za atribute s podčrtajem
-----------------------------------------------------

.. versionadded:: 2.3
    Metoda :method:`GetSetMethodNormalizer::setCamelizedAttributes<Symfony\\Component\\Serializer\\Normalizer\\GetSetMethodNormalizer::setCamelizedAttributes>`
    je bila predstavljena v Symfony 2.3.

Včasih so imena lastnosti iz serializirane vsebine s podčrtaji (npr.
``first_name``). Običajno, ti atributi bodo uporabili get/set metode kot je
``getFirst_name``, ko je pa metoda ``getFirstName`` to kar res želite. Da
spremenite to obnašanje uporabite
metodo :method:`Symfony\\Component\\Serializer\\Normalizer\\GetSetMethodNormalizer::setCamelizedAttributes`
na definiciji normalizatorja::

    $encoder = new JsonEncoder();
    $normalizer = new GetSetMethodNormalizer();
    $normalizer->setCamelizedAttributes(array('first_name'));

    $serializer = new Serializer(array($normalizer), array($encoder));

    $json = <<<EOT
    {
        "name":       "foo",
        "age":        "19",
        "first_name": "bar"
    }
    EOT;

    $person = $serializer->deserialize($json, 'Acme\Person', 'json');

Kot končni rezultat, deserializator uporablja atribut ``first_name`` kot če
je bil ``first_name`` in uporablja metodi ``getFirstName`` in ``setFirstName``.

Serializacija atributov z logičnimi vrednostmi
----------------------------------------------

.. versionadded:: 2.5
    Podpora za ``is*`` dostopanje v
    :class:`Symfony\\Component\\Serializer\\Normalizer\\GetSetMethodNormalizer`
    je bila predstavljena v Symfony 2.5.

Če uporabljate isser metode (metode ki imajo predpono ``is``, kot je
``Acme\Person::isSportsman()``), bo komponenta Serializer avtomatično
detektirala in ga uporabila za serializacijo povezanih atributov.

Uporaba povratnih klicev za serializacijo lastnosti z instancami objektov
-------------------------------------------------------------------------

Ko serializirate, lahko nastavite povratni klic, da oblikujete določeno lastnost objekta::

    use Acme\Person;
    use Symfony\Component\Serializer\Encoder\JsonEncoder;
    use Symfony\Component\Serializer\Normalizer\GetSetMethodNormalizer;
    use Symfony\Component\Serializer\Serializer;

    $encoder = new JsonEncoder();
    $normalizer = new GetSetMethodNormalizer();

    $callback = function ($dateTime) {
        return $dateTime instanceof \DateTime
            ? $dateTime->format(\DateTime::ISO8601)
            : '';
    }

    $normalizer->setCallbacks(array('createdAt' => $callback));

    $serializer = new Serializer(array($normalizer), array($encoder));

    $person = new Person();
    $person->setName('cordoval');
    $person->setAge(34);
    $person->setCreatedAt(new \DateTime('now'));

    $serializer->serialize($person, 'json');
    // Output: {"name":"cordoval", "age": 34, "createdAt": "2014-03-22T09:43:12-0500"}

JMSSerializer
-------------

Popularna tretje-osebna knjižnica `JMS serializer`_ ponuja bolj
sofisticirano a bolj komplekso rešitev. Ta knjižnica vključuje
zmožnost nastaviti, kako bi objekti morali biti serializirani/deserializirani preko
anotacij (kot tudi YAML, XML in PHP), integracijo z Doctrine ORM
in upravljanje drugih kompleksnih primerov (npr. krožnih sklicev).

.. _`JMS serializer`: https://github.com/schmittjoh/serializer
.. _Packagist: https://packagist.org/packages/symfony/serializer
