# 📅 Hệ Thống Lịch Học và Thời Khóa Biểu - BST

Hệ thống quản lý lịch học và thời khóa biểu sử dụng cây BST (Binary Search Tree) để quản lý và tổ chức các lớp học theo mã môn hoặc tên môn. Hệ thống hỗ trợ tìm kiếm, sắp xếp theo thời gian bắt đầu một cách có thứ tự, giúp sinh viên và giảng viên quản lý lịch học hiệu quả.

## ✨ Tính Năng Chính

- 📚 **Quản lý Lịch Học**: Thêm, xóa, tìm kiếm các môn học trong thời khóa biểu
- 🔍 **Tìm Kiếm Linh Hoạt**: Tìm kiếm môn học theo mã môn hoặc tên môn
- ⏰ **Sắp Xếp Theo Thời Gian**: Sắp xếp danh sách môn học theo thời gian bắt đầu (08:00, 10:30, 14:00...)
- 📋 **Xem Thời Khóa Biểu**: Hiển thị thời khóa biểu theo tên môn (A-Z) hoặc theo thời gian trong tuần
- 💾 **Lưu Trữ Dữ Liệu**: Lưu và đọc thời khóa biểu từ file .txt, không mất dữ liệu khi tắt chương trình
- ✅ **Kiểm Tra Tính Hợp Lệ**: Validate dữ liệu nhập vào (thời gian không âm, format đúng...)
- 📊 **Đánh Giá Hiệu Năng**: Đo thời gian thực thi các thuật toán tìm kiếm và sắp xếp

## 🏗️ Cấu Trúc Dự Án

```
cpp/
├── BST.h          # Khai báo struct MonHoc, Node và function prototypes
├── BST.cpp        # Implementation các hàm BST (Insert, Search, Delete, Traversal, File I/O)
├── main.cpp       # Menu điều khiển và Validate dữ liệu
├── test.cpp       # Test cases và đo hiệu năng
└── README.md      # File này
```

## 📋 Cấu Trúc Dữ Liệu

### Struct MonHoc (Môn Học)
Mỗi môn học trong thời khóa biểu bao gồm:
- `maMon`: Mã môn học (unique key) - VD: "CS101", "MATH202"
- `tenMon`: Tên môn học - VD: "Lập trình C++", "Toán cao cấp"
- `thoiGianBatDau`: Thời gian bắt đầu - VD: "08:00", "14:30"
- `phongHoc`: Phòng học - VD: "A101", "B202"
- `thu`: Thứ trong tuần - VD: "Thứ 2", "Thứ 5"

### Cây BST (Binary Search Tree)
- Cây BST được sắp xếp theo **mã môn học** để tối ưu tìm kiếm
- Độ phức tạp tìm kiếm: **O(log n)**
- Hỗ trợ sắp xếp lại theo **tên môn** hoặc **thời gian** khi hiển thị

## 🚀 Cài Đặt & Biên Dịch

### Yêu Cầu Hệ Thống
- **Compiler**: C++11 trở lên (g++, clang++, hoặc Visual Studio)
- **OS**: Windows, Linux, macOS

### Windows (Visual Studio)

```bash
# Biên dịch
cl /EHsc main.cpp BST.cpp /Fe:lich-hoc.exe

# Chạy chương trình
lich-hoc.exe
```

### Linux/macOS (GCC/Clang)

```bash
# Biên dịch
g++ -std=c++11 -o lich-hoc main.cpp BST.cpp

# Chạy chương trình
./lich-hoc
```

### Biên Dịch Phần Test

```bash
# Linux/macOS
g++ -std=c++11 -DRUN_TEST -o test test.cpp BST.cpp
./test

# Windows
cl /EHsc /DRUN_TEST test.cpp BST.cpp /Fe:test.exe
test.exe
```

## 💻 Sử Dụng

### Menu Chính

