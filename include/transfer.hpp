#pragma once
#include <string>

using std::string;

int senddata(int socket_desc, const char *buffer, const int size);
int recv_data(int socket_desc, const char* filename);
char* recv_string(int socket_desc);
int getfile(int socket_desc, string &filename);
int sendfile(int socket_desc, string &filename);