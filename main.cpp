#include <functional>
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

// acá cuando se hace `v = ivec`, se llama al copy constructor
// del vector y por lo tanto se copia toda la metadata del vector
// junto con sus elementos (muy ineficiente)
void by_value(std::vector<int> v) {
  printf("&data: %p\n", v.data());
  for (const auto& i : v) {
    printf("\t&data[i]: %p\n", &i);
  }
}

// acá cuando se hace `v = ivec`, se crea una referencia,
// un alias, un puntero por debajo que no copia absolutamente
// nada de ivec a v (solo el puntero), por lo tanto mucho
// más rápido. ahora v es lo mismo que ivec, es un alias
void by_ref(const std::vector<int>& v) {
  printf("&data: %p\n", v.data());
  for (const auto& i : v) {
    printf("\t&data[i]: %p\n", &i);
  }
}

void map_ref(std::vector<int>& v, const std::function<int(int)>& f) {
  for (auto& item : v) {
    item = f(item);
  }
}

auto main() -> int {
  std::vector<TA> vec;

  vec.emplace_back(21, "gabriel", 'M');
  vec.emplace_back(22, "macarena", 'F');

  // el linter levantará un warning por no usar `const auto& item`
  for (auto& item : vec) {
    std::cout << item.getName() << "\n";
  }

  std::vector<int> ivec = {1, 2, 3, 4, 5, 6};

  printf("&data: %p\n", ivec.data());

  for (const auto& i : ivec) {
    printf("\t&data[i]: %p\n", &i);
  }

  by_value(ivec);
  by_ref(ivec);
  map_ref(ivec, [](int item) -> int { return item * 2; });

  for (const auto& item : ivec) {
    printf("%d ", item);
  }
  printf("\n");

  return 0;
}
