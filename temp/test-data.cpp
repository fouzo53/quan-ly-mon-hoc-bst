#define RUN_TEST
#include "bst.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <limits>

using namespace std;
using namespace chrono;

// ---------------------- HÀM SINH DỮ LIỆU NGẪU NHIÊN ----------------------

// sinh một môn học ngẫu nhiên nhưng hợp lệ
MonHoc taoMonHocNgauNhien(int index) {
    // dùng static để tối ưu hiệu năng, tránh khởi tạo lại mỗi lần gọi
    static vector<string> tienToMa = {
        "CS", "MATH", "ENG", "PHY", "CHEM", "HIST", "BIO", "ECON", "IT"
    };

    static vector<string> tenMonList = {
        "Lap trinh C++",
        "Cau truc du lieu",
        "Co so du lieu",
        "Toan cao cap",
        "Vat ly dai cuong",
        "Tieng Anh chuyen nganh",
        "He dieu hanh",
        "Mang may tinh",
        "Tri tue nhan tao",
        "Nhap mon lap trinh"
    };

    static vector<string> phongList = {
        "A101", "A102", "B201", "B202", "C303", "D404", "Lab A1", "Lab B2"
    };

    static vector<string> thuList = {
        "Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6", "Thu 7", "Chu nhat"
    };

    // khởi tạo bộ sinh số ngẫu nhiên chất lượng cao (Mersen Twister)
    // static: giữ trạng thái không bị reset mỗi lần gọi (tránh trùng lặp dữ liệu)
    // 12345: seed cố định để đảm bảo dữ liệu sinh ra luôn giống nhau khi chạy lại
    static mt19937 rng(123456);

    // thiết lập phân phối ngẫu nhiên. Ý nghĩa:
    // => uniform: đảm bảo tính công bằng. Mọi số trong phạm vi từ A đến B đều có xác suất xuất hiện ngang nhau
    // => không bị thiên lệch như cách dùng rand() % N cũ
    // => int: kết quả trả về là số nguyên
    // => distribution: xác định phạm vi của số ngẫu nhiên
    // mục đích: biến các số ngẫu nhiên (rất lớn) thành các index trong khoảng cần thiết
    uniform_int_distribution<int> tienToDist(0, tienToMa.size() - 1);
    uniform_int_distribution<int> tenMonDist(0, tenMonList.size() - 1);
    uniform_int_distribution<int> phongDist(0, phongList.size() - 1);
    uniform_int_distribution<int> thuDist(0, thuList.size() - 1);

    // sinh giờ và phút bắt đầu ngẫu nhiên
    uniform_int_distribution<int> startHourDist(7, 18); // giờ học từ 7AM -> 18PM
    uniform_int_distribution<int> startMinuteDist(0, 1); // phút là 00 hoặc 30

    // sinh thời lượng buổi học (90, 120, 150, 180 phút)
    uniform_int_distribution<int> durationDist(0, 3);
    vector<int> durations = {90, 120, 150, 180};

    MonHoc mh;
    mh.maMon = tienToMa[tienToDist(rng)] + to_string(index);
    mh.tenMon = tenMonList[tenMonDist(rng)];
    mh.phongHoc = phongList[phongDist(rng)];
    mh.thu = thuList[thuDist(rng)];

    // tạo thời gian bắt đầu và kết thúc
    int startHour = startHourDist(rng);
    int startMinute = startMinuteDist(rng) * 30;
    int duration = durations[durationDist(rng)];

    int endHour = startHour + (startMinute + duration) / 60;
    int endMinute = (startMinute + duration) % 60;

    // format thành chuỗi "HH:MM - HH:MM"
    stringstream ss;
    ss << setfill('0') << setw(2) << startHour << ":" << setw(2) << startMinute
       << " - "
       << setfill('0') << setw(2) << endHour << ":" << setw(2) << endMinute;
    mh.thoiGianBatDau = ss.str();   

    return mh;
}

// hàm tạo danh sách dữ liệu mẫu (mock data gerenator)
vector<MonHoc> taoDuLieuMau(int n) {
    vector<MonHoc> ds;
    // cấp phát trước bộ nhớ ít nhất bằng kích thước n để tránh vector phải resize nhiều lần khi thêm phần tử (tối ưu tốc độ)
    ds.reserve(n);
    for (int i = 0; i < n; i++)
        ds.push_back(taoMonHocNgauNhien(i));
    return ds;
}

