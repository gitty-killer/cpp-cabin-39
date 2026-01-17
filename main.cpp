#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

struct WordCount {
    std::string word;
    int count;
};

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "usage: textstats <path> [--top N]\n";
        return 1;
    }
    int top = 10;
    std::string path = argv[1];
    for (int i = 1; i < argc; i++) {
        if (std::string(argv[i]) == "--top" && i + 1 < argc) {
            top = std::atoi(argv[i + 1]);
        }
    }

    std::ifstream in(path);
    if (!in) {
        std::cerr << "failed to open file\n";
        return 1;
    }
    std::string text((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    int lines = text.empty() ? 0 : 1;
    for (char ch : text) {
        if (ch == '\n') lines++;
    }

    std::unordered_map<std::string, int> counts;
    std::string word;
    int words = 0;
    for (size_t i = 0; i <= text.size(); i++) {
        char ch = (i < text.size()) ? text[i] : '\0';
        if (std::isalnum(static_cast<unsigned char>(ch))) {
            word.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
        } else if (!word.empty()) {
            counts[word]++;
            words++;
            word.clear();
        }
    }

    std::vector<WordCount> list;
    list.reserve(counts.size());
    for (const auto &kv : counts) {
        list.push_back({kv.first, kv.second});
    }
    std::sort(list.begin(), list.end(), [](const WordCount &a, const WordCount &b) {
        if (a.count == b.count) return a.word < b.word;
        return a.count > b.count;
    });

    std::cout << "lines: " << lines << "\n";
    std::cout << "words: " << words << "\n";
    std::cout << "chars: " << text.size() << "\n";
    std::cout << "top words:\n";
    int limit = std::min(top, static_cast<int>(list.size()));
    for (int i = 0; i < limit; i++) {
        std::cout << "  " << list[i].word << ": " << list[i].count << "\n";
    }
    return 0;
}
