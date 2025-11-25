#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// ============================================================================
// HỆ THỐNG RÚT TIỀN TỪ VÍ ĐIỆN TỬ - TÍCH HỢP TẤT CẢ KỸ THUẬT PHÂN TÍCH
// ============================================================================
// File này minh họa TẤT CẢ 8 kỹ thuật phân tích chương trình trong một
// tình huống thực tế: Module rút tiền từ ví điện tử
// ============================================================================

// --- CẤU TRÚC DỮ LIỆU ---
struct TraceEvent {
  int eventId;
  int lineNumber;
  string eventType;
  string description;
  string variableState;
};

struct TestCase {
  int testId;
  string testName;
  double initialBalance;
  double withdrawAmount;
  bool hasPin;
  bool expectedResult;
};

// --- BIẾN TOÀN CỤC ĐỂ TRUY VẾT ---
vector<TraceEvent> executionTrace;
int globalEventId = 0;

// --- HÀM TIỆN ÍCH: GHI LẠI TRUY VẾT ---
void recordTrace(int line, string type, string desc, double balance,
                 double amount, bool pinVerified) {
  stringstream ss;
  ss << "balance=" << fixed << setprecision(2) << balance
     << ", amount=" << amount
     << ", pinVerified=" << (pinVerified ? "true" : "false");

  executionTrace.push_back({++globalEventId, line, type, desc, ss.str()});
}

// ============================================================================
// HÀM CHÍNH: RÚT TIỀN TỪ VÍ
// ============================================================================
// Hàm này minh họa:
// 1. DATAFLOW ANALYSIS - Theo dõi định nghĩa biến
// 2. CONTROL FLOW GRAPH - Các nhánh điều kiện
// 3. MEMORY ALLOCATION - Quản lý bộ nhớ động
// 4. POINTER USAGE - Sử dụng con trỏ
// 5. TRACING - Ghi lại lịch sử thực thi
// 6. DYNAMIC SLICING - Phụ thuộc dữ liệu và điều khiển
// 7. EXECUTION INDEXING - Đánh số sự kiện
// 8. FAULT LOCALIZATION - Phát hiện lỗi
// ============================================================================

