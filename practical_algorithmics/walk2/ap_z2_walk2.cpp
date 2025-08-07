#include <iostream>

int main() {
    int cases;
    std::cin >> cases;
    for (int i = 0; i < cases; i++) {
        int x;
        std::cin >> x;
        int stp_min = x;
        int min = (stp_min == 0) ? 15 : ((3000 + stp_min - 1) / stp_min);
        if (min <= 15) {
            std::cout << min << std::endl;
        }
        else {
            std::cout << "15" << std::endl;
        }
    }
    return 0;
}
