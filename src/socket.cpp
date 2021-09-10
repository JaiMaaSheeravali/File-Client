#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "../include/request.hpp"

using namespace std;
#define PORT 2400
#define IP_ADDRESS "127.0.0.1"


int connect(){
    int socket_desc;
    struct sockaddr_in server_addr;
    
    // Create socket:
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    
    if(socket_desc < 0){
        cout << "Unable to create socket\n";
        return -1;
    }
    
    cout << "Socket created successfully\n";
    
    // Set port and IP the same as server-side:
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);
    
    // Send connection request to server:
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        cout << "Unable to connect\n";
        return -1;
    }
    cout << "Connected with server successfully\n";
    
    Request request = Request(socket_desc);

    request.handle_request();
    
    return 0;
}