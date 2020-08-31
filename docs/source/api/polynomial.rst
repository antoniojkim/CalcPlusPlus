Polynomials
===========

Roots of Polynomials
^^^^^^^^^^^^^^^^^^^^

``quad(a, b, c)``: Computes the real roots of the quadratic equation

.. math::

    ax^2 + bx + c

.. code::

    >>> quad(1, -7, 12)
    = (x1 = 3, x2 = 4)
    >>> quad(1, 7, 11)
    = ()

``quadc(a, b, c)``: Computes the complex roots of the quadratic equation

.. math::

    az^2 + bz + c

.. code::

    >>> quadc(1, -7, 12)
    = (z1 = 3, z2 = 4)
    >>> quadc(1, 7, 11)
    = (z1 = -4.618033988749895, z2 = -2.381966011250105)

``cubic(a, b, c, d)``: Computes the real roots of the cubic equation

.. math::

    ax^3 + bx^2 + cx + d

.. code::

    >>> cubic(1, 4, 7, 11)
    = (x1 = -2.894558248242799)
    >>> cubic(1, -3, -7, 12)
    = (x1 = -2.302775637731995, x2 = 1.302775637731995, x3 = 4)

``cubicc(a, b, c)``: Computes the complex roots of the cubic equation

.. math::

    az^3 + bz^2 + cz + d

.. code::

    >>> cubicc(1, 4, 7, 11)
    = (z1 = -2.894558248242799, z2 = -0.5527208758786003-1.869420790744347i, z3 = -0.5527208758786003+1.869420790744347i)
    >>> cubic(1, -3, -7, 12)
    = (z1 = -2.302775637731995, z2 = 1.302775637731995, z3 = 4)
