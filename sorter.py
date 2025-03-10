#!/usr/bin/env python3


def variable(variable_name : str, last : bool = True) -> str:
    the_answer = variable_name[variable_name.rindex(' ') + 1: ] if last else variable_name[variable_name.index(' ') + 1 : ]
    return the_answer





VARIABLE_NAMES = f"variables"
FUNCTION_NAMES = f"functions"










save_file = f"sorter_results.dat"

# variables
    # For all
CONNECT_ADDRESS = "struct addrinfo* connect_address"

NEW_CLIENT = "struct sockaddr_storage new_client"

NEW_CLIENT_SIZE = "new_client_length"

HINTS = "struct addrinfo hints"

CONNECT_SOCKET = "socket_type connect_socket"

HOSTNAME, PORTVALUE = "std::string hostname", "std::string port_value"

TIMEOUT = "struct timeval timeout"

TCP, WAS_INIT, SECURE_ = "bool tcp", "bool was_init", "bool secure_"

LISTENING_LIMIT = "int listening_limit"

LISTENING, BOUND = "bool listening", "bool bound"

MAX_SECURE_SOCKET, MAX_SOCKET = "secure_socket_type max_secure_socket", "socket_type max_socket"

CLIENTS = "std::map<connected_host::client_name, connected_host::client> clients"

CERT_FILE, KEY_FILE = "std::string cert_file", "std::string key_file"

BYTES = "int bytes"

BUFFER_SIZE = f"buffer_size"

KILO_BYTE = f"kilo_byte"

EXTRA_KILOBYTE = 2

SENDING_FLAG = 0

MESSAGE_BUFFER = f"char message_buffer[{EXTRA_KILOBYTE} * {KILO_BYTE}]"

READY = f"fd_set ready"






    # For secure
SECURE_INIT = "bool secure_init"

SSL_CONTEXT = "SSL_CTX* context"

SSL_SOCKET = "SSL* secure_socket"

X509_CERTIFICATE = "X509* certificate"






# function calls
    # non secure
INITIALIZE_NETWORK_FUNCTION = lambda : "initialize_network()"

GETADDRINFO_FUNCTION = lambda a = f"this->{variable(HOSTNAME)}.c_str()", \
    b = f"this->{variable(PORTVALUE)}.c_str()", \
        c = f"&{variable(HINTS)}", \
            d = f"&{variable(CONNECT_ADDRESS)}" : \
                f"getaddrinfo({a}, {b}, {c}, {d})"

SOCKET_FUNCTION = lambda a = f"{variable(CONNECT_ADDRESS)}", \
    b = f"{variable(CONNECT_ADDRESS)}", \
        c = f"{variable(CONNECT_ADDRESS)}" : \
            f"socket({a}, {b}, {c})"

BIND_FUNCTION = lambda a = f"{variable(CONNECT_SOCKET)}", \
    b = f"{variable(CONNECT_ADDRESS)}", \
        c = f"{variable(CONNECT_ADDRESS)}" : \
            f"bind({a}, {b}, {c})"

FREEADDRINFO_FUNCTION = lambda addr = f"{variable(CONNECT_ADDRESS)}" : f"freeaddrinfo({addr})"

LISTEN_FUNCTION = lambda s = f"{variable(CONNECT_SOCKET)}",\
    listen_lim = f"{variable(LISTENING_LIMIT)}": f"listen({s}, {listen_lim})"

CONNECT_FUNCTION = lambda a = f"{variable(CONNECT_SOCKET)}", \
    b = f"{variable(CONNECT_ADDRESS)}", \
        c = f"{variable(CONNECT_ADDRESS)}" : \
            f"connect({a}, {b}, {c})"

ACCEPT_FUNCTION = lambda s = f"{variable(CONNECT_SOCKET)}",\
    addr = f"(struct sockaddr*) &{variable(NEW_CLIENT)}->ai_addr", \
        addr_len = f"&{variable(NEW_CLIENT_SIZE)}" : f"accept({s}, {addr}, {addr_len})"

SEND_FUNCTION = lambda socket_val = variable(CONNECT_SOCKET) : f"send({socket_val}, {variable(MESSAGE_BUFFER, False)[ : variable(MESSAGE_BUFFER, False).rindex('[')]}, {EXTRA_KILOBYTE} * {KILO_BYTE}, {SENDING_FLAG})"

RECV_FUNCTION = lambda socket_val = variable(CONNECT_SOCKET) : f"recv({socket_val}, {variable(MESSAGE_BUFFER, False)[ : variable(MESSAGE_BUFFER, False).rindex('[')]}, {EXTRA_KILOBYTE} * {KILO_BYTE}, {SENDING_FLAG})"

FD_ZERO_FUNCTION = lambda ready_name = variable(READY) : f"FD_ZERO({ready_name})"

FD_SET_FUNCTION = lambda fd = variable(CONNECT_SOCKET), \
    ready_read = f"&{variable(READY)}" : f"FD_SET({fd}, {ready_read})"

