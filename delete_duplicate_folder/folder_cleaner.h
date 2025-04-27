// folder_cleaner.h
#ifndef FOLDER_CLEANER_H
#define FOLDER_CLEANER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <filesystem>

class FolderCleaner {
public:
    void deleteDuplicateFolders(const std::filesystem::path& root);

private:
    struct Trie {
        std::unordered_map<std::string, Trie*> children;
        std::string serialization;
        std::filesystem::path folderPath;
    };

    Trie* rootTrie = new Trie();
    std::unordered_map<std::string, std::vector<std::filesystem::path>> duplicates;

    void buildTrie(const std::filesystem::path& path, Trie* node);
    std::string serialize(Trie* node);
    void collectDuplicates(Trie* node);
};

#endif // FOLDER_CLEANER_H
