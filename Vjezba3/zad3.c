#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _Person* Position;
typedef struct _Person {
    char name[50];
    char lastName[50];
    int year;
    Position next;
} Person;


Position createPerson(char* name, char* lastName, int year);
int insertAtBeginning(Position head, char* name, char* lastName, int year);
int insertAtEnd(Position head, char* name, char* lastName, int year);
int printList(Position head);
Position findPerson(Position head, char* lastName);
int deletePerson(Position head, char* lastName);

/*---------------3 Vjezba--------------------*/

int insertAfter(Position head, char* lastName, char* name, char* newLastName, int year);
int insertBefore(Position head, char* lastName, char* name, char* newLastName, int year);
int sortFun(Position head);
int writeToFile(Position head, char* filename);
int readFromFile(Position head, char* filename);


int main()
{
    Person headNode = { .name = "", .lastName = "", .year = 0, .next = NULL };
    Position head = &headNode;

    // A. Dodavanje novih elementa na pocetak liste
    insertAtBeginning(head, "Ivan", "Horvat", 2000);
    insertAtBeginning(head, "Marko", "Maric", 2002);

    // C. Dodavanje novih elementa na kraj liste
    insertAtEnd(head, "Ana", "Anic", 2001);

    // B. Ispis liste
    printf("--- Trenutna lista ---\n");
    printList(head);

    
    // D. Pronalazi element u listi
    printf("\n--- Trazenje osobe (Maric) ---\n");
    Position found = findPerson(head, "Maric");
    if (found != NULL) {
        printf("Pronadeno: %s %s (%d)\n", found->name, found->lastName, found->year);
    } else {
        printf("Osoba nije pronadena.\n");
    }

    // E. Brise odredeni element iz liste
    printf("\n--- Brisanje osobe (Anic) ---\n");
    deletePerson(head, "Anic");

    printf("\n--- Lista nakon brisanja ---\n");
    printList(head);


    /*----------------3 Vjezba----------------*/
    printf("\n--------- 3 Vjezba ----------\n");

    // 3.A) Dodavanje iza odredene osobe
    printf("\n--- Dodavanje iza Maric ---\n");

    insertAfter(head, "Maric", "Petar", "Peric", 2003);
    printList(head);


    // 3.B) Dodavanje ispred odredene osobe
    printf("\n--- Dodavanje ispred Horvat ---\n");

    insertBefore(head, "Horvat", "Luka", "Kovac", 2004);
    printList(head);


    // 3.C) Sortiranje po prezimenima
    printf("\n--- Sortirana lista ---\n");

    sortFun(head);
    printList(head);


    // 3.D) Zapisivanje liste u datoteku
    printf("\n--- Zapisivanje u datoteku ---\n");

    if (writeToFile(head, "osobe.txt") == 0)                                    //Neznan di se napravi ovaj file pa ako ocu ciljano ga stavit zamini "osobe.txt" sa "C:\\Users\\'user'\\'folder'\\osobe.txt"
        printf("Lista je zapisana u datoteku.\n");


    // 3.E) Citanje liste iz datoteke
    Person headNode2 = { .name = "", .lastName = "", .year = 0, .next = NULL };
    Position head2 = &headNode2;
    printf("\n--- Citanje iz datoteke ---\n");
    if (readFromFile(head2, "osobe.txt") == 0)
        printList(head2);



    
    // Oslobadanje memorije prve liste
    Position current = head->next;
    while (current != NULL) {
        Position temp = current;
        current = current->next;
        free(temp);
    }

    // Oslobadanje memorije druge liste
    current = head2->next;
    while (current != NULL) {
        Position temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}





Position createPerson(char* name, char* lastName, int year) {
    Position newPerson = (Position)malloc(sizeof(Person));
    if (!newPerson) {
        printf("Greska pri alokaciji memorije!\n");
        return NULL;
    }
    strcpy(newPerson->name, name);
    strcpy(newPerson->lastName, lastName);
    newPerson->year = year;
    newPerson->next = NULL;
    return newPerson;
}


// 2.A) DODAVANJE NA POCETAK
int insertAtBeginning(Position head, char* name, char* lastName, int year) {
    Position newPerson = createPerson(name, lastName, year);
    if (!newPerson) return -30;

    newPerson->next = head->next;
    head->next = newPerson;
    return 0;
}


// 2.C) DODAVANJE NA KRAJ
int insertAtEnd(Position head, char* name, char* lastName, int year) {
    Position newPerson = createPerson(name, lastName, year);
    if (!newPerson) return -30;

    Position last = head;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = newPerson;
    return 0;
}


// 2.B) ISPIS LISTE
int printList(Position head) {
    Position current = head->next;
    if (current == NULL) {
        printf("Lista je prazna.\n");
        return 0;
    }
    while (current != NULL) {
        printf("%s %s (%d)\n", current->name, current->lastName, current->year);
        current = current->next;
    }
    return 0;
}

// 2.D) PRONALAZENJE PO PREZIMENU
Position findPerson(Position head, char* lastName) {
    Position current = head->next;
    while (current != NULL) {
        if (strcmp(current->lastName, lastName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}


// 2.E) BRISANJE OSOBE
int deletePerson(Position head, char* lastName) {
    Position prev = head;
    Position current = head->next;

    while (current != NULL) {
        if (strcmp(current->lastName, lastName) == 0) {
            
            prev->next = current->next;
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    printf("Osoba s prezimenom %s nije pronadena za brisanje.\n", lastName);
    return -20;
}



/*-----------------3 Vjezba----------------*/


// 3.A) DODAVANJE IZA ODREDENE OSOBE
int insertAfter(Position head, char* lastName, char* name, char* newLastName, int year)
{
    Position current = findPerson(head, lastName);

    if (current == NULL) {
        printf("Osoba s prezimenom %s nije pronadena.\n", lastName);
        return -1;
    }

    Position newPerson = createPerson(name, newLastName, year);

    if (!newPerson) return -30;

    newPerson->next = current->next;
    current->next = newPerson;

    return 0;
}


// 3.B) DODAVANJE ISPRED ODREDENE OSOBE
int insertBefore(Position head, char* lastName, char* name, char* newLastName, int year)
{
    Position prev = head;
    Position current = head->next;

    while (current != NULL && strcmp(current->lastName, lastName) != 0) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Osoba s prezimenom %s nije pronadena.\n", lastName);
        return -40;
    }

    Position newPerson = createPerson(name, newLastName, year);

    if (!newPerson) return 30;

    newPerson->next = current;
    prev->next = newPerson;

    return 0;
}


// 3.C) SORTIRANJE PO PREZIMENIMA
int sortFun(Position head)
{
    if (head->next == NULL)
        return 0;

    Position p;
    Position q;

    for (p = head->next; p != NULL; p = p->next) {
        for (q = p->next; q != NULL; q = q->next) {

            if (strcmp(p->lastName, q->lastName) > 0) {
                char tempName[50];
                char tempLastName[50];
                int tempYear;

                strcpy(tempName, p->name);
                strcpy(tempLastName, p->lastName);
                tempYear = p->year;

                strcpy(p->name, q->name);
                strcpy(p->lastName, q->lastName);
                p->year = q->year;

                strcpy(q->name, tempName);
                strcpy(q->lastName, tempLastName);
                q->year = tempYear;
            }
        }
    }

    return 0;
}


// 3.D) ZAPISIVANJE LISTE U DATOTEKU
int writeToFile(Position head, char* filename)
{
    FILE* fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return -20;
    }

    Position current = head->next;

    while (current != NULL) {
        fprintf(fp, "%s %s %d\n", current->name, current->lastName, current->year);
        current = current->next;
    }

    fclose(fp);

    return 0;
}


// 3.E) CITANJE LISTE IZ DATOTEKE
int readFromFile(Position head, char* filename)
{
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke!\n");
        return -20;
    }

    char name[50];
    char lastName[50];
    int year;

    while (fscanf(fp, "%49s %49s %d",  name, lastName, &year) == 3) {

        if (insertAtEnd(head, name, lastName, year) != 0) {
            fclose(fp);
            return -1;
        }
    }

    fclose(fp);

    return 0;
}