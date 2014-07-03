property_path
~~~~~~~~~~~~~

**tip**: ``katerikoli`` **privzeto**: ``ime polja``

Polja privzeto prikazujejo lastnost vrednosti domene objekta obrazca. Ko
je obrazec poslan, je poslana vrednost napisana nazaj v objekt.

Če želite prepisati lastnost, ki jo polje prebere iz in piše v,
lahko nastavite opcijo ``property_path``. Njena privzeta vrednost je ime
polja.

Če želite, da je polje ignorirano pri branju ali pisanju v objekt,
lahko nastavite opcijo ``property_path`` na ``false``, vendar uporaba
``property_path`` za ta razlog je opuščena, morali bi uporabiti
opcijo ``mapped``.
