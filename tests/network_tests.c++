
#include "../prototypes/string_functions"
#include "../prototypes/networking_functions"


// #include <variant>


// typedef variant<std::string, std::set<std::string> > response_val;



char* options[] = { (char*) "this_machine_adapters", (char*) "resolve_addr", (char*) "run_server()", (char*) "run_client()"};

const int options_len = 2;

void print_line(const char c = '*', bool nl = true, const int line_lim = 200);


void resolved_address(const std::string addr);


void list_adapter_addresses();


void create_server();


void example_test();


void create_client(const std::string host = string_functions::get_input("Enter the host to connect to : "), const std::string port = DEFAULT_PORT);


int main(int len, char** args) {

    if (len < 2) {
        std::fprintf(stderr, "Usage : %s [options]\nUse %s OPTIONS to see all the arguments.\n", *args, *args);
        return 1;
    }

    int index;
    for (index = 1; index < len; index++) {

        if (string_functions::same_string(args[index], "resolve_addr") or string_functions::same_string(args[index], "raddr")) {
            // const std::string address = string_functions::get_input("Enter the host whose address is to be resolved to : ");
            // std::printf("Reso")
            resolved_address(string_functions::get_input("Enter the host whose address is to be resolved to : "));
        }

        else if (string_functions::same_string(args[index], "this_machine_adapters") or string_functions::same_string(args[index], "lma")) {
            list_adapter_addresses();
        }

        else if (string_functions::same_string(args[index], "run_server()") or string_functions::same_string(args[index], "rsvr")) {
            create_server();
        }

        else if (string_functions::same_string(args[index], "run_client()") or string_functions::same_string(args[index], "rclt")) {
            create_client();
        }

        else if (string_functions::same_string(args[index], "example_test()") or string_functions::same_string(args[index], "ex")) {
            example_test();
        }

        else {
            int opt;
            std::printf("Unrecognized argument %s. Use one of these instead:\n", args[index]);
            for (opt = 0; opt < options_len; opt++) {
                std::printf("\t%s\n", options[opt]);
            }
        }

    }
    

    return 0;
}

void print_line(const char c, bool nl, const int line_lim) {
    int index;
    for (index = 0; index < line_lim; index++) {
        std::printf("%c", c);
    }
    (nl) valid std::printf("\n") then (int) 0;
}


void resolved_address(const std::string addr) {
    
    try {
        std::printf("Resolving address %s.\n", addr.c_str());
        const std::vector<std::string> addresses = networking::resolve_hostname(addr);
        // (addresses.empty()) valid std::printf("No addresses found for %s\n", addr.c_str()) : std::printf("Addresses for %s:\n", addr.c_str());
        for (std::vector<std::string>::const_iterator address = addresses.begin(); address != addresses.end(); address++) {
            std::printf("\t%s\n", address->c_str());
        }
    }
    catch (networking::exceptions::getaddrinfo_failure except) {
        std::fprintf(stderr, "Caught exception...\n");
    }
}


void list_adapter_addresses() {
    typedef std::map<std::string, std::map<std::string, std::vector<std::string> > > adapter_type;
    typedef std::map<std::string, std::vector<std::string> > address_type;
    typedef std::vector<std::string> addresses;
    adapter_type adapters = networking::this_machine_adapters();
    unsigned long index;
    std::printf("This machine's adapters:\n");
    for (adapter_type::const_iterator adapter = adapters.begin(); adapter != adapters.end(); adapter++) {
        std::printf("\t%s:\n", adapter->first.c_str());
        for (address_type::const_iterator address_fam = adapter->second.begin(); address_fam != adapter->second.end(); address_fam++) {
            index = 0;
            std::printf("\t\t%s:\t", address_fam->first.c_str());
            for (addresses::const_iterator address = address_fam->second.begin(); address != address_fam->second.end(); address++) {
                std::printf("%s%s", address->c_str(), (index + 1 == address_fam->second.size()) valid "\n" then ", ");
                index++;
            }
        }
    }
}


