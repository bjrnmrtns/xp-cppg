#include <algorithm>
#include <fstream>
#include <optional>
#include <vector>
#include <string>
#include <string_view>
#include <sstream>
#include <iostream>
#include <absl/types/span.h>

namespace {
    void write_to_file(const std::string& filename, const std::string&
contents) {
        std::ofstream out(filename);
        out << contents;
    }

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

    struct filename_t {
        std::string_view base;
        std::string_view dot;
        std::string_view ext;
    };
    
    filename_t get_filename(const std::string_view filename) {
        filename_t output;
        std::string_view::size_type pos = filename.find_last_of(".");
        output.base = pos != std::string_view::npos ?
filename.substr(0, pos) : filename;
        output.dot = pos != std::string_view::npos ?
filename.substr(pos, 1) : std::string_view();
        output.ext = pos != std::string_view::npos ?
filename.substr(pos + 1, filename.size() - pos) : filename;
        return output;
    }
    
    std::vector<std::string_view> get_dirs(const
std::vector<std::string_view>& parts) {
        std::vector<std::string_view> output(parts);
        if(!parts.empty()) {
            output.pop_back();
        }
        return output;
    }
    
    std::string_view get_file(const std::vector<std::string_view>& parts) {
        if(!parts.empty()) {
            return parts.back();
        }
        return std::string_view();
    }
    
    struct build_cmake {
        std::ostringstream ss;
        const std::string project_pr;
        const std::string project_ep;
        const std::string compilation_pr;
        const std::string compilation_ep;
        void add_project(const std::string& name) {
            ss << project_pr;
            ss << name;
            ss << project_ep;
        }
        void add_compilation(const std::vector<std::string_view>& files) {
            ss << compilation_pr;
            std::for_each(files.cbegin(), files.cend(), [this](const
auto& file) { ss << file; });
            ss << compilation_ep;
        }
    };

    struct file {
        file(const std::string_view line)
        : parts(split(line, "/")) 
        , dirs(get_dirs(parts))
        , filename(get_filename(get_file(parts))) {
        }
        const std::vector<std::string_view> parts;
        std::vector<std::string_view> dirs;
        const filename_t filename;
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
    return 0;
}
