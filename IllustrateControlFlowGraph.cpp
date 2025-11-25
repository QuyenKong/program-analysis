#include <iostream>

using namespace std;

// --- PHẦN 2: MINH HỌA ĐỒ THỊ LUỒNG ĐIỀU KHIỂN (CFG) ---
// Đồ thị luồng điều khiển (CFG) là sơ đồ biểu diễn tất cả các đường đi có thể
// mà chương trình có thể thực thi.
// Các Node là các Khối Cơ bản (Basic Blocks) của mã nguồn.
// Các Edge là các bước nhảy hoặc rẽ nhánh điều khiển.
void IllustrateControlFlowGraph() {
  cout << "\n--- 2. MINH HỌA ĐỒ THỊ LUỒNG ĐIỀU KHIỂN (CFG) ---" << endl;
  cout << "Trực quan hóa luồng điều khiển bằng sơ đồ ASCII\n" << endl;

  int input = 15;
  cout << "Giá trị đầu vào: " << input << "\n" << endl;

  // In sơ đồ CFG TRƯỚC
  cout << "=== TRỰC QUAN HÓA ĐỒ THỊ LUỒNG ĐIỀU KHIỂN ===" << endl;
  cout << endl;
  cout << "                    ┌─────────────────┐" << endl;
  cout << "                    │  ENTRY (BẮT ĐẦU)│" << endl;
  cout << "                    └────────┬────────┘" << endl;
  cout << "                             │" << endl;
  cout << "                             ▼" << endl;
  cout << "                    ┌─────────────────┐" << endl;
  cout << "                    │  Node 1: KHỞI   │" << endl;
  cout << "                    │  TẠO result = 0 │" << endl;
  cout << "                    └────────┬────────┘" << endl;
  cout << "                             │" << endl;
  cout << "                             ▼" << endl;
  cout << "                    ┌─────────────────┐" << endl;
  cout << "                    │ Node 2: RẼ NHÁNH│" << endl;
  cout << "                    │  if(input > 10) │" << endl;
  cout << "                    └────────┬────────┘" << endl;
  cout << "                             │" << endl;
  cout << "           ┌─────────────────┼─────────────────┐" << endl;
  cout << "           │ ĐÚNG             │ SAI             │" << endl;
  cout << "           ▼                  ▼                 ▼" << endl;
  cout << "  ┌────────────────┐ ┌────────────────┐ ┌────────────────┐" << endl;
  cout << "  │  Node 3: ĐÚNG  │ │ Node 4: ELSE-IF│ │  Node 5: ELSE  │" << endl;
  cout << "  │ result=input*2 │ │ if(input < 5)  │ │ result = input │" << endl;
  cout << "  │                │ │ result=input+1 │ │                │" << endl;
  cout << "  └───────┬────────┘ └───────┬────────┘ └───────┬────────┘" << endl;
  cout << "          │                  │                  │" << endl;
  cout << "          └──────────────────┼──────────────────┘" << endl;
  cout << "                             │" << endl;
  cout << "                             ▼" << endl;
  cout << "                    ┌─────────────────┐" << endl;
  cout << "                    │  Node 6: HỢP    │" << endl;
  cout << "                    │  NHẤT - In kết  │" << endl;
  cout << "                    │  quả            │" << endl;
  cout << "                    └────────┬────────┘" << endl;
  cout << "                             │" << endl;
  cout << "                             ▼" << endl;
  cout << "                    ┌─────────────────┐" << endl;
  cout << "                    │  EXIT (KẾT THÚC)│" << endl;
  cout << "                    └─────────────────┘" << endl;
  cout << endl;

  cout << "=== THEO DÕI THỰC THI ===" << endl;

  // Bắt đầu (Entry Node) -> Node 1 (Khối cơ bản 1)
  cout << "\n[ENTRY] Bắt đầu thực thi chương trình" << endl;

  // Node 1: Khối cơ bản đầu tiên (không có nhảy vào/ra)
  int result = 0; // Câu lệnh A
  cout << "[Node 1] Khởi tạo: result = 0" << endl;

  // Edge 1: Kết nối Node 1 đến Node 2 (Node điều kiện)
  // Node 2: Khối quyết định
  cout << "[Node 2] Đánh giá điều kiện: input > 10 (" << input << " > 10)"
       << endl;

  if (input > 10) { // Điều kiện B - Rẽ nhánh
    // Edge 2: Từ Node 2 đến Node 3 (Nhánh đúng)
    // Node 3: Khối cơ bản cho trường hợp 'Đúng'
    cout << "         → Điều kiện ĐÚNG, đi theo đường đến Node 3" << endl;
    result = input * 2; // Câu lệnh C
    cout << "[Node 3] Thực thi: result = input * 2 = " << result << endl;

  } else if (input < 5) { // Điều kiện D - Rẽ nhánh
    // Edge 3: Từ Node 2 đến Node 4 (Nhánh sai của B, Điều kiện D)
    // Node 4: Khối quyết định thứ hai
    cout << "         → Điều kiện SAI, kiểm tra: input < 5" << endl;
    cout << "         → Điều kiện ĐÚNG, đi theo đường đến Node 4" << endl;
    result = input + 1; // Câu lệnh E
    cout << "[Node 4] Thực thi: result = input + 1 = " << result << endl;

  } else {
    // Edge 4: Từ Node 4 đến Node 5 (Nhánh sai của D)
    // Node 5: Khối cơ bản cho trường hợp 'Else'
    cout << "         → Điều kiện SAI, đi theo đường đến Node 5" << endl;
    result = input; // Câu lệnh F
    cout << "[Node 5] Thực thi: result = input = " << result << endl;
  }

  // Edges 5, 6, 7: Các nhánh (từ Node 3, 4, 5) đều hợp nhất tại Node 6
  // Node 6: Khối hợp nhất
  cout << "[Node 6] Điểm hợp nhất - Tất cả đường đi gặp nhau tại đây" << endl;
  cout << "         Kết quả cuối cùng: " << result << endl;

  // Kết thúc (Exit Node) -> Node 6
  cout << "[EXIT] Hoàn thành thực thi chương trình\n" << endl;

  // Tổng kết
  cout << "=== TỔNG KẾT PHÂN TÍCH CFG ===" << endl;
  cout << "Tổng số Node: 6 (Entry, Node1-5, Exit)" << endl;
  cout << "Tổng số Edge: 7" << endl;
  cout << "Các đường đi có thể:" << endl;
  cout << "  Đường 1: Entry → Node1 → Node2 → Node3 → Node6 → Exit" << endl;
  cout << "  Đường 2: Entry → Node1 → Node2 → Node4 → Node6 → Exit" << endl;
  cout << "  Đường 3: Entry → Node1 → Node2 → Node5 → Node6 → Exit" << endl;
  cout << "\n*CFG giúp các công cụ phân tích tĩnh xác định TẤT CẢ các luồng "
          "điều khiển*"
       << endl;
  cout << "*và đảm bảo rằng phân tích được áp dụng cho mọi đường đi có thể.*"
       << endl;
}
int main() {
  // Gọi các hàm minh họa từ các câu hỏi trước
  IllustrateControlFlowGraph();

  return 0;
}