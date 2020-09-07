Vectors and Matrices
====================

Matrices are a data structure that is built into the math engine. They can be constructed using the c-style inline array syntax

.. code::

    >>> {{1, 2}, {3, 4}}
    = {{1, 2}, {3, 4}}


Vectors are treated as one-dimensional matrices (single row) within the engine

.. code::

    >>> {1, 2, 3}
    = {1, 2, 3}


Matrix Operations
^^^^^^^^^^^^^^^^^

A matrix can be transposed by taking the power of the matrix by :math`T`

.. code::

    >>> {{1, 2}, {3, 4}}^T
    = {{1, 3}, {2, 4}}

A square matrix can be inverted by taking the power of the matrix by :math:`-1`

.. code::

    >>> {{1, 2}, {3, 4}}^-1
    = {{-2, 1}, {3/2, -1/2}}

A scalar can be added to a matrix element-wise simply using the addition operator

.. code::

    >>> {{1, 2}, {3, 4}} + 2
    = {{3, 4}, {5, 6}}
    >>> 2 + {{1, 2}, {3, 4}}
    = {{3, 4}, {5, 6}}

Two matrices of the same shape can be element-wise added together simply using the addition operator

.. code::

    >>> {{1, 2}, {3, 4}} + {{6, 7}, {8, 9}}
    = {{7, 9}, {11, 13}}

A scalar can be subtracted from a matrix element-wise simply using the subtraction operator

.. code::

    >>> {{1, 2}, {3, 4}} - 2
    = {{-1, 0}, {1, 2}}
    >>> 2 - {{1, 2}, {3, 4}}
    = {{1, 0}, {-1, -2}}

Two matrices of the same shape can be element-wise subtracted together simply using the subtraction operator

.. code::

    >>> {{1, 2}, {3, 4}} - {{6, 7}, {8, 9}}
    = {{-5, -5}, {-5, -5}}

A scalar and multiplied to a matrix element-wise simply using the multiplication operator

.. code::

    >>> {{1, 2}, {3, 4}} * 2
    = {{2, 4}, {6, 8}}
    >>> 2 * {{1, 2}, {3, 4}}
    = {{2, 4}, {6, 8}}

An :math:`m \times n` matrix and an :math:`m \times n` matrix matrix multiplied together simply using the multiplication operator

.. code::

    >>> {{1, 2, 3}, {4, 5, 6}} * {{1, 2}, {3, 4}, {5, 6}}
    = {{22, 28}, {49, 64}}

Two :math:`m \times n` matrices (where :math:`m \ne n`) can be element-wise multiplied together simply using the multiplication operator

.. code::

    >>> {{1, 2, 3}, {4, 5, 6}} * {{7, 8, 9}, {6, 5, 4}}
    = {{7, 16, 27}, {24, 25, 24}}

.. note::

    The matrix multiplication takes precedence for square matrices.

A scalar m a matrix element-wise added together simply using the subtraction operator

.. code::

    >>> {{1, 2}, {3, 4}} - 2
    = {{-1, 0}, {1, 2}}
    >>> 2 - {{1, 2}, {3, 4}}
    = {{1, 0}, {-1, -2}}

Two matrices of the same shape can be element-wise subtracted together simply using the subtraction operator

.. code::

    >>> {{1, 2}, {3, 4}} - {{6, 7}, {8, 9}}
    = {{-5, -5}, {-5, -5}}
