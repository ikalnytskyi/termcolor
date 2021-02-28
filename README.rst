Termcolor
=========

.. image:: docs/_static/example.png
   :alt: termcolor in action
   :align: left

.. -*- inclusion-marker-for-sphinx-docs -*-

Termcolor_ is a header-only C++ library for printing colored messages to the
terminal. Written just for fun with a help of `the Force`_. Termcolor uses
`ANSI color formatting`_, so you can use it on every system that is used such
terminals (most \*nix systems, including Linux and Mac OS).

.. note::

   On Windows, `Windows API`_ is used instead of escape codes but some
   limitations are applied (not everything is supported). That's why it's
   recommended to enter `virtual terminal processing`_ mode and set
   ``TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES`` macro to trick termcolor to use
   ANSI color codes.

   .. _virtual terminal processing: https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences

It's licensed under the BSD (3-clause) License. That basically means: do
whatever you want as long as copyright sticks around.

.. _Termcolor: https://github.com/ikalnytskyi/termcolor
.. _the Force: https://starwars.wikia.com/wiki/The_Force
.. _ANSI color formatting: https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
.. _Windows API: https://docs.microsoft.com/en-us/windows/console/setconsoletextattribute


Installation
------------

* Add ``termcolor.hpp`` (grab it from ``include/termcolor/termcolor.hpp``) to
  the project and use stream manipulators from the ``termcolor`` namespace.

* You can also use vcpkg_ to install the library:

  .. code:: sh

     $ vcpkg install termcolor

  .. _vcpkg: https://github.com/microsoft/vcpkg

* Or if you are on macOS, you can use Homebrew_ for that purpose:

  .. code:: sh

     $ brew install termcolor

  .. _Homebrew: https://brew.sh/

* For up-to-date information about existing packages, refer to the the following
  picture:

  .. image:: https://repology.org/badge/vertical-allrepos/termcolor.svg
     :target: https://repology.org/project/termcolor/versions
     :alt: Packaging Status


How to use?
-----------

It's very easy to use. The idea is built upon C++ stream manipulators.
Typical «Hello World» application looks like this:

.. code:: c++

    #include <iostream>
    #include <termcolor/termcolor.hpp>

    int main(int /*argc*/, char** /*argv*/)
    {
        std::cout << termcolor::red << "Hello, ";                   // 16 colors
        std::cout << termcolor::color<100> << "Colorful ";          // 256 colors
        std::cout << termcolor::color<211, 54, 130> << "World!";    // true colors
        std::cout << std::endl;
        return 0;
    }

The application above prints a string using different colors. There is one
caveat though. You must not forget to reset colors, otherwise they will be
applied to other prints as well.

.. code:: c++

    std::cout << termcolor::red << "Hello, Colorful World!" << std::endl;
    std::cout << "I'm RED too!" << std::endl;

Correct version of the code above should look like this:

.. code:: c++

    std::cout << termcolor::red << "Hello, Colorful World!" << termcolor::reset << std::endl;
    std::cout << termcolor::reset << "Here I'm!" << std::endl;

By default, Termcolor ignores any colors for non-tty streams (e.g.
``std::stringstream``), so the following snippet

.. code:: c++

    std::stringstream ss;
    ss << termcolor::red << "unicorn";
    std::cout << ss.str();

will print «unicorn» using default color, not red. In order to change this
behaviour one can use ``termcolor::colorize`` manipulator that enforce colors
no matter what.


What manipulators are supported?
--------------------------------

The manipulators are divided into four groups:

* *foreground*, which changes text color;
* *background*, which changes text background color;
* *attributes*, which changes some text style (bold, underline, etc);
* *control*, which changes termcolor's behaviour.

Also, there are color manipulators for `16 colors`_, `256 colors`_ and
`true colors`_ palettes.

.. note::

   While ``termcolor`` supports true color, it's required for the terminal
   emulator you use to run your software to support true color too. So please
   ensure it's supported before filing an issue.

.. _16 colors: https://en.wikipedia.org/wiki/Color_depth#4-bit_color
.. _256 colors: https://en.wikipedia.org/wiki/Color_depth#8-bit_color
.. _true colors: https://en.wikipedia.org/wiki/Color_depth#True_color_(24-bit)


Foreground manipulators
.......................

16 colors
`````````

#. ``termcolor::grey``
#. ``termcolor::red``
#. ``termcolor::green``
#. ``termcolor::yellow``
#. ``termcolor::blue``
#. ``termcolor::magenta``
#. ``termcolor::cyan``
#. ``termcolor::white``
#. ``termcolor::bright_grey``
#. ``termcolor::bright_red``
#. ``termcolor::bright_green``
#. ``termcolor::bright_yellow``
#. ``termcolor::bright_blue``
#. ``termcolor::bright_magenta``
#. ``termcolor::bright_cyan``
#. ``termcolor::bright_white``

256 colors
``````````

#. ``termcolor::color<256_COLOR_CODE>``

true colors
```````````

#. ``termcolor::color<RED, GREEN, BLUE>``


Background manipulators
.......................

16 colors
`````````

#. ``termcolor::on_grey``
#. ``termcolor::on_red``
#. ``termcolor::on_green``
#. ``termcolor::on_yellow``
#. ``termcolor::on_blue``
#. ``termcolor::on_magenta``
#. ``termcolor::on_cyan``
#. ``termcolor::on_white``
#. ``termcolor::on_bright_grey``
#. ``termcolor::on_bright_red``
#. ``termcolor::on_bright_green``
#. ``termcolor::on_bright_yellow``
#. ``termcolor::on_bright_blue``
#. ``termcolor::on_bright_magenta``
#. ``termcolor::on_bright_cyan``
#. ``termcolor::on_bright_white``

256 colors
``````````

#. ``termcolor::on_color<256_COLOR_CODE>``


true colors
```````````

#. ``termcolor::on_color<RED, GREEN, BLUE>``


Attribute manipulators
......................

(Windows API does not support these manipulators except for ``underline``)

#. ``termcolor::bold``
#. ``termcolor::dark``
#. ``termcolor::italic``
#. ``termcolor::underline``
#. ``termcolor::blink``
#. ``termcolor::reverse``
#. ``termcolor::concealed``
#. ``termcolor::crossed``

Control manipulators
....................

(Windows API does not support these manipulators)

#. ``termcolor::colorize``
#. ``termcolor::nocolorize``


Caveats
-------

#. On Windows, due to internal usage of ``<windows.h>``, global namespace could
   be polluted with `min`/`max` macros. If such effect is desireable, please
   consider using ``#define NOMINMAX`` before ``#include <termcolor.hpp>``.

