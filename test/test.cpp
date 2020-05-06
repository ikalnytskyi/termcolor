//!
//! termcolor's test
//! ~~~~~~~~~~~~~~~~
//!
//! A simple file which used all the termcolor featured.
//! It isn't a usual automated test, it's an unsual visual test! :D
//!
//! :copyright: (c) 2013 by Ihor Kalnytskyi
//! :license: BSD, see LICENSE for details
//!

#if defined(_WIN32) || defined(_WIN64)
#   define NO_ANSI_ESCAPE_SEQUENCES
#endif

// Cygwin's C++ libraries seem to be stricter than other unix platforms.
// Strict standard conformance must be disabled by passing -U__STRICT_ANSI__
// (or equivalent option) to the compiler, or by #undef __STRICT_ANSI__
// before including this header file, <cstdio>, or before any other header
// that includes <cstdio> in the inclusion chain whithin the compilation
// unit that includes "termcolor.hpp". Or by enabling compiler extensions,
// such as issuing -std=gnu11++ GNU compiler option.
//
// This is required in order to `fileno()` is seen whithin "termcolor.hpp"
// scope. Note that other unix-like platforms could enforce strict standard
// conformance in the future and will require a similar workaround.
#if defined(__CYGWIN__)
#   undef __STRICT_ANSI__
#   include <iostream>
#   include <sstream>
#   define __STRICT_ANSI__
#else
#   include <iostream>
#   include <sstream>
#endif
#include "termcolor/termcolor.hpp"

using namespace termcolor;


int main(int /*argc*/, char** /*argv*/)
{
    // test truecolors
    std::cout << color<181, 137, 0> << "#b58900" << reset << std::endl;
    std::cout << on_color<211, 54, 130> << "#d33682" << reset << std::endl;
    std::cout << std::endl;

    // test 256 colors
    std::cout << color<123>  << "No. 123" << reset << std::endl;
    std::cout << on_color<234>  << "No. 234" << reset << std::endl;
    std::cout << std::endl;

    // test foreground colors
    std::cout << grey    << "grey message"    << reset << std::endl;
    std::cout << red     << "red message"     << reset << std::endl;
    std::cout << green   << "green message"   << reset << std::endl;
    std::cout << yellow  << "yellow message"  << reset << std::endl;
    std::cout << blue    << "blue message"    << reset << std::endl;
    std::cout << magenta << "magenta message" << reset << std::endl;
    std::cout << cyan    << "cyan message"    << reset << std::endl;
    std::cout << white   << "white message"   << reset << std::endl;
    std::cout            << "default message" << std::endl;
    std::cout << std::endl;

    // test background colors
    std::cout << on_grey    << "message on grey"    << reset << std::endl;
    std::cout << on_red     << "message on red"     << reset << std::endl;
    std::cout << on_green   << "message on green"   << reset << std::endl;
    std::cout << on_yellow  << "message on yellow"  << reset << std::endl;
    std::cout << on_blue    << "message on blue"    << reset << std::endl;
    std::cout << on_magenta << "message on magenta" << reset << std::endl;
    std::cout << on_cyan    << "message on cyan"    << reset << std::endl;
    std::cout << on_white   << "message on white"   << reset << std::endl;
    std::cout               << "default message"    << std::endl;
    std::cout << std::endl;

    // test foreground and backgrounds colors
    std::cout << red  << on_white  << "red on white"   << reset << std::endl;
    std::cout << blue << on_yellow << "blue on yellow" << reset << std::endl;
    std::cout << std::endl;

    // test unsual attributes
    std::cout << bold      << red  << "bold red message"  << reset << std::endl;
    std::cout << dark      << blue << "dark blue message" << reset << std::endl;
    std::cout << italic    << "italic message"     << reset << std::endl;
    std::cout << underline << "underlined message" << reset << std::endl;
    std::cout << blink     << "blinked message"    << reset << std::endl;
    std::cout << reverse   << "reversed message"   << reset << std::endl;
    std::cout << concealed << "concealed message"  << reset << std::endl;
    std::cout << crossed   << "crossed message"    << reset << std::endl;
    std::cout              << "default message"    << std::endl;
    std::cout << std::endl;

    // test clog/cerr streams
    std::clog << "formatted " << yellow << "std::clog" << reset << " message" << std::endl;
    std::cerr << "formatted " << red    << "std::cerr" << reset << " message" << std::endl;
    std::cout << std::endl;

    // test ansi escape characters are skipped for streams
    std::stringstream s1;
    s1 << red << "term" << blue << on_yellow << "color";

    if (s1.str() != "termcolor")
        return 1;

#ifndef NO_ANSI_ESCAPE_SEQUENCES
    // test ansi escape characters are preserved for streams if asked
    std::stringstream s2;
    s2 << colorize << red << "term" << nocolorize << blue << "color";

    if (s2.str() != "\033[31m" "termcolor")
        return 2;
#endif  // NO_ANSI_ESCAPE_SEQUENCES

    return 0;
}
