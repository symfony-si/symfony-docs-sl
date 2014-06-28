.. index::
   single: Forms; Fields; url

url tip polja
=============

Polje ``url`` je tekstovno polje, ki predstavlja poslano vrednost z dodanim
protokolom (npr. ``http://``), če poslana vrednost še ne vsebuje
protokola.

+----------------+-------------------------------------------------------------------+
| Izpisan kot    | ``input url`` polje                                               |
+----------------+-------------------------------------------------------------------+
| Opcije         | - `default_protocol`_                                             |
+----------------+-------------------------------------------------------------------+
| Podedovane     | - `max_length`_ (opuščena od 2.5.)                                |
| opcije         | - `empty_data`_                                                   |
|                | - `required`_                                                     |
|                | - `label`_                                                        |
|                | - `label_attribute`_                                              |
|                | - `data`_                                                         |
|                | - `trim`_                                                         |
|                | - `read_only`_                                                    |
|                | - `disabled`_                                                     |
|                | - `error_bubbling`_                                               |
|                | - `error_mapping`_                                                |
|                | - `mapped`_                                                       |
+----------------+-------------------------------------------------------------------+
| Starševski tip | :doc:`text </reference/forms/types/text>`                         |
+----------------+-------------------------------------------------------------------+
| Razred         | :class:`Symfony\\Component\\Form\\Extension\\Core\\Type\\UrlType` |
+----------------+-------------------------------------------------------------------+

Opcije polja
------------

default_protocol
~~~~~~~~~~~~~~~~

**tip**: ``string`` **privzeto**: ``http``

Če se poslana vrednost ne začne z nekim protokolom (npr. ``http://``,
``ftp://`` itd.), bo ta protokol pripet nizu, ko se pošlje
podatke obrazcu.

Podedovane opcije
-----------------

Te opcije dedujejo iz tipa :doc:`form </reference/forms/types/form>`:

.. include:: /reference/forms/types/options/max_length.rst.inc

.. include:: /reference/forms/types/options/empty_data.rst.inc

.. include:: /reference/forms/types/options/required.rst.inc

.. include:: /reference/forms/types/options/label.rst.inc

.. include:: /reference/forms/types/options/label_attr.rst.inc

.. include:: /reference/forms/types/options/data.rst.inc

.. include:: /reference/forms/types/options/trim.rst.inc

.. include:: /reference/forms/types/options/read_only.rst.inc

.. include:: /reference/forms/types/options/disabled.rst.inc

.. include:: /reference/forms/types/options/error_bubbling.rst.inc

.. include:: /reference/forms/types/options/error_mapping.rst.inc

.. include:: /reference/forms/types/options/mapped.rst.inc
