#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <arpa/inet.h>
using namespace std;

#define PORT 8080
#define SA struct sockaddr
#define windowSize 4
#define MAX_PACKETS 12

// Function designed for chat between client and server.
void sender(int connfd)
{
    int clientValue;
    int serverValue;
    int p = 0;

    // till all packets are acknowledged
    for (;;)
    {
        // Clear buffer
        clientValue = 0;
        serverValue = 0;
        int packetCount = 0;

        for (int i = 0; i < windowSize; i++){
            if((p+i) < MAX_PACKETS) cout << "Sent packet : " << (p+i) << endl;
        }

        p += windowSize;

        for (int i = 0; i < windowSize && packetCount < MAX_PACKETS; i++)
        {
            // Read acknowledge message from server
            read(connfd, &clientValue, sizeof(clientValue));
            int temp = p - windowSize;

            cout << "\nPacket " << (temp + i) << ": ";
            if (clientValue == 0) cout << "Not Acknowledged" << endl;
            else cout << "Acknowledged" << endl;

            if (clientValue == 0)
            {
                p = p - (windowSize - i);

                cout << "Resending from Packet: " << p << "\n";
                break;
            }
            if (clientValue == 1)
            {
                packetCount = temp + i + 1;
                // cout << "\nPacket Counts is: " << packetCount << endl;
                continue;
            }
        }
    
        if (packetCount == MAX_PACKETS)
        {
            cout << "ALL PACKETS SENT AND ACKNOWLEDGED" << endl;
            break;
        }
    
        sleep(1);
    }
}

// Driver function
int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;

    // Socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cout << "Socket creation failed..." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Socket successfully created.." << endl;
    }

    bzero(&servaddr, sizeof(servaddr));

    // Assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_addr.s_addr = inet_addr("192.168.143.53");
    servaddr.sin_port = htons(PORT);

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0)
    {
        cout << "Socket bind failed..." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Socket successfully binded.." << endl;
    }

    // Now server is ready to listen and verification
    if ((listen(sockfd, 4)) != 0)
    {
        cout << "Listen failed..." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Server listening.." << endl;
    }

    socklen_t len = sizeof(cli);

    connfd = accept(sockfd, (SA *)&cli, &len);
    if (connfd < 0)
    {
        cout << "Server accept failed..." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Server accept the client..." << endl;
    }

    sender(connfd);

    // close the socket
    close(sockfd);
    return 0;
}