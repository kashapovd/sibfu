// Кашапов Ярослав, 12 вар., 100%
// compile: g++ 2.cpp -lncurses

#include <fstream>
#include <cstdio>
#include <ciso646>
#include <ncurses.h>
#include <cmath>

#define OST "your path"
#define IST "your path"
#define INSERT_LIST_NUM 3

struct node
{
    int data;
    node *prev;
    node *next;
};

struct list
{
    node *first;
    node *last;
};

int menu(void);
void print_menu(void);
void loadtxt(list &list, std::istream &ist);
void insert_node(list &list, node *next, node *n);
void remove_node(list &list, int &num);
void print_list(const list &list, int &order);
void save2file(list &list, std::ostream &ost, int &order);
void pressany(void);

void mytask(list &list);
bool isPerfect(const int &num);
node *searchPerfect(node *list);
int genNum(const int &startNum);

int main()
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);

    srand(time(0));
    list _list {nullptr, nullptr};

    std::ifstream ist;
    std::ofstream ost;
    ist.open(IST);
    ost.open(OST);

    int getmenu = 0;
    do {
        getmenu = menu();
        curs_set(TRUE);
        clear();
        switch (getmenu) {
        case 0: {
            int data;
            printw("Data which will put in node: ");
            attron(COLOR_PAIR(3));
            scanw("%d", &data);
            attroff(COLOR_PAIR(3));
            node *_node = new node {data, nullptr, nullptr};
            insert_node(_list, nullptr, _node);
            break;
            }
        case 1: {
            int num;
            if (_list.first == nullptr and _list.last == nullptr) {
                printw("List is empty, nothing to remove...\n");
            }
            else {
                printw("Number in the list: ");
                scanw("%d", &num);
                remove_node(_list, num);
            }
            break;
        }
        case 2: {
            if (_list.first == nullptr)
                printw("List is empty, nothing to do...\n");
            else {
                int order = true;
                printw("direct(1) or reverse?(0): ");
                attron(COLOR_PAIR(3));
                scanw("%d", &order);
                attroff(COLOR_PAIR(3));
                print_list(_list, order);
            }
            break;
        }

        case 3: {
            loadtxt(_list, ist);
            break;
        }
        case 4: {
            if (_list.first == nullptr)
                printw("List is empty, nothing to do...\n");
            else
            {
                int order = true;
                printw("direct(1) or reverse?(0): ");
                attron(COLOR_PAIR(3));
                scanw("%d", &order);
                attroff(COLOR_PAIR(3));
                save2file(_list, ost, order);
            }
            break;
        }
        case 5: {
            mytask(_list);
            break;
        }
        }
        curs_set(FALSE);
        if (getmenu != -1) pressany();
    } while (getmenu != -1);

    ist.close();
    ost.close();
    endwin();
    return 0;
}

int menu(void)
{
    clear();
    curs_set(FALSE);
    keypad(stdscr, true);
    int menu_count = 7;
    int currmenui = 0;
    char menu[7][30] = {
        " Insert a node into the list",
        " Remove a node from the list",
        " Print the list",
        " Load from file",
        " Save to file",
        " mytask",
        " Quit"
    };
    while (1) {


        for (int i = 0; i < menu_count; i++) {
            attron(COLOR_PAIR(2));
            if (i == currmenui)
                addch('>');
            else
                addch(' ');
            attroff(COLOR_PAIR(2));
            printw("%s\n", menu[i]);
        }

        switch (getch()) {
            case KEY_DOWN:
                if (currmenui < menu_count-1)
                    currmenui++;
            break;
            case KEY_UP:
                if (currmenui > 0)
                    currmenui--;
            break;
            case '\n':
            {
                if (currmenui+1 == menu_count)
                {
                    return -1;
                }
                return currmenui;
            }
        }
        clear();
    }
}

void insert_node(list &list, node *next, node *n) {
    if(list.first == nullptr) {
        list.first = n;
        list.last = n;
    } else if(next == nullptr) {
        list.last->next = n;
        n->prev = list.last;
        list.last = n;
    } else {
        node *prev = next->prev;
        prev->next = n;
        next->prev = n;
        n->prev = prev;
        n->next = next;
    }
}

