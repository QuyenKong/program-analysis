#include <iostream>

using namespace std;

// --- PHẦN 1: MINH HỌA PHÂN TÍCH LUỒNG DỮ LIỆU ---
// Phân tích luồng dữ liệu (DFA) là kỹ thuật thu thập thông tin về khả năng
// thực thi của chương trình tại các điểm khác nhau. Ý tưởng cốt lõi là tính
// toán một "thuộc tính" được lan truyền qua Luồng Điều khiển. Ví dụ này minh
// họa ý tưởng phân tích "Định nghĩa Đạt được" (Reaching Definitions).
void IllustrateDataflowAnalysis() {
  cout << "--- 1. MINH HỌA PHÂN TÍCH LUỒNG DỮ LIỆU (Định nghĩa Đạt được) ---"
       << endl;

  // Giả sử chúng ta đang theo dõi các định nghĩa của biến 'x' và 'y'.

  // Một định nghĩa (d) là một câu lệnh gán.

  int x = 10; // d1: Định nghĩa 1 (x được định nghĩa là 10)
  // Tại điểm này, Định nghĩa Đạt được là: {d1}

  int y = 5; // d2: Định nghĩa 2 (y được định nghĩa là 5)
  // Tại điểm này, Định nghĩa Đạt được là: {d1, d2}

  if (y > 0) {
    x = x + 1; // d3: Định nghĩa 3 (x được định nghĩa lại)
    // Tại điểm này (bên trong khối if), Định nghĩa Đạt được là: {d2, d3}
    // (d1 bị loại bỏ vì x được định nghĩa lại)
  } else {
    y = y - 1; // d4: Định nghĩa 4 (y được định nghĩa lại)
    // Tại điểm này (bên trong khối else), Định nghĩa Đạt được là: {d1, d4}
    // (d2 bị loại bỏ vì y được định nghĩa lại)
  }

  // Sau khi khối if/else kết thúc (Điểm P):
  // Định nghĩa Đạt được là sự hợp nhất của các định nghĩa từ cả hai nhánh:
  // Nhánh If: {d2, d3}
  // Nhánh Else: {d1, d4}
  // Hợp nhất: {d1, d2, d3, d4}
  // *Phân tích chỉ ra rằng tại Điểm P, biến 'x' có thể đến từ d1 HOẶC d3,
  // và biến 'y' có thể đến từ d2 HOẶC d4.*
  // Đây là bản chất của DFA: thu thập thông tin xấp xỉ đúng tại các điểm chương
  // trình.
  cout << "Kết quả thực thi (không thể biết tĩnh x đến từ d1 hay d3): x = " << x
       << endl;
  //
}
int main() {
  // Gọi các hàm minh họa từ các câu hỏi trước
  IllustrateDataflowAnalysis();

  return 0;
}