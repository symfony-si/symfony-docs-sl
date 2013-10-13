.. index::
    single: Configuration reference; Kernel class

Nastavitve v jedru (Kernel) (npr. AppKernel)
============================================

Nekaj nastavitev je lahko urejenih v samem razredu Kernel (ponavadi imenovan
``app/AppKernel.php``). To lahko naredite preko prepisovanja določenih metod
in starševskega razreda :class:`Symfony\\Component\\HttpKernel\\Kernel`.

Nastavitev
-----------

* `Charset`_
* `Kernel Name`_
* `Root Directory`_
* `Cache Directory`_
* `Log Directory`_

Charset
~~~~~~~

**type**: ``string`` **default**: ``UTF-8``

Ta nastavitev vrne nabor znakov, ki je uporabljen v aplikaciji. Za spremembo, prepišite
metodo :method:`Symfony\\Component\\HttpKernel\\Kernel::getCharset` in vrnite drug
nabor znakov, na primer::

    // app/AppKernel.php

    // ...
    class AppKernel extends Kernel
    {
        public function getCharset()
        {
            return 'ISO-8859-1';
        }
    }

Kernel Name
~~~~~~~~~~~

**type**: ``string`` **default**: ``app`` (i.e. the directory name holding the kernel class)

Za spremembo te nastavitve, prepišite metodo :method:`Symfony\\Component\\HttpKernel\\Kernel::getName`.
Alternativno premaknite vaše jedro v drug direktorij. Na primer, če
ste premaknili jedro v ``foo`` direktorij (namesto v ``app``),
bo ime jedra potem ``foo``.

Ime jedra ni dejansko direktno pomembno - uporabljeno je pri
generiranju predpomnilniških datotek. Če imate aplikacijo z večimi jedri,
je najenostavnejša pot narediti, da ima vsako unikatno ime z dupliciranjem
``app`` direktorija in ga preimenovati v nekaj drugega (npr. ``foo``).

Root Directory
~~~~~~~~~~~~~~

**type**: ``string`` **default**: the directory of ``AppKernel``

To vrne vrhnji direktorij v vašem jedru. Če uporabljate Symfony standardno
izdajo, se vrhnji direktorij sklicuje na ``app`` direktorij.

Da spremenite to nastavitev, prepišite metodo
:method:`Symfony\\Component\\HttpKernel\\Kernel::getRootDir`::

    // app/AppKernel.php

    // ...
    class AppKernel extends Kernel
    {
        // ...

        public function getRootDir()
        {
            return realpath(parent::getRootDir().'/../');
        }
    }

Cache Directory
~~~~~~~~~~~~~~~

**type**: ``string`` **default**: ``$this->rootDir/cache/$this->environment``

To vrne pot do predpomnilniškega direktorija. Za spremembo, prepišite
metodo :method:`Symfony\\Component\\HttpKernel\\Kernel::getCacheDir`. Preberite
":ref:`override-cache-dir`" za več informacij.

Log Directory
~~~~~~~~~~~~~

**type**: ``string`` **default**: ``$this->rootDir/logs``

To vrne pot do direktorija dnevnikov. Da ga spremenite, prepišite
metodo :method:`Symfony\\Component\\HttpKernel\\Kernel::getLogDir`. Preberite
":ref:`override-logs-dir`" za več informacij.
