#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cstdlib>

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
      char* tokens = strtok(p, ':');
      std::vector<std::string> paths;
      std::string file = input.substr(5);

      while (tokens != nullptr) {
        paths.push_back(tokens);
        tokens = strtok(nullptr, ':');
      }

      for (std::string path: paths) {
        for (const auto& entry: std::filesystem::directory_iterator(path)) {
          if (entry.path().stem() == "file") {
            std::cout << entry.path().parent_path().string() << "/" << file << std::endl;
            return;
          }
        }
      }
      std::cout << file << ": not found" << std::endl;
    }
    else {
      if (input == "exit 0") return 0;
      else if (input.substr(0, 4) == "echo") std::cout << input.substr(5) << std::endl;
      else std::cout << input << ": command not found" << std::endl;
    }
  }
}
