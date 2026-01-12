#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

class Player {
protected:
    string name;

public:
    Player(string playerName) { name = playerName;}

    virtual void getShot(int& x, int& y) {
        cout << "\n" << name << ", unesi koordinate (x y): ";
        cin >> x >> y;
    }

    
};

class AIPlayer : public Player {
public:
    AIPlayer(string playerName) : Player(playerName) {}

    void getShot(int& x, int& y) override {
        x = rand() % 5; 
        y = rand() % 5;
        cout << "\n" << name << " puca na: " << x << " " << y << endl;
    }
};

class Board {
private:
    static const int SIZE = 5; 
    static const int SHIPS = 3;

    char grid[SIZE][SIZE]; 
    int ships[SHIPS][2];
    int shipsLeft;

public:
    Board() {
        shipsLeft = SHIPS;

        for (int i = 0; i < SIZE; i++) { 
            for (int j = 0; j < SIZE; j++) {
                grid[i][j] = '~';
            }
        }

        ships[0][0] = 1; ships[0][1] = 1;
        ships[1][0] = 3; ships[1][1] = 2;
        ships[2][0] = 4; ships[2][1] = 4;

        for (int i = 0; i < SHIPS; i++) {
            int x = ships[i][0];
            int y = ships[i][1];
            grid[x][y] = 'S';
        }

    }

    void printBoard(bool hideShips) { 
        cout << "\n  0 1 2 3 4\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " ";
            for (int j = 0; j < SIZE; j++) {
                char c = grid[i][j];
                if (hideShips && c == 'S')
                    cout << "~ ";
                else
                    cout << c << " ";
            }
            cout << endl;
        }
    }

    bool shoot(int x, int y) {
        if (grid[x][y] == 'X' || grid[x][y] == 'O') {
            cout << "Vec iskoristeni pokusaj!" << endl;
            return false;
        }

        for (int i = 0; i < SHIPS; i++) {
            if (ships[i][0] == x && ships[i][1] == y) {
                grid[x][y] = 'X';
                shipsLeft--;
                return true;
            }
        }

        grid[x][y] = 'O';
        return false;
    }

    bool allShipsSunk() {
        return shipsLeft == 0;
    }
};

int main() {
    srand(time(0));
    
    string Plname;
    cout << "Unesi ime igraca: ";
    cin >> Plname;

    Player human(Plname);
    AIPlayer ai("Ai");

    Board playerBoard;
    Board aiBoard;

    int x, y;

    while (true) {
        cout << "\nTvoj Board: ";
        playerBoard.printBoard(false);

        cout << "\nAI Board: ";
        aiBoard.printBoard(true);

        human.getShot(x, y);
        if (aiBoard.shoot(x, y))
            cout << "HIT!\n";
        else
            cout << "MISS!\n";

        if (aiBoard.allShipsSunk()) {
            cout << "\nPOBIJEDNIK JE IGRAC" << endl;
            break;
        }
        ai.getShot(x, y);
        if (playerBoard.shoot(x, y))
            cout << "HIT!\n";
        else
            cout << "MISS!\n";

        if (playerBoard.allShipsSunk()) {
            cout << "\nAI JE POBIJEDIO.\n";
            break;
        }
    }

    return 0;
}
