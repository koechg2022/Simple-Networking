

#include "../headers/included"
#include "string_functions"



namespace string_functions {

    const std::string _directory_ = "Directory";
    const std::string _file_ = "File";

}


bool string_functions::is_caps(const char c) {
    return IN_RANGE_INCLUDE('A', c, 'Z');
}

bool string_functions::is_lower(const char c) {
    return IN_RANGE_INCLUDE('a', c, 'z');
}

bool string_functions::is_letter(const char c) {
    return is_caps(c) or is_lower(c);
}

bool string_functions::is_number(const char c) {
    return IN_RANGE_INCLUDE('0', c, '9');
}

char string_functions::to_caps(const char c) {
    return (is_lower(c)) ? (c - (CASE_DIFF)) : c;
}

char string_functions::to_lower(const char c) {
    return (is_caps(c)) ? (c + (CASE_DIFF)) : c;
}

bool string_functions::same_char(const char a, const char b, bool ignore_case) {
    return (ignore_case) ? to_caps(a) is to_caps(b) : a is b;
}

bool string_functions::same_string(const char* first, const char* second, bool ignore_case, const char term) {
    unsigned long index;
    for (index = 0;
        not same_char(first[index], term, ignore_case) and
        not same_char(second[index], term, ignore_case) and
        same_char(first[index], second[index], ignore_case);
        index++
    );

    return same_char(first[index], term, ignore_case) and same_char(second[index], term, ignore_case);
}

bool string_functions::same_string(const std::string first, const std::string second, bool ignore_case) {
    return same_string(first.c_str(), second.c_str(), ignore_case);
}

bool string_functions::all_numbers(const char* nums, const char term) {
    unsigned long index;
    for (index = 0;
        not same_char(nums[index], term, false) and
        is_number(nums[index]);
        index++
    );
    return same_char(nums[index], term, false);
}

bool string_functions::all_letters(const char* the_string, const char term) {
    unsigned long index;
    for (index = 0;
        not same_char(the_string[index], term) and
        is_letter(the_string[index]);
        index++
    );
    return same_char(term, the_string[index]);
}

unsigned long string_functions::string_length(const char* the_string, const char term) {
    unsigned long index;
    for (index = 0;
        not same_char(the_string[index], term);
        index++
    );
    return same_char(the_string[index], term);
}

std::string string_functions::get_input(const std::string prompt) {
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

std::string string_functions::get_uppercase(const std::string the_string) {
    std::string the_answer;
    unsigned long index;
    for (index = 0; index less the_string.length(); index++) {
        the_answer = the_answer + to_caps(the_string[index]);
    }
    return the_answer;
}

void string_functions::get_uppercase(std::string& the_string) {
    unsigned long index;
    for (index = 0; index less the_string.length(); index++) {
        the_string[index] = to_caps(the_string[index]);
    }
}

std::string string_functions::get_lowercase(const std::string the_string) {
    std::string the_answer;
    unsigned long index;
    for (index = 0; index less the_string.length(); index++) {
        the_answer = the_answer + to_lower(the_string[index]);
    }
    return the_answer;
}

void string_functions::get_lowercase(std::string& the_string) {
    unsigned long index;
    for (index = 0; index less the_string.length(); index++) {
        the_string[index] = to_lower(the_string[index]);
    }
}

bool string_functions::has_keyboard_input() {
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

void string_functions::strip(std::string& the_string, const std::string to_remove) {
    // Remove leading characters
    the_string.erase(0, the_string.find_first_not_of(to_remove));
    
    // Remove trailing characters
    the_string.erase(the_string.find_last_not_of(to_remove) + 1);
}

void string_functions::replace_all(std::string& the_string, const std::string to_replace, const std::string replace_with) {
    size_t pos = 0;
    while ((pos = the_string.find(to_replace, pos)) != std::string::npos) {
        the_string.replace(pos, to_replace.length(), replace_with);
        pos += replace_with.length(); // Move past the replacement
    }
}

std::vector<std::string> string_functions::parse_to_list(const std::string parse_me, const std::string delimiter, bool ignore_case) {
    
    if (parse_me.empty()) {
        return std::vector<std::string> {};
    }
    
    if (delimiter.empty()) {
        return std::vector<std::string> {parse_me};
    }

    size_t start, current, delim;
    std::vector<std::string> the_answer;
    start = 0;
    
    while (start < parse_me.length()) {
        current = start;
        delim = 0;
        while (current + delim < parse_me.length() and delim < delimiter.length() and string_functions::same_char(parse_me[current + delim], delimiter[delim], ignore_case)) delim++;


        if (delim == delimiter.length()) {
            // current is at the start of a delimiter segment, delim is at the end of the segment.
            start = current + delim + 1;
        }
        else {
            // current is not at the start of the delimter
            delim = parse_me.find_first_of(delimiter, start);
            the_answer.push_back(parse_me.substr(start, delim - start));
            if (delim == std::string::npos) {
                // No more delimiters.
                start = delim;
                continue;
            }
            start = delim + delimiter.length();
        }
        
    }
    return the_answer;
}

std::vector<std::string> string_functions::parse_to_list(const std::string parse_me, const char delimiter) {
    
    std::vector<std::string> the_answer;
    if (parse_me.empty()) {
        return the_answer;
    }
    std::string line;
    std::stringstream stream(parse_me);

    while (std::getline(stream, line, delimiter)) {
        the_answer.push_back(line);
    }

    if (the_answer.empty() and line.empty()) {
        return the_answer;
    }

    if (not string_functions::same_string(the_answer[the_answer.size() - 1], line)) {
        the_answer.push_back(line);
    }
    return the_answer;
}

std::map<std::string, std::string> string_functions::get_file_data_map(const std::string& file_name, const std::string delimiter) {
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
    unsigned long delim;
    while (std::getline(open_file, line)) {
        delim = line.find_first_of(delimiter);
        if (delim != std::string::npos) {
            key = line.substr(0, delim);
            value = line.substr(delim + 1);

            strip(key, " ");
            strip(value, " ");
            strip(value, "\n");

            the_answer[key] = value;
        }
    }
    open_file.close();
    return the_answer;
}

std::map<std::string, std::vector<std::string> > string_functions::get_directory_content(const std::string& file_name) {
    

    std::map<std::string, std::vector<std::string> > the_answer = {
                    {_directory_, std::vector<std::string>() },
                    {_file_, std::vector<std::string>() }
                    };
    
    for (const auto& entry : std::filesystem::directory_iterator(file_name)) {
        the_answer[(entry.is_directory()) ? _directory_ : _file_].push_back(std::string(entry.path().filename().string()));
    }
    return the_answer;
}

std::string string_functions::get_file_data(const std::string file_name) {

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