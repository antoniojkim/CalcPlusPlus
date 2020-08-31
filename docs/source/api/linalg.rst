Linear Algebra
==============

``det(m)``: Computes the determinant of the matrix :math:`m`

.. code::

    >>> det({{1, 2, 4}, {4, 0, 6}, {7, 8, 9}})
    = 92


``lndet(m)``: Computes the logarithm of the absolute value of the determinant of the matrix :math:`m`. That is, :math:`\ln|\det(m)|`

.. code::

    >>> lndet({{1, 2, 4}, {4, 0, 6}, {7, 8, 9}})
    = 4.52178857704904


``LU(m)``: Computes the :math:`LU` decomposition of the matrix :math:`m`.

.. code::

    >>> lndet({{1, 2, 4}, {4, 0, 6}, {7, 8, 9}})
    =  (LU = {{7, 8, 9}, {4/7, -32/7, 6/7}, {1/7, -3/16, 23/8}}, P = {2, 1, 0}, sign = -1)


``LUsolve(A, b)``: Solves the square system :math:`Ax = b`. Aliases: ``solve``

.. code::

    >>> LUsolve({{1, 2, 4}, {4, 0, 6}, {7, 8, 9}}, {1, 2, 3})
    = {{4/23}, {-1/46}, {5/23}}

    >>> solve({{1, 6, 4}, {4, 0, 6}, {7, 8, 2}}, {4, 2, 3})
    = {{-11/71}, {57/142}, {31/71}}


``Cholesky(m)``: Factorize the symmetric, positive-definite square matrix :math:`m` into the Cholesky decomposition :math:`m = L L^T`

.. code::

    >>> Cholesky{{9, 3, 0}, {3, 5, 2}, {0, 2, 17}}
    = {{3, 3, 0}, {1, 2, 2}, {0, 1, 4}
    >>> chol{{9, 3, 0}, {3, 5, 2}, {0, 2, 17}}
    = {{3, 3, 0}, {1, 2, 2}, {0, 1, 4}


``SVD(m)``: Factorizes the :math:`M \times N` matrix :math:`m` into the singular value decomposition :math:`m = U S V^T` for  :math:`M \ge N`.

.. code::

    >>> SVD{{4, 0}, {0, -1}}
    = (U = {{1, 0}, {0, 1}}, S = {{4}, {1}}, V = {{1, 0}, {0, -1}})
    >>> SVD{{3, 0}, {0, 2}}
    = (U = {{1, 0}, {0, 1}}, S = {{3}, {2}}, V = {{1, 0}, {0, 1}})


``QR(m)``: Computes the :math:`QR` decomposition of the matrix :math:`m`.

.. code::

    >>> QR({{12, -51, 4}, {6, 167, -68}, {-4, 24, -41}})
    = (Q = {{-6/7, 69/175, 58/175}, {-3/7, -158/175, -6/175}, {2/7, -6/35, 33/35}}, R = {{-14, -21, 14}, {0, -175, 70}, {0, 0, -35}})
