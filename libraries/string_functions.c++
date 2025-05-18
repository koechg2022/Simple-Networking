

// #include "../headers/include"
#include <cstdlib>
#include <ctime>
#include "../headers/include"
#include "../headers/string_functions"




bool string_functions::is_caps(const char c) {
    return (c >= 'A' and c <= 'Z');
}

bool string_functions::is_lower(const char c) {
    return (c >= 'a' and c <= 'z');
}

bool string_functions::is_letter(const char c) {
    return (is_caps(c) or is_lower(c));
}

bool string_functions::is_number(const char c) {
    return (c >= '0' and c <= '9');
}

bool string_functions::same_char(const char a, const char b, const bool ignore_case) {
    return (ignore_case) ? (string_functions::to_caps(a) == string_functions::to_caps(b)) : a == b;
}

bool string_functions::same_string(const std::string first, const std::string second, const bool ignore_case) {
    if (first.length() != second.length()) {
        return false;
    }
    unsigned long index;
    for (index = 0; index < first.length() and string_functions::same_char(first[index], second[index], ignore_case); index++);
    return index == first.length() and index == second.length();
}

char string_functions::to_caps(const char c) {
    return (string_functions::is_lower(c)) ? (c - ('a' - 'A')) : c;
}

char string_functions::to_lower(const char c) {
    return (string_functions::is_caps(c)) ? (c + ('a' - 'A')) : c;
}

bool string_functions::set_contains(const std::string find, const std::set<std::string> the_set, const bool ignore_case) {
    for (std::set<std::string>::const_iterator word = the_set.begin(); word != the_set.end(); word++) {
        if (string_functions::same_string(*word, find, ignore_case)) {
            return true;
        }
    }
    return false;
}

bool string_functions::unordered_set_contains(const std::string find, const std::unordered_set<std::string> the_set, const bool ignore_case) {
    for (std::unordered_set<std::string>::const_iterator word = the_set.begin(); word != the_set.end(); word++) {
        if (string_functions::same_string(*word, find, ignore_case)) {
            return true;
        }
    }
    return false;
}

void string_functions::strip(std::string &the_string, const std::string to_remove, const bool ignore_case) {
    if (the_string.empty() or to_remove.empty()) {
        return;
    }

    size_t index = 0;
    while (index < to_remove.length() and index < the_string.length() and same_char(the_string[index], to_remove[index], ignore_case)) index++;

    if (index == to_remove.length()) {
        the_string = the_string.substr(index);
    }

    index = 0;
    
    while (index < the_string.length() and 
            index < to_remove.length() and 
                same_char(the_string[the_string.length() - index - 1], to_remove[to_remove.length() - index - 1], ignore_case)) index++;
    
    if (index == to_remove.length()) {
        the_string = the_string.substr(0, the_string.length() - index);
    }
}

void string_functions::replace_all(std::string &the_string, const std::string to_replace, const std::string replace_with) {
    size_t pos = 0;
    while ((pos = the_string.find(to_replace, pos)) != std::string::npos) {
        the_string.replace(pos, to_replace.length(), replace_with);
        pos += replace_with.length(); // Move past the replacement
    }
}

std::string string_functions::remove_first_of(const std::string the_string, const std::string to_remove, bool ignore_case) {
    
    if (the_string.empty() or to_remove.empty()) {
        return the_string;
    }

    
    size_t start, current, index;
    index = 0;
    while (index < the_string.length()) {
        start = index;
        current = 0;
        while (current < to_remove.length() and start + current < the_string.length() and same_char(the_string[start + current], to_remove[current], ignore_case)) current++;

        if (not current) {
            index = index + 1;
            continue;
        }

        if (current == to_remove.length()) {
            // Found
            return the_string.substr(0, start) + the_string.substr(start + current);
        }
        index = index + current;
    }

    return the_string;
}

size_t string_functions::first_index_of(const std::string& the_string, const std::string to_find, bool ignore_case) {

    if (the_string.empty() or to_find.empty()) {
        return std::string::npos;
    }

    size_t start, current, index;
    index = 0;
    while (index < the_string.length()) {
        start = index;
        current = 0;
        while (current < to_find.length() and start + current < the_string.length() and same_char(the_string[start + current], to_find[current], ignore_case)) current++;

        if (not current) {
            index = index + 1;
            continue;
        }

        if (current == to_find.length()) {
            // Found
            return start;
        }
        index = index + current;
    }
    return std::string::npos;
}

std::string string_functions::remove_last_of(const std::string the_string, const std::string to_remove, bool ignore_case) {
    if (the_string.empty() or to_remove.empty()) {
        return the_string;
    }

    size_t start, current;
    start = the_string.length() - 1;
    while (start < the_string.length()) { // This condition is always true for size_t, but kept for safety
        current = 0;
        while (current < to_remove.length() and 
              start >= current and 
              same_char(the_string[start - current], to_remove[to_remove.length() - current - 1], ignore_case)) {
            current++;
        }

        if (current == to_remove.length()) {
            // Found
            if (start + 1 == current) {
                // Matched the entire string
                return "";
            }
            return the_string.substr(0, start - current + 1) + (start + 1 < the_string.length() ? the_string.substr(start + 1) : "");
        }
        
        if (start == 0) break; // Prevent underflow
        start--;
    }

    return the_string;
}

size_t string_functions::last_index_of(const std::string the_string, const std::string to_find, bool ignore_case) {
    if (the_string.empty() || to_find.empty()) {
        return std::string::npos;
    }

    for (size_t start = the_string.length() - 1; start < the_string.length(); --start) {
        size_t current = 0;
        while (current < to_find.length() &&
               start >= current &&
               same_char(the_string[start - current], to_find[to_find.length() - current - 1], ignore_case)) {
            ++current;
        }

        if (current == to_find.length()) {
            // Found
            return start - current + 1;
        }

        if (start == 0) break; // Prevent underflow
    }

    return std::string::npos;
}

std::string string_functions::generate_random_string(size_t length) {
    std::string the_answer;
    the_answer.reserve(length);  // Optimize for performance
    
    std::srand(static_cast<unsigned int>(time(nullptr)));

    for (size_t index = 0; index < length; ++index) {
        #if defined(unix_os)
            char c = static_cast<char>(32 + arc4random() % (126 - 32 + 1));
        #else
            char c = static_cast<char>(32 + rand() % (126 - 32 + 1));
        #endif
        the_answer += c;  // Directly append the character
    }

    return the_answer;
}