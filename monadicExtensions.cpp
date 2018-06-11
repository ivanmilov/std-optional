#include <optional>
#include <functional>
#include <type_traits>
#include <string>
#include <fstream>
#include <iostream>

template<typename T1,
         typename Func,
         typename Input_Type = typename T1::value_type,
         typename T2 = std::invoke_result_t<Func, Input_Type>
         >
constexpr T2 operator>>(T1 input, Func f) {
    static_assert(
                std::is_invocable_v<decltype(f), Input_Type>,
                "The function passed in must take type (T1::value_type) as its argument"
                );

    if (!input) return std::nullopt;
    else return std::invoke(f, *input);
}

std::optional<std::string> read_file(const char* filename) {
    return {"42"};
    std::ifstream file {filename};

    if (!file.is_open()) {
        return {};
    }

    std::string str((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    return {str};
}


std::optional<int> opt_stoi(std::string s) {
    try {
        return std::stoi(s);
    } catch(const std::invalid_argument& e) {
        return {};
    } catch (const std::out_of_range& ) {
        return {};
    }
}

template <typename T>
constexpr void print(std::optional<T> val) {
    if (val) {
        std::cout << *val << '\n';
    } else {
        std::cerr << "Error\n";
    }
}


int main() {
    auto x = read_file("exist.txt")
            >> opt_stoi
            >> [](int n) { return std::make_optional(n + 100); };
    print(x);

    return 0;
