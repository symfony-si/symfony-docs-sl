.. index::
   single: Process
   single: Components; Process

Komponenta Process
==================

    Komponenta Process izvršuje ukaze v pod-procesih.

Namestitev
----------

Komponento lahko namestite na 2 različna načina:

* :doc:`Namestite jo preko Composer-ja </components/using_components>` (``symfony/process`` na `Packagist`_);
* Uporabite uradni Git repozitorij (https://github.com/symfony/Process).

Uporaba
-------

Razred :class:`Symfony\\Component\\Process\\Process` vam omogoča, da izvršite
ukaz v pod-procesu::

    use Symfony\Component\Process\Process;

    $process = new Process('ls -lsa');
    $process->run();

    // executes after the command finishes
    if (!$process->isSuccessful()) {
        throw new \RuntimeException($process->getErrorOutput());
    }

    print $process->getOutput();

Komponenta poskrbi za majhne razlike med različnimi platformami,
ko se izvršuje ukaz.

Metoda ``getOutput()`` vedno vrne celotno vsebino standardnega
izpisa ukaza in ``getErrorOutput()`` vsebino izpisa napake.
Alternativno metodi :method:`Symfony\\Component\\Process\\Process::getIncrementalOutput`
in :method:`Symfony\\Component\\Process\\Process::getIncrementalErrorOutput`
vrneta nov izpis od zadnjega klica.

.. versionadded:: 2.4
    Metodi ``clearOutput()`` in ``clearErrorOutput()`` sta bili predstavljeni v Symfony 2.4.

Metoda :method:`Symfony\\Component\\Process\\Process::clearOutput` počisti
vsebine izpisa in
:method:`Symfony\\Component\\Process\\Process::clearErrorOutput` počisti
vsebine izpisa napak.

Pridobiti realno-časovni izpis procesa
--------------------------------------

Ko izvršujete dolgo trajajoči ukaz (kot je rsync datotek na oddaljenem
strežniku) lahko date povratne informacije končnemu uporabniku v realnem času s podajanjem
anonimne funkcije k
metodi :method:`Symfony\\Component\\Process\\Process::run`::

    use Symfony\Component\Process\Process;

    $process = new Process('ls -lsa');
    $process->run(function ($type, $buffer) {
        if (Process::ERR === $type) {
            echo 'ERR > '.$buffer;
        } else {
            echo 'OUT > '.$buffer;
        }
    });

Poganjanje procesov ashinhrono
------------------------------

Lahko tudi začnete pod-proces in ga nato pustite teči asinhrono, pridobite
izpis in status v vašem glavnem procesu kadarkoli ga potrebujete. Uporabite
metodo :method:`Symfony\\Component\\Process\\Process::start`, da začnete asinhroni
proces, metodo :method:`Symfony\\Component\\Process\\Process::isRunning`,
da preverite, če je proces končan in
metodo :method:`Symfony\\Component\\Process\\Process::getOutput`, da dobite izpis::

    $process = new Process('ls -lsa');
    $process->start();

    while ($process->isRunning()) {
        // waiting for process to finish
    }

    echo $process->getOutput();

Lahko tudi počakate, da se proces konča, če ste ga začeli asinhrono in
ste končali opravljati druge stvari::

    $process = new Process('ls -lsa');
    $process->start();

    // ... do other things

    $process->wait(function ($type, $buffer) {
        if (Process::ERR === $type) {
            echo 'ERR > '.$buffer;
        } else {
            echo 'OUT > '.$buffer;
        }
    });

.. note::

    Metoda :method:`Symfony\\Component\\Process\\Process::wait` blokira,
    kar pomeni, da bo vaša koda čakala na tej vrstici dokler ni zunanji
    proces končan.

Ustavitev procesa
-----------------

.. versionadded:: 2.3
    Parameter ``signal`` metode ``stop`` je bil predstavljen v Symfony 2.3.

Katerikoli asinhroni proces se lahko ustavi kadarkoli z
metodo :method:`Symfony\\Component\\Process\\Process::stop`. Ta metoda vzame
dva argumenta: timeout in signal. Ko je enkrat dosežen timeout, je signal
posla procesu, ki se poganja. Privzeti signal poslan procesu je ``SIGKILL``.
Prosimo, preberite :ref:`signal documentation below<reference-process-signal>`,
da izveste več o upravljanju signalov v komponenti Process::

    $process = new Process('ls -lsa');
    $process->start();

    // ... do other things

    $process->stop(3, SIGINT);

Izvrševanje PHP kode v izolaciji
--------------------------------

Če želite izvršiti nekatero PHP kodo v izolaciji, uporabite zato
``PhpProcess``::

    use Symfony\Component\Process\PhpProcess;

    $process = new PhpProcess(<<<EOF
        <?php echo 'Hello World'; ?>
    EOF
    );
    $process->run();

Da naredite, da vaša koda deluje bolje na vseh platformah, morda zato želite uporabiti
razred :class:`Symfony\\Component\\Process\\ProcessBuilder`::

    use Symfony\Component\Process\ProcessBuilder;

    $builder = new ProcessBuilder(array('ls', '-lsa'));
    $builder->getProcess()->run();

.. versionadded:: 2.3
    Metoda :method:`ProcessBuilder::setPrefix<Symfony\\Component\\Process\\ProcessBuilder::setPrefix>`
    je bila predstavljena v Symfony 2.3.

V primeru, da gradite binarni gonilnik, lahko uporabite
metodo :method:`Symfony\\Component\\Process\\Process::setPrefix`, da dodate predpono vsem
generiranim ukazem procesa.

Sledeči primer bo generiral dva procesna ukaza za tar binarni
adapter::

    use Symfony\Component\Process\ProcessBuilder;

    $builder = new ProcessBuilder();
    $builder->setPrefix('/usr/bin/tar');

    // '/usr/bin/tar' '--list' '--file=archive.tar.gz'
    echo $builder
        ->setArguments(array('--list', '--file=archive.tar.gz'))
        ->getProcess()
        ->getCommandLine();

    // '/usr/bin/tar' '-xzf' 'archive.tar.gz'
    echo $builder
        ->setArguments(array('-xzf', 'archive.tar.gz'))
        ->getProcess()
        ->getCommandLine();

Timeout procesa
---------------

Omejite lahko količino časa, ki ga proces vzame za dokončanje z nastavitvijo
timeout-a (v sekundah)::

    use Symfony\Component\Process\Process;

    $process = new Process('ls -lsa');
    $process->setTimeout(3600);
    $process->run();

Če je timeout dosežen, je vržena
:class:`Symfony\\Process\\Exception\\RuntimeException`.

Za dolgo trajajoče ukaze, je vaša dolžnost narediti redno preverjanje
timeout-a::

    $process->setTimeout(3600);
    $process->start();

    while ($condition) {
        // ...

        // check if the timeout is reached
        $process->checkTimeout();

        usleep(200000);
    }

.. _reference-process-signal:

Timeout mirovanja procesa
-------------------------

.. versionadded:: 2.4
   Metoda :method:`Symfony\\Component\\Process\\Process::setIdleTimeout`
   je bila predstavljena v Symfony 2.4.

Z razliko od timeout-a v prejšnjem poglavju, timeout mirovanja
smatra samo čas od zadnjega izpisa, ki je bil produciran s strani procesa::

   use Symfony\Component\Process\Process;

   $process = new Process('something-with-variable-runtime');
   $process->setTimeout(3600);
   $process->setIdleTimeout(60);
   $process->run();

V primeru zgoraj, proces je mišljen kot pretečen, ko ali celotni čas pogona
preseže 3600 sekund, ali proces ne producira nobenega izpisa za 60 sekund.

Signali procesa
---------------

.. versionadded:: 2.3
    Metoda ``signal`` je bila predstavljena v Symfony 2.3.

Ko poganjate program asinhrono, mu lahko pošljete posix signale z
metodo :method:`Symfony\\Component\\Process\\Process::signal`::

    use Symfony\Component\Process\Process;

    $process = new Process('find / -name "rabbit"');
    $process->start();

    // will send a SIGKILL to the process
    $process->signal(SIGKILL);

.. caution::

    Zaradi nekaterih omejitev v PHP, če uporabljate signale s komponento Process,
    boste morda morali dodati predpono `exec`_ vašim ukazom. Prosimo, preberite
    `Symfony Issue#5759`_ in `PHP Bug#39992`_, da boste razumeli, zakaj se to dogaja.

    Signali POSIX niso na voljo na platformah Windows, prosimo sklicujte se na
    `dokumentacijo PHP`_ za signale, ki so na voljo.

Pid procesa
-----------

.. versionadded:: 2.3
    Metoda ``getPid`` je bila predstavljena v Symfony 2.3.

Lahko dostopate do `pid`_ poganjajočega procesa z
metodo :method:`Symfony\\Component\\Process\\Process::getPid`.

.. code-block:: php

    use Symfony\Component\Process\Process;

    $process = new Process('/usr/bin/php worker.php');
    $process->start();

    $pid = $process->getPid();

.. caution::

    Zaradi nekaterih omejitev v PHP, če želite dobiti pid procesa symfony,
    boste morda morali dodati predpono `exec_` vašim ukazom. Prosimo, preberite
    `Symfony Issue#5759`_, da razumete, zakaj se to dogaja.

Onemogočanje izpisa
-------------------

.. versionadded:: 2.5
    Metodi :method:`Symfony\\Component\\Process\\Process::disableOutput` in
    :method:`Symfony\\Component\\Process\\Process::enableOutput` sta bili
    predstavljeni v Symfony 2.5.

Ker sta standardni izpis in izpis napak vedno ujeta iz podležečega procesa,
je morda priročno onemogočiti izpis v nekaterih primerih, da varčujete spomin.
Uporabite :method:`Symfony\\Component\\Process\\Process::disableOutput` in
:method:`Symfony\\Component\\Process\\Process::enableOutput`, da omogočite to lastnost::

    use Symfony\Component\Process\Process;

    $process = new Process('/usr/bin/php worker.php');
    $process->disableOutput();
    $process->run();

.. caution::

    Ne morete omogočiti ali onemogočiti izpisa, ko se proces poganja.

    Če onemogočite izpis, ne morete dostopati do ``getOutput``,
    ``getIncrementalOutput``, ``getErrorOutput`` ali ``getIncrementalErrorOutput``.
    Še več, lahko bi podali povratni klic metodam ``start``, ``run`` ali ``mustRun``
    ali uporabili ``setIdleTimeout``.

.. _`Symfony Issue#5759`: https://github.com/symfony/symfony/issues/5759
.. _`PHP Bug#39992`: https://bugs.php.net/bug.php?id=39992
.. _`exec`: http://en.wikipedia.org/wiki/Exec_(operating_system)
.. _`pid`: http://en.wikipedia.org/wiki/Process_identifier
.. _`dokumentacijo PHP`: http://php.net/manual/en/pcntl.constants.php
.. _Packagist: https://packagist.org/packages/symfony/process
