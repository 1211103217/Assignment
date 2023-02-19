#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <iomanip>
#include <set>
using namespace std;

void pause()
{
    system("pause");
}

void clear()
{
    system("cls");
}

void mainMenu();

class Boards
{
private:
    vector<vector<char>> map_;
    vector<vector<int>> zombie_List;
    set<pair<int, int>> map_occupied;
    vector<int> zombieX_, zombie_y;
    int boardX_, boardY_;
    int alien_X, alien_Y, alienHealth, alienMaxHealth, alienAttack;
    int zombieCount_, zombieNo, zombieHealth, zombieAttack;

    char alienCh_ = 'A';

public:
    // board
    Boards(int boardX = 7, int boardY = 5, int zombieCount = 3);
    void init(int boardX, int boardY, int zombieCount);
    void displayMap() const;
    void displayAttributeAlien();
    void displayDefaultSetting(int boardX, int boardY, int zombieCount);
    void displayCurrentSetting(int boardX, int boardY, int zombieCount);
    void changeSetting(int boardX, int boardY, int zombCount);

    // menu
    void commandMenu();
    void restoreMap();
    void helpMenu();
    void gameOver();

    // get variable
    int getDim_X(), getDim_Y(), getZombieCount();
    void setObject(int x, int y, char ch);

    // item
    void healthItem(), pod(int podX, int podY), rock();
    void arrowUp(), arrowDown(), arrowLeft(), arrowRight();

    // alien
    void alienLand();
    void alienMoveUp(), alienMoveDown(), alienMoveRight(), alienMoveLeft();

    // zombie
    void zombieSpawn(int zombieCount);
    void zombieMove();
};

Boards::Boards(int boardX, int boardY, int zombieCount)
{
    init(boardX, boardY, zombieCount);
}

// initiating board
void Boards::init(int boardX, int boardY, int zombieCount)
{
    srand(time(NULL));

    boardX_ = boardX;
    boardY_ = boardY;
    zombieCount_ = zombieCount;

    char objects[] = {' ', ' ', 'h', 'r', '^', 'v', '<', '>', 'p', ' '};
    int noOfObjects = 10; // number of objects in the objects array

    map_.resize(boardY_);
    for (int i = 0; i < boardY_; i++)
    {
        map_[i].resize(boardX_);
    }

    for (int i = 0; i < boardY_; i++)
    {
        for (int j = 0; j < boardX_; j++)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }

    map_occupied.clear();
    alienLand();
    zombieSpawn(zombieCount_);

    for (int i = 0; i < zombieCount_; i++)
    {
        int zombCoorX = zombie_List[i][1] - 1;
        int zombCoorY = zombie_List[i][2] - 1;
        // char zombChar = zombieList_[i][0];
        char zombChar = to_string(i + 1)[0];

        map_occupied.insert({zombCoorX, zombCoorY}); // mark occupied zombie coordinate
        map_[zombCoorY][zombCoorX] = zombChar;
    }
}

int Boards::getDim_X()
{
    return boardX_;
}

int Boards::getDim_Y()
{
    return boardY_;
}

void Boards::setObject(int x, int y, char ch)
{
    map_[y - 1][x - 1] = ch;
}

