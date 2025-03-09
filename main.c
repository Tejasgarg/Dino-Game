// C Program for Dino Game
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <time.h>
#include <fcntl.h>

// Function to move the cursor to a specific position
void moveTo(int x, int y)
{
    printf("\033[%d;%dH", y, x);
    fflush(stdout);
}

// Function to clear the screen
void clearScreen()
{
    system("clear");
}

// Function to pause execution for a given number of milliseconds
void pauseGame(unsigned int milliseconds)
{
    usleep(milliseconds * 1000);
}
// Main function
int main()
{
    // Set console mode and initialize variables
    system("mode con: lines=29 cols=82");
    char input;
    int i;
    displayGameInfo();

    // Game loop
    while (true) {
        // Continuous display of character and obstacle
        // until a key is pressed
        while (!kbhit()) {
            displayCharacter();
            displayObstacle();
        }

        // Handle user input
        input = getch();
        if (input == ' ') {
            // Jump animation when the space key is pressed
            for (i = 0; i < 10; i++) {
                displayCharacter(1);
                displayObstacle();
            }
            for (i = 0; i < 10; i++) {
                displayCharacter(2);
                displayObstacle();
            }
        }
        else if (input == 'x') {
            // Exit the game if the 'X' key is pressed
            return (0);
        }
    }

    return 0;
}
