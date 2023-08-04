#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    SLEEPER,
    AC3,
    AC2,
    AC1
} TravelClass;

typedef struct {
    char name[50];
    int passenger_id;
    char boarding_train[20];
    char boarding_station[50];
    TravelClass travel_class;
    char destination_station[50];
    int train_id;
    int seat_number;
    // Add other fields if necessary
    struct Passenger* next;
} Passenger;

typedef struct {
    int total_seats;
    int booked_seats;
} Bogie;

typedef struct {
    int train_id;
    int num_bogies;
    Bogie sleeper_bogies[10];
    Bogie ac3_bogies[5];
    Bogie ac2_bogies[3];
    Bogie ac1_bogies[2];
    // Add other fields if necessary
} Train;

typedef struct {
    Train train_data;
    Passenger* passengers;
    struct TrainNode* next;
} TrainNode;

typedef struct {
    TrainNode* head;
} TrainList;

void initializeTrainList(TrainList* list) {
    list->head = NULL;
}

Passenger* createPassengerNode(char name[], int passenger_id, char boarding_train[], char boarding_station[], TravelClass travel_class, char destination_station[], int train_id, int seat_number) {
    Passenger* newPassenger = (Passenger*)malloc(sizeof(Passenger));
    if (newPassenger == NULL) {
        printf("Memory allocation failed for the passenger.\n");
        return NULL;
    }

    strcpy(newPassenger->name, name);
    newPassenger->passenger_id = passenger_id;
    strcpy(newPassenger->boarding_train, boarding_train);
    strcpy(newPassenger->boarding_station, boarding_station);
    newPassenger->travel_class = travel_class;
    strcpy(newPassenger->destination_station, destination_station);
    newPassenger->train_id = train_id;
    newPassenger->seat_number = seat_number;
    newPassenger->next = NULL;

    return newPassenger;
}

void insertPassengers(TrainList* list, char name[], int passenger_id, char boarding_train[], char boarding_station[], TravelClass travel_class, char destination_station[], int train_id) {
    TrainNode* currentTrainNode = list->head;
    while (currentTrainNode != NULL) {
        if (currentTrainNode->train_data.train_id == train_id) {
            // Check for seat availability and allocate seats
            // Assume there is a function available to do this: allocateSeat(currentTrainNode, travel_class, seat_number);

            // Create a new passenger node
            int seat_number = 1; // Assume the seat number is 1 for simplicity (should be allocated properly)
            Passenger* newPassenger = createPassengerNode(name, passenger_id, boarding_train, boarding_station, travel_class, destination_station, train_id, seat_number);
            if (newPassenger == NULL) {
                printf("Failed to create a new passenger node.\n");
                return;
            }

            // Insert the new passenger node into the linked list
            if (currentTrainNode->passengers == NULL) {
                currentTrainNode->passengers = newPassenger;
            } else {
                Passenger* currentPassenger = currentTrainNode->passengers;
                while (currentPassenger->next != NULL) {
                    currentPassenger = currentPassenger->next;
                }
                currentPassenger->next = newPassenger;
            }

            printf("Reservation done successfully.\n");
            return;
        }
        currentTrainNode = currentTrainNode->next;
    }

    printf("Reservation failed. Train with ID %d not found.\n", train_id);
}



void deletePassengers(TrainList* list, int passenger_id) {
    TrainNode* currentTrainNode = list->head;
    while (currentTrainNode != NULL) {
        Passenger* prevPassenger = NULL;
        Passenger* currentPassenger = currentTrainNode->passengers;

        while (currentPassenger != NULL) {
            if (currentPassenger->passenger_id == passenger_id) {
                // Found the passenger to delete
                if (prevPassenger == NULL) {
                    // The passenger to delete is the head of the passenger list
                    currentTrainNode->passengers = currentPassenger->next;
                } else {
                    prevPassenger->next = currentPassenger->next;
                }
                free(currentPassenger);
                printf("Reservation cancelled successfully.\n");
                return;
            }

            prevPassenger = currentPassenger;
            currentPassenger = currentPassenger->next;
        }

        currentTrainNode = currentTrainNode->next;
    }

    printf("Reservation cancellation failed. Passenger with ID %d not found.\n", passenger_id);
}



