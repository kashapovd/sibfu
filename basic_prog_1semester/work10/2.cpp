//Кашапов Ярослав, 12 вар., 100%

#include <iostream>
using namespace std;

int *read_array(int len) {
    int *arr;
    arr = new int[len];
    for(int i=0; i<len; i++) {
        cout << i << "-элемент = ";
        cin >> arr[i];
    }
    cout << "\n";
    return arr;
}

void print_array(int *arr, int len) {
    cout << " = { ";
    for(int k=0; k<len; k++) {
        cout << arr[k] << " ";
    }
    cout << "}\n";
}

void sort(int *arr, int len, bool asc) {
    int tmp = 0;
    for(int i=0; i<len-1; i++) {
        for(int j = 0; j<len-1; j++) {
            if((asc && arr[j] > arr[j+1]) || (!asc && arr[j] < arr[j+1])) {
                tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

bool find_num(int *arr, int num, int len) {
    for(int i=0; i<len; i++) {
        if(*(arr+i) == num) {
            return true;
        }
    }
    return false;
}

int count_num(int *arrA, int *arrB, int lenA, int lenB) {
    int count = 0, prev_count = 0;
    for(int j=0; j<lenA; j++) {
        if(!find_num(arrB, arrA[j], lenB)) {
            if(arrA[j] == prev_count && j != 0) {
                continue;
            }
            prev_count = arrA[j];
            count++;
        }
    }
    return count;
}

int *gen_arrC(int *arrA, int *arrB, int lenA, int lenB, int lenC) {
    int *arrC, k = 0, prev_count = 0;
    arrC = new int[lenC];
    for(int i=0; i<lenA; i++) {
        if(!find_num(arrB, arrA[i], lenB)) {
            if(arrA[i] == prev_count && i != 0) {
                continue;
            }
            prev_count = arrA[i];
            arrC[k] = arrA[i];
            ++k;
        }
    }
    return arrC;
}

void print_all(int *arrA, int *arrB, int *arrC, int lenA, int lenB, int lenC, bool asc) {
    cout << "массив A";
    print_array(arrA, lenA);
    cout << "отсортированный массив A";
    sort(arrA, lenA, asc);
    print_array(arrA, lenA);
    cout << "массив B";
    print_array(arrB, lenB);
    cout << "отсортированный массив B";
    sort(arrB, lenB, asc);
    print_array(arrB, lenB);
    cout << "массив С";
    print_array(arrC, lenC);
    cout << "отсортированный массив C";
    sort(arrC, lenC, asc);
    print_array(arrC, lenC);
}

int main() {
    int *arrA, *arrB, *arrC, lenA, lenB, lenC = 0;
    bool asc;

    cout << "длина массива А = ";
    cin >> lenA;
    cout << "длина массива В = ";
    cin >> lenB;
    cout << "Как сортировать массив?\n(1 - по возрастанию, 0 - по убыванию): ";
    cin >> asc;
    if(asc) cout << "Вы выбрали сортировку по возрастанию\n\n";
    else cout << "Вы выбрали сортировку по убыванию\n\n";

    cout << "Заполнение массива A:\n";
    arrA = read_array(lenA);
    cout << "Заполнение массива B:\n";
    arrB = read_array(lenB);

    lenC = count_num(arrA, arrB, lenA, lenB);
    arrC = gen_arrC(arrA, arrB, lenA, lenB, lenC);

    print_all(arrA, arrB, arrC, lenA, lenB, lenC, asc);

    delete[] arrA;
    delete[] arrB;
    delete[] arrC;
    arrA = nullptr;
    arrB = nullptr;
    arrC = nullptr;
    return 0;
}
