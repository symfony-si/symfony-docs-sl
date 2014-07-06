.. index::
   single: Filesystem

Komponenta Filesystem
=====================

    Komponenta Filesystem ponuja osnovna orodja za datotečni sistem.

.. versionadded:: 2.1
    Komponenta Filesystem je bila predstavljena v Symfony 2.1. Prejšnji
    razred ``Filesystem`` je bil lociran v komponenti HttpKernel.

Namestitev
----------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestitev preko Composer-ja </components/using_components>` (``symfony/filesystem`` na `Packagist`_);
* Uporabite uradni repozitorij (https://github.com/symfony/Filesystem).

Uporaba
-------

Razred :class:`Symfony\\Component\\Filesystem\\Filesystem` je unikatna
končna točka za operacije datotečnega sistema::

    use Symfony\Component\Filesystem\Filesystem;
    use Symfony\Component\Filesystem\Exception\IOExceptionInterface;

    $fs = new Filesystem();

    try {
        $fs->mkdir('/tmp/random/dir/' . mt_rand());
    } catch (IOExceptionInterface $e) {
        echo "An error occurred while creating your directory at ".$e->getPath();
    }

.. versionadded:: 2.4
    ``IOExceptionInterface`` in njegova ``getPath`` metoda sta bili predstavljeni v
    Symfony 2.4. Pred 2.4, bi ujeli razred ``IOException``.

.. note::

    Metode :method:`Symfony\\Component\\Filesystem\\Filesystem::mkdir`,
    :method:`Symfony\\Component\\Filesystem\\Filesystem::exists`,
    :method:`Symfony\\Component\\Filesystem\\Filesystem::touch`,
    :method:`Symfony\\Component\\Filesystem\\Filesystem::remove`,
    :method:`Symfony\\Component\\Filesystem\\Filesystem::chmod`,
    :method:`Symfony\\Component\\Filesystem\\Filesystem::chown` in
    :method:`Symfony\\Component\\Filesystem\\Filesystem::chgrp` lahko dobijo
    niz, polje ali katerikoli objekt, ki implementira :phpclass:`Traversable` kot
    ciljni argument.

Mkdir
~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::mkdir` ustvari direktorij.
Na posix datotečnih sistemih, so direktoriji ustvarjeni s privzeto vrednostjo načina
`0777`. Lahko uporabite drugi argument, da nastavite vaš način::

    $fs->mkdir('/tmp/photos', 0700);

.. note::

    Lahko podate polje ali katerikoli :phpclass:`Traversable` objekt kot prvi
    argument.

Exists
~~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::exists` preveri
prisotnost vseh datotek ali direktorijev in vrne ``false``, če datoteka manjka::

    // this directory exists, return true
    $fs->exists('/tmp/photos');

    // rabbit.jpg exists, bottle.png does not exists, return false
    $fs->exists(array('rabbit.jpg', 'bottle.png'));

.. note::

    Lahko podate polje ali katerikoli :phpclass:`Traversable` objekt kot prvi
    argument.

Copy
~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::copy` je uporabljena za kopiranje
datotek. Če cilj že obstaja, je datoteka kopirana samo, če je izvorni
datum spremembe kasnejši kot ciljni. To obnašanje je lahko prepisano s
tretjim logičnim argumentom::

    // works only if image-ICC has been modified after image.jpg
    $fs->copy('image-ICC.jpg', 'image.jpg');

    // image.jpg will be overridden
    $fs->copy('image-ICC.jpg', 'image.jpg', true);

Touch
~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::touch` nastavi dostop in
čas spremembe za datoteko. Privzeto je uporabljen trenutni čas. Lahko nastavite
svojega z drugim argumentom. Tretji argument je dostopni čas::

    // set modification time to the current timestamp
    $fs->touch('file.txt');
    // set modification time 10 seconds in the future
    $fs->touch('file.txt', time() + 10);
    // set access time 10 seconds in the past
    $fs->touch('file.txt', time(), time() - 10);

.. note::

    Lahko podate polje ali katerikoli :phpclass:`Traversable` objekt kot prvi
    argument.

Chown
~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::chown` je uporabljena za spremembo
lastnika datoteke. Tretji argument je logična rekurzivna opcija::

    // set the owner of the lolcat video to www-data
    $fs->chown('lolcat.mp4', 'www-data');
    // change the owner of the video directory recursively
    $fs->chown('/video', 'www-data', true);

