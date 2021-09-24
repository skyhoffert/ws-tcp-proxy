
#include "constants.hpp"

// #include <websocketpp/client.hpp>
// #include <sockpp/acceptor.h>
#include <sockpp/tcp6_connector.h>

#include <iostream>
#include <string.h>
#include <pthread.h>

class Args {
public:
    Args() {
        mode = '?';
        port_in = -1;
        port_out = -1;
        addr_out = new char[kAddrOutLen];
        memset(addr_out, 0, kAddrOutLen);
        mempcpy(addr_out, "::1", 3);
    }
    ~Args() { delete[] addr_out; }
    char mode;
    int port_in;
    int port_out;
    char* addr_out;
};

int ParseArguments(Args* a, int argc, char* argv[]);
void* RunModeW(void* a);
void* RunModeT(void* a);

int main(int argc, char* argv[]) {
    std::cout << "WS TCP Proxy " << kRevision << "." << std::endl;

    Args* args = new Args();
    int retval = ParseArguments(args, argc, argv);

    if (retval != 0) {
        delete args;
        return retval;
    }

    std::cout << "Starting with mode=" << args->mode << ", "
        << "port_in=" << args->port_in << ", "
        << "port_out=" << args->port_out << ", "
        << "addr_out=" << args->addr_out << "." << std::endl;

    pthread_t thread;
    bool exists = false;
    if (args->mode == 'W') {
        if (pthread_create(&thread, NULL, RunModeW, args) != 0) {
            std::cerr << "ERR. Unable to create thread." << std::endl;
            delete args;
            return 201;
        }
        exists = true;
    } else if (args->mode == 'T') {
        if (pthread_create(&thread, NULL, RunModeT, args) != 0) {
            std::cerr << "ERR. Unable to create thread." << std::endl;
            delete args;
            return 202;
        }
        exists = true;
    }

    if (exists) {
        pthread_join(thread, NULL);
    }

    delete args;
    return 0;
}

int ParseArguments(Args* a, int argc, char* argv[]) {
    if (argc < 4) {
        std::cerr << "ERR. Not enough arguments." << std::endl;
        return 100;
    }

    for (int i = 1; i < argc; ++i) {
        if (strlen(argv[i]) >= 8 && memcmp(argv[i], "--mode=", 7) == 0) {
            // Mode argument.

            a->mode = argv[i][7];

            if (a->mode != 'W' && a->mode != 'T') {
                std::cerr << "ERR. Invalid Mode \'" << a->mode << "\'."
                    << std::endl;
                return 101;
            }

        } else if (strlen(argv[i]) >= 14 &&
                memcmp(argv[i], "--port-in=", 10) == 0) {
            // Port In argument.

            a->port_in = atoi(argv[i]+10);

            if (a->port_in < 1024 || a->port_in >= 65535) {
                std::cerr << "ERR. Invalid Port In number." << std::endl;
                return 102;
            }
        
        } else if (strlen(argv[i]) >= 15 &&
                memcmp(argv[i], "--port-out=", 11) == 0) {
            // Port Out argument.

            a->port_out = atoi(argv[i]+11);

            if (a->port_out < 1024 || a->port_out >= 65535) {
                std::cerr << "ERR. Invalid Port Out number." << std::endl;
                return 103;
            }
        
        } else if (strlen(argv[i]) >= 13 &&
                memcmp(argv[i], "--addr-out=", 11) == 0) { 
            // Addr Out argument.

            int len = strlen(argv[i]+11);
            memset(a->addr_out, 0, kAddrOutLen);
            memcpy(a->addr_out, argv[i]+11, len);

        } else {
            // Unknown argument.

            std::cerr << "couldn't parse " << argv[i] << " of length "
                << strlen(argv[i]) << std::endl;
            return 104;

        }
    }

    return 0;
}

void* RunModeW(void* a) {
    std::cerr << "ERR. Mode W not supported." << std::endl;
    pthread_exit(NULL);
}

void* RunModeT(void* a) {
    std::cerr << "ERR. Mode T not supported." << std::endl;
    pthread_exit(NULL);
}
