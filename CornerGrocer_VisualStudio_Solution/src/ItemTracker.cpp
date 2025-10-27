#include "ItemTracker.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

ItemTracker::ItemTracker(const std::string& inputPath) : m_inputPath(inputPath) {}

bool ItemTracker::Load() {
    m_counts.clear();

    std::ifstream inFile(m_inputPath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open input file: " << m_inputPath << std::endl;
        return false;
    }

    std::string token;
    // Accept either one item per line or space-separated items per line.
    while (inFile >> token) {
        std::string key = Normalize(token);
        if (!key.empty()) {
            ++m_counts[key];
        }
    }
    return true;
}

bool ItemTracker::WriteFrequencyBackup(const std::string& outPath) const {
    std::ofstream out(outPath);
    if (!out.is_open()) {
        std::cerr << "Error: Could not open output file for writing: " << outPath << std::endl;
        return false;
    }
    for (const auto& kv : m_counts) {
        out << kv.first << " " << kv.second << "\n";
    }
    return true;
}

int ItemTracker::FrequencyOf(const std::string& rawWord) const {
    std::string key = Normalize(rawWord);
    auto it = m_counts.find(key);
    if (it == m_counts.end()) return 0;
    return it->second;
}

void ItemTracker::PrintAllFrequencies() const {
    if (m_counts.empty()) {
        std::cout << "(No items found.)" << std::endl;
        return;
    }
    for (const auto& kv : m_counts) {
        std::cout << kv.first << " " << kv.second << std::endl;
    }
}

void ItemTracker::PrintHistogram(char barChar) const {
    if (m_counts.empty()) {
        std::cout << "(No items to display.)" << std::endl;
        return;
    }
    for (const auto& kv : m_counts) {
        std::cout << kv.first << " ";
        for (int i = 0; i < kv.second; ++i) std::cout << barChar;
        std::cout << std::endl;
    }
}

std::string ItemTracker::Normalize(const std::string& raw) {
    // Lowercase copy
    std::string s;
    s.reserve(raw.size());
    for (unsigned char ch : raw) s.push_back(static_cast<char>(std::tolower(ch)));

    // Strip leading/trailing punctuation
    auto is_punct = [](unsigned char c){
        return std::ispunct(c) && c != '-' && c != '\''; // keep hyphens/apostrophes inside words
    };

    // trim left
    size_t start = 0;
    while (start < s.size() && is_punct(static_cast<unsigned char>(s[start]))) ++start;
    // trim right
    size_t end = s.size();
    while (end > start && is_punct(static_cast<unsigned char>(s[end-1]))) --end;

    if (start >= end) return "";
    return s.substr(start, end - start);
}
