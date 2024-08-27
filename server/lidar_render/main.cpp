#include "Websocket.h"

int main(int argc, char *argv[])
{
    Websocket *web = new Websocket();
    // Check command line arguments.
    if (argc != 4)
    {
        std::cerr << "Usage: http-server-sync <address> <port> <doc_root>\n"
                  << "Example:\n"
                  << "    http-server-sync 0.0.0.0 8080 .\n";
        return EXIT_FAILURE;
    }
    std::string arg;
    arg.assign(argv[1]);
    web->insertParam("address", arg);
    web->insertParam("port", atoi((const char *)argv[2]));
    arg.assign(argv[3]);
    web->insertParam("doc_root", arg);
    
    web->run();
    web->join();
}
