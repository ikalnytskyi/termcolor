//!
//! termcolor
//! ~~~~~~~~~
//!
//! termcolor is a header-only c++ library for printing colored messages
//! to the terminal. Written just for fun with a help of the Force.
//!
//! :copyright: (c) 2013 by Igor Kalnitsky
//! :license: BSD, see LICENSE for details
//!

#ifndef TERMCOLOR_HPP_
#define TERMCOLOR_HPP_

// the following snippet of code detects the current OS and
// defines the appropriate macro that is used to wrap some
// platform specific things
#if defined(_WIN32) || defined(_WIN64)
#   define OS_WINDOWS
#elif defined(__APPLE__)
#   define OS_MACOS
#elif defined(linux) || defined(__linux)
#   define OS_LINUX
#else
#   error unsupported platform
#endif


// This headers provides the `isatty()`/`fileno()` functions,
// which are used for testing whether a standart stream refers
// to the terminal.
#if defined(OS_MACOS) || defined(OS_LINUX)
#   include <unistd.h>
#elif defined(OS_WINDOWS)
#   include <io.h>
#endif


#include <iostream>
#include <cstdio>



namespace termcolor
{
    // Forward declaration of the `__internal` namespace.
    // All comments are below.
    namespace __internal
    {
        inline FILE* get_standard_stream(const std::ostream& stream);
        inline bool is_atty(const std::ostream& stream);
    }


    inline
    std::ostream& reset(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[00m";
        return stream;
    }


    inline
    std::ostream& bold(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[1m";
        return stream;
    }


    inline
    std::ostream& dark(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[2m";
        return stream;
    }


    inline
    std::ostream& underline(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[4m";
        return stream;
    }


    inline
    std::ostream& blink(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[5m";
        return stream;
    }


    inline
    std::ostream& reverse(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[7m";
        return stream;
    }


    inline
    std::ostream& concealed(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[8m";
        return stream;
    }


    inline
    std::ostream& grey(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[30m";
        return stream;
    }

    inline
    std::ostream& red(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[31m";
        return stream;
    }

    inline
    std::ostream& green(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[32m";
        return stream;
    }

    inline
    std::ostream& yellow(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[33m";
        return stream;
    }

    inline
    std::ostream& blue(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[34m";
        return stream;
    }

    inline
    std::ostream& magenta(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[35m";
        return stream;
    }

    inline
    std::ostream& cyan(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[36m";
        return stream;
    }

    inline
    std::ostream& white(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[37m";
        return stream;
    }



    inline
    std::ostream& on_grey(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[40m";
        return stream;
    }

    inline
    std::ostream& on_red(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[41m";
        return stream;
    }

    inline
    std::ostream& on_green(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[42m";
        return stream;
    }

    inline
    std::ostream& on_yellow(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[43m";
        return stream;
    }

    inline
    std::ostream& on_blue(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[44m";
        return stream;
    }

    inline
    std::ostream& on_magenta(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[45m";
        return stream;
    }

    inline
    std::ostream& on_cyan(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[46m";
        return stream;
    }

    inline
    std::ostream& on_white(std::ostream& stream)
    {
        if (__internal::is_atty(stream))
            stream << "\033[47m";
        return stream;
    }



    //! Since C++ hasn't a way to hide something in the header from
    //! the outer access, I have to introduce this namespace which
    //! is used for internal purpose and should't be access from
    //! the user code.
    namespace __internal
    {
        //! Since C++ hasn't a true way to extract stream handler
        //! from the a given `std::ostream` object, I have to write
        //! this kind of hack.
        inline
        FILE* get_standard_stream(const std::ostream& stream)
        {
            if (&stream == &std::cout)
                return stdout;
            else if (&stream == &std::cerr)
                return stderr;
            return nullptr;
        }


        //! Test whether a given `std::ostream` object refers to
        //! a terminal.
        inline
        bool is_atty(const std::ostream& stream)
        {
            FILE* std_stream = get_standard_stream(stream);

        #if defined(OS_MACOS) || defined(OS_LINUX)
            return ::isatty(fileno(std_stream));
        #elif defined(OS_WINDOWS)
            return ::_isatty(_fileno(std_stream));
        #endif
        }
    } // namespace __internal

} // namespace termcolor


#undef OS_WINDOWS
#undef OS_MACOS
#undef OS_LINUX

#endif // TERMCOLOR_HPP_