FD_CLR_FUNCTION = lambda fd = f"{variable(CONNECT_SOCKET)}", \
    read_ready = f"&{variable(READY)}" : f"FD_CLR({fd}, {read_ready})"

SELECT_FUNCTION = lambda sc = f"{variable(MAX_SOCKET)} + 1", \
                    ready_read = f"&{variable(READY)}", \
                        ready_write = f"{0}", \
                            ready_except = f"{0}", \
                                timeout_ = f"&{variable(TIMEOUT)}" \
                                    : f"select({sc}, {ready_read}, {ready_write}, {ready_except}, {timeout_})"

FD_ISSET_FUNCTION = lambda sc = f"{variable(CONNECT_SOCKET)}",\
    ready_read = f"&{variable(READY)}" : f"FD_ISSET({sc}, {ready_read})"
    
CLOSE_SOCKET_FUNCTION = lambda sc : f"close_socket({sc})"

UNINITIALIZE_NETWORK_FUNCTION = lambda : f"uninitialize_network()"




# Secure
SSL_LIBRARY_INIT_FUNCTION = lambda : f"SSL_library_int()"

OPENSSL_ADD_ALL_ALGORITHMS_FUNCTION = lambda : f"OpenSSL_add_all_algorithms()"

SSL_LOAD_ERROR_STRINGS_FUNCTION = lambda : f"SSL_load_error_strings()"

SSL_CTX_NEW_SERVER_FUNCTION = lambda  : f"SSL_CTX_new(TLS_server_method())"

SSL_CTX_NEW_CLIENT_FUNCTION = lambda : f"SSL_CTX_new(TLS_client_method())"

SSL_CTX_USE_CERT_FILE_FUNCTION = lambda cert_ = f"{variable(SSL_CONTEXT)}", \
    cert_file = f"{variable(CERT_FILE)}" : f"SSL_CTX_use_certificate_file({cert_}, {cert_file}, SSL_FILETYPE_PEM)"

SSL_CTX_USE_PRIVATE_KEY_FUNCTION = lambda cert_ = f"{variable(SSL_CONTEXT)}", \
    key_file = f"{variable(KEY_FILE)}" : f"SSL_CTX_use_PrivateKey_file({cert}, {key_file}, SSL_FILETYPE_PEM)"

SSL_NEW_FUNCTION = lambda context_ = 'this->context' : f"SSL_new({context_})"

SSL_SET_TLSEXT_HOST_NAME_FUNCTION = lambda secure_socket_ = variable(SSL_SOCKET), \
    hostname_ = f"this->{variable(HOSTNAME)}" : \
        f"SSL_set_tlsext_host_name({secure_socket_}, {hostname_})"

SSL_SET_FD_FUNCTION = lambda secure_socket_ = f"{variable(SSL_SOCKET)}", \
    socket_ = f"this->{variable(CONNECT_SOCKET)}" : f"SSL_set_fd({secure_socket_}, {socket_})"

SSL_ACCEPT_FUNCTION = lambda secure_socket = f"{variable(SSL_SOCKET)}" : f"SSL_accept({secure_socket})"

SSL_GET_CIPHER_FUNCTION = lambda secure_socket_ = f"{variable(SSL_SOCKET)}" : f"SSL_get_cipher({secure_socket_})"

SSL_GET_PEER_CERTIFICATE_FUNCTION = lambda secure_socket_ = f"{variable(SSL_SOCKET)}" : f"SSL_get_peer_certificate({secure_socket_})"

X509_NAME_ONELINE_FUNCTION = lambda inner_function_ = f"subject", \
    cert_ = f"this->{variable(X509_CERTIFICATE)}", \
        v1 = 0, \
            v2 = 0 : f"X509_NAME_oneline(X509_get_{inner_function_}_name({cert_}), {v1}, {v2}))"
OPENSSL_FREE_FUNCTION = lambda to_free = f"temp" : f"OPENSSL_free({to_free})"

X509_FREE_FUNCTION = lambda cert_ = f"{variable(X509_CERTIFICATE)}" : f"X509_free({cert_})"

SSL_READ_FUNCTION = lambda secure_socket = f"this->{variable(SSL_SOCKET)}", \
    buffer = f"{MESSAGE_BUFFER[0 : MESSAGE_BUFFER.rindex('[') - 1]}", \
        buffer_size = f"{EXTRA_KILOBYTE} * {KILO_BYTE}" : f"SSL_read({secure_socket}, {buffer}, {buffer_size})"

SSL_WRITE_FUNCTION = lambda secure_socket = f"this->{variable(SSL_SOCKET)}", \
    buffer = f"{MESSAGE_BUFFER[0 : MESSAGE_BUFFER.rindex('[') - 1]}", \
        buffer_size = f"{EXTRA_KILOBYTE} * {KILO_BYTE}" : f"SSL_write({secure_socket}, {buffer}, {buffer_size})"

