Random Number Distributions
===========================

Uniform Distribution
^^^^^^^^^^^^^^^^^^^^^

.. function:: rand()

    Generates a random number between :math:`0` and :math:`1` from the uniform distribution :math:`U(0, 1)`.

    .. code::

        >>> rand()
        = 0.1629098753910512


Gaussian Distribution
^^^^^^^^^^^^^^^^^^^^^

.. function:: randn()

    Generates a random number from the gaussian distribution :math:`\mathcal{N}(0, 1)`.

    The probability distribution for Gaussian random variates is,

    .. math::

        p(x) dx = \frac{1}{\sqrt{2\pi\sigma^2}} \exp\left( -\frac{x^2}{2\sigma^2} \right) dx

    .. code::

        >>> randn()
        = 0.1339186081186759

.. function:: gauss_pdf(x, sigma=1)

    Computes the probability density :math:`p(x)` at :math:`x` for a Gaussian distribution with standard deviation ``sigma``, using the formula given above.

    .. code::

        >>> gauss_pdf(2)
        = 0.05399096651318806
        >>> gauss_pdf(2, 1)
        = 0.05399096651318806


.. function:: gauss_P(x, sigma=1)

    Computes the cumulative density :math:`P(x)` at :math:`x`

    .. math::

        P(x) = \int_{-\infty}^{x} p(t) dt

    where :math:`p(t)` is the gaussian distribution with standard deviation ``sigma``. Aliases: ``norm``

    .. code::

        >>> gauss_P(2)
        = 0.9772498680518208
        >>> norm(2, 1)
        = 0.9772498680518208


.. function:: gauss_Pinv(x, sigma=1)

    Computes the inverse of the cumulative density :math:`P^{-1}(x)` at :math:`x` for the gaussian distribution with standard deviation ``sigma``. Aliases: ``norminv``

    .. code::

        >>> gauss_Pinv(0.9772498680518208)
        = 2
        >>> norminv(2, 1)
        = 2


.. function:: gauss_Q(x, sigma=1)

    Computes the cumulative density :math:`P(x)` at :math:`x`

    .. math::

        Q(x) = \int_{x}^{\infty} p(t) dt

    where :math:`p(t)` is the gaussian distribution with standard deviation ``sigma``. Aliases: ``cnorm``

    .. code::

        >>> gauss_Q(2)
        = 0.02275013194817921
        >>> cnorm(2, 1)
        = 0.02275013194817921


.. function:: gauss_Qinv(x, sigma=1)

    Computes the inverse of the cumulative density :math:`Q^{-1}(x)` at :math:`x` for the gaussian distribution with standard deviation ``sigma``. Aliases: ``cnorminv``

    .. code::

        >>> gauss_Qinv(0.02275013194817921)
        = 2
        >>> cnorminv(2, 1)
        = 2


Exponential Distribution
^^^^^^^^^^^^^^^^^^^^^^^^

.. function:: exponential(mu)

    Generates a random number from the exponential distribution with mean ``mu``.

    The probability distribution for exponential random variates is,

    .. math::

        p(x) dx = \frac{1}{\mu} \exp\left( -\frac{x}{\mu} \right) dx

    for :math:`x \ge 0`

    .. code::

        >>> exponential(1)
        = 8.261578216370394
        >>> exponential(1)
        = 0.177823538531874


.. function:: exponential_pdf(x, mu)

    Computes the probability density :math:`p(x)` at :math:`x` for an exponential distribution with mean ``mu``, using the formula given above.

    .. code::

        >>> exponential_pdf(2, 1)
        = 0.1353352832366127I


.. function:: exponential_P(x, mu)

    Computes the cumulative density :math:`P(x)` at :math:`x`

    .. math::

        P(x) = \int_{-\infty}^{x} p(t) dt

    where :math:`p(t)` is the exponential distribution with mean ``mu``. Aliases: ``exp_P``

    .. code::

        >>> exponential_P(2, 1)
        = 0.8646647167633873
        >>> exp_P(2, 1)
        = 0.8646647167633873


