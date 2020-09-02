Statistics
==========

Mean, Standard Deviation and Variance
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. function:: mean(a…)

    Computes the arithmetic mean of :math:`a`, a dataset of length :math:`n`. The arithmetic mean, or sample mean, is denoted by :math:`\hat\mu` and defined as,

    .. math:: \hat\mu = {1 \over N} \sum a_i

    where :math:`a_i` are the elements of the dataset :math:`a`.

    .. code::

        >>> mean(1, 3, 6, 10)
        = 5
        >>> mean(1, 3, 7, 11, 13, 17)
        = 26/3


.. function:: var(a…, ddof=1)

    Computes the variance of :math:`a`, a dataset of length :math:`n`. The variance is denoted by :math:`\hat\sigma^2` and defined as,

    .. math:: \hat\sigma^2 = \frac{1}{N - \text{ddof}} \sum (a_i - \hat\mu)^2

    where :math:`a_i` are the elements of the dataset :math:`a` and ``ddof`` denotes the degrees of freedom. Aliases: ``variance``

    .. code::

        >>> var(1, 3, 7, 11, 13, 17)
        = 562/15
        >>> variance(1, 3, 7, 11, 13, 17, ddof=2)
        = 281/6


.. function:: sd(a…, ddof=1)

    Computes the standard deviation of :math:`a`, a dataset of length :math:`n`. The standard deviation is denoted by :math:`\hat\sigma` and defined as the square root of the variance. Aliases: ``std``, ``stdev``

    .. code::

        >>> sd(1, 3, 7, 11, 13, 17)
        = 6.121002096606949
        >>> std(1, 3, 7, 11, 13, 17, ddof=2)
        = 6.843488389215937


.. function:: tss(a…)

    Computes the total sum of squares (TSS) of :math:`a`, a dataset of length :math:`n`. The TSS defined as,

    .. math::

        \text{TSS} = \sum (a_i - \hat\mu)^2

    where :math:`a_i` are the elements of the dataset :math:`a` and :math:`\hat\mu` denotes the arithmetic mean of :math:`a`.

    .. code::

        >>> tss(1, 3, 7, 11, 13, 17)
        = 562/3


Absolute deviation
^^^^^^^^^^^^^^^^^^

.. function:: absdev(a…)

    Computes the absolute deviation from the mean of :math:`a`, a dataset of length :math:`n`. The absolute deviation from the mean is defined as,

    .. math::

        \text{absdev} = \frac{1}{N} \sum |a_i - \hat\mu|

    where :math:`a_i` are the elements of the dataset :math:`a` and :math:`\hat\mu` denotes the arithmetic mean of :math:`a`.

    .. code::

        >>> absdev(1, 3, 7, 11, 13, 17)
        = 5


Higher moments (skewness and kurtosis)
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. function:: skew(a…)

    Computes the skewness of :math:`a`, a dataset of length :math:`n`. The skewness is defined as,

    .. math::

        \text{skew} = \frac{1}{N} \sum \left( \frac{a_i - \hat\mu}{\hat\sigma} \right)^3

    where :math:`a_i` are the elements of the dataset :math:`a`, :math:`\hat\mu` denotes the arithmetic mean of :math:`a`, and :math:`\hat\sigma` denotes the standard deviation of :math:`a`.

    .. code::

        >>> skew(1, 3, 7, 11, 13, 17)
        = 0.02583976940771193


.. function:: kurtosis(a…)

    Computes the kurtosis of :math:`a`, a dataset of length :math:`n`. The kurtosis is defined as,

    .. math::

        \text{kurtosis} = \left( \frac{1}{N} \sum \left( \frac{a_i - \hat\mu}{\hat\sigma} \right)^4 \right) - 3

    where :math:`a_i` are the elements of the dataset :math:`a`, :math:`\hat\mu` denotes the arithmetic mean of :math:`a`, and :math:`\hat\sigma` denotes the standard deviation of :math:`a`. Aliases: ``kurt``

    .. code::

        >>> kurtosis(1, 3, 7, 11, 13, 17)
        = -1.848508546413208
        >>> kurt(1, 3, 7, 11, 13, 17)
        = -1.848508546413208


Autocorrelation
^^^^^^^^^^^^^^^

.. function:: lag1(a…)

    Computes the lag-1 autocorrelation of :math:`a`, a dataset of length :math:`n`. The lag-1 autocorrelation is defined as,

    .. math::

        l_1 = \frac{\sum_{i=2}^{n} (a_i - \hat\mu)(a_{i-1} - \hat\mu)}{\sum_{i=1}^{n} (a_i - \hat\mu)(a_i - \hat\mu)}

    where :math:`a_i` are the elements of the dataset :math:`a`, :math:`\hat\mu` denotes the arithmetic mean of :math:`a`, and :math:`\hat\sigma` denotes the standard deviation of :math:`a`. Aliases: ``autocorr``

    .. code::

        >>> lag1(1, 3, 7, 11, 13, 17)
        = 857/1686 = 0.5083036773428232
        >>> autocorr(1, 3, 7, 11, 13, 17)
        = 857/1686 = 0.5083036773428232


Maximum and Minimum Values
^^^^^^^^^^^^^^^^^^^^^^^^^^

.. function:: max(a…)

    Computes the maximum value of :math:`a`, a dataset of length :math:`n`.

    .. code::

        >>> max(1, 3, 7, 11, 13, 17)
        = 17
        >>> max(-1, -3, -7, -11, -13, -17)
        = -1


.. function:: min(a…)

    Computes the minimum value of :math:`a`, a dataset of length :math:`n`.

    .. code::

        >>> min(1, 3, 7, 11, 13, 17)
        = 17
        >>> min(-1, -3, -7, -11, -13, -17)
        = -1


.. function:: argmax(a…)

    Computes the index of the maximum value of :math:`a`, a dataset of length :math:`n`. Aliases: ``max_index``

    .. code::

        >>> argmax(1, 3, 7, 11, 13, 17)
        = 5
        >>> max_index(-1, -3, -7, -11, -13, -17)
        = 0


.. function:: argmin(a…)

    Computes the index of the minimum value of :math:`a`, a dataset of length :math:`n`. Aliases: ``min_index``

    .. code::

        >>> argmin(1, 3, 7, 11, 13, 17)
        = 0
        >>> min_index(-1, -3, -7, -11, -13, -17)
        = 5


Median and Percentiles
^^^^^^^^^^^^^^^^^^^^^^

.. function:: median(a…)

    Computes the median of :math:`a`, a dataset of length :math:`n`.

    .. code::

        >>> median(1, 3, 7, 11, 13, 17)
        = 9
        >>> median(0, -1, -3, -7, -11, -13, -17)
        = -7
