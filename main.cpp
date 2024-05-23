// Header file
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <graphics.h>

// Класс Krug дополнен методами для задачи
struct Point {
    int X, Y;
};

// "Object" class
class Object {
public:
    int X, Y;
    unsigned short Cvet;

    void Init(int XN, int YN, unsigned short Color) {
        X = XN;
        Y = YN;
        Cvet = Color;
    }

    virtual void Show() {}
    virtual void Hide() {}
    void Locat(int& XL, int& YL) {
        XL = X;
        YL = Y;
    }
    void Fly(int Cost) {
        X += Cost;
        Y += Cost;
    }
};

// "Circle" class
class Krug : public Object {
public:
    unsigned short Radius;

    Krug(int XN, int YN, unsigned short R, unsigned short Color) {
        Init(XN, YN, Color);
        Radius = R;
    }

    virtual void Show() {
        setcolor(Cvet);
        circle(X, Y, Radius);
    }

    virtual void Hide() {
        setcolor(getbkcolor());
        circle(X, Y, Radius);
    }

    void Fly(int Cost) {
        Object::Fly(Cost);
    }

    // Функция SetAngle
    void Krug::SetAngle(int StartAngle, int EndAngle)
    {
        pieslice(X, Y, Radius, StartAngle, EndAngle);
    }

// Функция ChangeColor
    void Krug::ChangeColor(Color Color)
    {
        setColor(Color);
    }

// Функция Move
    void Krug::Move(int dx, int dy)
    {
        X += dx;
        Y += dy;
    }

// Функция Show
    void Krug::Show()
    {
        SetAngle(0, 360);
        ChangeColor(Color);
        pieslice(X, Y, Radius, 0, 360);
    }

// Функция Hide
    void Krug::Hide()
    {
        ChangeColor(GetBkColor);
        pieslice(X, Y, Radius, 0, 360);
    }
};

// "Ring" class
class Ring : public Krug {
public:
    unsigned short Width;

    Ring(int XN, int YN, unsigned short R, unsigned short Color, unsigned short Wid) : Krug(XN, YN, R, Color) {
        Width = Wid;
    }

    virtual void Show() {
        setcolor(Cvet);
        circle(X, Y, Radius);
        circle(X, Y, Radius - Width);
    }

    virtual void Hide() {
        setcolor(getbkcolor());
        circle(X, Y, Radius);
        circle(X, Y, Radius - Width);
    }

    void Fly(int Cost) {
        Object::Fly(Cost);
    }
};

int main() {
    srand(time(NULL));

    // Create objects
    Krug Krug1(150, 40, 50, 117);
    Krug Krug2(450, 80, 90, 50, 10);
    Ring Ring1(250, 120, 70, 255, 10);

    int XX, YY;

    // Event loop
    while (!kbhit()) {
        // Move objects
        if (kbhit()) {
            char Key = getch();
            switch (Key) {
                case 72: Krug1.Fly(100); break;
                case 80: Krug1.Fly(-100); break;
                case 75: Krug2.Fly(100); break;
                case 77: Krug2.Fly(-100); break;
                case 71: Ring1.Fly(60); break;
                case 79: Ring1.Fly(-60); break;
            }
        }

        // Display objects
        Krug1.Show();
        Krug2.Show();
        Ring1.Show();

        // Создать объект класса
        Krug krug(150, 40, 50, 117);

        // Задать начальный и конечный углы вырезанного сектора
        krug.SetAngle(0, 180);

        // Изменить цвет фигуры
        krug.ChangeColor(RGB(255, 0, 0));

        // Переместить фигуру на 10 пикселей вправо и 20 пикселей вниз
        krug.Move(10, 20);

        // Отобразить фигуру на экране
        krug.Show();

        // Скрыть фигуру с экрана
        krug.Hide();

        delay(30);

        // Change color
        Krug1.Cvet = rand() % 16777215;
        Krug2.Cvet = rand() % 16777215;
        Ring1.Cvet = rand() % 16777215;

        // Move objects
        XX = round((rand() / (double)RAND_MAX - 0.5) * 100);
        YY = round((rand() / (double)RAND_MAX - 0.5) * 100);

        Krug1.Locat(XX, YY);
        Krug2.Locat(XX, YY);
        Ring1.Locat(XX, YY);

        // Clear screen
        cleardevice();
    }

    getch();
    return 0;
}

