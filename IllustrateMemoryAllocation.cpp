#include <iostream>

using namespace std;

// --- PHẦN 3: MINH HỌA CẤP PHÁT VÀ GIẢI PHÓNG BỘ NHỚ ---
// Minh họa sự khác biệt giữa cấp phát Stack (Bộ nhớ Tĩnh) và Heap (Bộ nhớ
// Động).
void IllustrateMemoryAllocation() {
  cout << "\n--- 3. MINH HỌA CẤP PHÁT VÀ GIẢI PHÓNG BỘ NHỚ ---" << endl;

  // 1. Cấp phát STACK (Bộ nhớ Tĩnh)
  // Các biến được cấp phát khi hàm được gọi và tự động giải phóng
  // khi hàm kết thúc.
  int stackVariable = 100; // Cấp phát trên Stack
  cout << "Stack: Biến 'stackVariable' = " << stackVariable
       << " (Tự động Giải phóng)" << endl;

  // 2. Cấp phát HEAP (Bộ nhớ Động)
  // Yêu cầu sử dụng toán tử 'new' và quản lý thủ công (hoặc Smart Pointers).
  // Kích thước có thể không biết tại thời điểm biên dịch.

  // Cấp phát bộ nhớ cho một số nguyên trên Heap
  int *heapPtr = new int(200); // Cấp phát trên Heap (Cấp phát Động)
  cout << "Heap: Giá trị vùng nhớ đã cấp phát: " << *heapPtr << endl;

  // Giải phóng bộ nhớ Heap
  // Nếu không có lệnh 'delete', bộ nhớ này sẽ bị rò rỉ (memory leak).
  delete heapPtr;    // Giải phóng bộ nhớ Heap
  heapPtr = nullptr; // Đặt con trỏ về NULL để tránh sử dụng con trỏ lơ lửng

  cout << "Heap: Vùng nhớ đã cấp phát đã được giải phóng. (Quản lý Thủ công)"
       << endl;
  // [Hình ảnh mô hình bộ nhớ Stack và Heap]
}
int main() {
  // Gọi các hàm minh họa từ các câu hỏi trước
  IllustrateMemoryAllocation();

  return 0;
}