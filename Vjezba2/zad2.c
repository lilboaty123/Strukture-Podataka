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


int main() {
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
    printf("\n--- Brisanje osobe (Horvat) ---\n");
    deletePerson(head, "Horvat");

    printf("\n--- Lista nakon brisanja ---\n");
    printList(head);

    Position current = head->next;
    while(current != NULL) {
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

// A. Dodavanje na pocetak
int insertAtBeginning(Position head, char* name, char* lastName, int year) {
    Position newPerson = createPerson(name, lastName, year);
    if (!newPerson) return -30;

    newPerson->next = head->next;
    head->next = newPerson;
    return 0;
}

// C. Dodavanje na kraj
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

// B. Ispis liste
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

// D. Pronalazenje po prezimenu
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

// E. Brisanje elementa
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