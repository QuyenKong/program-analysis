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

// --- BIẾN TOÀN CỤC ---
vector<TraceEvent> executionTrace;
int globalEventId = 0;

// --- HÀM GHI TRUY VẾT ---
void recordTrace(int line, string type, string desc, double balance,
                 double amount, bool pinVerified) {
  stringstream ss;
  ss << "balance=" << fixed << setprecision(2) << balance
     << ", amount=" << amount
     << ", pinVerified=" << (pinVerified ? "true" : "false");

  executionTrace.push_back({++globalEventId, line, type, desc, ss.str()});
}

// --- VẼ ĐỒ THỊ CFG ---
void displayCFG() {
  cout << "\n" << string(80, '=') << endl;
  cout << "ĐỒ THỊ LUỒNG ĐIỀU KHIỂN (CONTROL FLOW GRAPH)" << endl;
  cout << string(80, '=') << endl;
  cout << endl;

  cout << "                         ┌──────────────────┐" << endl;
  cout << "                         │  Node 1: ENTRY   │" << endl;
  cout << "                         │  (Bắt đầu)       │" << endl;
  cout << "                         └────────┬─────────┘" << endl;
  cout << "                                  │" << endl;
  cout << "                                  ▼" << endl;
  cout << "                         ┌──────────────────┐" << endl;
  cout << "                         │  Node 2: CHECK   │" << endl;
  cout << "                         │  if(!pinVerified)│" << endl;
  cout << "                         └────────┬─────────┘" << endl;
  cout << "                                  │" << endl;
  cout << "                 ┌────────────────┼────────────────┐" << endl;
  cout << "                 │ TRUE                        FALSE│" << endl;
  cout << "                 ▼                                  ▼" << endl;
  cout << "        ┌─────────────────┐              ┌──────────────────┐"
       << endl;
  cout << "        │  Node 3: ERROR  │              │  Node 4: CHECK   │"
       << endl;
  cout << "        │  PIN không hợp  │              │  if(amount <= 0) │"
       << endl;
  cout << "        │  lệ             │              └────────┬─────────┘"
       << endl;
  cout << "        └────────┬────────┘                       │" << endl;
  cout << "                 │                   ┌────────────┼────────────┐"
       << endl;
  cout << "                 │                   │ TRUE                FALSE│"
       << endl;
  cout << "                 │                   ▼                          ▼"
       << endl;
  cout << "                 │          ┌─────────────────┐      "
          "┌──────────────────┐"
       << endl;
  cout << "                 │          │  Node 5: ERROR  │      │  Node 6-9: "
          "FEE   │"
       << endl;
  cout << "                 │          │  Số tiền không  │      │  Tính phí "
          "giao   │"
       << endl;
  cout << "                 │          │  hợp lệ         │      │  dịch "
          "(if-else)  │"
       << endl;
  cout << "                 │          └────────┬────────┘      "
          "└────────┬─────────┘"
       << endl;
  cout << "                 │                   │                        │"
       << endl;
  cout << "                 │                   │                        ▼"
       << endl;
  cout << "                 │                   │              "
          "┌──────────────────┐"
       << endl;
  cout << "                 │                   │              │ Node 10: "
          "CHECK   │"
       << endl;
  cout << "                 │                   │              │ if(balance <  "
          "   │"
       << endl;
  cout << "                 │                   │              │    "
          "totalAmount)  │"
       << endl;
  cout << "                 │                   │              "
          "└────────┬─────────┘"
       << endl;
  cout << "                 │                   │                       │"
       << endl;
  cout << "                 │                   │          "
          "┌────────────┼──────────┐"
       << endl;
  cout << "                 │                   │          │ TRUE              "
          "FALSE│"
       << endl;
  cout << "                 │                   │          ▼                   "
          "     ▼"
       << endl;
  cout << "                 │                   │  ┌────────────────┐    "
          "┌──────────────────┐"
       << endl;
  cout << "                 │                   │  │ Node 11: ERROR │    │ "
          "Node 12: SUCCESS │"
       << endl;
  cout << "                 │                   │  │ Số dư không đủ │    │ "
          "Thực hiện rút    │"
       << endl;
  cout << "                 │                   │  └───────┬────────┘    │ "
          "tiền             │"
       << endl;
  cout << "                 │                   │          │             "
          "└────────┬─────────┘"
       << endl;
  cout << "                 │                   │          │                   "
          "   │"
       << endl;
  cout << "                 │                   │          │                   "
          "   ▼"
       << endl;
  cout << "                 │                   │          │            "
          "┌──────────────────┐"
       << endl;
  cout << "                 │                   │          │            │ Node "
          "13: EXIT    │"
       << endl;
  cout << "                 │                   │          │            │ "
          "(Thành công)     │"
       << endl;
  cout << "                 │                   │          │            "
          "└────────┬─────────┘"
       << endl;
  cout << "                 │                   │          │                   "
          "  │"
       << endl;
  cout << "                 "
          "└───────────────────┴──────────┴─────────────────────┘"
       << endl;
  cout << "                                              │" << endl;
  cout << "                                              ▼" << endl;
  cout << "                                    ┌──────────────────┐" << endl;
  cout << "                                    │  EXIT PROGRAM    │" << endl;
  cout << "                                    └──────────────────┘" << endl;
  cout << endl;
  cout << "Tổng số Node: 13" << endl;
  cout << "Tổng số Edge: 16" << endl;
  cout << "Số đường đi có thể: 4 (1 thành công, 3 thất bại)" << endl;
  cout << string(80, '=') << endl;
}

