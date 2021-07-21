#include <iostream>
#include <string>
#include <vector>

#define SERVER_SIZE 50000
using namespace std;

struct node
{
    string title, syn, genre;
    int qual, duration, frequency;
    node *left, *right;
    float size;

    node(const string &t = "NULL", const string &s = "NULL", const string &g = "NULL",
         const int &q = -1, const int &d = -1, const int &f = 0, const float &si = 0,
         node *l = NULL, node *r = NULL): title(t), syn(s), genre(g),
                                           qual(q), duration(d), frequency(f), size(si), left(l), right(r)
    {
        if (duration != -1 && qual != -1)
            cal_size();
    }

    node(const node &t);
    void cal_size();
    void get();
    void put();

};

class splay
{
    node *root, *nullnode;

public:

    splay();
    ~splay();
    void rot1l(node *&k);
    void rot1r(node *&k);
    void makeempty(node *&t);
    void splayt(node *&spnode, node *&t);
    void splayt(string ti);
    void insert(node *nnode);
    node *find(string ti, node *t);
    void search(string t);
    void traversal(vector<node> &v);
    void traversal(vector<node> &v, node *t);
    void size_avail_calc(int &size, node *t);
    void size_avail();
    void remove(string t);
    void print(node *t) const;
    void display() const;
    void play(string title);
    void lastplayed();
    void playhistory();
    void freq_searched(string &ti, int &f, node *t);
    void freq_searched();
    bool flag = false;
    void genre_find(string t);
    void genre_find(node *t, string s);
};

extern vector<string> play_hist;
extern splay s;
extern int count;

//file function prototypes

void unload_playhistory();
void load_playhistory();
void write_data(node temp, bool flag);
void read_data(node &temp);
void load_data();
void unload_data();