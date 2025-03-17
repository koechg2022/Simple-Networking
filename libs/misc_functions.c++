


// #include "../headers/included"
#include "string_functions"
#include "misc_functions"


namespace misc_functions {
    const std::string _directory_ = "Directory";
    const std::string _file_ = "File";
}

const std::string misc_functions::get_current_time() {
    
    std::time_t now = std::time(nullptr);
    char buffer[buffer_size]; // Standard size for ctime output

    #if defined(crap_os)
        // Use ctime_s on Windows
        errno_t result = ctime_s(buffer, buffer_size, &now);
        if (result != 0) {
            return "Error getting time";
        }
    #else
        // Use ctime_r on POSIX systems (Linux, macOS, etc.)
        if (not ctime_r(&now, buffer)) {
            return "Error getting time";
        }
    #endif

    std::string the_answer(buffer);
    return the_answer.substr(0, the_answer.length() - 1); // Remove trailing newline
}

int misc_functions::get_terminal_width() {
    int the_answer = 0;
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
    int the_answer = 0;
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

std::map<std::string, std::string> misc_functions::get_file_data_map(const std::string& file_name, const std::string delimiter) {
    std::map<std::string, std::string> the_answer;

    if (not std::filesystem::exists(std::filesystem::path(file_name).lexically_normal())) {
        std::cerr << "No file '" << file_name << "' found\n";
        return the_answer;
    }

    std::ifstream open_file(file_name);
    if (not open_file.is_open()) {
        std::cerr << "Could not open file '" << file_name << "'" << std::endl;
        return the_answer;
    }

    std::string line, key, value;
    size_t delim;
    while (std::getline(open_file, line)) {
        delim = line.find_first_of(delimiter);
        if (delim < line.length()) {
            key = line.substr(0, delim);
            value = line.substr(delim + 1);

            string_functions::strip(key, " ");
            string_functions::strip(value, " ");
            string_functions::strip(value, "\n");

            the_answer[key] = value;
        }
    }
    open_file.close();
    return the_answer;
}

std::map<std::string, std::vector<std::string> > misc_functions::get_directory_content(const std::string& file_name) {
    

    std::map<std::string, std::vector<std::string> > the_answer = {
                    {_directory_, std::vector<std::string>() },
                    {_file_, std::vector<std::string>() }
                    };
    
    for (const auto& entry : std::filesystem::directory_iterator(file_name)) {
        the_answer[(entry.is_directory()) ? _directory_ : _file_].push_back(std::string(entry.path().filename().string()));
    }
    return the_answer;
}

std::string misc_functions::get_file_data(const std::string file_name) {

    std::string the_answer, line;
    
    if (not std::filesystem::exists(std::filesystem::path(file_name).lexically_normal())) {
        std::cerr << "No file '" << file_name << "' found\n";
        return the_answer;
    }

    std::fstream open_file(file_name, std::ios_base::in | std::ios_base::binary);
    if (not open_file.is_open()) {
        std::cerr << "Could not open file \"" << file_name << "\"" << std::endl;
        return the_answer;
    }

    while (std::getline(open_file, line)) {
        the_answer = the_answer + line;
    }

    return the_answer;
}


std::string misc_functions::get_base_directory(const std::string dir_name, bool ignore_case) {
    std::filesystem::path current_path = std::filesystem::absolute(std::filesystem::current_path());
    std::string name = dir_name;
    string_functions::strip(name, sys_slash);

    // Search up the directory tree
    while (current_path != current_path.root_path()) {
        std::string parent_path = current_path.string();
        std::map<std::string, std::vector<std::string>> dir_content = misc_functions::get_directory_content(parent_path);

        for (const auto& content : dir_content[misc_functions::_directory_]) {
            std::string stripped_content = content;
            string_functions::strip(stripped_content, sys_slash);
            if (string_functions::same_string(name, stripped_content, ignore_case)) {
                return (std::filesystem::path(parent_path) / content).string();
            }
        }

        current_path = current_path.parent_path();
    }

    // If not found in parent directories, search recursively from project root
    std::filesystem::path project_root = std::filesystem::absolute(std::filesystem::path(".."));
    for (const auto& entry : std::filesystem::recursive_directory_iterator(project_root)) {
        if (entry.is_directory()) {
            std::string stripped_entry_name = entry.path().filename().string();
            string_functions::strip(stripped_entry_name, sys_slash);
            if (string_functions::same_string(name, stripped_entry_name, ignore_case)) {
                return entry.path().string();
            }
        }
    }

    // If not found at all, return original absolute path
    return std::filesystem::absolute(dir_name).string();
}

bool misc_functions::has_keyboard_input() {
    #if defined(crap_os)
        return _kbhit();
    #else
        fd_set ready;
        FD_ZERO(&ready);
        FD_SET(STDIN_FILENO, &ready);
        struct timeval default_timeout = {0, 100000};
        if (select(STDIN_FILENO + 1, &ready, 0, 0, &default_timeout) less 0) {
            return false;
        }
        return FD_ISSET(STDIN_FILENO, &ready);
    #endif
}


std::string misc_functions::get_input(const std::string prompt) {
    std::string the_answer;

    if (not prompt.empty()) {
        std::printf("%s", prompt.c_str());
    }
    
    char buffer[1024];
    std::memset(buffer, 0, 1024);
    if (not fgets(buffer, 1024, stdin)) {
        return the_answer;
    }
    the_answer = std::string(buffer);
    the_answer = (the_answer[the_answer.length() - 1] is '\n') ? the_answer.substr(0, the_answer.length() - 1) : the_answer;
    return the_answer;
}