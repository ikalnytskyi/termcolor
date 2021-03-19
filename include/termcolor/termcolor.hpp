//!
//! termcolor
//! ~~~~~~~~~
//!
//! termcolor is a header-only c++ library for printing colored messages
//! to the terminal. Written just for fun with a help of the Force.
//!
//! :copyright: (c) 2013 by Ihor Kalnytskyi
//! :license: BSD, see LICENSE for details
//!

#ifndef TERMCOLOR_HPP_
#define TERMCOLOR_HPP_

#include <iostream>
#include <cstdio>

// Detect target's platform and set some macros in order to wrap platform
// specific code this library depends on.
#if defined(_WIN32) || defined(_WIN64)
#   define TERMCOLOR_TARGET_WINDOWS
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#   define TERMCOLOR_TARGET_POSIX
#endif

// If implementation has not been explicitly set, try to choose one based on
// target platform.
#if !defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES) && !defined(TERMCOLOR_USE_WINDOWS_API) && !defined(TERMCOLOR_USE_NOOP)
#   if defined(TERMCOLOR_TARGET_POSIX)
#       define TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES
#       define TERMCOLOR_AUTODETECTED_IMPLEMENTATION
#   elif defined(TERMCOLOR_TARGET_WINDOWS)
#       define TERMCOLOR_USE_WINDOWS_API
#       define TERMCOLOR_AUTODETECTED_IMPLEMENTATION
#   endif
#endif

// These headers provide isatty()/fileno() functions, which are used for
// testing whether a standard stream refers to the terminal.
#if defined(TERMCOLOR_TARGET_POSIX)
#   include <unistd.h>
#elif defined(TERMCOLOR_TARGET_WINDOWS)
#   include <io.h>
#   include <windows.h>
#endif


namespace termcolor
{
    // Forward declaration of the `_internal` namespace.
    // All comments are below.
    namespace _internal
    {
        inline int colorize_index();
        inline FILE* get_standard_stream(const std::ostream& stream);
        inline FILE* get_standard_stream(const std::wostream& stream);
        template <typename CharT>
        inline bool is_colorized(std::basic_ostream<CharT>& stream);
        template <typename CharT>
        inline bool is_atty(const std::basic_ostream<CharT>& stream);

