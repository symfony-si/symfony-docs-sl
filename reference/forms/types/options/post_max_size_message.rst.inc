post_max_size_message
~~~~~~~~~~~~~~~~~~~~~

**tip**: ``string`` **default**: ``The uploaded file was too large. Please try to upload a smaller file.``

To je sporočilo napake preverjanja, ki je uporabljeno, če poslani podatki obrazca POST
presežejo direktivo ``post_max_size`` v ``php_ini``. Prostornik ``{{ max }}``
je lahko uporabljen za prikaz dovoljene velikosti.

.. note::

    Preverjanje ``post_max_size`` se zgodi samo na vrhnjem obrazcu.