// ============================================================================
// HÀM CHÍNH: RÚT TIỀN TỪ VÍ
// ============================================================================
bool withdrawFromWallet(double *balance, double amount, bool pinVerified) {
  cout << "\n=== BẮT ĐẦU GIAO DỊCH RÚT TIỀN ===" << endl;
  cout << "Số dư hiện tại: " << fixed << setprecision(2) << *balance << " VND"
       << endl;
  cout << "Số tiền muốn rút: " << amount << " VND" << endl;
  cout << "PIN đã xác thực: " << (pinVerified ? "Có" : "Không") << "\n" << endl;

  // Hiển thị CFG
  displayCFG();

  // --- PHẦN 1: DATAFLOW ANALYSIS ---
  recordTrace(100, "INIT", "Khởi tạo tham số", *balance, amount, pinVerified);

  double originalBalance = *balance;
  recordTrace(101, "ASSIGN", "Lưu số dư gốc", *balance, amount, pinVerified);

  double fee = 0.0;
  bool canWithdraw = false;
  recordTrace(102, "ASSIGN", "Khởi tạo fee và canWithdraw", *balance, amount,
              pinVerified);

  cout << "\n--- THEO DÕI THỰC THI QUA CFG ---" << endl;
  cout << "Đi qua: Node 1 (ENTRY)" << endl;

  // Node 2: Kiểm tra PIN
  cout << "Đi qua: Node 2 (Kiểm tra PIN)" << endl;
  if (!pinVerified) {
    recordTrace(110, "BRANCH", "if (!pinVerified) → TRUE", *balance, amount,
                pinVerified);
    cout << "  → Rẽ nhánh TRUE → Node 3 (ERROR)" << endl;
    cout << "❌ THẤT BẠI: PIN chưa được xác thực!" << endl;
    recordTrace(111, "ERROR", "Lỗi: PIN không hợp lệ", *balance, amount,
                pinVerified);
    cout << "Đi qua: EXIT PROGRAM" << endl;
    return false;
  }

  recordTrace(115, "BRANCH", "if (!pinVerified) → FALSE", *balance, amount,
              pinVerified);
  cout << "  → Rẽ nhánh FALSE → Node 4 (Kiểm tra số tiền)" << endl;

  // Node 4: Kiểm tra số tiền
  cout << "Đi qua: Node 4 (Kiểm tra số tiền)" << endl;
  if (amount <= 0) {
    recordTrace(120, "BRANCH", "if (amount <= 0) → TRUE", *balance, amount,
                pinVerified);
    cout << "  → Rẽ nhánh TRUE → Node 5 (ERROR)" << endl;
    cout << "❌ THẤT BẠI: Số tiền phải lớn hơn 0!" << endl;
    recordTrace(121, "ERROR", "Lỗi: Số tiền <= 0", *balance, amount,
                pinVerified);
    cout << "Đi qua: EXIT PROGRAM" << endl;
    return false;
  }

  recordTrace(125, "BRANCH", "if (amount <= 0) → FALSE", *balance, amount,
              pinVerified);
  cout << "  → Rẽ nhánh FALSE → Node 6-9 (Tính phí)" << endl;

  // --- PHẦN 3 & 4: MEMORY & POINTER ---
  cout << "\n--- QUẢN LÝ BỘ NHỚ VÀ CON TRỎ ---" << endl;
  cout << "Con trỏ balance:" << endl;
  cout << "  - Địa chỉ con trỏ: " << &balance << " (Stack)" << endl;
  cout << "  - Trỏ đến: " << balance << endl;
  cout << "  - Giá trị (*balance): " << *balance << " VND" << endl;

  int *transactionHistory = new int[3];
  transactionHistory[0] = 1001;
  transactionHistory[1] = (int)amount;
  transactionHistory[2] = (int)*balance;

  cout << "Cấp phát Heap: transactionHistory tại " << transactionHistory
       << endl;

  // Node 6-9: Tính phí
  cout << "\nĐi qua: Node 6-9 (Tính phí theo điều kiện)" << endl;
  if (amount > 1000000) {
    fee = amount * 0.02;
    recordTrace(130, "COMPUTE", "Phí 2% cho giao dịch lớn", *balance, amount,
                pinVerified);
    cout << "  → Giao dịch lớn (>1M): Phí 2% = " << fee << " VND" << endl;
  } else if (amount > 500000) {
    fee = amount * 0.01;
    recordTrace(135, "COMPUTE", "Phí 1% cho giao dịch trung bình", *balance,
                amount, pinVerified);
    cout << "  → Giao dịch trung bình (>500k): Phí 1% = " << fee << " VND"
         << endl;
  } else {
    fee = 5000;
    recordTrace(140, "COMPUTE", "Phí cố định 5000 VND", *balance, amount,
                pinVerified);
    cout << "  → Giao dịch nhỏ: Phí cố định = " << fee << " VND" << endl;
  }

  double totalAmount = amount + fee;
  recordTrace(145, "COMPUTE", "Tổng tiền = amount + fee", *balance, amount,
              pinVerified);
  cout << "Tổng tiền cần trừ: " << totalAmount << " VND" << endl;

  // Node 10: Kiểm tra số dư
  cout << "\nĐi qua: Node 10 (Kiểm tra số dư)" << endl;
  if (*balance < totalAmount) {
    recordTrace(150, "BRANCH", "if (*balance < totalAmount) → TRUE", *balance,
                amount, pinVerified);
    cout << "  → Rẽ nhánh TRUE → Node 11 (ERROR)" << endl;
    cout << "❌ THẤT BẠI: Số dư không đủ! (Cần: " << totalAmount
         << ", Có: " << *balance << ")" << endl;
    recordTrace(151, "ERROR", "Lỗi: Số dư không đủ", *balance, amount,
                pinVerified);
    delete[] transactionHistory;
    cout << "Đi qua: EXIT PROGRAM" << endl;
    return false;
  }

  recordTrace(155, "BRANCH", "if (*balance < totalAmount) → FALSE", *balance,
              amount, pinVerified);
  cout << "  → Rẽ nhánh FALSE → Node 12 (Thực hiện rút tiền)" << endl;

  // Node 12: Thực hiện rút tiền
  cout << "\nĐi qua: Node 12 (Thực hiện rút tiền)" << endl;
  cout << "--- CẬP NHẬT QUA CON TRỎ ---" << endl;
  cout << "Trước: *balance = " << *balance << " VND" << endl;

  *balance = *balance - totalAmount;
  recordTrace(160, "UPDATE", "Cập nhật balance qua con trỏ", *balance, amount,
              pinVerified);

  cout << "Sau: *balance = " << *balance << " VND" << endl;
  cout << "→ Biến gốc đã thay đổi qua con trỏ!" << endl;

  canWithdraw = true;
  recordTrace(165, "SUCCESS", "Giao dịch thành công", *balance, amount,
              pinVerified);

  delete[] transactionHistory;
  transactionHistory = nullptr;
  cout << "Đã giải phóng bộ nhớ Heap" << endl;

  // Node 13: Exit Success
  cout << "\nĐi qua: Node 13 (EXIT - Thành công)" << endl;
  cout << "✅ THÀNH CÔNG: Đã rút " << amount << " VND" << endl;
  cout << "Phí giao dịch: " << fee << " VND" << endl;
  cout << "Số dư mới: " << *balance << " VND" << endl;
  cout << "Đi qua: EXIT PROGRAM" << endl;

  return canWithdraw;
}

