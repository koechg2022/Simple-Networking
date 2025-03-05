
#include "../libs/networking.h++"
#include "../libs/misc_functions.h++"
#include "included.h++"



// const std::string UNDER_CONSTRUCTION = "UNDER CONSTRUCTION";
const std::string connection_port = "5500";


void list_machine_adapters();

void resolve_hostname();

void test_server();

void test_client();

int main(int len, char** args) {

    int index;
    // std::printf("There are %d arguments:\n", len - 1);
    if (len <= 1) {
        std::printf("Help. This is for testing the networking library. Use one of the following arguments to test the library:\n");
        std::printf("\t'list_machine_adapters()' | 'la':\tTo see all the current machine's adapters.\n");
        std::printf("\t'resolve_hostname()' | 'rh':\tTo resolve hostname into an IP address.\n");
    }
    for (index = 1; index < len; index++) {
        std::printf("\t%d.) %s\n", index, args[index]);
        if (string_functions::same_string(std::string(args[index]), "list_adapters") or string_functions::same_string(std::string(args[index]), "la")) {
            list_machine_adapters();
        }

        else if (string_functions::same_string(std::string(args[index]), "resolve_host") or string_functions::same_string(std::string(args[index]), "rh")) {
            resolve_hostname();
        }

        else if (string_functions::same_string(args[index], "test_server") or string_functions::same_string(args[index], "ts")) {
            test_server();
        }

        else if (string_functions::same_string(args[index], "test_client") or string_functions::same_string(args[index], "tc")) {
            test_client();
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

    networking::network_structures::tcp_server server("", 
                                                    connection_port,
                                                        10, 
                                                            0, 
                                                                100000, 
                                                                    true, 
                                                                        true);
    
    if (server.start()) {
        std::printf("Server is listening...\n");
        std::cout << "Connect to the server using:" << std::endl;
        std::cout << "\t" << server.host_name() << " : " << server.port_value() << std::endl;
        std::set<networking::network_structures::connected_host::client> clients;
        networking::network_structures::connected_host::client new_client;
        char msg[kilo_byte];
        ssize_t msg_len;
        std::string msg_string;
        int bytes;
        
        std::memset(msg, 0, kilo_byte);

        while (server) {
            new_client = server.new_client();
            
            if (valid_socket(new_client.connected_socket)) {

                bytes = SSL_read(new_client.secure_socket, msg, kilo_byte);

                if (bytes < 1) {
                    std::fprintf(stderr, "Failed to accept a message from the new client.\n");
                }
                else {
                    std::printf("Message from New Client:\n\n%.*s\n", bytes, msg);
                    std::printf("----------------------------------------\n");
                }

                msg_string = 
                        "HTTP/1.1 200 OK\r\n"
                        "Connection: close\r\n"
                        "Content-Type: text/plain\r\n"
                        "Local time is: " + misc_functions::get_current_time() + 
                        "\r\n";
                bytes = SSL_write(new_client.secure_socket, msg_string.c_str(), msg_string.length());
                if (bytes < 1) {
                    std::fprintf(stderr, "Failed to send %lu bytes. Only sent %d bytes.\n", msg_string.length(), bytes);
                    server.close_connection(new_client.connected_socket);
                }
                else {
                    std::printf("Successfully sent %d bytes out of %lu bytes.\n", bytes, msg_string.length());
                }
            }

            // New connected have been accounted for
            // Are there any new messages from the clients?
            clients = server.get_clients();
            for (auto client = clients.begin(); client NOT clients.end(); client++) {
                const std::string now = misc_functions::get_current_time();
                std::memset(msg, 0, kilo_byte);
                msg_len = recv(client->connected_socket, msg, kilo_byte, 0);
                if (msg_len > 0) {
                    msg_string = std::string(msg);
                    std::cout << client->hostname << "(" << now << ") : " << std::endl;
                    std::cout << "\"" << msg_string << "\"" << std::endl;
                    continue;
                }
                server.close_connection(client->connected_socket);
            }

            // Control the server from the command line.
            if (string_functions::has_keyboard_input()) {
                msg_string = string_functions::get_input();
                
                
                if (string_functions::same_string(msg_string, "exit()") or string_functions::same_string(msg_string, "exit")) {
                    server.close_server();
                }

                else if (string_functions::same_string(msg_string, "list_connected_machines()") or string_functions::same_string(msg_string, "lcm")) {
                    clients = server.get_all_clients();
                    if (clients.empty()) {
                        std::cout << "No clients connected to this server..." << std::endl;
                    }
                    else {
                        for (auto client = clients.begin(); client NOT clients.end(); client++) {
                            std::cout << client->hostname << ":" << std::endl;
                            std::cout << "\tConnection socket : " << client->connected_socket << std::endl;
                            std::cout << "\tPort : " << client->portvalue << std::endl;
                        }
                    }
                }

                else if (string_functions::same_string(msg_string, "broadcast()") or string_functions::same_string(msg_string, "brdcst")) {
                    
                    msg_string = string_functions::get_input("Message to broadcast: ");
                    clients = server.get_all_clients();
                    ssize_t len;
                    for (auto client = clients.begin(); client NOT clients.end(); client++) {
                        len = send(client->connected_socket, msg_string.c_str(), msg_string.length(), 0);
                        if (len < 1) {
                            std::cerr << "Error sending message to client \"" << client->hostname << "\"" << std::endl;
                            server.close_connection(client->connected_socket);
                            continue;
                        }
                        if ((unsigned long) len == msg_string.length()) {
                            std::cout << "Successfully sent message to client \"" << client->hostname << "\"" << std::endl;
                        }
                        else {
                            std::cerr << "Failed to send complete message to client \"" << client->hostname << "\"" << std::endl << "Only sent " << len << " bytes of " << msg_string.length() << " bytes." << std::endl;
                        }
                    }
                }

                else if (string_functions::same_string(msg_string, "message_client()") or string_functions::same_string(msg_string, "msgc")) {
                    
                    networking::network_structures::connected_host::client the_client;
                    the_client.connected_socket = invalid_socket;
                    the_client.hostname = the_client.portvalue = "";
                    clients = server.get_all_clients();

                    for (auto client = clients.begin(); client NOT clients.end(); client++) {
                        std::cout << client->hostname << std::endl;
                        std::cout << "\t" << client->portvalue << std::endl;
                        std::cout << "\t" << client->connected_socket << std::endl;
                        std::cout << "--------------------------------------------------------" << std::endl;
                    }
                    msg_string = string_functions::get_input("Client : ");

                    // socket or port
                    if (string_functions::all_numbers(msg_string.c_str())) {
                        // socket or port
                        #if defined(unix_os)
                            socket_type the_socket = std::stoi(msg_string);
                        #else
                            socket_type the_socket = std::stoull(msg_string);
                        #endif

                        while (not valid_socket(the_client.connected_socket)) {
                            for (auto client = clients.begin(); client NOT clients.end(); client++) {
                                if (string_functions::same_string(msg_string, client->portvalue) or the_socket == client->connected_socket) {
                                    the_client = *client;
                                    break;
                                }
                            }

                            if (not valid_socket(the_client.connected_socket)) {
                                clients = server.get_all_clients();
                                for (auto client = clients.begin(); client NOT clients.end(); client++) {
                                    std::cout << client->hostname << std::endl;
                                    std::cout << "\t" << client->portvalue << std::endl;
                                    std::cout << "\t" << client->connected_socket << std::endl;
                                    std::cout << "--------------------------------------------------------" << std::endl;
                                }
                                msg_string = string_functions::get_input("Client : ");
                            }
                        }
                    }

                    // hostname
                    else if (networking::is_ipstring(msg_string, true) or 
                                networking::is_ipstring(msg_string, false)) {
                        while (not valid_socket(the_client.connected_socket)) {
                            
                            for (auto client = clients.begin(); client NOT clients.end(); client++) {
                                if (string_functions::same_string(msg_string, client->hostname)) {
                                    the_client = *client;
                                    break;
                                }
                            }

                            if (not valid_socket(the_client.connected_socket)) {
                                clients = server.get_all_clients();
                                for (auto client = clients.begin(); client NOT clients.end(); client++) {
                                    std::cout << client->hostname << std::endl;
                                    std::cout << "\t" << client->portvalue << std::endl;
                                    std::cout << "\t" << client->connected_socket << std::endl;
                                    std::cout << "--------------------------------------------------------" << std::endl;
                                }
                                msg_string = string_functions::get_input("Client : ");
                            }
                        }
                    }
                    
                    // Unrecotnized client passed in
                    else {
                        std::cerr << "Unrecognized client passed in " << msg_string << std::endl;
                        continue;
                    }
                    msg_string = string_functions::get_input("Message to send : ");
                    msg_len = send(the_client.connected_socket, msg_string.c_str(), msg_string.length(), 0);
                    if (msg_len < 1) {
                        std::cerr << "Error occurred while trying to send message." << std::endl;
                        server.close_connection(the_client.connected_socket);
                        continue;
                    }

                    std::cout << "Successfully sent " << msg_len << " bytes out of " << msg_string.length() << " bytes" << std::endl;
                }

                else {
                    std::cout << "Unrecognized command " << msg_string << std::endl;
                    std::cout << "Use the recognized commands:" << std::endl;
                    std::cout << "\texit()/exit to close the server" << std::endl;
                    std::cout << "\tlist_connected_machines()/lcm to list all the clients that are connected to the server" << std::endl;
                    std::cout << "\tbroadcast()/brdcst to send a message to all connected clients" << std::endl;
                    std::cout << "\tmessage_client()/msgc to message a specific client only" << std::endl;
                }

            }

        }
        std::printf("Server is disconnected...\n");
    }
}

void test_client() {

    networking::network_structures::tcp_client client(string_functions::get_input("Enter host to connect to: "), connection_port);

    if (not client.connect()) {
        std::fprintf(stderr, "Failed to connect to the remote host. Error '%d'\n", get_socket_error());
        return;
    }

    std::printf("Connected to '%s'.\n", client.host_name().c_str());

    std::string message;
    networking::network_structures::connected_host::server server_info;
    char message_buffer[kilo_byte];
    int bytes;
    std::memset(message_buffer, 0, kilo_byte);

    while (client) {
        
        
        if (client.server_has_message()) {
            std::memset(message_buffer, 0, kilo_byte);
            bytes = (client.secure_host()) ? 
                                SSL_read(client.get_secure_connection_socket(), message_buffer, kilo_byte) : 
                                        recv(client.get_connection_socket(), message_buffer, kilo_byte, 0);
            if ((client.secure_host() and bytes <= 0 )
                            or 
                (not client.secure_host() and bytes < 1)) {
                std::printf("Connection closed.\n");
                client.disconnect();
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