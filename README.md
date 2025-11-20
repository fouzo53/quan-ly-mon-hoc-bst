# PHÂN CÔNG CÔNG VIỆC - HỆ THỐNG QUẢN LÝ MÔN HỌC BST

## 📋 TỔNG QUAN DỰ ÁN
Hệ thống quản lý lịch học và thời khóa biểu sử dụng cây BST (Binary Search Tree) để quản lý các môn học theo mã môn hoặc tên môn.

---

## 👥 PHÂN CÔNG CHI TIẾT

### 🔹 **PHẦN 1: Khung Cấu trúc dữ liệu & Video Demo**
**File:** `BST.h`  
**Thành viên:** [BẠN 1]  
**Trạng thái:** ✅ ĐÃ HOÀN THÀNH PHẦN ĐẦU

#### Nhiệm vụ:
- ✅ Khai báo `struct Node`, `struct MonHoc`
- ✅ Viết hàm `Init()` - Khởi tạo cây BST
- ✅ Viết hàm `IsEmpty()` - Kiểm tra cây rỗng
- 📹 **Làm Video Demo** (quay màn hình + thuyết minh):
  - Quay màn hình thao tác chương trình với các chức năng cơ bản
  - Thuyết minh về cấu trúc BST và cách hoạt động
  - Demo hàm `Init()` và `IsEmpty()`

---

### 🔹 **PHẦN 2: Xử lý Tìm kiếm & Sắp xếp**
**File:** `BST.cpp`  
**Thành viên:** [BẠN 2]  
**Trạng thái:** ⏳ ĐANG THỰC HIỆN

#### Nhiệm vụ cần hoàn thành:

1. **HÀM INSERT** - Thêm môn học vào cây BST
   - So sánh theo mã môn học
   - Xử lý trường hợp mã môn đã tồn tại

2. **HÀM SEARCH** - Tìm kiếm môn học
   - `SearchByMaMon()` - Tìm theo mã môn
   - `SearchByTenMon()` - Tìm theo tên môn (duyệt toàn bộ cây)

3. **HÀM DELETE** - Xóa môn học
   - Xử lý 3 trường hợp: node lá, node 1 con, node 2 con

4. **HÀM TRAVERSAL** - Duyệt cây In-order (LNR)
   - `InOrderTraversal()` - In danh sách sắp xếp theo tên (A-Z)
   - `InOrderTraversalByTime()` - In danh sách sắp xếp theo thời gian

5. **HÀM FILE I/O** - Đọc/Ghi file
   - `SaveToFile()` - Lưu danh sách vào file .txt
   - `LoadFromFile()` - Đọc danh sách từ file .txt

6. **HÀM HỖ TRỢ**
   - `compareTime()` - So sánh thời gian
   - `Clear()` - Xóa toàn bộ cây

#### Lưu ý:
- Xem chi tiết trong file `BST.cpp` (có comments hướng dẫn)
- Khai báo function prototypes trong `BST.h` trước khi implement

---

### 🔹 **PHẦN 3: Xây dựng Menu & IO**
**File:** `main.cpp`  
**Thành viên:** [BẠN 3]  
**Trạng thái:** ⏳ ĐANG THỰC HIỆN

#### Nhiệm vụ cần hoàn thành:

1. **MENU ĐIỀU KHIỂN**
   - Viết hàm `printMenu()` - Hiển thị menu với Switch-case
   - Tích hợp các hàm từ `BST.cpp` vào menu
   - Xử lý lựa chọn người dùng

2. **NHẬP LIỆU & VALIDATE**
   - `nhapMonHoc()` - Nhập môn học từ bàn phím
   - `validateMaMon()` - Kiểm tra mã môn hợp lệ
   - `validateTenMon()` - Kiểm tra tên môn hợp lệ
   - `validateThoiGian()` - Kiểm tra thời gian hợp lệ (HH:MM, không âm, 00:00-23:59)
   - `validatePhongHoc()` - Kiểm tra phòng học hợp lệ
   - `validateThu()` - Kiểm tra thứ hợp lệ

