#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "plex_Server.h"

#define SERVER_SIZE 50000
using namespace std;

vector<string> play_hist;
splay s;
int count;

//node functions

node::node(const node &t)
{
    title = t.title;
    syn = t.syn;
    genre = t.genre;
    qual = t.qual;
    duration = t.duration;
    frequency = t.frequency;
    size = t.size;
}

void node::cal_size()
{
    if (qual == 144)
        size = duration * 5;
    else if (qual == 240)
        size = duration * 6;
    else if (qual == 360)
        size = duration * 7;
    else if (qual == 480)
        size = duration * 8;
    else if (qual == 720)
        size = duration * 11;
    else if (qual == 1080)
        size = duration * 15;
    else if (qual == 1440)
        size = duration * 21;
    else if (qual == 2160)
        size = duration * 30;
}

void node::get()
{
    char ch;
    scanf("%c", &ch);
    cout << "\n\tEnter title of the movie: ";
    getline(cin, title);
    cout << "\tEnter synopsis: ";
    getline(cin, syn);
    cout << "\tEnter Genre: ";
    getline(cin, genre);
    cout << "\tEnter Quality (144, 240, 360, 480, 720, 1080, 1440, 2160): ";
    cin >> qual;
    cout << "\tEnter duration (minutes): ";
    cin >> duration;
    frequency = 0;
    left = right = NULL;
    cal_size();
}

void node::put()
{
    cout<< "\tTitle : " << title << endl
        << "\tSynopsis: " << syn << endl
        << "\tGenre: " << genre << endl
        << "\tQuality: " << qual << endl
        << "\tDuration (minutes): " << duration << endl
        << "\tSize: " << size << "MB" << endl;
}

//splay functions

splay::splay()
{
    //constructor for the splay tree
    nullnode = new node;
    nullnode->left = nullnode->right = nullnode;
    root = nullnode;
}

splay::~splay()
{
    makeempty(root);
    delete nullnode;
}

void splay::makeempty(node *&t)
{
    if (!t)
        {
            makeempty(t->left);
            makeempty(t->right);
            delete t;
        }
        t = NULL;
}

void splay::rot1l(node *&k)
{ //single rotate with left
    node *kl = k->left;
    k->left = kl->right;
    kl->right = k;
    k = kl;
}

void splay::rot1r(node *&k)
{ //single rotate with right
    node *kr = k->right;
    k->right = kr->left;
    kr->left = k;
    k = kr;
}

void splay::splayt(node *&spnode, node *&t)
{
    node *ltmax, *rtmin;
    static node header;
    header.left = header.right = nullnode;
    ltmax = rtmin = &header;
    nullnode->title = spnode->title;

    while (true)
        if (spnode->title.compare(t->title) < 0)
        {
            if (t->left == nullnode)
                break;
            if (spnode->title.compare(t->left->title) < 0)
                rot1l(t);
            rtmin->left = t;
            rtmin = t;
            t = t->left;
        }

        else if (spnode->title.compare(t->title) > 0)
        {
            if (t->right == nullnode)
                break;
            if (spnode->title.compare(t->right->title) > 0)
                rot1r(t);
            ltmax->right = t;
            ltmax = t;
            t = t->right;
        }
        else
            break;
    ltmax->right = t->left;
    rtmin->left = t->right;
    t->left = header.right;
    t->right = header.left;
}

void splay::splayt(string ti)
{
    node *t = find(ti, root);
    splayt(t, root);
}

void splay::insert(node *nnode)
{
    static node *newnode = NULL;
    if (newnode == NULL)
    {
        newnode = new node(*nnode);
    }
    if (root == nullnode)
    {
        newnode->left = newnode->right = nullnode;
        root = newnode;
    }

    else
    {
        splayt(newnode, root);
        if (newnode->title.compare(root->title) < 0)
        {
            newnode->left = root->left;
            newnode->right = root;
            root->left = nullnode;
            root = newnode;
            //getchar();
        }
        else if (newnode->title.compare(root->title) > 0)
        {
            newnode->left = root;
            newnode->right = root->right;
            root->right = nullnode;
            root = newnode;
            //getchar();
        }
        else
        {
            cout << "\tMOVIE ALREADY EXISTS!!!" << endl
                    << endl;
        }
    }
    newnode = NULL;
}

