#pragma once

#include <string>
#include <utility>

/*
std::string path = "Test";
std::cout << std::experimental::filesystem::is_directory(path) << std::endl;
for (auto & p : std::experimental::filesystem::directory_iterator(path)) {
        if (!std::experimental::filesystem::is_directory(p)) {
                std::string fileName = p.path().filename().generic_string();
                auto file = File(fileName);
                files.emplace_back(file);
        }
}
*/

class File {
 public:
  explicit File(std::string path) : path(std::move(path)) {}

  File() = delete;

  ~File() = default;

  void read() = delete;

  void write() = delete;

  std::string getPath() const { return path; };

  void setPath(std::string &path) { this->path = path; }

 private:
  std::string path;
};
