Calculus
========

.. function:: deriv(f, x, var="x")

    Computes the numerical derivative for the function :math:`f` at point :math:`x` with respect to the variable ``var`` which by default is :math:`x`. That is, it computes

    .. math::

        f'(a) = \left(\frac{\partial}{\partial x} f \right) (a)

    .. code::

        >>> deriv(sin(x), 3)
        = -0.9899924966004454
        >>> deriv(sin(cos(x)), 3)
        = -0.07743200279648704
        >>> deriv(sin(cos(y)), 3, y)
        = -0.07743200279648704


.. function:: diff(f, var="x")

    Computes the differentiation of the function :math:`f` with respect to the variable ``var`` which by default is :math:`x`. That is, it computes

    .. math::

        f'(x) = \frac{\partial}{\partial x} f

    .. code::

        >>> diff(sin(x))
        = cos(x)
        >>> sin(x)'
        = cos(x)
        >>> diff(sin(cos(t)), t)
        = cos(cos(t)) * -sin(t)


.. function:: integral(f, a, b, var="x")

    Computes the numerical integration for the function :math:`f` from :math:`a` to :math:`b` with respect to the variable ``var`` which by default is :math:`x`. That is, it computes

    .. math::

        \int_{a}^{b} {f(x) dx}

    .. code::

        >>> integral(sin(x), 3, 5)
        = -1.273654682063672
        >>> integral(ln(sin(x)^2), -4, 7)
        = -17.06809502828264
