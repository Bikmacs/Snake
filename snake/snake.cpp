#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <windows.h>


const int height = 10;
const int width = 20;
int fr_x, fr_y;
int point;
int x = 10; 
int y = 5;  

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {};
};

class Snak {
private:
    Node* tail;
    Node* head;
    int length;
public:
    enum snakesDir { STOP = 0, LEFT, RIGHT, UP, DOWN };
    snakesDir press;
    bool GameOver;

    Snak() {
        head = new Node(0); 
        press = STOP;
        GameOver = false;
        length = 0;
        fr_x = rand() % (width - 2) + 1; 
        fr_y = rand() % (height - 2) + 1; 
    }

    void moving() {
        if (_kbhit()) { 
            int key = _getch();
            switch (key) {  
            case 'a': press = LEFT; break;
            case 's': press = DOWN; break;
            case 'd': press = RIGHT; break;
            case 'w': press = UP; break;
            }
        }
    }

    void deletedPLus() {
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Node* temp = head;
            while (temp->next != tail) {
                temp = temp->next;
            }
            delete tail;
            tail = temp;
            tail->next = nullptr;
        }
        length++;
    }

    void print() {
        system("cls");
        for (int i = 0; i < width; i++) {
            std::cout << "#";
        }
        std::cout << std::endl;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (j == 0 || j == width - 1) {
                    std::cout << "#";
                }
                else if (i == y && j == x) {
                    std::cout << "O"; 
                }
                else if (i == fr_y && j == fr_x) {
                    std::cout << "0";
                }
                else {
                    std::cout << " "; 
                }
            }
            std::cout << std::endl;
        }

        for (int i = 0; i < width; i++) {
            std::cout << "#";
        }
        std::cout << std::endl;
        std::cout << point;
    }

    void logic() {
        switch (press)
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        }

        if (x < 1 || x >= width - 1 || y < 0 || y >= height) {
            GameOver = true;
        }

        if (x == fr_x || y == fr_y) {
            point++;
            
            
            deletedPLus();
        }
    }
};

int main() {
    setlocale(0, "rus");
    Snak snake;
    while (!snake.GameOver) { 
        snake.moving(); 
        snake.print();
        snake.logic();
        Sleep(100);
    }

    std::cout << "Вы проиграли" << std::endl;
    return 0;
}
