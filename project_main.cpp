#include <iostream>
#include "plex_Server.h"
#include <stdlib.h>

using namespace std;

void menu4();

int main()
{
    string ip;
    char c;
    int choice;
    load_data();
    do
    {
        //system("clear");
        cout << "\n\t\t\t\t\t\t\tPLEX MEDIA SERVER INTERFACE" << endl
             << "\t1.  PLAY A MOVIE" << endl
             << "\t2.  SEARCH A MOVIE" << endl
             << "\t3.  LIST ALL MOVIES" << endl
             << "\t4.  EDIT SERVER" << endl
             << "\t5.  MOST FREQUENTLY SEARCHED MOVIE" << endl
             << "\t6.  PLAY HISTORY" << endl
             << "\t7.  LAST PLAYED" << endl
             << "\t8.  SERVER DETAILS" << endl
             << "\t9.  LIST MOVIES OF SAME GENRE" << endl
             << "\t10. EXIT" << endl
             << "\tENTER YOUR CHOICE: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\n\tENTER MOVIE TO PLAY: ";
            scanf("%c", &c);
            getline(cin, ip);
            s.play(ip);
            getchar();
            break;

        case 2:
            cout << "\n\tENTER MOVIE NAME TO SEARCH: ";
            scanf("%c", &c);
            getline(cin, ip);
            s.search(ip);
            getchar();
            break;
        case 3:
            s.display();
            getchar();
            getchar();
            break;

        case 4:
            menu4();
            break;
        case 5:
            s.freq_searched();
            getchar();
            break;
        case 6:
            s.playhistory();
            getchar();
            getchar();
            break;
        case 7:
            s.lastplayed();
            getchar();
            getchar();
            break;
        case 8:
            cout << "\n\tNUMBER OF MOVIES: " << count << endl
                 << "\tTOTAL SERVER SIZE: " << SERVER_SIZE << " MB" << endl;
            s.size_avail();
            getchar();
            getchar();
            break;
        case 9:
            cout << "\n\tENTER GENRE: ";
            scanf("%c", &c);
            getline(cin, ip);
            s.genre_find(ip);
            getchar();
            break;
        case 10:
            cout << "\n\tEXITTING.." << endl;
            unload_data();
            return 0;
        default:
            cout << "\tENTER CORRECT CHOICE" << endl;
            getchar();
            break;
        }
    } while (true);
}

void menu4()
{
    string pass;
    char c;
    static node *temp = new node;
    static string title;
    int choice1;
    cout << "\nENTER ADMIN PASSWORD: ";
    scanf("%c", &c);
    getline(cin, pass);
    if (pass == "password")
    {
        do
        {
            //system("clear");
            cout << "\tSERVER EDIT MENU: " << endl
                 << "\t1. UPLOAD A MOVIE" << endl
                 << "\t2. DELETE A MOVIE" << endl
                 << "\t3. BACK" << endl
                 << "\tENTER YOUR CHOICE: ";
            cin >> choice1;
            switch (choice1)
            {
            case 1:
                cout << "\tENTER DETAILS:" << endl;
                temp->get();
                s.insert(temp);
                count++;
                break;
            case 2:
                scanf("%c", &c);
                cout << "\tENTER TITLE OF THE MOVIE: ";
                getline(cin, title);
                s.remove(title);
                count--;
                break;
            case 3:
                return;
            default:
                cout << "\tENTER CORRECT CHOICE" << endl;
                getchar();
                break;
            }
        } while (true);
    }
}