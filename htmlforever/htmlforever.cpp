#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    struct sockaddr_in server_address;

    // create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("socket creation error");
        exit(errno);
    }

    // fill the server ip and port address
    server_address.sin_addr.s_addr = inet_addr("146.190.62.39");
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(80);

    // connect
    int connected = connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    if (connected == -1)
    {
        perror("connection failed");
        exit(errno);
    }

    // send message to server
    std::string mess = "GET / HTTP/1.1\r\nHost: httpforever.com\r\nConnection: close\r\n\r\n";

    int sent = send(client_socket, mess.c_str(), mess.size(), 0);
    if (sent == -1)
    {
        exit(errno);
    }

    ofstream outFile("httpforever.html");
    if (!outFile.is_open())
    {
        cerr << "Failed to open file for writing!" << endl;
        close(client_socket);
        return -1;
    }

    char buffer[3001];
    int rs;
    while ((rs = recv(client_socket, buffer, 3000, 0)) > 0)
    {
        // cout << "Got message" << endl;
        // buffer[rs] = '\0';
        outFile << buffer;
        // cout << buffer << '\n';
    }
    if (rs == -1)
    {
        perror("client socket connection error");
        close(client_socket);
        outFile.close();
        exit(-1);
    }
    if (rs == 0)
    {
        cout << "end of message" << endl;
    }
    outFile.close();
    close(client_socket);
    return 0;
}