```
========== HE THONG LICH HOC VA THOI KHOA BIEU ==========
1. Khoi tao cay BST
2. Them mon hoc moi vao lich hoc
3. Tim kiem mon hoc theo ma mon
4. Tim kiem mon hoc theo ten mon
5. Hien thi thoi khoa bieu (sap xep theo ten A-Z)
6. Hien thi thoi khoa bieu (sap xep theo thoi gian)
7. Xoa mon hoc khoi lich hoc
8. Luu thoi khoa bieu vao file
9. Doc thoi khoa bieu tu file
10. Xem thong tin chi tiet mon hoc
0. Thoat chuong trinh
```

### Ví Dụ Sử Dụng

#### 1. Thêm Môn Học Vào Lịch

```cpp
BST lichHoc;
lichHoc.Init();

// Thêm môn học vào lịch
MonHoc mh1("CS101", "Lap trinh C++", "08:00", "Phong A101", "Thu 2");
MonHoc mh2("MATH202", "Toan cao cap", "10:30", "Phong B202", "Thu 3");
MonHoc mh3("ENG301", "Tieng Anh", "14:00", "Phong C303", "Thu 5");

lichHoc.Insert(mh1);
lichHoc.Insert(mh2);
lichHoc.Insert(mh3);
```

#### 2. Tìm Kiếm Môn Học

```cpp
// Tìm theo mã môn (nhanh - O(log n))
Node* result = lichHoc.SearchByMaMon("CS101");
if (result != NULL) {
    cout << "Tim thay: " << result->data.tenMon << endl;
}

// Tìm theo tên môn (duyệt toàn bộ cây)
vector<Node*> results = lichHoc.SearchByTenMon("Lap trinh");
```

#### 3. Xem Thời Khóa Biểu

```cpp
// Xem thời khóa biểu sắp xếp theo tên (A-Z)
lichHoc.InOrderTraversal();

// Xem thời khóa biểu sắp xếp theo thời gian bắt đầu
lichHoc.InOrderTraversalByTime();
```

#### 4. Lưu và Đọc Thời Khóa Biểu

```cpp
// Lưu thời khóa biểu vào file
lichHoc.SaveToFile("thoi-khoa-bieu.txt");

// Đọc thời khóa biểu từ file
lichHoc.LoadFromFile("thoi-khoa-bieu.txt");
```

### Format File Thời Khóa Biểu

File `.txt` lưu trữ thời khóa biểu có format:
```
maMon|tenMon|thoiGian|phongHoc|thu
CS101|Lap trinh C++|08:00|Phong A101|Thu 2
MATH202|Toan cao cap|10:30|Phong B202|Thu 3
ENG301|Tieng Anh|14:00|Phong C303|Thu 5
```

## 📊 Thuật Toán và Độ Phức Tạp

| Thao Tác | Độ Phức Tạp | Mô Tả |
|---------|-------------|-------|
| **Insert** | O(log n) | Thêm môn học vào lịch |
| **Search (theo mã)** | O(log n) | Tìm kiếm nhanh theo mã môn |
| **Search (theo tên)** | O(n) | Duyệt toàn bộ cây |
| **Delete** | O(log n) | Xóa môn học khỏi lịch |
| **Traversal** | O(n) | Duyệt toàn bộ cây để hiển thị |
| **Sort** | O(n log n) | Sắp xếp theo tên hoặc thời gian |

## 🧪 Kiểm Thử

Chạy file `test.cpp` để đánh giá hiệu năng:

```bash
g++ -std=c++11 -DRUN_TEST -o test test.cpp BST.cpp
./test
```

### Test Cases

- ✅ Test với **10 môn học** trong thời khóa biểu
- ✅ Test với **100 môn học** trong thời khóa biểu  
- ✅ Test với **1000 môn học** trong thời khóa biểu
- ✅ Đo thời gian Insert, Search, Traversal, Sort
- ✅ So sánh hiệu năng với số lượng môn học khác nhau

### Kết Quả Mong Đợi

