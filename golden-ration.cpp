// Задача - Однажды Женя посмотрел серию одного известного мультсериала и узнал о золотом сечении. Его красота произвела впечатление на Женю. По его подобию он придумал свой способ раскраски прямоугольника со сторонами a и b. Пусть в данный момент у Жени не раскрашен прямоугольник со сторонами c и d, c 6 d, тогда он раскрашивает квадрат со стороной c, который прилегает к трем сторонам прямоугольника, в новый цвет. После этого он повторяет процесс с оставшейся частью. Такой способ покраски очень понравился Жене, поэтому он начал раскрашивать все прямоугольники, которые попадаются под руку. Оказалось, что некоторые прямоугольники раскрашиваются довольно долго, поэтому перед раскраской Женю интересует, в какое количество цветов будет покрашен прямоугольник.

#include <bits/stdc++.h>
#include <iostream>

using namespace std;


unsigned long long solve(unsigned long long a, unsigned long long b) {
    unsigned long long counter = 0;
    unsigned long long difference;
    while (true) {
        if (a == b) {
            counter += 1;
            break;
        } else if (a < b) {
            difference = b / a;
            b -= (a * (difference));
            counter += difference;

            if (b == 0) {
                break;
            }
        } else if (a > b) {
            difference = a / b;
            a -= (b * (difference));
            counter += difference;

            if (a == 0) {
                break;
            }

        }
    }


    return counter;
}


int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    unsigned long long a, b;
    cin >> a >> b;

    cout << solve(a, b);

    return 0;
}
