#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char ime[30];
    char prezime[30];
    int bodovi;
} Student;

int main() {
    FILE *fp;
    Student *s;
    int n = 0;
    int i;
    int max_bodova = 100;
    char redak[100];

    fp = fopen("studenti.txt", "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return 1;
    }

    while (fgets(redak, 100, fp) != NULL) {
        n++;
    }

    fclose(fp);

    s = malloc(n * sizeof(Student));

    fp = fopen("studenti.txt", "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        free(s);
        return 1;
    }

    for (i = 0; i < n; i++) {
        fscanf(fp, "%s %s %d",
           s[i].ime,
           s[i].prezime,
           &s[i].bodovi);
    }

    fclose(fp);

    for (i = 0; i < n; i++) {
        printf("Ime: %s\n", s[i].ime);
        printf("Prezime: %s\n", s[i].prezime);
        printf("Broj bodova: %d\n", s[i].bodovi);

        printf("Relativni broj bodova: %.2f%%\n\n",
               (float)s[i].bodovi / max_bodova * 100);
    }

    free(s);

    return 0;
}