void remove_node(list &list, int &num) {
    node *curnode = list.first;
    int count = 0;
    while(curnode) {
        if (++count == num) {
            if (curnode->prev == nullptr)
                list.first = curnode->next;
            else
                curnode->prev->next=curnode->next;

            if (curnode->next == nullptr)
                list.last = curnode->prev;
            else
                curnode->next->prev= curnode->prev;
            curnode->prev = nullptr;
            curnode->next = nullptr;
        }
        curnode=curnode->next;
    }
}

void print_list(const list &list, int &order)
{
    attron(COLOR_PAIR(4));
    if (list.first == list.last)
        printw("[%d]\n", list.first->data);
    else
    {
        if (order)
        {
            node *curnode = list.first;
            while (curnode not_eq nullptr)
            {
                if (isPerfect(curnode->data))
                    attron(COLOR_PAIR(6));
                else
                    attron(COLOR_PAIR(4));
                if (curnode->next == nullptr)
                {
                    printw("[%d]\n", curnode->data);
                    break;
                }
                else {
                    printw("[%d]", curnode->data);
                    attron(COLOR_PAIR(5));
                    printw("<->");
                    attron(COLOR_PAIR(4));
                }
                curnode = curnode->next;
            }
        }
        else
        {
            node *curnode = list.last;
            while (1)
            {
                if (isPerfect(curnode->data))
                    attron(COLOR_PAIR(6));
                else
                    attron(COLOR_PAIR(4));
                if (curnode->prev == nullptr)
                {
                    printw("[%d]\n", curnode->data);
                    break;
                }
                else
                {
                    printw("[%d]", curnode->data);
                    attron(COLOR_PAIR(5));
                    printw("<->");
                    attron(COLOR_PAIR(4));

                }
                curnode = curnode->prev;
            }
        }
    }
    attroff(COLOR_PAIR(4));
}

void loadtxt(list &list, std::istream &ist)
{
    int data;
    node *newnode;
    while (ist >> data)
    {
        newnode = new node {data, nullptr, nullptr};
        insert_node(list, nullptr, newnode);
    }
    if (list.first == nullptr)
        printw("Nothing to load");
    else
        printw("List have loaded");
}

void save2file(list &list, std::ostream &ost, int &order) {
    if (order) {
        node *curnode = list.first;
        while (curnode) {
            ost << curnode->data << ' ';
            curnode = curnode->next;
        }
    } else {
        node *curnode = list.last;
        while (1) {
            if (curnode->prev == nullptr)
                break;
            ost << curnode->data << ' ';
            curnode = curnode->prev;
        }
    }
}

void pressany(void) {
    int x,y;
    getyx(stdscr,y,x);
    move(y, 0);
    printw("Press any key...");
    getch();
}

void mytask(list &list) {
    for(auto i = list.first; searchPerfect(i); i = i->next) {
        i = searchPerfect(i);
        for (int j = 0; j < INSERT_LIST_NUM; j++) {
            node *newnode = new node;
            newnode->data = genNum(i->data);
            newnode->next = i->next;
            newnode->prev = i;
            if (i->next != nullptr)
                i->next->prev = newnode;
            i->next = newnode;
            i = newnode;
        }
    }
}

node *searchPerfect(node *list) {
    node *curnode = list;
    while (curnode not_eq nullptr) {
        if(isPerfect(curnode->data)) {
            return curnode;
        }
        curnode = curnode->next;
    }
    return nullptr;
}

bool isPerfect(const int &num) {
    int div = 0;
    if (num not_eq 1) {
        div = 1;
        for (int i = sqrt(num) ; i > 1; i--) { // O(sqrt(n))
            if (num % i == 0) {
                div+=i;
                div+=num/i;
            }
        }
    }
    return !(num-div);
}

int genNum(const int &startNum) {
    return startNum + abs(rand() % 10);
}
