

#include "../headers/include"

#if defined(crap_os)
    #if not defined(_INC_CONIO)
        #include <conio.h>
    #endif

    #if not defined(_WINDOWS_)
        #include <Windows.h>
    #endif
#else
    #include <sys/ioctl.h>
    #include <unistd.h>
#endif

#include <cstdio>
#include <chrono>
#include <filesystem>
#include "../headers/misc_functions"
#include "../headers/string_functions"


std::string misc_functions::get_current_time() {
    const std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
    std::time_t answer = std::chrono::system_clock::to_time_t(time);
    std::string the_answer = std::ctime(&answer);
    return the_answer.substr(0, the_answer.length() - 1);
}

int misc_functions::get_terminal_width() {
    int the_answer = -1;
    #if defined(unix_os)
        struct winsize the_window;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &the_window);
        the_answer = the_window.ws_col;
    #else
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
        the_answer = cbsi.srWindow.Right - cbsi.srWindow.Left + 1;
    #endif
    return the_answer;
}

int misc_functions::get_terminal_height() {
    int the_answer = -1;
    #if defined(unix_os)
        struct winsize the_window;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &the_window);
        the_answer = the_window.ws_row;
    #else
        CONSOLE_SCREEN_BUFFER_INFO cbsi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cbsi);
        the_answer = cbsi.srWindow.Bottom - cbsi.srWindow.Top + 1;
    #endif
    return the_answer;
}

bool misc_functions::has_keyboard_input(const struct timeval timeout) {
    #if defined(crap_os)
        return _kbhit();
    #else
        fd_set ready;
        struct timeval timeout_ = {timeout.tv_sec < 0 ? 0 : timeout.tv_sec, timeout.tv_usec < 0 ? 0 : timeout.tv_usec};
        FD_ZERO(&ready);
        FD_SET(STDIN_FILENO, &ready);

        if (select(STDIN_FILENO + 1, &ready, 0, 0, &timeout_) < 0) {
            return false;
        }

        return FD_ISSET(STDIN_FILENO, &ready);
    #endif
}

std::unordered_map<misc_functions::content_type, std::vector<std::string> > misc_functions::get_directory_content(const std::string& directory, const bool complete_path) {
    std::unordered_map<misc_functions::content_type, std::vector<std::string> > the_answer;
    const content_type dir = DIRECTORY;
    const content_type file = FILE;

    for (const auto& thing : std::filesystem::directory_iterator(directory)) {
        the_answer[thing.is_directory() ? dir : file].push_back((complete_path) ? thing.path().string() : thing.path().filename().string());
    }

    return the_answer;
}

std::string misc_functions::get_input(const std::string prompt, std::FILE* the_file, const int k_count) {
    std::string the_answer;

    if (not prompt.empty()) {
        std::printf("%s", prompt.c_str());
    }

    char buffer[__kilo_bytes__(k_count)];
    if (not fgets(buffer, __kilo_bytes__(k_count), the_file)) {
        return the_answer;
    }
    
    the_answer = std::string(buffer);
    the_answer = string_functions::same_char(the_answer[the_answer.length() - 1], '\n') ? the_answer.substr(0, the_answer.length() - 1) : the_answer;
    return the_answer;
}