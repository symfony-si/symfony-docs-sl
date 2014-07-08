Generiranje novega tipa razreda obrazca na osnovi entitete Doctrine
===================================================================

Uporaba
-------

``generate:doctrine:form`` generira osnovni tip razreda obrazca z uporabo
preslikav meta podatkov danega razreda entitete:

.. code-block:: bash

    php app/console generate:doctrine:form AcmeBlogBundle:Post

Zahtevani argumenti
-------------------

* ``entity``: Ime entitete dano kot notacija bližnjice, ki vsebuje
  ime paketa v katerem je locirana entiteta in ime entitete. Na
  primer: ``AcmeBlogBundle:Post``:

    .. code-block:: bash

        php app/console generate:doctrine:form AcmeBlogBundle:Post
