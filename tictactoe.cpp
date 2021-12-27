//Allows inputs/outputs into the console
#include <iostream>
//Allows manipulation of outputs.
#include <iomanip>
//Allows for number randomization.
#include <cstdlib>
#include <ctime>
//Makes writing code easier.
using namespace std;
//Declares constant for how many cin characters to ignore.
const int IGNORE = 10000;
//Declares constants for board dimensions.
const int WIDTH = 3;
const int HEIGHT = 3;
//Declares constants for matches to win.
const int WIN = 3;
//Declares magic number constants for CodeGrade.
const int BORDER = 34;
const int TEXT = 29;
const int FOUR = 4; 
//Prototypes function to select game mode.
void singleOrMulti(int&, bool&, bool);
//Prototypes function to display game board.
void printBoard(char [][WIDTH]);
//Prototypes function for the different game board.
void singlePlayer(char [][WIDTH], bool&, int&, bool, int&);
void multiplayer(char [][WIDTH], bool&, int&, bool, int&);
//Prototypes function to check for win state.
bool winX(char [][WIDTH], bool);
bool win0(char [][WIDTH], bool);
//Prototype functions for players to change the game board.
void playerX(char [][WIDTH], bool, bool&);
void player0(char [][WIDTH], bool, bool&);
//Prototypes function to for computer to change game board.
void computer(char [][WIDTH], bool);
//Prototypes function asking player to play again.
void repeatGame(int&, bool);
//Prototypes function to initialize game board array.
void resetGame(char [][WIDTH], bool, int);
//Defines main function.
int main(int argc, char *argv[])
{
    //Declares variables for debug mode.
    bool debug = false;
    char debugConfirm = 'p';
    //Checks for debug mode input error.
    bool debugError = false;
    //Displays top message.
    cout << "Hello and welcome. Before the game actually starts, please";
    cout << " decide whether you would like to launch the game in debug mode.";
    cout << endl;
    cout << "Debug mode displays background system activities in red text." << endl;
    //Prompts user for debug mode.
    do
    {
        cout << "Would you like to enable debug mode? (Y/N)" << endl;
        cin >> debugConfirm;
        if(debugConfirm == 'Y' || debugConfirm == 'y')
        {
            //Resets error state and sets appropriate variable.
            debugError = false;
            debug = true;
        }
        else if(debugConfirm == 'N' || debugConfirm == 'n')
        {
            //Reset error state and sets appropriate variable.
            debugError = false;
            debug = false;
        }
        else
        {
            //This clears failed input.
            cin.clear();
            //This ignores 1000 cin characters until an endline.
            cin.ignore(IGNORE, '\n');
            //This sets an error state.
            debugError = true;
            //Displays error message.
            cout << "Unexpected choice. Please try again." << endl;
        }
    }while(debugError);
    //Outputs information on debugging mode.
    if(debug)
    {
        cout << "\033[31mDebugging mode:" << endl;
        cout << "\033[30m";
    }
    //Declares gamemode variable.
    int modeChoice = 0;
    //Declares variable for exiting game.
    bool endGame = false;
    //Declares variable for playing again.
    int playAgain = 0;
    //Creates game board array.
    char gameBoard[HEIGHT][WIDTH];
    //Creates variable relevant to debug mode.
    int atLeastOnce = 0;
    //Outputs program title and border.
    cout << setw(BORDER) << setfill('#');
    cout << right << "#" << endl;
    cout << "#";
    cout << setw(TEXT) << setfill(' ');
    cout << "Welcome to TicTacToe Game!";
    cout << setw(FOUR) << "#" << endl;
    cout << setw(BORDER) << setfill('#');
    cout << right << "#" << endl << endl;
    //Loop to display main menu and call game functions.
    do
    {
        //Prompts user for choice of game mode.
        singleOrMulti(modeChoice, endGame, debug);
        //Ends game if necessary.
        if(endGame)
        {
            cout << "Thank you for playing" << endl;
            return 0;
        }
        //Calls function for appropriate game mode.
        if(modeChoice == 1)
        {
            //Runs game as single player.
            singlePlayer(gameBoard, endGame, playAgain, debug, atLeastOnce);
        }
        else if(modeChoice == 2)
        {
            //Runs game as single player.
            multiplayer(gameBoard, endGame, playAgain, debug, atLeastOnce);
        }
    }while(playAgain == 2);
    //Confirms end of program.
    return 0;
}
//Defines function to initialize array.
void resetGame(char gameBoard[][WIDTH], bool debug, int atLeastOnce)
{
    //Initialized game board array.
    gameBoard[0][0] = '1';
    gameBoard[0][1] = '2';
    gameBoard[0][2] = '3';
    gameBoard[1][0] = '4';
    gameBoard[1][1] = '5';
    gameBoard[1][2] = '6';
    gameBoard[2][0] = '7';
    gameBoard[2][1] = '8';
    gameBoard[2][2] = '9';
    //Prints debug mode information.
    if(debug && atLeastOnce == 0)
    {
        cout << "\033[31mGame board created" << endl;
        cout << "\033[30m";
    }
}
//Defines function to determine game mode.
void singleOrMulti(int& modeChoice, bool& endGame, bool debug)
{
    //Declares error variable.
    bool error = false;
    //Outputs prompt for user.
    do
    {
        //Displays menu.
        cout << "Main Menu:" << endl;
        cout << "1. Single Player." << endl;
        cout << "2. Multiplayer." << endl;
        cout << "3. Exit game." << endl;
        cin >> modeChoice;
        //Tests input for errors.
        if(cin.fail())
        {
            //This clears failed input.
            cin.clear();
            //This ignores 1000 cin characters until an endline.
            cin.ignore(IGNORE, '\n');
            //This outputs an error message.
            cout << "You can enter numbers only!" << endl;
            //Sets error to true.
            error = true;
        }
        //Checks input against possible inputs.
        else if(modeChoice < 1 || modeChoice > 3)
        {
            //This clears failed input.
            cin.clear();
            //This ignores 1000 cin characters until an endline.
            cin.ignore(IGNORE, '\n');
            //This outputs an error message.
            cout << "Selection must be between 1 and 3" << endl;
            //Sets error to true.
            error = true;
        }
        else
        {
            //Resets error variable.
            error = false;
        }
    }while(error);
    //Sets end game variable if necessary.
    if(modeChoice == 3)
    {
        endGame = true;
    }
    //Displays debug mode info.
    if(debug)
    {
        //Displays what gamemode was chosen.
        if(modeChoice == 1)
        {
            cout << "\033[31mEntering singleplayer mode:" << endl;
            cout << "\033[30m";
        }
        else if(modeChoice == 2)
        {
            cout << "\033[31mEntering multiplayer mode:" << endl;
            cout << "\033[30m";
        }
        else if(modeChoice == 3)
        {
            cout << "\033[31mExiting the game:" << endl;
            cout << "\033[30m";
        }
    }
}
//Defines game board function.
void printBoard(char gameBoard[][WIDTH])
{
    //Prints out game board.
    for(int i = 0; i < HEIGHT; i++)
    {
        //Displays row border.
        cout << setw(11) << setfill('-') << left;
        cout << " ";
        cout << setw(2) << setfill(' ');
        cout << "-" << endl;
        //Displays row.
        cout << "|";
        for(int j = 0; j < WIDTH; j++)
        {

            cout << setw(2) << right;
            cout << gameBoard[i][j];
            cout << setw(2) << "|";
        }
        //Displays end of row.
        cout << endl;
    }
    //Displays row bottom border.
    //Displays row border.
    cout << setw(11) << setfill('-') << left;
    cout << " ";
    cout << setw(2) << setfill(' ');
    cout << "-" << endl;
}
//Defines single player game function.
void singlePlayer(char gameBoard[][WIDTH], bool& endGame, 
                  int& playAgain, bool debug, int& atLeastOnce)
{
    //Declares variables for player scores.
    int player1Score = 0;
    int computerScore = 0;
    //Declares variable for victory states.
    bool victory = false;
    bool computerWon = false;
    bool tie = false;
    //Declares variable to indicate successful turn.
    bool changed = false;
    //Declares variable to count turn number.
    int turns = 0;
    //Loop to output game data.
    do
    {
        //Initializes game board.
        resetGame(gameBoard, debug, atLeastOnce);
        atLeastOnce ++;
        //Resets turn counter.
        turns = 0;
        //Resets win state.
        victory = false;
        //Resets changed variable.
        changed = false;
        //Outputs score data.
        cout << "Scoreboard:" << endl;
        cout << "X: " << player1Score << "\t";
        cout << "O: " << computerScore << endl;
        //Loop to output game board and player prompts.
        do
        {
            if(!computerWon && !tie)
            {
                //Loop to call for player turn.
                do
                {
                    //Calls player turn.
                    playerX(gameBoard, debug, changed);
                    //Checks for player victory.
                    if(winX(gameBoard, debug))
                    {
                        player1Score ++;
                        //Sets victory state.
                        victory = true;
                        tie = false;
                        computerWon = false;
                    }
                }while(!changed);
                //Adds turn number.
                turns ++;
                if(!victory && turns < 9)
                {
                    //Calls computer turn.
                    cout << "Computer's turn!" << endl;
                    computer(gameBoard, debug);
                    //Checks for computer victory.
                    if(win0(gameBoard, debug))
                    {
                        computerScore ++;
                        //Sets victory state.
                        victory = true;
                        tie = false;
                        computerWon = true;
                    }
                    turns ++;
                }
            }
            else
            {
                //Calls computer turn.
                cout << "Computer's turn!" << endl;
                computer(gameBoard, debug);
                //Checks for computer victory.
                if(win0(gameBoard, debug))
                {
                    computerScore ++;
                    //Sets victory state.
                    victory = true;
                    tie = false;
                    computerWon = true;
                }
                turns ++;
                //Calls player turn.
                if(!victory && turns < 9)
                {
                    //Loop to call for player turn.
                    do
                    {
                        //Calls player turn.
                        playerX(gameBoard, debug, changed);
                        //Checks for player victory.
                        if(winX(gameBoard, debug))
                        {
                            player1Score ++;
                            //Sets victory state.
                            victory = true;
                            tie = false;
                            computerWon = false;
                        }
                    }while(!changed);
                    //Adds turn number.
                    turns ++;
                }
            }
        }while(!victory && turns < 9);
        //Displays final board state.
        if(victory || turns == 9)
        {
            //Prints game board.
            printBoard(gameBoard);
            //Displays victory or tie message.
            if(turns == 9 && !victory)
            {
                //Displays tie message.
                cout << "It is a tie!!" << endl;
                //Sets tie.
                tie = true;
            }
            else if(!computerWon)
            {
                //Displays victory message.
                cout << "Player X Won!!" << endl;
            }
            else
            {
                //Displays victory message.
                cout << "Computer Won!!" << endl;
            }
        }
        //Asks player if they want to play again.
        repeatGame(playAgain, debug);
    }while(playAgain == 1);
}
//Defines function for computer player.
void computer(char gameBoard[][WIDTH], bool debug)
{
    //Generates seed for number randomizing process.
    srand(static_cast<unsigned>(time(0)));
    //Declares variables for random array coordinates.
    int y = rand() % HEIGHT;
    int x = rand() % WIDTH;
    //Displays debug mode information.
    if(debug)
    {
        cout << "\033[31mrow: " << y << " , ";
        cout << "col: " << x << "\033[30m" << endl;
    }
    //Changes selection if location was used.
    while(gameBoard[y][x] == 'O' || gameBoard[y][x] == 'X')
    {
        //Sets coordinates to different values.
        y = rand() % HEIGHT;
        x = rand() % WIDTH;
        //Displays debug mode information.
        if(debug)
        {
            cout << "\033[31mCell is already selected!" << endl;
            cout << "Changing selection." << endl;
            cout << "\033[30m" << endl;
        }
    }
    //Changes randomized location in game board.
    gameBoard[y][x] = 'O';
    //Displays debug mode data.
    if(debug)
    {
        cout << "\033[31mPlaying in row: " << y << ", ";
        cout << "col: " << x << "\033[30m" << endl;
    }
}
//Defines function for player X.
void playerX(char gameBoard[][WIDTH], bool debug, bool& changed)
{
    //Resets changed variable.
    changed = false;
    //Defines player input variable.
    int input = 0;
    //Defines error variable.
    bool error = false;
    do
    {
        //Calls print board function.
        printBoard(gameBoard);
        //Loop to prompt player for input.
        cout << "Player X, Make a selection:" << endl;
        do
        {
            cin >> input;
            //Checks input for error.
            if(cin.fail())
            {
                //This clears failed input.
                cin.clear();
                //This ignores 1000 cin characters until an endline.
                cin.ignore(IGNORE, '\n');
                //This outputs an error message.
                cout << "You can enter numbers only!" << endl;
                //Sets error to true.
                error = true;
            }
            //Checks input against possible inputs.
            else if(input < 1 || input > 9)
            {
                //This clears failed input.
                cin.clear();
                //This ignores 1000 cin characters until an endline.
                cin.ignore(IGNORE, '\n');
                //This outputs an error message.
                cout << "Your selection must be between 1 and 9" << endl;
                //Sets error to true.
                error = true;
            }
            else
            {
                //Resets error variable.
                error = false;
            }
        }while(error);
        //Changes game board values based on player input.
        switch(input)
        {
            case 1:
            if(gameBoard[0][0] != 'X' && gameBoard[0][0] != 'O')
            {
                gameBoard[0][0] = 'X';
                changed = true;
            }
            break;
            case 2:
            if(gameBoard[0][1] != 'X' && gameBoard[0][1] != 'O')
            {
                gameBoard[0][1] = 'X';
                changed = true;
            }
            break;
            case 3:
            if(gameBoard[0][2] != 'X' && gameBoard[0][2] != 'O')
            {
                gameBoard[0][2] = 'X';
                changed = true;
            }
            break;
            case 4:
            if(gameBoard[1][0] != 'X' && gameBoard[1][0] != 'O')
            {
                gameBoard[1][0] = 'X';
                changed = true;
            }
            break;
            case 5:
            if(gameBoard[1][1] != 'X' && gameBoard[1][1] != 'O')
            {
                gameBoard[1][1] = 'X';
                changed = true;
            }
            break;
            case 6:
            if(gameBoard[1][2] != 'X' && gameBoard[1][2] != 'O')
            {
                gameBoard[1][2] = 'X';
                changed = true;
            }
            break;
            case 7:
            if(gameBoard[2][0] != 'X' && gameBoard[2][0] != 'O')
            {
                gameBoard[2][0] = 'X';
                changed = true;
            }
            break;
            case 8:
            if(gameBoard[2][1] != 'X' && gameBoard[2][1] != 'O')
            {
                gameBoard[2][1] = 'X';
                changed = true;
            }
            break;
            case 9:
            if(gameBoard[2][2] != 'X' && gameBoard[2][2] != 'O')
            {
                gameBoard[2][2] = 'X';
                changed = true;
            }
            break;
        }
        //Outputs debug mode information.
        if(debug)
        {
            cout << "\033[31mPlay function called." << endl;
            cout << "\033[30m";
        }
        //Displays error if nothing changed.
        if(!changed)
        {
            //This clears failed input.
            cin.clear();
            //This ignores 1000 cin characters until an endline.
            cin.ignore(IGNORE, '\n');
            //This outputs an error message.
            cout << "This slot is already selected" << endl;
            //Outputs debug message.
            if(debug)
            {
                cout << "\033[31mChecking the board for a winning sequence" << endl;
                cout << "\033[30m";
            }
        }
        /*
        I know the win checking function isn't actually called here,
        but this is the most fitting location to output this information.
        */
    }while(!changed);
}
//Defines function to check player X victory.
bool winX(char gameBoard[][WIDTH], bool debug)
{
    //Defines return variabl.e
    bool win = false;
    //Outputs debug mode info
    if(debug)
    {
        cout << "\033[31mChecking the board for a winning sequence" << endl;
        cout << "\033[30m";
    }
    //Checks for vertical victories.
    for(int i = 0; i < WIDTH; i++)
    {
        if(gameBoard[0][i] == 'X' && 
           gameBoard[0][i] == gameBoard[1][i] &&
           gameBoard[1][i] == gameBoard[2][i])
        {
            win = true;
            //Outputs debug mode info.
            if(debug)
            {
                if(gameBoard[0][0] == gameBoard[1][0] &&
                   gameBoard[1][0] == gameBoard[2][0])
                {
                    cout << "\033[31mPlayer won in 1,4,7" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[0][1] == gameBoard[1][1] &&
                        gameBoard[1][1] == gameBoard[2][1])
                {
                    cout << "\033[31mPlayer won in 2,5,8" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[0][2] == gameBoard[1][2] &&
                        gameBoard[1][2] == gameBoard[2][2])
                {
                    cout << "\033[31mPlayer won in 3,6,9" << endl;
                    cout << "\033[30m";
                }
            }
        }
    }
    //Checks for horizontal victories.
    for(int i = 0; i < HEIGHT; i++)
    {
        if(gameBoard[i][0] == 'X' &&
           gameBoard[i][0] == gameBoard[i][1] &&
           gameBoard[i][1] == gameBoard[i][2])
        {
            win = true;
            //Outputs debug mode info.
            if(debug)
            {
                if(gameBoard[0][0] == gameBoard[0][1] &&
                   gameBoard[0][1] == gameBoard[0][2])
                {
                    cout << "\033[31mPlayer won in 1,2,3" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[1][0] == gameBoard[1][1] &&
                        gameBoard[1][1] == gameBoard[1][2])
                {
                    cout << "\033[31mPlayer won in 4,5,6" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[2][0] == gameBoard[2][1] &&
                        gameBoard[2][1] == gameBoard[2][2])
                {
                    cout << "\033[31mPlayer won in 7,8,9" << endl;
                    cout << "\033[30m";
                }
            }
        }
    }
    //Checks for diagonal victories.
    if(gameBoard[0][0] == 'X' &&
       gameBoard[0][0] == gameBoard[1][1] &&
       gameBoard[1][1] == gameBoard[2][2])
    {
        win = true;
        //Outputs debug mode info.
        if(debug)
        {
            cout << "\033[31mPlayer won in 1,5,9" << endl;
            cout << "\033[30m";
        }
    }
    else if(gameBoard[0][2] == 'X' &&
            gameBoard[0][2] == gameBoard[1][1] &&
            gameBoard[1][1] == gameBoard[2][0])
    {
        win = true;
        //Outputs debug mode info.
        if(debug)
        {
            cout << "\033[31mPlayer won in 3,5,7" << endl;
            cout << "\033[30m";
        }
    }
    //Returns variable.
    return win;
}
//Defines function for player 0/O.
void player0(char gameBoard[][WIDTH], bool debug, bool& changed)
{
    //Resets changed variable.
    changed = false;
    //Defines player input variable.
    int input = 0;
    //Defines error variable.
    bool error = false;
    do
    {
        //Calls print board function.
        printBoard(gameBoard);
        //Loop to prompt player for input.
        cout << "Player O, Make a selection:" << endl;
        do
        {
            cin >> input;
            //Checks input for error.
            if(cin.fail())
            {
                //This clears failed input.
                cin.clear();
                //This ignores 1000 cin characters until an endline.
                cin.ignore(IGNORE, '\n');
                //This outputs an error message.
                cout << "You can enter numbers only!" << endl;
                //Sets error to true.
                error = true;
            }
            //Checks input against possible inputs.
            else if(input < 1 || input > 9)
            {
                //This clears failed input.
                cin.clear();
                //This ignores 1000 cin characters until an endline.
                cin.ignore(IGNORE, '\n');
                //This outputs an error message.
                cout << "Your selection must be between 1 and 9" << endl;
                //Sets error to true.
                error = true;
            }
            else
            {
                //Resets error variable.
                error = false;
            }
        }while(error);
        //Changes game board values based on player input.
        switch(input)
        {
            case 1:
            if(gameBoard[0][0] != 'X' && gameBoard[0][0] != 'O')
            {
                gameBoard[0][0] = 'O';
                changed = true;
            }
            break;
            case 2:
            if(gameBoard[0][1] != 'X' && gameBoard[0][1] != 'O')
            {
                gameBoard[0][1] = 'O';
                changed = true;
            }
            break;
            case 3:
            if(gameBoard[0][2] != 'X' && gameBoard[0][2] != 'O')
            {
                gameBoard[0][2] = 'O';
                changed = true;
            }
            break;
            case 4:
            if(gameBoard[1][0] != 'X' && gameBoard[1][0] != 'O')
            {
                gameBoard[1][0] = 'O';
                changed = true;
            }
            break;
            case 5:
            if(gameBoard[1][1] != 'X' && gameBoard[1][1] != 'O')
            {
                gameBoard[1][1] = 'O';
                changed = true;
            }
            break;
            case 6:
            if(gameBoard[1][2] != 'X' && gameBoard[1][2] != 'O')
            {
                gameBoard[1][2] = 'O';
                changed = true;
            }
            break;
            case 7:
            if(gameBoard[2][0] != 'X' && gameBoard[2][0] != 'O')
            {
                gameBoard[2][0] = 'O';
                changed = true;
            }
            break;
            case 8:
            if(gameBoard[2][1] != 'X' && gameBoard[2][1] != 'O')
            {
                gameBoard[2][1] = 'O';
                changed = true;
            }
            break;
            case 9:
            if(gameBoard[2][2] != 'X' && gameBoard[2][2] != 'O')
            {
                gameBoard[2][2] = 'O';
                changed = true;
            }
            break;
        }
        //Outputs debug mode information.
        if(debug)
        {
            cout << "\033[31mPlay function called." << endl;
            cout << "\033[30m";
        }
        //Displays error if nothing changed.
        if(!changed)
        {
            cout << "This slot is already selected." << endl;
            //Outputs debug message.
            if(debug)
            {
                cout << "\033[31mChecking the board for a winning sequence" << endl;
                cout << "\033[30m";
            }
        }
    }while(!changed);
}
//Defines function to check player 0/O victory.
bool win0(char gameBoard[][WIDTH], bool debug)
{
    //Defines return variabl.e
    bool win = false;
    //Outputs debug mode info
    if(debug)
    {
        cout << "\033[31mChecking the board for a winning sequence" << endl;
        cout << "\033[30m";
    }
    //Checks for vertical victories.
    for(int i = 0; i < WIDTH; i++)
    {
        if(gameBoard[0][i] == 'O' && 
           gameBoard[0][i] == gameBoard[1][i] &&
           gameBoard[1][i] == gameBoard[2][i])
        {
            win = true;
            //Outputs debug mode info.
            if(debug)
            {
                if(gameBoard[0][0] == gameBoard[1][0] &&
                   gameBoard[1][0] == gameBoard[2][0])
                {
                    cout << "\033[31mPlayer won in 1,4,7" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[0][1] == gameBoard[1][1] &&
                        gameBoard[1][1] == gameBoard[2][1])
                {
                    cout << "\033[31mPlayer won in 2,5,8" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[0][2] == gameBoard[1][2] &&
                        gameBoard[1][2] == gameBoard[2][2])
                {
                    cout << "\033[31mPlayer won in 3,6,9" << endl;
                    cout << "\033[30m";
                }
            }
        }
    }
    //Checks for horizontal victories.
    for(int i = 0; i < HEIGHT; i++)
    {
        if(gameBoard[i][0] == 'O' &&
           gameBoard[i][0] == gameBoard[i][1] &&
           gameBoard[i][1] == gameBoard[i][2])
        {
            win = true;
            //Outputs debug mode info.
            if(debug)
            {
                if(gameBoard[0][0] == gameBoard[0][1] &&
                   gameBoard[0][1] == gameBoard[0][2])
                {
                    cout << "\033[31mPlayer won in 1,2,3" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[1][0] == gameBoard[1][1] &&
                        gameBoard[1][1] == gameBoard[1][2])
                {
                    cout << "\033[31mPlayer won in 4,5,6" << endl;
                    cout << "\033[30m";
                }
                else if(gameBoard[2][0] == gameBoard[2][1] &&
                        gameBoard[2][1] == gameBoard[2][2])
                {
                    cout << "\033[31mPlayer won in 7,8,9" << endl;
                    cout << "\033[30m";
                }
            }
        }
    }
    //Checks for diagonal victories.
    if(gameBoard[0][0] == 'O' &&
       gameBoard[0][0] == gameBoard[1][1] &&
       gameBoard[1][1] == gameBoard[2][2])
    {
        win = true;
        //Outputs debug mode info.
        if(debug)
        {
            cout << "\033[31mPlayer won in 1,5,9" << endl;
            cout << "\033[30m";
        }
    }
    else if(gameBoard[0][2] == 'O' &&
            gameBoard[0][2] == gameBoard[1][1] &&
            gameBoard[1][1] == gameBoard[2][0])
    {
        win = true;
        //Outputs debug mode info.
        if(debug)
        {
            cout << "\033[31mPlayer won in 3,5,7" << endl;
            cout << "\033[30m";
        }
    }
    //Returns variable.
    return win;
}
//Defines function for multiplayer game.
void multiplayer(char gameBoard[][WIDTH], bool& endGame, 
                  int& playAgain, bool debug, int& atLeastOnce)
{
    //Declares variables for player scores.
    int player1Score = 0;
    int player2Score = 0;
    //Declares variable for victory states.
    bool victory = false;
    bool player2Victory = false;
    bool tie = false;
    //Declares variable to indicate successful turn.
    bool changed = false;
    //Declares variable to count turns.
    int turns = 0;
    //Loop to output game data.
    do
    {
        //Initializes game board.
        resetGame(gameBoard, debug, atLeastOnce);
        atLeastOnce ++;
        //Resets turns.
        turns = 0;
        //Resets victory.
        victory = false;
        //Outputs score data.
        cout << "Scoreboard:" << endl;
        cout << "X: " << player1Score << "\t";
        cout << "O: " << player2Score << endl;
        //Loop to output game board and player prompts.
        do
        {
            if(!player2Victory && !tie)
            {
                //Prompts player X.
                do
                {
                    //Calls player turn.
                    playerX(gameBoard, debug, changed);
                    //Checks for player victory.
                    if(winX(gameBoard, debug))
                    {
                        player1Score ++;
                        //Sets victory state.
                        victory = true;
                        tie = false;
                        player2Victory = false;
                    }
                }while(!changed);
                //Adds a turn.
                turns ++;
                if(!victory && turns < 9)
                {
                    //Prompts player 0/O.
                    do
                    {
                        //Calls player turn.
                        player0(gameBoard, debug, changed);
                        //Checks for player victory.
                        if(win0(gameBoard, debug))
                        {
                            player2Score ++;
                            //Sets victory state.
                            victory = true;
                            tie = false;
                            player2Victory = true;
                        }
                    }while(!changed);
                    //Adds a turn.
                    turns ++;
                }
            }
            else
            {
                //Prompts player 0/O.
                do
                {
                    //Calls player turn.
                    player0(gameBoard, debug, changed);
                    //Checks for player victory.
                    if(win0(gameBoard, debug))
                    {
                        player2Score ++;
                        //Sets victory state.
                        victory = true;
                        tie = false;
                        player2Victory = true;
                    }
                }while(!changed);
                //Adds a turn.
                turns ++;
                if(!victory)
                {
                    //Prompts player X.
                    do
                    {
                        //Calls player turn.
                        playerX(gameBoard, debug, changed);
                        //Checks for player victory.
                        if(winX(gameBoard, debug))
                        {
                            player1Score ++;
                            //Sets victory state.
                            victory = true;
                            tie = false;
                            player2Victory = false;
                        }
                    }while(!changed);
                    //Adds a turn.
                    turns ++;
                }
            }
        }while(!victory && turns < 9);
        //Displays final board state.
        if(victory || turns == 9)
        {
            //Prints game board.
            printBoard(gameBoard);
            //Displays victory or tie message.
            if(turns == 9 && !victory)
            {
                //Displays tie message.
                cout << "It is a tie!!" << endl;
                //Sets tie.
                tie = true;
            }
            else if(!player2Victory)
            {
                //Displays victory message.
                cout << "Player X Won!!" << endl;
            }
            else
            {
                //Displays victory message.
                cout << "Player O Won!!" << endl;
            }
        }
        //Asks player if they want to play again.
        repeatGame(playAgain, debug);
    }while(playAgain == 1);
}
//Defines the function to repeat the game.
void repeatGame(int& playAgain, bool debug)
{
    //Sets error variable.
    bool error = false;
    //Loop to prompt player for input.
    do
    {
        cout << "GameOver" << endl;
        cout << "1. Play again." << endl;
        cout << "2. Back to main menu." << endl;
        cin >> playAgain;
        //Checks input for error.
        if(cin.fail())
        {
            //This clears failed input.
            cin.clear();
            //This ignores 1000 cin characters until an endline.
            cin.ignore(IGNORE, '\n');
            //This outputs an error message.
            cout << "You can enter numbers only!" << endl;
            //Sets error to true.
            error = true;
        }
        else if(playAgain < 1 || playAgain > 2)
        {
            //This clears failed input.
            cin.clear();
            //This ignores 1000 cin characters until an endline.
            cin.ignore(IGNORE, '\n');
            //This outputs an error message.
            cout << "Selection must be between 1 and 2" << endl;
            //Sets error to true.
            error = true;
        }
        else
        {
            error = false;
        }
    }while(error);
    //Outputs debug mode data.
    if(debug)
    {
        cout << "\033[31mCalling resetGame function" << endl;
        cout << "\033[30m";
    }
}