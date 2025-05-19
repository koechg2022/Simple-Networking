


#include <vector>
#include <chrono>
#include <filesystem>
#include <mutex>



#include "../headers/networking"
#include "../headers/string_functions"
#include "../headers/misc_functions"




namespace networking {

    namespace {

        #if defined(crap_os)
            std::atomic<bool> network_init = false;
        #else
            const std::atomic<bool> network_init = true;
        #endif
        std::atomic<bool> secure_init = false;
        std::mutex init_mutex, secure_init_mutex;
    }


    exceptions::base_exception::base_exception(const std::string exception_type,
                                                    const std::string msg, 
                                                        const std::string file_name,
                                                            const bool print_msg,
                                                                const int line, 
                                                                    const int error_number,
                                                                        const std::string function) {
        this->exception_type_ = exception_type;
        this->message_ = msg;
        this->file_ = file_name;
        this->error_line_ = line;
        this->error_num_ = error_number;
        this->func_ = function;
        (print_msg) ? this->print() : (void) 0;
    }

    std::string exceptions::base_exception::type() const {
        return this->exception_type_;
    }

    std::string exceptions::base_exception::message() const {
        return this->message_;
    }

    std::string exceptions::base_exception::file() const {
        return this->file_;
    }

    std::string exceptions::base_exception::function() const {
        return this->func_;
    }

    int exceptions::base_exception::error_line() const {
        return this->error_line_;
    }

    int exceptions::base_exception::error_number() const {
        return this->error_num_;
    }

    void exceptions::base_exception::print() const {
        std::fprintf(stderr, "%s : %s : %s : line %d : %d : %s\n", this->file_.c_str(), this->exception_type_.c_str(), this->func_.c_str(), this->error_line_, this->error_num_, this->message_.c_str());
    }

    exceptions::memory_exception_failure::memory_exception_failure(const std::string msg,
                                                        const bool print_msg, 
                                                            const std::string file_name,
                                                                const int line,
                                                                    const int error_number,
                                                                        const std::string function) 
                unpack_exception_base_call(exceptions::memory_exception_failure_type)

    exceptions::initialize_network_failure::initialize_network_failure(const std::string msg,
                                                        const bool print_msg, 
                                                            const std::string file_name,
                                                                const int line,
                                                                    const int error_number,
                                                                        const std::string function)
                unpack_exception_base_call(exceptions::initialize_network_failure_type)


    exceptions::uninitialize_network_failure::uninitialize_network_failure(const std::string msg,
                                                        const bool print_msg, 
                                                            const std::string file_name,
                                                                const int line,
                                                                    const int error_number,
                                                                        const std::string function)
                unpack_exception_base_call(exceptions::uninitialize_network_failure_type)
    
    exceptions::getaddrinfo_failure::getaddrinfo_failure(const std::string msg,
                                                        const bool print_msg, 
                                                            const std::string file_name,
                                                                const int line,
                                                                    const int error_number,
                                                                        const std::string function)
                unpack_exception_base_call(exceptions::getaddrinfo_failure_type)


    exceptions::getifaddrs_failure::getifaddrs_failure(const std::string msg,
                                                        const bool print_msg, 
                                                            const std::string file_name,
                                                                const int line,
                                                                    const int error_number,
                                                                        const std::string function)
                unpack_exception_base_call(exceptions::getifaddrs_failure_type)

    exceptions::unexpected_failure::unexpected_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::getifaddrs_failure_type)


    exceptions::create_connection_address_failure::create_connection_address_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::create_connection_address_failure_type)


    exceptions::create_connection_socket_failure::create_connection_socket_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::create_connection_socket_failure_type)

    exceptions::listening_failure::listening_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::listening_failure_type)

    exceptions::create_context_failure::create_context_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::create_context_failure_type)

    exceptions::use_key_and_cert_failure::use_key_and_cert_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::use_key_and_cert_failure_type)

    exceptions::select_failure::select_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::select_failure_type)


    exceptions::getnameinfo_failure::getnameinfo_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::getnameinfo_failure_type)


    exceptions::create_secure_socket_failure::create_secure_socket_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::create_secure_socket_failure_type)


    exceptions::accept_secure_connection_failure::accept_secure_connection_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::accept_secure_connection_failure_type)


    exceptions::socket_information_failure::socket_information_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::socket_information_failure_type)

    exceptions::bind_socket_failure::bind_socket_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::socket_information_failure_type)


    exceptions::connection_failure::connection_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::connection_failure_type)


    exceptions::certificate_failure::certificate_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::certificate_failure_type)

    exceptions::key_failure::key_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::key_failure_type)


    exceptions::secure_handshake_failure::secure_handshake_failure(const std::string msg,
        const bool print_msg, 
            const std::string file_name,
                const int line,
                    const int error_number,
                        const std::string function)
                unpack_exception_base_call(exceptions::secure_handshake_failure_type)

}

bool networking::network_initialized() {
    return networking::network_init;
}

bool networking::initialize_network() {
    #if defined(crap_os)
        std::lock_guard<std::mutex> init_lock(networking::init_mutex);
        if (not networking::network_init) {
            WSADATA d;
            if (WSAStartup(MAKEWORD(2, 2), &d)) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize network", unpack_exception_parameters(1));
            }
            networking::network_init = true;
        }
    #endif
    return networking::network_init;
}

bool networking::uninitialize_network() {
    #if defined(crap_os)
    std::lock_guard<std::mutex> init_lock(networking::init_mutex);
        if(networking::network_init) {
            if (WSACleanup()) {
                throw networking::exceptions::uninitialize_network_failure("Failed to uninitialize the network", unpack_exception_parameters(1));
            }
            networking::network_init = false;
        }
        return not networking::network_init;
    #endif
    return networking::network_init;
}

bool networking::secure_network_initialized() {
    return networking::secure_init;
}

bool networking::initialize_secure_network() {
    std::lock_guard<std::mutex> secure_lock(networking::secure_init_mutex);
    if (not networking::secure_init) {
        SSL_library_init();
        OpenSSL_add_all_algorithms();
        SSL_load_error_strings();
        networking::secure_init = true;
    }
    return networking::secure_init;
}

bool networking::uninitialize_secure_network() {
    std::lock_guard<std::mutex> secure_lock(networking::secure_init_mutex);
    if (networking::secure_init) {
        OPENSSL_cleanup();
        networking::secure_init = false;
    }
    return not networking::secure_init;
}



/***********************************************************************************************/




std::set<std::string> networking::network_address_families::get_address_families() {
    return (const std::set<std::string>) {
        networking::network_address_families::unspec_address_family,
        networking::network_address_families::unrecognized_address_family,
        networking::network_address_families::ip_version4_address_family,
        networking::network_address_families::ip_version6_address_family,
        #if defined(unix_os)
            #if defined(mac_os)
                networking::network_address_families::link_layer_address_family,
            #else
                networking::network_address_families::netlink_address_family,
                networking::network_address_families::packet_address_family,
            #endif
        #else
            networking::network_address_families::netbios_address_family,
            networking::network_address_families::irda_address_family,
            networking::network_address_families::bluetooth_address_family
        #endif
    };
}

std::string networking::network_address_families::resolve_address_family_to_string(const socket_family_type the_family) {
    
    std::string the_answer;
    
    switch(the_family) {

        case (AF_UNSPEC) : {
            the_answer = networking::network_address_families::unspec_address_family;
            break;
        }

        case (AF_INET) : {
            the_answer = networking::network_address_families::ip_version4_address_family;
            break;
        }

        case (AF_INET6) : {
            the_answer = networking::network_address_families::ip_version6_address_family;
            break;
        }

        #if defined(unix_os)

            #if defined(mac_os)
                case (AF_LINK) : {
                    the_answer = networking::network_address_families::link_layer_address_family;
                    break;
                }
            #else
                case (AF_NETLINK) : {
                    the_answer = networking::network_address_families::packet_address_family;
                    break;
                }

                case (AF_PACKET) : {
                    the_answer = networking::network_address_families::packet_address_family;
                    break;
                }
            #endif

        #else

            case (AF_NETBIOS) : {
                the_answer = networking::network_address_families::netbios_address_family;
                break;
            }

            case (AF_IRDA) : {
                the_answer = networking::network_address_families::irda_address_family;
                break;
            }

            case (AF_BTH) : {
                the_answer = networking::network_address_families::bluetooth_address_family;
                break;
            }

        #endif

        default : {
            the_answer = network_address_families::unrecognized_address_family;
            break;
        }

    }

    return the_answer;
}

std::unordered_set<std::string> networking::resolve_hostname(const std::string hostname, const std::string port, const bool name) {
    const bool was_init = networking::network_init;

    if (not networking::initialize_network()) {
        throw networking::exceptions::initialize_network_failure("Failed to initialize the network to resolve the hostname \"" + hostname + "\"", unpack_exception_parameters(1));
    }

    std::unordered_set<std::string> the_answer;

    struct addrinfo hints, *current, *all_addresses;

    char buffer[__buffer_size__];
    std::memset(buffer, 0, __buffer_size__);
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_flags = AI_ALL;

    if (getaddrinfo(hostname.c_str(), port.c_str(), &hints, &all_addresses)) {
        (not was_init) ? uninitialize_network() : true;
        throw networking::exceptions::getaddrinfo_failure("Failed to retrieve address information for host \"" + hostname + "\"", unpack_exception_parameters(2));
    }

    for (current = all_addresses; current; current = current->ai_next) {

        if (not getnameinfo(current->ai_addr, current->ai_addrlen, buffer, __buffer_size__, 0, 0, NI_NUMERICHOST | AI_ALL)) {
            the_answer.insert(std::string(buffer));
        }

        if (name) {
            if (not getnameinfo(current->ai_addr, current->ai_addrlen, buffer, __buffer_size__, 0, 0, NI_NAMEREQD | AI_ALL)) {
                the_answer.insert(std::string(buffer));
            }
        }
    }

    freeaddrinfo(all_addresses);

    if (not was_init) {
        networking::uninitialize_network();
    }
    return the_answer;
}

