#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <fstream>

using namespace std;

#define PORT 8080
#define SA struct sockaddr

string readFromFile(const string& filename) {
    ifstream file(filename);
    string content;
    if (file.is_open()) {
        // Read the file content into a string
        string line;
        while (getline(file, line)) {
            content += line; // Append each line to the content string
        }
        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
    }
    return content;
}

void client(int sockfd) {
    // string word = "Umar";
    string path = "./files/";
    int count = 0;
    int k=3; // Number of files

    string word = readFromFile(path + "fileS.txt");
    int wordLength = word.size() + 1; // +1 to include null terminator
    write(sockfd, &wordLength, sizeof(wordLength));
    write(sockfd, word.c_str(), wordLength);

    for(int i=1; i<=k; i++)
    {
        string filePath = path + "file" + to_string(i) + ".txt";
        string sentence = readFromFile(filePath);

        // Send sentence length and sentence
        int sentenceLength = sentence.size() + 1; // +1 to include null terminator
        write(sockfd, &sentenceLength, sizeof(sentenceLength));
        write(sockfd, sentence.c_str(), sentenceLength);
    }
    // Send word length and word

    int frequencies[k+1];
    int size = sizeof(frequencies) / sizeof(frequencies[0]);

    read(sockfd, frequencies, size*sizeof(int));
    cout << "\nTotal Count is: " << frequencies[0] << endl;
    for(int i=1; i<=k; i++)
    {
        cout << "Frequency in file" << i << " : " << frequencies[i] << endl;
    }
    sleep(1);
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
    client(sockfd);

    // close the socket
    close(sockfd);

    return 0;
}