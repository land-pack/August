#include <stdlib.h>
#include "server.c"


int
main(int argc, char *argv[])
{
    sayHello();
    createSocketServer();
    exit(EXIT_SUCCESS);
}