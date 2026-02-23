#include "utils.h"

#include <iostream>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// Enable ANSI escape sequence processing on Windows consoles (once).
static void enable_ansi_colors_on_windows() {
#ifdef _WIN32
    static bool enabled = []() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE)
            return false;
        DWORD dwMode = 0;
        if (!GetConsoleMode(hOut, &dwMode))
            return false;
        dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        if (!SetConsoleMode(hOut, dwMode))
            return false;
        return true;
    }();
    (void)enabled;
#endif
}

void TestPrint(const std::string &s) {
    enable_ansi_colors_on_windows();
    // Print a blank line, then a blue [TEST] tag (bright blue) and reset color.
    const char *blue = "\x1b[1;34m"; // bright blue
    const char *reset = "\x1b[0m";
    std::cout << std::endl << blue << "[TEST]" << reset << " " << s << std::endl;
}

void ms::Student::set(int _id, bool _male, std::string _name) {
    id = _id;
    male = _male;
    name = _name;
}

void ms::Student::print() {
    if (id == -1)
        printf("[Student] NULL.\n");
    else
        printf("[Student] id = %d, %s, name = \"%s\".\n", id, male ? "male" : "female", name.c_str());
}

bool ms::Student::operator<(const Student &stu) const {
    if (id == stu.id && male == stu.male && name == stu.name)
        return true;
    // 完全相同时返回true，使得升序排序保持稳定性
    return id < stu.id;
}

void ms::Student::operator=(const Student &stu) {
    id = stu.id;
    male = stu.male;
    name = stu.name;
}

void ms::Student::operator=(Student &&stu) {
    id = stu.id;
    male = stu.male;
    name = std::move(stu.name);
}