// ============================================================================
// PHẦN 5: TRACING
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
// PHẦN 6: DYNAMIC SLICING
// ============================================================================
void performDynamicSlicing() {
  cout << "\n\n" << string(80, '=') << endl;
  cout << "=== PHẦN 6: CẮT LÁT ĐỘNG (DYNAMIC SLICING) ===" << endl;
  cout << string(80, '=') << endl;

  cout << "\nTiêu chí cắt lát: <balance, dòng 160>" << endl;
  cout
      << "Câu hỏi: Những câu lệnh nào ảnh hưởng đến giá trị cuối của balance?\n"
      << endl;

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

  cout << "Cắt lát động (9 câu lệnh ảnh hưởng):" << endl;
  for (size_t i = 0; i < slice.size(); i++) {
    cout << "  " << (i + 1) << ". " << slice[i] << endl;
  }
}

// ============================================================================
// PHẦN 7: EXECUTION INDEXING
// ============================================================================
void analyzeExecutionIndexing() {
  cout << "\n\n" << string(80, '=') << endl;
  cout << "=== PHẦN 7: ĐÁNH CHỈ MỤC THỰC THI (EXECUTION INDEXING) ===" << endl;
  cout << string(80, '=') << endl;

  cout << "\nPhân tích sự kiện:" << endl;
  cout << string(80, '-') << endl;

  cout << "\n1. Tất cả điểm rẽ nhánh (BRANCH):" << endl;
  for (const auto &event : executionTrace) {
    if (event.eventType == "BRANCH") {
      cout << "   [" << event.eventId << "] " << event.description << endl;
    }
  }

  cout << "\n2. Sự kiện thay đổi balance:" << endl;
  for (const auto &event : executionTrace) {
    if (event.eventType == "UPDATE") {
      cout << "   [" << event.eventId << "] " << event.description << endl;
    }
  }
}

