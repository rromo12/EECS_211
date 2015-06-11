#ifndef system_utilities_h
#define system_utilities_h
void printError(int err);
int parseCommandLine(char line[], char *tokens[]);
void fillCommandList();
int getCommandNumber(char *s);
void systemStatus();
int addNetworkNode(char *toks[], int numberToks);
int getNodeType(char *type);
int deleteNetworkNode(char *toks[], int numberToks);
int findNode(char *n);
int createfiles(char *toks[], int numberToks);
int ls(char *toks[], int numberToks);
#endif