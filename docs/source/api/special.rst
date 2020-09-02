Special Functions
=================

Gamma Functions
^^^^^^^^^^^^^^^

.. function:: gamma(x)

    Computes the Gamma function :math:`\Gamma(x)`, subject to :math:`x` not being a negative integer or zero. That is, it is computing

    .. math::

        \Gamma(x) = \int_0^{\infty}{ t^{x-1} e^{-t} dt}

    The value is computed using the real Lanczos method. The maximum value of :math:`x` such that :math:`\Gamma(x)` is not considered an overflow is 171.

    .. code::

        >>> gamma(5)
        = 24
        >>> gamma(5.5)
        = 52.34277778455351


.. function:: lngamma(x)

    Compute the logarithm of the Gamma function, :math:`\log(\Gamma(x))`, subject to :math:`x` not being a negative integer or zero. For :math:`x < 0` the real part of :math:`\log(\Gamma(x))` is returned, which is equivalent to :math:`\log(|\Gamma(x)|)`. The function is computed using the real Lanczos method.

    .. code::

        >>> lngamma(5)
        = 3.178053830347945
        >>> gamma(5.5)
        = 3.957813967618717


.. function:: gammastar(x)

    Compute the regulated Gamma function :math:`\Gamma^*(x)` for :math:`x > 0`. The regulated gamma function is given by,

    .. math::

        \Gamma^*(x) = \frac{\Gamma(x)}{\sqrt{2\pi}x^{x-1/2} e^{-x}}

    .. code::

        >>> gammastar(5)
        = 1.016783985827808
        >>> gammastar(5.5)
        = 1.015250086943625


.. function:: gammainv(x)

    Compute the reciprocal of the Gamma function :math:`1/\Gamma(x)` using the real Lanczos method.

    .. code::

        >>> gammainv(5)
        = 1/24
        >>> gammainv(5.5)
        = 0.01910483245876


.. function:: fact(x)

    Computes the factorial :math:`x!`. The factorial is related to the Gamma function by :math:`x! = \Gamma(x+1)`. The maximum value of :math:`x` such that :math:`x!` is not considered an overflow is :math:`170`.

    .. code::

        >>> fact(5)
        = 120
        >>> 5!
        = 120
        >>> fact(5.5)
        = 287.8852778150443
        >>> 5.5!
        = 287.8852778150443


.. function:: dfact(x)

    Computes the double factorial :math:`x!! = x(x-2)(x-4)\dots`. The maximum value of :math:`x` such that :math:`x!!` is not considered an overflow is :math:`297`.

    .. code::

        >>> dfact(10)
        = 3840
        >>> 10!!
        = 3840


.. function:: lnfact(x)

    Computes the logarithm of the factorial of :math:`x`, :math:`\log(x!)`. This algorithm is faster than computing :math:`\log(x!)` explicitly.

    .. code::

        >>> lnfact(5)
        = 4.787491742782046


.. function:: lndfact(x)

    Computes the logarithm of the double factorial of :math:`x`, :math:`\log(x!!)`. This algorithm is faster than computing :math:`\log(x!!)` explicitly.

    .. code::

        >>> lndfact(10)
        = 8.253227645581772


.. function:: choose(n, r)

    Computes the combinatorial factor :math:`{n \choose r} = \frac{n!}{r!(n-r)!}`. Aliases: ``comb``

    .. code::

        >>> choose(10, 3)
        = 120
        >>> comb(10, 3)
        = 120


.. function:: permute(n, r)

    Computes the permutation factor :math:`n^{(r)} = \frac{n!}{(n-r)!}`. Aliases: ``perm``

    .. code::

        >>> permute(10, 3)
        = 720
        >>> perm(10, 3)
        = 720


.. function:: lnpermute(n, r)

    Computes the logarithm of the permutation factor :math:`\ln(n^{(r)}) = \ln(n!) - \ln((n-r)!)`. Aliases: ``lmperm``

    .. code::

        >>> lnpermute(10, 3)
        = 6.579251212010101
        >>> lnperm(10, 3)
        = 6.579251212010101


.. function:: taylorcoeff(n, x)

    Computes the Taylor coefficient :math:`\frac{x^n}{n!}` for :math:`x \ge 0, n \ge 0`

    .. code::

        >>> taylorcoeff(3, 4)
        = 32/3