// hàm đo thời gian thực hiện thao tác Insert
double doThoiGianInsert(BST &tree, const vector<MonHoc> &danhSach) {
    auto start = high_resolution_clock::now();  // bắt đầu bấm giờ

    for (const auto &mh : danhSach)             // duyệt qua danh sách môn học 
        tree.Insert(mh);
    
    auto end = high_resolution_clock::now();    // kết thúc bấm giờ
    duration<double, milli> diff = end - start; // tính thời gian chệnh lệch & chuyển sang đơn vị milisecond
    return diff.count();                        // trả về thời gian thực hiện thao tác Insert
}

double doThoiGianSearch(BST &tree, const string &maMon, int soLan) {
    auto start = high_resolution_clock::now();  // bắt đầu bấm giờ

    for (int i = 0; i < soLan; i++)             // vì tốc độ tìm kiếm của BST là o(logN), không thể chính xác nếu chỉ chạy 1 lần
        tree.SearchMa(maMon);                   // vì thế phải chạy nhiều lần để có tổng thời gian lớn hơn

    auto end = high_resolution_clock::now();    // kết thúc bấm giờ
    duration<double, milli> diff = end - start; // tính thời gian chênh lệch (ms)
    return diff.count() / soLan;                // chia trung bình để ra thời gian thực của một lần tìm kiếm
}

// double doThoiGianTraversal(BST &tree) {
//     auto start = high_resolution_clock::now();  // bắt đầu bấm giờ

//     Traverse(tree.root);                        // duyệt cây theo thứ tự In-Order (Left -> Root -> Right), độ phức tạo O(N) 

//     auto end = high_resolution_clock::now();    // kết thúc bấm giờ
//     duration<double, milli> diff = end - start; // tính thời gian chệnh lệch (ms)
//     return diff.count();                        // trả về thời gian thực hiện thao tác Traversal   
// }

double doThoiGianSort(vector<MonHoc> &danhSach) {
    auto start = high_resolution_clock::now();  // bắt đầu bấm giờ

    // sắp xếp danh sách môn học theo tên môn học (tenMon) sử dụng hàm sort của thư viện chuẩn
    // tham số thứ 3 là lambda function để định nghĩa quy tắc sắp xếp
    // tức sắp xếp tăng dần theo tên môn học
    sort(danhSach.begin(), danhSach.end(),
         [](const MonHoc &a, const MonHoc &b) {
             return a.tenMon < b.tenMon;
         });

    auto end = high_resolution_clock::now();    // kết thúc bấm giờ
    duration<double, milli> diff = end - start; // tính thời gian chênh lệch (ms)
    return diff.count();                        // trả về thời gian thực hiện thao tác Sort   
}

struct KetQuaTest {
    int soLuong;                 // số lượng môn học để test
    double tInsert_ms;           // thời gian thực hiện thao tác Insert (ms)
    double tSearch_ms;           // thời gian thực hiện thao tác Search trung bình (µs)
    // double tTraversal_ms;     // thời gian thực hiện thao tác Traversal (ms)
    double tSort_ms;             // thời gian thực hiện thao tác Sort (ms)
};

struct GioiHanTruc {
    double minVal;
    double maxVal;
};

GioiHanTruc tinhMocBieuDo(double thucTeMin, double thucTeMax) {
GioiHanTruc gh;
    
    // 1. Xử lý MAX (Làm tròn LÊN - Ceiling)
    if (thucTeMax > 100)
        gh.maxVal = ceil(thucTeMax / 10) * 10;      // Ví dụ: 115 -> 120
    else if (thucTeMax > 10)
        gh.maxVal = ceil(thucTeMax);                // Ví dụ: 15.7 -> 16.0
    else if (thucTeMax > 1)
        gh.maxVal = ceil(thucTeMax * 10) / 10.0;    // Ví dụ: 3.42 -> 3.5
    else
        gh.maxVal = ceil(thucTeMax * 100) / 100.0;  // Ví dụ: 0.28 -> 0.29

    // 2. Xử lý MIN (Làm tròn XUỐNG - Floor)
    if (thucTeMin > 100)
        gh.minVal = floor(thucTeMin / 10) * 10;
    else if (thucTeMin > 10)
        gh.minVal = floor(thucTeMin);
    else if (thucTeMin > 1)
        gh.minVal = floor(thucTeMin * 10) / 10.0;
    else
        // Ví dụ: 0.035 -> 0.03
        gh.minVal = floor(thucTeMin * 100) / 100.0; 
    
    // Đảm bảo min không âm nếu dữ liệu dương
    if (thucTeMin >= 0 && gh.minVal < 0) gh.minVal = 0;

    return gh;
}