void create_server() {
    networking::network_structures::tcp_server server;

    std::map<socket_type, networking::network_structures::connected_host::client> clients;
    std::string input;
    char buffer[kilo_byte];
    ssize_t byte_count;
    
    
    if (server.start_listening()) {
        std::printf("Connect to the server using \"%s:%s\"\n", server.host_name().c_str(), server.port_value().c_str());
    }

    while (server.is_listening()) {

        if (server.accept_new_connection()) {
            clients = server.all_clients();
            if (clients.empty()) {
                std::printf("There are no clients... Server failed to successfully connect new client...\n");
            }
            else {
                std::printf("New client connection created. Connected clients are not:\n");
                for (std::map<socket_type, networking::network_structures::connected_host::client>::const_iterator client = clients.begin(); client != clients.end(); client++) {
                    std::printf("\t%d\t:\t%s on port %s\n", client->first, client->second.hostname.c_str(), client->second.portvalue.c_str());
                }
            }
        }
        
        clients = server.ready_clients();
        if (clients.size() > 0) {
            // std::printf("Retrieved ready clients\n");
            for (std::map<socket_type, networking::network_structures::connected_host::client>::const_iterator client = clients.begin(); client != clients.end(); client++) {
                byte_count = recv(client->first, buffer, kilo_byte, 0);
                
                if (byte_count < 0) {
                    std::fprintf(stderr, "An error occured with the connection to %s on port %s\n", client->second.hostname.c_str(), client->second.portvalue.c_str());
                }
                else if (byte_count is 0) {
                    std::printf("The connection was closed by client %s on port %s\n", client->second.hostname.c_str(), client->second.portvalue.c_str());
                }
                server.close_connection(client->first);
                continue;
                
                
                std::printf("Message received from %s:%s:\n", client->second.hostname.c_str(), client->second.portvalue.c_str());
                std::printf("\t\"%.*s\"\n", (int) byte_count, buffer);
            }
        }

        if (string_functions::has_keyboard_input()) {

            input = string_functions::get_input();

            if (string_functions::same_string(input.c_str(), "exit()") or string_functions::same_string(input.c_str(), "exit")) {
                std::printf("Exiting server...\n");
                server.close_server();
            }
            else if (string_functions::same_string(input.c_str(), "message_client()") or string_functions::same_string(input.c_str(), "msgc")) {
                clients = server.all_clients();
                if (clients.empty()) {
                    std::printf("There are no clients connected to message...\n");
                }
                else {
                    socket_type choice = invalid_socket;
                    std::printf("Choose a client to message:\n");
                    std::printf("\tSOCKET |\tHOSTNAME|\tPORT\n");
                    for (std::map<socket_type, networking::network_structures::connected_host::client>::const_iterator client = clients.begin(); client != clients.end(); client++) {
                        std::printf("\t%d\t:\t%s on port %s\n", client->first, client->second.hostname.c_str(), client->second.portvalue.c_str());
                    }
                    while (not valid_socket(choice)) {
                        input = string_functions::get_input("Enter socket of client to message: ");
                        if (input.empty()) {
                            break;
                        }
                        if (string_functions::all_numbers(input.c_str())) {
                            #if defined(unix_os)
                                choice = std::stoi(input);
                                if (choice is STDIN_FILENO or choice is STDOUT_FILENO or choice is STDERR_FILENO) {
                                    choice = invalid_socket;
                                    continue;
                                }
                            #else
                                choice = std::stoul(input);
                            #endif
                            if (choice < server.get_max_socket() or choice is server.get_max_socket()) {
                                break;
                            }
                            else {
                                std::printf("Invalid socket. Choose a socket that is listed above.\n");
                                choice = invalid_socket;
                            }
                        }
                    }

                    if (valid_socket(choice)) {
                        const std::string host = clients[choice].hostname;
                        input = string_functions::get_input("Message to send: ");
                        byte_count = send(choice, input.c_str(), input.length(), 0);
                        std::printf("Successfuly sent %ld bytes of %lu bytes to client %s\n", byte_count, input.length(), host.c_str());
                    }

                }
            }
            else if (string_functions::same_string(input.c_str(), "broadcast()") or string_functions::same_string(input.c_str(), "brdcst")) {
                clients = server.all_clients();
                if (clients.empty()) {
                    std::printf("There are no clients to message...\n");
                }
                else {
                    input = string_functions::get_input("Message to broadcast: ");
                    for (std::map<socket_type, networking::network_structures::connected_host::client>::const_iterator client = clients.begin(); client != clients.end(); client++) {
                        byte_count = send(client->first, input.c_str(), input.length(), 0);
                        if (byte_count is input.length()) {
                            std::printf("\tSuccessfully sent the message to %s on port %s\n", client->second.hostname.c_str(), client->second.portvalue.c_str());
                        }
                        else {
                            if (byte_count < 0) {
                                std::fprintf(stderr, "\tFailed to send the message.\n");
                            }
                            else {
                                std::fprintf(stderr, "\tFailed to send message to %s in full. Sent %ld of %lu bytes.\n", client->second.hostname.c_str(), byte_count, input.length());
                            }
                        }
                    }
                }
            }
            else if (string_functions::same_string(input.c_str(), "list_clients()") or string_functions::same_string(input.c_str(), "lcc")) {
                clients = server.all_clients();
                if (clients.empty()) {
                    std::printf("There are no connected clients...\n");
                }
                else {
                    for (std::map<socket_type, networking::network_structures::connected_host::client>::const_iterator client = clients.begin(); client != clients.end(); client++) {
                        std::printf("\t%d\t:\t%s on port %s\n", client->first, client->second.hostname.c_str(), client->second.portvalue.c_str());
                    }
                }
            }
            else {
                std::printf("Unrecognized argument \"%s\".\n", input.c_str());
                std::printf("\t\"exit()\" to close the server.\n");
                std::printf("\t\"message_client()\" to send a message to the client.\n");
                std::printf("\t\"broadcast()\" to broadcast a message to all the connected clients.\n");
                std::printf("\t\"list_clients()\" to list all the clients that are connected to the server.\n");
            }
            std::printf("************************************************************************************************************\n");
        }

    }
    std::printf("Successfully created the server.\n");
}