.. function:: exponential_Pinv(x, mu)

    Computes the inverse of the cumulative density :math:`P^{-1}(x)` at :math:`x` for the exponential distribution with mean ``mu``. Aliases: ``exp_Pinv``

    .. code::

        >>> exponential_Pinv(0.8646647167633873, 1)
        = 2
        >>> exp_Pinv(0.8646647167633873, 1)
        = 2


.. function:: exponential_Q(x, mu)

    Computes the cumulative density :math:`P(x)` at :math:`x`

    .. math::

        Q(x) = \int_{x}^{\infty} p(t) dt

    where :math:`p(t)` is the exponential distribution with mean ``mu``. Aliases: ``exp_Q``

    .. code::

        >>> exponential_Q(2, 1)
        = 0.1353352832366127
        >>> exp_Q(2, 1)
        = 0.1353352832366127


.. function:: exponential_Qinv(x, mu)

    Computes the inverse of the cumulative density :math:`Q^{-1}(x)` at :math:`x` for the exponential distribution with mean ``mu``. Aliases: ``exp_Pinv``

    .. code::

        >>> exponential_Qinv(0.1353352832366127, 1)
        = 2
        >>> exp_Qinv(0.1353352832366127, 1)
        = 2


Chi-Squared Distribution
^^^^^^^^^^^^^^^^^^^^^^^^

.. function:: chisq(nu)

    Generates a random number from the chi-squared distribution with ``nu`` degrees of freedom.

    The probability distribution for chi-squared random variates is,

    .. math::

        p(x) dx = \frac{1}{2\Gamma(\nu/2)} (x/2)^{\nu/2-1} \exp\left( -\frac{x}{2} \right) dx

    for :math:`x \ge 0`

    .. code::

        >>> chisq(1)
        = 1.915412399185662
        >>> chisq(1)
        = 3.098215236623985


.. function:: chisq_pdf(x, nu)

    Computes the probability density :math:`p(x)` at :math:`x` for an chi-squared distribution with ``nu`` degrees of freedom, using the formula given above.

    .. code::

        >>> chisq_pdf(2, 1)
        = 0.1037768743551486


.. function:: chisq_P(x, nu)

    Computes the cumulative density :math:`P(x)` at :math:`x`

    .. math::

        P(x) = \int_{-\infty}^{x} p(t) dt

    where :math:`p(t)` is the chi-squared distribution with ``nu`` degrees of freedom.

    .. code::

        >>> chisq_P(2, 1)
        = 0.842700792949715
        >>> chisq_P(2, 2)
        = 0.6321205588285578


.. function:: chisq_Pinv(x, nu)

    Computes the inverse of the cumulative density :math:`P^{-1}(x)` at :math:`x` for the chi-squared distribution with ``nu`` degrees of freedom.

    .. code::

        >>> chisq_Pinv(0.842700792949715, 1)
        = 2
        >>> chisq_Pinv(0.6321205588285578, 2)
        = 2


.. function:: chisq_Q(x, nu)

    Computes the cumulative density :math:`P(x)` at :math:`x`

    .. math::

        Q(x) = \int_{x}^{\infty} p(t) dt

    where :math:`p(t)` is the chi-squared distribution with ``nu`` degrees of freedom.

    .. code::

        >>> chisq_Q(2, 1)
        = 0.157299207050285
        >>> chisq_Q(2, 2)
        = 0.3678794411714423


.. function:: chisq_Qinv(x, nu)

    Computes the inverse of the cumulative density :math:`Q^{-1}(x)` at :math:`x` for the chi-squared distribution with ``nu`` degrees of freedom.

    .. code::

        >>> chisq_Qinv(0.157299207050285, 1)
        = 2
        >>> chisq_Qinv(0.3678794411714423, 2)
        = 2
