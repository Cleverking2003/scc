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
    NodePtr parse_decl();
    NodePtr parse_assign_expr();
    NodePtr parse_expr_stmt();
    NodePtr parse_stmt();
    NodePtr parse_compound_stmt();

    TokenIter m_iter;
    struct Error {
        Token tok;
        std::string mesg;
    };
    std::vector<Error> m_errors;
};
