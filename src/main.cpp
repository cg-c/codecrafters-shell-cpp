#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <cstdlib>
#include <cstring>
#include <sstream>

std::vector<std::string> GetTokens(std::string input, char delime) {
  std::stringstream ss(input);
  std::string token = "";
  std::vector<std::string> tokens;
  while (std::getline(ss, token, delime)) tokens.push_back(token);
  return tokens;
}

std::string GetPath(char* p, std::string file) {
  std::vector<std::string> paths = GetTokens(p, ':');

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

  std::vector<std::string> commands = {"exit", "type", "echo", "pwd", "cd"};

  while (true) {
    std::cout << "$ ";
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = GetTokens(input, ' ');

    if (tokens[0] == "type") {
      if (find(commands.begin(), commands.end(), tokens[1]) != commands.end()) std::cout << tokens[1] << " is a shell builtin" << std::endl;
      else {
        std::string path = input.substr(5);
        char* p = std::getenv("PATH");
        std::string filePath = GetPath(p, path);

        if (filePath == "") std::cout << path << ": not found" << std::endl;
        else std::cout << path << " is " << filePath << std::endl;
      }
    }
    else if (input == "exit 0") return 0;
    else if (tokens[0] == "echo") {
      if (tokens[1].at(0) == '\'' && input[input.size() - 1] == '\''){
        for (int i = 1; i < tokens.size(); i++) {
          std::string t = tokens[i];

          if (t[0] == '\'' ) t = t.substr(1);
          if (t[t.size() - 1] == '\'') t = t.subtr(0, t.size() - 1);
          std::cout << t << " "; 
        }
        std::cout << std::endl;
      }
      else { 
        std::cout << tokens[1];
        for (int i = 2; i < tokens.size(); i++) {
          if (tokens[i] == "") continue;
          std::cout << " " << tokens[i];
        }
        std::cout << std::endl;
      }
    }
    else if (tokens[0] == "pwd") std::cout << std::filesystem::current_path().string() << std::endl;
    else if (tokens[0] == "cd") {
      if (tokens[1] == "~") tokens[1] = std::getenv("HOME");

      std::filesystem::directory_entry entry(tokens[1]);

      if (entry.exists()) std::filesystem::current_path(tokens[1]);
      else std::cout << "cd: " << tokens[1] << ": No such file or directory" << std::endl;
    }
    else if (GetPath(std::getenv("PATH"), tokens[0]) != "") system(input.c_str());
    else std::cout << input << ": command not found" << std::endl;
  }
}
