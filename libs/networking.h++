#include "../headers/included.h++"
#include "string_functions.h++"


#if not defined(_NETWORKING_FUNC_)
    #define _NETWORKING_FUNC_


    namespace networking {

        static bool clean_on_except = true;

        namespace {
            #if defined(crap_os)
                bool is_init = false;
            #else
                const bool is_init = true;
                #if defined(mac_os)
                    const std::string rel_adapter = "en0";
                #elif
                    const std::string rel_adapter = "enp0s8";
                #else
                    const std::string rel_adapter = "Wi-Fi 3"
                #endif
            #endif
            const std::string ip6_regex_pattern = std::string("^(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}") + 
                                                    std::string("|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}") +
                                                    std::string("|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}") +
                                                    std::string("){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:)") + 
                                                    std::string("{1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6}") + 
                                                    std::string(")|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}") + 
                                                    std::string("|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}") + 
                                                    std::string("(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1") + 
                                                    std::string("{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))$");
        }

        namespace network_address_families {

            const std::string unspec_address_family = "Unspecific Address family";
            const std::string ip_version4_address_family = "IP Version 4 family";
            const std::string ip_version6_address_family = "IP Version 6 family";

            #if defined(unix_os)
                
                #if defined(mac_os)
                    const std::string link_layer_address_family = "Link-layer Interface Address family";
                #else
                    const std::string netlink_address_family = "Netlink Address family";
                    const std::string packet_address_family = "Packet Address family";
                #endif
            #else
                
                const std::string netbios_address_family = "NetBIOS Address family";
                const std::string irda_address_family = "IrDa Address family";
                const std::string bluetooth_address_family = "Bluetooth Address family";

            #endif

            const std::string unrecognized_address_family = "Unrecognized Address family";


            std::set<std::string> get_address_families();


            std::string resolve_address_family_to_string(socket_family_type the_family);

        }


        namespace exceptions {

            class base_exception {

                protected:
                    std::string except_name, message, file, func;
                    int line;
                
                public:

                    base_exception(const std::string name = "Exception", const std::string msg = "Simple exception thrown", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");

                    ~base_exception() throw();

                    const std::string msg() const;

            };

            class unexpected_exception : public base_exception {
                public:
                    unexpected_exception(const std::string msg = "An unexpected exception has occured", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class memory_exception : public base_exception {
                public:
                    memory_exception(const std::string msg = "A memory exception has occured", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class initialize_network_failure : public base_exception {
                public:
                    initialize_network_failure(const std::string msg = "Failed to initialize the network", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class getaddrinfo_failure : public base_exception {
                public:
                    getaddrinfo_failure(const std::string msg = "Failed to retrieve address information", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class getifaddrs_failure : public base_exception {
                public:
                    getifaddrs_failure(const std::string msg = "Failed to retrieve adapter information", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");

            };

            class create_socket_failure : public base_exception {
                public:
                    create_socket_failure(const std::string msg = "Failed to create a socket", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class bind_socket_failure : public base_exception {
                public:
                    bind_socket_failure(const std::string msg = "Failed to bind the socket", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class listen_socket_failure : public base_exception {
                public:
                    listen_socket_failure(const std::string msg = "Failed to start the socket listening", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class select_failure : public base_exception {
                public:
                    select_failure(const std::string msg = "select function failure", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class getnameinfo_failure : public base_exception {
                public:
                    getnameinfo_failure(const std::string msg = "getnameinfo function failure", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class connect_failure : public base_exception {
                public:
                    connect_failure(const std::string msg = "connection failure", bool print = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class certificate_or_key_error : public base_exception {
                public:
                    certificate_or_key_error(const std::string msg = "A certificate or key failure occured", bool pirnt = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class secure_sockets_layer_error : public base_exception {
                public:
                    secure_sockets_layer_error(const std::string msg = "A secure sockets layer error occured", bool pirnt = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class certificate_error : public base_exception {
                public:
                    certificate_error(const std::string msg = "A certificate error occurred", bool pirnt = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

            class accept_failure : public base_exception {
                public:
                    accept_failure(const std::string msg = "An acception error occurred", bool pirnt = true, const std::string file_name = __FILE__, const int except_line = __LINE__, const std::string function = "Unknown function");
            };

        }

        
        /**
        *
        *   @brief Initialize the network for use.
        *   
        *
        *   @returns `true` if the network is successfully
        *   initialized, `false` otherwise.
        *
        *   @note This only does something on windows machines.
        *
        *
        */
        bool initialize_network();

        
        /**
        *
        *   @brief Uninitialize the network for use.
        *
        *
        *   @returns `true` if the network was successfully 
        *   uninitialized, `false` otherwise.
        *
        *   @note This only does something on windows machines.
        *
        *
        */
        bool uninitialize_network();


        /**
        *
        *
        *   @brief Get the IP address of a hostname
        *
        *   @param hostname (`const std::string`) : The hostname whose IP address is to be retrieved.
        *
        *   @param port (`const std::string`) : Defaults to `DEFAULT_PORT`. The port to be used 
        *   in resolving the hostname.
        *
        *   @returns A `std::vector<std::string>` of the IP addresses associated with the `hostname` passed in.
        *
        *
        */
        std::vector<std::string> resolve_hostname(const std::string hostname, const std::string port = DEFAULT_PORT);


        
        /**
        *
        *
        *   @brief Get the adapters on this machine and return then in the form of a std::map with the characteristics:
        *       std::map<std::string, std::map<std::string, std::vector<std::string> > > : {
        *           adapter name : {
        *                           adapter family : {std::set of adapter addresses for this family}
        *                           }
        *       }
        *
        *
        *   @returns A `std::map<std::string, std::map<std::string, std::set<std::string> > >` with the adapters,
        *   the adapter's adapter families, and their IP addresses.
        *
        */
        std::map<std::string, std::map<std::string, std::vector<std::string> > > this_machine_adapters();


        /**
            @brief Check if the socket is connected or not.
            @param the_socket (`const socket_type`) : The socket to check if it's connected or not.
            @returns `true` if `the_socket` is connected, `false` otherwise.
         */
        bool socket_is_connected(const socket_type the_socket);

        /**
            @brief Check if `the_ip` is an `IP version 4` or an `IP version 6` 
            depending on what the flag `ip4` is set to.

            @param the_ip (`const std::string`) : The IP address to be checked
            @param ip4 (`const bool`) : The IP version to be checked for. If `true`, then it's checked
            to see if it's IP4, otherwise, it's checking for IP6.
            @returns `true` if `the_ip` is IP Version 4 and `ip4` is `true`, or if `the_ip` is IP Version 6 and `ip4` is `false`. `false` otherwise.
         */
        bool is_ipstring(const std::string the_ip, const bool ip4 = true);

        
        namespace network_structures {

            namespace connected_host {
                
                typedef struct client {
                    std::string hostname, portvalue;
                    socket_type connected_socket;
                    secure_sockets_layer_type secure_sockets_layer;
                    secure_sockets_layer_context_type context;

                    struct sockaddr_storage address_info;

                    bool operator<(const client& other) const;
                } client;

                typedef struct server{
                    std::string hostname, portvalue;
                    struct addrinfo address_info;
                    secure_sockets_layer_context_type context;
                    secure_sockets_layer_type secure_socket;

                    bool operator<(const server& other) const;
                } server;

            }

            class host {

                protected:

                    socket_type connect_socket;
                    std::string hostname, portvalue;
                    struct addrinfo* connect_address;
                    struct timeval timeout;
                    bool tcp, was_init, del_on_except, secure_;
                    
                    

                public:

                    host();
                    

                    host(const std::string host_name, const std::string port = DEFAULT_PORT, bool use_tcp = true, long wait_sec = 0, int wait_msec = 100000, bool will_del = true, bool secure = false);

                    
                    ~host();

                    
                    /**
                    *
                    *   @brief Update the `hostname` that this host refers to.
                    *
                    *   @param new_host `const std::string` 
                    *   The new hostname that this host will refer to.
                    *
                    *   
                    *   @returns `true` if the hostname was successfully updated, `false` otherwise
                    *
                    *   @note if the host has address_information, then the hostname will not be updated.
                    *   
                    */
                    bool host_name(const std::string new_host);

                    
                    /**
                    *
                    *   @brief Get the hostname that this host references.
                    *
                    *   @returns `const std::string` The hostname.
                    *
                    */
                    std::string host_name() const;
                    
                    /**
                    *
                    *   @brief Update the port that this host will use for connection.
                    *
                    *
                    *   @param new_port `const std::string` The new port that this host will use.
                    *
                    *
                    *   @note If the host has address_information, then the port will not be updated.
                    */
                    bool port_value(const std::string new_port);

                    
                    /**
                    *
                    *   @brief Get the port value that this host is using.
                    *
                    *   @returns `const std::string` The port value that this host is using.
                    *
                    */
                    std::string port_value() const;

                    
                    /**
                    *
                    *   @brief Creates the address for this host.
                    *
                    *   @returns `true` if the address is fulfilled, `false` otherwise.
                    */
                    bool create_address();

                    
                    /**
                    *
                    *   @brief Creates the socket that this host will use for communication
                    *
                    *   @returns `true` if the socket was successfully created, `false` otherwise.
                    */
                    bool create_socket();

                    
                    /**
                    *
                    *   @brief update the timeout for the select function that is used by the host
                    *   when selecting between different sockets that are in an active state.
                    *
                    *   @param sec `long` The number of seconds that the select function should check for
                    *
                    *   @param m_sec `int` The number of milliseconds that the select function should check for.
                    *   
                    *
                    */
                    void update_timeout(long sec, int m_sec);


                    /**
                    *
                    *   @brief See if this host will delete it's content when an exception is thrown or not.
                    *
                    *   @returns `true` if the host will delete it's content when an exception is thrown,
                    *   `false` otherwise.
                    *
                    */
                    bool will_delete_on_except() const;

                    
                    /**
                    *
                    *
                    *   @brief Tell the host to delete it's content when an exception is thrown or not.
                    *
                    *   @param new_flag `const bool` The flag that will tell the host whether to delete
                    *   it's content or not upon an exception being thrown.
                    *
                    */
                    void will_delete_on_except(const bool new_flag);


                    /**
                    *
                    *   @brief Get the socket that this host is using for commuication.
                    *
                    *
                    *   @returns A `socket_type` of the socket that is being used by this host.
                    *
                    */
                    socket_type get_connection_socket() const;


                    /**
                        @brief Get the secure sockets layers socket that is used for secure connections.
                        @returns The secure_sockets_layer that this host is using 
                            for it's secure connection (provided a secure connection is set up).
                     */
                    secure_sockets_layer_type get_connection_secure_sockets_layers() const;



            };

            class tcp_server : public host {
                private:

                    int listen_lim;
                    bool listening, bound, created_certs;
                    socket_type max_socket;
                    secure_sockets_layer_type max_secure_socket_layer;
                    std::map<socket_type, connected_host::client> clients;
                    const std::string cert_pem_file = "cert.pem", key_pem_file = "key.pem";


                    bool create_certs_for_server();

                public:

                    tcp_server(const std::string host = "", const std::string port = DEFAULT_PORT, int listen_limit = 10, long seconds_wait = 0, int micro_sec_wait = 100000, bool will_del = true, bool secure = false);


                    ~tcp_server();

            };

            class tcp_client : public host {
                private:
                    
                    
                    bool is_connected;


                    bool create_certificate();


                public:

                    tcp_client();


                    tcp_client(const std::string remote_host, const std::string connect_port = DEFAULT_PORT, const long wait_sec = 0, const int wait_msec = 100000, bool will_del = true, bool secure = false);


                    ~tcp_client();

            };

        }

    }


#endif