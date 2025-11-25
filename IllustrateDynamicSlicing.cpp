#include <iostream>

using namespace std;

// --- PHẦN 6: MINH HỌA CẮT LÁT ĐỘNG ---
// Cắt lát Động tính toán tập hợp các câu lệnh thực sự ảnh hưởng đến giá trị của
// biến tại một điểm cụ thể trong một lần thực thi cụ thể (tiêu chí cắt lát).
void IllustrateDynamicSlicing() {
  cout << "\n--- 6. MINH HỌA CẮT LÁT ĐỘNG ---" << endl;

  int x = 10; // Câu lệnh S1
  int y = 5;  // Câu lệnh S2
  int z = 0;  // Câu lệnh S3

  // Câu lệnh điều kiện (Phụ thuộc Điều khiển)
  if (x > y) { // Câu lệnh S4
    z = x + 1; // Câu lệnh S5 (Được thực thi)
  } else {
    z = y + 1; // Câu lệnh S6 (Bị bỏ qua)
  }

  x = z * 2; // Câu lệnh S7 (Điểm Tiêu chí Cắt lát)

  // Đường đi thực thi: S1 -> S2 -> S3 -> S4 (Đúng) -> S5 -> S7

  // Cắt lát Động (các câu lệnh liên quan):
  // Giá trị của 'x' tại S7 phụ thuộc vào 'z' (S5).
  // Việc thực thi S5 phụ thuộc vào điều kiện S4.
  // S5 phụ thuộc vào giá trị 'x' ban đầu (S1).
  // S2 và S3 không liên quan trong lần chạy cụ thể này.

  cout << "Giá trị đầu ra 'x' = " << x << endl;
  cout << "Cắt lát Động cho 'x' tại S7 (Thực thi Cụ thể):" << endl;
  cout << "  - S7: x = z * 2 (Đầu ra)" << endl;
  cout << "  - S5: z = x + 1 (Phụ thuộc Dữ liệu vào z)" << endl;
  cout << "  - S4: if (x > y) (Phụ thuộc Điều khiển)" << endl;
  cout << "  - S1: x = 10 (Định nghĩa ban đầu của x)" << endl;

  cout << "*Cắt lát Động cô lập tập hợp tối thiểu mã đã thực thi chịu trách "
          "nhiệm cho hành vi quan sát được.*"
       << endl;
  //
}

int main() {
  IllustrateDynamicSlicing();

  return 0;
}