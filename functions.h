#include "dataType.h"

// Các khai báo hàm
// Ham cua Admin///////////////////////////////////////////////////////////////////////DEREEK//////////////////////////////////////////////////////////////////////////////////////////////////

void printHello();                                                                            // Hien thi Menu ban dau
void managerMenu();                                                                           // In ra quan ly nguoi dung cho admin
void printUsers();                                                                            // Hien thi danh sach nguoi dung
void addUser();                                                                               // Them nguoi dung
void searchUserByName(char *name);                                                            // Tim kiem nguoi dung
void adminMenu();                                                                             // ham quan ly cua chuc nang admin
int checkLeght(char *str);                                                                    // Kiem tra do dai cua thong tin ( Tra ve int 0 true 1 fales )
int is_unique(char *name, char *phone, char *email, char *username);                          // Kiem tra tinh duy nhat cua thong tin
void searchUserById(char *id);                                                                // Tim kiem theo Id
void lockUnlock();                                                                            // Khoa hoac mo khoa nguoi dung
void sortUsersByName();                                                                       // Sap xep nguoi dung theo ten 

// Ham cua User ////////////////////////////////////////////////////////////////////////DEREEK////////////////////////////////////////////////////////////////////////////////////////////////
void userMenu();
