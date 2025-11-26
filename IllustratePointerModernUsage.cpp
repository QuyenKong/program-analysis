#include <iostream>
#include <memory>

using namespace std;

void IllustratePointerModernUsage() {
  // 1) std::unique_ptr - quyền sở hữu duy nhất
  {
    auto upNumber = std::make_unique<int>(10); // tự động delete khi ra khỏi scope
    cout << "unique_ptr<int> giá trị: " << *upNumber << endl;

    int n = 3;
    // unique_ptr cho mảng (tự động dùng delete[])
    auto upArray = std::make_unique<int[]>(n);
    for (int i = 0; i < n; ++i) upArray[i] = (i + 1) * 11;
    cout << "unique_ptr<int[]> phần tử đầu/cuối: " << upArray[0] << ", "
         << upArray[n - 1] << endl;

    // chuyển giao quyền sở hữu bằng move
    auto upMoved = std::move(upNumber);
    cout << "Sau move, upNumber rỗng? " << std::boolalpha << (upNumber == nullptr)
         << ", upMoved = " << *upMoved << endl;
  } // upMoved và upArray tự động giải phóng ở đây

  // 2) std::shared_ptr - sở hữu chia sẻ (đếm tham chiếu)
  {
    auto spA = std::make_shared<int>(2025);
    cout << "shared_ptr<int> use_count ban đầu: " << spA.use_count()
         << ", giá trị: " << *spA << endl;

    {
      auto spB = spA; // tăng use_count
      cout << "Trong scope, use_count: " << spA.use_count() << endl;
    } // spB hết scope, use_count giảm

    cout << "Sau scope, use_count: " << spA.use_count() << endl;
  } // Tự động giải phóng khi use_count về 0
}

int main() {
  IllustratePointerModernUsage();
  return 0;
}