std::unordered_map<std::string, std::unordered_map<std::string, std::set<std::string> > > networking::machine_adapters(const bool names) {
    typedef std::unordered_map<std::string, std::set<std::string> > answer_data_type;
    std::unordered_map<std::string, answer_data_type> the_answer;

    const bool was_init = networking::network_init;

    if (not networking::initialize_network()) {
        throw networking::exceptions::initialize_network_failure("Failed to initialize the network to retrieve the adapters for this machine", unpack_exception_parameters(1));
    }

    adapter_type all_adapters;

    #if defined(crap_os)
        all_adapters = NULL;
        DWORD memory_size = 20000;

        while (not all_adapters) {
            all_adapters = (adapter_type) malloc(memory_size);
            if (not all_adapters) {
                (not was_init) ? networking::uninitialize_network() : true;
                throw networking::exceptions::memory_exception_failure("Failed to allocate meory to hold the adapter information", unpack_exception_parameters(3));
            }

            int response = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, all_adapters, &memory_size);

            if (response == ERROR_BUFFER_OVERFLOW) {
                free_adapters(all_adapters);
            }

            else if (response == ERROR_SUCCESS) {
                break;
            }

            else {
                (not was_init) ? networking::uninitialize_network() : true;
                throw networking::exceptions::unexpected_failure("Failed to retrieve machine's adapter address information", unpack_exception_parameters(12));
            }
        }
    #else
        if (getifaddrs(&all_adapters)) {
            (not was_init) ? networking::uninitialize_network() : true;
            throw networking::exceptions::getifaddrs_failure("Failed to retrieve adapter information for this machine", unpack_exception_parameters(2));
        }
    #endif

    adapter_type this_adapter;
    address_type this_address;
    char buffer[__buffer_size__];
    std::string adapter_name, address_family, address_name;
    
    for (this_adapter = all_adapters; this_adapter; this_adapter = get_next_adapter(this_adapter)) {
        adapter_name = get_adapter_name(this_adapter);

        for (this_address = get_address_from_adapter(this_adapter); this_address; this_address = get_next_address(this_address)) {
            address_family = networking::network_address_families::resolve_address_family_to_string(get_address_family(this_address));
            std::memset(buffer, 0, __buffer_size__);

            switch (getnameinfo(get_address_sockaddr(this_address), get_address_sockaddrlen(this_address), buffer, __buffer_size__, 0, 0, NI_NUMERICHOST)) {

                case 0 : {
                    address_name = std::string(buffer);

                    if (not string_functions::unordered_map_contains<answer_data_type>(adapter_name, the_answer)) {
                        std::set<std::string> new_set = {{address_name}};
                        std::unordered_map<std::string, std::set<std::string> > new_map = {{{address_family, new_set}}};
                        
                        the_answer.insert({adapter_name, new_map});
                    }

                    else if (not string_functions::unordered_map_contains<std::set<std::string> >(address_family, the_answer[adapter_name])) {
                        std::set<std::string> new_set = {address_name};
                        the_answer[adapter_name].insert({address_family, new_set});
                    }

                    else {
                        the_answer[adapter_name][address_family].insert(address_name);
                    }
                }

            }

            if (names) {

                switch (getnameinfo(get_address_sockaddr(this_address), get_address_sockaddrlen(this_address), buffer, __buffer_size__, 0, 0, NI_NAMEREQD)) {

                    case 0 : {
                        address_name = std::string(buffer);

                        if (not string_functions::unordered_map_contains<answer_data_type>(adapter_name, the_answer)) {
                            std::set<std::string> new_set = {{address_name}};
                            std::unordered_map<std::string, std::set<std::string> > new_map = {{{address_family, new_set}}};
                            
                            the_answer.insert({adapter_name, new_map});
                        }

                        else if (not string_functions::unordered_map_contains<std::set<std::string> >(address_family, the_answer[adapter_name])) {
                            std::set<std::string> new_set = {address_name};
                            the_answer[adapter_name].insert({address_family, new_set});
                        }

                        else {
                            the_answer[adapter_name][address_family].insert(address_name);
                        }
                    }

                }

            }
        } // inner for loop
    } // outer for loop
    
    free_adapters(all_adapters);

    return the_answer;
}

bool networking::socket_blocking(const socket_type& the_socket) {
    if (not valid_socket(the_socket)) {
        return false;
    }

    #if defined(crap_os)
        unsigned long mode = 0;
        if (not ioctlsocket(the_socket, FIONBIO, &mode)) {
            return not mode;
        }
    #else
        int flags = fcntl(the_socket, F_GETFL, 0);
        if (flags != 1) {
            return not (flags & O_NONBLOCK);
        }
    #endif
    return false;
}

bool networking::set_blocking(socket_type& the_socket, const bool block) {
    if (not valid_socket(the_socket)) {
        return false;
    }

    #if defined(crap_os)
        unsigned long mode = (block) ? 0 : 1;
        if (ioctlsocket(the_socket, FIONBIO, &mode)) {
            return false;
        }

    #else
        int flags = fcntl(the_socket, F_GETFL, 0);
        if (flags == -1) {
            return false;
        }
        if (fcntl(the_socket, F_SETFL, block ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK)) == -1) {
            return false;
        }
    #endif
    return true;
}

// bool networking::socket_connected(socket_type& the_socket) {
//     if (not valid_socket(the_socket)) {
//         return false;
//     }

//     const bool was_blocking = networking::socket_blocking(the_socket);

//     int retval = 0;
    
//     #if defined(crap_os)
//         u_long mode = 1;
//         ioctlsocket(the_socket, FIONBIO, &mode);
//     #else
//         int flags = fcntl(the_socket, F_GETFL, 0);
//         fcntl(the_socket, F_SETFL, flags | O_NONBLOCK);
//     #endif

//     char buffer[1];
//     retval = recv(the_socket, buffer, 1, MSG_PEEK);

//     if (not retval) {
//         return false; // Connection closed
//     }
//     else if (retval < 0) {
//         #if defined(crap_os)
            
//             if (socket_error != WSAWOULDBLOCK) {
//                 if (was_blocking) {
//                     networking::set_blocking(the_socket, true);
//                 }
//             }
//             return false; // An error occured.
//         #else
//             if (socket_error != EWOULDBLOCK and socket_error != EAGAIN) {
//                 if (was_blocking) {
//                     networking::set_blocking(the_socket, true);
//                 }
//             }
//             return false; // An error occured.
//         #endif
//     }

//     if (was_blocking) {
//         networking::set_blocking(the_socket, true);
//     }
//     return true;
// }

std::string networking::this_machine_name() {
    std::string the_answer;
    #if defined(unix_os)
        
        long max_name = -1;
        #if defined(_POSIX_HOST_NAME_MAX)
            max_name = _POSIX_HOST_NAME_MAX;
        #else
            max_name = sysconf(_SC_HOST_NAME_MAX);
        #endif

        max_name = (max_name <= 0) ? 3 * __buffer_size__ : max_name + 1;

        the_answer.resize(max_name);
        if (gethostname(the_answer.data(), the_answer.size())) {
            the_answer = "Unknown";
        }
    #else

        #if not defined(MAX_COMPUTERNAME_LENGTH)
            #define MAX_COMPUTERNAME_LENGTH __buffer_size__
        #endif

        the_answer.resize(MAX_COMPUTERNAME_LENGTH + 1);
        DWORD size = the_answer.size();
        if (not GetComputerNameA(the_answer.data(), &size)) {
            the_answer = "Unknown";
        }
    #endif
    the_answer.shrink_to_fit();
    return the_answer;
}

/***********************************************************************************************/



/* network_structures::client_id */

networking::network_structures::client_id::client_id() {}

networking::network_structures::client_id::client_id(const std::string hname, const std::string hport, const std::string ctime_) {
    this->hostname = hname;
    this->port = hport;
    this->connection_time = ctime_;
}

bool networking::network_structures::client_id::operator<(const networking::network_structures::client_id& other) const {
    return this->hostname < other.hostname and 
            (not this->port.empty() and not other.port.empty() ? this->port < other.port : true) and 
                (this->connection_time.empty() and not other.connection_time.empty() ? this->connection_time < other.connection_time : true);
}

bool networking::network_structures::client_id::operator==(const networking::network_structures::client_id& other) const {
    return string_functions::same_string(this->hostname, other.hostname) and 
            ((not this->port.empty() and not other.port.empty()) ? string_functions::same_string(this->port, other.port) : true) and 
                ((not this->connection_time.empty() and not other.connection_time.empty()) ? string_functions::same_string(this->connection_time, other.connection_time) : true);
}

networking::network_structures::client_id::operator bool() const {
    return not this->hostname.empty();
}

networking::network_structures::client_id& networking::network_structures::client_id::operator=(const networking::network_structures::client_id& other) {
    if (this != &other) {
        this->hostname = other.hostname;
        this->port = other.port;
        this->connection_time = other.connection_time;
    }
    return *this;
}

/***********************************************************************************************/



/* network_structures::host_connection */

networking::network_structures::host_connection::host_connection() {}

networking::network_structures::host_connection::host_connection(client_id client_, const socket_type sock_, secure_socket_type sec_sock) {
    this->host_information = client_;
    this->connect_socket = sock_;
    this->secure_connect_socket = sec_sock;
}

bool networking::network_structures::host_connection::operator<(const networking::network_structures::host_connection& other) const {
    return this->host_information < other.host_information;
}

bool networking::network_structures::host_connection::operator==(const networking::network_structures::host_connection& other) const {
    return this->host_information == other.host_information and
                this->connect_socket == other.connect_socket and 
                    (valid_secure_socket(this->secure_connect_socket) and valid_secure_socket(other.secure_connect_socket)) ? this->secure_connect_socket == other.secure_connect_socket : true;
}

networking::network_structures::host_connection::operator bool() const {
    return this->host_information and valid_socket(this->connect_socket);
}

