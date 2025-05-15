#ifndef REQUEST_H
#define REQUEST_H

#define MAX_METHOD_LEN     8
#define MAX_PATH_LEN       2048
#define MAX_VERSION_LEN    16
#define MAX_HEADER_KEY     64
#define MAX_HEADER_VALUE   1024
#define MAX_HEADERS        32  // Adjust as needed


typedef struct {
    char* key;
    char* value;
} Header;

typedef struct {
    char* method;
    char* uri;
    char* http_version;
    Header headers[MAX_HEADERS];
    int header_count;
    
} Request;

#endif