#ifndef bst_h
#define bst_h
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;
struct MonHoc {
    string maMon;          // khóa chính
    string tenMon;         // tên hiển thị
    string thoiGianBatDau; // định dạng hh:mm - hh:mm
    string phongHoc;       // địa điểm
    string thu;            // ngày học trong tuần

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

    Node(const MonHoc &mh) {
        data = mh;
        left = NULL;
        right = NULL;
    }
};

Node* InsertNode(Node* root, const MonHoc &mh);
Node* FindMin(Node* root);
Node* DeleteNode(Node* root, string maMon, bool& deleted);
Node* SearchByMa(Node* root, string maMon);
void SearchByTen(Node* root, string tenMon, vector<MonHoc>& result);
void SaveNode(Node* root, ofstream& out);
void CollectAllNodes(Node* root, vector<MonHoc>& list);
void hienThiMonHoc(MonHoc mh);
// void Traverse(Node* root);

// Forward declare BST for isTimeConflict
struct BST;

// Declarations of validation functions
bool validateMaMon(string maMon);
bool validateTenMon(string tenMon);
bool validateThoiGian(string thoiGian);
bool isTimeConflict(BST& tree, const string& newTimeStr, const string& newThu);
bool validateThu(string thu);
bool validatePhongHoc(string phong);

struct BST {
    Node* root;
    BST() : root(NULL) {}
    ~BST();
    void deleteTree(Node* node);
    void Init() { root = NULL; }
    bool IsEmpty() { return root == NULL; }
    void Insert(const MonHoc &mh);
    void InsertWithInput();
    Node* SearchMa(string maMon);
    vector<MonHoc> SearchTen(string tenMon);
    bool Update(string maMon);
    bool Delete(string maMon);
    void LoadFromFile(string filename);
    void SaveToFile(string filename);
    void inSchedule();
    void inScheduleByTime();
};
#endif