networking::network_structures::host_connection& networking::network_structures::host_connection::operator=(const networking::network_structures::host_connection& other) {
    if (this != &other) {
        this->host_information = other.host_information;
        this->connect_socket = other.connect_socket;
        this->secure_connect_socket = other.secure_connect_socket;
    }
    return *this;
}

/***********************************************************************************************/



/* host_report */

networking::network_structures::host_report::host_report() {}

networking::network_structures::host_report::host_report(const host_connection con_host, bytes total_bytes, const bool succeeded) {
    this->host = con_host;
    this->byte_count = total_bytes;
    this->success = succeeded;
}

networking::network_structures::host_report::host_report(const std::string hname, const std::string hport, const std::string hctime, const socket_type conn_sock, secure_socket_type sec_sock) {
    this->host.host_information.hostname = hname;
    this->host.host_information.port = hport;
    this->host.host_information.connection_time = hctime;
    this->host.connect_socket = conn_sock;
    this->host.secure_connect_socket = sec_sock;
}


bool networking::network_structures::host_report::operator==(const networking::network_structures::host_report& other) const {
    return this->host == other.host and this->byte_count == other.byte_count and this->success == other.success;
}

networking::network_structures::host_report::operator bool() const {
    return this->success;
}

bool networking::network_structures::host_report::operator<(const networking::network_structures::host_report& other) const {
    return this->host < other.host and this->byte_count < other.byte_count;
}

networking::network_structures::host_report& networking::network_structures::host_report::operator=(const networking::network_structures::host_report& other){
    if (this != &other) {
        this->host = other.host;
        this->byte_count = other.byte_count;
        this->success = other.success;
    }
    return *this;
}


/***********************************************************************************************/


/* complete_report */

bool networking::network_structures::complete_report::operator==(const networking::network_structures::complete_report& other) const {
    
    if (this->reports.size() != other.reports.size()) {
        return false;
    }
    if (this->successes != other.successes or this->failures != other.failures) {
        return false;
    }
    unsigned long index;
    for (index = 0; index < this->reports.size(); index++) {
        if (this->reports[index] != other.reports[index]) {
            return false;
        }
    }
    return true;
}

networking::network_structures::complete_report::operator bool() const {
    return not this->reports.empty() and (this->successes or this->failures);
}

bool networking::network_structures::complete_report::operator<(const networking::network_structures::complete_report& other) const {
    if (other.successes < this->successes or other.failures < this->failures) {
        return false;
    }
    return this->reports.size() < other.reports.size();
}

networking::network_structures::host_report& networking::network_structures::complete_report::operator[](const unsigned long index) {
    if (index >= this->reports.size()) {
        throw networking::exceptions::unexpected_failure("Cannot access index " + std::to_string(index) + "\". Can only access an index in range [0, " + std::to_string(this->reports.size()) + ")", unpack_exception_parameters(1));
    }
    return this->reports[index];
}

void networking::network_structures::complete_report::add_report(const host_report new_report) {
    this->reports.push_back(new_report);
    (new_report.success) ? this->successes++ : this->failures++;
}

unsigned long networking::network_structures::complete_report::success() const {
    return this->successes;
}

unsigned long networking::network_structures::complete_report::fails() const {
    return this->failures;
}


/***********************************************************************************************/



/* network_structures::client_connection */

bool networking::network_structures::client_connection::operator==(const networking::network_structures::client_connection& other) const {
    return networking::network_structures::host_connection::operator==(other) and std::memcmp(&this->address_information, &other.address_information, sizeof(this->address_information));
}

/* networking::network_structures::server_connection */
bool networking::network_structures::server_connection::operator==(const networking::network_structures::server_connection& other) const {
    return networking::network_structures::host_connection::operator==(other) and std::memcmp(&this->address_information, &other.address_information, sizeof(this->address_information));
}


/***********************************************************************************************/



/* network_structures::tcp_server */

networking::network_structures::client_connection networking::network_structures::tcp_server::contains_client(const std::string hostname, const std::string port, const std::string connect_time) {
    std::lock_guard<std::mutex> client_check_mutex(this->clients_mutex_);
    networking::network_structures::client_connection the_answer;
    for (const auto& [id, client] : this->clients_) {
        if (string_functions::same_string(id.hostname, hostname)) {
            if (not string_functions::same_string(id.port, port)) {
                continue;
            }

            // They are the same port as well as the same hostname
            // If the connection times are different (and connect_time is not empty)
            //  then it's not the same id
            if (not connect_time.empty()) {
                if (not string_functions::same_string(id.connection_time, connect_time)) {
                    // Not the same
                    continue;
                }
            }
            // FOUND!
            the_answer = client;
            break;
        }
    }
    return the_answer;
}


void networking::network_structures::tcp_server::drop_client(networking::network_structures::client_connection& client) {
    
    valid_secure_socket(client.secure_connect_socket) ? SSL_shutdown(client.secure_connect_socket) : 0;
    (valid_socket(client.connect_socket)) ? close_socket(client.connect_socket) : 0;
    client.connect_socket = invalid_socket;
    valid_secure_socket(client.secure_connect_socket) ? SSL_free(client.secure_connect_socket) : (void) 0;
    client.secure_connect_socket = invalid_secure_socket;
    client = {};
}


bool networking::network_structures::tcp_server::create_context() {
    std::lock_guard<std::mutex> context_lock(this->context_mutex_);
    if (this->secure_ and not valid_context(this->context_)) {
        // std::printf("Creating secure connection context.\n");
        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        // Initialize the network
        // network_init
        if (not networking::network_init) {

            // Deals with init_mutex lock
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network (windows crap).", unpack_exception_parameters(1));
            }
            this->was_init_ = false;
        }

        // Initialize the secure library
        // The secure_init is an atomic variable, 
        // but the initialize secure_network is not a thread safe function. 
        // It might need it's own mutex
        if (not secure_init) {
            // Deals with secure_init_mutex lock
            if (not networking::initialize_secure_network()){
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize the secure network. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
            this->was_secure_init_ = false;
        }

        this->context_ = SSL_CTX_new(TLS_server_method());
    }
    return this->secure_ and valid_context(this->context_);
}

bool networking::network_structures::tcp_server::set_cert_and_key() {
    
    // Both atomic bools
    if (this->secure_ and not this->certified_) {
        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        // lock the cert and key file mutexes
        std::unique_lock<std::mutex> cert_lock(this->cert_file_mutex_);
        std::unique_lock<std::mutex> key_lock(this->key_file_mutex_);
        if (this->cert_file_.empty() and this->key_file_.empty()) {
            throw networking::exceptions::use_key_and_cert_failure("Missing certificate and key (files(?)). They are both needed for a secure connection to be established.", unpack_exception_parameters(1));
        }

        if (this->cert_file_.empty()) {
            throw networking::exceptions::certificate_failure("Missing certificate (file). It's needed to establish a secure connection.", unpack_exception_parameters(1));
        }

        if (this->key_file_.empty()) {
            throw networking::exceptions::key_failure("Missing key (file). It's needed to establish a secure connection.", unpack_exception_parameters(1));
        }

        const bool key_exists = std::filesystem::exists(std::filesystem::path(this->key_file_).lexically_normal());
        const bool cert_exists = std::filesystem::exists(std::filesystem::path(this->cert_file_).lexically_normal());

        // TODO: Add a branch that will generate the 
        // key and certs and store them in the `key_file_` and `cert_file`
        // variables if the files don't exist.

        if (not key_exists and not cert_exists) {
            throw networking::exceptions::use_key_and_cert_failure("Key and Cert file paths passed in don't point to any files.", unpack_exception_parameters(1));
        }

        if (not key_exists) {
            throw networking::exceptions::key_failure("Key file path passed in doesn't point to any file.", unpack_exception_parameters(1));
        }

        if (not cert_exists) {
            throw networking::exceptions::certificate_failure("Cert file passed in doesn't point to any file.", unpack_exception_parameters(1));
        }

        if (not this->create_context()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::create_context_failure("Failed to create context for the secure connection. Error \"" + std::string(msg) + "\"", unpack_exception_parameters(2));
        }
        
        // lock the context, key/cert already locked.
        std::lock_guard<std::mutex> context_lock(this->context_mutex_);
        if (not SSL_CTX_use_certificate_file(this->context_, this->cert_file_.c_str(), SSL_FILETYPE_PEM) or not SSL_CTX_use_PrivateKey_file(this->context_, this->key_file_.c_str(), SSL_FILETYPE_PEM)) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::use_key_and_cert_failure("Failed to set the certificate and/or private key to use for a secure connection. Error \"" + std::string(msg) + "\"", unpack_exception_parameters(2));
        }
        this->certified_ = true;
    }
    return this->secure_ and this->certified_;
}

networking::network_structures::tcp_server::tcp_server() :
networking::network_structures::host<networking::network_structures::tcp_server>::host("", default_port, true, true){}


networking::network_structures::tcp_server::tcp_server(const std::string host_name, const std::string port_value, const int listen_lim, const bool secure, const std::string key_file, const std::string cert_file) :
networking::network_structures::host<networking::network_structures::tcp_server>::host(host_name, port_value, true, true) {
    this->listening_limit_ = listen_lim;
    this->secure_ = secure;
    this->key_file_ = key_file;
    this->cert_file_ = cert_file;
}

networking::network_structures::tcp_server::tcp_server(const networking::network_structures::tcp_server& other) :
networking::network_structures::host<networking::network_structures::tcp_server>::host(other) {
    this->listening_limit_.store(other.listening_limit_.load());
    // this->listening_ = other.listening_;
    this->secure_.store(other.secure_.load());
    // this->secure_ = other.secure_;
    this->block_clients_.store(other.block_clients_.load());
    // this->block_clients_ = other.block_clients_;
    this->certified_.store(other.certified_.load());
    // this->certified_ = other.certified_;
    this->listening_.store(other.listening_.load());
    // this->listening_ = other.listening_;
    this->was_secure_init_.store(other.was_secure_init_.load());
    // this->was_secure_init_ = other.was_secure_init_;
    
    // context_type
    this->context_ = other.context_;
    
    // std::string types
    this->key_file_ = other.key_file_;
    this->cert_file_ = other.cert_file_;
}

