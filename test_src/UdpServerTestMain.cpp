#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int socket = ::socket(AF_INET, SOCK_DGRAM, 0);
    if (socket < 0)
    {
        std::cout << "Error creating UDP socket" << std::endl;
        exit(1);
    }

    int reuse = 1;
    if (setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0)
    {
        std::cout << "Error setting UDP socket options" << std::endl;
        exit(1);
    }

    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081); 
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0)
    {
        std::cout << "Error converting IP address" << std::endl;
        exit(1);
    }
    if (::bind(socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        std::cout << "Error binding UDP socket: " << strerror(errno) << std::endl;
        exit(1);
    }
    std::cout << "Server is up" << std::endl;
    while (true)
    {
        char buffer[1024];
        struct sockaddr_in senderAddr;
        socklen_t senderAddrLen = sizeof(senderAddr);
        bzero(buffer, sizeof(buffer));
        sleep(1);
        if (recvfrom(socket, buffer, sizeof(buffer), 0, (struct sockaddr *)&senderAddr, &senderAddrLen) < 0)
        {
            std::cout << "Error receiving data from server" << std::endl;
        }
        else
        {
            std::cout << "Received: " << buffer << std::endl;
        }
    }
}
