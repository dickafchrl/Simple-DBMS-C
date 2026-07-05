/**
 * 
 * 
 */
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

#define MAX_RECORDS 51

typedef struct {
    char PrimaryKey[255]; // Id barang
    char Atribute[255]; // Nama Barang
    char ForeignKey[255]; // ForeignKey
    char ForeignKeySecond[255]; // ForeignKey-2
}dataName;

typedef enum{
    TB_NONE,
    TB_ITEMNAME,
    TB_TYPE,
    TB_PRICE
} TableType;

typedef enum{
    CMD_UNKNOWN,
    CMD_SHOW,
    CMD_INSERT,
    CMD_DELETE,
    CMD_UPDATE,
    CMD_JOIN,
    CMD_EXIT
} Command;


/**
 * Global Parser
 * 
 */
extern int  idx;
extern int  wordlength;
extern char currentWord[255];

/**
 * Sorting
 * 
 */
void swap(dataName *a, dataName *b);
void bubbleSort(int n, dataName *arr);


/**
 *  Parser
 * 
 */
bool eop(char ribbon[]);
void start(char ribbon[]);
void reset(char ribbon[]);
void increment(char ribbon[]);
char* getCw();
int getLength();


/**
 *  search & File I/O
 * 
 */
int sequentialSearch(int n, dataName arr[] ,char target[]);
void readFile (int *n, dataName source[], char fileName[]);
void writeFile(int n, dataName source[], char fileName[]);

/**
 * Query handlers
 * 
 */
void queryInsert(char ribbon[], int *n, dataName source[], char *fileName);
void queryDelete(char ribbon[], int *n, dataName source[], char *fileName);
void queryUpdate(char ribbon[], int n, dataName source[], char *fileName);
void queryShow(dataName source[], char *fileName);

/**
 * Helper
 * 
 */
TableType getTable(char ribbon[]);
Command getCommand();
char* getFileName(TableType table);

void errorTable();
void errorQueryEnd() ;

/**
 * Command Handlers
 * 
 */
void handleShow(char ribbon[]);
void handleInsert(char ribbon[]);
void handleDelete(char ribbon[]);
void handleUpdate(char ribbon[]);
void handleJoin();
void readQuery(char ribbon[]);