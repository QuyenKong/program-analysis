#include <iostream>

using namespace std;

// --- PHẦN 4: MINH HỌA SỬ DỤNG VÀ GIẢI PHÓNG CON TRỎ ---
// Minh họa cách sử dụng Con trỏ và tầm quan trọng của việc giải phóng.
void IllustratePointerUsage() {
  cout << "\n--- 4. MINH HỌA SỬ DỤNG VÀ GIẢI PHÓNG CON TRỎ ---" << endl;

  // 1. Sử dụng Con trỏ Cơ bản (Trỏ đến biến Stack)
  int value = 42;
  int *ptrValue = &value; // Gán địa chỉ của 'value' cho 'ptrValue'

  cout << "Giá trị: " << value << endl;
  cout << "Địa chỉ của Giá trị (&value): " << &value << endl;
  cout << "Giá trị Con trỏ (ptrValue): " << ptrValue << endl;
  cout << "Truy cập qua Con trỏ (*ptrValue): " << *ptrValue << endl;

  // Thay đổi giá trị qua Con trỏ
  *ptrValue = 99;
  cout << "Giá trị Mới: " << value << endl;

  // 2. Sử dụng Con trỏ cho Bộ nhớ Động (Heap) và Giải phóng
  // Đây là nơi quản lý bộ nhớ thủ công trở nên quan trọng.
  int size = 5;
  int *dynamicArray = new int[size]; // Cấp phát một mảng 5 phần tử trên Heap

  for (int i = 0; i < size; ++i) {
    dynamicArray[i] = (i + 1) * 10;
  }
  cout << "Mảng Động trên Heap: " << dynamicArray[0] << ", " << dynamicArray[4]
       << "..." << endl;

  // QUAN TRỌNG: Giải phóng bộ nhớ mảng đã cấp phát trên Heap
  // Phải sử dụng 'delete[]' cho mảng.
  delete[] dynamicArray;
  dynamicArray = nullptr; // Ngăn chặn lỗi sử dụng con trỏ lơ lửng

  // Lưu ý: Trong C++ hiện đại, nên sử dụng Smart Pointers (std::unique_ptr,
  // std::shared_ptr) để tự động hóa việc giải phóng bộ nhớ và ngăn chặn rò rỉ.
  // Ví dụ: auto modern_ptr = std::make_unique<int>(10);
  cout << "Bộ nhớ mảng động đã được giải phóng an toàn." << endl;
}
int main() {
  // Gọi các hàm minh họa từ các câu hỏi trước
  IllustratePointerUsage();

  return 0;
}