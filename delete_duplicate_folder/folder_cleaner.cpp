// folder_cleaner.cpp
#include "folder_cleaner.h"
#include <iostream>
#include <fstream>
#include <algorithm>

namespace fs = std::filesystem;

void FolderCleaner::deleteDuplicateFolders(const fs::path& root) {
    rootTrie->folderPath = root;
    buildTrie(root, rootTrie);
    serialize(rootTrie);
    collectDuplicates(rootTrie);

    for (const auto& [key, paths] : duplicates) {
        if (paths.size() < 2) continue;
        for (size_t i = 0; i + 1 < paths.size(); ++i) {
            const auto& dupPath = paths[i];
            std::error_code ec;
            fs::remove_all(dupPath, ec);
            if (ec) {
                std::cerr << "Failed to delete " << dupPath << ": " << ec.message() << '\n';
            } else {
                std::cout << "Deleted: " << dupPath << '\n';
            }
        }        
    }
    std::cout << "Deletion completed.\n";
}

void FolderCleaner::buildTrie(const fs::path& path, Trie* node) {
    for (const auto& entry : fs::directory_iterator(path)) {
        if (!entry.is_directory()) continue;
        std::string folderName = entry.path().filename().string();

        Trie* child;
        if (node->children.count(folderName) == 0) {
            child = new Trie();
            child->folderPath = entry.path();
            node->children[folderName] = child;
        } else {
            child = node->children[folderName];
        }
        buildTrie(entry.path(), child);
    }
}

std::string FolderCleaner::serialize(Trie* node) {
    if (node->children.empty()) {
        node->serialization = "";
        return "";
    }

    std::vector<std::pair<std::string, std::string>> serializedChildren;
    for (auto& [name, child] : node->children) {
        std::string rep = serialize(child);
        serializedChildren.emplace_back(name, rep);
    }

    std::sort(serializedChildren.begin(), serializedChildren.end());

    std::string serial;
    for (const auto& [name, rep] : serializedChildren) {
        serial += "(" + name + rep + ")";
    }

    node->serialization = serial;
    duplicates[serial].push_back(node->folderPath);
    return serial;
}

void FolderCleaner::collectDuplicates(Trie* node) {
    for (auto& [name, child] : node->children) {
        collectDuplicates(child);
    }
}
