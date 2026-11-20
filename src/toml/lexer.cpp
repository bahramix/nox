#include "token.hpp"
#include <iterator>
#include <toml/token.hpp>
#include <toml/lexer.hpp>
#include <fstream>

namespace nox::toml{
    lexer::lexer()
    : position(0)
    , line(0)
    , column(0)
    {}

    char lexer::peek(){
        if(is_at_end()){
            return '\0';
        }

        return source[position];
    }

    char lexer::advance(){
        if(is_at_end()){
            return '\0';
        }

        return source[position++];
    }

    bool lexer::is_at_end(){
        return position >= source.size();
    }

    bool lexer::is_bare_char(char c){
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_') || (c == '-');
    }

    void lexer::skip_white_space(){
        while(peek() == ' ' || peek() == '\t'){
            advance();
        }
    }

    token lexer::next_token(){
        skip_white_space();

        if(is_at_end()){
            return {token_type::EndOfFile, ""};
        }

        char c = advance();

        switch(c){
            case '=':
                return {token_type::Equals};
            case '[':
                return {token_type::RightBracket};
            case ']':
                return {token_type::LeftBracket};
            case '\n':
                return {token_type::NewLine};
            case '"':
                return read_string();
        }

        if(is_bare_char(c)){
            return read_bare(c);
        }

        return {token_type::Invalid, std::string(1, c)};
    }

    token lexer::read_string(){
        std::string value = "";

        while(!is_at_end()){
            char c = peek();

            if(c == '"'){
                advance();
                return {token_type::String, value};
            }
            if(c == '\n'){
                break;
            }

            value += advance();
        }

        return {token_type::Invalid, "unterminated string"};
    }

    token lexer::read_bare(char c){
        std::string value = "";

        value += c;

        while(!is_at_end() ){
            char c = peek();

            if(!is_bare_char(c)){
                break;
            }

            value += advance();
        }

        return {token_type::Bare, value};
    }

    bool lexer::load_tokens(){
        while(!is_at_end()){
            tokens.push_back(next_token());
        }

        return true;
    }

    bool lexer::load_from_file(const std::string& path){
        std::ifstream file(path);

        if(!file.is_open()){
            return false;
        }

        source = std::string(std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{});

        return load_tokens();
    }
}
