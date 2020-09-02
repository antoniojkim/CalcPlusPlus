Exponentials and Logarithms
===========================

.. function:: exp(x)

    Computes :math:`e^{x}`.

    .. code::

        >>> exp(3)
        = 20.08553692318767
        >>> exp(ln(3))
        = 3


.. function:: exp2(x)

    Computes :math:`2^{x}`.

    .. code::

        >>> exp2(3)
        = 8
        >>> exp2(ln2(3))
        = 3


.. function:: expm1(x)

    Computes :math:`e^{x} - 1` in a way that is accurate for small :math:`x`.

    .. code::

        >>> expm1(20)
        = 19.08553692318767
        >>> expm1(0.01)
        = 0.01005016708416806
        >>> expm1(ln(3))
        = 2


.. function:: ln(x)

    Computes the natural logarithm :math:`\log_{e}{x}`.

    .. code::

        >>> ln(20)
        = 2.995732273553991
        >>> ln(exp(20))
        = 20


.. function:: ln2(x)

    Computes the logarithm base :math:`2`, :math:`\log_{2}{x}`. Aliases: ``log2``.

    .. code::

        >>> ln2(8)
        = 3
        >>> log2(exp2(8))
        = 8


.. function:: ln1p(x)

    Computes :math:`\log_{e}(1 + x)`. Aliases: ``log1p``.

    .. code::

        >>> ln1p(8)
        = 2.19722457733622
        >>> log1p(expm1(8))
        = 8


.. function:: log(x)

    Computes the logarithm base :math:`10`, :math:`\log_{10}{x}`. Aliases: ``log10``.

    .. code::

        >>> log(100)
        = 2
        >>> log10(10^3)
        = 3


.. function:: log1pm(x)

    Computes :math:`\log_{e}(1 + x) - x`.

    .. code::

        >>> log1pm(5)
        = -3.208240530771945


.. function:: logabs(x)

    Computes :math:`\log_{e}|x|`.

    .. code::

        >>> log1pm(5)
        = 1.09861228866811


.. function:: logn(a, b)

    computes :math:`\log_{b}{a}`

    .. code::

        >>> logn(2, 3)
        = 0.6309297535714574