3. **XỬ LÝ LOGIC**
   - `parseTimeToMinutes()` - Parse thời gian sang phút (để so sánh)
   - `formatTime()` - Format thời gian đúng chuẩn HH:MM
   - Xử lý logic sắp xếp theo thời gian (có thể cần đổ ra mảng tạm)

4. **HÀM MAIN**
   - Vòng lặp do-while với menu
   - Switch-case xử lý từng chức năng
   - Xử lý thông báo lỗi/thành công
   - Xử lý trường hợp cây rỗng

#### Lưu ý:
- Xem chi tiết trong file `main.cpp` (có comments hướng dẫn)
- Các hàm validate phải kiểm tra kỹ các trường hợp đặc biệt

---

### 🔹 **PHẦN 4: Kiểm thử & Đánh giá hiệu năng**
**File:** `test.cpp`  
**Thành viên:** [BẠN 4]  
**Trạng thái:** ⏳ ĐANG THỰC HIỆN

#### Nhiệm vụ cần hoàn thành:

1. **TẠO DỮ LIỆU MẪU**
   - `taoDuLieuMau()` - Tạo danh sách môn học mẫu (10, 100, 1000 môn)
   - `taoMonHocNgauNhien()` - Tạo môn học ngẫu nhiên để test nhanh

2. **ĐO THỜI GIAN**
   - `doThoiGianInsert()` - Đo thời gian Insert
   - `doThoiGianSearch()` - Đo thời gian Search
   - `doThoiGianTraversal()` - Đo thời gian Traversal
   - `doThoiGianSort()` - Đo thời gian Sort
   - Sử dụng thư viện `<chrono>` trong C++

3. **TEST CÁC KỊCH BẢN**
   - `test10MonHoc()` - Test với 10 môn học
   - `test100MonHoc()` - Test với 100 môn học
   - `test1000MonHoc()` - Test với 1000 môn học
   - `soSanhHieuNang()` - So sánh và hiển thị kết quả dạng bảng

4. **BÁO CÁO KẾT QUẢ**
   - `inKetQuaTest()` - In kết quả test ra màn hình
   - `luuKetQuaVaoFile()` - Lưu kết quả vào file .txt hoặc .csv
   - Đánh giá độ phức tạp thuật toán (O(log n), O(n), ...)

#### Lưu ý:
- Xem chi tiết trong file `test.cpp` (có comments hướng dẫn)
- Test tất cả các chức năng: Insert, Search, Delete, Traversal, File I/O
- Có thể dùng `#ifdef RUN_TEST` để compile riêng phần test

---

## 📁 CẤU TRÚC FILE

```
cpp/
├── BST.h          # Khai báo struct và function prototypes
├── BST.cpp        # Implementation các hàm BST (Insert, Search, Delete, Traversal, File I/O)
├── main.cpp       # Menu điều khiển và Validate dữ liệu
├── test.cpp       # Test cases và đo hiệu năng
└── PHAN_CONG.md   # File này - Phân công công việc
```

---

## 🔗 LIÊN KẾT GIỮA CÁC PHẦN

```
BST.h (Phần 1)
    ↓
BST.cpp (Phần 2) → Sử dụng các struct từ BST.h
    ↓
main.cpp (Phần 3) → Sử dụng các hàm từ BST.cpp
    ↓
test.cpp (Phần 4) → Test tất cả các hàm từ BST.cpp và main.cpp
```

---

## ✅ CHECKLIST TIẾN ĐỘ

- [x] Phần 1: Khai báo struct và hàm Init() (BST.h)
- [ ] Phần 2: Các hàm BST (Insert, Search, Delete, Traversal, File I/O) (BST.cpp)
- [ ] Phần 3: Menu và Validate (main.cpp)
- [ ] Phần 4: Test và đánh giá hiệu năng (test.cpp)
- [ ] Video Demo (Phần 1)

---

## 📝 GHI CHÚ

1. **Đọc kỹ comments trong mỗi file** trước khi bắt đầu code
2. **Test từng hàm** sau khi viết xong
3. **Commit code thường xuyên** để tránh mất code
4. **Hỏi khi không hiểu** thay vì đoán mò
5. **Review code** trước khi merge vào main branch

---

**Chúc các bạn làm bài tốt! 💪**