void sortByTravelDate(TrainList* list, int passenger_id) {
    TrainNode* currentTrainNode = list->head;
    while (currentTrainNode != NULL) {
        Passenger* currentPassenger = currentTrainNode->passengers;
        int found = 0;

        while (currentPassenger != NULL) {
            if (currentPassenger->passenger_id == passenger_id) {
                found = 1;
                break;
            }
            currentPassenger = currentPassenger->next;
        }

        if (found) {
            // Implementation of sorting passenger destination stations by travel date
            // You can use any sorting algorithm to sort the destination stations based on travel date
            // For simplicity, we will just print the destination stations in the order they appear in the linked list

            printf("List of destination stations for passenger with ID %d:\n", passenger_id);
            currentPassenger = currentTrainNode->passengers;
            while (currentPassenger != NULL) {
                if (currentPassenger->passenger_id == passenger_id) {
                    printf("%s\n", currentPassenger->destination_station);
                }
                currentPassenger = currentPassenger->next;
            }

            return;
        }

        currentTrainNode = currentTrainNode->next;
    }

    printf("Passenger with ID %d not found.\n", passenger_id);
}



void sortTrains(TrainList* list) {
    // Count the number of passengers on each train
    int trainCount[1000] = {0}; // Assuming train IDs are within the range [1, 1000]

    TrainNode* currentTrainNode = list->head;
    while (currentTrainNode != NULL) {
        Passenger* currentPassenger = currentTrainNode->passengers;
        while (currentPassenger != NULL) {
            trainCount[currentTrainNode->train_data.train_id]++;
            currentPassenger = currentPassenger->next;
        }
        currentTrainNode = currentTrainNode->next;
    }

    // Create an array of train IDs and their corresponding passenger counts
    int numTrains = 0;
    int trainIDs[1000] = {0};
    int passengerCounts[1000] = {0};

    currentTrainNode = list->head;
    while (currentTrainNode != NULL) {
        int trainID = currentTrainNode->train_data.train_id;
        int passengerCount = trainCount[trainID];

        int i = 0;
        while (i < numTrains && passengerCounts[i] > passengerCount) {
            i++;
        }

        for (int j = numTrains; j > i; j--) {
            trainIDs[j] = trainIDs[j - 1];
            passengerCounts[j] = passengerCounts[j - 1];
        }

        trainIDs[i] = trainID;
        passengerCounts[i] = passengerCount;

        numTrains++;

        currentTrainNode = currentTrainNode->next;
    }

    // Print the sorted list of trains and their passenger counts
    printf("Sorted list of trains by number of passengers:\n");
    for (int i = 0; i < numTrains; i++) {
        printf("Train ID: %d, Passenger Count: %d\n", trainIDs[i], passengerCounts[i]);
    }
}



