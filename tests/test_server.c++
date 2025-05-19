

#include <string>
#include <sstream>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <chrono>
#include <filesystem>
#include <thread>


#include "../headers/string_functions"
#include "../headers/misc_functions"
#include "../headers/networking"
#include "include"








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
        TEST_MULTITHREAD_SERVER = "test_multithread_server", TEST_MULTITHREAD_SERVER_ = "tmts",
        
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
    {TEST_WEB_CLIENT, TEST_WEB_CLIENT},
    {TEST_MULTITHREAD_SERVER, TEST_MULTITHREAD_SERVER}
};

// For running file lower
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
    {TEST_WEB_CLIENT, TEST_WEB_CLIENT_},
    {TEST_MULTITHREAD_SERVER, TEST_MULTITHREAD_SERVER_}
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

// Change this to whatever the name of the project base directory is
const std::string project_root_directory = [](std::string base_ = "Simple-Networking") {
    std::filesystem::path the_answer = std::filesystem::path(__FILE__);
    while (not string_functions::same_string(the_answer.filename().string(), base_)) {
        
        the_answer = the_answer.parent_path();
        // std::cout << "the_answer \"" << the_answer.string() << std::endl;
        if (the_answer.string().length() == 1) {
            break;
        }
    }
    
    return the_answer.string();
}();

const std::chrono::duration<int> timeout = std::chrono::seconds(10);


std::unordered_map<std::string, std::string> parse_url(const std::string url = default_url, 
            const std::unordered_map<std::string, std::string> default_values = {
                {PROTOCOL, "HTTP"},
                {HOSTNAME, default_url},
                {PORT, "443"},
                {PATH, "/"},
                {HASH, ""}
            });

std::unordered_map<std::string, std::string> parse_header(const std::string& raw_header, const std::string& separator = ":");

void list_machine_adapters();

void resolve_hostname();

void resolve_hostname_name();

void test_server();

void test_multithread_server();

void test_secure_server();

void test_multithread_secure_server();

void test_client();

void test_secure_client();

void windows_tests();

void test_web_client();

void print_socket_configs(socket_type the_socket);

void print_horizontal(char to_print = '*', bool nl = true);

void print_horizontal_count(char to_print = '*', int count = misc_functions::get_terminal_width(), bool nl = true);

