#include <sys/socket.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket creation failed" << std::endl;
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int i = 0;
    while (true) {
        std::string input = "Input can you hear me";
        // std::getline(std::cin, input);
        sendto(sockfd, input.c_str(), input.length(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        std::cout << "Message sended";
    }
    close(sockfd);

    return 0;
}
