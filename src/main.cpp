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
      char *p = std::getenv("PATH");
      std::string currPath(p);
      std::string file = input.substr(5);
      std::cout << currPath << std::endl;
      std::cout << p << std::endl;

      if (currPath.find(file) != std::string::npos) std::cout << currPath.substr(0, currPath.find(file) + file.length()) << std::endl;
      else std::cout << file << ": not found" << std::endl;
    }
    else {
      if (input == "exit 0") return 0;
      else if (input.substr(0, 4) == "echo") std::cout << input.substr(5) << std::endl;
      else std::cout << input << ": command not found" << std::endl;
    }
  }
}
