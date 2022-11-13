/** =======================================================================
 * Author: Shrey Ghosh
 * Date:  Nov 16, 2021
 *
 * Purpose   Program simulating Conway's Game of Life
 *
 * Course:   Programming 25
 * Teacher:  Ms. Deepeka Dalal
* ========================================================================*/

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    // Declaration of intial variables
    int userHeight, userLength;
    int cellInput;
    int genNum;
    int yVal {0}, xVal {0};

    cout << "Welcome to Conways Game of Life." << endl;

    //User input for height
    cout << "Please enter the gameboard height: " ;
    cin >> userHeight;

    while (userHeight <= 0)
    {
        cout << "Please enter a positive height: " ;
        cin >> userHeight;
    }

    //User input for length
    cout << "Please enter the gameboard length: " ;
    cin >> userLength;

    while (userLength <= 0)
    {
        cout << "Please enter a positive length: " ;
        cin >> userLength;
    }

    // User input for amount of generations to be shown
    cout << "Please enter the amount of generation that you would like to run: ";
    cin >> genNum;

    while (genNum <= 0)
    {
        cout << "Please enter a positive number of generations: " ;
        cin >> genNum;
    }

    cout << endl;

    // Converts height and length to constant unsigned integers
    const size_t rowNum = userHeight;
    const size_t colNum = userLength;

    // Two arrays declared - one for printing and one for comparing (copyList and gameBoard respectively)
    string gameBoard[rowNum][colNum];
    string copyList[rowNum][colNum];

    // Declaration of constant unsigned integer for gameboard total size
    const size_t boardSize = userHeight * userLength;
    int countNum = 1;

    // Populating both vectors with numbers according to desired columns and rows
    // Saved as a string
    for (int i{0}; i < rowNum; i++)
    {
        for (int j{0}; j < colNum; j++)
        {
            gameBoard [i][j] = to_string(countNum);
            copyList[i][j] = to_string(countNum);
            countNum ++;
        }
    }

    // Displays unfilled gameboard to the user
    cout << "Unfilled Gameboard: " << endl << endl;

    for( auto &row : gameBoard)
    {
        for(auto col : row)
             cout << setw(4) << col << " ";
        cout<<endl;
    }
    cout << endl;

    // Do - while loop for purpose of asking user to populate gameboard
    do
    {
        cout << "Please enter the cell you would like to bring to life (0 to quit): ";
        cin >> cellInput;

        // Finds the location of the cell and marks it with @
        if (cellInput <= boardSize && cellInput > 0)
        {
                    if (cellInput % colNum != 0)
                        yVal = floor(cellInput/colNum);
                    else if (cellInput % colNum == 0)
                        yVal = floor(cellInput/colNum -1);
                    if (cellInput % colNum == 0)
                        xVal = colNum - 1;
                    else if (cellInput % colNum != 0)
                        xVal = (cellInput % colNum) - 1;
                    gameBoard[yVal][xVal] = "@";
                    copyList[yVal][xVal] = "@";

        }

        // Takes care of invalid inputs
        else if (cellInput < 0 || cellInput > boardSize)
        {
            cout << "Please choose a valid number of cells as shown on the gameboard! " << endl;
        }

    } while (cellInput != 0);


    // Shows initial gameboard with @ symbols to user
    cout << "This is your initial gameboard: " << endl << endl;

    for( auto &row : gameBoard)
    {
        for(auto col : row)
            cout << setw(4) << col << " ";
        cout<<endl;
    }
    cout << endl;

    // For loop runs the code for every generation that the user specified
    for (int currentGen{1}; currentGen <= genNum; currentGen++)
    {

        vector<int>stayVec;
        vector<int>underVec;
        vector<int>overVec;
        vector<int>newVec;

        // For loop runs the code for every string in the vector (gameboard)
        for (int currentNum{1}; currentNum <= boardSize; currentNum++)
        {

           // Calculates position of the particular string (number)
           int xCoord = 0;
           int yCoord = 0;
           if (currentNum % colNum != 0)
           {
               yCoord = floor(currentNum/colNum);
               xCoord = (currentNum % colNum) - 1;
           }
           else if (currentNum % colNum == 0)
           {
               yCoord = floor((currentNum/colNum) -1);
               xCoord = colNum - 1;
           }

           // Values to store how values are around the particular number
           int aroundIt = 0;
           int checkAbove = yCoord - 1;
           int checkBelow = yCoord + 1;
           int checkLeft = xCoord - 1;
           int checkRight = xCoord + 1;

           // Runs if there are rows above the number
           if (checkAbove >= 0)
           {
                     // Adds 1 to around it if there is a @ directly above, otherwise does nothing
                   if (gameBoard[yCoord - 1][xCoord] == "@")
                       aroundIt += 1;

                   //  Adds 1 to around it if there is a @ to the left and above
                   if (checkLeft >= 0)
                   {
                       if (gameBoard[yCoord - 1][xCoord - 1] == "@")
                           aroundIt += 1;
                   }

                   // Adds 1 to around it if there is a @ to the right and above
                   if (checkRight < colNum)
                   {
                       if (gameBoard[yCoord - 1][xCoord + 1] == "@")
                           aroundIt += 1;
                   }
            }

           // Does same as above code but for the row below (checks directly above, above right, above left - adds to around it accordingly)
           if (checkBelow < rowNum)
           {
                   if (gameBoard[yCoord + 1][xCoord] == "@")
                       aroundIt += 1;
                   if (checkLeft >= 0)
                   {
                       if (gameBoard[yCoord + 1][xCoord - 1] == "@")
                           aroundIt += 1;
                   }
                   if (checkRight < colNum)
                   {
                       if (gameBoard[yCoord + 1][xCoord + 1] == "@")
                           aroundIt += 1;
                   }
           }

           // Adds 1 to around it if there is an @ directly beside current number (left)
           if (checkLeft >= 0)
           {
                   if (gameBoard[yCoord][xCoord - 1] == "@")
                           aroundIt += 1;
           }

           // Adds 1 to around it if there is an @ directly beside current number (right)
           if (checkRight < colNum)
           {
               if (gameBoard[yCoord][xCoord + 1] == "@")
                       aroundIt += 1;
           }

           // Checks whether the cell overpopulates, lives, gets born, or dies depending on how many are around it (found by previous code section)
           if (aroundIt < 2 && aroundIt >= 0 && gameBoard[yCoord][xCoord] == "@")
           {
               underVec.push_back(currentNum);
               copyList[yCoord][xCoord] = to_string(currentNum);

           }
           else if (aroundIt > 3 && gameBoard[yCoord][xCoord] == "@")
           {
               overVec.push_back(currentNum);
               copyList[yCoord][xCoord] = to_string(currentNum);

           }
           else if (aroundIt == 3 && gameBoard[yCoord][xCoord] != "@")
           {
               newVec.push_back(currentNum);
               copyList[yCoord][xCoord] = "@";

           }
           else if ((aroundIt == 3 || aroundIt == 2) && (gameBoard[yCoord][xCoord] == "@"))
               stayVec.push_back(currentNum);

        }

        // Copies the current values in copyList (printing list) to gameBoard (calculation list) for comparison on next generation
        std::copy(&copyList[0][0], &copyList[0][0]+rowNum*colNum,&gameBoard[0][0]);

        cout << "Generation " << currentGen << endl;

        // Displays to the user the gameboard after all actions in current generation
        for( auto &row : copyList)
        {
            for(auto col : row)
                cout << setw(4) << col << " ";
            cout<<endl;
        }

        cout << endl;

        // Displays to user which cells have overpopulated, underpopulated, lived, born
        cout << "Cells that died of underpopulation: ";

        for(int elem : underVec)
            cout << elem << " ";
        cout << endl;

        cout << "Cells that died of overpopulation: ";

        for(int elem : overVec)
            cout << elem << " ";
        cout << endl;

        cout << "Cells that came to life: ";

        for(int elem : newVec)
            cout << elem << " ";
        cout << endl;

        cout << "Cells that stayed alive: ";

        for(int elem : stayVec)
            cout << elem << " ";
        cout << endl;
        cout << endl;
    }

    return 0;
}
