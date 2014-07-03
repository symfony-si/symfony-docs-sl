cascade_validation
~~~~~~~~~~~~~~~~~~

**tip**: Boolean **privzeto**: false

Nastavite to opcijo na ``true``, da vsilite preverjanje na vključenih tipih obrazcev.
Na primer, če imate ``ProductType`` z vključeno ``CategoryType``,
nastavitev ``cascade_validation`` na ``true`` pri ``ProductType`` bo povzročilo,
da bodo podatki iz ``CategoryType`` tudi preverjeni.

Namesto uporabe te opcije, lahko tudi uporabite ``Valid`` omejitev v
vašem modelu, da vsilite preverjanje na otroškem objektu shranjenem na lastnosti.

.. include:: /reference/forms/types/options/_error_bubbling_hint.rst.inc