// map display
void Boards::displayMap() const
{
    clear();
    // upper line title
    cout << "   ";
    for (int j = 0; j < boardX_; j++)
    {
        cout << "****";
    }
    cout << "*" << endl;

    // middle title
    // cout << "   ";
    for (int j = 0; j < (((boardX_ * 4 - 34) / 2) / 2); j++)
    {
        cout << "-*";
    }

    cout << "           ALIEN VS ZOMBIES          ";

    for (int j = 0; j < (((boardX_ * 4 - 34) / 2) / 2); j++)
    {
        cout << "*-";
    }
    cout << endl;

    // bottom line title
    cout << "   ";
    for (int j = 0; j < boardX_; j++)
    {
        cout << "****";
    }
    cout << "*" << endl
         << endl;

    // for each row
    for (int i = 0; i < boardY_; i++)
    {
        // display upper border
        cout << "   ";
        for (int j = 0; j < boardX_; j++)
        {
            cout << "+---";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << "   | ";

        // display cell content n border each column
        for (int j = 0; j < boardX_; j++)
        {
            cout << map_[i][j] << " | ";
        }
        cout << endl;
    }

    // display lower border last row
    cout << "   ";
    for (int j = 0; j < boardX_; j++)
    {
        cout << "+---";
    }
    cout << "+" << endl;
}

void Boards::displayAttributeAlien()
{
    cout << "-> Alien    : Life " << setw(3) << alienHealth << ", Attack " << setw(3) << alienAttack << endl;
    for (int i = 0; i < zombieCount_; i++)
    {
        cout << "   Zombie " << zombie_List[i][0] << " : Life " << setw(3) << zombie_List[i][3] << ", Attack " << setw(3) << zombie_List[i][4] << endl;
    }
}

// restore map after alienMove
void Boards::restoreMap()
{

    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int noOfObjects = 10;

    for (int i = 0; i < boardY_; i++)
    {
        for (int j = 0; j < boardX_; j++)
        {
            if (map_[i][j] == '.')
            {
                int objNo = rand() % noOfObjects;
                map_[i][j] = objects[objNo];
            }
        }
    }
}

// customize board size
void Boards::displayDefaultSetting(int boardX, int boardY, int zombieCount)
{
    clear();
    cout << " ******************************* " << endl;
    cout << " *                             * " << endl;
    cout << " *   DEFAULT  GAME  SETTINGS   * " << endl;
    cout << " *                             * " << endl;
    cout << " ******************************* " << endl;

    cout << " number of Columns => " << boardX << endl;
    cout << " number of Rows    => " << boardY << endl;
    cout << " number of Zombies => " << zombieCount << endl

         << endl;

    string confirmSettings;

    cout << " Do you want to change the defualt game settings (y/N) ? ";
    cin >> confirmSettings;

    if (confirmSettings == "y" || confirmSettings == "Y")
    {
        changeSetting(boardX, boardY, zombieCount);
    }
    else if (confirmSettings == "n" || confirmSettings == "N")
    {
        init(boardX, boardY, zombieCount);
    }
    else
    {
        cout << "\n You enter the wrong input \n try again...\n ";
        pause();
        displayDefaultSetting(boardX, boardY, zombieCount);
    }
}

void Boards::displayCurrentSetting(int boardX, int boardY, int zombieCount)
{
    clear();
    cout << " ***************************" << endl;
    cout << "  CURRENT   GAME   SETTINGS " << endl;
    cout << " ***************************" << endl;

    cout << " number of Columns : " << boardX << endl;
    cout << " number of Rows    : " << boardY << endl;
    cout << " number of Zombies : " << zombieCount << endl

         << endl;

    string confirmSetting2;

    cout << " Do you want to change the game settings (y/N) ? ";
    cin >> confirmSetting2;

    if (confirmSetting2 == "n" || confirmSetting2 == "N")
    {
        init(boardX, boardY, zombieCount);
    }
    else if (confirmSetting2 == "y" || confirmSetting2 == "Y")
    {
        changeSetting(boardX, boardY, zombieCount);
    }
    else
    {
        cout << "\n You enter the wrong input \n Please try again...\n ";
        pause();
        displayCurrentSetting(boardX, boardY, zombieCount);
    }
}

void Boards::changeSetting(int boardX, int boardY, int zombieCount)
{
    clear();
    cout << " *****************" << endl;
    cout << "  BOARD  SETTINGS " << endl;
    cout << " *****************" << endl
         << endl;

    do
    {
        cout << " Enter Columns  > ";
        cin >> boardX;

        if (boardX % 2 == 0)
        {
            cout << " enter an Odd number only\n";
        }
    } while (boardX % 2 == 0);

    cout << endl;
    do
    {
        cout << " Enter Rows  > ";
        cin >> boardY;
        ;

        if (boardY % 2 == 0)
        {
            cout << "\n Please enter an Odd number only\n";
        }
    } while (boardY % 2 == 0);

    cout << " ******************" << endl;
    cout << "  ZOMBIE  SETTINGS " << endl;
    cout << " ******************" << endl
         << endl;

    cout << " Total zombies > ";
    cin >> zombieCount;
    cout << endl;
    cout << " returning to settings...\n ";
    pause();
    clear();
    displayCurrentSetting(boardX, boardY, zombieCount);
}

// item; arrow, health, rock, pod
void Boards::healthItem()
{
    displayMap();
    displayAttributeAlien();
    cout << "\n  The Alien found a health pack\n\n ";
    pause();

    int healthItem = 10;
    if (alienHealth + healthItem >= alienMaxHealth)
    {
        alienHealth = alienMaxHealth;
        cout << "\n Alien's life has reached its maximum"
             << "\n\n ";
    }
    else
    {
        alienHealth = alienHealth + healthItem;
    }

    displayMap();
    displayAttributeAlien();
    cout << "\n  Alien's life is increased by " << healthItem << "\n\n ";
    pause();
}

void Boards::arrowUp()
{
    displayMap();
    displayAttributeAlien();
    alienAttack = alienAttack + 10;

    cout << "\n  Alien's attack is increased by 10 \n";
    cout << "\n  Alien moves up\n\n ";

    alienMoveUp();
}

void Boards::arrowDown()
{
    displayMap();
    displayAttributeAlien();
    alienAttack = alienAttack + 10;

    cout << "\n  Alien's attack is increased by 10 \n";
    cout << "\n  Alien moves down\n\n ";

    alienMoveDown();
}

void Boards::arrowLeft()
{
    displayMap();
    displayAttributeAlien();
    alienAttack = alienAttack + 10;

    cout << "\n  Alien's attack is increased by 10 \n";
    cout << "\n  Alien moves left\n\n ";

    alienMoveLeft();
}

void Boards::arrowRight()
{
    displayMap();
    displayAttributeAlien();
    alienAttack = alienAttack + 10;

    cout << "\n  Alien's attack is increased by 10 \n";
    cout << "\n  Alien moves right\n\n ";

    alienMoveRight();
}

void Boards::rock()
{
    char objects[] = {' ', ' ', 'h', '^', 'v', '<', '>', 'p', ' '};
    int noOfObjects = 9;

    int objNo = rand() % noOfObjects;
    map_[alien_Y - 1][alien_X - 1] = objects[objNo];

    displayMap();
    displayAttributeAlien();

    cout << "\n  The Alien hit a rock and found \"" << map_[alien_Y - 1][alien_X - 1] << "\"\n ";
    pause();
}

// alien
void Boards::alienLand()
{
    alien_X = getDim_X() / 2 + 1;
    alien_Y = getDim_Y() / 2 + 1;

    alienHealth = 150 + 50 * (rand() % 4);
    alienMaxHealth = alienHealth;
    alienAttack = 10;

    setObject(alien_X, alien_Y, alienCh_);
    map_occupied.insert({alien_X - 1, alien_Y - 1});
}

void Boards::alienMoveUp()
{
    bool keepLooping = true;

    if (alien_Y > 1)
    {
        do
        {
            cout << "\n\n ";
            pause();
            alien_Y--;

            if (map_occupied.find({alien_X - 1, alien_Y - 1}) != map_occupied.end())
            {
                for (int i = 0; i < zombieCount_; i++)
                {
                    // if (zombieList_[i][3] > 0) // if zombie is still alive
                    // {
                    if (alien_X == zombie_List[i][1] && alien_Y == zombie_List[i][2])
                    {

                        zombie_List[i][3] = zombie_List[i][3] - alienAttack;
                        int zombX = zombie_List[i][1], zombY = zombie_List[i][2];

                        displayMap();
                        displayAttributeAlien();
                        cout << "\n  The Alien hit zombie " << zombie_List[i][0] << ", deal " << alienAttack << " damage\n\n ";

                        if (zombie_List[i][3] <= 0)
                        {
                            zombie_List[i][3] = 0;
                            map_[alien_Y - 1][alien_X - 1] = alienCh_;
                            map_[alien_Y][alien_X - 1] = '.';

                            map_occupied.insert({alien_X - 1, alien_Y - 1});
                            map_occupied.erase({alien_X - 1, alien_Y});
                        }
                        else
                        {
                            alien_Y++;
                            keepLooping = false;
                        }
                    }
                    //}
                }

                pause();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'h') // if there is h
            {
                healthItem(); // alien will get healed

                map_[alien_Y - 1][alien_X - 1] = alienCh_; // alien will move to the spot
                map_[alien_Y][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y});

                displayMap();
                displayAttributeAlien();
                cout << "\n  Alien's life is increased by 10 \n\n ";
                pause();
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'p')
            {
                // continue;
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y});
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '^')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y});
                arrowUp();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '>')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y});
                arrowRight();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'v')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y});
                arrowDown();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '<')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y});
                arrowLeft();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'r')
            {
                rock();

                alien_Y++;
                keepLooping = false;
                break;
            }
            else
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y});
            }

            displayMap();
            displayAttributeAlien();
            cout << "\n ";

        } while (alien_Y > 1 && keepLooping);

        if (keepLooping) // breaks the loop because alien has reached the border
        {
            cout << " Alien has reach the border\n\n ";
            pause();
        }
    }
    else
    {
        displayMap();
        displayAttributeAlien();
        cout << "\n Alien has reach the border\n\n ";
        pause();
    }
    restoreMap();
    zombieMove();
    commandMenu();
}

