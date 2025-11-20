#include "BST.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

/*
================================================================================
PHẦN 2: XỬ LÝ TÌM KIẾM & SẮP XẾP
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [Điền tên]

CÁC HÀM CẦN VIẾT:

1. HÀM INSERT - Thêm môn học vào cây BST
   - Tham số: BST* tree hoặc Node*& root, MonHoc mh
   - So sánh theo mã môn học để quyết định thêm vào trái hay phải
   - Trả về: bool (true nếu thành công, false nếu mã môn đã tồn tại)

2. HÀM SEARCH - Tìm kiếm môn học
   a) SearchByMaMon - Tìm theo mã môn học
      - Tham số: Node* root, string maMon
      - Trả về: Node* (trỏ đến node tìm được, NULL nếu không tìm thấy)
   
   b) SearchByTenMon - Tìm theo tên môn học
      - Tham số: Node* root, string tenMon
      - Trả về: Node* hoặc vector<Node*> (vì có thể có nhiều môn cùng tên)
      - Lưu ý: Tìm kiếm phải duyệt toàn bộ cây vì cây sắp xếp theo mã, không theo tên

3. HÀM DELETE - Xóa môn học
   - Tham số: Node*& root, string maMon
   - Xử lý 3 trường hợp:
     + Node lá (không có con)
     + Node có 1 con
     + Node có 2 con (tìm node thay thế: node trái nhất của cây con phải)
   - Trả về: bool (true nếu xóa thành công, false nếu không tìm thấy)

4. HÀM TRAVERSAL - Duyệt cây In-order (LNR)
   a) InOrderTraversal - Duyệt và in danh sách theo thứ tự tên (A-Z)
      - Tham số: Node* root
      - Ý tưởng: Duyệt LNR, nhưng cần sắp xếp lại theo tên
      - Giải pháp: Thu thập tất cả môn học vào vector, sort theo tên, rồi in
   
   b) InOrderTraversalByTime - Duyệt và in danh sách theo thời gian bắt đầu
      - Tham số: Node* root
      - Ý tưởng: Đổ dữ liệu ra vector tạm, sort theo thoiGianBatDau, rồi in
      - Lưu ý: Phân tích chuỗi thời gian (VD: "08:00") để so sánh đúng

5. HÀM FILE I/O - Đọc/Ghi file
   a) SaveToFile - Lưu danh sách môn học vào file .txt
      - Tham số: BST tree, string fileName
      - Định dạng file: Mỗi môn học trên 1 dòng, các trường cách nhau bởi dấu "|"
      - VD: CS101|Lap trinh C++|08:00|Phong A101|Thu 2
   
   b) LoadFromFile - Đọc danh sách môn học từ file .txt
      - Tham số: BST& tree, string fileName
      - Đọc file, parse từng dòng, tạo MonHoc và Insert vào cây
      - Trả về: int (số lượng môn học đã đọc được)

6. HÀM HỖ TRỢ
   a) So sánh thời gian: int compareTime(string time1, string time2)
      - Trả về: -1 nếu time1 < time2, 0 nếu bằng, 1 nếu time1 > time2
   
   b) Xóa toàn bộ cây: void Clear(Node*& root)
      - Giải phóng bộ nhớ (delete) tất cả các node trong cây

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