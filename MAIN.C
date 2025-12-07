*Source code*

#include <stdio.h>
#include <string.h>

#define STUD_FILE "students.txt"
#define LOGIN_FILE "credentials.txt"

char role[20];

int login() {
    char user[50], pass[50];
    char fileUser[50], filePass[50], fileRole[20];

    printf("Enter username: ");
    scanf("%s", user);

    printf("Enter password: ");
    scanf("%s", pass);

    FILE *fp = fopen(LOGIN_FILE, "r");
    if (fp == NULL) {
        printf("Login file not found!\n");
        return 0;
    }

    while (fscanf(fp, "%s %s %s", fileUser, filePass, fileRole) == 3) {
        if (strcmp(user, fileUser) == 0 && strcmp(pass, filePass) == 0) {
            strcpy(role, fileRole);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent() {
    int roll;
    char name[50];
    float mark;

    printf("Enter roll: ");
    scanf("%d", &roll);

    printf("Enter name: ");
    scanf("%s", name);

    printf("Enter marks: ");
    scanf("%f", &mark);

    FILE *fp = fopen(STUD_FILE, "a");
    fprintf(fp, "%d %s %.2f\n", roll, name, mark);
    fclose(fp);

    printf("Student added.\n");
}

void showStudents() {
    int roll;
    char name[50];
    float mark;

    FILE *fp = fopen(STUD_FILE, "r");
    if (fp == NULL) {
        printf("No student file found.\n");
        return;
    }

    printf("\nROLL  NAME        MARKS\n");
    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        printf("%d   %-10s   %.2f\n", roll, name, mark);
    }

    fclose(fp);
}

void searchStudent() {
    int roll, find, found = 0;
    char name[50];
    float mark;

    printf("Enter roll to search: ");
    scanf("%d", &find);

    FILE *fp = fopen(STUD_FILE, "r");
    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == find) {
            printf("Found: %d %s %.2f\n", roll, name, mark);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student not found.\n");

    fclose(fp);
}

void updateStudent() {
    int roll, find;
    char name[50];
    float mark;

    printf("Enter roll to update: ");
    scanf("%d", &find);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    int updated = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == find) {
            printf("Enter new name: ");
            scanf("%s", name);
            printf("Enter new marks: ");
            scanf("%f", &mark);
            updated = 1;
        }
        fprintf(temp, "%d %s %.2f\n", roll, name, mark);
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (updated)
        printf("Student updated.\n");
    else
        printf("Roll not found.\n");
}

void deleteStudent() {
    int roll, find;
    char name[50];
    float mark;

    printf("Enter roll to delete: ");
    scanf("%d", &find);

    FILE *fp = fopen(STUD_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");

    int deleted = 0;

    while (fscanf(fp, "%d %s %f", &roll, name, &mark) == 3) {
        if (roll == find)
            deleted = 1;
        else
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
    }

    fclose(fp);
    fclose(temp);

    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);

    if (deleted)
        printf("Student deleted.\n");
    else
        printf("Roll not found.\n");
}

void adminMenu() {
    int c;
    do {
        printf("\nADMIN MENU\n1.Add\n2.Show\n3.Search\n4.Update\n5.Delete\n0.Logout\n");
        scanf("%d", &c);

        if (c == 1) addStudent();
        else if (c == 2) showStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();
        else if (c == 5) deleteStudent();

    } while (c != 0);
}

void staffMenu() {
    int c;
    do {
        printf("\nSTAFF MENU\n1.Add\n2.Show\n3.Search\n4.Update\n0.Logout\n");
        scanf("%d", &c);

        if (c == 1) addStudent();
        else if (c == 2) showStudents();
        else if (c == 3) searchStudent();
        else if (c == 4) updateStudent();

    } while (c != 0);
}

void guestMenu() {
    int c;
    do {
        printf("\nGUEST MENU\n1.Show\n2.Search\n0.Logout\n");
        scanf("%d", &c);

        if (c == 1) showStudents();
        else if (c == 2) searchStudent();

    } while (c != 0);
}

int main() {
    printf("Student Management System\n");

    if (!login()) {
        printf("Wrong login.\n");
        return 0;
    }

    printf("Logged in as: %s\n", role);

    if (strcmp(role, "admin") == 0) adminMenu();
    else if (strcmp(role, "staff") == 0) staffMenu();
    else guestMenu();

    return 0;
}