void Boards::alienMoveDown()
{
    bool keepLooping = true;

    if (alien_Y < boardY_)
    {
        do
        {
            cout << "\n\n ";
            pause();
            alien_Y++;

            if (map_occupied.find({alien_X - 1, alien_Y - 1}) != map_occupied.end())
            {
                for (int i = 0; i < zombieCount_; i++)
                {
                    if (alien_X == zombie_List[i][1] && alien_Y == zombie_List[i][2])
                    {

                        zombie_List[i][3] = zombie_List[i][3] - alienAttack;
                        int zombX = zombie_List[i][1], zombY = zombie_List[i][2];

                        displayMap();
                        displayAttributeAlien();
                        cout << "\n  The Alien attacked the zombie " << zombie_List[i][0] << ", deals " << alienAttack << " damage\n\n ";

                        if (zombie_List[i][3] <= 0)
                        {
                            zombie_List[i][3] = 0;
                            map_[alien_Y - 1][alien_X - 1] = alienCh_;
                            map_[alien_Y - 2][alien_X - 1] = '.';

                            map_occupied.insert({alien_X - 1, alien_Y - 1});
                            map_occupied.erase({alien_X - 1, alien_Y - 2});
                        }
                        else
                        {
                            alien_Y--;
                            keepLooping = false;
                        }
                    }
                }

                pause();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'h')
            {
                healthItem();

                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 2][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y - 2});

                displayMap();
                displayAttributeAlien();
                cout << "\n  Alien's life is increased by 10 \n\n ";
                pause();
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'p')
            {
                // continue;
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 2][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y - 2});
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '^')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 2][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y - 2});
                arrowUp();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '>')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 2][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y - 2});
                arrowRight();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'v')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 2][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y - 2});
                arrowDown();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '<')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 2][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y - 2});
                arrowLeft();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'r')
            {
                rock();

                alien_Y--;
                keepLooping = false;
                break;
            }
            else
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 2][alien_X - 1] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 1, alien_Y - 2});
            }

            // setObject(alienX_, alienY_, alienCh_);
            // setObject(alienX_, alienY_-1, '.');
            displayMap();
            displayAttributeAlien();
            cout << "\n ";

        } while (alien_Y < boardY_ && keepLooping);

        if (keepLooping)
        {
            cout << " Alien has reach the border\n\n ";
            pause();
        }
    }
    else
    {
        displayMap();
        displayAttributeAlien();
        cout << "\n Alien has reach the border\n\n ";
        pause();
    }
    restoreMap();
    zombieMove();
    commandMenu();
}

