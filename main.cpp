#include <iostream>
#include "component.h"

// Utility function.
std::vector<std::string> TokenizeString(std::string const& string)
{
    std::istringstream iss(string);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},
        std::istream_iterator<std::string>());
    return std::move(results);
}

int main()
{
    Transform test("test_name");
    std::cout << "Transform member variables are: \n";
    auto& variables = test.GetVariables();
    for (auto const& variable : variables)
    {
        std::cout << variable->GetName() << "\n";
    }
    system("pause");
}