bool withdrawFromWallet(double *balance, double amount, bool pinVerified) {
  cout << "\n=== BẮT ĐẦU GIAO DỊCH RÚT TIỀN ===" << endl;
  cout << "Số dư hiện tại: " << fixed << setprecision(2) << *balance << " VND"
       << endl;
  cout << "Số tiền muốn rút: " << amount << " VND" << endl;
  cout << "PIN đã xác thực: " << (pinVerified ? "Có" : "Không") << "\n" << endl;

  // --- PHẦN 1: DATAFLOW ANALYSIS ---
  // Theo dõi các định nghĩa của biến balance, amount, pinVerified

  // d1: balance được truyền vào (tham chiếu qua con trỏ)
  // d2: amount được truyền vào (giá trị)
  // d3: pinVerified được truyền vào (giá trị)
  recordTrace(100, "INIT", "Khởi tạo tham số", *balance, amount, pinVerified);

  double originalBalance = *balance; // d4: Định nghĩa originalBalance
  recordTrace(101, "ASSIGN", "Lưu số dư gốc", *balance, amount, pinVerified);

  double fee = 0.0;         // d5: Định nghĩa fee
  bool canWithdraw = false; // d6: Định nghĩa canWithdraw
  recordTrace(102, "ASSIGN", "Khởi tạo fee và canWithdraw", *balance, amount,
              pinVerified);

  // --- PHẦN 2: CONTROL FLOW GRAPH ---
  // Vẽ CFG cho luồng điều khiển

  cout << "--- ĐỒ THỊ LUỒNG ĐIỀU KHIỂN (CFG) ---" << endl;
  cout << "Node 1 (ENTRY) → Node 2 (Kiểm tra PIN)" << endl;

  // Node 2: Kiểm tra PIN
  if (!pinVerified) { // S1: Điều kiện rẽ nhánh
    recordTrace(110, "BRANCH", "if (!pinVerified) → TRUE", *balance, amount,
                pinVerified);

    // Node 3: Nhánh lỗi - PIN không đúng
    cout << "  → Node 3: PIN không hợp lệ (EARLY RETURN)" << endl;
    cout << "❌ THẤT BẠI: PIN chưa được xác thực!" << endl;
    recordTrace(111, "ERROR", "Lỗi: PIN không hợp lệ", *balance, amount,
                pinVerified);
    return false; // Early exit
  }

  recordTrace(115, "BRANCH", "if (!pinVerified) → FALSE, tiếp tục", *balance,
              amount, pinVerified);
  cout << "  → Node 4: PIN hợp lệ, kiểm tra số tiền" << endl;

  // Node 4: Kiểm tra số tiền hợp lệ
  if (amount <= 0) { // S2: Điều kiện rẽ nhánh
    recordTrace(120, "BRANCH", "if (amount <= 0) → TRUE", *balance, amount,
                pinVerified);

    // Node 5: Nhánh lỗi - Số tiền không hợp lệ
    cout << "  → Node 5: Số tiền không hợp lệ" << endl;
    cout << "❌ THẤT BẠI: Số tiền phải lớn hơn 0!" << endl;
    recordTrace(121, "ERROR", "Lỗi: Số tiền <= 0", *balance, amount,
                pinVerified);
    return false;
  }

  recordTrace(125, "BRANCH", "if (amount <= 0) → FALSE, tiếp tục", *balance,
              amount, pinVerified);
  cout << "  → Node 6: Số tiền hợp lệ, tính phí" << endl;

  // --- PHẦN 3 & 4: MEMORY ALLOCATION & POINTER USAGE ---
  // Minh họa cấp phát bộ nhớ động và sử dụng con trỏ

  cout << "\n--- QUẢN LÝ BỘ NHỚ VÀ CON TRỎ ---" << endl;
  cout << "Con trỏ balance:" << endl;
  cout << "  - Địa chỉ con trỏ: " << &balance << " (trên Stack)" << endl;
  cout << "  - Trỏ đến: " << balance << " (địa chỉ biến balance)" << endl;
  cout << "  - Giá trị tại địa chỉ (*balance): " << *balance << " VND" << endl;

  // Cấp phát mảng động để lưu lịch sử giao dịch
  int *transactionHistory = new int[3]; // Cấp phát trên Heap
  transactionHistory[0] = 1001;         // ID giao dịch
  transactionHistory[1] = (int)amount;
  transactionHistory[2] = (int)*balance;

  cout << "\nCấp phát bộ nhớ động (Heap) cho lịch sử giao dịch:" << endl;
  cout << "  - Địa chỉ mảng: " << transactionHistory << endl;
  cout << "  - transactionHistory[0] (ID): " << transactionHistory[0] << endl;

  // Node 6: Tính phí giao dịch
  if (amount > 1000000) { // S3: Điều kiện phí cao
    fee = amount * 0.02;  // d7: Định nghĩa lại fee (2%)
    recordTrace(130, "COMPUTE", "Phí 2% cho giao dịch lớn", *balance, amount,
                pinVerified);
    cout << "  → Node 7: Giao dịch lớn, phí 2% = " << fee << " VND" << endl;
  } else if (amount > 500000) { // S4: Điều kiện phí trung bình
    fee = amount * 0.01;        // d8: Định nghĩa lại fee (1%)
    recordTrace(135, "COMPUTE", "Phí 1% cho giao dịch trung bình", *balance,
                amount, pinVerified);
    cout << "  → Node 8: Giao dịch trung bình, phí 1% = " << fee << " VND"
         << endl;
  } else {      // S5: Phí cố định
    fee = 5000; // d9: Định nghĩa lại fee (cố định)
    recordTrace(140, "COMPUTE", "Phí cố định 5000 VND", *balance, amount,
                pinVerified);
    cout << "  → Node 9: Giao dịch nhỏ, phí cố định = " << fee << " VND"
         << endl;
  }

  double totalAmount = amount + fee; // d10: Định nghĩa totalAmount
  recordTrace(145, "COMPUTE", "Tổng tiền = amount + fee", *balance, amount,
              pinVerified);
  cout << "\nTổng tiền cần trừ (gồm phí): " << totalAmount << " VND" << endl;

  // Node 10: Kiểm tra số dư
  if (*balance < totalAmount) { // S6: Điều kiện số dư không đủ
    recordTrace(150, "BRANCH", "if (*balance < totalAmount) → TRUE", *balance,
                amount, pinVerified);

    // Node 11: Nhánh lỗi - Số dư không đủ
    cout << "  → Node 11: Số dư không đủ" << endl;
    cout << "❌ THẤT BẠI: Số dư không đủ! (Cần: " << totalAmount
         << ", Có: " << *balance << ")" << endl;
    recordTrace(151, "ERROR", "Lỗi: Số dư không đủ", *balance, amount,
                pinVerified);

    // Giải phóng bộ nhớ trước khi return
    delete[] transactionHistory;
    return false;
  }

  recordTrace(155, "BRANCH", "if (*balance < totalAmount) → FALSE, đủ tiền",
              *balance, amount, pinVerified);
  cout << "  → Node 12: Số dư đủ, thực hiện rút tiền" << endl;

  // --- PHẦN 4: POINTER USAGE (Cập nhật qua con trỏ) ---
  // Node 12: Thực hiện rút tiền (cập nhật balance qua con trỏ)
  cout << "\n--- CẬP NHẬT QUA CON TRỎ ---" << endl;
  cout << "Trước khi cập nhật:" << endl;
  cout << "  *balance = " << *balance << " VND" << endl;

  *balance =
      *balance - totalAmount; // d11: Định nghĩa lại balance (qua con trỏ)
  recordTrace(160, "UPDATE", "Cập nhật balance qua con trỏ", *balance, amount,
              pinVerified);

  cout << "Sau khi cập nhật (*balance -= totalAmount):" << endl;
  cout << "  *balance = " << *balance << " VND" << endl;
  cout << "  → Biến gốc đã được thay đổi qua con trỏ!" << endl;

  canWithdraw = true; // d12: Định nghĩa lại canWithdraw
  recordTrace(165, "SUCCESS", "Giao dịch thành công", *balance, amount,
              pinVerified);

  // Giải phóng bộ nhớ động
  delete[] transactionHistory;
  transactionHistory = nullptr;
  cout << "\nĐã giải phóng bộ nhớ động (Heap)" << endl;

  // Node 13: Exit (Success)
  cout << "\n✅ THÀNH CÔNG: Đã rút " << amount << " VND" << endl;
  cout << "Phí giao dịch: " << fee << " VND" << endl;
  cout << "Số dư mới: " << *balance << " VND" << endl;
  cout << "  → Node 13: EXIT (SUCCESS)" << endl;

  return canWithdraw;
}