node* splay::find(string ti, node *t)
{
    if (t == nullnode)
        return NULL;
    if (t->title.compare(ti) > 0)
        return find(ti, t->left);
    else if (t->title.compare(ti) < 0)
        return find(ti, t->right);
    return t;
}

void splay::search(string t)
{
    node *temp = find(t, root);
    if (temp == NULL)
        cout << "\tMOVIE NOT FOUND!!!" << endl;
    else
    {
        cout << "\tFOUND:" << endl;
        temp->put();
        temp->frequency++;
    }
}


void splay::traversal(vector<node> &v)
{
    traversal(v, root);
}

void splay::traversal(vector<node> &v, node *t)
{
    if (t == nullnode)
        return;
    else
    {
        v.push_back(*t);
        traversal(v, t->left);
        traversal(v, t->right);
    }
}

void splay::size_avail_calc(int &size, node *t)
{

    if (t == nullnode)
        return;
    else
    {
        size += t->size;
        size_avail_calc(size, t->left);
        size_avail_calc(size, t->right);
    }
}

void splay::size_avail()
{
    int size = 0;
    size_avail_calc(size, root);
    cout << "\tSIZE AVAILABLE IN SERVER : " << SERVER_SIZE - size << " MB" << endl;
}

void splay::remove(string t)
{
    node *delnode = find(t, root);
    node *newtree;
    node *temp;
    if (root == nullnode || !delnode)
    {
        cout << "\tMOVIE DOESN'T EXIST!!!" << endl
                << endl;
        getchar();
        return;
    }
    splayt(delnode, root);
    if (delnode->title.compare(root->title) != 0)
    {
        cout << "\tMOVIE DOESN'T EXIST!!!" << endl
                << endl;
        getchar();
        return;
    }
    if (root->left == nullnode)
        newtree = root->right;
    else
    {
        newtree = root->left;
        splayt(delnode, newtree);
        newtree->right = root->right;
    }

    delete root;
    root = newtree;
    cout << "\tDELETED " << t << endl;
    getchar();
    for (int i = play_hist.size() - 1; i >= 0; --i)
    {
        temp = find(play_hist.at(i), root);
        if (temp)
        {
            splayt(temp->title);
            break;
        }
    }
}

void splay::print(node *t) const
{
    if (t != nullnode)
    {
        cout << endl
                << "\tDETAILS:" << endl;
        t->put();
        print(t->left);
        print(t->right);
    }
}

void splay::display() const
{
    if (root != nullnode)
    {
        cout << "\tThe movies in the server: " << endl;
        print(root);
        cout << endl;
    }
    else
        cout << "\tSERVER IS EMPTY!!!" << endl;
}

void splay::play(string title)
{
    node *p = find(title, root);
    if (!p)
        cout << "\tMOVIE NOT FOUND!!!" << endl;
    else
    {
        play_hist.push_back(p->title);
        splayt(p, root);
        cout << endl
                << endl;
        p->put();
        cout << endl
                << "\tPLAYING NOW, ENJOY YOUR SHOW" << endl;
    }
}

void splay::lastplayed()
{
    node *temp;
    for (int i = play_hist.size() - 1; i >= 0; --i)
    {
        temp = find(play_hist.at(i), root);
        if (temp)
        {
            cout << "\tMOVIE LAST PLAYED:" << endl;
            temp->put();
            return;
        }
    }
    cout << "\tNO MOVIE WAS LAST PLAYED";
}

void splay::playhistory()
{
    if (play_hist.size() == 0)
    {
        cout << "\tNO MOVIES IN PLAY HISTORY" << endl;
        return;
    }
    cout << "\t----PLAY HISTORY----" << endl;
    for (int i = play_hist.size() - 1; i >= 0; --i)
        cout << "\t" << play_hist.at(i) << endl;
}

void splay::freq_searched(string &ti, int &f, node *t)
{
    if (t == nullnode)
        return;
    else if (f < t->frequency)
    {
        ti = t->title;
        f = t->frequency;
        freq_searched(ti, f, t->left);
        freq_searched(ti, f, t->right);
    }
}

