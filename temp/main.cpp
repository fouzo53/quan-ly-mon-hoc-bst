#include "bst.h"
#include <iostream>
#include <vector>
#include <limits>
#include <regex>
#include <sstream>
using namespace std;

void hienThiMonHoc(MonHoc mh) {
    cout << "\n" << mh.maMon << " | " << mh.tenMon << " | "
         << mh.thoiGianBatDau << " | " << mh.phongHoc << " | "
         << mh.thu << "\n";
}
void printMenu() {
    cout << "\n========== HE THONG LICH HOC VA THOI KHOA BIEU ==========\n\n";
    cout << "1. Them mon hoc moi vao lich hoc\n";
    cout << "2. Tim kiem mon hoc (theo ma mon hoc)\n";
    cout << "3. Tim kiem mon hoc (theo ten mon hoc)\n";
    cout << "4. Cap nhat thong tin mon hoc\n";
    cout << "5. Xoa mon hoc khoi lich hoc\n";
    cout << "6. Hien thi thoi khoa bieu (theo ten mon hoc)\n";
    cout << "7. Hien thi thoi khoa bieu (theo thoi gian bat dau)\n";
    cout << "0. Thoat chuong trinh\n\n";
    cout << "Lua chon cua ban: ";
}

int main() {
    BST tree;
    tree.LoadFromFile("lichhoc.txt");
    int choice;

    do {
        printMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                tree.InsertWithInput();
                break;

            case 2:
                {
                    string ma;
                    cout << "Nhap ma mon can tim: ";
                    cin >> ma;
                    cin.ignore();
                    Node* res = tree.SearchMa(ma);
                    if (res) hienThiMonHoc(res->data);
                    else cout << "\nKhong tim thay mon hoc.\n";
                }
                break;

            case 3:
                {
                    string ten;
                    cout << "Nhap ten mon can tim: ";
                    getline(cin, ten);
                    vector<MonHoc> res = tree.SearchTen(ten);
                    if (res.empty()) cout << "\nKhong tim thay mon hoc.\n";
                    else
                        for (auto mh : res) hienThiMonHoc(mh);
                }
                break;

            case 4:
                {
                    string ma;
                    cout << "Nhap ma mon can cap nhat: ";
                    getline(cin, ma);
                    if (tree.Update(ma)) cout << "Cap nhat thanh cong.\n";
                    else cout << "\nKhong tim thay mon hoc.\n";
                }
                break;

            case 5:
                {
                    string ma;
                    cout << "Nhap ma mon can xoa: ";
                    cin >> ma;
                    cin.ignore();
                    if (tree.Delete(ma)) cout << "\nXoa thanh cong.\n";
                    else cout << "\nXoa khong thanh cong.\n";
                }
                break;

            case 6:
                tree.inSchedule();
                break;

            case 7:
                tree.inScheduleByTime();
                break;

            case 0:
                cout << "\nThoat chuong trinh.\n\n";
                break;

            default:
                cout << "\nLua chon khong hop le.\n";
        }

    } while (choice != 0);

    return 0;
}