// ============================================================================
// PHẦN 5: TRACING - HIỂN THỊ LỊCH SỬ THỰC THI
// ============================================================================
void displayExecutionTrace() {
  cout << "\n\n" << string(80, '=') << endl;
  cout << "=== PHẦN 5: TRUY VẾT THỰC THI (EXECUTION TRACE) ===" << endl;
  cout << string(80, '=') << endl;

  cout << "\nLịch sử thực thi đầy đủ:" << endl;
  cout << string(80, '-') << endl;
  cout << "[ID] Line | Type      | Description" << endl;
  cout << string(80, '-') << endl;

  for (const auto &event : executionTrace) {
    cout << "[" << setw(2) << event.eventId << "] L" << setw(3)
         << event.lineNumber << " | " << setw(9) << left << event.eventType
         << " | " << event.description << endl;
    cout << "     State: " << event.variableState << endl;
  }

  cout << string(80, '-') << endl;
  cout << "Tổng số sự kiện: " << executionTrace.size() << endl;
}

// ============================================================================
// PHẦN 6: DYNAMIC SLICING - PHÂN TÍCH PHỤ THUỘC
// ============================================================================
void performDynamicSlicing() {
  cout << "\n\n" << string(80, '=') << endl;
  cout << "=== PHẦN 6: CẮT LÁT ĐỘNG (DYNAMIC SLICING) ===" << endl;
  cout << string(80, '=') << endl;

  cout
      << "\nTiêu chí cắt lát: <balance, dòng 160> (giá trị balance sau khi rút)"
      << endl;
  cout << "\nCâu hỏi: Những câu lệnh nào ảnh hưởng đến giá trị cuối của "
          "balance?\n"
       << endl;

  cout << "Phân tích phụ thuộc ngược (Backward slicing):" << endl;
  cout << string(80, '-') << endl;

  vector<string> slice = {
      "L160: *balance = *balance - totalAmount (Cập nhật trực tiếp)",
      "L145: totalAmount = amount + fee (Phụ thuộc dữ liệu)",
      "L130-140: fee = ... (Phụ thuộc dữ liệu - tính phí)",
      "L130: if (amount > 1000000) (Phụ thuộc điều khiển)",
      "L100: amount (Tham số đầu vào)",
      "L100: balance (Tham số đầu vào - con trỏ)",
      "L110: if (!pinVerified) (Phụ thuộc điều khiển)",
      "L120: if (amount <= 0) (Phụ thuộc điều khiển)",
      "L150: if (*balance < totalAmount) (Phụ thuộc điều khiển)"};

  cout << "Cắt lát động (các câu lệnh đã thực thi ảnh hưởng đến balance):"
       << endl;
  for (size_t i = 0; i < slice.size(); i++) {
    cout << "  " << (i + 1) << ". " << slice[i] << endl;
  }

  cout << "\nCác câu lệnh KHÔNG trong cắt lát (không ảnh hưởng):" << endl;
  cout << "  - L101: originalBalance = *balance (chỉ để tham chiếu)" << endl;
  cout << "  - L102: canWithdraw = false (bị ghi đè sau)" << endl;
  cout << "  - transactionHistory (chỉ để demo, không ảnh hưởng logic)" << endl;
}