// Hàm tính toán cho toàn bộ danh sách kết quả
void xuatGoiYAxis(const vector<KetQuaTest>& ds, ofstream& out) {
    double minIns = 1e9, maxIns = -1e9;
    double minSea = 1e9, maxSea = -1e9;
    double minSor = 1e9, maxSor = -1e9;

    // Tìm Min/Max thực tế của toàn bộ dữ liệu
    for (const auto& k : ds) {
        if (k.tInsert_ms < minIns) minIns = k.tInsert_ms;
        if (k.tInsert_ms > maxIns) maxIns = k.tInsert_ms;

        if (k.tSearch_ms < minSea) minSea = k.tSearch_ms;
        if (k.tSearch_ms > maxSea) maxSea = k.tSearch_ms;

        if (k.tSort_ms < minSor) minSor = k.tSort_ms;
        if (k.tSort_ms > maxSor) maxSor = k.tSort_ms;
    }

    GioiHanTruc axisIns = tinhMocBieuDo(minIns, maxIns);
    GioiHanTruc axisSea = tinhMocBieuDo(minSea, maxSea);
    GioiHanTruc axisSor = tinhMocBieuDo(minSor, maxSor);

    out << "\n\nGIỚI HẠN TỐC ĐỘ HIỆU NĂNG TỐI THIỂU/TỐI ĐA\n";
    out << "Loai_Bieu_Do,Axis_Min,Axis_Max,Ghi_Chu\n";
    
    out << "Insert_Chart," << axisIns.minVal << "," << axisIns.maxVal 
        << ",(Thực tế: " << minIns << " - " << maxIns << ")\n";
        
    out << "Search_Chart," << axisSea.minVal << "," << axisSea.maxVal 
        << ",(Thực tế: " << minSea << " - " << maxSea << ")\n";
        
    out << "Sort_Chart," << axisSor.minVal << "," << axisSor.maxVal 
        << ",(Thực tế: " << minSor << " - " << maxSor << ")\n";
}

void luuKetQuaVaoFile(const string &fileName, const vector<KetQuaTest> &dsKq);
void luuVaoLichHocTxt(const string &fileName, const vector<MonHoc> &dsMon);

void inKetQuaTest(const KetQuaTest &kq) {
    cout << left << setw(10) << kq.soLuong
         << setw(15) << fixed << setprecision(4) << kq.tInsert_ms
         << setw(20) << fixed << setprecision(4) << kq.tSearch_ms
         /* << setw(18) << fixed << setprecision(4) << kq.tTraversal_ms */
         << setw(15) << fixed << setprecision(4) << kq.tSort_ms << "\n";
}

void luuKetQuaVaoFile(const string &fileName, const vector<KetQuaTest> &dsKq) {
    ofstream fout(fileName);
    if (!fout.is_open()) return;

    // fout << "SoMonHoc, Insert_ms, Search_avg_us, Traversal_ms, Sort_ms\n";
    fout << "SoMonHoc, Insert_ms, Search_avg_ms, Sort_ms\n";
    for (const auto &kq : dsKq) {
        fout << kq.soLuong << ","               // cột 1: số lượng
             << kq.tInsert_ms << ","            // cột 2: thời gian Insert (ms)
             << kq.tSearch_ms << ","            // cột 3: thời gian Search trung bình (µs)
             /* << kq.tTraversal_ms << "," */   // cột 4: thời gian Traversal (ms)
             << kq.tSort_ms << "\n";            // cột 5: thời gian Sort (ms)
    }
    xuatGoiYAxis(dsKq, fout);
    fout.close();
}

void luuVaoLichHocTxt(const string &fileName, const vector<MonHoc> &dsMon) {
    ofstream fout(fileName);
    if (!fout.is_open()) {
        cout << "Loi: Khong the mo file " << fileName << " de ghi.\n";
        return;
    }
    
    // ghi từng môn học vào file theo định dạng
    for (const auto& mh : dsMon) {
        fout << "maMon: " << mh.maMon << "\n"
             << "tenMon: " << mh.tenMon << "\n"
             << "thoiGianBatDau: " << mh.thoiGianBatDau << "\n"
             << "phongHoc: " << mh.phongHoc << "\n"
             << "thu: " << mh.thu << "\n\n";
    }
    fout.close();
}

