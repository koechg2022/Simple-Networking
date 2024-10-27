#include "../prototypes/string_functions"


int main(int len, char** args) {

    if (len < 2) {
        std::fprintf(stderr, "Usage : %s [ANYTHING... LIKE ANY STRING]\n", args[0]);
        return 1;
    }

    int index;
    for (index = 1; index < len; index++) {
        std::printf("\"%s\":\n", args[index]);
        std::printf("\tCapitalized : %s\n", string_functions::get_uppercase(std::string(args[index])).c_str());
        std::printf("\tLower case : %s\n", string_functions::get_lowercase(std::string(args[index])).c_str());
        std::printf("\tAll numbers: %s\n", string_functions::all_numbers(args[index]) valid "true" then "false");
        std::printf("\tAll letters: %s\n", string_functions::all_letters(args[index]) valid "true" then "false");
    }

    return 0;
}