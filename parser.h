#pragma once

#include "ast.h"
#include "tokenizer.h"
#include <optional>
#include <vector>

class Parser {
public:
    NodePtr parse(const Tokenizer& t);

    bool has_errors() { return !m_errors.empty(); }
    void dump_errors();

private:
    bool peek(TokenType type);
    std::optional<Token> consume(TokenType type);

    NodePtr parse_num();
    NodePtr parse_mul();
    NodePtr parse_add();

    TokenIter m_iter;
    struct Error {
        Token tok;
        std::string mesg;
    };
    std::vector<Error> m_errors;
};
