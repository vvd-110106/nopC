#include <stdbool.h>

// Ham cua Admin ///////////////////////////////////////////////////////////////////////////////////////////DEREEK////////////////////////////////////////////////////////////////////////////
struct User {
	int id;
    char name[50];    // Ten nguoi dung 
    char phone[20];   // So dien thoai 
    char email[50];   // Email 
    char username[20]; // Ten dang nhap 
    char password[20]; // Mat khau 
    char status[10];   // Trang thai nguoi dung
};

struct Date {
    int month, day, year;
};

struct User* users = NULL;  // con tro danh sach nguoi dung . dc cap phat dong
struct User newUser;    // Mot user moi, them nguoi dung moi

struct Login{
	char email[100];
	char password[50];
};
struct Login login={ "Dereekdz123", "110106 - 270406" };  // tk,mk
struct Login input;       // thong tin dang nhap
struct User temp;         // Luu tru doi tuong sap xep
struct User tempUser;    // Bien luu thong tin doc tu file bankDta.dat


