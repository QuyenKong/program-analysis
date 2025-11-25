#include <iomanip>
#include <iostream>

using namespace std;

// --- PHẦN 8: MINH HỌA ĐỊNH VỊ LỖI ---
// Định vị Lỗi xác định các phần mã đáng ngờ có khả năng cao nhất
// chịu trách nhiệm cho lỗi, thường bằng cách so sánh độ bao phủ thực thi của
// các test đạt so với test lỗi.
void IllustrateFaultLocalization() {
  cout << "\n--- 8. MINH HỌA ĐỊNH VỊ LỖI ---" << endl;

  // Mô phỏng dữ liệu bao phủ cho 4 khối mã (B1: Khởi tạo, B2: Dễ lỗi, B3: An
  // toàn, B4: Cuối) T1: ĐẠT (1 test đạt) T2, T3: LỖI (2 test lỗi)

  // Dữ liệu Bao phủ: 1 nếu khối được thực thi, 0 nếu không.

  cout << "Kết quả Test và Bao phủ Khối (0=Bỏ qua, 1=Thực thi):" << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "Test | Kết quả | B1 (Khởi) | B2 (Lỗi) | B3 (An toàn) | B4 (Đầu ra) |"
       << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;
  cout << "T1   | ĐẠT    |     1     |      0      |     1     |      1      |"
       << endl;
  cout << "T2   | LỖI    |     1     |      1      |     0     |      1      |"
       << endl;
  cout << "T3   | LỖI    |     1     |      1      |     1     |      1      |"
       << endl;
  cout << "--------------------------------------------------------------------"
          "--"
       << endl;

  // Logic Định vị Lỗi Đơn giản (ví dụ: hệ số Ochiai):
  // Độ ngờ vực (B) = (Test lỗi bao phủ B) / sqrt(Tổng test lỗi * Tổng test bao
  // phủ B)

  // Tổng Test Lỗi (F): 2 (T2, T3)
  // Tổng Test Đạt (P): 1 (T1)

  // B2: Thực thi bởi F=2, Thực thi bởi P=0. Tổng bao phủ=2. Độ ngờ vực = 2 /
  // sqrt(2 * 2) = 1.0 B3: Thực thi bởi F=1 (T3), Thực thi bởi P=1 (T1). Tổng
  // bao phủ=2. Độ ngờ vực = 1 / sqrt(2 * 2) = 0.5

  cout << fixed << setprecision(2);
  cout << "\nKết luận Phân tích (dựa trên so sánh bao phủ):" << endl;
  cout << "Điểm Ngờ vực Khối B2 (Lỗi): 1.00" << endl;
  cout << "Điểm Ngờ vực Khối B3 (An toàn): 0.50" << endl;
  cout << "Khối B2 được thực thi bởi TẤT CẢ test lỗi nhưng KHÔNG có test đạt "
          "(T1)."
       << endl;
  cout << "*Định vị Lỗi xếp hạng B2 là vị trí có khả năng cao nhất có lỗi.*"
       << endl;
  //
}
int main() {
  // Gọi các hàm minh họa từ các câu hỏi trước
  IllustrateFaultLocalization();

  return 0;
}