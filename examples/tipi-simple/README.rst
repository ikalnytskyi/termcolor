Termcolor example with tipi.build
=================================

This example shows how Termcolor_ can be easily used with tipi.build_.

.. _Termcolor: https://github.com/ikalnytskyi/termcolor
.. _tipi.build: https://tipi.build/

Building the example
--------------------

You can build the example using one of the following commands (depending on your host OS):

  .. code:: sh

      $ tipi . -t linux
      $ tipi . -t macos
      $ tipi . -t windows
      $ tipi . -t vs-16-2019-win64-cxx17


Use the command ``tipi build . -t <target>`` to execute remote builds for targets not supported by your host OS using tipi.
