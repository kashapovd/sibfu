#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>

void pressany(void);
int menu(void);

int exec_cmd();
int exec_script();
int print_terms();

int main() {
    int getmenu = 0;
    int ret = 0;
    do {
        getmenu = menu();
        curs_set(TRUE);
        clear();
        switch (getmenu) {
        case 0:
            ret = exec_cmd();
            break;
        case 1:
            ret = exec_script();
            break;
        case 2:
            ret = print_terms();
            break;
        }
        curs_set(FALSE);
        if (ret == -1)
                printw("Fork was corrupted");
        if (getmenu != -1) pressany();
    } while (getmenu != -1);

    endwin();
    return 0;
}

int exec_cmd() {
    printw("Enter the command to execute: ");
    char command[256];
    attron(COLOR_PAIR(3));
    scanw("%255[^\n]", command);
    attroff(COLOR_PAIR(3));
    int ret = fork();
    if(ret == 0) {
        execl("/bin/sh","sh","-c",command, (char *)NULL);
    }
    return ret;
}

int exec_script() {
    printw("Script path: ");
    char script[256];
    attron(COLOR_PAIR(3));
    scanw("%s", script);
    attroff(COLOR_PAIR(3));
    printw("User time: ");
    uint utime[10];
    attron(COLOR_PAIR(5));
    scanw("%d", utime);
    attroff(COLOR_PAIR(5));
    printw("Output file path: ");
    uint file[256];
    attron(COLOR_PAIR(2));
    scanw("%s", file);
    attroff(COLOR_PAIR(2));
    printw(script);
    int ret = fork();
    if(ret == 0) {
        execl("/bin/sh", "sh", script, utime, file, (char *)NULL);
    }
    return ret;
}

int print_terms() {
    int ret = fork();
    if(ret == 0) {
        execlp("ps", "ps", "ah", "-o", "tty", (char *)NULL);
        return 0;
    }
    return ret;
}

int menu(void)
{
    initscr();
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_BLACK, COLOR_YELLOW);
    clear();
    curs_set(FALSE);
    keypad(stdscr, true);
    int menu_count = 4;
    int currmenui = 0;
    char menu[4][40] = {
        " Execute command",
        " Execute shell script from work1",
        " Print user's terminals",
        " Quit"
    };
    while (1) {


        for (int i = 0; i < menu_count; i++) {
            attron(COLOR_PAIR(4));
            if (i == currmenui)
                addch('>');
            else
                addch(' ');
            attroff(COLOR_PAIR(4));
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

void pressany() {
    int x,y;
    getyx(stdscr,y,x);
    move(y, 0);
    getch();
}
