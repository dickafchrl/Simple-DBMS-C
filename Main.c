#include "Library.h"

void printHelp() {
    printf("=======================================================\n");
    printf(" Mesin Ketik - Mini Database Engine\n");
    printf("=======================================================\n");
    printf("Format perintah (diakhiri ';'):\n");
    printf("  SHOW <TABEL>;\n");
    printf("  INSERT <TABEL> <PrimaryKey> <Atribute> <ForeignKey> <ForeignKeySecond>;\n");
    printf("  DELETE <TABEL> <PrimaryKey>;\n");
    printf("  UPDATE <TABEL> <PrimaryKey> <Atribute> <ForeignKey> <ForeignKeySecond>;\n");
    printf("  exit;\n\n");
    printf("<TABEL> salah satu dari: ITEMNAME, TYPE, PRICE\n\n");
    printf("Contoh:\n");
    printf("  INSERT ITEMNAME I01 Baju Pakaian 50000;\n");
    printf("  SHOW ITEMNAME;\n");
    printf("  UPDATE ITEMNAME I01 BajuBaru Pakaian 60000;\n");
    printf("  DELETE ITEMNAME I01;\n");
    printf("=======================================================\n\n");
}

int main() {
    char ribbon[255];

    printHelp();
    while (1) {
        printf("query> ");
        scanf(" %500[^\n]s", ribbon);
        // printf("a%s\n", getCw());

        if (strlen(ribbon) == 0) {
            continue;
        }

        readQuery(ribbon);
        
        reset(ribbon);
        // printf("b%s\n", getCw());
        start(ribbon);
        // printf("c%s\n", getCw());
        if (getCommand() == CMD_EXIT) {
            printf("See ya!\n");
            break;
        }
    }
    
    return 0;
}