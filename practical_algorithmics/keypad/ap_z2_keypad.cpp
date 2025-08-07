#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>


std::unordered_map<char, std::string> keymap = {
    {'a', "2"}, {'b', "2"}, {'c', "2"},
    {'d', "3"}, {'e', "3"}, {'f', "3"},
    {'g', "4"}, {'h', "4"}, {'i', "4"},
    {'j', "5"}, {'k', "5"}, {'l', "5"},
    {'m', "6"}, {'n', "6"}, {'o', "6"},
    {'p', "7"}, {'q', "7"}, {'r', "7"}, {'s', "7"},
    {'t', "8"}, {'u', "8"}, {'v', "8"},
    {'w', "9"}, {'x', "9"}, {'y', "9"}, {'z', "9"}
};

std::string translate_to_key(std::string str) {
    std::string string_to_key = "";
    for (char c : str) {
        string_to_key += keymap[c];
    }
    return string_to_key;
}

int main() {
    int cases;
    std::cin >> cases;
    while (cases>0) {
        int n, q;
        std::cin >> n >> q;

        std::vector<std::string> lines(n);
        std::unordered_map<std::string, int> incidence;


        for (int i = 0; i < n; i++) {
            std::cin >> lines[i];
        }

        for (std::string iter_line : lines) {
            incidence[translate_to_key(iter_line)]++;
        }

        for (int i = 0; i < q; i++) {
            std::string keys;
            std::cin >> keys;
            std::cout << incidence[keys] << std::endl;
        }

        cases--;
    }
    return 0;
}
