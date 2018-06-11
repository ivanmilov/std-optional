#include <iostream>
#include <optional>
#include <map>

// Provide an iterator-free interface for lookups to map-like objects.
// Warning: the output value is copied into the optional.
template <typename Map, typename Key>
std::optional<typename Map::mapped_type>/*auto*/ lookup(const Map& m, const Key& k)
{
    if(auto it = m.find(k); it != m.end())
        return std::make_optional(it->second);
    return std::nullopt;
    
    // auto it = m.find(k);
    // return it != m.end() ? std::make_optional(it->second) : std::nullopt;
}

int main()
{
    const std::map<int, int> squares = { {1, 1}, {2, 4}, {3, 9}, {4, 16} };

    if (const auto square = lookup(squares, 2)) // cleaner, no need for != end()
    {
        std::cout << "Square is " << *square << '\n';
    }
    else
    {
        std::cout << "Square is unknown.\n";
    }
}