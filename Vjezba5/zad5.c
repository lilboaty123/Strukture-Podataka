#include <stdio.h>
#include <stdlib.h>

typedef struct Stack* Position;

typedef struct Stack {
    int broj;
    Position next;
} stack;



int push(Position head, int broj)
{
    Position newP;

    newP = (Position)malloc(sizeof(stack));

    if (newP == NULL)
        return -1;

    newP->broj = broj;
    newP->next = head->next;
    head->next = newP;

    return 0;
}



Position pop(Position head)
{
    Position p;

    p = head->next;

    if (p == NULL)
        return NULL;

    head->next = p->next;

    return p;
}


void freeStack(Position head)
{
    Position p;

    while (head->next != NULL) {
        p = pop(head);
        free(p);
    }
}


int izracunaj(char *ime)
{
    FILE *fp;
    stack head = { .broj = 0, .next = NULL };

    char token[100];
    int broj, rezultat;
    int i;

    Position p, q;

    fp = fopen(ime, "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while (fscanf(fp, "%99s", token) == 1) {

        
        if ((token[0] >= '0' && token[0] <= '9') ||
            (token[0] == '-' && token[1] != '\0')) {

            broj = 0;
            i = 0;

            if (token[0] == '-')
                i = 1;

            for (; token[i] != '\0'; i++) {
                broj = broj * 10 + (token[i] - '0');
            }

            if (token[0] == '-')
                broj = -broj;

            if (push(&head, broj) != 0) {
                printf("Greska pri alokaciji!\n");

                freeStack(&head);
                fclose(fp);

                return -1;
            }
        }

        
        else {

            q = pop(&head);
            p = pop(&head);

            if (p == NULL || q == NULL) {
                printf("Greska: nedovoljno elemenata!\n");

                free(p);
                free(q);
                freeStack(&head);
                fclose(fp);

                return -1;
            }

            if (token[0] == '+')
                rezultat = p->broj + q->broj;

            else if (token[0] == '-')
                rezultat = p->broj - q->broj;

            else if (token[0] == '*')
                rezultat = p->broj * q->broj;

            else {
                if (q->broj == 0) {
                    printf("Dijeljenje s nulom!\n");

                    free(p);
                    free(q);
                    freeStack(&head);
                    fclose(fp);

                    return -1;
                }

                rezultat = p->broj / q->broj;
            }

            
            free(p);
            free(q);

            
            if (push(&head, rezultat) != 0) {
                printf("Greska pri alokaciji!\n");

                freeStack(&head);
                fclose(fp);

                return -1;
            }
        }
    }

    fclose(fp);

    
    if (head.next == NULL || head.next->next != NULL) {
        printf("Neispravan izraz!\n");

        freeStack(&head);
        return -1;
    }

    rezultat = head.next->broj;

    printf("Rezultat je: %d\n", rezultat);

    freeStack(&head);

    return rezultat;
}



int main()
{
    izracunaj("izraz.txt");

    return 0;
}