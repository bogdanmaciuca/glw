#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <print>

class Debug {
public:
    Debug() = delete;
    Debug operator=(Debug&) = delete;

    static void Set(bool debug);

    template<typename... Args>
    static void Print(std::format_string<Args...> fmt_str, Args&&... args) {
        if (s_debug)
            std::println(fmt_str, std::forward<Args>(args)...);
    }
private:
    inline static bool s_debug = false;
};

#endif // DEBUG_HPP

