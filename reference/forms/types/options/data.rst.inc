data
~~~~

**tip**: mešano **privzeto**: Privzeto je polju osnovnega objekta (če obstaja)

Ko ustvarite obrazec, vsako polje na začetku prikaže vrednost
pripadajoče lastnosti domene objekta obrazca (če je objekt vezan
na obrazec). Če želite prepisati začetno vrednost za obrazec ali samo
posamezno polje, ga lahko nastavite v opciji data::

    $builder->add('token', 'hidden', array(
        'data' => 'abcdef',
    ));

.. note::

    Privzete vrednosti za polja obrazca so vzete direktno iz
    osnovne podatkovne strukture (npr. entiteta ali polje).
    Opcija ``data`` prepiše to privzeto vrednost.