    #if defined(TERMCOLOR_TARGET_WINDOWS)
        inline void win_change_attributes(std::ostream& stream, int foreground, int background = -1);
        inline void win_change_attributes(std::wostream& stream, int foreground, int background = -1);
    #endif
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& colorize(std::basic_ostream<CharT>& stream)
    {
        stream.iword(_internal::colorize_index()) = 1L;
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& nocolorize(std::basic_ostream<CharT>& stream)
    {
        stream.iword(_internal::colorize_index()) = 0L;
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& reset(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[00m" : "\033[00m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1, -1);
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bold(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[1m" : "\033[1m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& dark(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[2m" : "\033[2m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& italic(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[3m" : "\033[3m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& underline(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[4m" : "\033[4m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1, COMMON_LVB_UNDERSCORE);
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& blink(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[5m" : "\033[5m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& reverse(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[7m" : "\033[7m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& concealed(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[8m" : "\033[8m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& crossed(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t>::value ? L"\033[9m" : "\033[9m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT, uint8_t code> inline
    std::basic_ostream<CharT>& color(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            CharT command[12];
            if (std::is_same<CharT, wchar_t>::value)
                std::_snrpintf_s(command, sizeof(command), L"\033[38;5;%dm", code);
            else
                std::snprintf(command, sizeof(command), "\033[38;5;%dm", code);
            stream << command;
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT, uint8_t code> inline
    std::basic_ostream<CharT>& on_color(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            CharT command[12];
            if (std::is_same<CharT, wchar_t>::value)
                std::_snrpintf_s(command, sizeof(command), L"\033[48;5;%dm", code);
            else
                std::snprintf(command, sizeof(command), "\033[48;5;%dm", code);
            stream << command;
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT, uint8_t r, uint8_t g, uint8_t b> inline
    std::basic_ostream<CharT>& color(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            CharT command[20];
            if (std::is_same<CharT, wchar_t>::value)
                std::_snrpintf_s(command, sizeof(command), L"\033[38;2;%d;%d;%dm", r, g, b);
            else
                std::snprintf(command, sizeof(command), "\033[38;2;%d;%d;%dm", r, g, b);
            stream << command;
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT, uint8_t r, uint8_t g, uint8_t b> inline
    std::basic_ostream<CharT>& on_color(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            CharT command[20];
            if (std::is_same<CharT, wchar_t>::value)
                std::_snrpintf_s(command, sizeof(command), L"\033[38;2;%d;%d;%dm", r, g, b);
            else
                std::snprintf(command, sizeof(command), "\033[38;2;%d;%d;%dm", r, g, b);
            stream << command;
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& grey(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[30m" : "\033[30m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                0   // grey (black)
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& red(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[31m" : "\033[31m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& green(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[32m" : "\033[32m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& yellow(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[33m" : "\033[33m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& blue(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[34m" : "\033[34m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& magenta(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[35m" : "\033[35m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& cyan(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[36m" : "\033[36m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& white(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[37m" : "\033[37m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }


    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_grey(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[90m" : "\033[90m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                0 | FOREGROUND_INTENSITY   // grey (black)
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_red(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[91m" : "\033[91m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_RED | FOREGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_green(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[92m" : "\033[92m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN | FOREGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_yellow(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[93m" : "\033[93m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_blue(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[94m" : "\033[94m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_magenta(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[95m" : "\033[95m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_cyan(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[96m" : "\033[96m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& bright_white(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[97m" : "\033[97m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }


    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_grey(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[40m" : "\033[40m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                0   // grey (black)
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_red(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[41m" : "\033[41m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_green(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[42m" : "\033[42m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_yellow(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[43m" : "\033[43m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_blue(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[44m" : "\033[44m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_magenta(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[45m" : "\033[45m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE | BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_cyan(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[46m" : "\033[46m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_white(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[47m" : "\033[47m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED
            );
        #endif
        }

        return stream;
    }


    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_grey(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[100m" : "\033[100m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                0 | BACKGROUND_INTENSITY   // grey (black)
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_red(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[101m" : "\033[101m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_RED | BACKGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_green(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[102m" : "\033[102m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_yellow(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[103m" : "\033[103m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_blue(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[104m" : "\033[104m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE | BACKGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_magenta(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[105m" : "\033[105m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_cyan(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[106m" : "\033[106m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY
            );
        #endif
        }
        return stream;
    }

    template <typename CharT>
    inline
    std::basic_ostream<CharT>& on_bright_white(std::basic_ostream<CharT>& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES)
            stream << std::is_same<CharT, wchar_t> ? L"\033[107m" : "\033[107m";
        #elif defined(TERMCOLOR_USE_WINDOWS_API)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY
            );
        #endif
        }

        return stream;
    }



    //! Since C++ hasn't a way to hide something in the header from
    //! the outer access, I have to introduce this namespace which
    //! is used for internal purpose and should't be access from
    //! the user code.
    namespace _internal
    {
        // An index to be used to access a private storage of I/O streams. See
        // colorize / nocolorize I/O manipulators for details. Due to the fact
        // that static variables ain't shared between translation units, inline
        // function with local static variable is used to do the trick and share
        // the variable value between translation units.
        inline int colorize_index()
        {
            static int colorize_index = std::ios_base::xalloc();
            return colorize_index;
        }

        //! Since C++ hasn't a true way to extract stream handler
        //! from the a given `std::ostream` object, I have to write
        //! this kind of hack.
        inline
        FILE* get_standard_stream(const std::ostream& stream)
        {
            if (&stream == &std::cout)
                return stdout;
            else if ((&stream == &std::cerr) || (&stream == &std::clog))
                return stderr;

            return nullptr;
        }

        //! Since C++ hasn't a true way to extract stream handler
        //! from the a given `std::ostream` object, I have to write
        //! this kind of hack.
        inline
        FILE* get_standard_stream(const std::wostream& stream)
        {
            if (&stream == &std::wcout)
                return stdout;
            else if ((&stream == &std::wcerr) || (&stream == &std::wclog))
                return stderr;

            return nullptr;
        }

        // Say whether a given stream should be colorized or not. It's always
        // true for ATTY streams and may be true for streams marked with
        // colorize flag.
        template <typename CharT>
        inline
        bool is_colorized(std::basic_ostream<CharT>& stream)
        {
            return is_atty(stream) || static_cast<bool>(stream.iword(colorize_index()));
        }

        //! Test whether a given `std::ostream` object refers to
        //! a terminal.
        template <typename CharT>
        inline
        bool is_atty(const std::basic_ostream<CharT>& stream)
        {
            FILE* std_stream = get_standard_stream(stream);

            // Unfortunately, fileno() ends with segmentation fault
            // if invalid file descriptor is passed. So we need to
            // handle this case gracefully and assume it's not a tty
            // if standard stream is not detected, and 0 is returned.
            if (!std_stream)
                return false;

        #if defined(TERMCOLOR_TARGET_POSIX)
            return ::isatty(fileno(std_stream));
        #elif defined(TERMCOLOR_TARGET_WINDOWS)
            return ::_isatty(_fileno(std_stream));
        #else
            return false;
        #endif
        }

    #if defined(TERMCOLOR_TARGET_WINDOWS)
        //! Change Windows Terminal colors attribute. If some
        //! parameter is `-1` then attribute won't changed.
        inline void win_change_attributes(std::ostream& stream, int foreground, int background)
        {
            // yeah, i know.. it's ugly, it's windows.
            static WORD defaultAttributes = 0;

            // Windows doesn't have ANSI escape sequences and so we use special
            // API to change Terminal output color. That means we can't
            // manipulate colors by means of "std::stringstream" and hence
            // should do nothing in this case.
            if (!_internal::is_atty(stream))
                return;

            // get terminal handle
            HANDLE hTerminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::cout)
                hTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
            else if ((&stream == &std::cerr) || (&stream == &std::clog))
                hTerminal = GetStdHandle(STD_ERROR_HANDLE);

            // save default terminal attributes if it unsaved
            if (!defaultAttributes)
            {
                CONSOLE_SCREEN_BUFFER_INFO info;
                if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                    return;
                defaultAttributes = info.wAttributes;
            }

            // restore all default settings
            if (foreground == -1 && background == -1)
            {
                SetConsoleTextAttribute(hTerminal, defaultAttributes);
                return;
            }

            // get current settings
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                return;

            if (foreground != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0x0F);
                info.wAttributes |= static_cast<WORD>(foreground);
            }

            if (background != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0xF0);
                info.wAttributes |= static_cast<WORD>(background);
            }

            SetConsoleTextAttribute(hTerminal, info.wAttributes);
        }

        //! Change Windows Terminal colors attribute. If some
        //! parameter is `-1` then attribute won't changed.
        inline void win_change_attributes(std::wostream& stream, int foreground, int background)
        {
            // yeah, i know.. it's ugly, it's windows.
            static WORD defaultAttributes = 0;

            // Windows doesn't have ANSI escape sequences and so we use special
            // API to change Terminal output color. That means we can't
            // manipulate colors by means of "std::stringstream" and hence
            // should do nothing in this case.
            if (!_internal::is_atty(stream))
                return;

            // get terminal handle
            HANDLE hTerminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::wcout)
                hTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
            else if ((&stream == &std::wcerr) || (&stream == &std::wclog))
                hTerminal = GetStdHandle(STD_ERROR_HANDLE);

            // save default terminal attributes if it unsaved
            if (!defaultAttributes)
            {
                CONSOLE_SCREEN_BUFFER_INFO info;
                if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                    return;
                defaultAttributes = info.wAttributes;
            }

            // restore all default settings
            if (foreground == -1 && background == -1)
            {
                SetConsoleTextAttribute(hTerminal, defaultAttributes);
                return;
            }

            // get current settings
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                return;

            if (foreground != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0x0F);
                info.wAttributes |= static_cast<WORD>(foreground);
            }

            if (background != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0xF0);
                info.wAttributes |= static_cast<WORD>(background);
            }

            SetConsoleTextAttribute(hTerminal, info.wAttributes);
        }
    #endif // TERMCOLOR_TARGET_WINDOWS

    } // namespace _internal

} // namespace termcolor


#undef TERMCOLOR_TARGET_POSIX
#undef TERMCOLOR_TARGET_WINDOWS

#if defined(TERMCOLOR_AUTODETECTED_IMPLEMENTATION)
#   undef TERMCOLOR_USE_ANSI_ESCAPE_SEQUENCES
#   undef TERMCOLOR_USE_WINDOWS_API
#endif

#endif // TERMCOLOR_HPP_
