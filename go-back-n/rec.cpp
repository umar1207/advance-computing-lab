#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

using namespace std;
#define PORT 8080
#define SA struct sockaddr
#define windowSize 4
#define MAX_PACKETS 12

void recv(int sockfd)
{
    int clientValue;
    int num = 0;
    for (;;)
    {
        int random = rand() % 2;
        clientValue = random;

        if (clientValue == 0)
        {
            cout << "Packet " << num << ": Not Acknowledged" << endl;
        }
        if (clientValue == 1)
        {
            cout << "Packet " << (num++) << ": Acknowledged" << endl;
        }
       
        write(sockfd, &clientValue, sizeof(clientValue));
        
        if (num == MAX_PACKETS && clientValue == 1)
        {
            cout << "ALL PACKETS ACKNOWLEDGED" << endl;
            break;
        }
        sleep(1);

    }
}

int main()
{
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        cerr << "socket creation failed..." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Socket successfully created.." << endl;
    }

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);

    // connect the client socket to server socket
    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0)
    {
        cerr << "connection with the server failed..." << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "connected to the server.." << endl;
    }

    // function for chat
    recv(sockfd);

    // close the socket
    close(sockfd);

    return 0;
}