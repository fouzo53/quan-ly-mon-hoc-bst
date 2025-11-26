#include "bst.h"
#include <fstream>
#include <sstream>
#include <iostream> 
#include <string>   
#include <limits>
#include <algorithm> 

string filedata = "lichhoc.txt";
using namespace std;
//ham thuat toan 

//ham chen
Node* InsertNode(Node* root, MonHoc mh) {
    if (root == NULL) return new Node(mh); 
    if (mh.maMon < root->data.maMon)
        root->left = InsertNode(root->left, mh);
    else if (mh.maMon > root->data.maMon)
        root->right = InsertNode(root->right, mh);
    return root;
}

//ham xoa
Node* FindMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}
Node* DeleteNode(Node* root, string maMon, bool& deleted) {
    if (root == NULL) return NULL;
    if (maMon < root->data.maMon) {
        root->left = DeleteNode(root->left, maMon, deleted);
    }
    else if (maMon > root->data.maMon) {
        root->right = DeleteNode(root->right, maMon, deleted);
    }
    else {
        deleted = true;
        if (root->left == NULL && root->right == NULL) {
            delete root; return NULL;
        }
        if (root->left == NULL) {
            Node* temp = root->right; delete root; return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left; delete root; return temp;
        }
        Node* successor = FindMin(root->right);
        root->data = successor->data;
        root->right = DeleteNode(root->right, successor->data.maMon, deleted);
    }
    return root;
}

//ham tim kiem
Node* SearchByMa(Node* root, string maMon) {
    if (root == NULL) return NULL;
    if (maMon == root->data.maMon) return root;
    if (maMon < root->data.maMon) return SearchByMa(root->left, maMon);
    return SearchByMa(root->right, maMon);
}

//ham tim kiem theo ten
void SearchByTen(Node* root, string tenMon, vector<MonHoc>& result) {
    if (root == NULL) return;
    SearchByTen(root->left, tenMon, result);
    if (root->data.tenMon == tenMon) result.push_back(root->data);
    SearchByTen(root->right, tenMon, result);
}

//ham luu file
void SaveNode(Node* root, ofstream& out) {
    if (root == NULL) return;
    SaveNode(root->left, out);
    out << "maMon: " << root->data.maMon << endl;
    out << "tenMon: " << root->data.tenMon << endl;
    out << "thoiGianBatDau: " << root->data.thoiGianBatDau << endl;
    out << "phongHoc: " << root->data.phongHoc << endl;
    out << "thu: " << root->data.thu << endl;
    out << endl;
    SaveNode(root->right, out);
}

//ham in lich
void TraverseInOrder(Node* root) {
    if (root == NULL) return;
    TraverseInOrder(root->left);
    cout << "\n----------------------------------------------------------------------------------------\n";
    cout << "Ma Mon: " << root->data.maMon
         << "    Ten Mon: " << root->data.tenMon
         << "\t" << "    Thoi gian: "
         << root->data.thoiGianBatDau
         << "    Ngay hoc:" << root->data.thu
         << "    Phong: " << root->data.phongHoc << "\n";
    /*cout << "Ten Mon: " << root->data.tenMon << endl;
    cout << "Thoi gian: " << root->data.thoiGianBatDau << " Ngay hoc:" << root->data.thu <<endl;
    cout << "Phong: " << root->data.phongHoc << endl;*/
    TraverseInOrder(root->right);
}

//ham thu thap tat ca mon hoc vao vector (helper function)
void CollectAllMonHoc(Node* root, vector<MonHoc>& list) {
    if (root == NULL) return;
    CollectAllMonHoc(root->left, list);
    list.push_back(root->data);
    CollectAllMonHoc(root->right, list);
}

//ham chen
void BST::Insert(MonHoc mh) {
    root = InsertNode(root, mh);
}

