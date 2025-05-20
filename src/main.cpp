#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

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

    if (input.find("type") != std::String::npos) {
      std::string command = input.substr(5);
      if (std::find(valid.begin(), valid.end(), command) != valid.end()) std::cout << command << " is a shell builtin" << std::endl;
      else std::cout << command << ": not found" << std::endl;
    }
    else {
      if (input == "exit 0") return 0;
      else if (input.substr(0, 4) == "echo") std::cout << input.substr(5) << std::endl;
      else std::cout << input << ": command not found" << std::endl;
    }
  }
}
