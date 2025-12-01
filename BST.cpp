#include "bst.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
#include <map>
#include <regex>

using namespace std;

string filedata = "lichhoc.txt";

// ==================== CÁC HÀM XỬ LÝ ĐỊNH DẠNG ====================
bool validateMaMon(string maMon) {
    regex pattern("^[A-Za-z0-9]+$"); // chỉ chứa chữ và số
    return !maMon.empty() && regex_match(maMon, pattern);
}

bool validateTenMon(string tenMon) {
    return !tenMon.empty() && tenMon.length() <= 50;
}

int timeToMinutes(const string& timeStr) {
    int hours = 0, minutes = 0;
    char colon = ' ';
    stringstream ss(timeStr);
    ss >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

bool validateThoiGian(string thoiGian) {
    // giải thích:
    // ^ và $ để đảm bảo khớp toàn bộ chuỗi
    // HH:MM - HH:MM với HH từ 00 -> 23 và MM từ 00 -> 59
    // ví dụ hợp lệ: 08:00 - 10:30
    regex pattern("^([01]?[0-9]|2[0-3]):([0-5][0-9]) - ([01]?[0-9]|2[0-3]):([0-5][0-9])$");
    if (!regex_match(thoiGian, pattern)) {
        cout << "Dinh dang thoi gian phai la HH:MM - HH:MM.\n";
        return false;
    }

    size_t dashPos = thoiGian.find(" - ");
    string startTimeStr = thoiGian.substr(0, dashPos);
    string endTimeStr = thoiGian.substr(dashPos + 3);

    if (timeToMinutes(startTimeStr) >= timeToMinutes(endTimeStr)) {
        cout << "Thoi gian bat dau phai som hon thoi gian ket thuc.\n";
        return false;
    }
    return true;
}

bool isTimeConflict(BST& tree, const string& newTimeStr, const string& newThu) {
    size_t dashPos = newTimeStr.find(" - ");
    string newStartTimeStr = newTimeStr.substr(0, dashPos);
    string newEndTimeStr = newTimeStr.substr(dashPos + 3);
    int newStartMinutes = timeToMinutes(newStartTimeStr);
    int newEndMinutes = timeToMinutes(newEndTimeStr);

    vector<MonHoc> allCourses;
    if (tree.root) {
        CollectAllNodes(tree.root, allCourses);
    }

    for (const auto& existingMh : allCourses) {
        if (existingMh.thu == newThu) {
            size_t existingDashPos = existingMh.thoiGianBatDau.find(" - ");
            if (existingDashPos == string::npos) continue;

            string existingStartTimeStr = existingMh.thoiGianBatDau.substr(0, existingDashPos);
            string existingEndTimeStr = existingMh.thoiGianBatDau.substr(existingDashPos + 3);
            int existingStartMinutes = timeToMinutes(existingStartTimeStr);
            int existingEndMinutes = timeToMinutes(existingEndTimeStr);

            if (newStartMinutes < existingEndMinutes && newEndMinutes > existingStartMinutes) {
                cout << "Bi trung lich voi mon: " << existingMh.maMon << " - " << existingMh.tenMon;
                cout << "Thoi gian bi trung: " << existingMh.thoiGianBatDau << "\n";
                return true;
            }
        }
    }
    return false;
}

// Helper functions
int getThuOrder(string thu) {
    // giải thích:
    // chuyển chuỗi về chữ thường để so sánh
    // trả về thứ tự tương ứng
    // Chu nhat = 1, Thu 2 = 2, ..., Thu 7 = 7
    // nếu không hợp lệ trả về 0
    // ví dụ: "Thu 2" -> 2, "chu nhat" -> 1
    string thuLower = thu;
    transform(thuLower.begin(), thuLower.end(), thuLower.begin(), ::tolower);

    if (thuLower.find("chu nhat") != string::npos || thuLower.find("chủ nhật") != string::npos) return 1;
    if (thuLower.find("2") != string::npos) return 2;
    if (thuLower.find("3") != string::npos) return 3;
    if (thuLower.find("4") != string::npos) return 4;
    if (thuLower.find("5") != string::npos) return 5;
    if (thuLower.find("6") != string::npos) return 6;
    if (thuLower.find("7") != string::npos) return 7;
    return 0;
}

bool validateThu(string thu) {
    vector<string> validThu = { "Thu 2","Thu 3","Thu 4","Thu 5","Thu 6","Thu 7","Chu nhat",
                                "thu 2","thu 3","thu 4","thu 5","thu 6","thu 7","chu nhat",
                                "Thứ 2","Thứ 3","Thứ 4","Thứ 5","Thứ 6","Thứ 7","Chủ nhật",
                                "thứ 2","thứ 3","thứ 4","thứ 5","thứ 6","thứ 7","chủ nhật",
                                "2"    ,"3"    , "4"   ,"5"    ,"6"    ,"7"    ,"1"};
    for (auto t : validThu)
        if (t == thu) return true;
    return false;
}

bool validatePhongHoc(string phong) {
    return !phong.empty();
}

string formatThu(string thu) {
    string thuLower = thu;
    transform(thuLower.begin(), thuLower.end(), thuLower.begin(), ::tolower);

    if (thuLower == "chu nhat" || thuLower == "chủ nhật" || thuLower == "1") return "Chu nhat";
    if (thuLower == "thu 2" || thuLower == "thứ 2" || thuLower == "2") return "Thu 2";
    if (thuLower == "thu 3" || thuLower == "thứ 3" || thuLower == "3") return "Thu 3";
    if (thuLower == "thu 4" || thuLower == "thứ 4" || thuLower == "4") return "Thu 4";
    if (thuLower == "thu 5" || thuLower == "thứ 5" || thuLower == "5") return "Thu 5";
    if (thuLower == "thu 6" || thuLower == "thứ 6" || thuLower == "6") return "Thu 6";
    if (thuLower == "thu 7" || thuLower == "thứ 7" || thuLower == "7") return "Thu 7";
    
    return thu; 
}

string parseStartTime(string thoiGian) {
    // Nếu có dạng "00:00 - 24:59", lấy phần đầu "00:00"
    size_t dashPos = thoiGian.find(" - ");
    if (dashPos != string::npos) {
        return thoiGian.substr(0, dashPos);
    }
    // Nếu chỉ có phần đầu "00:00", trả về như cũ
    return thoiGian;
}

// ==================== CÁC HÀM THUẬT TOÁN BST ====================
Node* InsertNode(Node* root, const MonHoc &mh) {
    if (root == NULL) return new Node(mh);
    if (mh.maMon < root->data.maMon)
        root->left = InsertNode(root->left, mh);
    else if (mh.maMon > root->data.maMon)
        root->right = InsertNode(root->right, mh);
    return root;
}

Node* FindMin(Node* root) {
    while (root->left != NULL) root = root->left;
    return root;
}

Node* DeleteNode(Node* root, string maMon, bool& deleted) {
    if (root == NULL) return NULL;
    if (maMon < root->data.maMon) 
        root->left = DeleteNode(root->left, maMon, deleted);
    else if (maMon > root->data.maMon) 
        root->right = DeleteNode(root->right, maMon, deleted);
    else {
        deleted = true;
        if (root->left == NULL && root->right == NULL) {
            delete root;
            return NULL;
        }
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        }
        if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        Node* successor = FindMin(root->right);
        root->data = successor->data;
        root->right = DeleteNode(root->right, successor->data.maMon, deleted);
    }
    return root;
}

