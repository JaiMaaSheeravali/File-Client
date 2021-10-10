#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../include/request.hpp"
#include "../include/color.hpp"

using namespace std;

int connect(){
    // Create socket:
    int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        cout << RED << "Unable to create socket\n" << RESET;
        return -1;
    }
    

    // Set port and IP the same as server-side:
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    
    // Send connection request to server:
    int server_sock = connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr));

    if(server_sock < 0){
        cout << RED << "Failed: Unable to connect to server\n" << RESET;
        return -1;
    }
    
    return socket_desc;
}