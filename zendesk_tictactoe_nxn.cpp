#include<iostream>
#include<string>

using namespace std;

class Game{
    public: 
        // Gets and stores player names from input.
        void EnterPlayerNames();
        
        // Gets BoardSize from user input.
        void EnterBoardSize();

        // Constructs the array for the Board State with size NxN, where N is the BoardSize.
        void MakeBoard();

        // Renders the Board state.
        void DisplayBoard();

        // Gets decision from user on the box where he wants to place his token.
        string GetDecision();

        // Check if decision is valid by checking if box has already been occupied with a mark.
        bool CheckDecisionFirst(string input);

        // Updates the Board state following user's decision which is a variable passed into it.
        void UpdateBoard(string input);

        // Checks if winning conditions had been fulfilled.
        int CheckForWin();

        // Swaps Turns for the players
        void SwapTurns();

        // Displays results of the game
        void DisplayResult();

        // Result == -1 : Nobody wins yet
        // Result == 0 : Player 1 wins
        // Result == 1 : Player 2 wins 
        // Result == 2 : Draw between Player 1 and 2
        int Result = -1;

        // Tracks the number of turns. 
        // If it is N^2, it means the Board is fully filled. A draw will be issued if nobody wins.
        int NumberOfTurns = 0;

        // Represents the Maximum Number of Moves that can be made which is equivalent to NxN.
        // If NumberOfTurns == MaxNumberOfTurns, it will imply that no more moves can be made. So check for draw.
        int MaxNumberOfTurns;

        // Represents if decision made by the user is valid (i.e can be applied to the board)
        // Conditions are stated in CheckDecisionFirst().
        bool Valid;

    private:
        // Array to represent board state of size N.
        // Upper limit of 101 set here to accomodate up to 10x10 matrix. Could possibly increase further.
        string Board[101];

        // Array to store the player names from EnterPlayerNames()
        string PlayerNames[2];

        // Array to store the marks of each player.
        string Marks[2] = {"X", "O"};

        // Turn == false : Player 1's Turn
        // Turn == true : Player 2's Turn.
        bool Turn = false; 

        // BoardSize is the length of the square matrix (provided by the user)
        int BoardSize;
};

void Game::EnterPlayerNames(){
    // Obtains Player Names from user input
    string s1, s2;
    cout << "Enter name for Player 1:\n";
    cin >> s1;
    cout << "Enter name for Player 2:\n";
    cin >> s2;

    // Ensures that Player 1 and Player 2 have unique names
    while (s2 == s1){
        cout << "Name is the same as Player 1\nPlease enter another name for Player 2: ";
        cin >> s2;
    }

    // Stores unique names of Player 1 and 2 into array
    PlayerNames[0] = s1;
    PlayerNames[1] = s2;
};

void Game::EnterBoardSize(){
    // Obtains desired Board Size from user input.
    int n;
    cout << "Enter Desired Board Size(must be 3 or more):\n";
    cin >> n;
    BoardSize = n;
    MaxNumberOfTurns = n*n;
};

void Game::MakeBoard(){
    // Constructs array to represent Board state.
    for (int i = 0; i < BoardSize*BoardSize; i++){
        string s = to_string(i+1);
        Board[i] = s;
    }
};

void Game::DisplayBoard(){
    // dashline was included to improve add horizontal borders to rendered Board.
    string dashline = string(BoardSize*(BoardSize), '-');
    cout << dashline << "\n";

    // Renders board state for each row 
    for (int row = 0; row < BoardSize*BoardSize; row+=BoardSize){
        cout << " | ";
        for (int col = 0; col < BoardSize; col++)
            cout <<  Board[row+col] << " | ";
        cout << "\n" << dashline << "\n";
        }
};

string Game::GetDecision(){
    // Gets Decision from Player input
    // Assumes player enters valid input
    string input;
    cout << PlayerNames[Turn] << ", ";
    cout << "choose a box to place an '" << Marks[Turn] <<"' into:\n";
    cin >> input;
    return input;
};

bool Game::CheckDecisionFirst(string input){
    // Check if decision can be applied to the board
    // Convert the string input to int to check
    int i = stoi(input);

    // Decision fails under 3 conditions 
    // 1. Position chosen had already been filled before and contains "X" or "O";
    // 2. Position chosen is 0 or negative.
    // 3. Position chosen exceeds NxN.
    if (Board[i-1] == Marks[0] || Board[i-1] == Marks[1] || i < 1 || i > BoardSize*BoardSize)
        return false;
    return true;
};

void Game::UpdateBoard(string input){
    // Updates the Board following user input
    for (int i = 0; i < BoardSize*BoardSize; i++){
        if (Board[i] == input){
            Board[i] = Marks[Turn];
            break;
        }
    }
}

int Game::CheckForWin(){
    //If winning condition is met, the current Turn (0 or 1) will indicate the corresponding
    //winner, thus "return Turn" was added to update Result variable accordingly.

    int n = BoardSize;
    //Check for Horizontal Match
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - 3 + 1; j++){
            if (Board[n*i+j] == Board[n*i+j+1] && Board[n*i+j] == Board[n*i+j+2])
                return Turn;
        }
    }
    // Check for Vertical Match 
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n - 3 + 1; j++){
            if (Board[i+n*j] == Board[i+n*(j+1)] && Board[i+n*j] == Board[i+n*(j+2)])
                return Turn;
        }
    }
    // Check for \ Diagonal Match 
    for (int i = 0; i < n - 3 + 1; i++){
        for (int j = 0; j < n - 3 + 1; j++){
            if (Board[i+n*j] == Board[i+n*j+n+1] && Board[i+n*j] == Board[i+n*j+2*n+2])
                return Turn;
        }
    }
    // Check for / Diagonal Match 
    for (int i = 2; i < n; i++){
        for (int j = 0; j < n - 3 + 1; j++){
            if (Board[i+n*j] == Board[i+n*j+n-1] && Board[i+n*j] == Board[i+n*j+2*n-2])
                return Turn;
        }
    }
    return Result;
};

void Game::SwapTurns(){
    // Alternates the turn to place marks on board.
    if (Turn)
        Turn = 0;
    else
        Turn = 1;
};

void Game::DisplayResult(){
    // Display message to conclude the result of the game.
    if (Result == 2)
        cout << "It's a Draw!\n";
    else 
        cout << "Congratulations " << PlayerNames[Result] << " ! You have won.\n";
    cout << "Thank you for playing!\n";
};

int main(){
    // Initialize class to g
    Game g;
    g.EnterPlayerNames();
    g.EnterBoardSize();
    g.MakeBoard();
    g.DisplayBoard();
    
    while (g.Result == -1){
        string in = g.GetDecision();
        g.Valid = g.CheckDecisionFirst(in);
        if (g.Valid){
            g.UpdateBoard(in);
            g.DisplayBoard();
            g.Result = g.CheckForWin();
            g.SwapTurns();
            g.NumberOfTurns++;
        }
        else
            cout << "Position had been filled or Input is out of range!\nPlease try again.\n";

        // Final check when all moves had been played
        // Issue draw if no winner
        if (g.NumberOfTurns == g.MaxNumberOfTurns & g.Result == -1)
            g.Result = 2;
    }
    g.DisplayResult();

    return 0;
}


