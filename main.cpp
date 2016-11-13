#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory.h>
#include <zconf.h>

int main() {

    unsigned short port = 4210;
    size_t bufferSize = 1024;

    sockaddr_in socketAddress, cliAddress;
    socklen_t cliAddressSize = sizeof(cliAddress);
    int socketFd, newSocketFd;
    char buffer[bufferSize];
    bool isBufferFull;

    bzero(&socketAddress, sizeof(socketAddress));
    socketAddress.sin_family = AF_INET;
    socketAddress.sin_port = htons(port);
    socketAddress.sin_addr.s_addr = INADDR_ANY;

    if ((socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0) throw;
    if (bind(socketFd, (const sockaddr *) &socketAddress, sizeof(socketAddress)) < 0) throw;
    listen(socketFd, 5);

    if ((newSocketFd = accept(socketFd, (sockaddr *) &cliAddress, &cliAddressSize)) < 0) throw;

    do {
        isBufferFull = read(newSocketFd, buffer, bufferSize-1) == bufferSize-1;
        std::cout << buffer;
    } while(isBufferFull);

    write(newSocketFd, "<h1>Hello</h1>", 14);

    return 0;
}