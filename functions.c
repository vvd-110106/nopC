#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int userCount = 0;

// Ham in ra menu chao ///////////////////////////////////////////////////////////////////DEREEK//////////////////////////////////////////////////////////////////////////////
void printHello() { 
    printf("\n   *** Bank Management System Using C ***\n");
    printf("               CHOOSE YOUR ROLE \n");
    printf("      ==============================\n");
    printf("      [1]. Admin \n");
    printf("      [2]. User \n");
    printf("      [3]. Exit the Program \n");
    printf("      ==============================\n");
}

// Ham in ra menu quan ly nguoi dung cho Admin ////////////////////////////////////////////DEREEK//////////////////////////////////////////////////////////////////////////
void managerMenu() {
    printf("\n   ===== User Management System =====\n");
    printf("           User Management Menu:\n");
    printf("       [1]. Display user list \n");
    printf("       [2]. Add new user\n");
    printf("       [3]. Sort Users By Name\n");
    printf("       [4]. Search User Name \n");
    printf("       [5]. Search User Id \n");
    printf("       [6]. Unlock ( lock ) User\n");
    printf("       [0]. Exit\n");
}

// Ham kiem tra do dai hop le cua chuoi ////////////////////////////////////////////////////DEREEK////////////////////////////////////////////////////////////////////////////
int checkLeght(char *str) {
    if(str != NULL && strlen(str) > 0);
    return;
}

// Ham kiem tra tinh duy nhat cua thong tin ////////////////////////////////////////////// /DEREEK////////////////////////////////////////////////////////////////////////////
int is_unique(char *name, char *phone, char *email, char *username) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 || strcmp(users[i].phone, phone) == 0 ||
            strcmp(users[i].email, email) == 0) {
            return 0;
        }
    }
    return 1;
}