networking::network_structures::tcp_server::tcp_server(networking::network_structures::tcp_server&& other) noexcept :
networking::network_structures::host<networking::network_structures::tcp_server>::host(std::move(other)) {
    std::scoped_lock move_mutex(
        this->clients_mutex_, this->context_mutex_, this->key_file_mutex_, this->cert_file_mutex_,
        other.clients_mutex_, other.context_mutex_, other.key_file_mutex_, other.cert_file_mutex_
    );

    // bools
    this->listening_.store(other.listening_.load());
    this->secure_.store(other.secure_.load());
    this->block_clients_.store(other.block_clients_.load());
    this->certified_.store(other.certified_.load());
    this->was_secure_init_.store(other.was_secure_init_.load());

    // int
    this->listening_limit_.store(other.listening_limit_.load());

    // Context
    this->context_ = other.context_;

    // strings
    this->key_file_ = std::move(other.key_file_);
    this->cert_file_ = std::move(other.cert_file_);


    // Reassign default values
    other.secure_.store(false);
    other.block_clients_.store(true);
    other.certified_.store(false);
    other.listening_.store(false);
    other.was_secure_init_.store(valid_context(this->context_)); // Dont want to uninitialize network library prematurely
    other.context_ = invalid_context;
}

networking::network_structures::tcp_server::~tcp_server() {
    this->stop();
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::operator=(const networking::network_structures::tcp_server& other) {
    if (this != &other) {
        

        networking::network_structures::host<networking::network_structures::tcp_server>::operator=(other);
        this->listening_limit_.store(other.listening_limit_.load());
        this->secure_.store(other.secure_.load());
        this->block_clients_.store(other.block_clients_.load());
        this->certified_.store(other.certified_.load());
        this->listening_.store(other.listening_.load());
        this->was_secure_init_.store(other.was_secure_init_.load());
        
        std::scoped_lock locks(this->clients_mutex_, this->context_mutex_, this->key_file_mutex_, this->cert_file_mutex_);
        
        // context_type
        this->context_ = other.context_;
        
        // std::string types
        this->key_file_ = other.key_file_;
        this->cert_file_ = other.cert_file_;
    }
    return *this;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::operator=(networking::network_structures::tcp_server&& other) noexcept {
    if (this != &other) {

        networking::network_structures::host<networking::network_structures::tcp_server>::operator=(std::move(other));
        // bools
        this->listening_.store(other.listening_.load());
        this->secure_.store(other.secure_.load());
        this->block_clients_.store(other.block_clients_.load());
        this->certified_.store(other.certified_.load());
        this->was_secure_init_.store(other.was_secure_init_.load());

        // int
        this->listening_limit_.store(other.listening_limit_.load());

        std::scoped_lock move_mutex(
            this->clients_mutex_, this->context_mutex_, this->key_file_mutex_, this->cert_file_mutex_,
            other.clients_mutex_, other.context_mutex_, other.key_file_mutex_, other.cert_file_mutex_
        );

        // Context
        this->context_ = other.context_;

        // strings
        this->key_file_ = std::move(other.key_file_);
        this->cert_file_ = std::move(other.cert_file_);


        // Reassign default values
        other.secure_.store(false);
        other.block_clients_.store(true);
        other.certified_.store(false);
        other.listening_.store(false);
        other.was_secure_init_.store(valid_context(this->context_)); // Dont want to uninitialize network library prematurely
        
        other.context_ = invalid_context;
        other.key_file_ = other.cert_file_ = "";
    }
    return *this;
}

networking::network_structures::tcp_server::operator bool() const {
    std::scoped_lock locks(this->context_mutex_, this->connect_socket_mutex_);
    return (this->secure_) ? valid_context(this->context_) and this->listening_ and valid_socket(this->connect_socket_) : this->listening_ and valid_socket(this->connect_socket_);
}

bool networking::network_structures::tcp_server::secure() const {
    return this->secure_;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::secure(const bool set_secure) {
    if (not *this) {
        this->secure_ = set_secure;
    }
    return *this;
}

std::string networking::network_structures::tcp_server::secure_key() const {
    return this->key_file_;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::secure_key(const std::string new_key) {
    if (not *this) {
        std::lock_guard<std::mutex> key_lock(this->key_file_mutex_);
        this->key_file_ = new_key;
    }
    return *this;
}

std::string networking::network_structures::tcp_server::certificate() const {
    return this->cert_file_;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::certificate(const std::string new_certificate) {
    if (not *this) {
        std::lock_guard<std::mutex> cert_lock(this->cert_file_mutex_);
        this->cert_file_ = new_certificate;
    }
    return *this;
}

int networking::network_structures::tcp_server::listening_limit() const {
    return this->listening_limit_;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::listening_limit(const int new_limit) {
    if (not *this) {
        this->listening_limit_ = (new_limit <= 0) ? 10 : new_limit;
    }
    return *this;
}

bool networking::network_structures::tcp_server::block_clients() const {
    return this->block_clients_;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::block_clients(const bool block_them) {
    this->block_clients_ = block_them;
    return *this;
}

bool networking::network_structures::tcp_server::disconnect_client(networking::network_structures::client_id client, const bool remove_client, const bool double_check) {
    /*  
    Not secure:
        1.) Close the connection socket
        2.) Remove client from clients map. -
        3.) Update max_socket. -

    Secure:
        1.) SSL_shutdown of client's secure socket.
        2.) close client's non-secure socket.
        3.) SSL free client's secure socket.
        4.) Remove client from clients map. -
        5.) Update max socket (non-secure) and max secure socket -
    */
    // bool found = false;
    // networking::network_structures::client_id id_ = client;
    networking::network_structures::client_connection client_;
    bool the_answer = false;
    if (double_check) {
        client_ = this->contains_client(client.hostname, client.port, client.connection_time);
    }
    else {
        client_.host_information = client;
    }
    
    if (client_.host_information) {
        std::lock_guard<std::mutex> disconnect_mutex(this->clients_mutex_);
        networking::network_structures::client_connection connection = this->clients_[client_.host_information];
        the_answer = valid_socket(connection.connect_socket); //networking::socket_connected(connection.connect_socket);
        this->clients_.erase(client_.host_information);
        this->drop_client(connection);
        the_answer = (the_answer and not valid_socket(connection.connect_socket));
        // valid_secure_socket(client.secure_connect_socket) ? SSL_shutdown(client.secure_connect_socket) : 0;
        // (valid_socket(client.connect_socket)) ? close_socket(client.connect_socket) : 0;
        // client.connect_socket = invalid_socket;
        // valid_secure_socket(client.secure_connect_socket) ? SSL_free(client.secure_connect_socket) : (void) 0;
        // client.secure_connect_socket = invalid_secure_socket;
        

        // (this->secure_) ? SSL_shutdown(connection.secure_connect_socket) : 0;
        // the_answer = valid_socket(connection.connect_socket);
        // (valid_socket(connection.connect_socket)) ? close_socket(connection.connect_socket) : 0;
        // (this->secure_) ? SSL_free(connection.secure_connect_socket) : (void) 0;
        // (remove_client) ? this->clients_.erase(client_.host_information) : 0;
    }
    
    return the_answer;
}

bool networking::network_structures::tcp_server::disconnect_client(networking::network_structures::client_connection client) {
    return this->disconnect_client({client.host_information.hostname, client.host_information.port, client.host_information.connection_time});
}

bool networking::network_structures::tcp_server::disconnect_client(const std::string host_name, const std::string port, const std::string time) {
    return this->disconnect_client({host_name, port, time});
}

networking::network_structures::client_connection networking::network_structures::tcp_server::new_client(const bool wait_to_connect, const struct timeval timeout) {
    networking::network_structures::client_connection the_answer;

    if (*this) {

        fd_set reads;
        FD_ZERO(&reads);
        FD_SET(this->connect_socket_, &reads);
        struct timeval timeout_ = {timeout.tv_sec < 0 ? 0 : timeout.tv_sec, timeout.tv_usec < 0 ? 0 : timeout.tv_usec};

        
        std::lock_guard<std::mutex> socket_lock(this->connect_socket_mutex_);
        if (select(this->connect_socket_ + 1, &reads, 0, 0, (wait_to_connect) ? 0 : &timeout_) < 0) {
            throw networking::exceptions::select_failure("Failed to select for the tcp server' actively listening socket.", unpack_exception_parameters(1));
        }

        if (FD_ISSET(this->connect_socket_, &reads)) {
            // std::printf("Accepting new client connection.\n");
            the_answer.address_size = sizeof(the_answer.address_information);

            the_answer.connect_socket = accept(this->connect_socket_, (struct sockaddr*) &the_answer.address_information, &the_answer.address_size);
            the_answer.host_information.connection_time = misc_functions::get_current_time();
            
            if (not valid_socket(the_answer.connect_socket)) {
                throw networking::exceptions::create_connection_socket_failure("Failed to accept the new incoming connection.", unpack_exception_parameters(1));
            }

            // std::printf("Accepted new connection. Now setting connection socket to %s\n", (this->block_clients_) ? "blocking" : "non-blocking");
            networking::set_blocking(the_answer.connect_socket, this->block_clients_);
            
            if (not valid_socket(the_answer.connect_socket)) {
                throw networking::exceptions::create_connection_socket_failure("Failed to set the new connection socket to " + ((this->block_clients_) ? std::string("blocking") : "nonstd::string(-blocking"), unpack_exception_parameters(1));
            }

            // std::printf("Successfully set the connection socket to %s\nNow retrieveing hostname and port number for the connection",  (this->block_clients_) ? "blocking" : "non-blocking");
            char host_buffer[__buffer_size__], port_buffer[__buffer_size__];
            std::memset(host_buffer, 0, __buffer_size__); std::memset(port_buffer, 0, __buffer_size__);
            if (getnameinfo((struct sockaddr*) &the_answer.address_information, the_answer.address_size, host_buffer, __buffer_size__, port_buffer, __buffer_size__, NI_NUMERICHOST | NI_NUMERICSERV)) {
                if (getnameinfo((struct sockaddr*) &the_answer.address_information, the_answer.address_size, host_buffer, __buffer_size__, port_buffer, __buffer_size__, NI_NAMEREQD | AI_ALL)) {
                    this->drop_client(the_answer);
                    throw networking::exceptions::getnameinfo_failure("Failed to retrieve address name information for new incoming connection.", unpack_exception_parameters(3));
                }
            }
            the_answer.host_information.hostname = std::string(host_buffer);
            the_answer.host_information.port = std::string(port_buffer);
            // std::printf("\nSuccessfully retrieved hostname (%s) and port (%s) for the new connection.\n", the_answer.host_information.hostname.c_str(), the_answer.host_information.port.c_str());

            if (this->secure_) {
                const int count = 1;
                char msg[__kilo_bytes__(count)];
                ERR_clear_error();
                
                the_answer.secure_connect_socket = SSL_new(this->context_);
                if (not valid_secure_socket(the_answer.secure_connect_socket)) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    this->drop_client(the_answer);
                    throw networking::exceptions::create_secure_socket_failure("Failed to create a secure socket layer socket for the new connection with cleint \"" + the_answer.host_information.hostname + "\". Error \"" + std::string(msg) + "\"", unpack_exception_parameters(4));
                }
                
                if (not SSL_set_fd(the_answer.secure_connect_socket, the_answer.connect_socket)) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    this->drop_client(the_answer);
                    throw networking::exceptions::create_secure_socket_failure("Failed to set the secure socket layer (SSL) for the socket connecting this tcp server to \"" + the_answer.host_information.hostname + "\". Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(3));
                }
                

                if (SSL_accept(the_answer.secure_connect_socket) != 1) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    this->drop_client(the_answer);
                    throw networking::exceptions::secure_handshake_failure("Failed to establish a secure handshake with new client \"" + the_answer.host_information.hostname + "\". Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(3));
                }
                
            }
            
            std::lock_guard<std::mutex> client_lock(this->clients_mutex_);
            this->clients_.insert({the_answer.host_information, the_answer});
            
        }

    }
    return the_answer;
}

std::unordered_set<networking::network_structures::client_connection> networking::network_structures::tcp_server::clients(const bool all) {
    std::unordered_set<networking::network_structures::client_connection> the_answer;
    if (all) {
        
        std::lock_guard<std::mutex> clients_lock(this->clients_mutex_);
        for (const auto& [id, connection] : this->clients_) {
            the_answer.insert(connection);
        }
    }
    else {
        // std::printf("Checking for clients with data..\n");
        
        if (this->connections()) {
            
            if (this->connections() <= select_poll_threshold) {
                fd_set reads;
                struct timeval timeout = {0, 200};
                FD_ZERO(&reads);
                std::lock_guard<std::mutex> clients_lock(this->clients_mutex_);
                if (this->clients_.empty()) {
                    return the_answer;
                }
                socket_type max_socket = this->clients_.begin()->second.connect_socket;
                for (const auto& [id, connection] : this->clients_) {
                    max_socket = (connection.connect_socket > max_socket) ? connection.connect_socket : max_socket;
                    FD_SET(connection.connect_socket, &reads);
                }

                if (select(max_socket + 1, &reads, 0, 0, &timeout) < 0) {
                    throw networking::exceptions::select_failure("Failed to select for active sockets that are in a listening state.", unpack_exception_parameters(1));
                }

                for (const auto& [id, connection] : this->clients_) {
                    if (FD_ISSET(connection.connect_socket, &reads)) {
                        the_answer.insert(connection);
                    }
                }
            }
            
            else {
                std::vector<pollfd> sockets;
                size_t index;
                std::unordered_map<socket_type, client_id> clients;
                std::lock_guard<std::mutex> clients_lock(this->clients_mutex_);
                for (const auto& [id, client] : this->clients_) {
                    pollfd poll_ = {client.connect_socket, POLLIN, 0};
                    sockets.push_back(poll_);
                    clients.insert({client.connect_socket, id});
                }

                #if defined(crap_os)
                    int results = WSAPoll(sockets.data(), sockets.size(), 0);
                #else
                    int results = poll(sockets.data(), sockets.size(), 0);
                #endif

                if (results < 0) {
                    throw networking::exceptions::select_failure("Failed to poll for client connection sockets that have data to be read from", unpack_exception_parameters(1));
                }

                for (index = 0; index < sockets.size(); index++) {
                    if (sockets[index].revents & POLLIN) {
                        the_answer.insert(this->clients_[clients[sockets[index].fd]]);
                    }
                }
            }
        }
        // std::printf("Done checking for clients with data...\n");
    }
    return the_answer;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::update() {
    std::vector<networking::network_structures::client_id> remove_me;

    std::lock_guard<std::mutex> socket_lock(this->connect_socket_mutex_);
    networking::set_blocking(this->connect_socket_, this->block_);

    std::lock_guard<std::mutex> client_lock(this->clients_mutex_);
    for (auto& [id, client] : this->clients_) {
        if (not valid_socket(client.connect_socket)) {
            remove_me.push_back(id);
            continue;
        }
        networking::set_blocking(client.connect_socket, this->block_);
    }

    for (const auto& id : remove_me) {
        this->disconnect_client(id, true, false);
    }

    return *this;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::start() {
    
    if (not *this) {
        const int count = 1;
        char msg[__kilo_bytes__(count)];

        if (not networking::network_initialized()) {
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize network network (crappy windows).", unpack_exception_parameters(1));
            }
            this->was_init_ = false;
        }

        if (this->secure_) {
            ERR_clear_error();

            // All contain a mutex lock
            if (not networking::secure_network_initialized()) {
                if (not networking::initialize_secure_network()) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::initialize_network_failure("Failed to initialize secure networking library. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
                }
                // std::printf("Initialized the secure network.\n");
                this->was_secure_init_ = false;
            }
            
            // Contains a mutex lock
            if (not this->create_context()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::create_context_failure("Failed to create secure context for this tcp server's secure connection. Error \"" + std::string(msg) + "\"", unpack_exception_parameters(2));
            }

            // Contains a mutex lock
            if (not this->set_cert_and_key()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::use_key_and_cert_failure("Failed to use key and certificate to establish secure connection channels with connected clients. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
            
        }
        
        // Contains mutex lock
        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address to be used for the creation of the connection socket.", unpack_exception_parameters(1));
        }

        // Contains mutex lock
        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create connection socket for this tcp server to listen for connections from.", unpack_exception_parameters(1));
        }

        // From here on, need a socket lock, and a connection lock
        std::scoped_lock connect_locks(this->connect_address_mutex_, this->connect_socket_mutex_);

        // Redundant check
        if (not valid_socket(this->connect_socket_)) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create connection socket for this tcp server to listen for connections from.", unpack_exception_parameters(1));
        }

        #if defined(unix_os)
            int sock = true;
        #else
            char sock = true;
        #endif

        if (setsockopt(this->connect_socket_, SOL_SOCKET, SO_REUSEADDR, &sock, sizeof(sock)) < 0) {
            throw networking::exceptions::socket_information_failure("Failed to set the listeing socket to reusable.", unpack_exception_parameters(1));
        }

        if (bind(this->connect_socket_, this->active_address_->ai_addr, this->active_address_->ai_addrlen)) {
            throw networking::exceptions::bind_socket_failure("Failed to bind the listening socket for this tcp server.", unpack_exception_parameters(1));
        }

        if (listen(this->connect_socket_, this->listening_limit_)) {
            throw networking::exceptions::listening_failure("Failed to start the tcp server listening", unpack_exception_parameters(1));
        }
        this->listening_ = true;
    }

    return *this;
}

networking::network_structures::tcp_server& networking::network_structures::tcp_server::stop() {

    std::scoped_lock stoping_locks(this->clients_mutex_, this->context_mutex_, this->key_file_mutex_, this->cert_file_mutex_);
    for (auto& [name, client] : this->clients_) {
        // this->disconnect_client(name, false);
        this->drop_client(client);
    }

    this->clients_.clear();

    (this->secure_ and this->context_) ? SSL_CTX_free(this->context_) : (void) 0;
    this->context_ = invalid_context;

    this->key_file_ = this->cert_file_ = "";

    
    (not this->was_secure_init_) ? networking::uninitialize_secure_network() : true;
    
    this->close_host();
    this->listening_ = false;

    return *this;
}

bool networking::network_structures::tcp_server::message(const networking::network_structures::client_connection& client, struct timeval timeout) {
    if (not valid_socket(client.connect_socket)) {
        return false;
    }

    fd_set reads;
    FD_ZERO(&reads);
    FD_SET(client.connect_socket, &reads);
    

    if (select(client.connect_socket + 1, &reads, 0, 0, (timeout.tv_sec < 0 or timeout.tv_usec < 0) ? 0 : &timeout) < 0) {
        throw networking::exceptions::select_failure("Failed to select for the connection socket for client \"" + client.host_information.hostname + "\"", unpack_exception_parameters(1));
    }

    return FD_ISSET(client.connect_socket, &reads);
}

unsigned long networking::network_structures::tcp_server::connections() const {
    std::lock_guard<std::mutex> client_lock(this->clients_mutex_);
    return this->clients_.size();
}

bool networking::network_structures::tcp_server::connected(const networking::network_structures::client_connection& client) const {
    if (not client) {
        // std::printf("About to return false from connected(1)\n");
        return false;
    }
    // std::printf("client's socket is %s\n", valid_socket(client.connect_socket) ? "true" : "false");
    // return valid_socket(client.connect_socket);
    std::lock_guard<std::mutex> clients_lock(this->clients_mutex_);
    for (const auto& [host_, info_] : this->clients_) {
        // std::printf("\tInside for loop for connected\n");
        // std::printf("\tAbout to compare\n%s : %s : %s\nAnd\n%s : %s : %s\n", 
        //                 host_.hostname.c_str(), host_.port.c_str(), host_.connection_time.c_str(),
        //                 client.host_information.hostname.c_str(), client.host_information.port.c_str(), client.host_information.connection_time.c_str());
        if (client.host_information == host_) {
            if (valid_socket(info_.connect_socket)) {
                // std::printf("About to return true from connected()\n");
                return true;
            }
        }
    }
    // std::printf("About to return false from connected(2)\n");
    return false;
}

/***********************************************************************************************/


bool networking::network_structures::tcp_client::create_context() {
    std::lock_guard<std::mutex> context_lock(this->context_mutex_);
    if (this->secure_ and not valid_context(this->context_)) {
        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();
        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connection", unpack_exception_parameters(1));
            }
        }

        if (not networking::secure_network_initialized()) {
            this->secure_was_init_ = networking::secure_network_initialized();
            if (not networking::initialize_secure_network()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize secure network library for the tcp client to establish a secure connection to the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }

        this->context_ = SSL_CTX_new(TLS_client_method());
    }
    return this->secure_ and valid_context(this->context_);
}

bool networking::network_structures::tcp_client::connect_socket(const std::chrono::duration<int> timeout) {

    if(not this->connected_) {

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connecion.", unpack_exception_parameters(1));
            }
        }

        if (this->secure_) {
            const int count = 1;
            char msg[__kilo_bytes__(count)];
            ERR_clear_error();

            if (not networking::secure_network_initialized()) {
                this->secure_was_init_ = networking::secure_network_initialized();
                if (not networking::initialize_secure_network()) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::initialize_network_failure("Failed to initialize the secure entworking library for this tcp client to establish a secure connection with the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
                }
            }

            if (not this->create_context()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::create_context_failure("Failed to create secure connection context for the tcp client to use. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }

        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address for the tcp client to use for the creation of a connection socket.", unpack_exception_parameters(1));
        }

        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create the connection socket for this tcp clien to use for establishing a connection to a remote host.", unpack_exception_parameters(1));
        }

        // Consider adding a timeout setting for this aspect of the program
        std::scoped_lock socket_lock(this->connect_socket_mutex_, this->connect_address_mutex_, this->connect_time_mutex_);
        if (not this->block_) {
            if (not networking::set_blocking(this->connect_socket_, this->block_)) {
                throw networking::exceptions::socket_information_failure("Failed to set the connection socket to non-blocking before establishing a connection.", unpack_exception_parameters(1));
            }
            std::printf("Socket is now %s\n", (networking::socket_blocking(this->connect_socket_) ? "blocking" : "non-blocking"));
        }
        int connect_return = connect(this->connect_socket_, this->active_address_->ai_addr, this->active_address_->ai_addrlen);
        if (connect_return) {

            #if defined(unix_os)
                int connect_error = EINPROGRESS;
            #else
                int connect_error = WSAEWOULDBLOCK;
            #endif

            if (not this->block_ and socket_error == connect_error) {
                
                // std::printf("waiting for timeout time again to establish the connection once more.\n");

                fd_set writes;
                FD_ZERO(&writes);
                FD_SET(this->connect_socket_, &writes);
                struct timeval timeout_struct;
                timeout_struct.tv_sec  = std::chrono::duration_cast<std::chrono::seconds>(timeout).count();
                timeout_struct.tv_usec = std::chrono::duration_cast<std::chrono::microseconds>(timeout).count() % 1000000; //C++14+ : 1'000'000;

                // This will wait for the timeout then try again.
                // std::printf("About to use select.\n");
                std::printf("Waiting for %ld.%d seconds\n", timeout_struct.tv_sec, timeout_struct.tv_usec);
                if (select(this->connect_socket_ + 1, 0, &writes, 0, &timeout_struct) < 0) {
                    throw networking::exceptions::connection_failure("Failed to establish a connection and exceeded timeout wait time.", unpack_exception_parameters(1));
                }
                std::printf("Now connecting...\n");
                // std::printf("About to use FD_ISSET.\n");
                if (not FD_ISSET(this->connect_socket_, &writes)) {
                    throw networking::exceptions::connection_failure("Connection socket is not capable of communicating with remote host, even after timeout wait.", unpack_exception_parameters(1));
                }


                #if defined(unix_os)
                    connect_error = 0;
                    socklen_t len = sizeof(connect_error);
                    // std::printf("About to use getsockopt.\n");
                    if (getsockopt(this->connect_socket_, SOL_SOCKET, SO_ERROR, &connect_error, &len) < 0 or connect_error != 0) {
                        throw networking::exceptions::connection_failure("A connection issue occured while trying to establish a connection with the remote machine.", unpack_exception_parameters(1));
                    }
                #else
                // For Windows
                    // int size;
                    // int optlen = sizeof(size);
                    // getsockopt(socket_descriptor, SOL_SOCKET, SO_RCVBUF, (char *)&size, &optlen);
                    char con_err;
                    int con_len = sizeof(con_err);
                    if (getsockopt(this->connect_socket_, SOL_SOCKET, SO_RCVBUF, (char*) &connect_error, &con_len)) {
                        throw networking::exceptions::connection_failure("A connection issue occured while trying to establish a connection with the remote machine.", unpack_exception_parameters(1));
                    }
                #endif
                std::printf("Did getsockopt finished.\n");

            }
            else {
                throw networking::exceptions::connection_failure("Failed to connect this tcp client to the remote host.", unpack_exception_parameters(1));
            }

        }

        this->connect_time_ = misc_functions::get_current_time();
        this->connected_ = true;
    }

    return this->connected_;
}

bool networking::network_structures::tcp_client::create_secure_socket() {
    std::lock_guard<std::mutex> secure_sock_lock(this->secure_socket_mutex_);
    if (this->secure_ and not valid_secure_socket(this->secure_socket_)) {
        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connecion.", unpack_exception_parameters(1));
            }
        }

        if (not networking::secure_network_initialized()) {
            this->secure_was_init_ = networking::secure_network_initialized();
            if (not networking::initialize_secure_network()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize the secure entworking library for this tcp client to establish a secure connection with the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }

        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address for the tcp client to use for the creation of a connection socket.", unpack_exception_parameters(1));
        }

        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create the connection socket for this tcp clien to use for establishing a connection to a remote host.", unpack_exception_parameters(1));
        }

        if (not this->connect_socket()) {
            throw networking::exceptions::connection_failure("Failed to connect the tcp client to the remote host.", unpack_exception_parameters(1));
        }
        this->secure_socket_ = SSL_new(this->context_);
    }

    return this->secure_ and valid_secure_socket(this->secure_socket_);
}

bool networking::network_structures::tcp_client::set_server_name_indication() {

    if (this->secure_ and this->sni_ and not this->server_name_indication_) {
        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connecion.", unpack_exception_parameters(1));
            }
        }
        
        if (not networking::secure_network_initialized()) {
            this->secure_was_init_ = networking::secure_network_initialized();
            if (not networking::initialize_secure_network()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize the secure entworking library for this tcp client to establish a secure connection with the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }
        
        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address for the tcp client to use for the creation of a connection socket.", unpack_exception_parameters(1));
        }
        
        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create the connection socket for this tcp clien to use for establishing a connection to a remote host.", unpack_exception_parameters(1));
        }
        
        if (not this->create_secure_socket()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::create_secure_socket_failure("Failed to create the secure connection socket for encrypted communication with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }
        std::scoped_lock locks(this->secure_socket_mutex_, this->hostname_mutex_);
        if (not SSL_set_tlsext_host_name(this->secure_socket_, this->hostname_.c_str())) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::socket_information_failure("Failed to establish the Server Name Indication (SNI) and choose host to connect to. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }
        
        this->server_name_indication_ = true;
    }

    return this->secure_ and this->sni_ and this->server_name_indication_;
}

bool networking::network_structures::tcp_client::secure_file_descriptor() {

    if (this->secure_ and not this->secure_fd_set_) {

        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connecion.", unpack_exception_parameters(1));
            }
        }

        if (not networking::secure_network_initialized()) {
            this->secure_was_init_ = networking::secure_network_initialized();
            if (not networking::initialize_secure_network()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize the secure entworking library for this tcp client to establish a secure connection with the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }

        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address for the tcp client to use for the creation of a connection socket.", unpack_exception_parameters(1));
        }

        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create the connection socket for this tcp clien to use for establishing a connection to a remote host.", unpack_exception_parameters(1));
        }

        if (not this->create_secure_socket()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::create_secure_socket_failure("Failed to create the secure connection socket for encrypted communication with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        if (this->sni_ and not this->set_server_name_indication()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::connection_failure("Failed to select the hostname for this tcp client to connect to. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }
        std::scoped_lock locks(this->secure_socket_mutex_, this->connect_socket_mutex_);
        if (not SSL_set_fd(this->secure_socket_, this->connect_socket_)) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::connection_failure("Failed to set the socket (file descriptor) for the secure socket to communcate over. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }
        this->secure_fd_set_ = true;
    }
    return this->secure_ and this->secure_fd_set_;
}

