#include <core/config.hpp>
#include <fstream>


namespace Nox{
    bool Config::create_file(const fs::path& path){
        std::ofstream file(path / "config.toml");

        if(!file.is_open()){
            return false;
        }

        file << "executable_name = "    << executable_name                      << "\n";
        file << "source_directory = "   << source_directory.filename().string() << "\n";
        file << "build_directory = "    << build_directory.filename().string()  << "\n";
        file << "compiler = "           << compiler                             << "\n";
        file << "compiler_version = "   << compiler_version                     << "\n";
        file << "cpp_version = "        << cpp_version                          << "\n";

        return file.good();
    }

    bool Config::load_file(){
        std::ifstream file("config.toml");

        if(!file.is_open()){
            return false;
        }

        std::string line;
        while(std::getline(file, line)){
            if(!line.empty()){
                std::string key = "";
                std::string value = "";
                bool is_key = true;

                for(char c : line){
                    if(c != '=' && c != ' '){
                        if(is_key){
                            key += c;
                        }
                        else{
                            value += c;
                        }
                    }else{
                        is_key = false;
                    }
                }

                if(key == "executable_name"){
                    executable_name = value;
                }
                else if(key == "source_directory"){
                    source_directory = value;
                }
                else if(key == "build_directory"){
                    build_directory = value;
                }
                else if(key == "compiler"){
                    compiler = value;
                }
                else if(key == "compiler_version"){
                    compiler_version = value;
                }
                else if(key == "cpp_version"){
                    cpp_version = value;
                }
            }
        }

        return true;
    }
}
