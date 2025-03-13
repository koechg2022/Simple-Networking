
#include "headers"
#include "included"
#include "networking"
#include "string_functions"
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
    
    bool secure = false;
    
    networking::network_structures::tcp_server server;
    server.print_exceptions(false).secure(secure);
    networking::network_structures::connected_host::client new_client;
    std::vector<networking::network_structures::connected_host::client> clients;
    std::string message;
    const int count = 3 * kilo_byte;
    int bytes;
    char msg[count];


    server.secure(false);
    server.retrieve_hostname();
    server.print_on_exceptions(false);

    try {
        
        if (not server.run()) {
            std::cerr << "Failed to start server" << std::endl;
        }

        std::cout << "Connect to host with \"" << server.hostname() << " : " << server.port() << "\"" << std::endl;

        while (server) {
            new_client = server.new_client();

            if (valid_socket(new_client.connected_socket)) {
                std::cout << "New connection from \"" << new_client.hostname << "\" at " << new_client.connection_time << std::endl;
            }

            clients = server.clients_with_data();

            // There is/are clients with data?
            for (const auto& this_client : clients) {
                bytes = recv(this_client.connected_socket, msg, count, 0);

                if (bytes < 1) {
                    std::cout << "Unexpected disconnect from \"" << this_client.hostname << "\"" << std::endl;
                    server.disconnect_client(this_client);
                    continue;
                }

                std::cout << "Message from client : " << std::string(msg) << std::endl;
            }

            if (string_functions::has_keyboard_input()) {
                message = string_functions::get_input();

                if (string_functions::same_string(message, "exit()") or string_functions::same_string(message, "exit")) {
                    server.close_server();
                }

                else if (string_functions::same_string(message, "list clients") or string_functions::same_string(message, "lc")) {
                    
                    clients = server.all_clients();
                    for (const auto& this_client : clients) {
                        std::cout << "Host : " << 
                                    this_client.hostname << ", Port :" << 
                                    this_client.portvalue << ", Connection time : " <<
                                    this_client.connection_time << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                    }
                }

                else {
                    std::cerr << "Unrecognized input : \"" << message << "\"" << std::endl;
                }
            }

        }
        
    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Caught exception : " << except.exception_type() << std::endl;
        std::cerr << "Error message \"" << except.msg() << "\"" << std::endl;
    }
    

}

