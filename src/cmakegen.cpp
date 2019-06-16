#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <string_view>
#include <iostream>

namespace {
    std::string read_file(const std::string& file_name) {
        std::ifstream ifs(file_name, std::ios::in | std::ios::binary);
        ifs.seekg(0, std::ios::end);
        std::ifstream::pos_type file_size = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        std::vector<char> file_contents(file_size);
        ifs.read(file_contents.data(), file_size); 
        return std::string(file_contents.data(), file_size);
    }
    
    std::vector<std::string_view> split(std::string_view input, std::string_view delims) {
        std::vector<std::string_view> output;
        std::string_view::size_type first = 0;
        std::string_view::size_type pos = 0;
        while(pos != std::string_view::npos) {
            pos = input.find_first_of(delims, first); 
            auto second = pos != std::string_view::npos ? pos : input.size(); 
            output.push_back(input.substr(first, second - first));
            first = second + 1;
        }
        return output;
    }

    std::vector<std::string_view> tree_lines(std::string_view input) {
        return split(input, "\r\n");
    }
}

int main()
{
    const std::string tree = read_file("tree");
    const auto lines = tree_lines(tree);
    for(auto x: lines) {
        std::cout << x;
    }
    return 0;
}
