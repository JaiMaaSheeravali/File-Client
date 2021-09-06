#pragma once

int senddata(int socket_desc, const char *buffer, const int size);
int recvdata(int socket_desc, char* buffer);