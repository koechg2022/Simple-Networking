
#include "headers"
#include "networking"
// #include "networking"
// #include "included"
// #include "string_functions"



const std::string UNDER_CONSTRUCTION = "UNDER CONSTRUCTION";
const std::string connection_port = "5500";


void list_machine_adapters();

void resolve_hostname();

void resolve_hostname_name();

void test_host();

void test_server();

void test_secure_server();

void test_client();

void test_secure_client();

void windows_tests();

int main(int len, char** args) {

    
    if (len <= 1) {
        std::printf("Help. This is for testing the networking library. Use one of the following arguments to test the library:\n");
        std::printf("\t'list_machine_adapters' | 'la':\tTo see all the current machine's adapters.\n");
        std::printf("\t'resolve_hostname' | 'rh':\tTo resolve hostname into an IP address.\n");
        std::printf("\ttest_server | 'ts':\tTo run a test server.\n");
        std::printf("\t'test_client' | 'tc':\tTo run a test client.\n");
        std::printf("\t'windows_tests' | 'wt':\tTo test windows basics on networking.\n");
    }
    
    int index;
    for (index = 1; index < len; index++) {
        
        if (string_functions::same_string(std::string(args[index]), "list_adapters") or string_functions::same_string(std::string(args[index]), "la")) {
            std::printf("Printing adapters for this machine:\n");
            list_machine_adapters();
        }

        else if (string_functions::same_string(std::string(args[index]), "resolve_host") or string_functions::same_string(std::string(args[index]), "rh")) {
            std::printf("Resolving hostname:\n");
            resolve_hostname();
        }

        else if (string_functions::same_string(std::string(args[index]), "resolve_host_name") or string_functions::same_string(std::string(args[index]), "rhn")) {
            std::printf("Resolving hostname name:\n");
            resolve_hostname_name();
        }

        else if (string_functions::same_string(args[index], "test_host") or string_functions::same_string(args[index], "th")) {
            std::printf("Testing host:\n");
            test_host();
        }
        
        else if (string_functions::same_string(args[index], "test_server") or string_functions::same_string(args[index], "ts")) {
            std::printf("Running test server:\n");
            test_server();
        }

        else if (string_functions::same_string(args[index], "test_secure_server") or string_functions::same_string(args[index], "tss")) {
            std::printf("Running test secure server:\n");
            test_secure_server();
        }

        else if (string_functions::same_string(args[index], "test_client") or string_functions::same_string(args[index], "tc")) {
            std::printf("Running test client:\n");
            test_client();
        }

        else if (string_functions::same_string(args[index], "test_secure_client") or string_functions::same_string(args[index], "tsc")) {
            std::printf("Running test secure client:\n");
            test_secure_client();
        }

        else if (string_functions::same_string(args[index], "windows_tests") or string_functions::same_string(args[index], "wt")) {
            std::printf("Running windows tests:\n");
            windows_tests();
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
    std::string host = string_functions::get_input("Hostname : ");
    std::vector<std::string> addresses = networking::resolve_hostname(host);
    std::cout << host << ":" << std::endl;
    unsigned long index;
    for (index = 0; index < addresses.size(); index++) {
        std::cout << "\t" << addresses[index] << std::endl;
    }
}

void resolve_hostname_name() {
    std::string host = string_functions::get_input("Hostname : ");
    std::vector<std::string> addresses = networking::resolve_hostname(host, DEFAULT_PORT, true);
    std::cout << host << ":" << std::endl;
    unsigned long index;
    for (index = 0; index < addresses.size(); index++) {
        std::cout << "\t" << addresses[index] << std::endl;
    }
}

void test_host() {
    
    networking::initialize_network();

    try {

        // For IP4
        // .retrieve_hostname({networking::network_address_families::rel_adapter}, {networking::network_address_families::ip_version4_address_family});

        // For IP6
        // .retrieve_hostname({networking::network_address_families::rel_adapter}, {networking::network_address_families::ip_version6_address_family});
        
        std::cout << "host server" << std::endl;
        networking::network_structures::host host_server;


        host_server.port(connection_port).retrieve_hostname();
        socket_type before_socket = host_server.get_socket();
        std::cout << (not valid_socket(before_socket) ? 
                    "\tBefore socket is correctly not a valid socket" : 
                        "\tBefore socket is incorrectly a valid socket") << std::endl;

    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Exception \"" << except.exception_type() << "\" caught" << std::endl;
        std::cerr << "Exception message \"" << except.msg() << "\"" << std::endl;
    }


    try {

        std::cout << "host client" << std::endl;
        networking::network_structures::host host_client("", DEFAULT_PORT, true, false);

        host_client.port(connection_port).retrieve_hostname();

        std::cout << "Creating test_new host" << std::endl;
        networking::network_structures::host test_new(host_client);

        

    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Exception \"" << except.exception_type() << "\" caught" << std::endl;
        std::cerr << "Exception message \"" << except.msg() << "\"" << std::endl;
    }

    networking::uninitialize_network();
}

void test_server() {
    // std::cout << UNDER_CONSTRUCTION << std::endl;
    
    try {
        networking::network_structures::tcp_server server;
        std::cout << "Successfully created a tcp_server object" << std::endl;
    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Caught exception " << except.exception_type() << std::endl << std::endl;
    }
}

void test_secure_server() {
    std::cout << UNDER_CONSTRUCTION << std::endl;
}

void test_client() {
    std::cout << UNDER_CONSTRUCTION << std::endl;
}

void test_secure_client() {
    std::cout << UNDER_CONSTRUCTION << std::endl;
}

void windows_tests() {

    if (networking::initialize_network()) {
        std::printf("Successfully initialized entwork.\n");
    }

    else {
        std::printf("Failed to initialize network.\n");
    }

    if (networking::uninitialize_network()) {
        std::printf("Successfully uninitialize network.\n");
    }
    else {
        std::printf("Failed to uninitialize network.\n");
    }
}