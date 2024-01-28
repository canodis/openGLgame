#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 8080
#define SERVER_IP "45.87.173.55"

int main() {
    int sockfd;
    struct sockaddr_in servaddr;

    // Soket oluşturma
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        std::cerr << "Socket oluşturulamadı" << std::endl;
        return 1;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Sunucu adres bilgileri
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERVER_PORT);
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Sunucuya bağlanmak için boş bir mesaj gönder
    const char *message = "";
    sendto(sockfd, message, strlen(message), 0, (const struct sockaddr *)&servaddr, sizeof(servaddr));

    // Sunucudan mesaj al
    char buffer[1024];
    recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    std::cout << "Sunucudan alınan mesaj: " << buffer << std::endl;

    close(sockfd);
    return 0;
}
