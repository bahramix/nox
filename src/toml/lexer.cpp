#include <toml/token.hpp>
#include <toml/lexer.hpp>
#include <fstream>
#include <iostream>

namespace nox::toml{
    bool lexer::load_from_file(const std::string& path){
        std::ifstream file(path);

        if(!file.is_open()){
            return false;
        }

        
    }
}