| Số Môn Học | Insert (ms) | Search (ms) | Traversal (ms) |
|-----------|-------------|-------------|----------------|
| 10 | ~0.1 | ~0.05 | ~0.2 |
| 100 | ~1.5 | ~0.8 | ~2.0 |
| 1000 | ~15 | ~10 | ~20 |

## 👥 Thành Viên Nhóm

| Thành Viên | Phần Đảm Nhiệm |
|-----------|----------------|
| [BẠN 1] | **Phần 1**: Khung Cấu trúc dữ liệu & Video Demo |
| [BẠN 2] | **Phần 2**: Xử lý Tìm kiếm & Sắp xếp (BST.cpp) |
| [BẠN 3] | **Phần 3**: Xây dựng Menu & Validate dữ liệu (main.cpp) |
| [BẠN 4] | **Phần 4**: Kiểm thử & Đánh giá hiệu năng (test.cpp) |

## 📈 Tiến Độ Dự Án

- [x] Phần 1: Khai báo struct MonHoc, Node và hàm Init() (BST.h)
- [ ] Phần 2: Các hàm BST (Insert, Search, Delete, Traversal, File I/O) (BST.cpp)
- [ ] Phần 3: Menu và Validate dữ liệu (main.cpp)
- [ ] Phần 4: Test và đánh giá hiệu năng (test.cpp)
- [ ] Video Demo: Giới thiệu hệ thống và cách sử dụng

## 📝 Validation Dữ Liệu

Hệ thống kiểm tra tính hợp lệ của dữ liệu nhập vào:

- ✅ **Mã môn học**: Không được rỗng, không được trùng
- ✅ **Tên môn học**: Không được rỗng
- ✅ **Thời gian bắt đầu**: Format HH:MM (24h), không âm, từ 00:00 đến 23:59
  - ✓ Hợp lệ: "08:00", "14:30", "10:15"
  - ✗ Không hợp lệ: "25:00", "-5:00", "08:60", "abc"
- ✅ **Phòng học**: Không được rỗng
- ✅ **Thứ trong tuần**: Hợp lệ (Thứ 2 - Thứ 7, Chủ nhật)

## 💡 Ví Dụ Thời Khóa Biểu

```
THỜI KHÓA BIỂU HỌC KỲ I

Thứ 2:
  08:00 - 10:30  |  CS101 - Lập trình C++        |  Phòng A101
  14:00 - 16:30  |  MATH202 - Toán cao cấp       |  Phòng B202

Thứ 3:
  08:00 - 10:30  |  ENG301 - Tiếng Anh           |  Phòng C303

Thứ 5:
  10:30 - 12:00  |  CS101 - Lập trình C++ (TH)   |  Phòng Lab A1
  14:00 - 16:30  |  PHYS101 - Vật lý đại cương   |  Phòng D404
```

## 🤝 Đóng Góp

1. Fork project
2. Tạo branch mới (`git checkout -b feature/AmazingFeature`)
3. Commit changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to branch (`git push origin feature/AmazingFeature`)
5. Mở Pull Request

## 📄 License

Educational purposes only

## 🔗 Tài Liệu Tham Khảo

- [Binary Search Tree - Wikipedia](https://en.wikipedia.org/wiki/Binary_search_tree)
- [C++ Data Structures](https://www.cplusplus.com/reference/)
- [BST Visualization](https://visualgo.net/en/bst)

## 🎯 Mục Tiêu Dự Án

- Học và áp dụng cấu trúc dữ liệu BST trong thực tế
- Xây dựng hệ thống quản lý lịch học hoàn chỉnh
- Thực hành các thuật toán tìm kiếm và sắp xếp
- Đánh giá hiệu năng của các thuật toán với dữ liệu lớn

---

⭐ Nếu project này hữu ích, hãy cho một star! ⭐

📧 **Liên hệ**: [Điền email hoặc GitHub username]

📅 **Ngày tạo**: 2024
