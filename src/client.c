#include <netdb.h>
#include <netinet/in.h>
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>


int main(int argc, char *argv[])
{
    // Create the socket to connect to server
    int sfd = dc_socket(AF_INET, SOCK_STREAM, 0);

    // Identify the server socket
    struct sockaddr_in serv_addr;
    struct hostent *hostinfo;
    hostinfo = gethostbyname("127.0.0.1");
    memset(&serv_addr, 0, sizeof(struct sockaddr_in));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(DEFAULT_PORT);
    serv_addr.sin_addr = *(struct in_addr *) hostinfo->h_addr_list[0];

    // Does this go between bind and listen?
    dc_connect(sfd, (struct sockaddr *)&serv_addr, sizeof(struct sockaddr_in));

    ssize_t request_len, reply_len;
    char buf[BUF_SIZE], tmp[BUF_SIZE];
    char end_code[5] = "end";
    while((request_len = dc_read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
    {
        dc_write(sfd, buf, request_len);

        strncpy(tmp, buf, 3); if (strcmp(tmp, end_code) == 0) {break;}
        
        reply_len = dc_read(sfd, buf, BUF_SIZE);
        dc_write(STDOUT_FILENO, buf, reply_len);
                dc_write(STDOUT_FILENO, "err", 4);

    }

    // char* request = "GET / HTTP/1.1\n"
    //                 "Host: 127.0.0.1:6969\n"
    //                 "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:68.0) Gecko/20100101 Firefox/68.0\n"
    //                 "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\n"
    //                 "Accept-Language: en-US,en;q=0.5\n"
    //                 "Accept-Encoding: gzip, deflate\n"
    //                 "Connection: keep-alive\n"
    //                 "Upgrade-Insecure-Requests: 1";
    // request_len = strlen(request);
    // dc_write(sfd, request, request_len);

    // //strncpy(tmp, buf, 3); if (strcmp(tmp, end_code) == 0) {break;}

    // reply_len = dc_read(sfd, buf, BUF_SIZE);
    
    // dc_write(STDOUT_FILENO, buf, reply_len);

    // dc_write(STDOUT_FILENO, "Closing sfd!\n", 14);

    dc_close(sfd);

    return EXIT_SUCCESS;
}
