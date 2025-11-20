#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
================================================================================
PHẦN 1: KHUNG CẤU TRÚC DỮ LIỆU - HỆ THỐNG LỊCH HỌC VÀ THỜI KHÓA BIỂU
================================================================================
THÀNH VIÊN PHỤ TRÁCH: [BẠN 1]

NHIỆM VỤ:
- Đã hoàn thành: Khai báo struct Node, struct MonHoc (lưu thông tin môn học trong lịch)
- Đã hoàn thành: Hàm Init() - Khởi tạo cây BST để lưu trữ thời khóa biểu
- Đã hoàn thành: Hàm IsEmpty() - Kiểm tra cây rỗng (kiểm tra có môn học nào trong lịch không)

DEMO VIDEO:
- Quay màn hình thao tác chương trình với các chức năng cơ bản
- Thuyết minh về cấu trúc BST và cách quản lý lịch học
- Demo hàm Init() và IsEmpty() với hệ thống thời khóa biểu

MỤC ĐÍCH:
- Cây BST được sử dụng để quản lý các môn học trong lịch học
- Cây sắp xếp theo mã môn học để tìm kiếm nhanh
- Hỗ trợ hiển thị thời khóa biểu theo thời gian bắt đầu

================================================================================
KHÁI BÁO THÊM CÁC HÀM CẦN THIẾT:
================================================================================
Lưu ý: Chỉ khai báo function prototypes ở đây (không viết code implementation)
Các hàm được khai báo ở đây sẽ được implement trong BST.cpp
*/

// cấu trúc môn học trong lịch học và thời khóa biểu
struct MonHoc {
    string maMon;          // mã môn học (unique key để sắp xếp trong BST)
    string tenMon;         // tên môn học
    string thoiGianBatDau; // thời gian bắt đầu trong thời khóa biểu (VD: "08:00", "14:30")
    string phongHoc;       // phòng học
    string thu;            // thứ trong tuần của lịch học (VD: "Thứ 2", "Thứ 3")
    
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
    
    // Hàm Insert - Thêm môn học vào lịch học
    // bool Insert(MonHoc mh);
    
    // Hàm Search - Tìm kiếm môn học trong thời khóa biểu
    // Node* SearchByMaMon(string maMon);  // Tìm theo mã môn (nhanh - O(log n))
    // vector<Node*> SearchByTenMon(string tenMon);  // Tìm theo tên môn (duyệt toàn bộ cây)
    
    // Hàm Delete - Xóa môn học khỏi lịch học
    // bool Delete(string maMon);
    
    // Hàm Traversal - Duyệt cây và hiển thị thời khóa biểu
    // void InOrderTraversal();  // Hiển thị danh sách môn học sắp xếp theo tên (A-Z)
    // void InOrderTraversalByTime();  // Hiển thị thời khóa biểu sắp xếp theo thời gian bắt đầu
    
    // Hàm File I/O - Lưu và đọc thời khóa biểu
    // bool SaveToFile(string fileName);  // Lưu thời khóa biểu vào file .txt
    // int LoadFromFile(string fileName);  // Đọc thời khóa biểu từ file .txt
    
    // Hàm hỗ trợ
    // void Clear();  // Xóa toàn bộ cây (xóa toàn bộ lịch học)
};

// Hàm hỗ trợ so sánh thời gian (khai báo ngoài struct)
// int compareTime(string time1, string time2);

#endif
