.. index::
    single: Console Helpers; Progress Helper

Pomočnik napredka
=================

.. versionadded:: 2.2
    Pomočnik ``progress`` je bil dodan v Symfony 2.2.

.. versionadded:: 2.3
    Metoda ``setCurrent`` je bila dodana v Symfony 2.3.

.. versionadded:: 2.4
    Metoda ``clear`` je bila dodana v Symfony 2.4.

Ko izvajate daljše-pogonske ukaze, je lahko v pomoč prikaz informacije
napredka, ki se posodablja kakor se izvaja vaš ukaz:

.. image:: /images/components/console/progress.png

Za prikaz podrobnosti napredka, uporabite :class:`Symfony\\Component\\Console\\Helper\\ProgressHelper`,
podajte mu celotno število enot in napredujte napredek kot se vaš ukaz izvaja::

    $progress = $this->getHelperSet()->get('progress');

    $progress->start($output, 50);
    $i = 0;
    while ($i++ < 50) {
        // ... do some work

        // advance the progress bar 1 unit
        $progress->advance();
    }

    $progress->finish();

.. tip::

    Lahko tudi nastavite trenutni napredek s klicom
    :method:`Symfony\\Component\\Console\\Helper\\ProgressHelper::setCurrent`
    metode.

Če želite izpisati nekaj, ko se vrstica napredka poganja,
kličite najprej :method:`Symfony\\Component\\Console\\Helper\\ProgressHelper::clear`.
Ko opravite, kličite
:method:`Symfony\\Component\\Console\\Helper\\ProgressHelper::display`
za ponovni prikaz vrstice napredka.

Izgled izpisa napredka se lahko tudi prilagodi s številnimi različnimi nivoji
besedičenja. Vsak od teh prikaže različne možne elemente - kot
je procentualno dokončanje, premikajoča se vrstica napredka, ali trenutne/skupne
informacije (npr. 10/50)::

    $progress->setFormat(ProgressHelper::FORMAT_QUIET);
    $progress->setFormat(ProgressHelper::FORMAT_NORMAL);
    $progress->setFormat(ProgressHelper::FORMAT_VERBOSE);
    $progress->setFormat(ProgressHelper::FORMAT_QUIET_NOMAX);
    // the default value
    $progress->setFormat(ProgressHelper::FORMAT_NORMAL_NOMAX);
    $progress->setFormat(ProgressHelper::FORMAT_VERBOSE_NOMAX);

Lahko tudi kontrolirate različne znake in uporabljeno širino za
vrstico napredka::

    // the finished part of the bar
    $progress->setBarCharacter('<comment>=</comment>');
    // the unfinished part of the bar
    $progress->setEmptyBarCharacter(' ');
    $progress->setProgressCharacter('|');
    $progress->setBarWidth(50);

Da vidite ostale opcije, ki so na voljo, preverite API dokumentacijo za
:class:`Symfony\\Component\\Console\\Helper\\ProgressHelper`.

.. caution::

    Zaradi razlogov uspešnosti, bodite previdni, če nastavite skupno število korakov
    na veliko številko. Na primer, če ponavljate preko velikega števila elementov,
    premislite nastaviti vračilno frekvenco na višje število s klicom
    :method:`Symfony\\Component\\Console\\Helper\\ProgressHelper::setRedrawFrequency`,
    da se posodobi samo na nekaterih iteracijah::

        $progress->start($output, 50000);

        // update every 100 iterations
        $progress->setRedrawFrequency(100);

        $i = 0;
        while ($i++ < 50000) {
            // ... do some work

            $progress->advance();
        }