void Boards::alienMoveRight()
{
    bool keepLooping = true;

    if (alien_X < boardX_)
    {
        do
        {
            cout << "\n\n ";
            pause();
            alien_X++;

            if (map_occupied.find({alien_X - 1, alien_Y - 1}) != map_occupied.end())
            {
                for (int i = 0; i < zombieCount_; i++)
                {
                    if (alien_X == zombie_List[i][1] && alien_Y == zombie_List[i][2])
                    {

                        zombie_List[i][3] = zombie_List[i][3] - alienAttack;
                        int zombX = zombie_List[i][1], zombY = zombie_List[i][2];

                        displayMap();
                        displayAttributeAlien();
                        cout << "\n  The Alien hit zombie " << zombie_List[i][0] << ", deal " << alienAttack << " damage\n\n ";

                        if (zombie_List[i][3] <= 0)
                        {
                            zombie_List[i][3] = 0;
                            map_[alien_Y - 1][alien_X - 1] = alienCh_;
                            map_[alien_Y - 1][alien_X - 2] = '.';

                            map_occupied.insert({alien_X - 1, alien_Y - 1});
                            map_occupied.erase({alien_X - 2, alien_Y - 1});
                        }
                        else
                        {
                            alien_X--;
                            keepLooping = false;
                        }
                    }
                }

                pause();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'h')
            {
                healthItem();

                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X - 2] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 2, alien_Y - 1});

                displayMap();
                displayAttributeAlien();
                cout << "\n  Alien's life is increased by 10 \n\n ";
                pause();
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'p')
            {
                // continue;
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X - 2] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 2, alien_Y - 1});
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '^')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X - 2] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 2, alien_Y - 1});
                arrowUp();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '>')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X - 2] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 2, alien_Y - 1});
                arrowRight();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'v')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X - 2] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 2, alien_Y - 1});
                arrowDown();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '<')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X - 2] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 2, alien_Y - 1});
                arrowLeft();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'r')
            {
                rock();

                alien_X--;
                keepLooping = false;
                break;
            }
            else
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X - 2] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X - 2, alien_Y - 1});
            }

            // setObject(alienX_, alienY_, alienCh_);
            // setObject(alienX_-1, alienY_, '.');
            displayMap();
            displayAttributeAlien();
            cout << "\n ";

        } while (alien_X < boardX_ && keepLooping);

        if (keepLooping)
        {
            cout << " Alien has reach the border\n\n ";
            pause();
        }
    }
    else
    {
        displayMap();
        displayAttributeAlien();
        cout << "\n Alien has reach the border\n\n ";
        pause();
    }
    restoreMap();
    zombieMove();
    commandMenu();
}

