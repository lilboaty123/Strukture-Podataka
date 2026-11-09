#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct Poly* Position;

typedef struct Poly {
    int coef;
    int pon;
    Position next;
} polynom;



int insertSorted(Position head, int coef, int pon)
{
    Position q = head;
    Position newPoly;

    
    while (q->next != NULL && q->next->pon > pon)
        q = q->next;

    
    if (q->next != NULL && q->next->pon == pon) {
        q->next->coef += coef;
        return 0;
    }

    
    newPoly = (Position)malloc(sizeof(polynom));

    if (newPoly == NULL)
        return -1;

    newPoly->coef = coef;
    newPoly->pon = pon;

    
    newPoly->next = q->next;
    q->next = newPoly;

    return 0;
}



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



int addPoly(Position headF, Position headP, Position headQ)
{
    Position p;

    
    for (p = headP->next; p != NULL; p = p->next) {
        if (insertSorted(headF, p->coef, p->pon) != 0)
            return -1;
    }

    
    for (p = headQ->next; p != NULL; p = p->next) {
        if (insertSorted(headF, p->coef, p->pon) != 0)
            return -1;
    }

    return 0;
}



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



void deletePoly(Position head)
{
    Position temp;

    while (head->next != NULL) {
        temp = head->next;
        head->next = temp->next;
        free(temp);
    }
}


int main()
{
    polynom headP = { 0, 0, NULL };
    polynom headQ = { 0, 0, NULL };
    polynom headF = { 0, 0, NULL };
    polynom headM = { 0, 0, NULL };


    if (readPoly(&headP, "polinom1.txt") != 0) {
        printf("Greska pri citanju prvog polinoma!\n");
        deletePoly(&headP);
        return 1;
    }

    if (readPoly(&headQ, "polinom2.txt") != 0) {
        printf("Greska pri citanju drugog polinoma!\n");
        deletePoly(&headP);
        deletePoly(&headQ);
        return 1;
    }

    printf("Prvi polinom: ");
    printPoly(&headP);

    printf("Drugi polinom: ");
    printPoly(&headQ);


    if (addPoly(&headF, &headP, &headQ) == 0) {
        printf("\nZbroj polinoma: ");
        printPoly(&headF);


        if (multiplyPoly(&headM, &headP, &headQ) == 0) {
            printf("Umnozak polinoma: ");
            printPoly(&headM);
        }
        else {
            printf("Greska pri mnozenju polinoma!\n");
        }
    }
    else {
        printf("Greska pri zbrajanju polinoma!\n");
    }

    deletePoly(&headP);
    deletePoly(&headQ);
    deletePoly(&headF);
    deletePoly(&headM);

    return 0;
}