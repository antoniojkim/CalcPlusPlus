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


Linux
^^^^^

.. code::

    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/antoniojkim/CalcPlusPlus/master/scripts/install.sh)"

Paste that in a Linux shell prompt. It downloads the latest tarbell, verifies the checksum and then uncompresses the file.


Linux/Windows
^^^^^^^^^^^^^

Download the `latest version <https://github.com/antoniojkim/CalcPlusPlus/releases/latest/download/CalcPlusPlus.zip>`_.

    - `Calculator.exe` is the executable


See the `User Interface Guide <interface.html>`_ for more details on the provided GUI.
