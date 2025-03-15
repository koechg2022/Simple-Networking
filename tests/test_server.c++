
#include "headers"
#include "networking"
#include "string_functions"




bool secure;



const std::string 
                  // For file itself:
                  LIST_ADAPTERS = "list_adapters", LIST_ADAPTERS_ = "la",
                  RESOLVE_HOST = "resolve_host", RESOLVE_HOST_ = "rh",
                  RESOLVE_HOST_NAME = "resolve_host_name", RESOLVE_HOST_NAME_ = "rhn",
                  TEST_HOST = "test_host", TEST_HOST_ = "th",
                  TEST_SERVER = "test_server", TEST_SERVER_ = "ts",
                  TEST_SECURE_SERVER = "test_secure_server", TEST_SECURE_SERVER_ = "tss",
                  TEST_CLIENT = "test_client", TEST_CLIENT_ = "tc",
                  TEST_SECURE_CLIENT = "test_secure_client", TEST_SECURE_CLIENT_ = "tsc",
                  TEST_WINDOWS = "test_windows", TEST_WINDOWS_ = "tw",
                  TEST_WEB_CLIENT = "test_web_client", TEST_WEB_CLIENT_ = "twc",
                  
                  // For server/clients
                  EXIT = "exit()", EXIT_ = "exit",
                  LIST_CLIENTS = "list clients", LIST_CLIENTS_ = "lc",
                  BROADCAST = "broadcast", BROADCAST_ = "brdcst",
                  MESSAGE_CLIENT = "message client", MESSAGE_CLIENT_ = "mc",
                  DISCONNECT_CLIENT = "disconnect client", DISCONNECT_CLIENT_ = "dc",
                  MESSAGE_SERVER = "message server", MESSAGE_SERVER_ = "ms",
                  CONNECTION_INFO = "connection information", CONNECTION_INFO_ = "ci",
                  
                  
                  // For URL parts
                  PROTOCOL = "PROTOCOL", HOSTNAME = "HOSTNAME",
                  PORT = "PORT", PATH = "PATH", HASH = "HASH";
                  



// For running file
std::unordered_map<std::string, std::string> test_args_caps = {
    {LIST_ADAPTERS, LIST_ADAPTERS},
    {RESOLVE_HOST, RESOLVE_HOST},
    {RESOLVE_HOST_NAME, RESOLVE_HOST_NAME},
    {TEST_HOST, TEST_HOST},
    {TEST_SERVER, TEST_SERVER},
    {TEST_CLIENT, TEST_CLIENT},
    {TEST_SECURE_SERVER, TEST_SECURE_SERVER},
    {TEST_SECURE_CLIENT, TEST_SECURE_CLIENT},
    {TEST_WINDOWS, TEST_WINDOWS},
    {TEST_WEB_CLIENT, TEST_WEB_CLIENT}
};


std::unordered_map<std::string, std::string> test_args_lower = {
    {LIST_ADAPTERS, LIST_ADAPTERS_},
    {RESOLVE_HOST, RESOLVE_HOST_},
    {RESOLVE_HOST_NAME, RESOLVE_HOST_NAME_},
    {TEST_HOST, TEST_HOST_},
    {TEST_SERVER, TEST_SERVER_},
    {TEST_CLIENT, TEST_CLIENT_},
    {TEST_SECURE_SERVER, TEST_SECURE_SERVER_},
    {TEST_SECURE_CLIENT, TEST_SECURE_CLIENT_},
    {TEST_WINDOWS, TEST_WINDOWS_},
    {TEST_WEB_CLIENT, TEST_WEB_CLIENT_}
};




// For running server
std::unordered_map<std::string, std::string> server_args_caps = {
    {EXIT, EXIT},
    {BROADCAST, BROADCAST},
    {LIST_CLIENTS, LIST_CLIENTS},
    {MESSAGE_CLIENT, MESSAGE_CLIENT},
    {DISCONNECT_CLIENT, DISCONNECT_CLIENT}
};

// For running server too
std::unordered_map<std::string, std::string> server_args_lower = {
    {EXIT, EXIT_},
    {BROADCAST, BROADCAST_},
    {LIST_CLIENTS, LIST_CLIENTS_},
    {MESSAGE_CLIENT, MESSAGE_CLIENT_},
    {DISCONNECT_CLIENT, DISCONNECT_CLIENT_}
};



