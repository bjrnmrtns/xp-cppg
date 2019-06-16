#include <algorithm>
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
    
    std::vector<std::string_view> split(const std::string_view input, const std::string_view delims) {
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

    std::vector<std::string_view> tree_to_lines(const std::string_view input) {
        return split(input, "\r\n");
    }
    
    std::string_view to_filename(const std::vector<std::string_view>& parts) {
        return parts.size() > 0 ? parts[parts.size() - 1] : "";
    }

    std::string_view to_extension(const std::string_view str) {
        assert(false);
    }

    std::string_view to_basename(const std::string_view str) {
        assert(false);
    }

    std::vector<std::string_view> parts_to_dirs(const std::vector<std::string_view> parts) {
        assert(false);
    }

    struct file {
        file(const std::string_view line)
        : parts(split(line, "/")) 
        , dirs(parts_to_dirs(parts))
        , filename(to_filename(parts))
        , basefilename(to_basename(filename))
        , extension(filename) {
        }
        const std::vector<std::string_view> parts;
        std::vector<std::string_view> dirs;
        std::string_view filename;
        std::string_view basefilename;
        std::string_view extension;
    };

    std::vector<file> lines_to_files(const std::vector<std::string_view>& lines) {
        std::vector<file> output;
        std::for_each(lines.cbegin(), lines.cend(), [&output](auto& line){ output.push_back(file(line)); });
        return output;
    }
}

int main()
{
    const std::string tree = read_file("tree");
    const auto lines = tree_to_lines(tree);
    const auto files = lines_to_files(lines);
    for(auto x: lines) {
    }
    return 0;
}
