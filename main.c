#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
    int choice;
    do {
        printHello();
        printf("Enter The Choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                adminMenu();
                break;
            case 2:
                break;
            case 3:
                printf("      ========= Thank You ========== \n");
				printf("      ========= See You Soon ======= \n");
				printf("   _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n");
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}

