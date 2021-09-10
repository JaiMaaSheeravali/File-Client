#pragma once

class Request
{
private:
    int socket_desc;
    
    bool is_authorised = false;

public:
    Request(int socket_id){
        socket_desc = socket_id;
    }

    void handle_request();
    int send_file();
    int delete_file();
    int get_file();
    int rename_file();
    int get_file_list();
    int send_data(const char *buffer, const int size);
    int recv_data(const char* filename);
    char* recv_string();
};