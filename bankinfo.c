#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Customer {
    int id;
    int arrivalTime;
    int serviceTime;
};

struct Node {
    struct Customer data;
    struct Node* next;
};

struct Node* front = NULL;
struct Node* rear = NULL;

int customerID = 1;      
int currentTime = 0;     
// ===================== QUEUE OPERATIONS =========================

int isEmpty() {
    return front == NULL;
}

void enqueue(int arrival, int service) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data.id = customerID++;
    newNode->data.arrivalTime = arrival;
    newNode->data.serviceTime = service;
    newNode->next = NULL;

    if (isEmpty()) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    printf("\nCustomer %d added to queue.\n", newNode->data.id);
}

void dequeue() {
    if (isEmpty()) {
        printf("\nQueue is empty! No customer to serve.\n");
        return;
    }

    struct Node* temp = front;
    int waitTime = currentTime - temp->data.arrivalTime;

    printf("\nServing Customer %d\n", temp->data.id);
    printf("Arrival Time : %d\n", temp->data.arrivalTime);
    printf("Service Time : %d minutes\n", temp->data.serviceTime);
    printf("Wait Time    : %d minutes\n\n", waitTime);

    currentTime += temp->data.serviceTime;  // Increase bank time

    front = front->next;
    free(temp);
}

// ===================== DISPLAY QUEUE ===========================

void display() {
    if (isEmpty()) {
        printf("\nQueue is empty.\n");
        return;
    }

    struct Node* temp = front;
    printf("\n--- Current Queue ---\n");
    while (temp != NULL) {
        printf("Customer %d (Arrived %d, Needs %d mins)\n",
               temp->data.id,
               temp->data.arrivalTime,
               temp->data.serviceTime);
        temp = temp->next;
    }
}

// ======================== MAIN MENU ===========================

int main() {
    int choice, arrival, service;

    while (1) {
        printf("\n====== BANK QUEUE SIMULATION ======\n");
        printf("1. Add Customer to Queue\n");
        printf("2. Serve Customer\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter customer arrival time (minutes): ");
            scanf("%d", &arrival);
            printf("Enter service time required (minutes): ");
            scanf("%d", &service);

            enqueue(arrival, service);
            break;

        case 2:
            dequeue();
            break;

        case 3:
            display();
            break;

        case 4:
            printf("\nExiting...\n");
            exit(0);

        default:
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}