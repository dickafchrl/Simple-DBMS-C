#include "Library.h"

int idx = 0;
int wordlength = 0;
char currentWord[255] = "";

/**
 * Sorting
 * 
 *  
 */
void swap(dataName *a, dataName *b) {
    dataName tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubbleSort(int n, dataName *arr) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j].PrimaryKey, arr[j+1].PrimaryKey) > 0) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false) {
            break;
        }
    }
}

/**
 * Parser
 * 
 */

bool eop(char ribbon[]) {
    if (ribbon[idx] == ';') {
        return true;
    } else {
        return false;
    }
}

void reset(char ribbon[]) {
    idx = 0;
    wordlength = 0;
    currentWord[wordlength] = '\0';
}

void increment(char ribbon[]) {
    wordlength = 0;
    currentWord[0] = '\0';

    // ignore blank or space
    while ((ribbon[idx] == ' ') && (ribbon[idx] != '\0')){ 
        idx++;
    }

    while ((eop(ribbon) == false) && (ribbon[idx] != ' ') && (ribbon[idx] != '\0')) {
        currentWord[wordlength] = ribbon[idx];
        wordlength++;
        idx++;
    }
    currentWord[wordlength] = '\0';
}

void start(char ribbon[]) {
    increment(ribbon);
}

char* getCw() {
    return currentWord;
}

int getLength() {
    return wordlength;
}

/**
 * Search
 *  
 * 
 */ 
int sequentialSearch(int n, dataName arr[] ,char target[]) {
    for (int i = 0; i < n; i++) {
        if (strcmp(target, arr[i].PrimaryKey) == 0) {
            return i;
        }
    }
    return -1;
}

/** 
 * File I/O
 * 
 * 
 * 
*/
void readFile (int *n, dataName source[], char fileName[]) {
    FILE *fTemp = fopen(fileName, "r");

    if (fTemp == NULL) {
        *n = 0;
        return;
    }

    while (
        fscanf(
            fTemp, "%s %s %s %s",
            source[*n].PrimaryKey,
            source[*n].Atribute,
            source[*n].ForeignKey,
            source[*n].ForeignKeySecond ) == 4 ) {
        if (strcmp(source[*n].PrimaryKey, "####") == 0) {
            break;
        }
        (*n)++;   
    }

    fclose(fTemp);
}

void writeFile(int n, dataName source[], char fileName[]) {
    FILE *fTemp = fopen(fileName, "w");

    if (fTemp == NULL) {
        printf("\033[91mError: Cannot write into the file %s.\033[0m\n", fileName);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fTemp, "%s %s %s %s\n",
            source[i].PrimaryKey,
            source[i].Atribute,
            source[i].ForeignKey,
            source[i].ForeignKeySecond
        );
    }
    fprintf(fTemp, "%s %s %s %s\n", "####", "####", "####", "####");
    
    fclose(fTemp);
}

/**
 * Query
 * 
 */
char *fieldName[] = {
    "primaryKey",
    "Atribue",
    "ForeignKey",
    "ForeignKeySecond"
};


void queryInsert(char ribbon[], int *n, dataName source[], char *fileName) {
    char temporary[4][255];

    int i = 0;

    while ((eop(ribbon) == false) && (i < 4)) {
        increment(ribbon);

        if (getLength() <= 0) {
            printf("\033[91mError: The %s Field is invalid.\033[0m\n", fieldName[i]);
            return;
        }

        strcpy(temporary[i], getCw());
        i++;
    }

    if (i < 4) {
        printf("\033[91mError: The %s field is invalid.\033[0m\n", fieldName[i + 1]);
        return;
    }
    
    if (*n >= MAX_RECORDS) {
        printf("\033[91mError: Table is full.\033[0m\n");
        return;
    }

    int found = sequentialSearch(*n, source, temporary[0]);
    if (found != -1) {
        printf("\033[91mError: There is the same primary code.\033[0m\n");
        return;
    }
    
    strcpy(source[*n].PrimaryKey, temporary[0]);
    strcpy(source[*n].Atribute, temporary[1]);
    strcpy(source[*n].ForeignKey, temporary[2]);
    strcpy(source[*n].ForeignKeySecond, temporary[3]);

    (*n)++;
    writeFile(*n, source, fileName);
}

void queryDelete(char ribbon[], int *n, dataName source[], char *fileName) {
    char codeDelete[255];

    increment(ribbon);
    strcpy(codeDelete, getCw());
    
    int found = sequentialSearch(*n, source, codeDelete);
    if (found == -1) {
        printf("\033[91mError: Code not found.\033[0m\n");
    }
    
    for (int i = found; i < *n - 1; i++) {                                       // code data hapus di temukan
        strcpy(source[i].PrimaryKey, source[i + 1].PrimaryKey); // lalu code hapus tersebut
        strcpy(source[i].Atribute, source[i + 1].Atribute); // akan di timpa oleh code selanjut nya
        strcpy(source[i].ForeignKey, source[i + 1].ForeignKey);
        strcpy(source[i].ForeignKeySecond, source[i + 1].ForeignKeySecond);
    }

    (*n)--;
    writeFile(*n, source, fileName);
}

