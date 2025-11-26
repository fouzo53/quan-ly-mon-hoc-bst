#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <vector> 
#include <fstream> 

using namespace std;
struct MonHoc {
    string maMon;
    string tenMon;
    string thoiGianBatDau;
    string phongHoc;
    string thu;

    MonHoc() {}
    MonHoc(string ma, string ten, string tg, string phong, string th) {
        maMon = ma;
        tenMon = ten;
        thoiGianBatDau = tg;
        phongHoc = phong;
        thu = th;
    }
};

struct Node {
    MonHoc data;
    Node* left;
    Node* right;

    Node(MonHoc mh) {
        data = mh;
        left = NULL;
        right = NULL;
    }
};

Node* InsertNode(Node* root, MonHoc mh);
Node* FindMin(Node* root);
Node* DeleteNode(Node* root, string maMon, bool& deleted);
Node* SearchByMa(Node* root, string maMon);
void SearchByTen(Node* root, string tenMon, vector<MonHoc>& result);
void SaveNode(Node* root, ofstream& out);
void TraverseInOrder(Node* root);
void CollectAllMonHoc(Node* root, vector<MonHoc>& list);  // Helper function: thu thap tat ca mon hoc vao vector 

struct BST {
    Node* root;
    BST() : root(NULL) {}
    void Init() { root = NULL; }
    bool IsEmpty() { return root == NULL; }
    void Insert(MonHoc mh);      
    void InsertWithInput();       
    Node* SearchMa(string maMon);
    vector<MonHoc> SearchTen(string tenMon);
    bool Update(string maMon);
    bool Delete(string maMon);
    void LoadFromFile(string filename);
    void SaveToFile(string filename);
    void inSchedule();
};
#endif 