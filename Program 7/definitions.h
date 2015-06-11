#ifndef definitions_h
#define definitions_h
#define MAX_CMD_LINE_LENGTH 255
#define MAX_TOKENS_ON_A_LINE 10
#define NUMBER_OF_COMMANDS  9
#define SYSTEM_STATUS       50
#define HALT			    51
#define ADD_NETWORK_NODE    60
#define DELETE_NETWORK_NODE 61
#define CREATE_FILE			70
#define LS					71
#define DELETE_FILES		72
#define PRINT_FILES			73
#define TRANSFER_FILE		80
#define UNDEFINED_COMMAND	99
#define MAX_NETWORK_NODES   10
#define BAD_BLOCK_NUMBER 200
#define NETWORK_FULL 201
#define COMPUTER_NOT_FOUND 202
#define INVALID_COMPUTER_TYPE 203
#define fasdlfkaslfkd 204
#define FILE_SYSTEM_FULL 205
struct fileDescriptor{
char filename[8];
int filelength;
int blocknum;};
#endif