void Boards::alienMoveLeft()
{
    bool keepLooping = true;

    if (alien_X > 1)
    {
        do
        {
            cout << "\n\n ";
            pause();
            alien_X--;

            if (map_occupied.find({alien_X - 1, alien_Y - 1}) != map_occupied.end())
            {
                for (int i = 0; i < zombieCount_; i++)
                {
                    if (alien_X == zombie_List[i][1] && alien_Y == zombie_List[i][2])
                    {

                        zombie_List[i][3] = zombie_List[i][3] - alienAttack;
                        int zombX = zombie_List[i][1], zombY = zombie_List[i][2];

                        displayMap();
                        displayAttributeAlien();
                        cout << "\n  The Alien hit zombie " << zombie_List[i][0] << ", deal " << alienAttack << " damage\n\n ";

                        if (zombie_List[i][3] <= 0)
                        {
                            zombie_List[i][3] = 0;
                            map_[alien_Y - 1][alien_X - 1] = alienCh_;
                            map_[alien_Y - 1][alien_X] = '.';

                            map_occupied.insert({alien_X - 1, alien_Y - 1});
                            map_occupied.erase({alien_X, alien_Y - 1});
                        }
                        else
                        {
                            alien_X++;
                            keepLooping = false;
                        }
                    }
                }

                pause();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'h')
            {
                healthItem();

                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X, alien_Y - 1});

                displayMap();
                displayAttributeAlien();
                cout << "\n  Alien's life is increased by 10 \n\n ";
                pause();
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'p')
            {
                // continue;
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X, alien_Y - 1});
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '^')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X, alien_Y - 1});
                arrowUp();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '>')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X, alien_Y - 1});
                arrowRight();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'v')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X, alien_Y - 1});
                arrowDown();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == '<')
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X, alien_Y - 1});
                arrowLeft();
                break;
            }
            else if (map_[alien_Y - 1][alien_X - 1] == 'r')
            {
                rock();

                alien_X++;
                keepLooping = false;
                break;
            }
            else
            {
                map_[alien_Y - 1][alien_X - 1] = alienCh_;
                map_[alien_Y - 1][alien_X] = '.';

                map_occupied.insert({alien_X - 1, alien_Y - 1});
                map_occupied.erase({alien_X, alien_Y - 1});
            }

            // setObject(alienX_, alienY_, alienCh_);
            // setObject(alienX_+1, alienY_, '.');
            displayMap();
            displayAttributeAlien();
            cout << "\n ";

        } while (alien_X > 1 && keepLooping);

        if (keepLooping)
        {
            cout << " Alien has reach the border\n\n ";
            pause();
        }
    }
    else
    {
        displayMap();
        displayAttributeAlien();
        cout << "\n Alien has reach the border\n\n ";
        pause();
    }
    restoreMap();
    zombieMove();
    commandMenu();
}

// zombie
int Boards::getZombieCount()
{
    return zombieCount_;
}