int main(int len, char** args) {

    
    if (len <= 1) {
        std::printf("Help. This is for testing the networking library. Use one of the following arguments to test the library:\n");
        for (const auto& arg : test_args_caps) {
            std::cout << "\t\"" << arg.second << "\"" << std::endl;
        }
    }
    
    int index;
    for (index = 1; index < len; index++) {
        
        if (string_functions::same_string(std::string(args[index]), test_args_caps[LIST_ADAPTERS]) or 
            string_functions::same_string(std::string(args[index]), test_args_lower[LIST_ADAPTERS])) {
            list_machine_adapters();
        }

        else if (string_functions::same_string(std::string(args[index]), test_args_caps[RESOLVE_HOST]) or 
            string_functions::same_string(std::string(args[index]), test_args_lower[RESOLVE_HOST])) {
            resolve_hostname();
        }

        else if (string_functions::same_string(std::string(args[index]), test_args_caps[RESOLVE_HOST_NAME]) or 
            string_functions::same_string(std::string(args[index]), test_args_lower[RESOLVE_HOST_NAME])) {
            resolve_hostname_name();
        }
        
        else if (string_functions::same_string(args[index], test_args_caps[TEST_SERVER]) or 
            string_functions::same_string(args[index], test_args_lower[TEST_SERVER])) {
            test_server();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_MULTITHREAD_SERVER]) or
            string_functions::same_string(args[index], test_args_lower[TEST_MULTITHREAD_SERVER])) {
            test_multithread_server();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_SECURE_SERVER]) or 
            string_functions::same_string(args[index], test_args_lower[TEST_SECURE_SERVER])) {
            test_secure_server();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_CLIENT]) or 
            string_functions::same_string(args[index], test_args_lower[TEST_CLIENT])) {
            test_client();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_SECURE_CLIENT]) or 
            string_functions::same_string(args[index], test_args_lower[TEST_SECURE_CLIENT])) {
            test_secure_client();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_WINDOWS]) or 
            string_functions::same_string(args[index], test_args_lower[TEST_WINDOWS])) {
            std::printf("Running windows tests:\n");
            windows_tests();
        }

        else if (string_functions::same_string(args[index], test_args_caps[TEST_WEB_CLIENT]) or 
            string_functions::same_string(args[index], test_args_lower[TEST_WEB_CLIENT])) {
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

std::unordered_map<std::string, std::string> parse_header(const std::string& raw_header, const std::string& separator) {
    std::unordered_map<std::string, std::string> the_answer;

    // Structure to parse:
    // HTTP/1.1 301 Moved Permanently\r\n
    // Content-Type: application/binary\r\n
    // X-Content-Type-Options: nosniff\r\n
    // Expires: Sun, 18 May 2025 21:19:06 GMT\r\n
    // Date: Sun, 18 May 2025 21:19:06 GMT\r\n
    // Cache-Control: private, max-age=31536000\r\n
    // Location: https://www.youtube.com/\r\n
    // Strict-Transport-Security: max-age=31536000; includeSubDomains; preload\r\n
    // X-Frame-Options: SAMEORIGIN\r\n
    // Content-Security-Policy: require-trusted-types-for 'script'\r\n
    // Report-To: {"group":"youtube_main","max_age":2592000,"endpoints":[{"url":"https://csp.withgoogle.com/csp/report-to/youtube_main"}]}\r\n
    // Cross-Origin-Opener-Policy: same-origin-allow-popups; report-to="youtube_main"\r\n
    // Origin-Trial: AmhMBR6zCLzDDxpW+HfpP67BqwIknWnyMOXOQGfzYswFmJe+fgaI6XZgAzcxOrzNtP7hEDsOo1jdjFnVr2IdxQ4AAAB4eyJvcmlnaW4iOiJodHRwczovL3lvdXR1YmUuY29tOjQ0MyIsImZlYXR1cmUiOiJXZWJWaWV3WFJlcXVlc3RlZFdpdGhEZXByZWNhdGlvbiIsImV4cGlyeSI6MTc1ODA2NzE5OSwiaXNTdWJkb21haW4iOnRydWV9\r\n
    // Permissions-Policy: ch-ua-arch=*, ch-ua-bitness=*, ch-ua-full-version=*, ch-ua-full-version-list=*, ch-ua-model=*, ch-ua-wow64=*, ch-ua-form-factors=*, ch-ua-platform=*, ch-ua-platform-version=*\r\n
    // Server: ESF\r\n
    // Content-Length: 0\r\n
    // X-XSS-Protection: 0\r\n
    // Alt-Svc: h3=":443"; ma=2592000,h3-29=":443"; ma=2592000\r\n
    // Connection: close\r\n
    // \r\n

    std::istringstream stream(raw_header);
    std::string line;
    bool first_line = true;

    while (std::getline(stream, line)) {
        // Remove trailing '\r' if present
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        // Skip empty lines (end of headers)
        if (line.empty()) break;

        if (first_line) {
            // Handle status line separately if needed
            the_answer["Status"] = line;
            first_line = false;
            continue;
        }

        // Find the first ':' as separator
        size_t sep = line.find(separator);
        if (sep == std::string::npos) {
            // Malformed header, skip or handle as needed
            continue;
        }
        // Extract key and value, trim spaces
        std::string key = line.substr(0, sep);
        std::string value = line.substr(sep + 1);
        // Trim leading spaces from value
        size_t value_start = value.find_first_not_of(" ");
        if (value_start != std::string::npos) {
            value = value.substr(value_start);
        } 
        
        else {
            value.clear();
        }
        the_answer[key] = value;
    }
    return the_answer;


   
}

void list_machine_adapters() {
    std::unordered_map<std::string, std::unordered_map<std::string, std::set<std::string> > > adapters = networking::machine_adapters();

    for (const auto& [name, adapter_map] : adapters) {
        std::cout << name << std::endl;
        for (const auto& [family, set_] : adapter_map) {
            unsigned long index = 0;
            const unsigned long len = set_.size();
            std::cout << "\t\"" << family << "\":\t" << std::endl;
            for (const auto& address : set_) {
                std::cout << address << ((index + 1 == len) ? "\n" : ", ");
            }
        }
    }
}

void resolve_hostname() {
    std::string host = misc_functions::get_input("Hostname : ");
    std::unordered_set<std::string> addresses = networking::resolve_hostname(host, connection_port);
    std::cout << host << ":" << std::endl;
    unsigned long index;
    for (const auto& address : addresses) {
        std::cout << "\t" << address << std::endl;
    }
}

void resolve_hostname_name() {
    std::string host = misc_functions::get_input("Hostname : ");
    std::unordered_set<std::string> addresses = networking::resolve_hostname(host, connection_port, true);
    std::cout << host << ":" << std::endl;
    unsigned long index;
    for (const auto& address : addresses) {
        std::cout << "\t" << address << std::endl;
    }
}

void test_server() {
    
    const int count = 1, flags = 0;
    char msg[__kilo_bytes__(count)];
    bytes byte_count;
    std::string message;

    networking::network_structures::host_report report;
    networking::network_structures::complete_report reports;
    networking::network_structures::client_connection client;
    std::unordered_set<networking::network_structures::client_connection> clients;

    networking::network_structures::tcp_server server;


    server
        .retrieve_hostname()
        .secure(false)
        .port(connection_port);

    // std::cout << "Set all the attributes of the server." << std::endl;

    try {

        if (not server.start()) {
            std::cerr << "Failed to successfully start the server" << std::endl;
            return;
        }
        std::cout << "Successfully started the server. Connect to the " << ((server.secure()) ? "secure" : "non-secure") << "server using " << server.hostname() << ":" << server.port() << std::endl;

        while (server) {

            try {
                if ((client = server.new_client())) {
                    std::cout << "New connection from \"" << client.host_information.hostname << "\"" << std::endl;
                }
            }

            catch (networking::exceptions::secure_handshake_failure& except) {
                continue;
            }
            

            if (not (clients = server.clients(false)).empty()) {

                for (auto& client_ : clients) {
                    message = misc_functions::get_current_time();
                    byte_count = (server.secure()) ? SSL_read(client_.secure_connect_socket, msg, __kilo_bytes__(count)) :
                                                    recv(client_.connect_socket, msg, __kilo_bytes__(count), flags);

                    if (byte_count < 1) {
                        std::cerr << "Something went wrong with client \"" << client_.host_information.hostname << "\". Disconnecting client now" << std::endl;
                        server.disconnect_client(client_);
                    }
                    std::cout << client_.host_information.hostname << "(" << message << ") : " << std::string(msg, byte_count) << std::endl;
                }
                clients.clear();
            }

            if (misc_functions::has_keyboard_input()) {
                message = misc_functions::get_input();

                if (string_functions::same_string(message, "close") or string_functions::same_string(message, "exit") or string_functions::same_string(message, "stop") or string_functions::same_string(message, "halt")) {
                    server.stop();
                }

                else if (string_functions::same_string(message, "list clients") or string_functions::same_string(message, "lc")) {
                    
                    if ((clients = server.clients()).empty()) {
                        std::cout << "No clients to message" << std::endl;
                        continue;
                    }
                    
                    for (const auto& client_ : clients) {
                        std::cout << client_.host_information.hostname << ":" << std::endl;
                        std::cout << "\t" << client_.host_information.port << ":" << std::endl;
                        std::cout << "\t" << client_.host_information.connection_time << ":" << std::endl;
                    }
                }

                else if (string_functions::same_string(message, "broadcast message") or string_functions::same_string(message, "broadcast") or string_functions::same_string(message, "brdcst")) {
                    
                    if ((clients = server.clients()).empty()) {
                        std::cout << "No clients to message" << std::endl;
                        continue;
                    }

                    message = misc_functions::get_input("Broadcast message : ");
                    
                    reports = server.broadcast<const char>(message.c_str(), message.length(), flags, true, timeout);

                    if (reports.fails()) {
                        std::cerr << "Failed to send broadcast message to " << reports.fails() << " clients out of " << clients.size() << " clients" << std::endl;
                        for (const auto& report_ : reports.reports) {
                            std::cout << "\t\"" << report_.host.host_information.hostname << "\"" << std::endl;
                        }
                        continue;
                    }
                    std::cout << "Successfully sent \"" << message << "\" to " << reports.success() << " clients out of " << clients.size() << " clients" << std::endl;

                }

                else if (string_functions::same_string(message, "message client") or string_functions::same_string(message, "msgc") or string_functions::same_string(message, "mc")) {
                    
                    if ((clients = server.clients()).empty()) {
                        std::cout << "No clients to message" << std::endl;
                        continue;
                    }
                    
                    std::cout << "Choose a client to message: " << std::endl;
                    message = "";
                    client = {};
                    while (message.empty() and not client and not clients.empty()) {
                        
                        for (const auto& client_ : clients) {
                            std::cout << "\t" << client_.host_information.hostname << ":" << std::endl;
                            std::cout << "\t\t" << client_.host_information.port << ":" << std::endl;
                            std::cout << "\t\t" << client_.host_information.connection_time << ":" << std::endl;
                        }
                        message = misc_functions::get_input("Client : ");

                        if (string_functions::same_string(message, "stop")) {
                            server.stop();
                            break;
                        }

                        if (message.empty() or string_functions::same_string(message, "n/a")) {
                            break;
                        }
                        
                        for (const auto& client_ : clients) {
                            if (string_functions::same_string(message, client_.host_information.hostname)) {
                                client = client_;
                            }

                            else if (string_functions::same_string(message, client_.host_information.port)) {
                                client = client_;
                            }

                            else if (string_functions::same_string(message, client_.host_information.connection_time)) {
                                client = client_;
                            }

                            if (client) {
                                break;
                            }
                        }

                        if (client) {
                            // client to message selected
                            break;
                        }

                        message = "";
                        clients = server.clients();
                    }

                    if (client) {
                        byte_count = message.length();
                        reports = server.message(client.host_information, message.c_str(), byte_count, flags, true, timeout);

                        if (reports.success()) {
                            std::cout << "Successfully sent the message to " << reports.reports.size() << " client" << (reports.reports.size() > 1 ? "s." : ".") << std::endl;
                        }

                        if (reports.fails()) {
                            std::cout << "Failed to send a message to " << reports.fails() << " clients out of " << reports.reports.size() << " clients" << std::endl;
                        }

                    }
                }

                else {
                    std::cerr << "Unrecognized command \"" << message << "\"" << std::endl;
                }

            }

        }
    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Caught exception \"" << except.message() << "\"" << std::endl;
    }

}

void test_multithread_server() {
    
    const bool block_clients = true, secure = false;
    const int flags = 0, listening_limit = 100;

    const std::chrono::duration<int> timeout = std::chrono::duration<int>(10);
    
    
    networking::network_structures::tcp_server server;
    networking::network_structures::client_connection client;
    networking::network_structures::complete_report reports;

    try {

        server.block_clients(block_clients).certificate("../files/cert.pem").secure_key("../files/key.pem").secure(secure).listening_limit(listening_limit).retrieve_hostname();
        server.port(connection_port);
        if (not server.start()) {
            std::cerr << "Failed to started the server" << std::endl;
            return;
        }

        std::cerr << "Server started. Connect to the server using \"" << server.hostname() << "\" and port \"" << server.port() << "\"" << std::endl;

        while (server) {

            try {

                if ((client = server.new_client())) {
                    
                    std::thread([&server, timeout](networking::network_structures::client_connection client){
                        std::cout << "Inside thread " << std::this_thread::get_id() << std::endl;
                        std::cout << "New connection from \"" << client.host_information.hostname << "\" at \"" << client.host_information.connection_time << "\"" << std::endl;
                        
                        const int count = 4, flags = 0;
                        char msg[__kilo_bytes__(count)];
                        bytes byte_count;
                        // networking::network_structures::host_report report;
                        
                        int byte_error;
                        #if defined(crap_os)
                            const int block_read = (server.secure()) ? SSL_ERROR_WANT_READ : WSAWOULDBLOCK;
                            const int block_write = (server.secure()) ? SSL_ERROR_WANT_WRITE : WSACONNRESET;
                        #else
                            const int block_write = (server.secure()) ? SSL_ERROR_WANT_WRITE : EWOULDBLOCK;
                            const int block_read = (server.secure()) ? SSL_ERROR_WANT_READ : EAGAIN;
                        #endif
                        std::cout << "client's host evaluates to " << ((client.host_information) ? "true" : "false") << std::endl;
                        std::string message;
                        networking::network_structures::host_report report;

                        
                        // fd_set read_ready;
                        while (server or server.connected(client)) {
                            
                            if (server.message(client)) {
                                // There is a message from the client
                                std::cout << "Client has a message" << std::endl;
                                message = misc_functions::get_current_time();
                                report = server.message<char>(client, msg, __kilo_bytes__(count), flags, timeout);
                                if (not report.success) {
                                    std::cerr << "Failed to receive data from client \"" << client.host_information.hostname << "\"" << std::endl;
                                    server.disconnect_client(client);
                                    break;
                                }

                                std::cout << "(" << message << ") Message from \"" << client.host_information.hostname << "\" : " << std::string(msg, report.byte_count) << std::endl;
                            }
                        }
                        std::cout << "Out of the while loop for client : " << client.host_information.hostname << std::endl;

                    }, client).detach();
                }

            }

            catch (networking::exceptions::secure_handshake_failure& except) {
                continue;
            }

            if (misc_functions::has_keyboard_input()) {
                std::string message = misc_functions::get_input();
                if (string_functions::same_string(message, "close") or string_functions::same_string(message, "exit") or string_functions::same_string(message, "stop") or string_functions::same_string(message, "halt")) {
                    server.stop();
                }

                else if (string_functions::same_string(message, "broadcast") or string_functions::same_string(message, "brdcst")) {
                    message = misc_functions::get_input("Message to broadcast : ");
                    reports = server.broadcast(message.data(), message.length(), flags, true, timeout);
                }

                else {
                    std::cerr << "Unrecognized argument \"" << message << "\"" << std::endl;
                }
            }

        }

    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Exception caught \"" << except.message() << "\"" << std::endl;
    }
}

void test_secure_server() {
    
    const int count = 1, flags = 0;
    char msg[__kilo_bytes__(count)];
    bytes byte_count;
    std::string message;

    networking::network_structures::host_report report;
    networking::network_structures::complete_report reports;
    networking::network_structures::client_connection client;
    std::unordered_set<networking::network_structures::client_connection> clients;

    networking::network_structures::tcp_server server;


    server
        .retrieve_hostname()
        .secure(true)
        .port(connection_port)
        .secure_key(project_root_directory + std::string(__sys_slash__) + "files" + std::string(__sys_slash__) + "key.pem")
        .certificate(project_root_directory + std::string(__sys_slash__) + "files" + std::string(__sys_slash__) + "cert.pem");

    // std::cout << "Set all the attributes of the server." << std::endl;

    try {

        if (not server.start()) {
            std::cerr << "Failed to successfully start the server" << std::endl;
            return;
        }
        std::cout << "Successfully started the server. Connect to the secure server using " << server.hostname() << ":" << server.port() << std::endl;

        while (server) {

            try {
                if ((client = server.new_client())) {
                    std::cout << "New connection from \"" << client.host_information.hostname << "\"" << std::endl;
                }
            }

            catch (networking::exceptions::secure_handshake_failure& except) {
                continue;
            }
            

            if (not (clients = server.clients(false)).empty()) {

                for (auto& client_ : clients) {
                    message = misc_functions::get_current_time();
                    byte_count = (server.secure()) ? SSL_read(client_.secure_connect_socket, msg, __kilo_bytes__(count)) :
                                                    recv(client_.connect_socket, msg, __kilo_bytes__(count), flags);

                    if (byte_count < 1) {
                        std::cerr << "Something went wrong with client \"" << client_.host_information.hostname << "\". Disconnecting client now" << std::endl;
                        server.disconnect_client(client_);
                    }
                    std::cout << client_.host_information.hostname << "(" << message << ") : " << std::string(msg, byte_count) << std::endl;
                }
                clients.clear();
            }

            if (misc_functions::has_keyboard_input()) {
                message = misc_functions::get_input();

                if (string_functions::same_string(message, "close") or string_functions::same_string(message, "exit") or string_functions::same_string(message, "stop") or string_functions::same_string(message, "halt")) {
                    server.stop();
                }

                else if (string_functions::same_string(message, "list clients") or string_functions::same_string(message, "lc")) {
                    
                    if ((clients = server.clients()).empty()) {
                        std::cout << "No clients to message" << std::endl;
                        continue;
                    }
                    
                    for (const auto& client_ : clients) {
                        std::cout << client_.host_information.hostname << ":" << std::endl;
                        std::cout << "\t" << client_.host_information.port << ":" << std::endl;
                        std::cout << "\t" << client_.host_information.connection_time << ":" << std::endl;
                    }
                }

                else if (string_functions::same_string(message, "broadcast message") or string_functions::same_string(message, "broadcast") or string_functions::same_string(message, "brdcst")) {
                    
                    if ((clients = server.clients()).empty()) {
                        std::cout << "No clients to message" << std::endl;
                        continue;
                    }

                    message = misc_functions::get_input("Broadcast message : ");
                    
                    reports = server.broadcast<const char>(message.c_str(), message.length(), flags, true, timeout);

                    if (reports.fails()) {
                        std::cerr << "Failed to send broadcast message to " << reports.fails() << " clients out of " << clients.size() << " clients" << std::endl;
                        for (const auto& report_ : reports.reports) {
                            std::cout << "\t\"" << report_.host.host_information.hostname << "\"" << std::endl;
                        }
                        continue;
                    }
                    std::cout << "Successfully sent \"" << message << "\" to " << reports.success() << " clients out of " << clients.size() << " clients" << std::endl;

                }

                else if (string_functions::same_string(message, "message client") or string_functions::same_string(message, "msgc") or string_functions::same_string(message, "mc")) {
                    
                    if ((clients = server.clients()).empty()) {
                        std::cout << "No clients to message" << std::endl;
                        continue;
                    }
                    
                    std::cout << "Choose a client to message: " << std::endl;
                    message = "";
                    client = {};
                    while (message.empty() and not client and not clients.empty()) {
                        
                        for (const auto& client_ : clients) {
                            std::cout << "\t" << client_.host_information.hostname << ":" << std::endl;
                            std::cout << "\t\t" << client_.host_information.port << ":" << std::endl;
                            std::cout << "\t\t" << client_.host_information.connection_time << ":" << std::endl;
                        }
                        message = misc_functions::get_input("Client : ");

                        if (string_functions::same_string(message, "stop")) {
                            server.stop();
                            break;
                        }

                        if (message.empty() or string_functions::same_string(message, "n/a")) {
                            break;
                        }
                        
                        for (const auto& client_ : clients) {
                            if (string_functions::same_string(message, client_.host_information.hostname)) {
                                client = client_;
                            }

                            else if (string_functions::same_string(message, client_.host_information.port)) {
                                client = client_;
                            }

                            else if (string_functions::same_string(message, client_.host_information.connection_time)) {
                                client = client_;
                            }

                            if (client) {
                                break;
                            }
                        }

                        if (client) {
                            // client to message selected
                            break;
                        }

                        message = "";
                        clients = server.clients();
                    }

                    if (client) {
                        byte_count = message.length();
                        reports = server.message(client.host_information, message.c_str(), byte_count, flags, true, timeout);

                        if (reports.success()) {
                            std::cout << "Successfully sent the message to " << reports.reports.size() << " client" << (reports.reports.size() > 1 ? "s." : ".") << std::endl;
                        }

                        if (reports.fails()) {
                            std::cout << "Failed to send a message to " << reports.fails() << " clients out of " << reports.reports.size() << " clients" << std::endl;
                        }

                    }
                }

                else {
                    std::cerr << "Unrecognized command \"" << message << "\"" << std::endl;
                }

            }

        }
    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Caught exception \"" << except.message() << "\"" << std::endl;
    }
}

void test_client() {
    // std::cout << UNDER_CONSTRUCTION << std::endl;
    const bool SECURE = false, BLOCK = false;

    const int flags = 0, time_limit = 10, count = 1;
    std::string message, file_name;
    char msg[__kilo_bytes__(count)];
    const std::chrono::duration<int> timeout = std::chrono::seconds(time_limit);

    networking::network_structures::server_connection server;
    networking::network_structures::host_report report;

    networking::network_structures::tcp_client client(misc_functions::get_input("Enter host to connect to : "));
    client.port(connection_port).secure(SECURE).block(BLOCK).server_name_indication(false);

    try {

        std::cout << "Connecting to \"" << client.hostname() << "\" on port \"" << client.port() << "\"" << std::endl;
        if (not client.start()) {
            std::cerr << "Failed to start the client and connect to remote host." << std::endl;
            return;
        }

        std::cout << "Connected to \"" << client.hostname() << "\" on port \"" << client.port() << "\"" << std::endl;

        while (client) {

            if (client.message()) {
                // There is a message from the server
                
                report = client.message<char>(msg, __kilo_bytes__(count), flags, timeout);

                if (not report.success) {
                    client.stop();
                    continue;
                }

                // Successfully received a message
                std::cout << "Received message at (" << misc_functions::get_current_time() << ") : " << std::endl << std::endl << "\"" << std::string(msg, report.byte_count) << "\"" << std::endl;
            }

            if (misc_functions::has_keyboard_input()) {

                message = misc_functions::get_input();

                if (string_functions::same_string(message, "close") or string_functions::same_string(message, "exit") or string_functions::same_string(message, "stop") or string_functions::same_string(message, "halt")) {
                    client.stop();
                }

                else if (string_functions::same_string(message, "server information") or string_functions::same_string(message, "si")) {
                    server = client.connection_information();
                    std::cout << "Host information :" << std::endl;
                    std::cout << "\tHostname : " << server.host_information.hostname << std::endl;
                    std::cout << "\tPort : " << server.host_information.port << std::endl;
                    std::cout << "\tConnection time : " << server.host_information.connection_time << std::endl;
                }

                else if (string_functions::same_string(message, "message server") or string_functions::same_string(message, "ms")) {
                    message = misc_functions::get_input("Message for server : ");

                    if (message.empty() or string_functions::same_string(message, "n/a")) {
                        continue;
                    }

                    report = client.message<const char>(message.c_str(), message.length(), flags, timeout);
                    if (not report.success) {
                        std::cerr << "Failed to send message." << std::endl;
                        if (report.byte_count > 0) {
                            std::cout << "Did a partial send of " << report.byte_count << " bytes out of " << message.length() << " bytes. Trying to send the rest of the bytes now." << std::endl;
                            report = client.message<const char>(message.data() + report.byte_count, message.length() - report.byte_count, flags, timeout);
                            if (report.success) {
                                std::cout << "Successfully sent the rest of the bytes." << std::endl;
                            }
                            else {
                                std::cerr << "Failed to send the rest of the bytes." << std::endl;
                            }
                            continue;
                        }
                        // Complete failure
                        std::cerr << "Complete failure to send the message." << std::endl;
                        continue;
                    }
                    std::cout << "Successfully sent " << report.byte_count << " bytes out of " << message.length() << " bytes." << std::endl;
                }

                else {
                    std::cerr << "Unrecognized command \"" << message << "\"" << std::endl;
                }

            }

        }

    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Exception caught of type \"" << except.type() << "\"" << std::endl;
    }
}

void test_secure_client() {
    // std::cout << UNDER_CONSTRUCTION << std::endl;
    const bool SECURE = true, BLOCK = false;

    const int flags = 0, time_limit = 10, count = 1;
    std::string message, file_name;
    char msg[__kilo_bytes__(count)];
    const std::chrono::duration<int> timeout = std::chrono::seconds(time_limit);

    networking::network_structures::server_connection server;
    networking::network_structures::host_report report;

    networking::network_structures::tcp_client client(misc_functions::get_input("Enter host to connect to : "));
    client.port(connection_port).secure(SECURE).block(BLOCK).server_name_indication(false);

    try {

        std::cout << "Connecting to \"" << client.hostname() << "\" on port \"" << client.port() << "\"" << std::endl;
        if (not client.start()) {
            std::cerr << "Failed to start the client and connect to remote host." << std::endl;
            return;
        }

        std::cout << "Connected to \"" << client.hostname() << "\" on port \"" << client.port() << "\"" << std::endl;

        while (client) {

            if (client.message()) {
                // There is a message from the server
                
                report = client.message<char>(msg, __kilo_bytes__(count), flags, timeout);

                if (not report.success) {
                    client.stop();
                    continue;
                }

                // Successfully received a message
                std::cout << "Received message at (" << misc_functions::get_current_time() << ") : " << std::endl << std::endl << "\"" << std::string(msg, report.byte_count) << "\"" << std::endl;
            }

            if (misc_functions::has_keyboard_input()) {

                message = misc_functions::get_input();

                if (string_functions::same_string(message, "close") or string_functions::same_string(message, "exit") or string_functions::same_string(message, "stop") or string_functions::same_string(message, "halt")) {
                    client.stop();
                }

                else if (string_functions::same_string(message, "server information") or string_functions::same_string(message, "si")) {
                    server = client.connection_information();
                    std::cout << "Host information :" << std::endl;
                    std::cout << "\tHostname : " << server.host_information.hostname << std::endl;
                    std::cout << "\tPort : " << server.host_information.port << std::endl;
                    std::cout << "\tConnection time : " << server.host_information.connection_time << std::endl;
                }

                else if (string_functions::same_string(message, "message server") or string_functions::same_string(message, "ms")) {
                    message = misc_functions::get_input("Message for server : ");

                    if (message.empty() or string_functions::same_string(message, "n/a")) {
                        continue;
                    }

                    report = client.message<const char>(message.c_str(), message.length(), flags, timeout);
                    if (not report.success) {
                        std::cerr << "Failed to send message." << std::endl;
                        if (report.byte_count > 0) {
                            std::cout << "Did a partial send of " << report.byte_count << " bytes out of " << message.length() << " bytes. Trying to send the rest of the bytes now." << std::endl;
                            report = client.message<const char>(message.data() + report.byte_count, message.length() - report.byte_count, flags, timeout);
                            if (report.success) {
                                std::cout << "Successfully sent the rest of the bytes." << std::endl;
                            }
                            else {
                                std::cerr << "Failed to send the rest of the bytes." << std::endl;
                            }
                            continue;
                        }
                        // Complete failure
                        std::cerr << "Complete failure to send the message." << std::endl;
                        continue;
                    }
                    std::cout << "Successfully sent " << report.byte_count << " bytes out of " << message.length() << " bytes." << std::endl;
                }

                else {
                    std::cerr << "Unrecognized command \"" << message << "\"" << std::endl;
                }

            }

        }

    }

    catch (networking::exceptions::base_exception& except) {
        std::cerr << "Exception caught of type \"" << except.type() << "\"" << std::endl;
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

void test_web_client() {

    // std::cout << (networking::cleans_on_excepts() ? "TRUEEEEE" : "FALSEEEEE");

    std::string url = misc_functions::get_input("URL : ");

    if (url.empty()) {
        url = "example.com";
    }

    // Parse the url
    std::unordered_map<std::string, std::string> url_parsed = parse_url(url);
    for (auto part : url_parsed) {
        std::cout << "\t" << part.first << " : " << part.second << std::endl;
    }

    // variables for use
    bytes bytes;
    unsigned long index, message_length;
    const int count = 32, flags = MSG_PEEK;
    char msg[__kilo_bytes__(count)];

    // char *p = msg, *q, *end = msg + __kilo_bytes__(count), *body = 0;

    enum {length, chunked, connection};
    int encoding = 0, remaining = 0;

    const std::string ending = "\r\n";
    std::string message;
    
    if (not url_parsed.contains(HOSTNAME)) {
        std::cerr << "No hostname specified in url" << std::endl;
        return;
    }

    networking::network_structures::tcp_client client(url_parsed[HOSTNAME], url_parsed[PORT]);
    
    client.secure(true).server_name_indication(true).block(false);

    if (client.message<char>(message.data(), message.length(), flags, timeout).success) {
        std::cerr << "Falsely reports a successful send when no connection has been established" << std::endl;
        return;
    }

    if (not client.start()) {
        std::cerr << "Failed to start client" << std::endl;
        return;
    }

    message = 
            "GET " + url_parsed[PATH] + " HTTP/1.1" + ending +
            "Host: " + url_parsed[HOSTNAME] + ":" +url_parsed[PORT] + ending +
            "Connection: close" + ending +
            "User-Agent: honpwc https_get 1.0" + ending +
            ending;

    
    networking::network_structures::host_report response;
    networking::network_structures::server_connection server = client.connection_information();
    
    
    response = client.message<const char>(message.data(), message.length(), flags, timeout);

    if (not response.success) {
        std::cerr << "Failed to send the resource request. Sent " << response.byte_count << " bytes out of " << message.length() << " bytes" << std::endl;
        client.stop();
        return;
    }
    
    message.clear();
    message.shrink_to_fit();
    std::cout << "Successfully requested resources" << std::endl;
    const auto start_time = std::chrono::steady_clock::now();

    
    response = client.message<char>(msg, __kilo_bytes__(count), flags, timeout);

    if (not response.success) {
        std::cerr << "Failed to retrieve data from server" << std::endl;
        return;
    }

    message = std::string(msg, response.byte_count);
    index = message.find(ending + ending);

    if (index == std::string::npos) {
        std::cerr << "Failed to parse the headers out of the response" << std::endl;
        return;
    }

    std::unordered_map<std::string, std::string> headers = parse_header(message);
    if (not headers.empty()) {
        message_length = 0;
        std::cout << "Parsed out headers : " << std::endl;
        for (const auto& [tag, value] : headers) {
            std::cout << tag << " : " << value << std::endl;
            if (string_functions::same_string(tag, "content-length")) {
                message_length = std::stoul(value, nullptr, 10);
            }
        }
        client.message<char>(msg, message.length(), 0, timeout);
        std::cout << std::endl << std::endl << std::endl;
        char complete_message[message_length];
        response = client.message<char>(complete_message, index + message_length, 0, timeout);

        if (not response.success) {
            std::cerr << "Failed to retrieve the complete response" << std::endl;
            return;
        }

        message = std::string(msg, index, message_length);

        std::cout << "And the message is:" << std::endl;
        std::cout << message << std::endl;
        client.stop();
        std::cout << "Client connection closed after " << std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time).count() << " seconds." << std::endl;
        return;
    }

    client.stop();
    std::cout << "Client connection closed after " << std::chrono::duration<double>(std::chrono::steady_clock::now() - start_time).count() << " seconds." << std::endl;

    if (response.success) {
        // message = std::string(msg, response.byte_count);
        std::cout << "Message from server" << ending << "\"" << std::string(msg, response.byte_count) << "\"" << std::endl;
    }
}

void print_socket_configs(socket_type the_socket) {
    if (not valid_socket(the_socket)) {
        return;
    }
    std::cout << UNDER_CONSTRUCTION << std::endl;
}

void print_horizontal(char to_print, bool nl) {
    int index, length = misc_functions::get_terminal_width();
    for (index = 0; index < length; index++) {
        std::printf("%c", to_print);
    }
    (nl) ? std::printf("\n") : 0;
}

void print_horizontal_count(char to_print, int count, bool nl) {
    // const int max_width = misc_functions::get_terminal_width();
    count = (count > misc_functions::get_terminal_width()) ? misc_functions::get_terminal_width() : count;
    int index;
    for (index = 0; index < count; index++) {
        std::printf("%c", to_print);
    }
    (nl) ? std::printf("\n") : 0;
}