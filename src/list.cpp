#include <iostream>
#include <cstring>
#include <string>
#include <sys/socket.h>

#include "../include/transfer.hpp"

using namespace std;


int getfilelist(int socket_desc){

    cout << recv_string(socket_desc) << endl;
    return 0;
}