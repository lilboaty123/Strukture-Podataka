#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;

typedef struct Poly {
    int coef;
    int pon;
    Position next;
} polynom;


// Umetanje clana polinoma na odgovarajuce mjesto
int insertSorted(Position head, int coef, int pon)
{
    Position q = head;
    Position newPoly;

    // Pronalazak mjesta za umetanje
    while (q->next != NULL && q->next->pon > pon)
        q = q->next;

    // Ako vec postoji isti eksponent, zbrajamo koeficijente
    if (q->next != NULL && q->next->pon == pon) {
        q->next->coef += coef;
        return 0;
    }

    // Alokacija novog clana
    newPoly = (Position)malloc(sizeof(polynom));

    if (newPoly == NULL)
        return -1;

    newPoly->coef = coef;
    newPoly->pon = pon;

    // Umetanje novog clana u listu
    newPoly->next = q->next;
    q->next = newPoly;

    return 0;
}


// Citanje polinoma iz datoteke
int readPoly(Position head, const char* filename)
{
    FILE* fp;
    int coef, pon;

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke %s!\n", filename);
        return -1;
    }

    while (fscanf(fp, "%d %d", &coef, &pon) == 2) {
        if (insertSorted(head, coef, pon) != 0) {
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}


// Ispis polinoma
void printPoly(Position head)
{
    Position p = head->next;
    int first = 1;

    if (p == NULL) {
        printf("0\n");
        return;
    }

    while (p != NULL) {
        if (p->coef != 0) {
            if (!first) {
                if (p->coef > 0)
                    printf(" + ");
                else
                    printf(" - ");
            }
            else if (p->coef < 0) {
                printf("-");
            }

            int c = abs(p->coef);

            if (p->pon == 0) {
                printf("%d", c);
            }
            else if (p->pon == 1) {
                if (c != 1)
                    printf("%d", c);
                printf("x");
            }
            else {
                if (c != 1)
                    printf("%d", c);
                printf("x^%d", p->pon);
            }

            first = 0;
        }

        p = p->next;
    }

    if (first)
        printf("0");

    printf("\n");
}


// Zbrajanje polinoma
int addPoly(Position headF, Position headP, Position headQ)
{
    Position p;

    // Kopiranje prvog polinoma u rezultat
    for (p = headP->next; p != NULL; p = p->next) {
        if (insertSorted(headF, p->coef, p->pon) != 0)
            return -1;
    }

    // Dodavanje drugog polinoma
    for (p = headQ->next; p != NULL; p = p->next) {
        if (insertSorted(headF, p->coef, p->pon) != 0)
            return -1;
    }

    return 0;
}


// Mnozenje polinoma
int multiplyPoly(Position headF, Position headP, Position headQ)
{
    Position p, q;

    for (p = headP->next; p != NULL; p = p->next) {
        for (q = headQ->next; q != NULL; q = q->next) {

            int coef = p->coef * q->coef;
            int pon = p->pon + q->pon;

            if (insertSorted(headF, coef, pon) != 0)
                return -1;
        }
    }

    return 0;
}


// Oslobadanje memorije
void deletePoly(Position head)
{
    Position temp;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
}


int main(void)
{
    polynom headP = { 0, 0, NULL };
    polynom headQ = { 0, 0, NULL };
    polynom headF = { 0, 0, NULL };
    polynom headM = { 0, 0, NULL };

    // Citanje polinoma iz datoteka
    if (readPoly(&headP, "polinom1.txt") != 0) {
        deletePoly(&headP);
        return 1;
    }

    if (readPoly(&headQ, "polinom2.txt") != 0) {
        deletePoly(&headP);
        deletePoly(&headQ);
        return 1;
    }

    printf("Prvi polinom: ");
    printPoly(&headP);

    printf("Drugi polinom: ");
    printPoly(&headQ);

    // Zbrajanje
    if (addPoly(&headF, &headP, &headQ) != 0) {
        printf("Greska pri zbrajanju!\n");
        goto cleanup;
    }

    printf("\nZbroj polinoma: ");
    printPoly(&headF);

    // Mnozenje
    if (multiplyPoly(&headM, &headP, &headQ) != 0) {
        printf("Greska pri mnozenju!\n");
        goto cleanup;
    }

    printf("Umnozak polinoma: ");
    printPoly(&headM);

cleanup:
    deletePoly(&headP);
    deletePoly(&headQ);
    deletePoly(&headF);
    deletePoly(&headM);

    return 0;
}