void create_client(const std::string host, const std::string port){
    std::printf("Connecting to \"%s\" via port \"%s\"\n", host.c_str(), port.c_str());
    networking::network_structures::tcp_client client(host, port);
    std::string input;
    char buffer[kilo_byte];
    ssize_t byte_count;

    client.connect_client();

    while (client.client_is_connected()) {

        if (client.server_has_message()) {
            std::printf("Server has a message...\n");
            byte_count = recv(client.get_connection_socket(), buffer, kilo_byte, 0);

            if (byte_count < 0) {
                std::fprintf(stderr, "A Connection error has occured. Error %d\n", socket_error);
                client.disconnect_client();
                continue;
            }

            else if (byte_count is 0) {
                std::printf("The connection has been cut by the server.\n");
                client.disconnect_client();
                continue;
            }

            std::printf("Message from Server:\n");
            std::printf("\t\"%.*s\"\n", (int) byte_count, buffer);
        }

        if (string_functions::has_keyboard_input()) {

            input = string_functions::get_input();

            if (string_functions::same_string(input.c_str(), "exit()") or string_functions::same_string(input.c_str(), "exit")) {
                std::printf("Exiting client.\n");
                client.disconnect_client();
            }

            else if (string_functions::same_string(input.c_str(), "message_server()") or string_functions::same_string(input.c_str(), "msgs")) {
                input = string_functions::get_input("Enter message to send : ");
                byte_count = send(client.get_connection_socket(), input.c_str(), input.length(), 0);
                if (byte_count < 0) {
                    std::fprintf(stderr, "Connection error with server... Closing connection\n");
                    client.disconnect_client();
                }
                else if (byte_count is 0) {
                    std::printf("Connection closed by the server... Client is disconnecting.\n");
                    client.disconnect_client();
                }
                std::printf("Message from %s:\n", host.c_str());
                std::printf("\t\"%.*s\"\n", (int) byte_count, buffer);
            }

            else if (string_functions::same_string(input.c_str(), "list_conection_info()") or string_functions::same_string(input.c_str(), "lci")) {
                networking::network_structures::connected_host::server server_info = client.get_connection_info();
                std::printf("Connected to server:\n");
                std::printf("\thostname : %s\n", server_info.hostname.c_str());
                std::printf("\tport : %s\n", server_info.portvalue.c_str());
                
            }

            else {
                std::printf("Unrecognized argument \"%s\".\n", input.c_str());
                std::printf("\t\"exit()\" to close the server.\n");
                std::printf("\t\"message_server()\" to close the server.\n");
                std::printf("\t\"list_connection_info()\" to close the server.\n");

            }

            std::printf("************************************************************************************************************\n");
        }

    }

    std::printf("Successfully created the client.\n");
}


