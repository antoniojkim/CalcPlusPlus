Mathematical Functions
======================

Mathematical Constants
^^^^^^^^^^^^^^^^^^^^^^

The mathematical constants that are available are

+------------+---------------------------------------+
| ``e``      |  The base of exponentials, :math:`e`  |
+------------+---------------------------------------+
| ``pi``     |  The constant pi, :math:`\pi`         |
+------------+---------------------------------------+
| ``gamma``  |  Euler's Constant, :math:`\gamma`     |
+------------+---------------------------------------+


Elementary Functions
^^^^^^^^^^^^^^^^^^^^

.. function:: neg(x)

    The negation of :math:`x`, i.e., :math:`-x`

    .. code::

        >>> -sin(3)
        = -0.1411200080598672


.. function:: frexp(x)

    Splits the number :math:`x` into its normalized fraction :math:`f` and exponent :math:`e`, such that :math:`x = f \times 2^{e}` and :math:`0.5 \le f < 1`

    .. code::

        >>> frexp(10)
        = (5/8, 4) = (0.625, 4)


.. function:: ldexp(x, e)

    Computes the number :math:`x \times 2^{e}`

    .. code::

        >>> ldexp(0.625, 4)
        = 10


.. function:: hex(x)

    Converts the number :math:`x` into its hex form

    .. code::

        >>> hex(253)
        = 0xfd


.. function:: bin(x)

    Converts the number :math:`x` into its two's complement binary form

    .. code::

        >>> bin(253)
        = 0b11111101


.. function:: abs(x)

    Returns the magnitude of the number :math:`x`, i.e., :math:`|x|`

    .. code::

        >>> abs(-4)
        = 4


.. function:: sqr(x)

    Returns the square of the number :math:`x`, i.e., :math:`x^2`

    .. code::

        >>> sqr(-4)
        = 16


.. function:: sqrt(x)

    Returns the square root of the number :math:`x`, i.e., :math:`\sqrt{x}`

    .. code::

        >>> sqrt(16)
        = 4


.. function:: cb(x)

    Returns the cube of the number :math:`x`, i.e., :math:`x^3`

    .. code::

        >>> cb(-4)
        = -64


.. function:: cbrt(x)

    Returns the cube root of the number :math:`x`, i.e., :math:`\sqrt[3]{x}`

    .. code::

        >>> cbrt(-64)
        = -4


.. function:: rad(x)

    Returns the radians form of the number :math:`x`. Note: Assumes number is in degrees.

    .. code::

        >>> rad(180)
        = 3.141592653589793


.. function:: deg(x)

    Returns the degrees form of the number :math:`x`. Note: Assumes number is in radians.

    .. code::

        >>> deg(pi)
        = 180


.. function:: hypot(a...)

    Computes euclidean distance for the variable number of arguments passed in. For two and three numbers, it computes it in a way that avoids overflow.

    .. code::

        >>> hypot(3, 4)
        = 5
        >>> hypot(3, 4, 5)
        = 7.071067811865476
        >>> hypot(3, 4, 5, 6, 7, 8, 9)
        = 16.73320053068151


.. function:: fcmp(x, y, tol=1e-8)

    Determines whether :math:`x` and :math:`y` are approximately equal with relative tolerance :math:`tol`. If they are approximately equal, the function returns 0. Otherwise, if :math:`x < y`, the function returns :math:`-1`, or if :math:`x > y`, the function returns :math:`+1`.

    .. code::

        >>> fcmp(sin(3 + pi/2), cos(3))
        = 0
        >>> fcmp(1, 1.0001)
        = -1
        >>> fcmp(1, 1.0001, tol=0.1)
        = 0
        >>> fcmp(1.0001, 1)
        = 1
        >>> fcmp(1.0001, 1, tol=0.1)
        = 0


.. function:: gcd(a...)

    Determines greatest common denominator among all passed in numbers.

    .. code::

        >>> gcd(20, 100)
        = 20
        >>> gcd(2, 20, 100)
        = 2


.. function:: lcm(a...)

    Determines least common multiple among all passed in numbers.

    .. code::

        >>> lcm(20, 100)
        = 100
        >>> lcm(3, 7, 13)
        = 273
