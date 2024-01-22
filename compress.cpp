// compress.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;
//list of substrings
struct ranges {
    //beginning index of substring
    int begin;
    //last index of substring
    int end;
    //true if this object is the end of the list
    bool isLast = true;
    //if isLast is false, the next substring of the list
    ranges* next;
};

struct node {
    //true if this node has a 0 branch
    bool has0 = false;
    //if has0 is true, branch 0
    node* _0;
    //true is this node has a 1 branch
    bool has1 = false;
    //if has1 is true, branch 1
    node* _1;
    //true if node contains substrings
    bool referenced = false;
    //all substrings
    ranges* refs;
};
/*/copies a range structure
ranges* rgCpy(ranges* r) {
    if (r->isLast) {
        ranges* res = new ranges;
        res->begin = r->begin;
        res->end = r->end;
        res->isLast = true;
        return res;
    }
    else {
        ranges* res = new ranges;
        res->begin = r->begin;
        res->end = r->end;
        res->isLast = false;
        res->next = rgCpy(r->next);
        return res;
    }
}*/
//update rest of binary search tree
void update(int x, node* it, bool* bDataIn) {
    if (it->referenced) {
        //iterates through all substrings in node
        ranges* tst = it->refs;
        while (true) {
            if (tst->end < sizeof(bDataIn)) {
                if (bDataIn[tst->end + 1] == bDataIn[x]) {
                    if (bDataIn[x]) {
                        if (it->has1) {
                            ranges* nx = new ranges;
                            nx->begin = tst->begin;
                            nx->end = tst->end + 1;
                            nx->isLast = false;
                            nx->next = tst->next;
                            it->_1->refs->next = nx;
                        }
                        else {
                            ranges* nx = new ranges;
                            nx->begin = tst->begin;
                            nx->end = tst->end + 1;
                            nx->isLast = true;
                            nx->next = tst->next;
                            it->_1->refs->next = nx;
                        }
                    }
                }
                else {
                    if (bDataIn[x]) {
                        if (it->has0) {
                            ranges* nx = new ranges;
                            nx->begin = tst->begin;
                            nx->end = tst->end + 1;
                            nx->isLast = false;
                            nx->next = tst->next;
                            it->_1->refs->next = nx;
                        }
                        else {
                            ranges* nx = new ranges;
                            nx->begin = tst->begin;
                            nx->end = tst->end + 1;
                            nx->isLast = true;
                            nx->next = tst->next;
                            it->_0->refs->next = nx;
                        }
                    }
                }
            }
            if (tst->isLast) {
                break;
            }
            else {
                tst = tst->next;
            }
        }
    }
    if (it->has0) {
        update(x, it->_0, bDataIn);
    }
    if (it->has1) {
        update(x, it->_1, bDataIn);
    }
}
//append next bit to binary search tree
void app(int x, node* m, bool* bDataIn) {
    if (bDataIn[x]) {
        if (m->has1) {
            //appended to front of substring list
            ranges* nx = new ranges;
            nx->begin = x;
            nx->end = x;
            nx->isLast = false;
            nx->next = m->refs;
            m->refs = nx;
        }
        else {
            m->referenced = true;
            ranges* nr = new ranges;
            nr->begin = x;
            nr->end = x;
            m->refs = nr;
        }
    }
    else {
        if (m->has0) {
            //appended to front of substring list
            ranges* nx = new ranges;
            nx->begin = x;
            nx->end = x;
            nx->isLast = false;
            nx->next = m->refs;
            m->refs = nx;
        }
        else {
            m->referenced = true;
            ranges* nr = new ranges;
            nr->begin = x;
            nr->end = x;
            m->refs = nr;
        }
    }
    update(x, m, bDataIn);
}
//get length of ranges
int rangesLen(ranges* r) {
    if (r->isLast) {
        return 1;
    }
    else {
        return rangesLen(r->next) + 1;
    }
}
//get size of compressed item
int size(node* t, bool* bDataIn) {
    
}

int main()
{
    std::cout << "Hello World!\n";
    std::wifstream t("file.txt");
    std::wstringstream buffer;
    buffer << t.rdbuf();
    wstring cont = buffer.str();
    wchar_t* dataIn = const_cast<wchar_t*>(cont.c_str());
    bool* bDataIn=new bool[cont.length()*16];
    for (int i = 0;i < cont.length();i++) {
        for (int j = 0;j < 16;j++) {
            bDataIn[i * 16 + j] = (dataIn[i] << j) % 2;
        }
    }
    //top of binary search tree
    node* top = new node;
    for (int i = 0;i < cont.length() * 16;i++) {
        app(i, top, bDataIn);
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
