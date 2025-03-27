// C Program for Dino Game (Linux/macOS Compatible)
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

// Cross-platform kbhit() function for Linux/macOS
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// Function to display game information on the console
void displayGameInfo()
{
    clearScreen();
    moveTo(10, 2);
    printf("Press X to Exit, Press Space to Jump");
    moveTo(62, 2);
    printf("SCORE : ");
    moveTo(1, 25);
    for (int x = 0; x < 79; x++)
        printf("=");
}

// Global variables for jump height and game speed
int jumpHeight = 0, gameSpeed = 40;

// Function to display the character on the console
void displayCharacter(int jumpType)
{
    static int animationState = 1;

    if (jumpType == 0)
        jumpHeight = 0;
    else if (jumpType == 2)
        jumpHeight--;
    else
        jumpHeight++;

    moveTo(2, 15 - jumpHeight);
    printf("                ");
    moveTo(2, 16 - jumpHeight);
    printf("     ooo       ");
    moveTo(2, 17 - jumpHeight);
    printf("    oooooo     ");
    moveTo(2, 18 - jumpHeight);
    printf("   oooooooo    ");
    moveTo(2, 19 - jumpHeight);
    printf("  oooo oooo   ");
    moveTo(2, 20 - jumpHeight);
    printf(" ooooo oo ooo  ");
    moveTo(2, 21 - jumpHeight);
    printf(" oooooo  ooooo ");
    moveTo(2, 22 - jumpHeight);
    printf(" ooooo   ooooo ");
    moveTo(2, 23 - jumpHeight);

    if (jumpType == 1 || jumpType == 2)
    {
        printf("   oo   ooo    ");
        moveTo(2, 24 - jumpHeight);
        printf("   o    o      ");
    }
    else if (animationState == 1)
    {
        printf("  ooo    oo    ");
        moveTo(2, 24 - jumpHeight);
        printf("     o         ");
        animationState = 2;
    }
    else if (animationState == 2)
    {
        printf("   ooo   o     ");
        moveTo(2, 24 - jumpHeight);
        printf("         o     ");
        animationState = 1;
    }

    moveTo(2, 25 - jumpHeight);
    if (jumpType != 0)
    {
        printf("                ");
    }
    else
    {
        printf("================");
    }

    pauseGame(gameSpeed);
}

// Function to display the obstacle on the console
void displayObstacle()
{
    static int obstaclePosition = 0, score = 0;

    if (obstaclePosition == 56 && jumpHeight < 4)
    {
        score = 0;
        gameSpeed = 40;
        moveTo(36, 8);
        printf("Game Over!");
        getchar(); // Wait for keypress
        moveTo(36, 8);
        printf("          ");
    }

    moveTo(74 - obstaclePosition, 20);
    printf("XX    XX ");
    moveTo(74 - obstaclePosition, 21);
    printf(" XX  XX  ");
    moveTo(74 - obstaclePosition, 22);
    printf("  XXXX   ");
    moveTo(74 - obstaclePosition, 23);
    printf("   XX    ");

    obstaclePosition++;
    if (obstaclePosition == 73)
    {
        obstaclePosition = 0;
        score++;
        moveTo(70, 2);
        printf("     ");
        moveTo(70, 2);
        printf("%d", score);
        if (gameSpeed > 20)
            gameSpeed--;
    }
}

// Main function
int main()
{
    char input;
    int i;
    displayGameInfo();

    while (1)
    {
        while (!kbhit())
        {
            displayCharacter(0);
            displayObstacle();
        }

        input = getchar();
        if (input == ' ')
        {
            for (i = 0; i < 10; i++)
            {
                displayCharacter(1);
                displayObstacle();
            }
            for (i = 0; i < 10; i++)
            {
                displayCharacter(2);
                displayObstacle();
            }
        }
        else if (input == 'x')
        {
            return 0;
        }
    }

    return 0;
}