// Ham hien thi danh sach nguoi dung ////////////////////////////////////////////////////// DEREEK//////////////////////////////////////////////////////////////////////////
void printUsers() {
    FILE *file = fopen("bankData.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    printf("-----------------------------------------------------------------------------------------------------------------");
    printf("\n%-10s | %-20s | %-15s | %-30s | %-15s | %-10s |\n",  "ID", "Name", "Phone Number", "Email", "Username", "Status");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    int found = 0;
    // Doc va in thong tin tung nguoi dung tu file
    while (fread(&tempUser, sizeof(struct User), 1, file) == 1) {
        printf("%-10d | %-20s | %-15s | %-30s | %-15s | %-10s |\n", 
               tempUser.id, tempUser.name, tempUser.phone, tempUser.email, 
               tempUser.username, tempUser.status);
        found = 1;
    }
    if (!found) {
        printf("No users available.\n");
    }
    fclose(file);
}

// Ham them nguoi dung moi va luu vao file /////////////////////////////////////////////////DEREEK/////////////////////////////////////////////////////////////////////////////
void addUser() {
    // Mo file de lay thong tin nguoi dung da co
    FILE *file = fopen("bankData.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    // Doc toan bo nguoi dung hien tai vao mang users
    users = malloc(0);
    userCount = 0;
    while (fread(&tempUser, sizeof(struct User), 1, file)) {
        users = realloc(users, (userCount + 1) * sizeof(struct User));
        users[userCount++] = tempUser;
    }
    fclose(file);
    // Tinh toan ID tiep theo sau khi out chuong trinh
    int nextId;
	if (userCount > 0) {
	    nextId = users[userCount - 1].id + 1;
	} else {
	    nextId = 1; 
	}
    // Cap phat lai bo nho cho mang nguoi dung moi
    users = realloc(users, (userCount + 1) * sizeof(struct User));
    if (users == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    printf("Enter user name: ");
    getchar();
    fgets(newUser.name, sizeof(newUser.name), stdin);
    newUser.name[strcspn(newUser.name, "\n")] = '\0';
    printf("Enter user phone number: ");
    scanf("%s", newUser.phone);
    printf("Enter user email: ");
    scanf("%s", newUser.email);
    printf("Enter username: ");
    scanf("%s", newUser.username);
    // Kiem tra tinh hop le cua thong tin
    if (!checkLeght(newUser.name) || !checkLeght(newUser.phone) || !checkLeght(newUser.email) || !checkLeght(newUser.username)) {
        printf("User information cannot be empty.\n");
        return;
    }
    // Kiem tra trung lap cac thong tin: phone, email, va username
    if (is_unique(newUser.name, newUser.phone, newUser.email, newUser.username) == 0) {
        printf("Duplicate information found. Please ensure name, phone number, email, and username are unique.\n");
        return;  // Dong loi va khong them ID neu co thong tin trung lap
    }
    // Gan ID cho nguoi dung moi
    newUser.id = nextId;
    strcpy(newUser.password, newUser.phone);
    strcpy(newUser.status, "open");
    users[userCount] = newUser;
    file = fopen("bankData.dat", "ab");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    // Ghi thong tin nguoi dung vao file duoi dang nhi phan
    fwrite(&newUser, sizeof(struct User), 1, file);
    fclose(file);
    userCount++;
    printf("User added successfully with ID %d!\n", newUser.id);
}

// Ham tim kiem nguoi dung theo ten ////////////////////////////////////////////////////////DEREEK///////////////////////////////////////////////////////////////////////////////////////////
void searchUserByName(char *name) {
    int found = 0;
    char searchNameLower[50];
    
    if (strlen(name) < 2) {
        printf("\nSearch Results:\n");
        printf("-----------------------------------------------------------------------------------------------------------------");
	    printf("\n%-10s | %-20s | %-15s | %-30s | %-15s | %-10s |\n",  "ID", "Name", "Phone Number", "Email", "Username", "Status");
	    printf("-----------------------------------------------------------------------------------------------------------------\n");
        printf("User not found. \n");
        return;
    }

    printf("\nSearch Results:\n");
    printf("-----------------------------------------------------------------------------------------------------------------");
    printf("\n%-10s | %-20s | %-15s | %-30s | %-15s | %-10s |\n",  "ID", "Name", "Phone Number", "Email", "Username", "Status");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    // Chuyen ten tim kiem thanh chu thuong bang cach kiem tra tung ky tu
    for (int i = 0; name[i]; i++) {
        if (name[i] >= 'A' && name[i] <= 'Z') {
            searchNameLower[i] = name[i] + 32; 
        } else {
            searchNameLower[i] = name[i];
        }
    }
    searchNameLower[strlen(name)] = '\0';
    // Duyet qua tat ca nguoi dung va tim kiem
    for (int i = 0; i < userCount; i++) {
        char userNameLower[50];
        for (int j = 0; users[i].name[j]; j++) {
            if (users[i].name[j] >= 'A' && users[i].name[j] <= 'Z') {
                userNameLower[j] = users[i].name[j] + 32; 
            } else {
                userNameLower[j] = users[i].name[j];
            }
        }
        userNameLower[strlen(users[i].name)] = '\0';
        if (strcmp(userNameLower, searchNameLower) == 0) {
            found = 1;
            printf("%-10d | %-20s | %-15s | %-30s | %-15s | %-10s |\n", users[i].id, users[i].name, users[i].phone, users[i].email, users[i].username, users[i].status);
        }
    }

    if (!found) {
        printf("No users found with the given name.\n");
    }
}

// Ham menu quan ly cua Admin //////////////////////////////////////////////////////////////DEREEK///////////////////////////////////////////////////////////////////////////////////////////////////
void adminMenu() {
	system("cls");
    getchar();
    printf("              LOGIN            \n");
    printf("   ===============================\n");
    printf("   Please enter your account: ");
    fgets(input.email, sizeof(input.email), stdin); 
    input.email[strcspn(input.email, "\n")] = '\0';
    printf("   Please enter your Password: "); 
    fgets(input.password, sizeof(input.password), stdin);
    input.password[strcspn(input.password, "\n")] = '\0';
    printf("   ===============================\n");
    // Kiem tra tai khoan va mat khau
    if (strncmp(input.email, login.email, strlen(login.email)) == 0 &&
        strncmp(input.password, login.password, strlen(login.password)) == 0) {
        printf("\n===================================\n");
        printf("|       Login Successful!         |\n");
        printf("===================================\n");
        system("cls");
        int choiceAdmin;
        int exitLoop = 0;
        while (!exitLoop) {
            managerMenu();
            printf("Enter the choice: ");
            scanf("%d", &choiceAdmin);

            switch(choiceAdmin) {
                case 1:
                	system("cls");
                    printUsers();
                    break;
                case 2:
                	system("cls");
                    addUser();
                    break;
                case 3:
                	sortUsersByName();
                    break;
                case 4:
                    {
                    	system("cls");
                        char searchName[50];
                        printf("Enter the user name to search for: ");
                        getchar();
                        fgets(searchName, sizeof(searchName), stdin);
                        searchName[strcspn(searchName, "\n")] = '\0';
                        searchUserByName(searchName);
                    }
                    break;
                case 5:
                    {
                    	system("cls");
                        char searchId[50];
                        printf("Enter the user ID to search for: ");
                        getchar();
                        fgets(searchId, sizeof(searchId), stdin);
                        searchId[strcspn(searchId, "\n")] = '\0';
                        searchUserById(searchId);
                    }
                    break;
                case 6:
                	system("cls");
                	lockUnlock();
                	break;
                case 0:
                    exitLoop = 1;
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }
    } else {
        printf("\n===================================\n");
        printf("|   Invalid email or password!    |\n");
        printf("===================================\n");
        printf("|       ~~~ WARNING ~~~           |\n"); 
        printf("|        Account locked           |\n");
        printf("===================================\n");
    }
}

// Tim kiem theo Id /////////////////////////////////////////////////////////////////////// DEREEK///////////////////////////////////////////////////////////////////////
void searchUserById(char *id) {
    int found = 0;
    // Kiem tra neu id co do dai hop le
    if (strlen(id) < 1) {
        printf("\nSearch Results:\n");
        printf("-----------------------------------------------------------------------------------------------------------------");
	    printf("\n%-10s | %-20s | %-15s | %-30s | %-15s | %-10s |\n",  "ID", "Name", "Phone Number", "Email", "Username", "Status");
	    printf("-----------------------------------------------------------------------------------------------------------------\n");
        printf("User not found. \n");
        return;
    }
    int userId;
    if (sscanf(id, "%d", &userId) != 1) {
        printf("Invalid ID format.\n");
        return;
    }
    printf("\nSearch Results:\n");
    printf("-----------------------------------------------------------------------------------------------------------------");
    printf("\n%-10s | %-20s | %-15s | %-30s | %-15s | %-10s |\n",  "ID", "Name", "Phone Number", "Email", "Username", "Status");
    printf("-----------------------------------------------------------------------------------------------------------------\n");
    // Duyet qua danh sach nguoi dung va tim ID
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == userId) {
            found = 1;
            printf("%-10d | %-20s | %-15s | %-30s | %-15s | %-10s |\n", users[i].id, users[i].name, users[i].phone, users[i].email, users[i].username, users[i].status);
        }
    }

    if (!found) {
        printf("No user found with the given ID.\n");
    }
}
// Mo khoa hoac khoa User
void lockUnlock() {
    // Mo file doc nguoi dung co trong file
    FILE *file = fopen("bankData.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    users = malloc(0);
    userCount = 0;
    while (fread(&tempUser, sizeof(struct User), 1, file)) {
        users = realloc(users, (userCount + 1) * sizeof(struct User));
        users[userCount++] = tempUser;
    }
    fclose(file);
    int lockUser;
    int found = 0;
    printf("Enter the user ID to lock (or unlock): ");
    scanf("%d", &lockUser);
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == lockUser) {
            found = 1;

            if (strcmp(users[i].status, "locked") == 0) {
                printf("User %s (%d) is currently locked. Are you sure you want to unlock it? (y/n): ", users[i].name, lockUser);
                char choiceLock;
                scanf(" %c", &choiceLock);

                if (choiceLock == 'y' || choiceLock == 'Y') {
                    strcpy(users[i].status, "open");
                    printf("User %s (%d) has been successfully unlocked!\n", users[i].name, lockUser);
                } else {
                    printf("Unlock request has been canceled.\n");
                }
            } else if (strcmp(users[i].status, "open") == 0) {
                printf("User %s (%d) is currently unlocked. Are you sure you want to lock it? (y/n): ", users[i].name, lockUser);
                char choiceLock;
                scanf(" %c", &choiceLock);

                if (choiceLock == 'y' || choiceLock == 'Y') {
                    strcpy(users[i].status, "locked");
                    printf("User %s (%d) has been successfully locked!\n", users[i].name, lockUser);
                } else {
                    printf("Lock request has been canceled.\n");
                }
            }
            file = fopen("bankData.dat", "wb");
            if (file == NULL) {
                printf("Error opening file for writing.\n");
                return;
            }
            fwrite(users, sizeof(struct User), userCount, file);
            fclose(file);
            break;
        }
    }

    if (found == 0) {
        printf("No user found with ID: %d\n", lockUser);
    }
    free(users);
}

// Sap xep theo ten
void sortUsersByName() {
    FILE *file = fopen("bankData.dat", "rb");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }
    users = malloc(0);
    userCount = 0;
    while (fread(&tempUser, sizeof(struct User), 1, file)) {
        users = realloc(users, (userCount + 1) * sizeof(struct User));
        users[userCount++] = tempUser;
    }
    fclose(file);
    for (int i = 0; i < userCount - 1; i++) {
        for (int j = 0; j < userCount - i - 1; j++) {
            if (strcmp(users[j].name, users[j + 1].name) > 0) {
                temp = users[j];
                users[j] = users[j + 1];
                users[j + 1] = temp;
            }
        }
    }
    printf("\nSorted User List by Name:\n");
    printf("-----------------------------------------------------------------------------------------------------------------");
    printf("\n%-10s | %-20s | %-15s | %-30s | %-15s | %-10s |\n", "ID", "Name", "Phone Number", "Email", "Username", "Status");
    printf("-----------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        printf("%-10d | %-20s | %-15s | %-30s | %-15s | %-10s |\n",
               users[i].id, users[i].name, users[i].phone, users[i].email, users[i].username, users[i].status);
    }
    file = fopen("bankData.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        free(users);
        return;
    }
    fwrite(users, sizeof(struct User), userCount, file);
    fclose(file);
    printf("\nUser list has been sorted and saved successfully!\n");
    free(users);
}

void userMenu() {
	printf("\n   ===== User Management System =====\n");
    printf("           User functions:\n");
    printf("       [1]. Display user list \n");
    printf("       [2]. Add new user\n");
    printf("       [3]. Sort Users By Name\n");
    printf("       [4]. Search User Name \n");
    printf("       [5]. Search User Id \n");
    printf("       [6]. Unlock ( lock ) User\n");
    printf("       [0]. Exit\n");
}
