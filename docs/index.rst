:orphan:

Welcome to Termcolor C++ library
================================

.. image:: _static/example.png
   :alt: termcolor in action
   :align: center

Welcome to termcolor_'s documentation. Termcolor is a header-only C++
library for printing colored messages to the terminal. Written just
for fun with a help of `the Force`_.

Termcolor uses `ANSI color formatting`_, so you can use it on every
system that is used such terminals (most \*nix systems, including Linux
and Mac OS). On Windows, WinAPI is used instead, but some limitations
are applied.

It's licensed under the BSD (3-clause) License. That basically means:
do whatever you want as long as copyright sticks around.

.. _termcolor: https://github.com/ikalnitsky/termcolor
.. _the Force: http://starwars.wikia.com/wiki/The_Force
.. _ANSI color formatting: http://en.wikipedia.org/wiki/ANSI_escape_code#Colors


Installation
------------

Add ``termcolor.hpp`` to the project and use provided stream manimulators
from the ``termcolor`` namespace.


How to use?
-----------

It's very easy to use. The idea is based on the use of C++ stream
manipulators. The typical «Hello World» application is below::

    #include <iostream>
    #include <termcolor/termcolor.hpp>


    int main(int /*argc*/, char** /*argv*/)
    {
        std::cout << termcolor::red << "Hello, Colorful World!" << std::endl;
        return 0;
    }

The application above prints a string with red. It's obvious, isn't it?
There is a one problem that is not obvious for the unexperienced users.
If you write something this way::

    std::cout << termcolor::red << "Hello, Colorful World!" << std::endl;
    std::cout << "Here I'm!" << std::endl;

the phrase «Here I'm» will be printed with red too. Why? Because you don't
reset termcolor's setting. So if you want to print text wit default terminal
setting you have to reset termcolor's settings. It can be done by using
``termcolor::reset`` manipulator::

    std::cout << termcolor::red << "Hello, Colorful World!" << std::endl;
    std::cout << termcolor::reset << "Here I'm!" << std::endl;


What manipulators are supported?
--------------------------------

The manipulators are divided into three groups:

* *foreground*, which changes text color;
* *background*, which changes text background color;
* *attributes*, which changes some text style (bold, underline, etc).


Foreground manipulators
.......................

#. ``termcolor::grey``
#. ``termcolor::red``
#. ``termcolor::green``
#. ``termcolor::yellow``
#. ``termcolor::blue``
#. ``termcolor::magenta``
#. ``termcolor::cyan``
#. ``termcolor::white``


Background manipulators
.......................

#. ``termcolor::on_grey``
#. ``termcolor::on_red``
#. ``termcolor::on_green``
#. ``termcolor::on_yellow``
#. ``termcolor::on_blue``
#. ``termcolor::on_magenta``
#. ``termcolor::on_cyan``
#. ``termcolor::on_white``


Attribute manipulators
......................

(so far they don't supported by Windows)

#. ``termcolor::bold``
#. ``termcolor::dark``
#. ``termcolor::underline``
#. ``termcolor::blink``
#. ``termcolor::reverse``
#. ``termcolor::concealed``