void Boards::zombieSpawn(int zombieCount)
{
    // zombieList[] = {zombieNo, zombieX_, zombieY_, zombieHealth, zombieAttack, zombieRange, zombieMoveTurn};
    int zombieListSize_ = 7;
    zombieCount_ = zombieCount;

    zombie_List.resize(zombieCount_);
    for (int i = 0; i < zombieCount_; i++)
    {
        zombie_List[i].resize(zombieListSize_);
    }

    // list of coordinate X
    zombieX_.resize(boardX_);
    for (int j = 0; j < boardX_; j++)
    {
        zombieX_[j] = j + 1;
    }
    int zombieXSize = zombieX_.size();

    // list of coordinate Y
    zombie_y.resize(boardY_);
    for (int i = 0; i < boardY_; i++)
    {
        zombie_y[i] = i + 1;
    }
    int zombie_y_size = zombie_y.size();

    // respective list
    int zombieHealth[] = {50, 75, 100, 125, 150, 175};
    int zombieHealthSize = 6;

    int zombieAttack[] = {10, 15, 20};
    int zombieAttackSize = 3;
    // column resize based on zombieCOunt_
    zombie_List.resize(zombieCount_);
    for (int i = 0; i < zombieCount_; i++)
    {
        // rows resize based on ZombieListSize_
        zombie_List[i].resize(zombieListSize_);
    }

    for (int i = 0; i < zombieCount_; i++)
    {
        for (int j = 0; j < zombieListSize_; j++)
        {
            if (j == 0)
            {
                // zombNo
                zombie_List[i][j] = i + 1;
            }
            else if (j == 3)
            {
                // random health
                int zomRanHealth = rand() % zombieHealthSize;
                zombie_List[i][j] = zombieHealth[zomRanHealth];
            }
            else if (j == 4)
            {
                // random attack
                int zomRanAtt = rand() % zombieAttackSize;
                zombie_List[i][j] = zombieAttack[zomRanAtt];
            }
        }
    }

    // empty zombieMap to check if occupied
    vector<vector<char>> zombieMap;
    set<pair<int, int>> occupiedCoor;

    char objects[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '-'};
    int noOfObjects = 10; // number of objects in the objects array

    zombieMap.resize(boardY_);
    for (int i = 0; i < boardY_; i++)
    {
        zombieMap[i].resize(boardX_);
    }

    for (int i = 0; i < boardY_; i++)
    {
        for (int j = 0; j < boardX_; j++)
        {
            int objNo = rand() % noOfObjects;
            zombieMap[i][j] = objects[objNo];
        }
    }

    occupiedCoor.insert({alien_X, alien_Y});
    // check for column 1 and 2 for zombieX and zombieY
    for (int i = 0; i < zombieCount_; i++)
    {
        int x;
        int y;

        do
        {
            // random zomX
            int zXNo = rand() % zombieXSize;

            // random zomY
            int zYNo = rand() % zombie_y_size;

            x = zombieX_[zXNo];

            y = zombie_y[zYNo];

        } while (occupiedCoor.find({x, y}) != occupiedCoor.end()); // check if the zombie occupied already

        occupiedCoor.insert({x, y});

        zombieMap[y - 1][x - 1] = 'z';

        zombie_List[i][1] = x;
        zombie_List[i][2] = y;
    }
}

