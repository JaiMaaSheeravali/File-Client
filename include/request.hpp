#pragma once
#include <string>
using std::string;

#define BUFSIZ 8192
#define PORT 2400
#define IP_ADDRESS "127.0.0.1"

class Request
{
private:
    int socket_desc;
    char nack = '1';
    
    string login;
    string password;
    string ftpRequest;
    string transferEndFlag;

    int bytes_left;
    int bytes_sent;
    char *buffer;
    int filefd;
    bool isGlobal;

public:
    Request(int socket_id);

    void handle_request();
    int send_file();
    int delete_file();
    int get_file();
    int rename_file();
    int get_file_list();
    char recvAck();
    int sendDataToServer();
    char* recvDataFromServer();
    void print_help_message();
    void connectToServer();
};