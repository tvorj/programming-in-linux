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

using namespace std;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct Client
{
    int client_socket;
    struct sockaddr_in client_address;
};

vector<Client *> clients;

void send_mess(const char *message, int size, int sender_socket)
{
    pthread_mutex_lock(&mutex);
    for (auto client : clients)
    {
        if (client->client_socket != sender_socket)
        {
            send(client->client_socket, message, size, 0);
        }
    }
    pthread_mutex_unlock(&mutex);
}

void remove_client(Client *cl)
{
    pthread_mutex_lock(&mutex);
    for (auto it = clients.begin(); it != clients.end(); ++it)
    {
        if (*it == cl)
        {
            clients.erase(it);
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
}

void *handle_client(void *arg)
{
    Client *cl = (Client *)arg;
    int client_socket = cl->client_socket;

    char buffer[1001];

    while (true)
    {
        memset(buffer, 0, sizeof(buffer));
        int rs = recv(client_socket, buffer, 1000, 0);
        if (rs <= 0)
        {
            break;
        }
        buffer[rs] = '\0';
        string msg(buffer);
        msg.erase(msg.find_last_not_of("\r\n") + 1);

        if (msg == "/exit")
        {
            string exit_message = "Disconnected.\n";
            send(client_socket, exit_message.c_str(), exit_message.size(), 0);
            break;
        }
        else if (msg == "/list")
        {
            string list_message = "Users: " + to_string(clients.size()) + "\n";
            send(client_socket, list_message.c_str(), list_message.size(), 0);
        }
        else
        {
            send_mess(buffer, rs, client_socket);
        }
    }

    cout << "Client disconnected: " << inet_ntoa(cl->client_address.sin_addr) << "\n";

    close(client_socket);
    remove_client(cl);
    delete cl;
    pthread_exit(nullptr);
}

int main()
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1)
    {
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(8888);

    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("bind failed");
        exit(errno);
    }

    if (listen(server_socket, 10) < 0)
    {
        perror("listen failed");
        exit(errno);
    }
    std::cout << "Waiting for connection\n";

    while (true)
    {
        int client_socket;
        struct sockaddr_in client_address;
        unsigned int client_addr_len = sizeof(client_address);

        if ((client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_addr_len)) < 0)
        {
            perror("accept failed");
            exit(errno);
        }

        Client *cl = new Client;
        cl->client_socket = client_socket;
        cl->client_address = client_address;

        pthread_mutex_lock(&mutex);
        clients.push_back(cl);
        pthread_mutex_unlock(&mutex);

        pthread_t tid;
        if (pthread_create(&tid, nullptr, handle_client, (void *)cl) != 0)
        {
            perror("pthread_create failed");
            continue;
        }
        pthread_detach(tid);

        std::cout << "Connected client with address: " << inet_ntoa(client_address.sin_addr) << "\n";
    }

    close(server_socket);
    pthread_mutex_destroy(&mutex);
    return 0;
}