// ============================================================================
// PHẦN 7: EXECUTION INDEXING - PHÂN TÍCH THỜI GIAN
// ============================================================================
void analyzeExecutionIndexing() {
  cout << "\n\n" << string(80, '=') << endl;
  cout << "=== PHẦN 7: ĐÁNH CHỈ MỤC THỰC THI (EXECUTION INDEXING) ===" << endl;
  cout << string(80, '=') << endl;

  cout << "\nMỗi sự kiện có chỉ mục duy nhất cho phép:" << endl;
  cout << "  1. Du hành thời gian (time-travel debugging)" << endl;
  cout << "  2. Tìm kiếm sự kiện cụ thể" << endl;
  cout << "  3. Phân tích nhân quả\n" << endl;

  cout << "Ví dụ phân tích:" << endl;
  cout << string(80, '-') << endl;

  // Tìm tất cả sự kiện BRANCH
  cout << "\n1. Tất cả điểm rẽ nhánh (BRANCH events):" << endl;
  for (const auto &event : executionTrace) {
    if (event.eventType == "BRANCH") {
      cout << "   [" << event.eventId << "] " << event.description << endl;
    }
  }

  // Tìm sự kiện thay đổi balance
  cout << "\n2. Sự kiện thay đổi balance:" << endl;
  for (const auto &event : executionTrace) {
    if (event.eventType == "UPDATE") {
      cout << "   [" << event.eventId << "] " << event.description << endl;
      cout << "      " << event.variableState << endl;
    }
  }

  cout << "\n3. Du hành đến sự kiện #5:" << endl;
  if (executionTrace.size() >= 5) {
    auto &event = executionTrace[4]; // Index 4 = event 5
    cout << "   Mô tả: " << event.description << endl;
    cout << "   Trạng thái: " << event.variableState << endl;
  }
}

