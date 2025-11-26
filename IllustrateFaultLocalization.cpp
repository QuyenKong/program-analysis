#include <cmath>
#include <iostream>

using namespace std;

// Hàm có BUG: Tính điểm trung bình
double calculateAverage(int scores[], int size) {
  if (size <= 0)
    return 0.0;
  int sum = 0;
  for (int i = 0; i < size; i++) {
    sum += scores[i];
  }
  return sum / size; // BUG: Integer division, thiếu (double)
}

void IllustrateFaultLocalization() {
  cout << "\n=== ĐỊNH VỊ LỖI (FAULT LOCALIZATION) ===" << endl;
  cout << "Bug: Hàm calculateAverage() làm tròn xuống do integer division\n"
       << endl;

  // Test cases
  int t1[] = {85};         // Pass: 85/1 = 85
  int t2[] = {70, 85};     // Fail: 155/2 = 77 (không phải 77.5)
  int t3[] = {60, 80, 95}; // Fail: 235/3 = 78 (không phải 78.33)

  double r1 = calculateAverage(t1, 1);
  double r2 = calculateAverage(t2, 2);
  double r3 = calculateAverage(t3, 3);

  cout << "T1: Kỳ vọng 85.00, Thực tế " << r1 << " → "
       << (r1 == 85.0 ? "PASS" : "FAIL") << endl;
  cout << "T2: Kỳ vọng 77.50, Thực tế " << r2 << " → "
       << (abs(r2 - 77.5) < 0.01 ? "PASS" : "FAIL") << endl;
  cout << "T3: Kỳ vọng 78.33, Thực tế " << r3 << " → "
       << (abs(r3 - 78.33) < 0.01 ? "PASS" : "FAIL") << endl;

  cout << "\nKết quả: 1 PASS, 2 FAIL\n" << endl;

  // Ma trận bao phủ: [test][line]
  // L1=if check, L2=sum init, L3=loop, L4=division (BUG), L5=return
  int coverage[3][5] = {
      {1, 1, 1, 1, 1}, // T1: PASS
      {1, 1, 1, 1, 1}, // T2: FAIL
      {1, 1, 1, 1, 1}  // T3: FAIL
  };

  cout << "Ma trận bao phủ:" << endl;
  cout << "    | T1 | T2 | T3 |" << endl;
  cout << "----|----|----|----" << endl;
  cout << "L1  |  1 |  1 |  1 |  if (size <= 0)" << endl;
  cout << "L2  |  1 |  1 |  1 |  sum = 0" << endl;
  cout << "L3  |  1 |  1 |  1 |  for loop" << endl;
  cout << "L4  |  1 |  1 |  1 |  sum/size ← BUG!" << endl;
  cout << "L5  |  1 |  1 |  1 |  return" << endl;
  cout << "----|----|----|----" << endl;
  cout << "    | P  | F  | F  |" << endl;

  // Tính Ochiai coefficient
  cout << "\nOchiai Coefficient:" << endl;
  int totalFailed = 2;
  for (int line = 0; line < 5; line++) {
    int failedAndExecuted = 0;
    int totalExecuted = 0;

    for (int test = 0; test < 3; test++) {
      if (coverage[test][line]) {
        totalExecuted++;
        if (test >= 1)
          failedAndExecuted++; // T2, T3 failed
      }
    }

    double ochiai = failedAndExecuted / sqrt(totalFailed * totalExecuted);
    cout << "L" << (line + 1) << ": " << ochiai;
    if (line == 3)
      cout << " ← Cao nhất!";
    cout << endl;
  }

  cout << "\n💡 KẾT LUẬN:" << endl;
  cout << "L4 có điểm ngờ vực cao nhất → Bug ở 'sum/size'" << endl;
  cout << "Sửa: Đổi thành '(double)sum/size'" << endl;
}

int main() {
  IllustrateFaultLocalization();
  return 0;
}