// For running client
std::unordered_map<std::string, std::string> client_args_caps = {
    {EXIT, EXIT},
    {CONNECTION_INFO, CONNECTION_INFO},
    {MESSAGE_SERVER, MESSAGE_SERVER}
};

// For running server too
std::unordered_map<std::string, std::string> client_args_lower = {
    {EXIT, EXIT_},
    {CONNECTION_INFO, CONNECTION_INFO_},
    {MESSAGE_SERVER, MESSAGE_SERVER_}
};



const std::string UNDER_CONSTRUCTION = "UNDER CONSTRUCTION";
const std::string connection_port = "5500";
const std::string default_url = "example.com";


std::unordered_map<std::string, std::string> parse_url(const std::string url = default_url, 
            const std::unordered_map<std::string, std::string> default_values = {
                {PROTOCOL, "HTTP"},
                {HOSTNAME, default_url},
                {PORT, "443"},
                {PATH, "/"},
                {HASH, ""}
            });

void list_machine_adapters();

void resolve_hostname();

void resolve_hostname_name();

void test_host();

void test_server();

void test_secure_server();

void test_client();

void test_secure_client();

void windows_tests();

void test_web_client();

void print_socket_configs(socket_type the_socket);

int main(int len, char** args) {

    
    if (len <= 1) {
        std::printf("Help. This is for testing the networking library. Use one of the following arguments to test the library:\n");
        for (const auto& arg : test_args_caps) {
            std::cout << "\t\"" << arg.second << "\"" << std::endl;
        }
    }
    
    int index;
    for (index = 1; index < len; index++) {
        
        if (string_functions::same_string(std::string(args[index]), test_args_caps[LIST_ADAPTERS]) or string_functions::same_string(std::string(args[index]), test_args_lower[LIST_ADAPTERS])) {
            list_machine_adapters();
        }

        else if (string_functions::same_string(std::string(args[index]), test_args_caps[RESOLVE_HOST]) or string_functions::same_string(std::string(args[index]), test_args_lower[RESOLVE_HOST])) {
            resolve_hostname();
        }

        else if (string_functions::same_string(std::string(args[index]), test_args_caps[RESOLVE_HOST_NAME]) or string_functions::same_string(std::string(args[index]), test_args_lower[RESOLVE_HOST_NAME])) {
            resolve_hostname_name();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_HOST]) or string_functions::same_string(args[index], test_args_lower[TEST_HOST])) {
            test_host();
        }
        
        else if (string_functions::same_string(args[index], test_args_caps[TEST_SERVER]) or string_functions::same_string(args[index], test_args_lower[TEST_SERVER])) {
            secure = false;
            test_server();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_SECURE_SERVER]) or string_functions::same_string(args[index], test_args_lower[TEST_SECURE_SERVER])) {
            secure = true;
            test_secure_server();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_CLIENT]) or string_functions::same_string(args[index], test_args_lower[TEST_CLIENT])) {
            secure = false;
            test_client();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_SECURE_CLIENT]) or string_functions::same_string(args[index], test_args_lower[TEST_SECURE_CLIENT])) {
            secure = true;
            test_secure_client();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_WINDOWS]) or string_functions::same_string(args[index], test_args_lower[TEST_WINDOWS])) {
            std::printf("Running windows tests:\n");
            windows_tests();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_WEB_CLIENT]) or string_functions::same_string(args[index], test_args_lower[TEST_WEB_CLIENT])) {
            std::cout << "Running test_web_client" << std::endl;
            test_web_client();
        }

        else {
            std::cout << "Unrecognized test \"" << args[index] << "\". Acceptable arguments are:" << std::endl;
            for (const auto& arg : test_args_caps) {
                std::cout << "\t\"" << arg.second << "\"" << std::endl;
            }
        }
    }

    return 0;
}


