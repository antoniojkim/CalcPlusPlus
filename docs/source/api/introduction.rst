Introduction
============

The CalcPlusPlus engine is a mathematics evaluation engine that can take in any string input and parse it into a mathematical expression, ready for evaluation. It is designed to be incredibly robust to syntax and semantic errors. In addition, it is written in high performance C++ code which employs low level BLAS operations to do most of the heavy lifting.

Installation
------------

Homebrew (Mac OS X)
^^^^^^^^^^^^^^^^^^^

Use homebrew to install a Mac OS version of the calculator using the following formula

.. code::

    brew cask install antoniojkim/public/calcpp
    # or to update the calculator
    brew reinstall antoniojkim/public/calcpp


Linux/Windows
^^^^^^^^^^^^^

Download the OS appropriate version from the `release page <https://github.com/antoniojkim/CalcPlusPlus/releases/>`_

  - `Linux <https://github.com/antoniojkim/CalcPlusPlus/releases/download/v0.3/calcplusplus.tar.gz>`_

    + ``Calculator.sh`` is the executable script

  - `Windows <https://github.com/antoniojkim/CalcPlusPlus/releases/download/v0.4/CalcPlusPlus.zip>`_

    + ``Calculator.exe`` is the executable


See the `User Interface Guide <interface.html>`_ for more details on the provided GUI.
