#ifndef CONFIG
#define CONFIG

#define CONFIG_MARK '\n'
#define MAX_CONFIG 1000000
#define MAX_LINE 1000
#define MAX_PATH 100

void finishWriteFile();
void startWriteFile(char* path);

void startReadFile(char* path);
void finishReadFile();
void readNext(char* str, char mark, int max);
int strToNumber();

#endif