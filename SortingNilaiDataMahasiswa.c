#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 200
#define MAX_NAME 100
#define CLS system("cls")

struct mahasiswa {
    char nama[MAX_NAME];
    int nilai;
};

struct mahasiswa student[MAX_STUDENTS];
int studentCount = 0;

// ================= PROTOTYPE =================
void menu();
void menuDisplay();
void inputStudent();
void loadStudents();
void bubbleSort();
void writeIn();
void writeOut();
void readOut();
void thankYou();

int isValidName(char *name);
int isValidGrade(int grade);
void getChoice(int *var, char *msg, int min, int max);

// ================= MAIN =================
int main() {
    menu();
    return 0;
}

// ================= MENU =================
void menu() {
    int choice;
    while (1) {
        menuDisplay();
        getChoice(&choice, "Masukkan pilihan: ", 1, 3);
        CLS;

        switch (choice) {
            case 1:
                inputStudent();
                break;
            case 2:
                loadStudents();
                break;
            case 3:
                thankYou();
                exit(0);
        }
    }
}

void menuDisplay() {
    CLS;
    printf("=================================\n");
    printf("||   PROGRAM SORTING NILAI     ||\n");
    printf("=================================\n");
    printf("|| 1. Input Manual             ||\n");
    printf("|| 2. Load & Sort              ||\n");
    printf("|| 3. Keluar                   ||\n");
    printf("=================================\n");
}

// ================= VALIDASI =================
void getChoice(int *var, char *msg, int min, int max) {
    char buf[50], c;
    while (1) {
        printf("%s", msg);
        if (fgets(buf, sizeof(buf), stdin)) {
            if (sscanf(buf, "%d %c", var, &c) == 1 && *var >= min && *var <= max)
                return;
        }
        printf("Input tidak valid!\n");
    }
}

int isValidName(char *name) {
    if (strlen(name) == 0) return 0;
    for (int i = 0; name[i]; i++) {
        if (!isalpha(name[i]) && name[i] != ' ')
            return 0;
    }
    return 1;
}

int isValidGrade(int grade) {
    return grade >= 0 && grade <= 100;
}

// ================= INPUT MANUAL =================
void inputStudent() {
    CLS;
    getChoice(&studentCount, "Masukkan jumlah mahasiswa: ", 1, MAX_STUDENTS);
    CLS;

    for (int i = 0; i < studentCount; i++) {
        char buffer[MAX_NAME];
        int grade;

        printf("Mahasiswa %d\n", i + 1);

        // Nama
        while (1) {
            printf("Nama  : ");
            fgets(buffer, MAX_NAME, stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (isValidName(buffer)) {
                strcpy(student[i].nama, buffer);
                break;
            }
            printf("Nama tidak valid!\n");
        }

        // Nilai
        while (1) {
            printf("Nilai : ");
            if (scanf("%d", &grade) == 1 && isValidGrade(grade)) {
                student[i].nilai = grade;
                break;
            }
            printf("Nilai harus 0-100!\n");
            while (getchar() != '\n');
        }
        getchar();
        printf("\n");
    }

    writeIn();
    printf("Data berhasil disimpan!\n");
    printf("Tekan ENTER untuk kembali...");
    getchar();
}

// ================= FILE INPUT =================
void writeIn() {
    FILE *f = fopen("asistenin.txt", "w");
    for (int i = 0; i < studentCount; i++) {
        fprintf(f, "%s\n%d\n", student[i].nama, student[i].nilai);
    }
    fclose(f);
}

// ================= LOAD & SORT =================
void loadStudents() {
    FILE *f = fopen("asistenin.txt", "r");
    if (!f) {
        printf("File asistenin.txt tidak ditemukan!\n");
        getchar();
        return;
    }

    studentCount = 0;
    while (!feof(f) && studentCount < MAX_STUDENTS) {
        fgets(student[studentCount].nama, MAX_NAME, f);
        if (feof(f)) break;
        student[studentCount].nama[strcspn(student[studentCount].nama, "\n")] = 0;
        fscanf(f, "%d\n", &student[studentCount].nilai);
        studentCount++;
    }
    fclose(f);

    bubbleSort();
    writeOut();
}

// ================= SORT =================
void bubbleSort() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = 0; j < studentCount - i - 1; j++) {
            if (student[j].nilai < student[j + 1].nilai) {
                struct mahasiswa temp = student[j];
                student[j] = student[j + 1];
                student[j + 1] = temp;
            }
        }
    }
}

// ================= OUTPUT =================
void writeOut() {
    FILE *f = fopen("asistenout.txt", "w");
    fprintf(f, "HASIL SORTING NILAI\n");
    fprintf(f, "===================\n");
    for (int i = 0; i < studentCount; i++) {
        fprintf(f, "%d. %s - %d\n", i + 1, student[i].nama, student[i].nilai);
    }
    fclose(f);

    readOut();
}

void readOut() {
    FILE *f = fopen("asistenout.txt", "r");
    char line[200];
    CLS;
    while (fgets(line, sizeof(line), f)) {
        printf("%s", line);
    }
    fclose(f);

    printf("\nTekan ENTER untuk kembali...");
    getchar();
}

// ================= THANK YOU =================
void thankYou() {
    CLS;
    printf("Terima kasih telah menggunakan program ini!\n");
    printf("Tekan ENTER untuk keluar...");
    getchar();
}
