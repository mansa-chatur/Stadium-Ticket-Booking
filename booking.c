#include <stdio.h>
#include <string.h>

#define maximum_name_length 50

int main() {
  FILE *file = fopen("booking_info.txt", "w");
  if (file == NULL) {
    fprintf(stderr, "Error opening the file.\n");
    return 1;
  }

  int NUMBER_OF_BOOKINGS;
  printf("Enter the number of bookings: ");
  scanf("%d", &NUMBER_OF_BOOKINGS);

  for (int i = 0; i < NUMBER_OF_BOOKINGS; i++) {
    char name[maximum_name_length];
    int R0W, SEAT;

    printf("\nEnter details for booking %d:\n", i + 1);

    // Clear the input buffer
    while (getchar() != '\n')
      ;

    printf("Enter name: ");
    fgets(name, maximum_name_length, stdin);
    name[strcspn(name, "\n")] = '\0'; // Remove newline character if present

    printf("Enter R0W number: ");
    scanf("%d", &R0W);

    printf("Enter SEAT number: ");
    scanf("%d", &SEAT);

    fprintf(file, "%s %d %d\n", name, R0W, SEAT);
  }

  fclose(file);

  printf("\nBooking information has been written to 'booking_info.txt'.\n");

  return 0;
}
