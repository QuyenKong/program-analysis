#include <iostream>
#include <string>
#include <vector>

using namespace std;

// --- PHẦN 7: MINH HỌA ĐÁNH CHỈ MỤC THỰC THI ---
// Đánh chỉ mục Thực thi gán một định danh duy nhất, được sắp xếp hoàn toàn (chỉ
// mục hoặc dấu thời gian) cho mọi sự kiện (lệnh, truy cập biến) trong một lần
// chạy chương trình cụ thể.
void IllustrateExecutionIndexing() {
  cout << "\n--- 7. MINH HỌA ĐÁNH CHỈ MỤC THỰC THI ---" << endl;

  struct TraceEvent {
    int index;
    string description;
  };

  vector<TraceEvent> trace;
  int indexCounter = 1;

  // Mô phỏng các lệnh và gán chỉ mục
  trace.push_back({indexCounter++, "Khởi tạo i = 0"});
  int i = 0;

  // Thực thi vòng lặp tạo ra nhiều sự kiện được đánh chỉ mục duy nhất
  while (i < 2) {
    trace.push_back({indexCounter++, "Kiểm tra điều kiện i < 2 (Đúng)"});
    i++;
    trace.push_back({indexCounter++, "Tăng i"});
  }
  trace.push_back({indexCounter++, "Kiểm tra điều kiện i < 2 (Sai)"});

  cout << "Các Sự kiện Truy vết Mô phỏng (Chỉ mục, Mô tả):" << endl;
  for (const auto &event : trace) {
    cout << "  [" << event.index << "] " << event.description << endl;
  }

  // Chỉ mục cho phép điều hướng xác định và theo dõi phụ thuộc.
  cout << "*Đánh chỉ mục thực thi cho phép 'du hành thời gian' chính xác và "
          "phân tích nhân quả trong gỡ lỗi.*"
       << endl;
  //
}
int main() {
  IllustrateExecutionIndexing();

  return 0;
}