void Boards::zombieMove()
{

    alienAttack = 0;
    for (int i = 0; i < zombieCount_; i++) // loop each zombie
    {
        int x, y, zombie_move;
        string move;
        int pre_X = zombie_List[i][1];
        int pre_y = zombie_List[i][2];
        int zombieTurn = 1;

        if (zombie_List[i][3] == 0)
        {
            continue;
        }

        bool is_blocked = false;
        bool up_blocked = false, down_blocked = false, left_locked = false, right_blocked = false;

        if (map_occupied.find({pre_X - 2, pre_y - 1}) != map_occupied.end()) // Check cell to the left
        {
            left_locked = true;
        }
        if (map_occupied.find({pre_X, pre_y - 1}) != map_occupied.end()) // Check cell to the right
        {
            right_blocked = true;
        }
        if (map_occupied.find({pre_X - 1, pre_y - 2}) != map_occupied.end()) // Check cell above
        {
            up_blocked = true;
        }
        if (map_occupied.find({pre_X - 1, pre_y}) != map_occupied.end()) // Check cell below
        {
            down_blocked = true;
        }

        // condition if zombie Blocked or not
        if (pre_X == 1 && pre_y == 1 && down_blocked && right_blocked) // top-left corner
        {
            is_blocked = true;
        }
        else if (pre_X == 1 && pre_y == boardY_ && up_blocked && right_blocked) // bottom-left corner
        {
            is_blocked = true;
        }
        else if (pre_X == boardX_ && pre_y == 1 && down_blocked && left_locked) // top-right corner
        {

            is_blocked = true;
        }
        else if (pre_X == boardX_ && pre_y == boardY_ && up_blocked && left_locked) // bottom-right corner
        {
            is_blocked = true;
        }
        else if (pre_X == 1 && up_blocked && down_blocked && right_blocked) // left edge
        {
            is_blocked = true;
        }
        else if (pre_X == boardX_ && up_blocked && down_blocked && left_locked) // right edge
        {
            is_blocked = true;
        }
        else if (pre_y == 1 && left_locked && down_blocked & right_blocked) // top edge
        {
            is_blocked = true;
        }
        else if (pre_y == boardY_ && up_blocked && right_blocked && left_locked) // bottom edge
        {
            is_blocked = true;
        }
        else if (up_blocked && down_blocked && left_locked && right_blocked) // surrounded
        {
            is_blocked = true;
        }

        do
        {

            zombie_move = rand() % 5;

            if (zombie_move == 1) // up
            {
                zombie_List[i][2]--;
            }
            else if (zombie_move == 2) // down
            {
                zombie_List[i][2]++;
            }
            else if (zombie_move == 3) // left
            {
                zombie_List[i][1]--;
            }
            else if (zombie_move == 4) // right
            {
                zombie_List[i][1]++;
            }

            x = zombie_List[i][1];
            y = zombie_List[i][2];

            if (is_blocked || map_occupied.find({x - 1, y - 1}) != map_occupied.end() || x < 1 || x > boardX_ || y < 1 || y > boardY_)
            {
                if (is_blocked)
                {
                    zombie_List[i][1] = pre_X;
                    zombie_List[i][2] = pre_y;

                    zombie_move = 5;
                    break;
                }
                zombie_List[i][1] = pre_X;
                zombie_List[i][2] = pre_y;
            }

            // cout << "current zombie " << zombieList_[i][0] << " new coordinate " << x << y << endl;

        } while (map_occupied.find({x - 1, y - 1}) != map_occupied.end() || x < 1 || x > boardX_ || y < 1 || y > boardY_);

        char zombChar = to_string(i + 1)[0];

        if (zombie_move == 1) // up
        {
            map_occupied.insert({x - 1, y - 1});
            map_occupied.erase({x - 1, y});

            map_[y - 1][x - 1] = zombChar;
            map_[y][x - 1] = ' ';

            move = "up";
        }
        else if (zombie_move == 2) // down
        {
            map_occupied.insert({x - 1, y - 1});
            map_occupied.erase({x - 1, y - 2});

            map_[y - 1][x - 1] = zombChar;
            map_[y - 2][x - 1] = ' ';

            move = "down";
        }
        else if (zombie_move == 3) // left
        {
            map_occupied.insert({x - 1, y - 1});
            map_occupied.erase({x, y - 1});

            map_[y - 1][x - 1] = zombChar;
            map_[y - 1][x] = ' ';

            move = "left";
        }
        else if (zombie_move == 4) // right
        {
            map_occupied.insert({x - 1, y - 1});
            map_occupied.erase({x - 2, y - 1});

            map_[y - 1][x - 1] = zombChar;
            map_[y - 1][x - 2] = ' ';

            move = "right";
        }
        zombie_List[i][6] = zombieTurn;
        displayMap();

        // for (auto elem : occupiedMap_)
        // {
        //     cout << "(" << elem.first + 1 << ", " << elem.second + 1 << ")\n";
        // }

        cout << "   Alien    : Life " << setw(3) << alienHealth << ", Attack " << setw(3) << alienAttack << endl;
        for (int j = 0; j < zombieCount_; j++)
        {
            if (zombie_List[j][6] == 1)
            {
                cout << "-> Zombie " << zombie_List[j][0] << " : Life " << setw(3) << zombie_List[j][3] << ", Attack " << setw(3) << zombie_List[j][4] << endl;
            }
            else
            {
                cout << "   Zombie " << zombie_List[j][0] << " : Life " << setw(3) << zombie_List[j][3] << ", Attack " << setw(3) << zombie_List[j][4] << endl;
            }
        }
        zombie_List[i][6] = 0;

        if (zombie_move == 5)
        {
            cout << "\n  zombie " << zombie_List[i][0] << " can't move\n\n";
        }
        else
        {
            cout << "\n  zombie " << zombie_List[i][0] << " moving " << move << "\n\n";
        }

        int diffX = abs(alien_X - zombie_List[i][1]);
        int diffY = abs(alien_Y - zombie_List[i][2]);

        if (diffX + diffY <= zombie_List[i][5])
        {
            alienHealth = alienHealth - zombie_List[i][4];

            cout << "  Zombie " << zombie_List[i][0] << " deal " << zombie_List[i][4] << " damage to the Alien\n\n ";
            if (alienHealth <= 0)
            {
                alienHealth = 0;
                break;
            }
        }
        // else
        // {
        //     cout << "  The Alien is outside Zombie " << zombieList_[i][0] << "'s range\n\n ";
        // }

        pause();
    }
    if (alienHealth <= 0)
    {
        cout << "The alien is now D E A D\n\n ";
        pause();
        gameOver();
    }
}

