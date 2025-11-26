#include <iostream>

using namespace std;

// Biến có thời gian sống tĩnh ở phạm vi tệp (tồn tại suốt chương trình)
static int g_staticFileScope = 42; // Tĩnh (Static): cấp phát trước khi chạy

void IllustrateMemoryAllocation() {
  // 1) TĨNH (STATIC)
  static int staticLocalCounter = 0; // cũng là bộ nhớ tĩnh, lưu qua nhiều lần gọi
  ++staticLocalCounter;
  cout << "Tĩnh (Static): g_staticFileScope = " << g_staticFileScope
      << ", staticLocalCounter sau khi ++ = " << staticLocalCounter << endl;

  // 2) ĐỘNG TỰ ĐỘNG (AUTOMATIC - STACK)
  int stackVariable = 100; // Automatic trên Stack
  cout << "Động tự động (Stack): stackVariable = " << stackVariable
      << " (Tự động giải phóng khi ra khỏi hàm)" << endl;

  // 3) ĐỘNG ĐIỀU KHIỂN BỞI CHƯƠNG TRÌNH (PROGRAM CONTROLLED - HEAP)
  int *heapPtr = new int(200); // Cấp phát trên Heap
  cout << "Động điều khiển (Heap): Giá trị được cấp phát = " << *heapPtr << endl;

  // Giải phóng vùng nhớ Heap được cấp phát thủ công
  delete heapPtr; // nếu quên sẽ gây rò rỉ bộ nhớ
  heapPtr = nullptr; // tránh con trỏ lơ lửng
  cout << "Động điều khiển (Heap): Đã giải phóng vùng nhớ" << endl;
}

int main() {
  // Gọi 2 lần để thấy biến tĩnh giữ giá trị giữa các lần gọi
  IllustrateMemoryAllocation();
  IllustrateMemoryAllocation();
  return 0;
}
