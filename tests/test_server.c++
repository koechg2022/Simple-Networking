
#include "headers"
#include "included"
#include "networking"
#include "string_functions"



// const std::string UNDER_CONSTRUCTION = "UNDER CONSTRUCTION";
const std::string connection_port = "5500";


void list_machine_adapters();

void resolve_hostname();

void test_server();

void test_secure_server();

void test_client();

void test_secure_client();

void windows_tests();

int main(int len, char** args) {

    int index;
    // std::printf("There are %d arguments:\n", len - 1);
    if (len <= 1) {
        std::printf("Help. This is for testing the networking library. Use one of the following arguments to test the library:\n");
        std::printf("\t'list_machine_adapters' | 'la':\tTo see all the current machine's adapters.\n");
        std::printf("\t'resolve_hostname' | 'rh':\tTo resolve hostname into an IP address.\n");
        std::printf("\ttest_server | 'ts':\tTo run a test server.\n");
        std::printf("\t'test_client' | 'tc':\tTo run a test client.\n");
        std::printf("\t'windows_tests' | 'wt':\tTo test windows basics on networking.\n");
    }
    for (index = 1; index < len; index++) {
        // std::printf("\t%d.) %s\n", index, args[index]);
        if (string_functions::same_string(std::string(args[index]), "list_adapters") or string_functions::same_string(std::string(args[index]), "la")) {
            std::printf("Printing adapters for this machine:\n");
            list_machine_adapters();
        }

        else if (string_functions::same_string(std::string(args[index]), "resolve_host") or string_functions::same_string(std::string(args[index]), "rh")) {
            std::printf("Resolving hostname:\n");
            resolve_hostname();
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

void test_server() {

    networking::network_structures::tcp_server server("", connection_port);

    if (not server.start()) {
        std::fprintf(stderr, "Failed to start server '%s' on port '%s'\n", server.host_name().c_str(), server.port_value().c_str());
        return;
    }

    char msg[kilo_byte];
    int bytes;
    std::string message;
    networking::network_structures::connected_host::client client;
    std::set<networking::network_structures::connected_host::client> clients;
    std::printf("Server is running on hostname '%s' and port '%s'\n", server.host_name().c_str(), server.port_value().c_str());
    while (server) {
        
        client = server.new_client();

        if (valid_socket(client.connected_socket)) {
            std::printf("New connection from client '%s' on port '%s'\n", client.hostname.c_str(), client.portvalue.c_str());
        }

        clients = server.get_clients();

        if (not clients.empty()) {
            // There are messages from the connected clients
            for (auto this_client = clients.begin(); this_client != clients.end(); this_client++) {
                bytes = (server.secure_host()) ? 
                        SSL_read(this_client->secure_socket, msg, kilo_byte) : 
                            recv(this_client->connected_socket, msg, kilo_byte, 0);

                if ((server.secure_host() and bytes <= 0) or (not server.secure_host() and bytes < 1)) {
                    std::printf("Connection closed by client '%s'\n", this_client->hostname.c_str());
                    server.close_connection(this_client->hostname, this_client->portvalue);
                }
                else {
                    std::printf("Message from '%s' (%s) : \n%.*s\n\n", this_client->hostname.c_str(), misc_functions::get_current_time().c_str(), (int) bytes, msg);
                }

            }
            clients.clear();
        }

        if (string_functions::has_keyboard_input()) {
            // There is keyboard input from this machine's user
            message = string_functions::get_input();

            if (string_functions::same_string(message, "exit()") or string_functions::same_string(message, "exit")) {
                server.close_server();
            }

            else if (string_functions::same_string(message, "broadcast()") or string_functions::same_string(message, "brdcst")) {
                
                clients = server.get_all_clients();

                if (clients.empty()) {
                    std::printf("No clients to send a message to.\n");
                    continue;
                }

                message = string_functions::get_input("Message to broadcast: ");

                for (auto this_client = clients.begin(); this_client != clients.end(); this_client++) {
                    bytes = (server.secure_host()) ? 
                                SSL_write(this_client->secure_socket, message.c_str(), message.length()) : 
                                    send(this_client->connected_socket, message.c_str(), message.length(), 0);

                    if ((server.secure_host() and bytes <= 0) or (not server.secure_host() and bytes < 1)) {
                        std::printf("Failed to send a message to '%s'.\n", this_client->hostname.c_str());
                        server.close_connection(this_client->hostname, this_client->portvalue);
                        continue;
                    }
                }
            }

            else if (string_functions::same_string(message, "list_clients()") or string_functions::same_string(message, "lc")) {
                clients = server.get_all_clients();
                
                if (clients.empty()) {
                    std::printf("No clients to message.\n");
                    continue;
                }
                bytes = 1;
                for (auto this_client = clients.begin(); this_client != clients.end(); this_client++, bytes++) {
                    std::printf("%d.)\t%s\n", bytes, this_client->hostname.c_str());
                }
            }

            else if (string_functions::same_string(message, "message_client()") or string_functions::same_string(message, "mc")) {
                clients = server.get_all_clients();
                
                if (clients.empty()) {
                    std::printf("No clients to message.\n");
                    continue;
                }


                // message = string_functions::get_input("Client to message (enter client name, not number. 'N/A' to cancel message): ");

                client.hostname = "";
                while (client.hostname.empty()) {

                    bytes = 1;
                    for (auto this_client = clients.begin(); this_client != clients.end(); this_client++, bytes++) {
                        std::printf("%d.)\t%s\n", bytes, this_client->hostname.c_str());
                    }

                    message = string_functions::get_input("Client to message (enter client name, not number. 'N/A' to cancel message): ");

                    if (string_functions::same_string(message, "N/A")) {
                        client.hostname = "";
                        break;
                    }

                    for (auto this_client = clients.begin(); this_client != clients.end(); this_client++) {
                        if (string_functions::same_string(message, this_client->hostname)) {
                            client = *this_client;
                            goto loop_exit;
                        }
                    }

                }

                loop_exit:
                if (client.hostname.empty()) {
                    continue;
                }

                message = string_functions::get_input("Message to send to " + message + ": ");

                bytes = (server.secure_host()) ? 
                            SSL_write(client.secure_socket, message.c_str(), message.length()) : 
                                send(client.connected_socket, message.c_str(), message.length(), 0);
                if ((server.secure_host() and bytes <= 0) or (not server.secure_host() and bytes < 1)) {
                    std::printf("Failed to send message to '%s'\n", client.hostname.c_str());
                    server.close_connection(client.hostname, client.portvalue);
                    continue;
                }
                
                #if defined(unix_os)
                    std::printf("Successfully sent '%d' bytes of %lu bytes\n", bytes, message.length());
                #else
                    std::printf("Successfully sent '%d' bytes of %zu bytes\n", bytes, message.length());
                #endif
            }

            else {
                std::printf("Unrecognized command '%s'. These are the recogized commands already\n", message.c_str());
                std::printf("\t'exit()' to close the server.\n");
                std::printf("\t'broadcast()' to broadcast a message to all clients.\n");
                std::printf("\t'list_clients()' to list all connected clients.\n");
                std::printf("\t'message_client()' to message a specific client.\n");
            }
        }

    }
}

void test_secure_server() {
    networking::network_structures::tcp_server server("", connection_port, 10, 0, 100000, true, true);
    // std::printf("starting server.....................................\n");
    if (not server.start()) {
        std::fprintf(stderr, "Failed to start server '%s' on port '%s'\n", server.host_name().c_str(), server.port_value().c_str());
        return;
    }
    
    char msg[kilo_byte];
    int bytes;
    std::string message;
    networking::network_structures::connected_host::client client;
    std::set<networking::network_structures::connected_host::client> clients;
    std::printf("Server is running on hostname '%s' and port '%s'\n", server.host_name().c_str(), server.port_value().c_str());

    
    while (server) {

        client = server.new_client();

        if (valid_socket(client.connected_socket)) {
            std::printf("New connection from client '%s' on port '%s'\n", client.hostname.c_str(), client.portvalue.c_str());
        }

        clients = server.get_clients();

        if (not clients.empty()) {
            for (auto this_client = clients.begin(); this_client != clients.end(); this_client++) {
                bytes = (server.secure_host()) ? 
                        SSL_read(this_client->secure_socket, msg, kilo_byte) :
                            recv(this_client->connected_socket, msg, kilo_byte, 0);
                if ((server.secure_host() and bytes <= 0) or (not server.secure_host() and bytes < 1)) {
                    std::printf("Connection closed by client. '%s'\n", this_client->hostname.c_str());
                    server.close_connection(this_client->hostname, this_client->portvalue);
                    continue;
                }
                std::printf("Message from '%s' (%s) : \n%.*s\n\n", this_client->hostname.c_str(), misc_functions::get_current_time().c_str(), (int) bytes, msg);
            }
            clients.clear();
        }

        if (string_functions::has_keyboard_input()) {
            // There is keyboard input from this machine's user
            message = string_functions::get_input();

            if (string_functions::same_string(message, "exit()") or string_functions::same_string(message, "exit")) {
                server.close_server();
            }

            else if (string_functions::same_string(message, "broadcast()") or string_functions::same_string(message, "brdcst")) {
                
                clients = server.get_all_clients();

                if (clients.empty()) {
                    std::printf("No clients to send a message to.\n");
                    continue;
                }

                message = string_functions::get_input("Message to broadcast: ");

                for (auto this_client = clients.begin(); this_client != clients.end(); this_client++) {
                    bytes = (server.secure_host()) ? 
                                SSL_write(this_client->secure_socket, message.c_str(), message.length()) : 
                                    send(this_client->connected_socket, message.c_str(), message.length(), 0);

                    if ((server.secure_host() and bytes <= 0) or (not server.secure_host() and bytes < 1)) {
                        std::printf("Failed to send a message to '%s'.\n", this_client->hostname.c_str());
                        server.close_connection(this_client->hostname, this_client->portvalue);
                        continue;
                    }
                }
            }

            else if (string_functions::same_string(message, "list_clients()") or string_functions::same_string(message, "lc")) {
                clients = server.get_all_clients();
                
                if (clients.empty()) {
                    std::printf("No clients to message.\n");
                    continue;
                }
                bytes = 1;
                for (auto this_client = clients.begin(); this_client != clients.end(); this_client++, bytes++) {
                    std::printf("%d.)\t%s\n", bytes, this_client->hostname.c_str());
                }
            }

            else if (string_functions::same_string(message, "message_client()") or string_functions::same_string(message, "mc")) {
                clients = server.get_all_clients();
                
                if (clients.empty()) {
                    std::printf("No clients to message.\n");
                    continue;
                }


                // message = string_functions::get_input("Client to message (enter client name, not number. 'N/A' to cancel message): ");

                client.hostname = "";
                while (client.hostname.empty()) {

                    bytes = 1;
                    for (auto this_client = clients.begin(); this_client != clients.end(); this_client++, bytes++) {
                        std::printf("%d.)\t%s\n", bytes, this_client->hostname.c_str());
                    }

                    message = string_functions::get_input("Client to message (enter client name, not number. 'N/A' to cancel message): ");

                    if (string_functions::same_string(message, "N/A")) {
                        client.hostname = "";
                        break;
                    }

                    for (auto this_client = clients.begin(); this_client != clients.end(); this_client++) {
                        if (string_functions::same_string(message, this_client->hostname)) {
                            client = *this_client;
                            goto loop_exit;
                        }
                    }

                }

                loop_exit:
                if (client.hostname.empty()) {
                    continue;
                }

                message = string_functions::get_input("Message to send to " + message + ": ");

                bytes = (server.secure_host()) ? 
                            SSL_write(client.secure_socket, message.c_str(), message.length()) : 
                                send(client.connected_socket, message.c_str(), message.length(), 0);
                if ((server.secure_host() and bytes <= 0) or (not server.secure_host() and bytes < 1)) {
                    std::printf("Failed to send message to '%s'\n", client.hostname.c_str());
                    server.close_connection(client.hostname, client.portvalue);
                    continue;
                }
                
                #if defined(unix_os)
                    std::printf("Successfully sent '%d' bytes of %lu bytes\n", bytes, message.length());
                #else
                    std::printf("Successfully sent '%d' bytes of %zu bytes\n", bytes, message.length());
                #endif
            }

            else {
                std::printf("Unrecognized command '%s'. These are the recogized commands already\n", message.c_str());
                std::printf("\t'exit()' to close the server.\n");
                std::printf("\t'broadcast()' to broadcast a message to all clients.\n");
                std::printf("\t'list_clients()' to list all connected clients.\n");
                std::printf("\t'message_client()' to message a specific client.\n");
            }
        }
    }
}

void test_client() {

    networking::network_structures::tcp_client client(string_functions::get_input("Enter host to connect to: "), connection_port);

    if (not client.connect_client()) {
        std::fprintf(stderr, "Failed to connect to the remote host. Error '%d'\n", get_socket_error());
        return;
    }

    std::printf("Connected to '%s'.\n", client.host_name().c_str());

    std::string message;
    networking::network_structures::connected_host::server server_info;
    char message_buffer[kilo_byte];
    int bytes, error;
    std::memset(message_buffer, 0, kilo_byte);

    while (client) {
        
        
        if (client.server_has_message()) {
            std::memset(message_buffer, 0, kilo_byte);
            bytes = (client.secure_host()) ? 
                                SSL_read(client.get_secure_connection_socket(), message_buffer, kilo_byte) : 
                                        recv(client.get_connection_socket(), message_buffer, kilo_byte, 0);
            if (bytes < 1) {
                if (client.secure_host()) {
                    error = SSL_get_error(client.get_secure_connection_socket(), bytes);
                    if ((error is SSL_ERROR_WANT_READ) or (SSL_ERROR_WANT_WRITE)) {
                        continue;
                    }
                    std::printf("Connection closed.\n");
                    client.disconnect();
                    continue;
                }
                std::printf("Connection closed.\n");
                client.disconnect();
                continue;
            }
            std::printf("Message from server:\n'%.*s'\n", (int) bytes, message_buffer);
        }

        if (string_functions::has_keyboard_input()) {
            message = string_functions::get_input();

            if (string_functions::same_string(message, "exit()") or string_functions::same_string(message, "exit")) {
                client.disconnect();
            }

            else if (string_functions::same_string(message, "list_connection()") or string_functions::same_string(message, "lc")) {
                server_info = client.get_server_connection();
                std::printf("Connection information:\n");
                std::printf("%s\n", server_info.hostname.c_str());
                std::printf("\tConnection socket : %s\n", std::to_string(server_info.connect_socket).c_str());
                std::printf("\tPort : %s\n", server_info.portvalue.c_str());
            }

            else if (string_functions::same_string(message, "send_message()") or string_functions::same_string(message, "sm")) {
                message = string_functions::get_input("Enter message to send: ");
                bytes = (client.secure_host()) ? 
                                SSL_write(client.get_secure_connection_socket(), message.c_str(), message.length()) : 
                                    send(client.get_connection_socket(), message.c_str(), message.length(), 0);
                if ((bytes <= 0 and client.secure_host()) or (bytes < 1 and not client.secure_host())) {
                    std::printf("Failed to send message to server...\n");
                    client.disconnect();
                    continue;
                }
                std::printf("Sent '%d' bytes of '%d' bytes.\n", (int) bytes, (int) message.length());
            }

            else {
                std::cout << "Unrecognized command '" << message << "'" << std::endl;
                std::cout << "Use the recognized commands:" << std::endl;
                std::cout << "\texit()/exit to close the server" << std::endl;
                std::cout << "\tlist_connecion() to view server connection information" << std::endl;
                std::cout << "\tsend_message() to send a message to the server" << std::endl;
            }
        }

    }
}

void test_secure_client() {
    networking::network_structures::tcp_client client(string_functions::get_input("Enter host to connect to: "), connection_port, 0, 100000, true, true);

    if (not client.connect_client()) {
        std::fprintf(stderr, "Failed to connect to the remote host. Error '%d'\n", get_socket_error());
        return;
    }

    std::printf("Connected to '%s'.\n", client.host_name().c_str());

    std::string message;
    networking::network_structures::connected_host::server server_info;
    char message_buffer[kilo_byte];
    int bytes;
    std::memset(message_buffer, 0, kilo_byte);
    // std::printf("Entering while loop\n");
    while (client) {
        // std::printf("In while loop...\n");
        
        if (client.server_has_message()) {
            std::memset(message_buffer, 0, kilo_byte);
            // bytes = (client.secure_host()) ? 
            //                     SSL_read(client.get_secure_connection_socket(), message_buffer, kilo_byte) : 
            //                             recv(client.get_connection_socket(), message_buffer, kilo_byte, 0);
            bytes = client.receive(message_buffer, kilo_byte);
            if (bytes < 1) {
                if (client) {
                    continue;
                }
                client.disconnect();
                std::printf("Connection closed by server.\n");
                continue;
            }
            std::printf("Message from server:\n'%.*s'\n", (int) bytes, message_buffer);
        }

        // std::printf("Checking if there's keyboard input...\n");
        if (string_functions::has_keyboard_input()) {
            message = string_functions::get_input();

            if (string_functions::same_string(message, "exit()") or string_functions::same_string(message, "exit")) {
                client.disconnect();
            }

            else if (string_functions::same_string(message, "list_connection()") or string_functions::same_string(message, "lc")) {
                server_info = client.get_server_connection();
                std::printf("Connection information:\n");
                std::printf("%s\n", server_info.hostname.c_str());
                std::printf("\tConnection socket : %s\n", std::to_string(server_info.connect_socket).c_str());
                std::printf("\tPort : %s\n", server_info.portvalue.c_str());
            }

            else if (string_functions::same_string(message, "send_message()") or string_functions::same_string(message, "sm")) {
                message = string_functions::get_input("Enter message to send: ");
                bytes = (client.secure_host()) ? 
                                SSL_write(client.get_secure_connection_socket(), message.c_str(), message.length()) : 
                                    send(client.get_connection_socket(), message.c_str(), message.length(), 0);
                if ((bytes <= 0 and client.secure_host()) or (bytes < 1 and not client.secure_host())) {
                    std::printf("Failed to send message to server...\n");
                    client.disconnect();
                    continue;
                }
                std::printf("Sent '%d' bytes of '%d' bytes.\n", (int) bytes, (int) message.length());
            }

            else {
                std::cout << "Unrecognized command '" << message << "'" << std::endl;
                std::cout << "Use the recognized commands:" << std::endl;
                std::cout << "\texit()/exit to close the server" << std::endl;
                std::cout << "\tlist_connecion() to view server connection information" << std::endl;
                std::cout << "\tsend_message() to send a message to the server" << std::endl;
            }
        }

    }
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