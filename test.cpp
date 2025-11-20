#include "BST.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <ctime>
#include <fstream>
using namespace std;
using namespace std::chrono;

/*
================================================================================
PHẦN 4: KIỂM THỬ & ĐÁNH GIÁ HIỆU NĂNG - HỆ THỐNG LỊCH HỌC VÀ THỜI KHÓA BIỂU
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [BẠN 4]

NHIỆM VỤ:
1. Tạo bộ dữ liệu mẫu (Test case): 10 môn, 100 môn, 1000 môn trong lịch học
2. Đo thời gian chạy của các thuật toán (tìm kiếm môn học, sắp xếp thời khóa biểu)
3. Code hàm tạo dữ liệu ngẫu nhiên để test nhanh (môn học, thời gian, phòng, thứ)
4. Đánh giá và báo cáo hiệu năng của hệ thống quản lý lịch học

================================================================================
CÁC HÀM CẦN VIẾT:
================================================================================
*/

// ==================== HÀM TẠO DỮ LIỆU MẪU ====================
// TODO: Viết hàm tạo danh sách môn học mẫu (cố định)
// vector<MonHoc> taoDuLieuMau(int soLuong) { ... }
// - soLuong: 10, 100, hoặc 1000
// - Tạo các môn học với mã, tên, thời gian, phòng, thứ hợp lệ
// - Trả về vector chứa các MonHoc

// TODO: Viết hàm tạo môn học ngẫu nhiên để test lịch học
// MonHoc taoMonHocNgauNhien(int index) { ... }
// - Dùng random để tạo mã môn (VD: "CS001", "MATH002", "ENG003", ...)
// - Dùng random để tạo tên môn (có thể dùng danh sách tên có sẵn: "Lập trình", "Toán", "Tiếng Anh"...)
// - Dùng random để tạo thời gian bắt đầu (07:00 - 17:00) - giờ học hợp lệ trong ngày
// - Dùng random để tạo phòng (VD: "A101", "B202", "C303", ...)
// - Dùng random để tạo thứ trong tuần (Thu 2 - Chu nhat) - phân bổ đều trong tuần

// ==================== HÀM ĐO THỜI GIAN ====================
// TODO: Viết hàm đo thời gian Insert
// double doThoiGianInsert(BST& tree, vector<MonHoc> danhSach) { ... }
// - Dùng high_resolution_clock::now() để đo thời gian
// - Thêm tất cả môn học vào cây
// - Trả về thời gian (giây hoặc milliseconds)

// TODO: Viết hàm đo thời gian Search
// double doThoiGianSearch(BST& tree, string maMon, int soLan) { ... }
// - Thực hiện tìm kiếm 'soLan' lần
// - Tính thời gian trung bình mỗi lần tìm kiếm
// - Trả về thời gian trung bình

// TODO: Viết hàm đo thời gian Traversal
// double doThoiGianTraversal(BST& tree) { ... }
// - Đo thời gian duyệt toàn bộ cây
// - Trả về thời gian

// TODO: Viết hàm đo thời gian Sort
// double doThoiGianSort(vector<MonHoc>& danhSach) { ... }
// - Đo thời gian sắp xếp danh sách theo tên hoặc thời gian
// - Trả về thời gian

// ==================== HÀM TEST CÁC KỊCH BẢN ====================
// TODO: Viết hàm test với 10 môn học
// void test10MonHoc() { ... }
// - Tạo 10 môn học
// - Đo thời gian: Insert, Search, Traversal, Sort
// - In kết quả ra màn hình

// TODO: Viết hàm test với 100 môn học
// void test100MonHoc() { ... }

// TODO: Viết hàm test với 1000 môn học
// void test1000MonHoc() { ... }

// TODO: Viết hàm so sánh hiệu năng
// void soSanhHieuNang() { ... }
// - Chạy test với 10, 100, 1000 môn
// - So sánh và hiển thị kết quả dạng bảng
// - Đánh giá độ phức tạp của thuật toán

// ==================== HÀM IN KẾT QUẢ ====================
// TODO: Viết hàm in kết quả test
// void inKetQuaTest(int soLuong, double thoiGianInsert, double thoiGianSearch, 
//                   double thoiGianTraversal, double thoiGianSort) { ... }
// - In ra bảng kết quả đẹp mắt
// - Hiển thị: Số lượng môn, Thời gian từng thao tác

// TODO: Viết hàm lưu kết quả vào file
// void luuKetQuaVaoFile(string fileName, ...) { ... }
// - Lưu kết quả test vào file .txt hoặc .csv
// - Dễ dàng import vào Excel để vẽ biểu đồ

// ==================== HÀM MAIN CHO TEST ====================
// Lưu ý: Có thể tách riêng hoặc dùng #ifdef để switch giữa main.cpp và test.cpp

#ifdef RUN_TEST
int main() {
    cout << "========================================" << endl;
    cout << "KIEM THU VA DANH GIA HIEU NANG" << endl;
    cout << "HE THONG LICH HOC VA THOI KHOA BIEU" << endl;
    cout << "========================================" << endl;
    
    // TODO: Gọi các hàm test
    // test10MonHoc();
    // test100MonHoc();
    // test1000MonHoc();
    // soSanhHieuNang();
    
    return 0;
}
#endif

/*
================================================================================
GỢI Ý TEST CASES:
================================================================================

1. Test Insert - Thêm môn học vào lịch:
   - Insert vào cây rỗng (khởi tạo lịch học mới)
   - Insert với mã đã tồn tại (phải báo lỗi - không cho trùng mã môn)
   - Insert nhiều môn học vào lịch (10, 100, 1000 môn)
   - Đo thời gian Insert từng môn học và tổng thời gian xây dựng lịch học

2. Test Search - Tìm kiếm môn học trong thời khóa biểu:
   - Search với mã tồn tại trong lịch
   - Search với mã không tồn tại trong lịch
   - Search với tên môn tồn tại (có thể nhiều môn cùng tên trong lịch)
   - Đo thời gian search trong lịch có 10, 100, 1000 môn học

3. Test Delete - Xóa môn học khỏi lịch:
   - Delete node lá (xóa môn học đơn giản)
   - Delete node có 1 con
   - Delete node có 2 con
   - Delete với mã không tồn tại trong lịch
   - Đo thời gian delete môn học khỏi lịch

4. Test Traversal - Hiển thị thời khóa biểu:
   - In danh sách môn học theo thứ tự tên (A-Z)
   - In thời khóa biểu theo thứ tự thời gian bắt đầu
   - Đo thời gian duyệt và hiển thị lịch học

5. Test File I/O - Lưu và đọc thời khóa biểu:
   - Lưu và đọc file với 10, 100, 1000 môn học
   - Kiểm tra tính toàn vẹn dữ liệu (không mất thông tin khi lưu/đọc)
   - Đo thời gian lưu và đọc thời khóa biểu

================================================================================
BÁO CÁO CẦN CÓ:
================================================================================
1. Bảng so sánh thời gian với 10, 100, 1000 môn học trong lịch học
2. Đánh giá độ phức tạp của các thuật toán: O(log n), O(n), ...
   - Insert: O(log n) - Thêm môn học vào lịch
   - Search theo mã: O(log n) - Tìm kiếm nhanh trong lịch
   - Search theo tên: O(n) - Duyệt toàn bộ lịch
   - Traversal: O(n) - Hiển thị toàn bộ thời khóa biểu
3. Biểu đồ thời gian (nếu có thể) để so sánh hiệu năng
4. Kết luận về hiệu năng của từng thuật toán trong hệ thống quản lý lịch học
*/