Node* SearchByMa(Node* root, string maMon) {
    if (root == NULL) return NULL;
    if (maMon == root->data.maMon) return root;
    if (maMon < root->data.maMon) return SearchByMa(root->left, maMon);
    return SearchByMa(root->right, maMon);
}

void SearchByTen(Node* root, string tenMon, vector<MonHoc>& result) {
    if (root == NULL) return;
    SearchByTen(root->left, tenMon, result);
    if (root->data.tenMon == tenMon) result.push_back(root->data);
    SearchByTen(root->right, tenMon, result);
}

void SaveNode(Node* root, ofstream& out) {
    if (root == NULL) return;
    out << "maMon: " << root->data.maMon << "\n";
    out << "tenMon: " << root->data.tenMon << "\n";
    out << "thoiGianBatDau: " << root->data.thoiGianBatDau << "\n";
    out << "phongHoc: " << root->data.phongHoc << "\n";
    out << "thu: " << root->data.thu << "\n";
    out << "\n";
    SaveNode(root->left, out);
    SaveNode(root->right, out);
}

// hàm in ra thông tin môn học (hiện tại hàm này không dùng đến)
// void inMonHoc(MonHoc mh) {
//     cout << "Ma: " << mh.maMon << " | "
//          << "Ten: " << mh.tenMon << " | "
//          << "Gio: " << mh.thoiGianBatDau << " (" << mh.thu << ") | "
//          << "Phong: " << mh.phongHoc << endl;
// }