std::unordered_map<std::string, std::string> parse_url(const std::string url, const std::unordered_map<std::string, std::string> default_values) {
    std::unordered_map<std::string, std::string> the_answer = default_values;
    
    size_t start = 0, end;
    
    // Protocol
    end = url.find("://");
    if (end != std::string::npos) {
        the_answer[PROTOCOL] = url.substr(start, end);
        start = end + 3;
    }

    // Hostname and Port
    end = url.find_first_of("/#", start);
    std::string host_port = url.substr(start, end - start);
    size_t colon_pos = host_port.find(':');
    if (colon_pos != std::string::npos) {
        the_answer[HOSTNAME] = host_port.substr(0, colon_pos);
        the_answer[PORT] = host_port.substr(colon_pos + 1);
    }
    else {
        the_answer[HOSTNAME] = host_port;
    }

    // Path
    if (end != std::string::npos && url[end] == '/') {
        start = end;
        end = url.find('#', start);
        the_answer[PATH] = url.substr(start, end - start);
    }

    // Hash
    if (end != std::string::npos && url[end] == '#') {
        the_answer[HASH] = url.substr(end + 1);
    }

    return the_answer;
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
        server.port(connection_port);
        
        networking::network_structures::connected_host::client new_client;
        std::vector<networking::network_structures::connected_host::client> clients;
        std::string message;
        const int count = 3 * kilo_byte;
        int bytes;
        char msg[count];

        server.secure(secure).retrieve_hostname().print_on_exceptions(false);
        
        if (not server.run()) {
            std::cerr << "Failed to start server" << std::endl;
        }

        std::cout << "Connect to host with http \"" << server.hostname() << " : " << server.port() << "\"" << std::endl;

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

                if (string_functions::same_string(message, server_args_caps[EXIT]) or string_functions::same_string(message, server_args_lower[EXIT])) {
                    server.close_server();
                }

                else if (string_functions::same_string(message, server_args_caps[LIST_CLIENTS]) or string_functions::same_string(message, server_args_lower[LIST_CLIENTS])) {
                    
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients connected..." << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                    }
                    for (const auto& this_client : clients) {
                        std::cout << "Host : " << 
                                    this_client.hostname << ", Port :" << 
                                    this_client.portvalue << ", Connection time : " <<
                                    this_client.connection_time << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                    }
                }

                else if (string_functions::same_string(message, server_args_caps[BROADCAST]) or string_functions::same_string(message, server_args_lower[BROADCAST])) {
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

                else if (string_functions::same_string(message, server_args_caps[MESSAGE_CLIENT]) or string_functions::same_string(message, server_args_lower[MESSAGE_CLIENT])) {

                    // Print the clients
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients to message" << std::endl;
                    }
                    bytes = 1;
                    for (const auto& this_client : clients) {
                        std::cout << bytes << ".)\t" << this_client.hostname << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                        bytes++;
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

                else if (string_functions::same_string(message, server_args_caps[DISCONNECT_CLIENT]) or string_functions::same_string(message, server_args_lower[DISCONNECT_CLIENT])) {

                    // Print the clients
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients to disconnect" << std::endl;
                    }
                    bytes = 1;
                    for (const auto& this_client : clients) {
                        std::cout << bytes << ".)\t" << this_client.hostname << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                        bytes++;
                    }
                    message = "";
                    new_client = networking::network_structures::connected_host::client();
                    while (message.empty() or not string_functions::same_string(message, "N/A"))  {
                        message = string_functions::get_input("Client to disconnect : ");
                        if (string_functions::all_numbers(message.c_str())) {
                            if (std::stoul(message) == 0) {
                                std::cout << "Cannot select \"0\" client..." << std::endl;
                                message = "N/A";
                                // break;
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
                        server.disconnect_client(new_client, true, true);
                        clients = server.all_clients();
                        bytes = 0;
                        for (const auto& this_client : clients) {
                            if (this_client == new_client) {
                                bytes = 1;
                                break;
                            }
                        }
                        if (not bytes) {
                            std::cout << "Successfully disconnected client \"" << new_client.hostname << "\"" << std::endl;
                            continue;
                        }
                        std::cout << "Did not disconnected client \"" << new_client.hostname << "\"" << std::endl;
                    }
                }

                else {
                    std::cerr << "Unrecognized input : \"" << message << "\". Acceptable server arguments are:" << std::endl;
                    for (const auto& arg : server_args_caps) {
                        std::cout << "\t\"" << arg.second << "\"" << std::endl;
                    }
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


    try {

        networking::network_structures::tcp_server server;
        
        
        server.key("../files/key.pem").
            cert("../files/cert.pem").
            retrieve_hostname().port(connection_port).
            print_on_exceptions(false);
        
        server.secure(true);

        networking::network_structures::connected_host::client new_client;
        std::vector<networking::network_structures::connected_host::client> clients;
        
        std::string message;
        const int count = 3 * kilo_byte;
        int bytes;
        char msg[count];

        if (not server.run()) {
            return;
        }

        std::cout << "Connect to host with https \"" << server.hostname() << " : " << server.port() << "\"" << std::endl;

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

                if (string_functions::same_string(message, server_args_caps[EXIT]) or string_functions::same_string(message, server_args_lower[EXIT])) {
                    server.close_server();
                }

                else if (string_functions::same_string(message, server_args_caps[LIST_CLIENTS]) or string_functions::same_string(message, server_args_lower[LIST_CLIENTS])) {
                    
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients connected..." << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                    }
                    for (const auto& this_client : clients) {
                        std::cout << "Host : " << 
                                    this_client.hostname << ", Port :" << 
                                    this_client.portvalue << ", Connection time : " <<
                                    this_client.connection_time << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                    }
                }

                else if (string_functions::same_string(message, server_args_caps[BROADCAST]) or string_functions::same_string(message, server_args_lower[BROADCAST])) {
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

                else if (string_functions::same_string(message, server_args_caps[MESSAGE_CLIENT]) or string_functions::same_string(message, server_args_lower[MESSAGE_CLIENT])) {

                    // Print the clients
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients to message" << std::endl;
                    }
                    bytes = 1;
                    for (const auto& this_client : clients) {
                        std::cout << bytes << ".)\t" << this_client.hostname << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                        bytes++;
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

                else if (string_functions::same_string(message, server_args_caps[DISCONNECT_CLIENT]) or string_functions::same_string(message, server_args_lower[DISCONNECT_CLIENT])) {

                    // Print the clients
                    clients = server.all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients to disconnect" << std::endl;
                    }
                    bytes = 1;
                    for (const auto& this_client : clients) {
                        std::cout << bytes << ".)\t" << this_client.hostname << std::endl;
                        std::cout << "------------------------------------------------" << std::endl;
                        bytes++;
                    }
                    message = "";
                    new_client = networking::network_structures::connected_host::client();
                    while (message.empty() or not string_functions::same_string(message, "N/A"))  {
                        message = string_functions::get_input("Client to disconnect : ");
                        if (string_functions::all_numbers(message.c_str())) {
                            if (std::stoul(message) == 0) {
                                std::cout << "Cannot select \"0\" client..." << std::endl;
                                message = "N/A";
                                // break;
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
                        server.disconnect_client(new_client, true, true);
                        clients = server.all_clients();
                        bytes = 0;
                        for (const auto& this_client : clients) {
                            if (this_client == new_client) {
                                bytes = 1;
                                break;
                            }
                        }
                        if (not bytes) {
                            std::cout << "Successfully disconnected client \"" << new_client.hostname << "\"" << std::endl;
                            continue;
                        }
                        std::cout << "Did not disconnected client \"" << new_client.hostname << "\"" << std::endl;
                    }
                }

                else {
                    std::cerr << "Unrecognized input : \"" << message << "\". Acceptable server arguments are:" << std::endl;
                    for (const auto& arg : server_args_caps) {
                        std::cout << "\t\"" << arg.second << "\"" << std::endl;
                    }
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
    networking::network_structures::tcp_client client(string_functions::get_input("Host to connect to : "));
    client.port(connection_port);
    client.secure(false);
    client.blocking(false);
    std::cout << "Successfully creates client object" << std::endl;

    if (not client.start()) {
        std::cerr << "Failed to start client" << std::endl;
        return;
    }

    std::cout << "Successfully created connection" << std::endl;
    
    std::cout << "Done. now closing client..." << std::endl;

}

void test_secure_client() {
    
    
    networking::network_structures::tcp_client client(string_functions::get_input("Host to connect to : "));
    
    
    std::cout << "Successfully created client object" << std::endl;
    
    client.port(connection_port);
    client.secure(true);
    client.blocking(false);

    if (not client.start(false)) {
        std::cerr << "Failed to start client connection" << std::endl;
        return;
    }
    
    std::cout << "Successfully created the connection" << std::endl;

    auto start = std::chrono::steady_clock::now();
    while (client and (std::chrono::steady_clock::now() - start < std::chrono::duration<int>(3))) {

        if (client.message()) {
            std::cout << "There is a message for the client..." << std::endl;
        }
    }

    std::cout << "Done. Now closing client..." << std::endl;

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

void test_web_client() {

    std::string url = string_functions::get_input("URL : ");

    if (url.empty()) {
        url = "example.com";
    }

    // Parse the url
    std::unordered_map<std::string, std::string> url_parsed = parse_url(url);

    // variables for use
    int bytes;
    const int count = 4 * kilo_byte;
    char msg[count];
    const std::string ending = "\r\n";

    for (const auto& attr : url_parsed) {
        std::cout << "\t" << attr.first << " : " << attr.second << std::endl;
    }
    
    if (not url_parsed.contains(HOSTNAME)) {
        std::cerr << "No hostname specified in url" << std::endl;
        return;
    }

    networking::network_structures::tcp_client client(url_parsed[HOSTNAME], url_parsed[PORT]);
    std::cout << "Created client with: " << std::endl;
    std::cout << "Hostname : " << client.hostname() << std::endl;
    std::cout << "Port : " << client.port() << std::endl;
    client.secure(false);

    if (not client.start(false)) {
        std::cerr << "Failed to start client" << std::endl;
        return;
    }

    std::string message = 
            "GET " + url_parsed[PATH] + " HTTP/1.1" + ending +
            "Host: " + url_parsed[HOSTNAME] + ":" +url_parsed[PORT] + ending +
            "Connection: close" + ending +
            "User-Agent honpwc https_get 1.0" + ending +
            ending;

    (client) ? std::cout << "Client is connected..." << std::endl : std::cerr << "Client is not connected..." << std::endl;
    while (client) {

        if (client.message()) {
            bytes = count;
            if (client.message_client(msg, bytes, 0, {-1, -1})) {
                if (not bytes) {
                    std::cout << "Connection closed" << std::endl;
                    client.close_client();
                    continue;
                }

                std::cout << std::string(msg, bytes);
            }
        }

    }
    
}

void print_socket_configs(socket_type the_socket) {
    if (not valid_socket(the_socket)) {
        std::cerr << "The socket is not a valid socket" << std::endl;
        return;
    }



    int option_value;
    socklen_t option_len = sizeof(option_value);

    std::cout << "Socket Configuration Settings:" << std::endl;

    // Check if socket is blocking or non-blocking
    int flags = fcntl(the_socket, F_GETFL, 0);
    std::cout << "Blocking mode: " << ((flags & O_NONBLOCK) ? "Non-blocking" : "Blocking") << std::endl;

    // Get socket type
    if (getsockopt(the_socket, SOL_SOCKET, SO_TYPE, &option_value, &option_len) == 0) {
        std::cout << "Socket type: " << (option_value == SOCK_STREAM ? "SOCK_STREAM (TCP)" : 
                                         option_value == SOCK_DGRAM ? "SOCK_DGRAM (UDP)" : "Unknown") << std::endl;
    }

    // Get receive buffer size
    if (getsockopt(the_socket, SOL_SOCKET, SO_RCVBUF, &option_value, &option_len) == 0) {
        std::cout << "Receive buffer size: " << option_value << " bytes" << std::endl;
    }

    // Get send buffer size
    if (getsockopt(the_socket, SOL_SOCKET, SO_SNDBUF, &option_value, &option_len) == 0) {
        std::cout << "Send buffer size: " << option_value << " bytes" << std::endl;
    }

    // Check if keep-alive is enabled
    if (getsockopt(the_socket, SOL_SOCKET, SO_KEEPALIVE, &option_value, &option_len) == 0) {
        std::cout << "Keep-alive: " << (option_value ? "Enabled" : "Disabled") << std::endl;
    }

    // Get reuse address setting
    if (getsockopt(the_socket, SOL_SOCKET, SO_REUSEADDR, &option_value, &option_len) == 0) {
        std::cout << "Reuse address: " << (option_value ? "Enabled" : "Disabled") << std::endl;
    }

    // Get linger setting
    struct linger linger_opt;
    option_len = sizeof(linger_opt);
    if (getsockopt(the_socket, SOL_SOCKET, SO_LINGER, &linger_opt, &option_len) == 0) {
        std::cout << "Linger: " << (linger_opt.l_onoff ? "On" : "Off");
        if (linger_opt.l_onoff) {
            std::cout << ", timeout: " << linger_opt.l_linger << " seconds";
        }
        std::cout << std::endl;
    }

    // Additional settings can be added here as needed


}