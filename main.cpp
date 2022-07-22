#include <iostream> // Wejscie, wyjscie. Wpisywanie tekstu
#include <windows.h>    // system(), Beep(), sleep()
#include <conio.h>  // getch()
#include <vector>   // vector

int const MAP_X = 20;   // Stale typu int
int const MAP_Y = 30;

using namespace std;

struct Position2D   // Przechowuje pozycje na plaszczyznie 2D
{
    int x, y;
};

class Game  // Glowna klasa gry
{
    Position2D player;
    vector<Position2D> monsters;
    int score;
    int monster_selected;
    bool not_failed;
public:
    Game()
    : monster_selected(0), score(0), not_failed(true)
    {
        player.x = 10;  // Pozycja gracza na start
        player.y = 10;
    }

    void fail() // Przegrana
    {
        system("cls");
        cout << "GAME OVER!" << endl;
        cout << "Monsters: " << monster_selected << endl;
        cout << "Score: " << score*monster_selected << endl;
        Beep(500, 200);
        Beep(500, 200);
        Beep(500, 200);
        not_failed = false;
    }

    bool fail_check()
    {
        return not_failed;
    }

    void start()    // Start gry
    {
        system("title Simple-Game");
        char menu = 'f';
        cout << "==========================" << endl
             << "= WELCOME TO SIPMLE-GAME =" << endl
             << "==========================" << endl
             << "Selected number of monster" <<
                " you want to have in game." << endl
             << "More monsters means higher score multi" << endl
             << "Make your choice: " << endl
             << "a) 1, b) 2, c) 3, d) 4 " << endl;
        cin >> menu;

        switch(menu)
        {
        case 'a':
            create_monsters(1);
            monster_selected = 1;
        break;
        case 'b':
            create_monsters(2);
            monster_selected = 2;
        break;
        case 'c':
            create_monsters(3);
            monster_selected = 3;
        break;
        case 'd':
            create_monsters(4);
            monster_selected = 4;
        break;
        default:
            create_monsters(4);
            monster_selected = 4;
        }
        not_failed = true;
        system("cls");
    }

void create_monsters(int number)    // Stworzenie potworow
{
    Position2D monster = {19, 19};  // Tworzy potwory
    Position2D monster2 = {0,0};
    Position2D monster3 = {0,29};
    Position2D monster4 = {19, 0};

    switch(number)      // Wrzuca stworzone potwory do wektora
                        // w zaleznosci od tego ile zostalo wybranych
    {
    case 1:
        monsters.push_back(monster);
    break;
    case 2:
        monsters.push_back(monster);
        monsters.push_back(monster2);
    break;
    case 3:
        monsters.push_back(monster);
        monsters.push_back(monster2);
        monsters.push_back(monster3);
    break;
    case 4:
        monsters.push_back(monster);
        monsters.push_back(monster2);
        monsters.push_back(monster3);
        monsters.push_back(monster4);
    break;
    }
}

void score_up() // Podaj wynik
{
    score++;
}

vector<Position2D>& return_ref_to_monster() // Zwraca referencje do wektora Position2D
                                            // ktory przechowuje pozycje potworow
{
    return monsters;
}

void move_player()  // Przeuwa gracza
{
    char move = getch();    // Pobiera klawisz do zmiennej move

    switch(move)
    {
        case 'w':
            if(player.x-1 == -1)
                break;
            else
                player.x--;
        break;
        case 's':
            if(player.x+1 == MAP_X)
                break;
            else
                player.x++;
        break;
        case 'a':
            if(player.y-1 == -1)
                break;
            else
                player.y--;
        break;
        case 'd':
            if(player.y+1 == MAP_Y)
                break;
            else
                player.y++;
        break;
    }
}

void monster_ai()   // "ai" potworow
{
    for(int i=0; i<monsters.size(); i++)    // Prosty algorytm goniacego Ai
    {
        if(monsters[i].x < player.x)
            monsters[i].x++;
        if(monsters[i].x > player.x)
            monsters[i].x--;
        if(monsters[i].y < player.y)
            monsters[i].y++;
        if(monsters[i].y > player.y)
            monsters[i].y--;
        // Jezeli jakis potwor ma takie same pozycje jak gracz
        // To znaczy, ze go zlapal, wiec koniec gry
        if(monsters[i].x == player.x && monsters[i].y == player.y)
        {
            cout << "Got you!" << endl;
            fail();
        }
    }
}


    Position2D& return_ref_to_player()  // Zwraca referencje do Position2D przechowujacego
                                        // pozycje gracza
    {
        return player;
    }

};

class Map
{
    int map[MAP_X][MAP_Y];  // Mapa gry

public:
    Map()   // Zeruje mape
    {
        for(int i=0; i<MAP_X; i++)
        {
            for(int j=0; j<MAP_Y; j++)
            {
                map[i][j] = 0;
            }

        }
    }

    void draw() // Rysuje mape
    {
        for(int i=0; i<MAP_X; i++)
        {
            for(int j=0; j<MAP_Y; j++)
            {
                switch(map[i][j])   // Zamienia liczby na
                                    // odpowiednie znaki graficzne
                {
                case 0:
                    cout << ".";
                break;
                case 1:
                    cout << "M";
                break;
                case 2:
                    cout << "@";
                }
            }
            cout << endl;   // Kolejny wiersz mapy
        }
    }


    void reset()  // Resetuje mape
    {
        for(int i=0; i<MAP_X; i++)
        {
            for(int j=0; j<MAP_Y; j++)
            {
                map[i][j] = 0;
            }
        }
    }

    void put_player(Position2D& player) // Umieszczenie gracza na mapie
    {
        map[player.x][player.y] = 2;
    }

    void put_monster(vector<Position2D>& monsters)  // Umieszczenie potworow na mapie
    {
        for(int i=0; i<monsters.size(); i++)
        {
            map[monsters[i].x] [monsters[i].y] = 1;
        }
    }
};

int main()
{
    Map m;  // Obiekt typu Map i Game
    Game g;

    g.start();  // Start gry

    while(g.fail_check())   // Glowna petla gry
    {
        m.reset();
        m.put_player(g.return_ref_to_player());
        m.put_monster(g.return_ref_to_monster());
        m.draw();
        g.monster_ai();
        g.move_player();
        g.score_up();
        system("cls");
    }

    return 0;
}
