#include <stdio.h>
#include <stdlib.h>


typedef enum EventType {
    HACK,
    CONCERT,
    WORKSHOP
} EventType;

typedef struct Event {
    int day;
    EventType type;
    int numParticipants;
    int revenue;
} Event;

// Added day-wise revenue array
int* dayWiseRevenue;

Event* generateEvent(int day, EventType type, int numParticipants, int revenue) {
    Event* event = malloc(sizeof(Event));
    event->day = day;
    event->type = type;
    event->numParticipants = numParticipants;
    event->revenue = revenue;
    return event;
}

void printEvent(Event* event) {
    char* type;
    switch (event->type) {
        case HACK:
            type = "HACK";
            break;
        case CONCERT:
            type = "CONCERT";
            break;
        case WORKSHOP:
            type = "WORKSHOP";
            break;
    }
    printf("Day: %d, Type: %s, Participants: %d, Revenue: %d\n", event->day, type, event->numParticipants, event->revenue);
}

void printReport(Event*** events, int numDays, int numEventsPerDay) {
    int totalRevenue = 0;

    // Reset day-wise revenue before calculating
    for (int i = 0; i < numDays; i++) {
        dayWiseRevenue[i] = 0;
    }

    // Added day-wise revenue calculation
    for (int i = 0; i < numDays; i++) {
        for (int j = 0; j < numEventsPerDay; j++) {
            if (events[i][j] != NULL) {
                printEvent(events[i][j]);
                totalRevenue += events[i][j]->revenue;
                dayWiseRevenue[i] += events[i][j]->revenue; // Accumulate day-wise revenue
            }
        }
    }

    // Print day-wise revenue
    printf("Day-wise Revenue:\n");
    for (int i = 0; i < numDays; i++) {
        printf("Day %d: %d\n", i + 1, dayWiseRevenue[i]);
    }

    // Print total revenue
    printf("Total Revenue: %d\n", totalRevenue);
}

int main() {
    int numDays = 5;
    int numEventsPerDay = 3;

    // Modified events array to be 2D
    Event*** events = malloc(sizeof(Event**) * numDays);
    for (int i = 0; i < numDays; i++) {
        events[i] = malloc(sizeof(Event*) * numEventsPerDay);
        for (int j = 0; j < numEventsPerDay; j++) {
            events[i][j] = NULL; // Initialize events to NULL
        }
    }

    // Added day-wise revenue array allocation
    dayWiseRevenue = malloc(sizeof(int) * numDays);

    int choice;
    int day;
    int revenue;
    EventType type;
    int numParticipants;

    do {
        printf("1. Register for an event\n");
        printf("2. Generate consolidated report\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter day of event (1-5): ");
                scanf("%d", &day);
                printf("Enter event type (0 for HACK, 1 for CONCERT, 2 for WORKSHOP): ");
                scanf("%d", (int*)&type);
                printf("Enter number of participants: ");
                scanf("%d", &numParticipants);
                printf("Enter revenue: ");
                scanf("%d", &revenue);

                // Check if the limit of events per day is reached
                int eventIndex = -1;
                for (int i = 0; i < numEventsPerDay; i++) {
                    if (events[day - 1][i] == NULL) {
                        eventIndex = i;
                        break;
                    }
                }

                if (eventIndex == -1) {
                    printf("Event limit reached for day %d\n", day);
                } else {
                    events[day - 1][eventIndex] = generateEvent(day, type, numParticipants, revenue);
                }
                break;
            case 2:
                printReport(events, numDays, numEventsPerDay);
                break;
            case 3:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                break;
        }
    } while (choice != 3);

    // Free allocated memory
    for (int i = 0; i < numDays; i++) {
        free(events[i]);
    }
    free(events);
    free(dayWiseRevenue);

    return 0;
}
