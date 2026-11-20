#pragma once
#include <string>

namespace nox::toml{
    enum class token_type{
        Bare,
        Equals,
        String,
        Integer,
        Float,
        Boolean,
        LeftBracket,
        RightBracket,
        NewLine,
        Invalid,
        EndOfFile
    };

    struct token{
        token_type type;
        std::string value;
    };
}