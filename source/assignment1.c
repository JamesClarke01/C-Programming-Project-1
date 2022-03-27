/*
Program to allow a user to manage their PIN number within an ATM machine.

This program allows the user to :
1. Enter a PIN and verify if it is the same as the PIN stored in the program.
2. Change their stored PIN by asking for their new PIN twice and making sure that they are both the same.
3. Display the number of times that a PIN was entered correctly and incorrectly.
4. End the program.

Author: James Clarke

Completion Date: 18/11/2020

Compiler Used: GCC C++ compiler in Visual Studio Code ~ https://code.visualstudio.com/docs/cpp/config-mingw

Note:   My program plays an error sound when an invalid input is entered.
        These sounds play fine when the code is run from a compiled executable, but do not play when running/debugging the code within the Visual Studio Code IDE.
*/

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#define PIN_SIZE 4                  //how many digits in pin
#define DEFAULT_PIN {1, 2, 3, 4}    //the default pin
#define SLEEP 1                     //how many seconds to wait after menu option ends
#define EXIT_WAIT 2                 //how many seconds to wait before exiting the program
#define MENU_BORDER "\n\n============================================\n"    //used for formatting the menu

//function for pin input (uses pointers to edit global array variables)
void PinInput(int *inputPin)
{
    int digitInt;
    char digitChar;

    for (int i = 0; i < PIN_SIZE; ++i)   //loops 4 times to ensure the PIN is 4 characters long
    {
        int validEntered = 0;

        while (validEntered == 0)   //while loop runs until a valid character is enterred
        {
            digitChar = getch();    //gets an entered character then moves to next line of code without the user having to press enter

            digitInt = (digitChar - '0'); //turns the character into an integer

            if ((digitInt >= 0) && (digitInt <= 9)) //makes sure that only the integers 0-9 are accepted (any other characters will not be included as their ascii value will be out of the range of 0-9)
            {
                inputPin[i] = digitInt; //sets the current item in the array to the inputted int
                printf("*");            //prints * when a valid character is input
                validEntered = 1;       //exits the while loop
            }
            else
            {
                printf("\a"); //plays error sound when invalid character is entered
            }
        }
    }
}

//Main function
int main(void)
{
    //defining arrays
    int pin[PIN_SIZE] = DEFAULT_PIN;
    int inputPin[PIN_SIZE];
    int newPin1[PIN_SIZE];
    int newPin2[PIN_SIZE];

    //menu variables
    int menuActive = 1;
    int menuNumber = 0;

    //pin entry counters
    int successfull = 0;
    int incorrect = 0;

    //used for the validation process
    int digitInt;
    char digitChar;

    while (menuActive == 1) //menu will always display once the menuActive variable is equal to 1
    {
        switch (menuNumber) //switch statement for each option on the menu
        {

        case 0: //this switch case is ran first when the program first starts
        {
            //instructions and menu below
            printf("\nWelcome, please enter the menu number corresponding to what you would like to do (1 - 4 inclusive):\n");
            printf("1. Verify your PIN\n");
            printf("2. Change your PIN\n");
            printf("3. Check how many times a PIN was entered\n");
            printf("4. Exit the program\n");

            int validEntered = 0;

            while (validEntered == 0) //while loop for menu number input (will always loop until valid character is entered)
            {
                digitChar = getch(); //gets an entered character then moves to next line of code without the user having to press enter

                digitInt = (digitChar - '0'); //turns the character into an integer

                if ((digitInt >= 1) && (digitInt <= 4)) //makes sure that only the integers 1-4 are accepted (any other characters will not be included as their ascii value will be out of the specified range)
                {
                    menuNumber = digitInt;                            //changing this variable means it will go to the entered menu number when the loop loops around
                    printf("\nMenu option %d selected.\n", menuNumber); //displays the menunumber entered
                    validEntered = 1;
                }
                else
                {
                    printf("\a"); //plays error sound when invalid character is entered
                }
            }

            break;
        }

        case 1:
        {
            printf("\nPlease enter your %d digit pin (numbers 0-9 inclusive only):\n", PIN_SIZE);

            PinInput(inputPin); //calls the function to enter the pin and edits the inputPin array

            printf("\n\n"); //skips a line

            if (memcmp(inputPin, pin, sizeof(inputPin)) == 0) //compares the input pin to the actual pin (returns 0 if both are equal)
            {
                successfull += 1; //adds 1 to the successful pin entry counter
                printf("PIN is correct!");
            }
            else
            {
                incorrect += 1; //adds 1 to the incorect pin entry
                printf("PIN is incorrect!");
            }
            
            sleep(SLEEP); //program waits for specified amount of time
            
            printf(MENU_BORDER); //prints a border

            menuNumber = 0; //sets the switch statement to case 0 so the main menu displays when the loop goes back around
            break;
        }

        case 2:
        {
            printf("\nEnter a new %d digit PIN number (numbers 0-9 inclusive only): \n", PIN_SIZE);

            PinInput(newPin1); //calls the function to enter the pin and edits the newPin1 array

            printf("\nPlease re-enter your new PIN (numbers 0-9 inclusive only):\n");

            PinInput(newPin2); //calls the function to enter the pin and edits the newPin2 array

            if (memcmp(newPin1, newPin2, sizeof(newPin1)) == 0) //checks if the two entered pins are the same (returns 0 if both are equal)
            {
                //runs if two pins match
                if (memcmp(newPin1, pin, sizeof(newPin1)) == 0) //checks if new pin is the same as the old pin
                {
                    //runs if new pin and old pin are the same
                    printf("\n\nThis is already your PIN!");
                }
                else
                {
                    //runs if new pin and old pin are not the same
                    for (int i = 0; i < PIN_SIZE; ++i) //for loop changes the users old pin to the users new pin element by element in the array
                    {
                        pin[i] = newPin1[i];
                    }

                    printf("\n\nYour PIN has been changed.");
                }
            }
            else
            {
                //runs if the two entered pins don't match
                printf("\n\nError, your PINs do not match, PIN not changed.");
            }
            
            sleep(SLEEP); //program waits for specified amount of time

            printf(MENU_BORDER); //prints a border

            menuNumber = 0; //sets the switch statement to case 0 so the main menu displays when the loop goes back around
            break;
        }

        case 3:
        {
            printf("\nPIN entered correctly %d times and incorrectly %d times.", successfull, incorrect); //prints the amount of successful and incorrect entries

            sleep(SLEEP); //program waits for specified amount of time

            printf(MENU_BORDER); //prints a border

            menuNumber = 0; //sets the switch statement to case 0 so the main menu displays when the loop goes back around
            break;
        }

        case 4:
        {
            printf("\nThank you for using this program, goodbye!\n\n");

            sleep(EXIT_WAIT); //waits before exiting program

            menuActive = 0; //exits the while loop
            break;
        }

        default:
        {
            //the user should never see this error but was included as an extra measure
            printf("\nInvalid option entered!\n\n");
            menuNumber = 0; //sets the switch statement to case 0 so the main menu displays when the loop goes back around
        }
        }
    }
    return 0;
}
