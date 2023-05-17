#include <stdio.h>
#include <windows.h>
#pragma warning(disable:4996)

char input[32];
int outputAmount = 0;

int main() {
    do {
        // Get user input
        getInputFromUser();
        // Call the timer for the 1st time to start the timer
        timer();
        // Caluclate length of input
        int length = strlen(input);
        // If the amount of strings printed is equal to the factorial of the input length, complete this run
        if (printStrings(0, length, input) == calculateLength(length)) {
            printf("Process finished successfully!\n");
            printf("That string had %d premutations.\n", calculateLength(length));
        }
        else {
            // If the program did not work correctly, exit the program early to prevent further issues.
            printf("\nAn error occurred during the process!\n");
            printf("Press any key to continue...\033[30m");
            return 0;
        }
        // Call timer for the 2nd time so the time elapsed can be displayed
        timer();
        // Ask the user if they wish to continue, if not: exit the program
        printf("Press Q to exit or any other key to continue.\n");
    } while (tolower(getch()) != 'q');
    printf("Press any key to continue...\033[30m");
    return 0;
}

int getInputFromUser() {
    // Simply take input from the user
    printf("Enter a string to get premutations from (max length is 32)\n");
    fgets(input, 32, stdin);
    input[strlen(input) - 1] = NULL;
    return 0;
}

//Get all the premutations
int printStrings(int depth, int length, char str[]) {
    for (int i = depth; i < length; i++) {
        // Reset the string if depth is 0
        if (depth == 0)
            strcpy(str, input);
        // Swap str[depth] and str[i] (depth and i may be equal to eachother)
        char temp = str[depth];
        str[depth] = str[i];
        str[i] = temp;
        // If this is the highest depth this string can have, print the string
        if (depth + 1 == length) {
            printf("\033[36m%s\n", str);
            outputAmount++;
        }
        else {
            // If this is not the highest depth, go deeper
            printStrings(depth + 1, length, str);
        }
    }
    if (depth == 0) {
        // Return the amount of premutations
        int ret = outputAmount;
        outputAmount = 0;
        return ret;
    }
    return 0;
}

int calculateLength(int length) {
    // Calculate the factorial of length (which is the total number of premutations)
	int ret = 1;
	for (int i = 1; i < length+1; i++) {
		ret = ret * i;
	}
	return ret;
}

// Timer Logic
int time = 0;
int timer() {
    // Set value of Time on every uneven call
    if (time == 0) {
        time = GetTickCount64();
    }
    // Print the time since last call on every even call
    else {
        char display[200];
        printf("Time elapsed: %dms\n", (int)GetTickCount64() - time);
        time = 0;
    }
    return 0;
}