SSL_SHUTDOWN_FUNCTION = lambda secure_socket = f"this->{variable(SSL_SOCKET)}" : \
    f"SSL_shutdown({secure_socket})"

SSL_FREE_FUNCTION = lambda secure_socket = f"this->{variable(SSL_SOCKET)}" : \
    f"SSL_free({secure_socket})"

SSL_CTX_FREE_FUNCTION = lambda context_ = f"this->{variable(SSL_CONTEXT)}" : \
    f"SSL_CTX_free({context_})"



simple_server = {
    
    VARIABLE_NAMES : list(set(
                            HINTS, 
                            CONNECT_ADDRESS, 
                            CONNECT_SOCKET, 
                            READY, 
                            MAX_SOCKET,
                            HOSTNAME,
                            PORTVALUE,
                            CLIENTS,
                            TIMEOUT
                        )),
    FUNCTION_NAMES : list(
                            INITIALIZE_NETWORK_FUNCTION,
                            GETADDRINFO_FUNCTION,
                            SOCKET_FUNCTION, 
                            BIND_FUNCTION, 
                            FREEADDRINFO_FUNCTION, 
                            LISTEN_FUNCTION, 
                            FD_ZERO_FUNCTION, 
                            FD_SET_FUNCTION,
                            SELECT_FUNCTION,
                            FD_ISSET_FUNCTION,
                            ACCEPT_FUNCTION,
                            RECV_FUNCTION,
                            SEND_FUNCTION
                        )
    
}


secure_server = {
    VARIABLE_NAMES : list(set(
                            SSL_CONTEXT,
                            MAX_SECURE_SOCKET,
                            HINTS, 
                            CONNECT_ADDRESS, 
                            CONNECT_SOCKET, 
                            READY, 
                            MAX_SOCKET,
                            HOSTNAME,
                            PORTVALUE,
                            CLIENTS,
                            TIMEOUT
                        )),
    FUNCTION_NAMES : list(
                            INITIALIZE_NETWORK_FUNCTION,
                            SSL_LIBRARY_INIT_FUNCTION,
                            OPENSSL_ADD_ALL_ALGORITHMS_FUNCTION,
                            SSL_LOAD_ERROR_STRINGS_FUNCTION,
                            SSL_CTX_NEW_SERVER_FUNCTION,
                            SSL_CTX_USE_CERT_FILE_FUNCTION,
                            SSL_CTX_USE_PRIVATE_KEY_FUNCTION,
                            GETADDRINFO_FUNCTION,
                            SOCKET_FUNCTION,
                            BIND_FUNCTION,
                            LISTEN_FUNCTION,
                            FD_ZERO_FUNCTION,
                            FD_SET_FUNCTION,
                            SELECT_FUNCTION,
                            FD_ISSET_FUNCTION,
                            ACCEPT_FUNCTION,
                            SSL_NEW_FUNCTION,
                            SSL_SET_FD_FUNCTION,
                            SSL_ACCEPT_FUNCTION,
                            SSL_READ_FUNCTION,
                            SSL_WRITE_FUNCTION,
                            SSL_SHUTDOWN_FUNCTION,
                            CLOSE_SOCKET_FUNCTION,
                            SSL_FREE_FUNCTION,
                            CLOSE_SOCKET_FUNCTION,
                            SSL_CTX_FREE_FUNCTION,
                            UNINITIALIZE_NETWORK_FUNCTION
                        )
}


simple_client = {
    VARIABLE_NAMES : list(set(
                            HINTS,
                            CONNECT_ADDRESS,
                            CONNECT_SOCKET,
                            READY,
                            TIMEOUT
                        )),
    FUNCTION_NAMES : list(
                            
                        )
}


secure_client = {
    VARIABLE_NAMES : [],
    FUNCTION_NAMES : []
}


secure_tls_client = {
    VARIABLE_NAMES : [],
    FUNCTION_NAMES : []
}


print("\n\n")
print(f"INITIALIZE_NETWORK_FUNCTION : ", INITIALIZE_NETWORK_FUNCTION())
print(f"GETADDRINFO_FUNCTION : ", GETADDRINFO_FUNCTION())
print(f"SOCKET_FUNCTION : ", SOCKET_FUNCTION())
print(f"BIND_FUNCTION : ", BIND_FUNCTION())
print(f"FREEADDRINFO_FUNCTION : ", FREEADDRINFO_FUNCTION())
print(f"LISTEN_FUNCTION : ", LISTEN_FUNCTION())
print(f"CONNECT_FUNCTION : ", CONNECT_FUNCTION())
print(f"SEND_FUNCTION : ", SEND_FUNCTION())
print(f"RECV_FUNCTION : ", RECV_FUNCTION())
print(f"SELECT_FUNCTION", SELECT_FUNCTION(f"this->{variable(MAX_SOCKET)} + 1"))
print("\n\n")

host = {
    VARIABLE_NAMES : [],
    FUNCTION_NAMES : []
}


