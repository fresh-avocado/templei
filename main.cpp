#include <iostream>
#include <vector>

class TA {
 private:
  int age;
  std::string name;
  char gender;

 public:
  explicit TA(int age, std::string name, char gender)
      : age{age}, name{std::move(name)}, gender{gender} {}

  inline auto getName() const -> const std::string& { return name; }
  inline auto getAge() const -> int { return age; }
  inline auto getGender() const -> char { return gender; }
};

auto main() -> int {
  std::vector<TA> vec;

  vec.emplace_back(21, "gabriel", 'M');
  vec.emplace_back(22, "macarena", 'F');

  // el linter levantará un warning por no usar `const auto& item`
  for (auto item : vec) {
    std::cout << item.getName() << "\n";
  }

  return 0;
}