KetQuaTest testTheoSoLuong(int n) {
    // sinh ra danh sách môn học ngẫu nhiên với số lượng n
    vector<MonHoc> ds = taoDuLieuMau(n);

    BST tree; tree.Init();
    // đo thời gian Insert
    double tInsert = doThoiGianInsert(tree, ds);

    // lấy ra mã môn ở giữa danh sách để đảm bảo nó có tồn tại trong cây
    string maSearch = ds[n/2].maMon;
    // đo thời gian Search trung bình
    double tSearchAvg = doThoiGianSearch(tree, maSearch, 10000);

    // đo thời gian Traversal
    // double tTraversal = doThoiGianTraversal(tree);

    // tạo bản sao của danh sách để thực hiện sắp xếp
    vector<MonHoc> dsCopy = ds;
    // đo thời gian Sort (để so sánh với Traversal)
    double tSort = doThoiGianSort(dsCopy);

    // sử uniform initializer list để đóng gói kết quả vào struct KetQuaTest và trả về
    return {n, tInsert, tSearchAvg, /* tTraversal, */ tSort};
}

#ifdef RUN_TEST
int main() {
    vector<KetQuaTest> dsKq;
    dsKq.push_back(testTheoSoLuong(10));
    dsKq.push_back(testTheoSoLuong(100));
    dsKq.push_back(testTheoSoLuong(1000));

    vector<MonHoc> dsMon = taoDuLieuMau(1000);

    cout << left << setw(10) << "SoMon"
         << setw(15) << "Insert(ms)"
         << setw(20) << "Search(ms/lan)"
         << setw(15) << "Sort(ms)" << endl;

    for (auto &kq : dsKq) inKetQuaTest(kq);

    char ch;
    cout << "Ban co muon xuat du lieu mau ra file CSV? (y/n): ";
    cin >> ch;
    cin.ignore();
    if (ch == 'y' || ch == 'Y') {
        ofstream fout("du_lieu_mau.csv");
        fout << "maMon,tenMon,thoiGianBatDau,phongHoc,thu\n";
        for (const auto& mh : dsMon) {
            fout << mh.maMon << "," << mh.tenMon << "," << mh.thoiGianBatDau << ","
                 << mh.phongHoc << "," << mh.thu << "\n";
        }
        fout.close();
        cout << "Da xuat du lieu mau ra file du_lieu_mau.csv\n";
    }

    cout << "Ban co muon xuat ket qua hieu nang ra file CSV? (y/n): ";
    cin >> ch;
    cin.ignore();
    if (ch == 'y' || ch == 'Y') {
        luuKetQuaVaoFile("ket_qua_hieu_nang.csv", dsKq);
        cout << "Da xuat ket qua hieu nang ra file ket_qua_hieu_nang.csv\n";
    }

    cout << "Ban co muon tao du lieu cho file lichhoc.txt? (y/n): ";
    cin >> ch;
    cin.ignore();
    if (ch == 'y' || ch == 'Y') {
        int n;
        cout << "Nhap so luong mon hoc can tao: ";
        cin >> n;
        if (n > 0) {
            vector<MonHoc> dsLichHoc = taoDuLieuMau(n);
            luuVaoLichHocTxt("lichhoc.txt", dsLichHoc);
            cout << "Da tao file lichhoc.txt voi " << n << " mon hoc.\n";
        } else
            cout << "So luong khong hop le.\n";
    }

    return 0;
}
#endif

// #ifdef RUN_TEST
// int main() {
//     vector<KetQuaTest> ds;

//     ds.push_back(testTheoSoLuong(10));
//     ds.push_back(testTheoSoLuong(100));
//     ds.push_back(testTheoSoLuong(1000));

//     cout << left << setw(10) << "SoMon"
//          << setw(15) << "Insert(ms)"
//          << setw(20) << "Search(ms/lan)"
//         //  << setw(18) << "Traversal(ms)"
//          << setw(15) << "Sort(ms)" << endl;

//     for (auto &kq : ds) inKetQuaTest(kq);

//     luuKetQuaVaoFile("ket_qua_hieu_nang.csv", ds);

//     return 0;
// }
// #endif
