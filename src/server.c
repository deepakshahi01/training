#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "utils.h"

#define PORT 8050

void handle_client(int client_socket) {
    char buffer[1024];
    read(client_socket, buffer, 1024);

    char *method = strtok(buffer, " ");
    char *path = strtok(NULL, " ");

    if (method == NULL || path == NULL) {
        close(client_socket);
        return;
    }

    // Simple routing and parsing: /add?a=1&b=2
    int a = 0, b = 0;
    int result = 0;
    int known_op = 0;

    // Really basic parsing logic for demo purposes
    char op[10] = {0};
    if (strstr(path, "/add")) strcpy(op, "add");
    else if (strstr(path, "/sub")) strcpy(op, "sub");
    else if (strstr(path, "/mul")) strcpy(op, "mul");
    else if (strstr(path, "/div")) strcpy(op, "div");

    if (strlen(op) > 0) {
        char *query = strchr(path, '?');
        if (query) {
            sscanf(query, "?a=%d&b=%d", &a, &b);
            known_op = 1;
        }
    }

    char response[1024];
    if (known_op) {
        if (strcmp(op, "add") == 0) result = add(a, b);
        else if (strcmp(op, "sub") == 0) result = subtract(a, b);
        else if (strcmp(op, "mul") == 0) result = multiply(a, b);
        else if (strcmp(op, "div") == 0) result = divide(a, b);

        sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nResult: %d\n", result);
    } else {
        sprintf(response, "HTTP/1.1 404 Not Found\r\nContent-Type: text/plain\r\n\r\nUnknown operation. Use /add, /sub, /mul, /div with ?a=X&b=Y\n");
    }

    write(client_socket, response, strlen(response));
    close(client_socket);
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d\n", PORT);
    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            continue;
        }
        handle_client(new_socket);
    }
    return 0;
}
