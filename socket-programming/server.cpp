#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstdlib>
#include <arpa/inet.h>
#include <string>
#include <sstream>

using namespace std;

#define PORT 8080
#define SA struct sockaddr

void server(int connfd) {
    char wordBuffer[256];
    char sentenceBuffer[1024];
    int count = 0;
    int k=3; // Number of files
    int frequencies[k+1];

    // Read word length and word
    int wordLength;
    read(connfd, &wordLength, sizeof(wordLength));
    read(connfd, wordBuffer, wordLength);
    wordBuffer[wordLength] = '\0'; // Ensure null-termination
    string word(wordBuffer);

    // Read sentence length and sentence
    for(int i=1; i<=k; i++)
    {
        int freq = 0;
        int sentenceLength;
        read(connfd, &sentenceLength, sizeof(sentenceLength));
        read(connfd, sentenceBuffer, sentenceLength);
        sentenceBuffer[sentenceLength] = '\0'; // Ensure null-termination
        string sentence(sentenceBuffer);

        stringstream ss(sentence);
        string token;
        while (ss >> token) {
            if (token == word) {
                freq++;
            }
        }

        frequencies[i] = freq;
        count += freq;
    }
    frequencies[0] = count;

    // write the array to the client back 
    int size = sizeof(frequencies) / sizeof(frequencies[0]);
    write(connfd, frequencies, size * sizeof(int));
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

    server(connfd);

    // close the socket
    close(sockfd);
    return 0;
}