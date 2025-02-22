//
// Created by gauth on 30-04-2018.
//

#include <algorithm>
#include <string>
#include <deque>
#include <iostream>
#include <cassert>

std::string output;

class KnuthsPermutation {
public:
    explicit KnuthsPermutation(std::string word_) : word_(std::move(word_)) {}

    void Generate() const;

private:
    void Generate(std::size_t i_word, std::deque<char> &permutation) const;

    void Print(const std::deque<char> &permutation) const;

    const std::string word_;
};

void KnuthsPermutation::Generate(std::size_t i_word, std::deque<char> &permutation) const {
    if (i_word >= word_.length()) {
        assert(permutation.size() == word_.length());

        Print(permutation);
        return;
    }

    permutation.emplace_front(word_[i_word]);
    Generate(i_word + 1, permutation);

    for (std::size_t i = 0; i < i_word; ++i) {
        std::swap(permutation[i], permutation[i + 1]);
        Generate(i_word + 1, permutation);
    }

    permutation.pop_back();
}

void KnuthsPermutation::Print(const std::deque<char> &permutation) const {
    std::string permutation_str;
    for (const auto c : permutation) {
        permutation_str += c;
    }

    output += permutation_str + "\n";
}

void KnuthsPermutation::Generate() const {
    std::deque<char> permutation;
    Generate(0, permutation);
}

int main() {
    std::string line;

    while (std::getline(std::cin, line), !std::cin.eof()) {
        KnuthsPermutation(line).Generate();
        output += "\n";
    }

    if (!line.empty()) {
        KnuthsPermutation(line).Generate();
        output += "\n";
    }

    output.pop_back();
    std::cout << output;
    return 0;
}