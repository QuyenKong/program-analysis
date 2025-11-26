#include <iostream>
#include <memory>

using namespace std;

void IllustratePointerUsage() {
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

  // 2. Sử dụng Con trỏ cho Bộ nhớ Heap và Giải phóng
  int size = 5;
  int *dynamicArray = new int[size]; // Cấp phát một mảng 5 phần tử trên Heap
  for (int i = 0; i < size; ++i) {
    dynamicArray[i] = (i + 1) * 10;
  }
  cout << "Mảng Động trên Heap: " << dynamicArray[0] << ", " << dynamicArray[4] << "..." << endl;

  // QUAN TRỌNG: Giải phóng bộ nhớ mảng đã cấp phát trên Heap
  delete[] dynamicArray;
  dynamicArray = nullptr; // Ngăn chặn lỗi dangling pointer

  cout << "Bộ nhớ mảng động đã được giải phóng an toàn." << endl;
}

int main() {
  IllustratePointerUsage();
  return 0;
}
