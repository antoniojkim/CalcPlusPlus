Special Functions
=================

``gamma(x)``: Computes the Gamma function :math:`\Gamma(x)`, subject to :math:`x` not being a negative integer or zero. That is, it is computing

.. math::

    \Gamma(x) = \int_0^{\infty}{ dtt^{x-1} e^{-t}}

The value is computed using the real Lanczos method. The maximum value of :math:`x` such that :math:`\Gamma(x)` is not considered an overflow is 171.

.. code::

    >>> gamma(5)
    = 24
    >>> gamma(5.5)
    = 52.34277778455351


``lngamma(x)``: Compute the logarithm of the Gamma function, :math:`\log(\Gamma(x))`, subject to :math:`x` not being a negative integer or zero. For :math:`x < 0` the real part of :math:`\log(\Gamma(x))` is returned, which is equivalent to :math:`\log(|\Gamma(x)|)`. The function is computed using the real Lanczos method.

.. code::

    >>> lngamma(5)
    = 3.178053830347945
    >>> gamma(5.5)
    = 3.957813967618717


``gammastar(x)``: Compute the regulated Gamma function :math:`\Gamma^*(x)` for :math:`x > 0`. The regulated gamma function is given by,

.. math::

    \Gamma^*(x) = \frac{\Gamma(x)}{\sqrt{2\pi}x^{x-1/2} e^{-x}}

.. code::

    >>> gammastar(5)
    = 1.016783985827808
    >>> gammastar(5.5)
    = 1.015250086943625


``gammainv(x)``: Compute the reciprocal of the Gamma function :math:`1/\Gamma(x)` using the real Lanczos method.

.. code::

    >>> gammainv(5)
    = 1/24
    >>> gammainv(5.5)
    = 0.01910483245876