void queryUpdate(char ribbon[], int n, dataName source[], char *fileName) {
    char codeUpdate[255];
    char temp[3][255];
    
    increment(ribbon);
    strcpy(codeUpdate, getCw());

    int found = sequentialSearch(n, source, codeUpdate);
    if (found == -1) {
        printf("\033[91mError: Code not found.\033[0m\n");
        return;
    }

    int i = 0;
    while ((eop(ribbon) == false) && (i < 3)) {
        increment(ribbon);
        
        if (getLength() <= 0) {
            printf("\033[91mError: The %s Field is invalid.\033[0m\n", fieldName[i]);
        }

        strcpy(temp[i], getCw());
        i++;
    }

    if (i < 3) {
        printf("\033[91mError: The %s Field is invalid.\033[0m\n", fieldName[i]);
        return;
    }

    strcpy(source[found].Atribute, temp[0]);
    strcpy(source[found].ForeignKey, temp[1]);
    strcpy(source[found].ForeignKeySecond, temp[2]);

    writeFile(n, source, fileName);
}

void queryShow(dataName source[], char *fileName) {
    int n = 0;
    readFile(&n, source, "ItemList.txt");

    if (n == 0) {
        printf("(Table is empty)\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("%s %s %s %s\n",
            source[i].PrimaryKey,
            source[i].Atribute,
            source[i].ForeignKey,
            source[i].ForeignKeySecond
        );
    }
}


/**
 * Helper
 * 
 */
TableType getTable(char ribbon[]) {
    increment (ribbon);
    if(strcmp(getCw(),"ITEMNAME")==0) {
        return TB_ITEMNAME;
    }
    if(strcmp(getCw(),"TYPE")==0) {
        return TB_TYPE;
    }
    if(strcmp(getCw(),"PRICE")==0) {
        return TB_PRICE;
    }

    return TB_NONE;
}

Command getCommand() {
    if(strcmp(getCw(),"SHOW")==0) {
        return CMD_SHOW;
    }

    if(strcmp(getCw(),"INSERT")==0) {
        return CMD_INSERT;
    }

    if(strcmp(getCw(),"DELETE")==0) {
        return CMD_DELETE;
    }

    if(strcmp(getCw(),"UPDATE")==0) {
        return CMD_UPDATE;
    }

    if(strcmp(getCw(),"JOIN")==0) {
        return CMD_JOIN;
    }

    if(strcmp(getCw(),"exit")==0) {
        return CMD_EXIT;
    }

    return CMD_UNKNOWN;
}

char* getFileName(TableType table)  {
    switch (table) {
        case TB_ITEMNAME: 
            return "ItemList.txt";
        case TB_TYPE:      
            return "TypeList.txt";
        case TB_PRICE:     
            return "PriceList.txt";
        default: 
            return NULL;
    }
}

void errorTable() {
    printf("\033[91mError: Query invalid. Use ITEMNAME, TYPE, or PRICE.\033[0m\n");
}

void errorQueryEnd() {
    printf("\033[91mError: The query need end with ';'.\033[0m\n");
}
 
/**
 * Command Handler
 * 
 * 
 */

void handleShow(char ribbon[]) {
    TableType table = getTable(ribbon);
    dataName source[MAX_RECORDS];

    if (table == TB_NONE) {
        errorTable();
        return;
    }

    queryShow(source, getFileName(table));
}

void handleInsert(char ribbon[]) {
    TableType table = getTable(ribbon);
    dataName source[MAX_RECORDS];
    int n = 0;

    if (table == TB_NONE) {
        errorTable();
        return;
    }

    char *fileName = getFileName(table);
    readFile(&n, source, fileName);
    queryInsert(ribbon, &n, source, fileName);
}

void handleDelete(char ribbon[]) {
    TableType table = getTable(ribbon);
    dataName source[MAX_RECORDS];
    int n = 0;

    if (table == TB_NONE) {
        errorTable();
        return;
    }

    char *fileName = getFileName(table);
    readFile(&n, source, fileName);
    queryDelete(ribbon, &n, source, fileName);
}

void handleUpdate(char ribbon[]) {
    TableType table = getTable(ribbon);
    dataName source[MAX_RECORDS];
    int n = 0;

    if (table == TB_NONE) {
        errorTable();
        return;
    }

    char *fileName = getFileName(table);
    readFile(&n, source, fileName);
    queryUpdate(ribbon, n, source, fileName);
}

void handleJoin() {
    /* ToDo */
}

void readQuery(char ribbon[]) {

    reset(ribbon);
    start(ribbon);

    switch(getCommand()) {
        case CMD_SHOW:
            handleShow(ribbon);
            break;

        case CMD_INSERT:
            handleInsert(ribbon);
            break;

        case CMD_DELETE:
            handleDelete(ribbon);
            break;

        case CMD_UPDATE:
            handleUpdate(ribbon);
            break;

        case CMD_JOIN:
            handleJoin();
            break;

        case CMD_EXIT:
            break;

        default:
            printf("\033[91mError: Query unrecognize.\033[0m\n");
            break;
    }
}