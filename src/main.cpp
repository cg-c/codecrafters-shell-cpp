#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <cstring>

std::string GetPath(char* p, std::string file) {
  std::vector<std::string> paths;
  std::stringstream ss(p);
  std::string token = "";
  while (std::getline(ss, token, ':')) paths.push_back(token);

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
      std::string command = input.substr(5);
      if (command == "echo" || command == "type" || command == "exit") std::cout << command << " is a shell builtin" << std::endl;
      else {
        char* p = std::getenv("PATH");
        std::string filePath = GetPath(p, command);

        if (filePath == "") std::cout << command << ": not found" << std::endl;
        else std::cout << command << " is " << filePath << std::endl;
      }
    }
    else {
      if (input == "exit 0") return 0;
      else if (input.substr(0, 4) == "echo") std::cout << input.substr(5) << std::endl;
      else if (GetPath(std::getenv("PATH"), input.substr(0, input.find(" "))) != "") system(input.c_str());
      else std::cout << input << ": command not found" << std::endl;
    }
  }
}