void hienThiMonHoc(MonHoc mh) {
    cout << "\n" << mh.maMon << " | " << mh.tenMon << " | "
         << mh.thoiGianBatDau << " | " << mh.phongHoc << " | "
         << mh.thu << "\n";
}

// void Traverse(Node* root) {
//     if (root == NULL) return;
//     Traverse(root->left);
//     volatile string temp = root->data.maMon; 
//     Traverse(root->right);
// }

// hàm in ra danh sách theo mã môn học
// void InOrderTraversal() {
//     if (root == NULL) return;
//     Traverse(root->left);
//     cout << "--------------------------------\n";
//     cout << "Ma Mon: " << root->data.maMon << "\n";
//     cout << "Ten Mon: " << root->data.tenMon << "\n";
//     cout << "Thoi gian: " << root->data.thoiGianBatDau << " (" << root->data.thu << ")" << "\n";
//     cout << "Phong: " << root->data.phongHoc << "\n";
//     Traverse(root->right);
// }

void CollectAllNodes(Node* root, vector<MonHoc>& list) {
    if (root == NULL) return;
    CollectAllNodes(root->left, list);
    list.push_back(root->data);
    CollectAllNodes(root->right, list);
}

// ==================== PHƯƠNG THỨC LỚP BST ====================

void BST::Insert(const MonHoc &mh) {
    root = InsertNode(root, mh);
}

void BST::InsertWithInput() {
    MonHoc mh;
    do {
        cout << "Nhap ma Mon: ";
        cin >> mh.maMon;
        cin.ignore();
        if (!validateMaMon(mh.maMon))
            cout << "Ma mon khong hop le. Nhap lai.\n";
        else if (this->SearchMa(mh.maMon) != nullptr)
            cout << "Ma mon da ton tai. Nhap lai.\n";
        else break;
    } while (true);

    do {
        cout << "Nhap ten mon: ";
        getline(cin, mh.tenMon);
        if (!validateTenMon(mh.tenMon))
            cout << "Dinh dang khong hop le. Nhap lai.\n";
    } while (!validateTenMon(mh.tenMon));

    do {
        cout << "Nhap phong hoc: ";
        getline(cin, mh.phongHoc);
        if (!validatePhongHoc(mh.phongHoc))
            cout << "Phong hoc khong hop le. Nhap lai.\n";
    } while (!validatePhongHoc(mh.phongHoc));

    do {
        cout << "Nhap thu: ";
        getline(cin, mh.thu);
        if (!validateThu(mh.thu))
            cout << "Ngay khong hop le. Vui long nhap lai (Vi du: 'Thu 2', '3', 'chu nhat',...).\n";
    } while (!validateThu(mh.thu));

    mh.thu = formatThu(mh.thu); // Chuẩn hóa lại sau khi nhập đúng

    do {
        cout << "Nhap thoi gian (HH:MM - HH:MM): ";
        getline(cin, mh.thoiGianBatDau);
        if (!validateThoiGian(mh.thoiGianBatDau)) {
            cout << "Thoi gian khong hop le. Nhap lai.\n";
        } else if (isTimeConflict(*this, mh.thoiGianBatDau, mh.thu)) {
            cout << "Trung thoi gian bat dau cua mon hoc khac. Nhap lai.\n";
        }
        else break;
    } while (true);

    this->Insert(mh);
    this->SaveToFile("lichhoc.txt");
    cout << "Them mon hoc thanh cong.\n";
}

Node* BST::SearchMa(string maMon) {
    return SearchByMa(root, maMon);
}