// ============================================================================
// PHẦN 8: FAULT LOCALIZATION - PHÁT HIỆN LỖI
// ============================================================================
void performFaultLocalization() {
  cout << "\n\n" << string(80, '=') << endl;
  cout << "=== PHẦN 8: ĐỊNH VỊ LỖI (FAULT LOCALIZATION) ===" << endl;
  cout << string(80, '=') << endl;

  // Tạo các test case
  vector<TestCase> tests = {
      {1, "Test rút tiền bình thường", 1000000, 100000, true, true},
      {2, "Test không có PIN", 1000000, 100000, false, false},
      {3, "Test số dư không đủ", 50000, 100000, true, false},
      {4, "Test số tiền âm", 1000000, -50000, true, false},
      {5, "Test rút 0 đồng", 1000000, 0, true, false},
      {6, "Test rút tiền lớn", 5000000, 2000000, true, true}};

  // Ma trận bao phủ: [test][block]
  // Blocks: B1=PIN check, B2=Amount check, B3=Fee calc, B4=Balance check,
  // B5=Withdraw
  vector<vector<int>> coverage = {
      {1, 1, 1, 1, 1}, // T1: PASS - tất cả block
      {1, 0, 0, 0, 0}, // T2: FAIL - chỉ B1 (lỗi PIN)
      {1, 1, 1, 1, 0}, // T3: FAIL - đến B4 (lỗi số dư)
      {1, 1, 0, 0, 0}, // T4: FAIL - đến B2 (lỗi số tiền âm)
      {1, 1, 0, 0, 0}, // T5: FAIL - đến B2 (lỗi số tiền = 0)
      {1, 1, 1, 1, 1}  // T6: PASS - tất cả block
  };

  cout << "\nKết quả Test Cases:" << endl;
  cout << string(80, '-') << endl;
  cout << "ID | Tên Test                    | Kết quả" << endl;
  cout << string(80, '-') << endl;

  int passCount = 0, failCount = 0;
  for (const auto &test : tests) {
    string result = test.expectedResult ? "PASS" : "FAIL";
    if (test.expectedResult)
      passCount++;
    else
      failCount++;
    cout << "T" << test.testId << " | " << setw(27) << left << test.testName
         << " | " << result << endl;
  }

  cout << string(80, '-') << endl;
  cout << "Tổng: " << passCount << " PASS, " << failCount << " FAIL" << endl;

  // Tính Ochiai coefficient
  vector<string> blockNames = {"B1: Kiểm tra PIN", "B2: Kiểm tra số tiền",
                               "B3: Tính phí", "B4: Kiểm tra số dư",
                               "B5: Thực hiện rút tiền"};

  cout << "\nPhân tích Ochiai Coefficient:" << endl;
  cout << string(80, '-') << endl;

  vector<double> suspiciousness(5);
  for (int block = 0; block < 5; block++) {
    int failedAndExecuted = 0;
    int totalExecuted = 0;

    for (int test = 0; test < 6; test++) {
      if (coverage[test][block]) {
        totalExecuted++;
        if (!tests[test].expectedResult) {
          failedAndExecuted++;
        }
      }
    }

    if (totalExecuted > 0 && failCount > 0) {
      suspiciousness[block] =
          failedAndExecuted / sqrt(failCount * totalExecuted);
    }

    cout << blockNames[block] << endl;
    cout << "  Thực thi bởi " << failedAndExecuted << " test lỗi / "
         << totalExecuted << " test tổng" << endl;
    cout << "  Điểm ngờ vực: " << fixed << setprecision(3)
         << suspiciousness[block] << endl;
  }

  cout << "\n" << string(80, '=') << endl;
  cout << "KẾT LUẬN: Các block có điểm ngờ vực cao nhất cần kiểm tra kỹ!"
       << endl;
  cout << string(80, '=') << endl;
}

// ============================================================================
// HÀM MAIN - CHẠY DEMO
// ============================================================================
int main() {
  cout << string(80, '=') << endl;
  cout << "   HỆ THỐNG RÚT TIỀN TỪ VÍ ĐIỆN TỬ" << endl;
  cout << "   Tích hợp 8 kỹ thuật phân tích chương trình" << endl;
  cout << string(80, '=') << endl;

  // Kịch bản: Rút 800,000 VND từ ví có 2,000,000 VND
  double walletBalance = 2000000.0;
  double withdrawAmount = 800000.0;
  bool pinVerified = true;

  // Thực hiện giao dịch
  bool success =
      withdrawFromWallet(&walletBalance, withdrawAmount, pinVerified);

  // Hiển thị kết quả cuối
  cout << "\n" << string(80, '=') << endl;
  cout << "KẾT QUẢ GIAO DỊCH" << endl;
  cout << string(80, '=') << endl;
  cout << "Trạng thái: " << (success ? "✅ THÀNH CÔNG" : "❌ THẤT BẠI") << endl;
  cout << "Số dư ví sau giao dịch: " << fixed << setprecision(2)
       << walletBalance << " VND" << endl;

  // Phân tích chi tiết
  displayExecutionTrace();
  performDynamicSlicing();
  analyzeExecutionIndexing();
  performFaultLocalization();

  cout << "\n" << string(80, '=') << endl;
  cout << "HOÀN THÀNH DEMO - ĐÃ MINH HỌA TẤT CẢ 8 KỸ THUẬT!" << endl;
  cout << string(80, '=') << endl;

  return 0;
}
