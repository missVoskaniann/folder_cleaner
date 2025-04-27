#include "folder_cleaner.h"
#include <iostream>
#include <filesystem>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./folder_cleaner <directory_path>" << std::endl;
        return 1;
    }

    std::filesystem::path root = argv[1];

    if (!std::filesystem::exists(root) || !std::filesystem::is_directory(root)) {
        std::cerr << "Invalid directory: " << root << std::endl;
        return 1;
    }

    FolderCleaner cleaner;
    cleaner.deleteDuplicateFolders(root);

    return 0;
}