vector<MonHoc> BST::SearchTen(string tenMon) {
    vector<MonHoc> result;
    SearchByTen(root, tenMon, result);
    return result;
}

bool BST::Delete(string maMon) {
    bool deleted = false;
    root = DeleteNode(root, maMon, deleted);
    SaveToFile(filedata);
    return deleted;
}

// hàm đệ quy xóa từng node từ lá lên gốc
void BST::deleteTree(Node* node) {
    if (node == NULL) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node; // Xóa node hiện tại
}

// destructor tự động gọi khi biến tree hết vòng đời
BST::~BST() {
    deleteTree(root);
}

bool BST::Update(string maMon) {
    // LoadFromFile(filedata);
    Node* node = SearchMa(maMon);
    if (node == NULL) return false;

    MonHoc& mh = node->data;

    // cập nhập tên môn
    do {
        cout << "Nhap ten mon moi: ";
        getline(cin, mh.tenMon);
        if (!validateTenMon(mh.tenMon))
            cout << "Dinh dang khong hop le. Nhap lai.\n";
    } while (!validateTenMon(mh.tenMon));

    // cập nhập phòng học
    do {
        cout << "Nhap phong hoc moi: ";
        getline(cin, mh.phongHoc);
        if (!validatePhongHoc(mh.phongHoc))
            cout << "Phong hoc khong hop le. Nhap lai.\n";
    } while (!validatePhongHoc(mh.phongHoc));

    // cập nhập ngày mới
    do {
        cout << "Nhap thu moi: ";
        getline(cin, mh.thu);
        if (!validateThu(mh.thu))
            cout << "Ngay khong hop le. Nhap lai.\n";
    } while (!validateThu(mh.thu));

    // cập nhập thời gian
    do {
        cout << "Nhap thoi gian moi (HH:MM - HH:MM): ";
        getline(cin, mh.thoiGianBatDau);
        if (!validateThoiGian(mh.thoiGianBatDau)) {
            cout << "Thoi gian khong hop le. Nhap lai.\n";
        } else if (isTimeConflict(*this, mh.thoiGianBatDau, mh.thu)) {
            cout << "Trung thoi gian bat dau cua mon hoc khac. Nhap lai.\n";
        }
        else break;
    } while (true);

    SaveToFile(filedata);
    return true;
}

void BST::LoadFromFile(string filename) {
    root = NULL; // xóa cây trước khi load
    ifstream in(filename);
    if (!in)
        return;

    string line;
    MonHoc mh;

    while (getline(in, line)) {
        if (!line.find("maMon: "))
            mh.maMon = line.substr(7);
        else if (!line.find("tenMon: "))
            mh.tenMon = line.substr(8);
        else if (!line.find("thoiGianBatDau: "))
            mh.thoiGianBatDau = line.substr(16);
        else if (!line.find("phongHoc: "))
            mh.phongHoc = line.substr(10);
        else if (!line.find("thu: "))
            mh.thu = line.substr(5);
        else if (line == "") {
            // khi gặp dòng trống, chèn môn học vào cây và reset mh
            if (!mh.maMon.empty())
                Insert(mh);
            mh = MonHoc();
        }
    }
    if (!mh.maMon.empty())
        Insert(mh);
    in.close();
}

void BST::SaveToFile(string filename) {
    ofstream out(filename);
    if (!out) {
        cout << "Khong mo duoc file.\n";
        return;
    }
    SaveNode(root, out);
    out.close();
}

