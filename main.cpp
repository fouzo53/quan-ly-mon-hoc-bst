#include "BST.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std;

/*
================================================================================
PHẦN 3: XÂY DỰNG MENU & IO - HỆ THỐNG LỊCH HỌC VÀ THỜI KHÓA BIỂU
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [BẠN 3]

NHIỆM VỤ:
1. Xây dựng Menu điều khiển với Switch-case cho hệ thống lịch học
2. Nhập liệu chuẩn với Validate dữ liệu (thời gian, thứ, phòng học...)
3. Xử lý logic sắp xếp theo "Thời gian bắt đầu" để hiển thị thời khóa biểu
4. Tích hợp các hàm từ BST.cpp vào menu (quản lý lịch học)

================================================================================
CÁC HÀM CẦN VIẾT:
================================================================================
*/

// ==================== HÀM MENU ====================
// TODO: Viết hàm hiển thị menu cho hệ thống lịch học và thời khóa biểu
// void printMenu() { ... }
// Menu bao gồm:
//   1. Khoi tao cay BST (Khoi tao lich hoc)
//   2. Them mon hoc moi vao lich hoc
//   3. Tim kiem mon hoc trong lich theo ma mon
//   4. Tim kiem mon hoc trong lich theo ten mon
//   5. Hien thi thoi khoa bieu (sap xep theo ten A-Z)
//   6. Hien thi thoi khoa bieu (sap xep theo thoi gian bat dau)
//   7. Xoa mon hoc khoi lich hoc
//   8. Luu thoi khoa bieu vao file
//   9. Doc thoi khoa bieu tu file
//   10. Xem thong tin chi tiet mon hoc trong lich
//   0. Thoat chuong trinh

// ==================== HÀM NHẬP LIỆU ====================
// TODO: Viết hàm nhập môn học từ bàn phím để thêm vào lịch học
// MonHoc nhapMonHoc() { ... }
// - Yêu cầu người dùng nhập từng trường: mã môn, tên môn, thời gian, phòng, thứ
// - Validate dữ liệu (xem phần validate bên dưới)
// - Mục đích: Nhập thông tin môn học để thêm vào thời khóa biểu

// TODO: Viết hàm hiển thị thông tin môn học trong lịch
// void hienThiMonHoc(MonHoc mh) { ... }
// - In ra tất cả thông tin môn học một cách đẹp mắt (mã, tên, thời gian, phòng, thứ)
// - Format: "CS101 | Lap trinh C++ | 08:00 | Phong A101 | Thu 2"

// ==================== HÀM VALIDATE DỮ LIỆU ====================
// TODO: Viết hàm kiểm tra mã môn học hợp lệ
// bool validateMaMon(string maMon) { ... }
// - Không được rỗng
// - Có thể kiểm tra format (VD: chữ + số)

// TODO: Viết hàm kiểm tra tên môn học hợp lệ
// bool validateTenMon(string tenMon) { ... }
// - Không được rỗng
// - Có thể kiểm tra độ dài

// TODO: Viết hàm kiểm tra thời gian bắt đầu hợp lệ trong lịch học
// bool validateThoiGian(string thoiGian) { ... }
// - Format: HH:MM (24h)
// - Kiểm tra: 00:00 <= HH:MM <= 23:59 (thời gian hợp lệ trong ngày)
// - Không được âm hoặc số không hợp lệ (giờ và phút phải hợp lệ)
// - VD hợp lệ: "08:00", "14:30", "10:15" ✓
// - VD không hợp lệ: "25:00", "-5:00", "08:60", "abc" ✗
// - Mục đích: Đảm bảo thời gian bắt đầu trong thời khóa biểu là hợp lệ

// TODO: Viết hàm kiểm tra phòng học hợp lệ
// bool validatePhongHoc(string phongHoc) { ... }
// - Không được rỗng

// TODO: Viết hàm kiểm tra thứ trong tuần hợp lệ cho lịch học
// bool validateThu(string thu) { ... }
// - Kiểm tra: "Thu 2", "Thu 3", ..., "Thu 7", "Chu nhat" (hoặc "Chủ nhật")
// - Hoặc: "Monday", "Tuesday", "Wednesday", ..., "Sunday" (tiếng Anh)
// - Mục đích: Đảm bảo thứ trong tuần hợp lệ trong thời khóa biểu

// ==================== HÀM XỬ LÝ LOGIC ====================
// TODO: Viết hàm parse thời gian (HH:MM -> phút) để so sánh và sắp xếp lịch học
// int parseTimeToMinutes(string time) { ... }
// - VD: "08:30" -> 510 (8*60 + 30), "14:00" -> 840 (14*60 + 0)
// - Dùng cho việc so sánh thời gian bắt đầu và sắp xếp thời khóa biểu
// - Mục đích: Chuyển đổi thời gian sang phút để dễ so sánh (08:00 < 14:30)

// TODO: Viết hàm format thời gian đúng chuẩn HH:MM
// string formatTime(string time) { ... }
// - Đảm bảo format đúng HH:MM (VD: thêm số 0 đằng trước nếu cần: "8:30" -> "08:30")
// - Mục đích: Hiển thị thời gian trong thời khóa biểu một cách chuẩn và đẹp

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