Fast Fourier Transform
======================

.. function:: fft(m)

    Computes the Fast Fourier Transform for the one dimensional matrix :math:`m`.

    .. code::

        >>> fft({1, 2, 3, 4})
        = {10, -2+2i, -2, -2-2i}


.. function:: ifft(m)

    Computes the inverse Fast Fourier Transform for the one dimensional matrix :math:`m`.

    .. code::

        >>> ifft({10, -2+2i, -2, -2-2i})
        = {1, 2, 3, 4}