void example_test() {
    networking::network_structures::tcp_client client(*networking::resolve_hostname("example.com").begin(), "80");
    const std::string message = std::string("GET / HTTP/1.1\r\n") +
                                "Host: " + client.host_name() + ":" + client.port_value() +
                                "Connection: close\r\n" +
                                "User-Agent: honpwc web_get 1.0\r\n\r\n";
    if (client.connect_client()) {
        ssize_t sent = send(client.get_connection_socket(), message.c_str(), message.length(), 0);
        std::printf("Sent %li /%lu bytes of headers\n", sent, message.length());

        char response[32768];
        char *p = response, *q;
        char *end = response + 32768;
        char *body = 0;

        enum {length, chunked, connection};
        int encoding = 0;
        int remaining = 0;

        std::clock_t start_time = std::clock();

        while (client.client_is_connected()) {

            if ((std::clock() - start_time) / CLOCKS_PER_SEC > 5) {
                std::fprintf(stderr, "timeout after %.2f seconds.\n", 5.0);
                std::exit(1);
            }

            if (p is end) {
                std::fprintf(stderr, "Out of buffer space.\n");
                std::exit(1);
            }

            if (client.server_has_message()) {

                int bytes =recv(client.get_connection_socket(), p, end - p, 0);

                if (bytes < 1) {
                    if (encoding is connection and body) {
                        std::printf("%.*s", (int) (end - body), body);
                    }

                    std::printf("\nConnection closed by peer.\n");
                    client.disconnect_client();
                }

                p = p + bytes;
                *p = 0;

                if (not body and (body = std::strstr(response, "\r\n\r\n"))) {
                    *body = 0;
                    body = body + 4;

                    std::printf("Received Headers:\n%s\n", response);

                    q = std::strstr(response, "\nContent-Length: ");
                    
                    if (q) {
                        encoding = length;
                        q = std::strchr(q, ' ');
                        q = q + 1;
                        remaining = std::strtol(q, 0, 16);
                    }

                    else {
                        q = std::strstr(response, "\nTransfer-Encoding: chunked");
                        if (q) {
                            encoding = chunked;
                            remaining = 0;
                        }
                        else {
                            encoding = connection;
                        }
                    }
                    std::printf("\nReceived Body:\n");
                }

                if (body) {
                    if (encoding is length) {
                        if (p - body >= remaining) {
                            std::printf("%.*s", remaining, body);
                            break;
                        }
                    }

                    else if (encoding is connection) {
                        do {

                            if (remaining is 0) {
                                if ((q = std::strstr(body, "\r\n"))) {
                                    remaining = std::strtol(body, 0, 16);
                                    if (not remaining) goto finish;
                                    body = q + 2;
                                }
                                else {
                                    break;
                                }
                            }

                            if (remaining and p - body >= remaining) {
                                std::printf("%.*s", remaining, body);
                                body = body + remaining + 2;
                                remaining = 0;
                            }

                        } while (not remaining);
                    }
                }

            }

        }

        finish:

        std::printf("Done.\n");
    }
    
}