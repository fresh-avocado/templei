#include <iostream>
#include <vector>

class Entity {
 private:
  int age;
  std::string name;
  char gender;

 public:
  explicit Entity(int age, std::string name, char gender)
      : age{age}, name{std::move(name)}, gender{gender} {}

  inline auto getName() const -> const std::string& { return name; }
  inline auto getAge() const -> int { return age; }
  inline auto getGender() const -> char { return gender; }
};

auto main() -> int {
  std::vector<Entity> vec;

  std::string name = "gabriel";

  vec.emplace_back(21, name, 'M');
  vec.emplace_back(22, "macarena", 'F');

  std::cout << "name after being moved: " << name << "\n";

  std::cout << "hola\n";

  for (auto item : vec) {
    std::cout << item.getName() << "\n";
  }

  return 0;
}
