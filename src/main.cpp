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
    std::string command = input.substr(5);

    if (std::find(valid.begin(), valid.end(), command) != valid.end()) std::cout << command << " is a shell builtin" << std::endl;
    else std::cout << command << ": command not found" << std::endl;
  }
}
