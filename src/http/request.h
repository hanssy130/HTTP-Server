#ifndef DC_REQUEST_H
#define DC_REQUEST_H

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../dc_lib/unistd.h"

int parse_request(char request[], char file_name[], int* content_type_code, int request_len);

#endif //DC_REQUEST_H