bool networking::network_structures::tcp_client::secure_handshake(const std::chrono::duration<int> timeout) {

    if (this->secure_ and not this->secure_handshook_) {

        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connecion.", unpack_exception_parameters(1));
            }
        }

        if (not networking::secure_network_initialized()) {
            this->secure_was_init_ = networking::secure_network_initialized();
            if (not networking::initialize_secure_network()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize the secure entworking library for this tcp client to establish a secure connection with the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }

        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address for the tcp client to use for the creation of a connection socket.", unpack_exception_parameters(1));
        }

        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create the connection socket for this tcp clien to use for establishing a connection to a remote host.", unpack_exception_parameters(1));
        }

        if (not this->create_secure_socket()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::create_secure_socket_failure("Failed to create the secure connection socket for encrypted communication with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        if (this->sni_ and not this->set_server_name_indication()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::connection_failure("Failed to select the hostname for this tcp client to connect to. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }
        std::lock_guard<std::mutex> secure_lock(this->secure_socket_mutex_);
        int result = SSL_connect(this->secure_socket_);
        
        if (result <= 0) {
            int secure_error = SSL_get_error(this->secure_socket_, result);
            
            if (secure_error == SSL_ERROR_ZERO_RETURN) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::accept_secure_connection_failure("Failed to establish a secure handshake with remote host. Error \"", unpack_secure_exception_parameters(2));
            }

            if (secure_error == SSL_ERROR_SYSCALL) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::connection_failure("Fatal system call error has occured. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }

            if (secure_error == SSL_ERROR_SSL) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::accept_secure_connection_failure("SSL/TLS secure handshake protocol failure. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }

            const auto& start_time = std::chrono::steady_clock::now();
            while ((secure_error == SSL_ERROR_WANT_READ) or (secure_error == SSL_ERROR_WANT_WRITE)) {
                
                if (std::chrono::steady_clock::now() - start_time > timeout) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::connection_failure("Failed to establish a secure connection handshake. Connection attempt timed out. Error\"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
                }
                result = SSL_connect(this->secure_socket_);
                
                if (result == 1) {
                    break;
                }
                
                secure_error = SSL_get_error(this->secure_socket_, result);
                if (secure_error == SSL_ERROR_ZERO_RETURN) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::accept_secure_connection_failure("Failed to establish a secure handshake with remote host. Error \"", unpack_secure_exception_parameters(2));
                }

                else if (secure_error == SSL_ERROR_SYSCALL) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::connection_failure("Fatal system call error has occured. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
                }

                else if (secure_error == SSL_ERROR_SSL) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::accept_secure_connection_failure("SSL/TLS secure handshake protocol failure. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
                }
            }

            if (result <= 0) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::connection_failure("Failed to establish a secure connection handshake. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }
        this->secure_handshook_ = true;
    }
    return this->secure_ and this->secure_handshook_;
}

bool networking::network_structures::tcp_client::get_cipher() {

    std::lock_guard<std::mutex> cipher_lock(this->cipher_mutex_);
    if (this->secure_ and this->cipher_.empty()) {

        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connecion.", unpack_exception_parameters(1));
            }
        }

        if (not networking::secure_network_initialized()) {
            this->secure_was_init_ = networking::secure_network_initialized();
            if (not networking::initialize_secure_network()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize the secure entworking library for this tcp client to establish a secure connection with the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }

        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address for the tcp client to use for the creation of a connection socket.", unpack_exception_parameters(1));
        }

        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create the connection socket for this tcp clien to use for establishing a connection to a remote host.", unpack_exception_parameters(1));
        }

        if (not this->create_secure_socket()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::create_secure_socket_failure("Failed to create the secure connection socket for encrypted communication with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        if (this->sni_ and not this->set_server_name_indication()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::connection_failure("Failed to select the hostname for this tcp client to connect to. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        if (not this->secure_handshake()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::connection_failure("Failed to establish a secure handshake with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        this->cipher_ = std::string(SSL_get_cipher(this->secure_socket_));
    }
    return this->secure_ and not this->cipher_.empty();
}

bool networking::network_structures::tcp_client::get_peer_certificate() {
    std::lock_guard<std::mutex> cert_lock(this->certificate_mutex_);
    if (this->secure_ and not valid_certificate(this->secure_socket_)) {

        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network for this tcp client to utilize for a secure connecion.", unpack_exception_parameters(1));
            }
        }

        if (not networking::secure_network_initialized()) {
            this->secure_was_init_ = networking::secure_network_initialized();
            if (not networking::initialize_secure_network()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::initialize_network_failure("Failed to initialize the secure entworking library for this tcp client to establish a secure connection with the remote server. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
        }

        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create the connection address for the tcp client to use for the creation of a connection socket.", unpack_exception_parameters(1));
        }

        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create the connection socket for this tcp clien to use for establishing a connection to a remote host.", unpack_exception_parameters(1));
        }

        if (not this->create_secure_socket()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::create_secure_socket_failure("Failed to create the secure connection socket for encrypted communication with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        if (this->sni_ and not this->set_server_name_indication()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::connection_failure("Failed to select the hostname for this tcp client to connect to. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        if (not this->secure_handshake()) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::connection_failure("Failed to establish a secure handshake with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

        this->certificate_ = SSL_get_peer_certificate(this->secure_socket_);
        if (not valid_certificate(this->certificate_)) {
            ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
            throw networking::exceptions::certificate_failure("Failed to retrieve peer certificate. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
        }

    }

    return this->secure_ and not valid_certificate(this->secure_socket_);
}


// Parameter Constructor
networking::network_structures::tcp_client::tcp_client(const std::string host_name, const std::string port, const bool secure, const bool sni) :
networking::network_structures::host<networking::network_structures::tcp_client>::host(host_name, port, true, false) {
    this->secure_ = secure;
    this->sni_ = sni;
}


// Copy Constructor
networking::network_structures::tcp_client::tcp_client(const networking::network_structures::tcp_client& other) :
networking::network_structures::tcp_client::host<networking::network_structures::tcp_client>::host(other) {

    // bools
    this->secure_.store(other.secure_.load());
    this->secure_was_init_.store(other.secure_was_init_.load());
    this->connected_.store(other.connected_.load());
    this->secure_fd_set_.store(other.secure_fd_set_.load());
    this->secure_connected_.store(other.secure_connected_.load());
    this->secure_handshook_.store(other.secure_handshook_.load());
    this->server_name_indication_.store(other.server_name_indication_.load());
    this->sni_.store(other.sni_.load());

    std::scoped_lock locks(
        this->context_mutex_, 
        this->secure_socket_mutex_, 
        this->certificate_mutex_,
        this->connect_time_mutex_, 
        this->cipher_mutex_,
        other.context_mutex_, 
        other.secure_socket_mutex_, 
        other.certificate_mutex_,
        other.connect_time_mutex_, 
        other.cipher_mutex_
    );

    // pointers
    this->context_ = other.context_;
    this->secure_socket_ = other.secure_socket_;
    this->certificate_ = other.certificate_;

    // std::strings
    this->connect_time_ = other.connect_time_;
    this->cipher_ = other.cipher_;
}


// Move Constructor
networking::network_structures::tcp_client::tcp_client::tcp_client(networking::network_structures::tcp_client&& other) noexcept :
networking::network_structures::tcp_client::host<networking::network_structures::tcp_client>::host(other) {


    // bools
    this->secure_.store(other.secure_.load());
    this->secure_was_init_.store(other.secure_was_init_.load());
    this->connected_.store(other.connected_.load());
    this->secure_fd_set_.store(other.secure_fd_set_.load());
    this->secure_connected_.store(other.secure_connected_.load());
    this->secure_handshook_.store(other.secure_handshook_.load());
    this->server_name_indication_.store(other.server_name_indication_.load());
    this->sni_.store(other.sni_.load());

    std::scoped_lock locks(
        this->context_mutex_, 
        this->secure_socket_mutex_, 
        this->certificate_mutex_,
        this->connect_time_mutex_, 
        this->cipher_mutex_,
        other.context_mutex_, 
        other.secure_socket_mutex_, 
        other.certificate_mutex_,
        other.connect_time_mutex_, 
        other.cipher_mutex_
    );

    // pointers
    this->context_ = other.context_;
    this->secure_socket_ = other.secure_socket_;
    this->certificate_ = other.certificate_;

    // std::strings
    this->connect_time_ = std::move(other.connect_time_);
    this->cipher_ = std::move(other.cipher_);


    // reassignment
    other.secure_ = other.connected_ = other.secure_fd_set_ =
    other.secure_connected_ = other.secure_handshook_ = 
    other.server_name_indication_ = false;
    other.sni_ = other.secure_was_init_ = true;
    
    other.context_ = invalid_context;
    other.secure_socket_ = invalid_secure_socket;
    other.certificate_ = invalid_certificate;
    other.connect_time_ = other.cipher_ = "";
}


// Destructor
networking::network_structures::tcp_client::tcp_client::~tcp_client() {
    this->stop();
}


// Assignment Copy Operator
networking::network_structures::tcp_client& networking::network_structures::tcp_client::operator=(const networking::network_structures::tcp_client& other) {
    if (this != &other) {
        networking::network_structures::host<networking::network_structures::tcp_client>::operator=(other);

        // bools
        this->secure_.store(other.secure_.load());
        this->secure_was_init_.store(other.secure_was_init_.load());
        this->connected_.store(other.connected_.load());
        this->secure_fd_set_.store(other.secure_fd_set_.load());
        this->secure_connected_.store(other.secure_connected_.load());
        this->secure_handshook_.store(other.secure_handshook_.load());
        this->server_name_indication_.store(other.server_name_indication_.load());
        this->sni_.store(other.sni_.load());

        std::scoped_lock locks(
            this->context_mutex_, 
            this->secure_socket_mutex_, 
            this->certificate_mutex_,
            this->connect_time_mutex_, 
            this->cipher_mutex_,
            other.context_mutex_, 
            other.secure_socket_mutex_, 
            other.certificate_mutex_,
            other.connect_time_mutex_, 
            other.cipher_mutex_
        );

        // pointers
        this->context_ = other.context_;
        this->secure_socket_ = other.secure_socket_;
        this->certificate_ = other.certificate_;

        // std::strings
        this->connect_time_ = other.connect_time_;
        this->cipher_ = other.cipher_;
    }
    return *this;
}


// Assignment Move Operator
networking::network_structures::tcp_client& networking::network_structures::tcp_client::operator=(networking::network_structures::tcp_client&& other) noexcept {

    if (this != &other) {

        // bools
        this->secure_.store(other.secure_.load());
        this->secure_was_init_.store(other.secure_was_init_.load());
        this->connected_.store(other.connected_.load());
        this->secure_fd_set_.store(other.secure_fd_set_.load());
        this->secure_connected_.store(other.secure_connected_.load());
        this->secure_handshook_.store(other.secure_handshook_.load());
        this->server_name_indication_.store(other.server_name_indication_.load());
        this->sni_.store(other.sni_.load());

        std::scoped_lock locks(
            this->context_mutex_, 
            this->secure_socket_mutex_, 
            this->certificate_mutex_,
            this->connect_time_mutex_, 
            this->cipher_mutex_,
            other.context_mutex_, 
            other.secure_socket_mutex_, 
            other.certificate_mutex_,
            other.connect_time_mutex_, 
            other.cipher_mutex_
        );

        // pointers
        this->context_ = other.context_;
        this->secure_socket_ = other.secure_socket_;
        this->certificate_ = other.certificate_;

        // std::strings
        this->connect_time_ = std::move(other.connect_time_);
        this->cipher_ = std::move(other.cipher_);


        // reassignment
        other.secure_ = other.connected_ = other.secure_fd_set_ =
        other.secure_connected_ = other.secure_handshook_ = 
        other.server_name_indication_ = false;
        other.sni_ = other.secure_was_init_ = true;
        
        other.context_ = invalid_context;
        other.secure_socket_ = invalid_secure_socket;
        other.certificate_ = invalid_certificate;
        other.connect_time_ = other.cipher_ = "";

    }

    return *this;
}


// Self Check Operator
networking::network_structures::tcp_client::operator bool() const {
    std::scoped_lock locks(this->context_mutex_, this->secure_socket_mutex_, connect_socket_mutex_);
    if (not ((this->secure_) ? valid_context(this->context_) and 
                                valid_secure_socket(this->secure_socket_) and 
                                valid_socket(this->connect_socket_) and 
                                this->connected_
                                        :
                                this->connected_ and valid_socket(this->connect_socket_))) {
        std::printf("About to return false on the self check for the client.\n");
        std::printf("the context is %s\n", valid_context(this->context_) ? "valid" : "invalid");
        std::printf("the secure socket is %s\n", valid_secure_socket(this->secure_socket_) ? "valid" : "invalid");
        std::printf("the connection socket is %s\n", valid_socket(this->connect_socket_) ? "valid" : "invalid");
        }
    return  (this->secure_) ? valid_context(this->context_) and 
                                valid_secure_socket(this->secure_socket_) and 
                                valid_socket(this->connect_socket_) and 
                                this->connected_
                                        :
                                this->connected_ and valid_socket(this->connect_socket_);
}

std::string networking::network_structures::tcp_client::connection_time() const {
    return this->connect_time_;
}

bool networking::network_structures::tcp_client::secure() const {
    return this->secure_;
}

networking::network_structures::tcp_client& networking::network_structures::tcp_client::secure(const bool set_secure) {
    if (not *this) {
        this->secure_ = set_secure;
    }
    return *this;
}

networking::network_structures::tcp_client& networking::network_structures::tcp_client::start(const std::chrono::duration<int> timeout) {
    if (not *this) {
        // Start the client

        std::unique_lock<std::mutex> host_lock(this->hostname_mutex_), port_lock(this->port_mutex_);
        if (this->hostname_.empty()) {
            throw networking::exceptions::unexpected_failure("No hostname specified to connect to.", unpack_exception_parameters(1));
        }

        if (this->portvalue_.empty()) {
            throw networking::exceptions::unexpected_failure("No port value specified to use for the connection to \"" + this->hostname_ + "\"", unpack_exception_parameters(1));
        }


        const int count = 1;
        char msg[__kilo_bytes__(count)];
        ERR_clear_error();

        if (not networking::network_initialized()) {
            this->was_init_ = networking::network_initialized();
            if (not networking::initialize_network()) {
                throw networking::exceptions::initialize_network_failure("Failed to initialize the network. (Crappy windows non sense)", unpack_exception_parameters(1));
            }
        }
        host_lock.unlock();
        port_lock.unlock();
        if (this->secure_) {

            if (not networking::secure_network_initialized()) {
                this->secure_was_init_ = networking::initialize_secure_network();
                if (not networking::initialize_secure_network()) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::initialize_network_failure("Failed to initialize the secure networking library for this tcp client. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
                }
            }

            if (not this->create_context()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::create_context_failure("Failed to create secure connection context for this tcp client to use for a secure connection. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }

        }

        // Now create the address
        if (not this->create_connection_address()) {
            throw networking::exceptions::create_connection_address_failure("Failed to create connection address.", unpack_exception_parameters(1));
        }

        // The socket
        if (not this->create_connection_socket()) {
            throw networking::exceptions::create_connection_socket_failure("Failed to create connection socket for this tcp client to use for establishing a connection to the remote host.", unpack_exception_parameters(1));
        }

        // Connect the socket
        if (not this->connect_socket()) {
            throw networking::exceptions::connection_failure("Failed to connect the client to the remote host over with the newly created socket.", unpack_exception_parameters(1));
        }

        // Redundant check
        if (not valid_socket(this->connect_socket_)) {
            throw networking::exceptions::connection_failure("Failed to connect the client to the remote host over with the newly created socket.", unpack_exception_parameters(1));
        }

        // The rest of this is for a secure connection
        if (this->secure_) {

            // Create a secure socket
            if (not this->create_secure_socket()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::create_secure_socket_failure("Failed to create a secure socket for a secure connection with the remote host. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }

            if (this->sni_) {
                if (not this->set_server_name_indication()) {
                    ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                    throw networking::exceptions::socket_information_failure("Failed to resolve the server name indication. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
                }
            }

            // Set the secure sockets communication socket
            if (not this->secure_file_descriptor()) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::connection_failure("Failed to set the secure socket's network communication socket. Error \"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }

            // Make the secure handshake
            if (not this->secure_handshake(timeout)) {
                ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
                throw networking::exceptions::connection_failure("Failed to establish a secure handshake with the remote host. Error\"" + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
            }
            
        }

    }
    return *this;
}

networking::network_structures::tcp_client& networking::network_structures::tcp_client::stop() {
    if (*this) {

        std::scoped_lock stop_locks(this->certificate_mutex_, this->secure_socket_mutex_, this->context_mutex_);
        (this->secure_ and valid_certificate(this->certificate_)) ? X509_free(this->certificate_) : (void) 0;
        this->certificate_ = invalid_certificate;
        
        (this->secure_ and valid_secure_socket(this->secure_socket_)) ? SSL_shutdown(this->secure_socket_) : 0;
        
        
        (this->secure_ and valid_secure_socket(this->secure_socket_)) ? SSL_free(this->secure_socket_) : (void) 0;
        this->secure_socket_ = invalid_secure_socket;

        (this->secure_ and valid_context(this->context_)) ? SSL_CTX_free(this->context_) : (void) 0;
        
        (not this->secure_was_init_) ? networking::uninitialize_secure_network() : true;
        this->secure_was_init_ = networking::secure_network_initialized();

        this->close_host();
    }
    return *this;
}

std::string networking::network_structures::tcp_client::get_subject() {

    if (not *this) {
        return "";
    }

    if (not this->secure_) {
        return "";
    }

    const int count = 1;
    char msg[__kilo_bytes__(count)];
    ERR_clear_error();
    if (not this->get_peer_certificate()) {
        ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
        throw networking::exceptions::certificate_failure("Failed to retrieve peer certificate to retrieve issuer name." + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
    }
    std::lock_guard<std::mutex> cert_lock(this->certificate_mutex_);
    char* answer;
    std::string the_answer = "";
    if ((answer = X509_NAME_oneline(X509_get_subject_name(this->certificate_), 0, 0))) {
        the_answer = std::string(answer);
        OPENSSL_free(answer);
    }
    return the_answer;
}

std::string networking::network_structures::tcp_client::get_issuer() {

    if (not *this) {
        return "";
    }

    if (not this->secure_) {
        return "";
    }

    const int count = 1;
    char msg[__kilo_bytes__(count)];
    ERR_clear_error();
    if (not this->get_peer_certificate()) {
        ERR_error_string_n(ERR_get_error(), msg, __kilo_bytes__(count));
        throw networking::exceptions::certificate_failure("Failed to retrieve peer certificate to retrieve issuer name." + std::string(msg) + "\"", unpack_secure_exception_parameters(2));
    }
    std::lock_guard<std::mutex> cert_lock(this->certificate_mutex_);
    char* answer;
    std::string the_answer = "";
    if ((answer = X509_NAME_oneline(X509_get_issuer_name(this->certificate_), 0, 0))) {
        the_answer = std::string(answer);
        OPENSSL_free(answer);
    }
    return the_answer;
}

bool networking::network_structures::tcp_client::message() {
    if (not *this) {
        return false;
    }
    std::lock_guard<std::mutex> sock_lock(this->connect_socket_mutex_);
    fd_set reads;
    struct timeval timeout = {0, 0};
    FD_ZERO(&reads);
    FD_SET(this->connect_socket_, &reads);

    if (select(this->connect_socket_ + 1, &reads, 0,  0, &timeout) < 0) {
        throw networking::exceptions::select_failure("Failed to select for the tcp client's listening socket.", unpack_exception_parameters(1));
    }

    return FD_ISSET(this->connect_socket_, &reads);
}

networking::network_structures::server_connection networking::network_structures::tcp_client::connection_information() const {
    networking::network_structures::server_connection the_answer;
    std::scoped_lock locks(this->hostname_mutex_, this->port_mutex_, this->connect_time_mutex_, this->connect_socket_mutex_, this->secure_socket_mutex_, this->active_address_mutex_);
    the_answer.host_information = {this->hostname_, this->portvalue_, this->connect_time_};
    the_answer.connect_socket = this->connect_socket_;
    the_answer.secure_connect_socket = this->secure_socket_;
    the_answer.address_information = *this->active_address_;
    return the_answer;
}

bool networking::network_structures::tcp_client::server_name_indication() {
    return this->sni_;
}

networking::network_structures::tcp_client& networking::network_structures::tcp_client::server_name_indication(const bool set_sni) {
    this->sni_ = set_sni;
    return *this;
}