void BST::inSchedule() {
    if (root == NULL) {
        cout << "\nTHOI KHOA BIEU CHUA DUOC CAP NHAT\n";
        return;
    }
    vector<MonHoc> list;
    CollectAllNodes(root, list);

    // sắp xếp: theo thứ, sau đó theo tên môn học
    sort(list.begin(), list.end(), [](const MonHoc& a, const MonHoc& b) {
        int thuA = getThuOrder(a.thu);
        int thuB = getThuOrder(b.thu);
        if (thuA != thuB) return thuA < thuB;
        return a.tenMon < b.tenMon;
    });

    // tính độ dài lớn nhất cho TOÀN BỘ danh sách
    size_t globalMaxLength = 0;
    for (const auto& mh : list) {
        string courseInfo = mh.maMon + " - " + mh.tenMon;
        if (courseInfo.length() > globalMaxLength) {
            globalMaxLength = courseInfo.length();
        }
    }
    cout << "\n=========================================================\n";
    cout << "\nTHOI KHOA BIEU THEO TEN MON HOC\n\n";

    // nhóm và hiển thị theo thứ
    map<int, vector<MonHoc>> groupedByThu;
    for (const auto& mh : list) {
        int thuOrder = getThuOrder(mh.thu);
        groupedByThu[thuOrder].push_back(mh);
    }

    // hiển thị theo thứ tự
    vector<int> thuOrders = {2, 3, 4, 5, 6, 7, 1}; // Thứ 2 đến CN
    for (int thuOrder : thuOrders) {
        if (groupedByThu.find(thuOrder) != groupedByThu.end()) {
            string thuName = formatThu(groupedByThu[thuOrder][0].thu);
            cout << thuName << ":\n";

            // hiển thị với căn chỉnh theo globalMaxLength
            for (const auto& mh : groupedByThu[thuOrder]) {
                string courseInfo = mh.maMon + " - " + mh.tenMon;
                // format: "[thời gian] | [mã môn] - [tên môn] (padded) | Phòng [phòng]"
                cout << "  " << left << setw(15) << mh.thoiGianBatDau // cố định độ rộng cột thời gian (ví dụ 15 ký tự)
                     << " | "
                     << left << setw(static_cast<int>(globalMaxLength)) << courseInfo
                     << " | "
                     << "Phong " << mh.phongHoc << "\n";
            }
            cout << "\n";
        }
    }
    cout << "=========================================================\n";
}

void BST::inScheduleByTime() {
    if (root == NULL) {
        cout << "\nTHOI KHOA BIEU CHUA DC CAP NHAT\n";
        return;
    }
    vector<MonHoc> list;
    CollectAllNodes(root, list);

    // sắp xếp: theo thứ, sau đó theo thời gian bắt đầu
    sort(list.begin(), list.end(), [](const MonHoc& a, const MonHoc& b) {
        int thuA = getThuOrder(a.thu);
        int thuB = getThuOrder(b.thu);
        if (thuA != thuB) return thuA < thuB;
        string timeA = parseStartTime(a.thoiGianBatDau);
        string timeB = parseStartTime(b.thoiGianBatDau);
        return timeA < timeB;
    });

    // tính độ dài lớn nhất cho TOÀN BỘ danh sách
    size_t globalMaxLength = 0;
    for (const auto& mh : list) {
        string courseInfo = mh.maMon + " - " + mh.tenMon;
        if (courseInfo.length() > globalMaxLength) {
            globalMaxLength = courseInfo.length();
        }
    }

    cout << "\n=========================================================\n";
    cout << "\nTHOI KHOA BIEU THEO THOI GIAN BAT DAU\n\n";

    // nhóm và hiển thị theo thứ
    map<int, vector<MonHoc>> groupedByThu;
    for (const auto& mh : list) {
        int thuOrder = getThuOrder(mh.thu);
        groupedByThu[thuOrder].push_back(mh);
    }

    // hiển thị theo thứ tự
    vector<int> thuOrders = {2, 3, 4, 5, 6, 7, 1}; // Thứ 2 đến CN
    for (int thuOrder : thuOrders) {
        if (groupedByThu.find(thuOrder) != groupedByThu.end()) {
            string thuName = formatThu(groupedByThu[thuOrder][0].thu);
            cout << thuName << ":\n";

            // hiển thị với căn chỉnh theo globalMaxLength
            for (const auto& mh : groupedByThu[thuOrder]) {
                string courseInfo = mh.maMon + " - " + mh.tenMon;

                // format: "[thời gian] | [mã môn] - [tên môn] (padded) | Phòng [phòng]"
                cout << "  " << left << setw(13) << mh.thoiGianBatDau
                     << " | "
                     << left << setw(static_cast<int>(globalMaxLength)) << courseInfo
                     << " | "
                     << "Phong " << mh.phongHoc << "\n";
            }
            cout << "\n";
        }
    }
    cout << "=========================================================\n";
}
