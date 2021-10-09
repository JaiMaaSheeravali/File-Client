#include <iostream>

#include "../include/socket.hpp"
#include "../include/request.hpp"
using namespace std;


int main(void)
{
    
    int socket_desc = connect();

    if(socket_desc == -1){
        cerr << "Error Creating Socket Exiting!\n";
        return -1;
    }

    Request request = Request(socket_desc);
    request.handle_request();

    return 0;
}