.. note::

    Lahko podate polje ali katerikoli :phpclass:`Traversable` objekt kot prvi
    argument.

Chgrp
~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::chgrp` je uporabljen za spremembo
skupine datoteke. Tretji argument je logična rekurzivna opcija::

    // set the group of the lolcat video to nginx
    $fs->chgrp('lolcat.mp4', 'nginx');
    // change the group of the video directory recursively
    $fs->chgrp('/video', 'nginx', true);

.. note::

    Lahko podate polje ali katerikoli :phpclass:`Traversable` objekt kot prvi
    argument.

Chmod
~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::chmod` je uporabljena za spremembo
načina datoteke. Četrti argument je logična rekurzivna opcija::

    // set the mode of the video to 0600
    $fs->chmod('video.ogg', 0600);
    // change the mod of the src directory recursively
    $fs->chmod('src', 0700, 0000, true);

.. note::

    Lahko podate polje ali katerikoli :phpclass:`Traversable` objekt kot prvi
    argument.

Remove
~~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::remove` je uporabljena za enostavno odstranitev
datotek, simbolnih povezav, direktorijev::

    $fs->remove(array('symlink', '/path/to/directory', 'activity.log'));

.. note::

    Lahko podate polje ali katerikoli :phpclass:`Traversable` objekt kot prvi
    argument.

Rename
~~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::rename` je uporabljen za preimenovanje
datotek in direktorijev::

    // rename a file
    $fs->rename('/tmp/processed_video.ogg', '/path/to/store/video_647.ogg');
    // rename a directory
    $fs->rename('/tmp/files', '/path/to/store/files');

symlink
~~~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::symlink` ustvari
simbolno povezavo iz cilja na destinacijo. Če datotečni sistem ne
podpira simbolnih povezav, je na voljo tretji argument::

    // create a symbolic link
    $fs->symlink('/path/to/source', '/path/to/destination');
    // duplicate the source directory if the filesystem
    // does not support symbolic links
    $fs->symlink('/path/to/source', '/path/to/destination', true);

makePathRelative
~~~~~~~~~~~~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::makePathRelative` vrne
relativno pot direktorija glede na drugega::

    // returns '../'
    $fs->makePathRelative(
        '/var/lib/symfony/src/Symfony/',
        '/var/lib/symfony/src/Symfony/Component'
    );
    // returns 'videos'
    $fs->makePathRelative('/tmp/videos', '/tmp')

mirror
~~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::mirror` prezrcali
direktorij::

    $fs->mirror('/path/to/source', '/path/to/target');

isAbsolutePath
~~~~~~~~~~~~~~

:method:`Symfony\\Component\\Filesystem\\Filesystem::isAbsolutePath` vrne
``true``, če je dana pot absolutna, drugače ``false``::

    // return true
    $fs->isAbsolutePath('/tmp');
    // return true
    $fs->isAbsolutePath('c:\\Windows');
    // return false
    $fs->isAbsolutePath('tmp');
    // return false
    $fs->isAbsolutePath('../dir');

dumpFile
~~~~~~~~

.. versionadded:: 2.3
    ``dumpFile`` je bil predstavljen v Symfony 2.3.

:method:`Symfony\\Component\\Filesystem\\Filesystem::dumpFile` vam omogoča
odložitev vsebine v datoteko. To naredi na atomičen način: najprej zapiše
začasno datoteko in jo nato premakne v novo lokacijo datoteke, ko konča.
To pomeni, da bo uporabnik vedno videl ali celotno staro datoteko ali
celotno novo datoteko (vendar nikoli delno zapisane datoteke)::

    $fs->dumpFile('file.txt', 'Hello World');

Datoteka ``file.txt`` sedaj vsebuje ``Hello World``.

Željeni datotečni način se lahko poda kot tretji argument.

Upravljanje z napakami
----------------------

Kadarkoli gre kaj narobe, je vržena izjema, ki implementira
:class:`Symfony\\Component\\Filesystem\\Exception\\ExceptionInterface` ali
:class:`Symfony\\Component\\Filesystem\\Exception\\IOExceptionInterface`.

.. note::

    :class:`Symfony\\Component\\Filesystem\\Exception\\IOException` je
    vržena, če ustvarjanje direktorija ne uspe.

.. _`Packagist`: https://packagist.org/packages/symfony/filesystem
