//Кашапов Ярослав, 12 вариант, 100%

#include <iostream>
#include <cmath>
using namespace std;

int *read_array(int len) { // функция создания и заполнения динамического массива A[]
    int *A;
    A = new int[len]; // создание динамического массива A[]
    srand(static_cast<unsigned int>((time(0)))); // инициализация датчика случайных значений таймером
    for(int i=0; i < len; i++) { // заполение массива случайными числами со случайным знаком
        *(A+i) = rand()%10 * static_cast<int>(pow((-1), rand()));
    }
    return A; // возвращаем указатель на массив
}

void print_arrayA(int *arr, int len) { // функция вывода A[]
    cout << "A[] = { ";
    for(int m=0; m < len; m++) {
        cout << *(arr+m) << " ";
    }
    cout << "}\n";
}

void print_arrayB(int *arr, int len) { // функция вывода B[]
    cout << "B[] = { ";
    for(int m=0; m < len; m++) {
        cout << *(arr+m) << " ";
    }
    cout << "}\n";
}

int last_neg(int *arr, int len) { // функция поиска последнего отрицательного значения
    int last = -1; // -1 для того, чтобы отследить изменялось ли значение; если нет, то в массиве нет отрицательных чисел
    for(int k=0; k < len; k++) {
        if (*(arr+k) < 0) last = k;
    }
    return last;
}

int my_task(int *A, int lenA, int *B, int lenB) { // функция, формирующая B[]
    for(int i=0, j=0; i < lenA; i++) {
        if(i != last_neg(A, lenA)) { // если попадётся i, равное послед. отр. значению, то следующие 2 шага будут пропущены
            *(B+j) = *(A+i);
            j++;
        }
    }
    print_arrayB(B, lenB); // вывод B[]
    return lenB;
}

int main() {
    int lenA, lenB, *arrA, *arrB;
    cout << "len = ";
    cin >> lenA;

    arrA = read_array(lenA); // вызов функции создания и заполнения динамического массива A[lenA]
    print_arrayA(arrA, lenA); // вызов функции вывода A[]

    int last = last_neg(arrA, lenA); // получение индекса последней отрицательной цифры
    cout << "индекс последнего отрицательного числа = " << last << endl;
    if(last == -1) { // если в массиве нет отрицательных чисел, тогда
        lenB = lenA; // длина B[] равна длине A[]
        arrB = new int[lenA];
    }
    else { // если отрицательное число есть, тогда
        lenB = lenA - 1; // длина B[] уменьшится на 1
        arrB = new int[lenB];
    }
    my_task(arrA, lenA, arrB, lenB); // вызов функции, заполняющей B[] в соответствии с заданием
    cout << "размер массива B[] = " << lenB << endl;
}
