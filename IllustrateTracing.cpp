#include <iostream>

using namespace std;

// --- PHẦN 5: MINH HỌA TRUY VẾT ---
// Truy vết ghi lại chuỗi các lệnh đã thực thi và trạng thái liên quan (giá trị
// biến) để tái tạo lịch sử thực thi của chương trình.
void IllustrateTracing() {
  cout << "\n--- 5. MINH HỌA TRUY VẾT ---" << endl;
  cout << "Mô phỏng ghi lại truy vết thực thi:" << endl;

  int a = 1; // Sự kiện Truy vết 1: a=1 (Dòng X)
  cout << "Sự kiện 1: Dòng X, a = " << a << endl;

  int b = 2; // Sự kiện Truy vết 2: b=2 (Dòng X+1)
  cout << "Sự kiện 2: Dòng X+1, b = " << b << endl;

  int sum = 0;

  for (int i = 0; i < 3; ++i) { // Sự kiện Truy vết (Các lần lặp)
    sum += a;                   // Sự kiện Truy vết (Gán)
    a++;                        // Sự kiện Truy vết (Thay đổi)
    // Lưu ý: Một truy vết thực sự ghi lại trạng thái biến tại các điểm này qua
    // các lần lặp.
  }

  cout << "Sự kiện truy vết cuối cùng: Thoát vòng lặp. Tổng cuối = " << sum
       << endl;
  cout << "Trạng thái cuối: a = " << a << ", sum = " << sum << endl;
  cout << "*Truy vết thu thập được là danh sách tuần tự các cặp (Dòng, Trạng "
          "thái) cho phép phát lại.*"
       << endl;
  //
}
int main() {
  // Gọi các hàm minh họa cho các câu hỏi mới (Phân tích Động)
  IllustrateTracing();

  return 0;
}