// ============================================================================
// PHẦN 8: FAULT LOCALIZATION
// ============================================================================
void performFaultLocalization() {
  cout << "\n\n" << string(80, '=') << endl;
  cout << "=== PHẦN 8: ĐỊNH VỊ LỖI (FAULT LOCALIZATION) ===" << endl;
  cout << string(80, '=') << endl;

  vector<TestCase> tests = {
      {1, "Test rút tiền bình thường", 1000000, 100000, true, true},
      {2, "Test không có PIN", 1000000, 100000, false, false},
      {3, "Test số dư không đủ", 50000, 100000, true, false},
      {4, "Test số tiền âm", 1000000, -50000, true, false},
      {5, "Test rút 0 đồng", 1000000, 0, true, false},
      {6, "Test rút tiền lớn", 5000000, 2000000, true, true}};

  vector<vector<int>> coverage = {
      {1, 1, 1, 1, 1}, // T1: PASS
      {1, 0, 0, 0, 0}, // T2: FAIL - lỗi PIN
      {1, 1, 1, 1, 0}, // T3: FAIL - lỗi số dư
      {1, 1, 0, 0, 0}, // T4: FAIL - lỗi số tiền
      {1, 1, 0, 0, 0}, // T5: FAIL - lỗi số tiền
      {1, 1, 1, 1, 1}  // T6: PASS
  };

  cout << "\nKết quả Test:" << endl;
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

  cout << "Tổng: " << passCount << " PASS, " << failCount << " FAIL" << endl;

  vector<string> blockNames = {"B1: Kiểm tra PIN", "B2: Kiểm tra số tiền",
                               "B3: Tính phí", "B4: Kiểm tra số dư",
                               "B5: Thực hiện rút tiền"};

  cout << "\nOchiai Coefficient:" << endl;
  cout << string(80, '-') << endl;

  for (int block = 0; block < 5; block++) {
    int failedAndExecuted = 0, totalExecuted = 0;

    for (int test = 0; test < 6; test++) {
      if (coverage[test][block]) {
        totalExecuted++;
        if (!tests[test].expectedResult)
          failedAndExecuted++;
      }
    }

    double suspiciousness = 0.0;
    if (totalExecuted > 0 && failCount > 0) {
      suspiciousness = failedAndExecuted / sqrt(failCount * totalExecuted);
    }

    cout << blockNames[block] << ": " << fixed << setprecision(3)
         << suspiciousness << endl;
  }
}

// ============================================================================
// MAIN
// ============================================================================
int main() {
  cout << string(80, '=') << endl;
  cout << "   HỆ THỐNG RÚT TIỀN TỪ VÍ ĐIỆN TỬ" << endl;
  cout << "   Tích hợp 8 kỹ thuật phân tích chương trình" << endl;
  cout << string(80, '=') << endl;

  double walletBalance = 2000000.0;
  double withdrawAmount = 800000.0;
  bool pinVerified = true;

  bool success =
      withdrawFromWallet(&walletBalance, withdrawAmount, pinVerified);

  cout << "\n" << string(80, '=') << endl;
  cout << "KẾT QUẢ GIAO DỊCH" << endl;
  cout << string(80, '=') << endl;
  cout << "Trạng thái: " << (success ? "✅ THÀNH CÔNG" : "❌ THẤT BẠI") << endl;
  cout << "Số dư ví: " << fixed << setprecision(2) << walletBalance << " VND"
       << endl;

  displayExecutionTrace();
  performDynamicSlicing();
  analyzeExecutionIndexing();
  performFaultLocalization();

  cout << "\n" << string(80, '=') << endl;
  cout << "HOÀN THÀNH - ĐÃ MINH HỌA TẤT CẢ 8 KỸ THUẬT!" << endl;
  cout << string(80, '=') << endl;

  return 0;
}