void test_secure_server() {
    bool secure = true;
    std::string message;
    networking::network_structures::tcp_server server("", DEFAULT_PORT, secure, "../files/key.pem", "../files/cert.pem");
    
    try {
        server.retrieve_hostname();
        if (server.hostname().empty()) {
            std::cerr << "Failed to retrieve hostname. Not gonna start server..." << std::endl;
            return;
        }
        std::cout << "Successfully retrieved hostname. Gonna proceed to start server..." << std::endl;
    }

    catch(networking::exceptions::base_exception& except) {
        std::cerr << "Caught exception : " << except.exception_type() << std::endl;
        return;
    }

    try {

        if (not server.secure(secure).secure()) {
            std::cerr << "Server is not secure. Not going to start server." << std::endl;
            return;
        }
        std::cout << "Server is secure. Gonna proceed to start server..." << std::endl;
    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Caught exception : " << except.exception_type() << std::endl;
        return;
    }

    try {

        if (not server.run()) {
            std::cerr << "Server failed to start running. Not gonna start server." << std::endl;
            return;
        }

        std::cout << "Server was successfully started." << std::endl;
    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Caught exception" << except.exception_type() << std::endl;
        return;
    }


    try {

        server.print_exceptions(false);
        networking::network_structures::connected_host::client new_client;
        std::vector<networking::network_structures::connected_host::client> clients;
        
        const int count = 3 * kilo_byte;
        int bytes;
        char msg[count];

        std::cout << "Connect to host with \"" << server.hostname() << " : " << server.port() << "\"" << std::endl;
        // std::cout << "Note, FD_SETSIZE = " << FD_SETSIZE << std::endl;

        while (server) {

            new_client = server.new_client({0, 200000});

            if (valid_socket(new_client.connected_socket)) {
                std::cout << "New connection from \"" << new_client.hostname << "\" at " << new_client.connection_time << std::endl;
            }


            
            if (not (clients = server.clients_with_data()).empty()) {
                for (const auto& client : clients) {
                    bytes = SSL_read(client.secure_socket, msg, count);
                    
                    if (bytes < 1) {
                        std::cout << "Client \"" << client.hostname << "\" disconnected." << std::endl;
                        server.disconnect_client(client);
                        continue;
                    }

                    std::cout << "Message from \"" << client.hostname << "\"" << std::endl;
                    std::cout << std::string(msg, bytes) << std::endl;
                }
            }


            if (string_functions::has_keyboard_input()) {
                message = string_functions::get_input();

                if (string_functions::same_string(message, "exit()") or string_functions::same_string(message, "exit")) {
                    server.close_server();
                }

                else if (string_functions::same_string(message, "list clients") or string_functions::same_string(message, "lc")) {
                    
                    clients = server.all_clients();
                    for (const auto& this_client : clients) {
                        std::cout << "Host : " << 
                                    this_client.hostname << ", Port :" << 
                                    this_client.portvalue << ", Connection time : " <<
                                    this_client.connection_time << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                    }
                }

                else if (string_functions::same_string(message, "broadcast") or string_functions::same_string(message, "brdcst")) {
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients to message..." << std::endl;
                        continue;
                    }

                    message = string_functions::get_input("Message to broadcast : ");
                    if (message.empty()) {
                        continue;
                    }
                    for (const auto& client : clients) {
                        bytes = SSL_write(client.secure_socket, message.c_str(), message.length());

                        if (bytes < 1) {
                            std::cerr << "Failed to send message to \"" << message << "\"" << std::endl;
                            continue;
                        }
                        std::cout << "Sent " << bytes << " out of " << message.length() << " bytes to \"" << client.hostname << "\"" << std::endl;
                    }
                }

                else if (string_functions::same_string(message, "message client") or string_functions::same_string(message, "mc")) {

                    // Print the clients
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients to message" << std::endl;
                    }
                    bytes = 1;
                    for (const auto& this_client : clients) {
                        std::cout << bytes << ".)\t" << this_client.hostname << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                    }
                    message = "";
                    new_client = networking::network_structures::connected_host::client();
                    while (message.empty() or not string_functions::same_string(message, "N/A"))  {
                        message = string_functions::get_input("Client to message : ");
                        if (string_functions::all_numbers(message.c_str())) {
                            if (std::stoul(message) == 0) {
                                std::cout << "Cannot select \"0\" client..." << std::endl;
                                message = "N/A";
                                break;
                            }
                            if (std::stoul(message) - 1 < clients.size()) {
                                new_client = clients[std::stoul(message) - 1];
                                break;
                            }
                        }

                        for (const auto& this_client : clients) {
                            if (string_functions::same_string(this_client.hostname, message)) {
                                new_client = this_client;
                                break;
                            }
                        }

                        if (not new_client.hostname.empty() or string_functions::same_string(message, "N/A")) {
                            break;
                        }

                        std::cout << "Unrecognized host : \"" << message << "\"" << std::endl;
                        message = "";
                    }

                    if (not new_client.hostname.empty()) {
                        message = string_functions::get_input("Message to send : ");
                        bytes = SSL_write(new_client.secure_socket, message.c_str(), message.length());
                        if (bytes < 1) {
                            std::cerr << "Failed to send message to \"" << new_client.hostname << "\"" << std::endl;
                            server.disconnect_client(new_client);
                            continue;
                        }
                        std::cout << "Sent " << bytes << " out of " << message.length() << " to \"" << new_client.hostname << "\"" << std::endl;
                    }

                }

                else {
                    std::cerr << "Unrecognized input : \"" << message << "\"" << std::endl;
                }
            }


        }
    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Exception caught : " << except.exception_type() << std::endl;
        std::cerr << except.msg() << std::endl;
    }

    // std::cout << UNDER_CONSTRUCTION << std::endl;
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