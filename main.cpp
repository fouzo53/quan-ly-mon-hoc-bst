#include "BST.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

/*
================================================================================
PHẦN 3: XÂY DỰNG MENU & IO
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [Điền tên]

NHIỆM VỤ:
1. Xây dựng Menu điều khiển với Switch-case
2. Nhập liệu chuẩn với Validate dữ liệu
3. Xử lý logic sắp xếp theo "Thời gian bắt đầu"
4. Tích hợp các hàm từ BST.cpp vào menu

================================================================================
CÁC HÀM CẦN VIẾT:
================================================================================
*/

// ==================== HÀM MENU ====================
// TODO: Viết hàm hiển thị menu
// void printMenu() { ... }
// Menu bao gồm:
//   1. Khoi tao cay BST
//   2. Them mon hoc moi
//   3. Tim kiem mon hoc theo ma mon
//   4. Tim kiem mon hoc theo ten mon
//   5. Hien thi danh sach mon hoc (sap xep theo ten A-Z)
//   6. Hien thi danh sach mon hoc (sap xep theo thoi gian)
//   7. Xoa mon hoc
//   8. Luu danh sach vao file
//   9. Doc danh sach tu file
//   10. Xem thong tin chi tiet mon hoc
//   0. Thoat chuong trinh

// ==================== HÀM NHẬP LIỆU ====================
// TODO: Viết hàm nhập môn học từ bàn phím
// MonHoc nhapMonHoc() { ... }
// - Yêu cầu người dùng nhập từng trường
// - Validate dữ liệu (xem phần validate bên dưới)

// TODO: Viết hàm hiển thị thông tin môn học
// void hienThiMonHoc(MonHoc mh) { ... }
// - In ra tất cả thông tin môn học một cách đẹp mắt

// ==================== HÀM VALIDATE DỮ LIỆU ====================
// TODO: Viết hàm kiểm tra mã môn học hợp lệ
// bool validateMaMon(string maMon) { ... }
// - Không được rỗng
// - Có thể kiểm tra format (VD: chữ + số)

// TODO: Viết hàm kiểm tra tên môn học hợp lệ
// bool validateTenMon(string tenMon) { ... }
// - Không được rỗng
// - Có thể kiểm tra độ dài

// TODO: Viết hàm kiểm tra thời gian hợp lệ
// bool validateThoiGian(string thoiGian) { ... }
// - Format: HH:MM (24h)
// - Kiểm tra: 00:00 <= HH:MM <= 23:59
// - Không được âm hoặc số không hợp lệ
// - VD: "08:00" ✓, "25:00" ✗, "-5:00" ✗, "08:60" ✗

// TODO: Viết hàm kiểm tra phòng học hợp lệ
// bool validatePhongHoc(string phongHoc) { ... }
// - Không được rỗng

// TODO: Viết hàm kiểm tra thứ hợp lệ
// bool validateThu(string thu) { ... }
// - Kiểm tra: "Thu 2", "Thu 3", ..., "Thu 7", "Chu nhat"
// - Hoặc: "Monday", "Tuesday", ...

// ==================== HÀM XỬ LÝ LOGIC ====================
// TODO: Viết hàm parse thời gian (HH:MM -> phút)
// int parseTimeToMinutes(string time) { ... }
// - VD: "08:30" -> 510 (8*60 + 30)
// - Dùng cho việc so sánh và sắp xếp

// TODO: Viết hàm format thời gian
// string formatTime(string time) { ... }
// - Đảm bảo format đúng HH:MM (VD: thêm số 0 đằng trước nếu cần)

// ==================== HÀM MAIN ====================
int main() {
    BST tree;
    int luaChon;
    bool daKhoiTao = false;
    
    // TODO: Tạo vòng lặp do-while với menu
    // TODO: Dùng switch-case để xử lý từng lựa chọn
    // TODO: Gọi các hàm từ BST.cpp:
    //   - tree.Insert()
    //   - tree.SearchByMaMon()
    //   - tree.SearchByTenMon()
    //   - tree.Delete()
    //   - tree.InOrderTraversal()
    //   - tree.InOrderTraversalByTime()
    //   - tree.SaveToFile()
    //   - tree.LoadFromFile()
    
    // TODO: Xử lý validation trước khi Insert
    // TODO: Xử lý thông báo lỗi/thành công cho người dùng
    // TODO: Xử lý trường hợp cây rỗng trước khi thao tác
    
    return 0;
}