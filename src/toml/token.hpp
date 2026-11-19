#pragma once
#include <string>

namespace nox::toml{
    enum class token_type{
        ID,
        EQUALS,
        STRING,
        INTEGER,
        FLOAT,
        BOOLEAN,
        LEFT_BRACKET,
        RIGHT_BRACKET
    };

    struct token{
        token_type type;
        std::string value;
    };
}