#include "server.h"
#include "client.h"

int main(int argc, char* argv[]) {
    if (argc > 3) {
        client_main(argc, argv);
    } else {
        server_main(argc, argv);
    }

    return 0;
}