void promotePassengers(TrainList* list, int train_id, int date_of_travel) {
    TrainNode* currentTrainNode = list->head;

    while (currentTrainNode != NULL) {
        if (currentTrainNode->train_data.train_id == train_id) {
            Passenger* currentPassenger = currentTrainNode->passengers;

            while (currentPassenger != NULL) {
                if (currentPassenger->travel_class != AC1) {
                    // Promote passengers to the next travel class if seats are available and consent is given
                    int bogie_index = currentPassenger->travel_class;
                    int seat_number = currentPassenger->seat_number;

                    switch (currentPassenger->travel_class) {
                        case SLEEPER:
                            if (currentTrainNode->train_data.ac3_bogies[0].booked_seats < currentTrainNode->train_data.ac3_bogies[0].total_seats) {
                                currentPassenger->travel_class = AC3;
                                currentTrainNode->train_data.ac3_bogies[0].booked_seats++;
                                currentTrainNode->train_data.sleeper_bogies[0].booked_seats--;
                                seat_number = currentTrainNode->train_data.ac3_bogies[0].booked_seats;
                            }
                            break;
                        case AC3:
                            if (currentTrainNode->train_data.ac2_bogies[0].booked_seats < currentTrainNode->train_data.ac2_bogies[0].total_seats) {
                                currentPassenger->travel_class = AC2;
                                currentTrainNode->train_data.ac2_bogies[0].booked_seats++;
                                currentTrainNode->train_data.ac3_bogies[0].booked_seats--;
                                seat_number = currentTrainNode->train_data.ac2_bogies[0].booked_seats;
                            }
                            break;
                        case AC2:
                            if (currentTrainNode->train_data.ac1_bogies[0].booked_seats < currentTrainNode->train_data.ac1_bogies[0].total_seats) {
                                currentPassenger->travel_class = AC1;
                                currentTrainNode->train_data.ac1_bogies[0].booked_seats++;
                                currentTrainNode->train_data.ac2_bogies[0].booked_seats--;
                                seat_number = currentTrainNode->train_data.ac1_bogies[0].booked_seats;
                            }
                            break;
                        default:
                            break;
                    }

                    currentPassenger->seat_number = seat_number;
                }

                currentPassenger = currentPassenger->next;
            }

            printf("Promotion of passengers on train ID %d and travel date %d completed.\n", train_id, date_of_travel);
            return;
        }

        currentTrainNode = currentTrainNode->next;
    }

    printf("Train with ID %d not found.\n", train_id);
}




int main() {
    initializeTrainList();
    int choice;
    while (1) {
        printf("\n                Choices                            \n");
        printf("\n 1.Insert     \n");
        printf("\n 2.Delete    \n");
        printf("\n 3. display   \n");
        printf("\n 4.get_List_Destination\n");
        printf("\n 5.SortByTravelDate\n");
        printf("\n 6.Sort_Trains\n");
        printf("\n 7.PromotePassengers     \n");
        printf("\n 8.Exit       \n");
        printf("\n--------------------------------------\n");
        printf("Enter your choice:\t");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            // Get input for insert and call insertPassengers function
            char name[50];
            int passenger_id, train_id;
            char boarding_train[20], boarding_station[50], destination_station[50];
            int travel_class;
            printf("Enter passenger name: ");
            scanf("%s", name);
            printf("Enter passenger ID: ");
            scanf("%d", &passenger_id);
            printf("Enter boarding train: ");
            scanf("%s", boarding_train);
            printf("Enter boarding station: ");
            scanf("%s", boarding_station);
            printf("Enter travel class (0: SLEEPER, 1: AC3, 2: AC2, 3: AC1): ");
            scanf("%d", &travel_class);
            printf("Enter destination station: ");
            scanf("%s", destination_station);
            printf("Enter train ID: ");
            scanf("%d", &train_id);

            insertPassengers(name, passenger_id, boarding_train, boarding_station, travel_class, destination_station, train_id);
            break;

        case 2:
            // Get input for delete and call deletePassengers function
            int delete_passenger_id;
            printf("Enter passenger ID to delete: ");
            scanf("%d", &delete_passenger_id);
            deletePassengers(delete_passenger_id);
            break;

        case 3:
            // Call display function
            display();
            break;

        case 4:
            // Call get_List_Destination function
            get_List_Destination();
            break;

        case 5:
            // Get input for sortByTravelDate and call sortByTravelDate function
            int passenger_id_to_sort;
            printf("Enter passenger ID to sort by travel date: ");
            scanf("%d", &passenger_id_to_sort);
            sortByTravelDate(passenger_id_to_sort);
            break;

        case 6:
            // Call Sort_Trains function
            Sort_Trains();
            break;

        case 7:
            // Call Promote_Passengers function
            Promote_Passengers(trainList.head);
            break;

        case 8:
            exit(0);
            break;

        default:
            printf("\n Wrong Choice:\n");
            break;
        }
    }
    return 0;
}
