
#include "../libs/networking.h++"
#include "../libs/misc_functions.h++"
#include "included.h++"
#include <unistd.h>


// const std::string UNDER_CONSTRUCTION = "UNDER CONSTRUCTION";



void list_machine_adapters();

void resolve_hostname();

int main(int len, char** args) {

    int index;
    std::printf("There are %d arguments:\n", len - 1);
    for (index = 1; index < len; index++) {
        std::printf("\t%d.) %s\n", index, args[index]);
        if (string_functions::same_string(std::string(args[index]), "list_adapters") or string_functions::same_string(std::string(args[index]), "la")) {
            list_machine_adapters();
        }

        else if (string_functions::same_string(std::string(args[index]), "resolve_host") or string_functions::same_string(std::string(args[index]), "rh")) {
            resolve_hostname();
        }
    }

    return 0;
}



void list_machine_adapters() {
    std::map<std::string, std::map<std::string, std::vector<std::string> > > 
    adapters = networking::this_machine_adapters();

    for (auto this_adapter = adapters.begin(); this_adapter NOT adapters.end(); this_adapter++) {
        std::printf("%s:\n", this_adapter->first.c_str());
        for (auto this_family = this_adapter->second.begin(); this_family NOT this_adapter->second.end(); this_family++) {
            std::printf("\t\"%s\":\t", this_family->first.c_str());
            const unsigned long len = this_family->second.size();
            unsigned long index = 0;
            for (auto this_address = this_family->second.begin(); this_address NOT this_family->second.end(); this_address++) {
                std::printf("%s%s", this_address->c_str(), (index + 1 is len) ? "\n" : ", ");
                index++;
            }
        }
    }
}

void resolve_hostname() {
    std::string host;
    std::cout << "Hostname : ";
    std::cin >> host;
    std::cout << std::endl;
    std::vector<std::string> addresses = networking::resolve_hostname(host);
    std::cout << host << ":" << std::endl;
    unsigned long index;
    for (index = 0; index < addresses.size(); index++) {
        std::cout << "\t" << addresses[index] << std::endl;
    }
}
