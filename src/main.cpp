#include <cstring>
#include <toml.hpp>

#include "root.h"

using std::string;

bool dirIsExist(std::string dir) {
    struct stat statBuf;
    return !(stat(dir.c_str(), &statBuf) == -1);
}

int main(int argc, char **argv) {

    std::string setting_path;
    int cli_opt;
    while((cli_opt = getopt(argc, argv, "a:")) != -1) {
        switch(cli_opt) {
        case 'a':
            setting_path = optarg;
            break;
        }
    }

    const auto data = toml::parse(setting_path);

    string title, data_set_name, struct_file_name;
    int min_sup, max_depth;

    title = toml::find<std::string>(data, "data_path");
    struct_file_name = toml::find<std::string>(data, "struct_file_name");
    min_sup = toml::find<int>(data, "min_sup");
    max_depth = toml::find<int>(data, "max_depth");

    string DB_struct_path_buf = title + "/" + struct_file_name;
    const char *DB_struct_path = DB_struct_path_buf.c_str();

    // cout << DB_struct_path_buf << endl;

    std::string root_dir = "./out/";
    if(!dirIsExist(root_dir)) {
        auto err = mkdir(root_dir.c_str(), 0777);
        if(err == 1) {
            cout << "[ERROR]: mkdir faild" << endl;
            return 0;
        }
    }

    INIT_SPACE::ROOT fRoot(DB_struct_path, root_dir, min_sup, max_depth);
    fRoot.traverse();

    return 0;
}
