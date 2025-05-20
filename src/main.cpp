#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <cstring>

std::string GetPath(std::vector<std::string> paths, std::string file) {
  for (std::string path: paths) {
    for (const auto& entry: std::filesystem::directory_iterator(path)) {
      if (entry.path().stem() == file) {
        return entry.path().parent_path().string() + "/" + file;
      }
    }
  }
  return "";
}

int main() {
  // Flush after every std::cout / std:cerr
  std::cout << std::unitbuf;
  std::cerr << std::unitbuf;

  // Uncomment this block to pass the first stage
  std::vector<std::string> valid = {"exit", "type", "echo"};

  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);

    if (input.substr(0,4) == "type") {
      char* p = std::getenv("PATH");
      char* tokens = strtok(p, ":");
      std::vector<std::string> paths;
      std::string file = input.substr(5);

      while (tokens != nullptr) {
        paths.push_back(tokens);
        tokens = strtok(nullptr, ":");
      }

      std::string filePath = GetPath(paths, file);

      if (filePath == "") std::cout << file << ": not found" << std::endl;
      else std::cout << file << " is " << filePath << std::endl;
      
      
    }
    else {
      if (input == "exit 0") return 0;
      else if (input.substr(0, 4) == "echo") std::cout << input.substr(5) << std::endl;
      else std::cout << input << ": command not found" << std::endl;
    }
  }
}
