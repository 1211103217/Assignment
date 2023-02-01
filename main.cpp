// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT9L 
// Names: ALIF DURRANI BIN ZAHARI | MUHAMMAD ANIQ FAHMI BIN AZHAR | MUHAMMAD ZAQUAN BIN ZAFRI
// IDs: 1211103217 | 1211101533 | 1211102759
// Emails:  1211103217@STUDENT.MMU.EDU.MY | 1211101533@STUDENT.MMU.EDU.MY | 1211102759@STUDENT.MMU.EDU.MY
// Phones: 01137835336 | 0173894013| 0134056143
// ********************************************************* 

#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    int rows = 5, columns = 3, num_zombies = 2, num_rocks, num_health, num_pods, max_rocks = 9, max_health = 9, max_pods = 9;

    cout << "The default number of rows is 5" << endl;
    cout << "The default number of columns is 3" << endl;
    cout << "The default number of zombies is 2" << endl;
    cout << endl;
    cout << "Do you want to change the default settings (y/n)? ";
    char answer;
    cin >> answer;
    cout << endl;

    if (answer == 'y' || answer == 'Y')
    {
        cout << "Enter the number of rows: ";
        cin >> rows;

        cout << "Enter the number of columns: ";
        cin >> columns;

        cout << "Enter the number of zombies: ";
        cin >> num_zombies;
        cout << endl;
    }

    vector<vector<char>> board(rows, vector<char>(columns, ' '));

    cout << " ***********************************" << endl;
    cout << " *                                 *" << endl;
    cout << " *         Aliens Vs Zombies       *" << endl;
    cout << " *                                 *" << endl;
    cout << " ***********************************" << endl;
    cout << endl;

    // Add aliens to the center of the board
    board[rows / 2][columns / 2] = 'A';

    // Add zombies randomly to the board
    srand(time(NULL));
    int z_count = 1;
    while (z_count <= num_zombies)
    {
        int i = rand() % rows;
        int j = rand() % columns;
        if (board[i][j] == ' ')
        {
            board[i][j] = z_count + '0';
            z_count++;
        }
    }

    srand(time(NULL));

    // Generate random number of health
    num_health = rand() % max_health + 1;

    // Add health to the board randomly
    int h = 0;
    while (h < num_health)
    {
        int i = rand() % rows;
        int j = rand() % columns;
        if (board[i][j] == ' ')
        {
            board[i][j] = 'H';
            h++;
        }
    }

    // Generate random number of rocks
    num_rocks = rand() % max_rocks + 1;

    // Add rocks to the board randomly
    int r = 0;
    while (r < num_rocks)
    {
        int i = rand() % rows;
        int j = rand() % columns;
        if (board[i][j] == ' ')
        {
            board[i][j] = 'R';
            r++;
        }
    }

    // Generate random number of pods

    num_pods = rand() % max_pods + 1;

    // Add pods to the board randomly
    int p = 0; 
    while (p < num_pods)
    {
        int i = rand() % rows;
        int j = rand() % columns;
        if (board[i][j] == ' ')
        {
            board[i][j] = 'P';
            p++;
        }
    }

    cout << setw(1) << " ";
    for (int i = 1; i <= columns; i++)
    {
        cout << setw(5) << i;
    }
    cout << endl;
    for (int i = 0; i < rows; i++)
    {
        cout << "   +";
        for (int j = 0; j < columns; j++)
        {
            cout << "----+";
        }
        cout << endl;
        cout << setw(2) << i + 1 << " |";
        for (int j = 0; j < columns; j++)
        {
            cout << setw(2) << " " << board[i][j] << setw(2) << " |";
        }
        cout << endl;
    }
    cout << "   +";
    for (int j = 0; j < columns; j++)
    {
        cout << "----+";
    }
    cout << endl;
    return 0;
}