#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a donor
typedef struct Donor {
    char name[13];
    char surname[13];
    float amount;
    struct Donor *next;
} Donor;

// Function to create a new donor node
Donor* createDonor(char* name, char* surname, float amount) {
    Donor* newDonor = (Donor*)malloc(sizeof(Donor));
    strcpy(newDonor->name, name);
    strcpy(newDonor->surname, surname);
    newDonor->amount = amount;
    newDonor->next = NULL;
    return newDonor;
}

// Function to insert the donor into the linked list in sorted order (descending)
void insertDonorSorted(Donor** head, Donor* newDonor) {
    if (*head == NULL || newDonor->amount > (*head)->amount) {
        newDonor->next = *head;
        *head = newDonor;
    } else {
        Donor* current = *head;
        while (current->next != NULL && current->next->amount >= newDonor->amount) {
            current = current->next;
        }
        newDonor->next = current->next;
        current->next = newDonor;
    }
}

// Function to free the linked list
void freeList(Donor* head) {
    Donor* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    
    Donor* head = NULL;
    
    for (int i = 0; i < m; i++) {
        char name[13], surname[13];
        float amount;
        scanf("%s %s %f", name, surname, &amount);
        Donor* newDonor = createDonor(name, surname, amount);
        insertDonorSorted(&head, newDonor);
    }
    
    // Print the top n donors
    Donor* current = head;
    int count = 0;
    while (current != NULL && count < n) {
        printf("%s %s %.2f\n", current->name, current->surname, current->amount);
        current = current->next;
        count++;
    }
    
    // Free the list
    freeList(head);
    
    return 0;
}

