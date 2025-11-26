#include "bst.h"
#include <iostream>
#include <limits> 

using namespace std;

void inMonHoc(const MonHoc& mh) {
    cout << "\n------------------------\n";
    cout << "Ma Mon: " << mh.maMon << "\n";
    cout << "Ten Mon: " << mh.tenMon << "\n";
    cout << "Thoi Gian Bat Dau: " << mh.thoiGianBatDau << "\n";
    cout << "Phong Hoc: " << mh.phongHoc << "\n";
    cout << "Thu: " << mh.thu << "\n";
    cout << "------------------------\n";

}

int DisplayMenu() {
    int choice;
    cout << "\n====================================================\n";
    cout << "         HE THONG LICH HOC VA THOI KHOA BIEU\n";
    cout << "====================================================\n";
    cout << "1. Them mon hoc moi vao lich hoc\n";
    cout << "2. Tim kiem mon hoc theo ma mon\n";
    cout << "3. Tim kiem mon hoc theo ten mon\n";
    cout << "4. Cap nhat thong tin mon hoc\n";
    cout << "5. Xoa mon hoc khoi lich hoc\n";
    cout << "6. Hien thi thoi khoa bieu (A-Z)\n";
    cout << "7. Hien thi thoi khoa bieu (theo thoi gian bat dau)\n";
    cout << "0. Thoat\n";
    cout << "----------------------------------------------------\n";
    cout << "Nhap lua chon cua ban: ";

    while (!(cin >> choice)) {
        cout << "Vui long nhap lai\n ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return choice;
}

int main() {
    BST lichHoc;
    lichHoc.Init();
    int choice;
    string searchKey;

    do {
        choice = DisplayMenu();

        switch (choice) {
        case 1: {
            lichHoc.InsertWithInput();
            break;
        }
		case 2: { 
            cout <<"Nhap Ma Mon can tim: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchKey);
            Node* result = lichHoc.SearchMa(searchKey);
            if (result) 
                inMonHoc(result->data);
            else
                cout << " Khong tim thay mon hoc ";
            break;
        }
		case 3: { 
            cout << "Nhap Ten Mon can tim: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchKey);
            vector<MonHoc> results = lichHoc.SearchTen(searchKey);
            if (!results.empty()) {
                for (const auto& mh : results) {
                    inMonHoc(mh);
                }
            }
            else {
                cout << " Khong tim thay mon hoc ";
            }
            break;
        }
        case 4: { 
            cout << "Nhap Ma Mon can cap nhat: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchKey);

            if (lichHoc.Update(searchKey)) {
                cout << "Da update thanh cong " ;
            }
            else {
                cout << "Khong tim thay mon hoc ";
            }
            break;
        }
        case 5: { 
            cout << "Nhap Ma Mon can xoa: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, searchKey);
            if (lichHoc.Delete(searchKey)) {
                cout << " Da xoa mon hoc";
            }
            else {
                cout << " Khong tim thay Ma Mon";
            }
            break;
        }
        case 6: { 
            lichHoc.inSchedule();
            break;
        }
        case 0: {
            break;
        }
        default: {
            cout << "\nVui long chon lai\n";
            break;
        }
        }
    } while (choice != 0);

    return 0;
}