Pochhammer Symbol
^^^^^^^^^^^^^^^^^

.. function:: poch(a, x)

    Compute the Pochhammer symbol :math:`(a)_x = \frac{\Gamma(a + x)}{\Gamma(a)}`. The Pochhammer symbol is also known as the Apell symbol and sometimes written as :math:`(a,x)`. When :math:`a` and :math:`a + x` are negative integers or zero, the limiting value of the ratio is returned.

    .. code::

        >>> poch(3, 4)
        = 360


.. function:: lnpoch(a, x)

    Computes the logarithm of the Pochhammer symbol, :math:`\log((a)_x) = \log(\frac{\Gamma(a + x)}{\Gamma(a)})`.

    .. code::

        >>> lnpoch(3, 4)
        = 5.886104031450156


.. function:: pochrel(a, x)

    Computes the relative Pochhammer symbol :math:`\frac{(a)_x - 1}{x}` where :math:`(a)_x = \frac{\Gamma(a + x)}{\Gamma(a)}`.

    .. code::

        >>> pochrel(3, 4)
        = 359/4


Incomplete Gamma Functions
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. function:: gamma_inc(a, x)

    These functions compute the unnormalized incomplete Gamma Function

    .. math::

        \Gamma(a,x) = \int_x^\infty t^{(a-1)} \exp(-t) dt

    for a real and :math:`x \ge 0`. Aliases: ``gammainc``

    .. code::

        >>> gamma_inc(3, 4)
        = 0.4762066111070874
        >>> gammainc(3, 4)
        = 0.4762066111070874


.. function:: gamma_inc_Q(a, x)

    These functions compute the normalized  incomplete Gamma Function

    .. math::

        Q(a,x) = \frac{1}{\Gamma(a)} \int_x^\infty t^{(a-1)} \exp(-t) dt

    for a real and :math:`a > 0, x \ge 0`. Aliases: ``gammaincq``

    .. code::

        >>> gamma_inc_Q(3, 4)
        = 0.2381033055535437
        >>> gammaincq(3, 4)
        = 0.2381033055535437


.. function:: gamma_inc_P(a, x)

    These functions compute the complementary normalized incomplete Gamma Function

    .. math::

        P(a, x) = 1 - Q(a,x) = 1 - \frac{1}{\Gamma(a)} \int_x^\infty t^{(a-1)} \exp(-t) dt

    for a real and :math:`a > 0, x \ge 0`. Aliases: ``gammaincp``

    .. code::

        >>> gamma_inc_P(3, 4)
        = 0.7618966944464536
        >>> gammaincp(3, 4)
        = 0.7618966944464536


Beta Functions
^^^^^^^^^^^^^^

.. function:: Beta(a, b)

    Computes the Beta Function, :math:`B(a,b) = \frac{\Gamma(a)\Gamma(b)}{\Gamma(a+b)}` subject to :math:`a` and :math:`b` not being negative integers.

    .. code::

        >>> Beta(3, 4)
        = 1/60


.. function:: lnBeta(a, b)

    Computes the logarithm of the Beta Function, :math:`\ln(B(a,b)) = \ln(\Gamma(a)) + \ln(\Gamma(b)) - \ln(\Gamma(a+b))` subject to :math:`a` and :math:`b` not being negative integers.

    .. code::

        >>> lnBeta(10, 15)
        = -16.79168073529216


Incomplete Beta Function
^^^^^^^^^^^^^^^^^^^^^^^^

.. function:: Betainc(a, b, x)

    Computes the normalized incomplete Beta function :math:`I_x(a,b) = \frac{B_x(a,b)}{B(a,b)}` where

    .. math::

        B_x(a,b) = \int_0^x t^{a-1} (1-t)^{b-1} dt

    for :math:`0 \le x \le 1`. For :math:`a > 0, b > 0` the value is computed using a continued fraction expansion. For all other values it is computed using the relation

    .. math::

        I_x(a,b,x) = \frac{1}{a} x^a {}_2F_1(a,1-b,a+1,x)/B(a,b)

    .. code::

        >>> Betainc(1, 2, 0.5)
        = 3/4
