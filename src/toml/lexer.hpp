#pragma once
#include <util/types.hpp>
#include <string>
#include <vector>
#include <toml/token.hpp>

namespace nox::toml{
    class lexer{
    private:
        u32 position;
        u32 line;
        u32 column;

        std::vector<toml::token> tokens;

    public:
        bool load_from_file(const std::string& path);
        token next_token();
    };
}