void splay::freq_searched()
{

    int f = 0;
    string t = "NULL";
    freq_searched(t, f, root);
    node *temp = find(t, root);
    if (temp == NULL)
    {
        cout << "\tNO MOVIE IN THE SERVER WAS SEARCHED" << endl;
        getchar();
        return;
    }
    cout << "\tMOST FREQUENTLY SEARCHED MOVIE:" << endl;
    temp->put();
    cout << "\tPLAY? y/n : " << endl;
    char c;
    cin >> c;
    if (c == 'y')
        play(temp->title);
}

    bool flag = false;
void splay::genre_find(string t)
{
    genre_find(root, t);
    if (!flag)
    {
        cout << endl
                << "\tNO MOVIES IN " << t << " GENRE" << endl;
    }
}

void splay::genre_find(node *t, string s)
{
    if (t != nullnode && t->genre.compare(s) == 0)
    {
        cout << endl
                << "\tDETAILS:" << endl;
        t->put();
        flag = true;
        genre_find(t->left, s);
        genre_find(t->right, s);
    }
}

//file function definitions

void unload_playhistory()
{
    ofstream f("playhistory.txt");
    for (int i = 0; i < play_hist.size(); ++i)
    {
        f.write(play_hist.at(i).c_str(), sizeof(char) * play_hist.at(i).size());
        f << '\n';
    }
    f.close();
}

void load_playhistory()
{
    char ch;
    ifstream f("playhistory.txt");
    string str;
    play_hist.clear();
    for (ch; f.read((char *)&ch, sizeof(ch));)
    {
        if (ch != '\n')
            str += ch;
        else
        {
            play_hist.push_back(str);
            str.clear();
        }
    }
    f.close();
}

void write_data(node temp, bool flag)
{
    //write into file from node
    //flag = true open mode ios::out, i.e , file is erased
    //flag = false open mode iso::app, added to the end
    ofstream f;
    if (flag)
        f.open("movies.txt");
    else
        f.open("movies.txt", ios::app);
    f.write(temp.title.c_str(), sizeof(char) * temp.title.size());
    f << "\n";
    f.write(temp.syn.c_str(), sizeof(char) * temp.syn.size());
    f << "\n";
    f.write(temp.genre.c_str(), sizeof(char) * temp.genre.size());
    f << "\n";
    f.write((char *)&temp.qual, sizeof(temp.qual));
    f.write((char *)&temp.duration, sizeof(temp.duration));
    f.write((char *)&temp.frequency, sizeof(temp.frequency));
    f.write((char *)&temp.size, sizeof(temp.size));
    f.close();
}

void read_data(node &temp)
{
    //write into node from file
    static ifstream fr("movies.txt");
    char ch;
    temp.title.clear();
    temp.syn.clear();
    temp.genre.clear();
    while (fr.read((char *)&ch, sizeof(ch)))
    {
        if (ch == '\n')
            break;
        temp.title += ch;
    }
    while (fr.read((char *)&ch, sizeof(ch)))
    {
        if (ch == '\n')
            break;
        temp.syn += ch;
    }
    while (fr.read((char *)&ch, sizeof(ch)))
    {
        if (ch == '\n')
            break;
        temp.genre += ch;
    }

    fr.read((char *)&temp.qual, sizeof(int));
    fr.read((char *)&temp.duration, sizeof(int));
    fr.read((char *)&temp.frequency, sizeof(int));
    fr.read((char *)&temp.size, sizeof(float));
}

void load_data()
{
    node *root;
    load_playhistory();
    ifstream f("server.txt");
    f.read((char *)&count, sizeof(int));
    f.close();
    node temp[count];
    for (int i = 0; i < count; ++i)
    {
        read_data(temp[i]);
        if (i == 0)
            root = &temp[i];
        s.insert(&temp[i]);
    }
    if (count == 0)
        return;
    s.splayt(root->title);
}

void unload_data()
{
    vector<node> list;
    ofstream f("server.txt");
    f.write((char *)&count, sizeof(count));
    f.close();
    s.traversal(list);
    for (int i = 0; i < list.size(); ++i)
        if (i == 0)
            write_data(list.at(i), true);
        else
            write_data(list.at(i), false);
    unload_playhistory();
}