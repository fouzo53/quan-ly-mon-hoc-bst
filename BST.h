#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
================================================================================
PHẦN 1: KHUNG CẤU TRÚC DỮ LIỆU
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [Điền tên]

NHIỆM VỤ:
- Đã hoàn thành: Khai báo struct Node, struct MonHoc
- Đã hoàn thành: Hàm Init() - Khởi tạo cây BST
- Đã hoàn thành: Hàm IsEmpty() - Kiểm tra cây rỗng

DEMO VIDEO:
- Quay màn hình thao tác chương trình với các chức năng cơ bản
- Thuyết minh về cấu trúc BST và cách hoạt động
- Test hàm Init() và IsEmpty()

================================================================================
KHÁI BÁO THÊM CÁC HÀM CẦN THIẾT:
================================================================================
Lưu ý: Chỉ khai báo function prototypes ở đây (không viết code implementation)
Các hàm được khai báo ở đây sẽ được implement trong BST.cpp
*/

// cấu trúc môn học
struct MonHoc {
    string maMon;          // mã môn học
    string tenMon;         // tên môn học
    string thoiGianBatDau; // thời gian bắt đầu (VD: "08:00", "14:30")
    string phongHoc;       // phòng học
    string thu;            // thứ trong tuần (VD: "Thứ 2", "Thứ 3")
    
    // constructor để khởi tạo môn học
    MonHoc() {}
    
    MonHoc(string ma, string ten, string tg, string phong, string th) {
        maMon = ma;
        tenMon = ten;
        thoiGianBatDau = tg;
        phongHoc = phong;
        thu = th;
    }
};

// cấu trúc Node cho cây BST
struct Node {
    MonHoc data;    // dữ liệu môn học
    Node* left;     // con trái
    Node* right;    // con phải
    
    // constructor để khởi tạo node
    Node(MonHoc mh) {
        data = mh;
        left = NULL;
        right = NULL;
    }
};

// cấu trúc cây BST
struct BST {
    Node* root;     // gốc của cây
    
    // hàm khởi tạo cây BST (ĐÃ HOÀN THÀNH)
    void Init() {
        root = NULL;
    }
    
    // hàm kiểm tra cây rỗng (ĐÃ HOÀN THÀNH)
    bool IsEmpty() {
        return root == NULL;
    }
    
    // ==================== KHAI BÁO CÁC HÀM CẦN THIẾT ====================
    // TODO: Thêm các khai báo hàm sau (chỉ khai báo, không viết code):
    
    // Hàm Insert - Thêm môn học vào cây
    // bool Insert(MonHoc mh);
    
    // Hàm Search - Tìm kiếm môn học
    // Node* SearchByMaMon(string maMon);
    // vector<Node*> SearchByTenMon(string tenMon);
    
    // Hàm Delete - Xóa môn học
    // bool Delete(string maMon);
    
    // Hàm Traversal - Duyệt cây
    // void InOrderTraversal();  // Sắp xếp theo tên
    // void InOrderTraversalByTime();  // Sắp xếp theo thời gian
    
    // Hàm File I/O
    // bool SaveToFile(string fileName);
    // int LoadFromFile(string fileName);
    
    // Hàm hỗ trợ
    // void Clear();  // Xóa toàn bộ cây
};

// Hàm hỗ trợ so sánh thời gian (khai báo ngoài struct)
// int compareTime(string time1, string time2);

#endif
