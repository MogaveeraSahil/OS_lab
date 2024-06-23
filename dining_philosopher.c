#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10

typedef enum { THINKING, HUNGRY, EATING } state_t;

state_t states[MAX_PHILOSOPHERS];
int num_philosophers;
int num_hungry;
int hungry_philosophers[MAX_PHILOSOPHERS];
int forks[MAX_PHILOSOPHERS];

void print_state() {
    printf("\n");
    for (int i = 0; i < num_philosophers; ++i) {
        if (states[i] == THINKING) printf("P %d is thinking\n", i + 1);
        else if (states[i] == HUNGRY) printf("P %d is waiting\n", i + 1);
        else if (states[i] == EATING) printf("P %d is eating\n", i + 1);
    }
}

void simulate(int allow_two) {
    int eating_count = 0;
    for (int i = 0; i < num_philosophers; ++i) {
        if (states[i] == HUNGRY) {
            int left_fork = i;
            int right_fork = (i + 1) % num_philosophers;

            if (forks[left_fork] == 0 && forks[right_fork] == 0) {
                forks[left_fork] = forks[right_fork] = 1;
                states[i] = EATING;
                eating_count++;
                printf("P %d is granted to eat\n", i + 1);
                if (!allow_two && eating_count == 1) break;
                if (allow_two && eating_count == 2) break;
            }
        }
    }

    sleep(1);

    for (int i = 0; i < num_philosophers; ++i) {
        if (states[i] == EATING) {
            int left_fork = i;
            int right_fork = (i + 1) % num_philosophers;
            forks[left_fork] = forks[right_fork] = 0;
            states[i] = THINKING;
        }
    }
}

int main() {
    printf("Enter the total number of philosophers (max %d): ", MAX_PHILOSOPHERS);
    scanf("%d", &num_philosophers);

    if (num_philosophers < 2 || num_philosophers > MAX_PHILOSOPHERS) {
        printf("Invalid number of philosophers. Exiting.\n");
        return 1;
    }

    printf("How many are hungry: ");
    scanf("%d", &num_hungry);

    for (int i = 0; i < num_hungry; ++i) {
        printf("Enter philosopher %d position: ", i + 1);
        int position;
        scanf("%d", &position);
        hungry_philosophers[i] = position - 1; 
        states[hungry_philosophers[i]] = HUNGRY;
    }

    
    for (int i = 0; i < num_philosophers; ++i) {
        forks[i] = 0;
    }

    int choice;
    do {
        print_state();
        printf("\n1. One can eat at a time\n");
        printf("2. Two can eat at a time\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                simulate(0);
                break;
            case 2:
                simulate(1);
                break;
            case 3:
                printf("Exiting.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }

    } while (choice != 3);

    return 0;
}