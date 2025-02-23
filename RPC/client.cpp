#include <iostream>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <string>

using namespace std;

int client_socket;

void *receive_messages(void *args)
{
    char buffer[1001];
    while (true)
    {
        int rs = recv(client_socket, buffer, 1000, 0);
        if (rs <= 0)
        {
            perror("Connection closed or error");
            close(client_socket);
            exit(-1);
        }
        buffer[rs] = '\0';
        cout << buffer << endl;
    }
    return nullptr;
}

int main()
{
    struct sockaddr_in server_address;
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("socket creation error");
        exit(errno);
    }

    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(8888);

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("connection failed");
        exit(errno);
    }

    pthread_t tid;
    if (pthread_create(&tid, nullptr, receive_messages, nullptr) != 0)
    {
        perror("pthread_create failed");
        exit(errno);
    }

    string message;
    while (true)
    {
        getline(cin, message);
        if (message == "/exit")
        {
            send(client_socket, message.c_str(), message.size(), 0);
            break;
        }
        send(client_socket, message.c_str(), message.size(), 0);
    }

    close(client_socket);
    return 0;
}

