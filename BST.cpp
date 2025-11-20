#include "BST.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
================================================================================
PHẦN 2: XỬ LÝ TÌM KIẾM & SẮP XẾP - HỆ THỐNG LỊCH HỌC VÀ THỜI KHÓA BIỂU
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [BẠN 2]

CÁC HÀM CẦN VIẾT:

1. HÀM INSERT - Thêm môn học vào lịch học (BST)
   - Tham số: BST* tree hoặc Node*& root, MonHoc mh
   - So sánh theo mã môn học để quyết định thêm vào trái hay phải
   - Trả về: bool (true nếu thành công, false nếu mã môn đã tồn tại trong lịch)

2. HÀM SEARCH - Tìm kiếm môn học trong thời khóa biểu
   a) SearchByMaMon - Tìm theo mã môn học (nhanh - O(log n))
      - Tham số: Node* root, string maMon
      - Trả về: Node* (trỏ đến node tìm được, NULL nếu không tìm thấy trong lịch)
      - Mục đích: Tìm nhanh môn học theo mã trong thời khóa biểu
   
   b) SearchByTenMon - Tìm theo tên môn học (duyệt toàn bộ cây - O(n))
      - Tham số: Node* root, string tenMon
      - Trả về: Node* hoặc vector<Node*> (vì có thể có nhiều môn cùng tên trong lịch)
      - Lưu ý: Tìm kiếm phải duyệt toàn bộ cây vì cây sắp xếp theo mã, không theo tên
      - Mục đích: Tìm các môn học có cùng tên trong lịch học

3. HÀM DELETE - Xóa môn học khỏi lịch học
   - Tham số: Node*& root, string maMon
   - Xử lý 3 trường hợp:
     + Node lá (không có con) - xóa môn học đơn giản
     + Node có 1 con - nối con trực tiếp với node cha
     + Node có 2 con (tìm node thay thế: node trái nhất của cây con phải)
   - Trả về: bool (true nếu xóa thành công, false nếu không tìm thấy trong lịch)
   - Mục đích: Xóa môn học khỏi thời khóa biểu

4. HÀM TRAVERSAL - Duyệt cây và hiển thị thời khóa biểu In-order (LNR)
   a) InOrderTraversal - Hiển thị danh sách môn học sắp xếp theo tên (A-Z)
      - Tham số: Node* root
      - Ý tưởng: Duyệt LNR, nhưng cần sắp xếp lại theo tên môn học
      - Giải pháp: Thu thập tất cả môn học vào vector, sort theo tên, rồi in ra
      - Mục đích: Xem danh sách môn học trong lịch theo thứ tự tên
   
   b) InOrderTraversalByTime - Hiển thị thời khóa biểu sắp xếp theo thời gian bắt đầu
      - Tham số: Node* root
      - Ý tưởng: Đổ dữ liệu ra vector tạm, sort theo thoiGianBatDau, rồi in ra
      - Lưu ý: Phân tích chuỗi thời gian (VD: "08:00") để so sánh đúng (08:00 < 14:30)
      - Mục đích: Xem thời khóa biểu theo thứ tự thời gian trong ngày/tuần

5. HÀM FILE I/O - Đọc/Ghi thời khóa biểu từ file
   a) SaveToFile - Lưu thời khóa biểu vào file .txt
      - Tham số: BST tree, string fileName
      - Định dạng file: Mỗi môn học trên 1 dòng, các trường cách nhau bởi dấu "|"
      - VD: CS101|Lap trinh C++|08:00|Phong A101|Thu 2
      - Mục đích: Lưu trữ thời khóa biểu để sử dụng sau, không mất dữ liệu khi tắt chương trình
   
   b) LoadFromFile - Đọc thời khóa biểu từ file .txt
      - Tham số: BST& tree, string fileName
      - Đọc file, parse từng dòng, tạo MonHoc và Insert vào cây
      - Trả về: int (số lượng môn học đã đọc được từ file)
      - Mục đích: Khôi phục thời khóa biểu từ file đã lưu trước đó

6. HÀM HỖ TRỢ
   a) So sánh thời gian: int compareTime(string time1, string time2)
      - Trả về: -1 nếu time1 < time2, 0 nếu bằng, 1 nếu time1 > time2
      - Mục đích: So sánh thời gian bắt đầu để sắp xếp thời khóa biểu (VD: "08:00" < "14:30")
      - Ví dụ: compareTime("08:00", "14:30") trả về -1
   
   b) Xóa toàn bộ cây: void Clear(Node*& root)
      - Giải phóng bộ nhớ (delete) tất cả các node trong cây
      - Mục đích: Xóa toàn bộ lịch học, giải phóng bộ nhớ trước khi kết thúc chương trình

================================================================================
GỢI Ý CẤU TRÚC:
================================================================================
*/

// ==================== HÀM INSERT ====================
// TODO: Viết hàm Insert tại đây
// bool BST::Insert(MonHoc mh) { ... }

// ==================== HÀM SEARCH ====================
// TODO: Viết hàm SearchByMaMon tại đây
// Node* BST::SearchByMaMon(string maMon) { ... }

// TODO: Viết hàm SearchByTenMon tại đây
// vector<Node*> BST::SearchByTenMon(string tenMon) { ... }

// ==================== HÀM DELETE ====================
// TODO: Viết hàm Delete tại đây
// bool BST::Delete(string maMon) { ... }

// ==================== HÀM TRAVERSAL ====================
// TODO: Viết hàm InOrderTraversal (sắp xếp theo tên) tại đây
// void BST::InOrderTraversal() { ... }

// TODO: Viết hàm InOrderTraversalByTime (sắp xếp theo thời gian) tại đây
// void BST::InOrderTraversalByTime() { ... }

// ==================== HÀM FILE I/O ====================
// TODO: Viết hàm SaveToFile tại đây
// bool BST::SaveToFile(string fileName) { ... }

// TODO: Viết hàm LoadFromFile tại đây
// int BST::LoadFromFile(string fileName) { ... }

// ==================== HÀM HỖ TRỢ ====================
// TODO: Viết hàm compareTime tại đây
// int compareTime(string time1, string time2) { ... }

// TODO: Viết hàm Clear tại đây
// void BST::Clear() { ... }