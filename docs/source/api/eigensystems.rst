EigenSystems
============

``Eig(m)``: Computes the eigenvalues and eigenvectors for the matrix :math:`m`. Returns two variables :math:`\Lambda` (the eigenvalues) and :math:`X` (the eigenvectors). Aliases: ``eig``, ``eigen``

.. code::

    >>> Eig({{3, 0}, {0, 4}}
    = (Λ = {{3}, {4}}, X = {{1, 0}, {0, 1}})
    >>> eig({{3, 0, 1}, {1, 0, 4}, {0, 0, 1}}
    = (Λ = {{0}, {3}, {1}}, X = {{0, -0.9486832980505138, -0.1360827634879543}, {1, -0.3162277660168379, 0.9525793444156803}, {0, 0, 0.2721655269759086}})