// menu but we dont sure o to save and load
void Boards::helpMenu()
{
    cout << "\n Commands: \n";
    cout << " 1. up    - Moves Up\n";
    cout << " 2. down  - Moves Down\n";
    cout << " 3. left  - Moves Left\n";
    cout << " 4. right - Moves RIght\n";
    cout << " 5. help  - Display This Help Menu\n";
    cout << " 6. quit  - Quit the Game\n \n";
    cout << " Returning to the game. \n ";
    pause();
    commandMenu();
}

void Boards::commandMenu()
{
    displayMap();
    displayAttributeAlien();
    string command;
    cout << "\n command => ";
    cin >> command;

    if (command == "right")
    {
        alienMoveRight();
    }
    else if (command == "left")
    {
        alienMoveLeft();
    }
    else if (command == "up")
    {
        alienMoveUp();
    }
    else if (command == "down")
    {
        alienMoveDown();
    }

    else if (command == "help")
    {
        helpMenu();
    }

    else if (command == "quit")
    {
        string confirmQuit;
        cout << "\n Are you sure to quit the game? (y/N)\n confirming => ";
        cin >> confirmQuit;

        if (confirmQuit == "n" || confirmQuit == "N")
        {
            cout << " Returning to the Game\n\n ";
            pause();
            commandMenu();
        }
        else if (confirmQuit == "y" || confirmQuit == "Y")
        {
            cout << " Returning to the Main Menu,\n\n ";
            pause();
            mainMenu();
        }
        else
        {
            cout << " Invalid input, return to the Game\n\n ";
            pause();
            commandMenu();
        }
    }
    else
    {
        cout << " Invalid input, please try again\n\n ";
        pause();
        commandMenu();
    }
}

void gameStart(Boards &board)
{
    int board_x = board.getDim_X(), board_y = board.getDim_Y();
    int zombCount = board.getZombieCount();

    board.displayDefaultSetting(board_x, board_y, zombCount);
    board.commandMenu();
}

void Boards::gameOver()
{

    clear();
    cout << " **************************************" << endl;
    cout << " *                                    *" << endl;
    cout << " *            GAME  OVER  !!          *" << endl;
    cout << " *                                    *" << endl;
    cout << " **************************************\n\n";

    cout << " Do you want to Play Again? or \n return to the Main Menu? (y/N) => ";

    string confirm;
    cin >> confirm;

    if (confirm == "n" || confirm == "N")
    {
        cout << "\n Returning to the Main Menu\n\n ";
        pause();
        mainMenu();
    }
    else if (confirm == "y" || confirm == "Y")
    {
        cout << "\n Returning to the Default Game Setting\n\n ";
        pause();

        int boardX = getDim_X(), boardY = getDim_Y();
        int zombCount = getZombieCount();

        displayDefaultSetting(boardX, boardY, zombCount);
        commandMenu();
    }
    else
    {
        cout << "\n Invalid input, please try again\n\n ";
        pause();
        gameOver();
    }
}

void mainMenu()
{
    clear();
    Boards board;
    string input;
    cout << " ************************************" << endl;
    cout << " *              WELCOME             *" << endl;
    cout << " *                TO                *" << endl;
    cout << " *         ALIEN  VS  ZOMBIES       *" << endl;
    cout << " ************************************" << endl;
    cout << " *         OPTIONS:                 *" << endl;
    cout << " *     1 - New Game                 *" << endl;
    cout << " *     2 - Load Game                *" << endl;
    cout << " *     3 - Exit                     *" << endl;
    cout << " *                                  *" << endl;
    cout << " *    this game has been made by    *" << endl;
    cout << " *         alif,aniq,zaquan         *" << endl;

    cout << " ************************************" << endl
         << endl;

    cout << " Enter => ";
    cin >> input;

    if (input == "1")
    {
        gameStart(board);
    }
    else if (input == "2")
    {
        // loadGame();
        cout << " The option has yet to be implemented, please try again later ;)\n\n ";
        pause();
        mainMenu();
    }
    else if (input == "3")
    {
        string confirmExit;
        cout << "\n Are you sure to exit the game? (y/N)\n confirming => ";
        cin >> confirmExit;

        if (confirmExit == "y" || confirmExit == "Y")
        {
            clear();
            cout << " Have a nice day :)\n ";
            pause();
            exit(0);
        }
        else if (confirmExit == "n" || confirmExit == "N")
        {
            cout << " Returning to the Main Menu\n\n ";
            pause();
            mainMenu();
        }
        else
        {
            cout << " Invalid input, return to the Main Menu\n ";
            pause();
            mainMenu();
        }
    }
    else
    {
        cout << " Invalid input, please try again\n\n ";
        pause();
        mainMenu();
    }
}

// main
int main()
{
    // Board board;
    // gameStart(board);
    mainMenu();

    return 0;
}