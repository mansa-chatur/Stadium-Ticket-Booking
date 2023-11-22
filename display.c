#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define number_of_rows 10
#define seats_per_row 10
#define MAX_NAME_LENGTH 50

// Structure to represent a seat
// struct seat: Represents a seat with information about its row, seat number,
// and a pointer to the next seat (for circular queue implementation).
struct Seat {
  int ROW;
  int seatNUM;
  struct Seat *next;
};

// Function to initialize an empty seat queue
// CREATE_SEAT_QUEUE():Initializes an empty seat queue and returns a pointer to
// the rear of the queue.

struct Seat *CREATE_SEAT_QUEUE() { return NULL; }

// Function to enqueue a seat (book a seat)
// enqueue:Adds a new seat to the queue (books a seat).Uses a circular queue
// implementation.

struct Seat *enqueue(struct Seat *REAR, int ROW, int seat_num) {
  struct Seat *NEW_seat = (struct Seat *)malloc(sizeof(struct Seat));
  if (NEW_seat == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(1);
  }
  NEW_seat->ROW = ROW;
  NEW_seat->seatNUM = seat_num;
  NEW_seat->next = NULL;

  if (REAR == NULL) {
    NEW_seat->next = NEW_seat; // First seat, circular queue
  } else {
    NEW_seat->next = REAR->next;
    REAR->next = NEW_seat;
  }

  return NEW_seat;
}

// Function to dequeue a seat (release a seat)
// dequeue:Removes a seat from the queue (cancels a booked seat).Uses a circular
// queue implementation.

struct Seat *dequeue(struct Seat *REAR, int *ROW, int *seatNUM) {
  if (REAR == NULL) {
    fprintf(stderr, "Seat queue is empty.\n");
    exit(1);
  }

  struct Seat *front = REAR->next;
  *ROW = front->ROW;
  *seatNUM = front->seatNUM;

  if (REAR->next == REAR) {
    free(front);
    REAR = NULL; // The last seat is being dequeued
  } else {
    REAR->next = front->next;
    free(front);
  }

  return REAR;
}

// Function to display the seating layout
// displayseating():Displays the current seating layout using 'X' for booked
// seats and 'O' for unbooked seats.

void displaySeating(bool seats[number_of_rows][seats_per_row]) {
  printf("Seating Layout:\n");
  for (int i = 0; i < number_of_rows; i++) {
    for (int j = 0; j < seats_per_row; j++) {
      printf("%c ", seats[i][j] ? 'X' : 'O');
    }
    printf("\n");
  }
}

int main() {
  FILE *bookingFile = fopen("custom_booking_info.txt", "w");
  if (bookingFile == NULL) {
    fprintf(stderr, "Error opening the file.\n");
    return 1;
  }

  int totalBookings;
  printf("Enter the total number of bookings: ");
  scanf("%d", &totalBookings);

  for (int bookingIndex = 0; bookingIndex < totalBookings; bookingIndex++) {
    char customerName[MAX_NAME_LENGTH];
    int selectedRow, selectedSeat;

    printf("\nEnter details for booking %d:\n", bookingIndex + 1);

    while (getchar() != '\n')
      ;

    printf("Enter customer name: ");
    fgets(customerName, MAX_NAME_LENGTH, stdin);
    customerName[strcspn(customerName, "\n")] =
        '\0'; // Remove newline character if present

    printf("Enter selected row number: ");
    scanf("%d", &selectedRow);

    printf("Enter selected seat number: ");
    scanf("%d", &selectedSeat);

    fprintf(bookingFile, "%s %d %d\n", customerName, selectedRow, selectedSeat);
  }

  fclose(bookingFile);

  printf(
      "\nBooking information has been written to 'custom_booking_info.txt'.\n");

  return 0;
}
