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

using namespace std;
using namespace chrono;


// ================================================================================
// PHẦN 4: KIỂM THỬ & ĐÁNH GIÁ HIỆU NĂNG
// - HỆ THỐNG LỊCH HỌC VÀ THỜI KHÓA BIỂU
// ================================================================================

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

    static vector<string> timeList = {
        "07:00", "08:00", "09:30", "10:30", "11:30",
        "13:00", "14:00", "15:30", "17:00", "18:30",
        "19:30"
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
    // tham số: (0, size-1)
    // => xác định phạm vi [min, max]. Ở đây ta muốn lấy index hợp lệ của vector

    // bộ phân phối rời rạc ngẫu nhiên cho các số ngẫu nhiên
    // phân phối ngẫu nhiên rời rạc cho phạm vi [min, max] với xác suất bằng nhau cho mọi giá trị trong phạm vi đó
    uniform_int_distribution<int> tenDis(0, (int)tenMonList.size() - 1);
    uniform_int_distribution<int> phongDis(0, (int)phongList.size() - 1);
    uniform_int_distribution<int> thuDis(0, (int)thuList.size() - 1);
    uniform_int_distribution<int> timeDis(0, (int)timeList.size() - 1);
    uniform_int_distribution<int> tienToDis(0, (int)tienToMa.size() - 1);

    string prefix = tienToMa[tienToDis(rng)]; // lấy ngẫu nhiên một tiền tố từ danh sách (ví dụ: "CS", "MATH", "ENG",...)
    int stt = index + 1;                      // số thứ tự bắt đầu từ 1
    char buf[8];                              // tạo bộ đệm để chứa mã môn học
    sprintf(buf, "%03d", stt);                // định dạng số thứ tự thành chuỗi 3 chữ số, ví dụ: 1 -> "001", 23 -> "023"
    string maMon = prefix + buf;              // ghép tiền tố với số thứ tự để tạo mã môn học, ví dụ: "CS001", "MATH023"

    // sử dụng bộ phân phối (Dis) và bộ sinh số ngẫu nhiên (rng) để lấy các giá trị ngẫu nhiên từ danh sách
    string tenMon = tenMonList[tenDis(rng)]; 
    string phong = phongList[phongDis(rng)];  
    string thu = thuList[thuDis(rng)];
    string thoiGian = timeList[timeDis(rng)];

    // khởi tạo đối tượng Monhoc với thông tin đã tạo
    MonHoc mh(maMon, tenMon, thoiGian, phong, thu);
    return mh;
}

// hàm tạo danh sách dữ liệu mẫu (mock data gerenator)
vector<MonHoc> taoDuLieuMau(int soLuong) {
    vector<MonHoc> ds;
    // cấp phát trước bộ nhớ ít nhất bằng kích thước soLuong để tránh vector phải resize nhiều lần khi thêm phần tử (tối ưu tốc độ)
    ds.reserve(soLuong);
    for (int i = 0; i < soLuong; i++)
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

double doThoiGianTraversal(BST &tree) {
    auto start = high_resolution_clock::now();  // bắt đầu bấm giờ

    tree.Traverse();                            // duyệt cây theo thứ tự In-Order (Left -> Root -> Right), độ phức tạo O(N) 

    auto end = high_resolution_clock::now();    // kết thúc bấm giờ
    duration<double, milli> diff = end - start; // tính thời gian chệnh lệch (ms)
    return diff.count();                        // trả về thời gian thực hiện thao tác Traversal   
}

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
    int soLuong;            // số lượng môn học để test
    double tInsert_ms;      // thời gian thực hiện thao tác Insert (ms)
    double tSearch_us;      // thời gian thực hiện thao tác Search trung bình (µs)
    double tTraversal_ms;   // thời gian thực hiện thao tác Traversal (ms)
    double tSort_ms;        // thời gian thực hiện thao tác Sort (ms)
};

void inKetQuaTest(const KetQuaTest &kq) {
    cout << left << setw(10) << kq.soLuong
         << setw(15) << fixed << setprecision(4) << kq.tInsert_ms
         << setw(20) << fixed << setprecision(4) << kq.tSearch_us
         << setw(18) << fixed << setprecision(4) << kq.tTraversal_ms
         << setw(15) << fixed << setprecision(4) << kq.tSort_ms << "\n";
}

void luuKetQuaVaoFile(const string &fileName, const vector<KetQuaTest> &dsKq) {
    ofstream fout(fileName);
    if (!fout.is_open()) return;

    fout << "SoMonHoc, Insert_ms, Search_avg_us, Traversal_ms, Sort_ms\n";
    for (const auto &kq : dsKq) {
        fout << kq.soLuong << ","       // cột 1: số lượng
             << kq.tInsert_ms << ","    // cột 2: thời gian Insert (ms)
             << kq.tSearch_us << ","    // cột 3: thời gian Search trung bình (µs)
             << kq.tTraversal_ms << "," // cột 4: thời gian Traversal (ms)
             << kq.tSort_ms << "\n";    // cột 5: thời gian Sort (ms)
    }
    fout.close();
}

KetQuaTest testTheoSoLuong(int soLuong) {
    // sinh ra danh sách môn học ngẫu nhiên với số lượng soLuong
    vector<MonHoc> ds = taoDuLieuMau(soLuong);

    BST tree;
    tree.Init();
    // đo thời gian Insert
    double tInsert = doThoiGianInsert(tree, ds);

    // lấy ra mã môn ở giữa danh sách để đảm bảo nó có tồn tại trong cây
    string maSearch = ds[soLuong / 2].maMon;
    // đo thời gian Search trung bình
    double tSearchAvg = doThoiGianSearch(tree, maSearch, 10000);

    // đo thời gian Traversal
    double tTraversal = doThoiGianTraversal(tree);

    // tạo bản sao của danh sách để thực hiện sắp xếp
    vector<MonHoc> dsCopy = ds;
    // đo thời gian Sort (để so sánh với Traversal)
    double tSort = doThoiGianSort(dsCopy);

    // sử uniform initializer list để đóng gói kết quả vào struct KetQuaTest và trả về
    return {soLuong, tInsert, tSearchAvg, tTraversal, tSort};
}

#ifdef RUN_TEST
int main() {
    vector<KetQuaTest> ds;

    ds.push_back(testTheoSoLuong(10));
    ds.push_back(testTheoSoLuong(100));
    ds.push_back(testTheoSoLuong(1000));

    cout << left << setw(10) << "SoMon"
         << setw(15) << "Insert(ms)"
         << setw(20) << "Search(ms/lan)"
         << setw(18) << "Traversal(ms)"
         << setw(15) << "Sort(ms)" << endl;

    for (auto &kq : ds) inKetQuaTest(kq);

    luuKetQuaVaoFile("ket_qua_hieu_nang.csv", ds);

    return 0;
}
#endif
