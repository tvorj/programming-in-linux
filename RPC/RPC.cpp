#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <pthread.h>
#include <sstream>

using namespace std;

struct Client
{
    int client_socket;
    struct sockaddr_in client_address;
};

vector<Client *> clients;

void send_message(const string &mess, int sender_socket)
{
    int sent = send(sender_socket, mess.c_str(), mess.size(), 0);
    if (sent == -1)
    {
        cerr << "Failed to send\n";
    }
}

void *handle(void *arg)
{
    Client *client = (Client *)arg;
    int client_socket = client->client_socket;

    while (true)
    {
        char buffer[1001];
        memset(buffer, 0, sizeof(buffer));

        int rs = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (rs <= 0)
        {
            cerr << "Client disconnected\n";
            close(client_socket);
            delete client;
            pthread_exit(nullptr);
        }

        stringstream out(buffer);
        string op;
        int a, b, result = 0;

        out >> op >> a >> b;

        if (op == "ADD")
        {
            result = a + b;
        }
        else if (op == "SUB")
        {
            result = a - b;
        }
        else if (op == "MUL")
        {
            result = a * b;
        }
        else if (op == "DIV")
        {
            if (b == 0)
            {
                send_message("Division by zero\n", client_socket);
                continue;
            }
            result = a / b;
        }
        else
        {
            send_message("No such operation\n", client_socket);
            continue;
        }

        send_message(to_string(result) + "\n", client_socket);
    }

    close(client_socket);
    return nullptr;
}

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("Socket creation failed");
        exit(errno);
    }

    struct sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8888);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Bind failed");
        exit(errno);
    }

    if (listen(server_socket, 10) < 0)
    {
        perror("Listen failed");
        exit(errno);
    }

    cout << "waiting for connection" << endl;

    while (true)
    {
        int client_socket;
        struct sockaddr_in client_address;
        socklen_t client_addr_len = sizeof(client_address);

        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len);
        if (client_socket < 0)
        {
            perror("Accept failed");
            continue;
        }

        cout << "Client connected: " << inet_ntoa(client_address.sin_addr) << "\n";

        Client *client = new Client{client_socket, client_address};
        clients.push_back(client);

        pthread_t tid;
        pthread_create(&tid, nullptr, handle, (void *)client);
        pthread_detach(tid);
    }

    close(server_socket);
    return 0;
}