//ham chen voi nhap tu ban phim
void BST::InsertWithInput() {
    LoadFromFile(filedata);
    string line;
    MonHoc mh;
    cout << "NHAP THONG TIN MON HOC MOI\n";
    do {
        cout << "Nhap Ma Mon Hoc: ";
        cin >> mh.maMon;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (SearchByMa(root, mh.maMon) != NULL) {
            cout << "Vui long nhap lai.\n";
        }
        else {
            break;
        }
    } while (true);

    cout << "Nhap Ten Mon Hoc: ";
    getline(cin, mh.tenMon);
    cout << "Nhap Thoi Gian : ";
    getline(cin, mh.thoiGianBatDau);
    cout << "Nhap Phong Hoc: ";
    getline(cin, mh.phongHoc);
    cout << "Nhap Ngay Trong Tuan:";
    getline(cin, mh.thu);
    root = InsertNode(root, mh);
    SaveToFile("lichhoc.txt");
}

//ham tim kiem
Node* BST::SearchMa(string maMon) {
    LoadFromFile(filedata);
    return SearchByMa(root, maMon);
}

//ham tim kiem theo ten
vector<MonHoc> BST::SearchTen(string tenMon) {
    LoadFromFile(filedata);
    vector<MonHoc> result;
    SearchByTen(root, tenMon, result);
    return result;
}

//ham xoa
bool BST::Delete(string maMon) {
    LoadFromFile(filedata);
    bool deleted = false;
    root = DeleteNode(root, maMon, deleted);
    SaveToFile(filedata);
    return deleted;
}

//ham cap nhat
bool BST::Update(string maMon) {
    LoadFromFile(filedata);
    Node* node = SearchMa(maMon);
    if (node == NULL) return false;
    cout << "Nhap ten mon moi: ";
    getline(cin, node->data.tenMon);
    cout << "Nhap thoi gian bat dau moi: ";
    getline(cin, node->data.thoiGianBatDau);
    cout << "Nhap phong hoc moi: ";
    getline(cin, node->data.phongHoc);
    cout << "Nhap thu moi: ";
    getline(cin, node->data.thu);
    SaveToFile(filedata);
    return true;
}

//ham tai file
void BST::LoadFromFile(string filedata) {
    ifstream in(filedata);
    if (!in) {
        cout << "Khong mo duoc file ";
        return;
    }

    string line;
    MonHoc mh;
    int count = 0;

    while (getline(in, line)) {
        if (line.find("maMon: ") == 0) 
            mh.maMon = line.substr(7);
        else if (line.find("tenMon: ") == 0) 
            mh.tenMon = line.substr(8);
        else if (line.find("thoiGianBatDau: ") == 0) 
            mh.thoiGianBatDau = line.substr(16);
        else if (line.find("phongHoc: ") == 0) 
            mh.phongHoc = line.substr(10);
        else if (line.find("thu: ") == 0) 
            mh.thu = line.substr(5);
        else if (line == "") {
            if (!mh.maMon.empty()) {
                Insert(mh);
                count++;
            }
            mh = MonHoc();
        }
    }
    if (!mh.maMon.empty()) {
        Insert(mh);
        count++;
    }

    in.close();
}

//ham luu file
void BST::SaveToFile(string filename) {
    ofstream out(filedata);
    if (!out) {
        cout << " Khong mo dc file  ";
        return;
    }
    SaveNode(root, out);
    out.close();
}

//ham in lich - hien thi sap xep theo ten mon hoc (A-Z)
void BST::inSchedule() {
    LoadFromFile(filedata);
    if (root == NULL) {
        cout << "\nTHOI KHOA BIEU CHUA DC CAP NHAT\n";
        return;
    }
    
    // Thu thap tat ca mon hoc vao vector
    vector<MonHoc> list;
    CollectAllMonHoc(root, list);
    
    // Sap xep theo ten mon (A-Z)
    sort(list.begin(), list.end(), [](const MonHoc& a, const MonHoc& b) {
        return a.tenMon < b.tenMon;
    });

    // In danh sach da sap xep
    cout << "\nTHOI KHOA BIEU (SAP XEP THEO TEN MON A-Z)\n";
    for (const auto& mh : list) {
        cout << "\n----------------------------------------------------------------------------------------\n";
        cout << "Ma Mon: " << mh.maMon << "    Ten Mon: " << mh.tenMon 
             << "\t    Thoi gian: " << mh.thoiGianBatDau 
             << "    Ngay hoc: " << mh.thu 
             << "    Phong: " << mh.phongHoc << endl;
    }
    cout << "----------------------------------------------------------------------------------------\n";
}