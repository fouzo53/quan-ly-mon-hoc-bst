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
PHẦN 4: KIỂM THỬ & ĐÁNH GIÁ HIỆU NĂNG
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [Điền tên]

NHIỆM VỤ:
1. Tạo bộ dữ liệu mẫu (Test case): 10 môn, 100 môn, 1000 môn
2. Đo thời gian chạy của các thuật toán (tìm kiếm, sắp xếp)
3. Code hàm tạo dữ liệu ngẫu nhiên để test nhanh
4. Đánh giá và báo cáo hiệu năng

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

// TODO: Viết hàm tạo môn học ngẫu nhiên
// MonHoc taoMonHocNgauNhien(int index) { ... }
// - Dùng random để tạo mã môn (VD: "CS001", "MATH002", ...)
// - Dùng random để tạo tên môn (có thể dùng danh sách tên có sẵn)
// - Dùng random để tạo thời gian (07:00 - 17:00)
// - Dùng random để tạo phòng (VD: "A101", "B202", ...)
// - Dùng random để tạo thứ (Thu 2 - Chu nhat)

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

1. Test Insert:
   - Insert vào cây rỗng
   - Insert với mã đã tồn tại (phải báo lỗi)
   - Insert nhiều phần tử (10, 100, 1000)
   - Đo thời gian Insert từng phần tử và tổng thời gian

2. Test Search:
   - Search với mã tồn tại
   - Search với mã không tồn tại
   - Search với tên tồn tại (có thể nhiều kết quả)
   - Đo thời gian search trong cây 10, 100, 1000 phần tử

3. Test Delete:
   - Delete node lá
   - Delete node có 1 con
   - Delete node có 2 con
   - Delete với mã không tồn tại
   - Đo thời gian delete

4. Test Traversal:
   - In danh sách theo thứ tự tên (A-Z)
   - In danh sách theo thứ tự thời gian
   - Đo thời gian traversal

5. Test File I/O:
   - Lưu và đọc file với 10, 100, 1000 môn
   - Kiểm tra tính toàn vẹn dữ liệu

================================================================================
BÁO CÁO CẦN CÓ:
================================================================================
1. Bảng so sánh thời gian với 10, 100, 1000 môn học
2. Đánh giá độ phức tạp: O(log n), O(n), ...
3. Biểu đồ thời gian (nếu có thể)
4. Kết luận về hiệu năng của từng thuật toán
*/

