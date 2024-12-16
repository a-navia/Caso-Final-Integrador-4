#include "Variant.hpp"
#include <iostream>

int main() {
    Variant v1(Variant::Symbol, "hola mundo");
    Variant v2(1972.21);
    std::vector<Variant> list = { Variant(Variant::Symbol, "ABC"), Variant(9.81) };
    Variant v3(list);

    std::cout << "v1: " << v1.to_string() << std::endl;
    std::cout << "v2: " << v2.to_string() << std::endl;
    std::cout << "v3: " << v3.to_string() << std::endl;

    std::cout << "v1 (JSON): " << v1.to_json_string() << std::endl;
    std::cout << "v2 (JSON): " << v2.to_json_string() << std::endl;
    std::cout << "v3 (JSON): " << v3.to_json_string() << std::endl;

    std::string json_str = "[\"ABC\", 9.81]";
    Variant v4 = Variant::from_json_string(json_str);
    std::cout << "v4: " << v4.to_string() << std::endl;

    return 0;
}