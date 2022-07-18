// Кашапов Ярослав, 12 вар., 100%

#define variant 4

#include <iostream>
#include <fstream>
using namespace std;

#define PATH_TXT "yourpath"
#define PATH_BIN "yourpath"

void text2bin(istream &, ostream &);
void my_task(istream &);
int *getRow(istream &, int, int);
void getMatrSize(istream &, int &, int &);
// 1 variant
bool isAscending(int *, int);
bool binSearch(int *, int, int);
// 2 variant
int searchFreq(int *, int);
// 4 variant
bool isDecending(int *, int);
bool linearSearch(int *, int, int);

int main() {
    fstream binRW; // read-write stream
    ifstream textR; // read stream

    textR.open(PATH_TXT, ios::in); // open for read
    if (!textR.is_open()) {
        cerr << "Unable to open file " << PATH_TXT << endl;
        exit(0);
    }
    binRW.open(PATH_BIN, ios::binary | ios::trunc | ios::out | ios::in); // open for read and write
    if (!binRW.is_open()) {
        cerr << "Unable to open/create file" << PATH_BIN << endl;
        exit(0);
    }

    text2bin(textR, binRW);
    my_task(binRW);

    binRW.close();
    textR.close();

    return 0;
}

void text2bin(istream &ist, ostream &ost) {
    int buff;
    while (ist >> buff) {
        //cout << buff << "  " << sizeof (buff) << "\n";
        ost.write(reinterpret_cast<char *>(&buff), sizeof(buff));
    }
}

void my_task(istream &ist) {
    int n, m;
    getMatrSize(ist, n, m);
    cout << "Matrix size: " << n << 'x' << m << endl;

    int k;
    cout << "k: ";
    cin >> k;

    if (k > n || k < 1) {
        cerr << "Error, " << k << " row doesn't exist" << endl;
        exit(0);
    }

    int *row = getRow(ist, k, m);

    cout << k << " row: ";
    for (int i = 0; i < m; i++)
        cout << *(row + i) << " ";
    cout << endl;

#if(variant%10==1)
    if (isAscending(row, m)) {
        if (binSearch(row, k, m))
            cout << "Number " << k << " included in this row" << endl;
        else
            cout << "Number " << k << " excluded in this row" << endl;
    } else
         cout << "All numbers in the row don't ascending" << endl;

#elif(variant%10==2)
    int num = searchFreq(row, m);
    if (num == -1) {
        cout << "All numbers occur ones" << endl;
    } else {
        cout << "The most frequent number: " << num << endl;
    }

#elif(variant%10==4)
    if (isDecending(row, m)) {
        if (linearSearch(row, k, m)) {
            cout << "Number " << k << " included in this row" << endl;
	} else {
	    cout << "Number " << k << " excluded in this row" << endl;
        }
    } else
 	cout << "All numbers in the row don't decending" << endl;

#endif

    delete [] row;
    row = nullptr;
}

void getMatrSize(istream &ist, int &n, int &m) {
    ist.seekg(0*sizeof (int), ist.beg);
    ist.read(reinterpret_cast<char *>(&n), sizeof (int));
    ist.seekg(1*sizeof (int), ist.beg);
    ist.read(reinterpret_cast<char *>(&m), sizeof (int));
}

int *getRow(istream &ist, int k, int m) {
    int size_int = sizeof(int);
    int *row = new int[m];
    for (int i = m*(k-1), j = 0; i < m*((k-1)+1); i++, j++) {
        int buff;
        ist.seekg(i*size_int + 2*size_int, ist.beg);
        ist.read(reinterpret_cast<char *>&buff, size_int);
        *(row+j) = buff;
    }
    return row;
}

int searchFreq(int *array, int len) {
    int count, num, max=0;
    for (int i = 0; i < len; i++) {
        count = 0;
        for (int j = 0; j < len; j++) {
            if (*(array+i) == *(array+j)) {
                count++;
            }
        }
        if (count > max) {
           max = count;
           num = *(array+i);
        }
    }
    if (max != 1) {
        return num;
    }
    return -1;
}

bool isAscending(int *array, int len) {
    for (int i = 0; i < len-1; i++) {
        if (*(array+i) > *(array+i+1)) {
            return false;
        }
    }
    return true;
}

bool binSearch(int *array, int key, int len) {
    /* Binary Search */
    int l = -1;
    int r = len;
    while (l < r - 1) {
        int mid = (l+r) / 2;
        if (*(array+mid) < key) {
            l = mid;
        } else {
            r = mid;
        }
    }
    if (key == *(array+r)) {
        return true;
    } else {
        return false;
    }
}

bool linearSearch(int *array, int key, int len) {
    for (int i = 0; i < len; i++) {
        if (key == *(array+i)) {
            return true;
        }
    }
    return false;
}

bool isDecending(int *array, int len) {
    for (int i = 0; i < len-1; i++) {
        if (*(array+i) < array[i+1]) {
            return false;
        }
    }
    return true;
}
