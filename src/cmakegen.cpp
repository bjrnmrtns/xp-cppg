#include <string>
#include <fstream>
#include <vector>
#include <optional>

namespace {
    std::string read_file(const std::string& file_name) {
        std::ifstream ifs(file_name, std::ios::in | std::ios::binary);
        std::ifstream::pos_type file_size = ifs.tellg();
        ifs.seekg(0, std::ios::beg);
        std::vector<char> file_contents(file_size);
        ifs.read(file_contents.data(), file_size); 
        return std::string(file_contents.data(), file_size);
    }
}

int main()
{
    std::string tree = read_file("tree");
    return 0;
}
