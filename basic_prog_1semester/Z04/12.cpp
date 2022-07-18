/*
 * 12. Даны целые числа x, y, sx, sy. Вывести прямоугольник из символов «@» с размерами sx по горизонтали, sy по вертикали,
 * левый верхний угол которого находится в точке с координатами (x, y). Ось X направлена вправо, ось Y — вниз.
 * Начало координат находится в левом верхнем углу в точке (0,0). Вывод прямоугольника оформить как функцию
 * void print_rect(int x, int y, int sx, int sy).
 */

#include <iostream>
using namespace std;

void print_rect(int x, int y, int sx, int sy);

int main() {
    int x, y, sx, sy;

    cout << "x = ";
    cin >> x;
    cout << "y = ";
    cin >> y;
    cout << "sx = ";
    cin >> sx;
    cout << "sy = ";
    cin >> sy;

    print_rect(x, y, sx, sy);
}

void print_rect(int x, int y, int sx, int sy) {
    for(int i = 0; i < y; i++) {
        cout << "\n";
    }
    for(int i = 0; i < sy; i++) {
        for(int k = 0; k < x; k++) {
            cout << " ";
        }
        for(int l = 0; l < sx; l++) {
            cout << "@";
        }
        cout << "\n";
    }
}


