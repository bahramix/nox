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

        std::string source;

        char peek();
        char advance();

        bool is_at_end();
        bool is_bare_char(char c);

        void skip_white_space();
        
        token next_token();

        token read_bare(char c);
        token read_string();

        bool load_tokens();

    public:
        std::vector<toml::token> tokens;
        
        lexer();
        bool load_from_file(const std::string& path);
    };
}