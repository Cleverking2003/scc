#include "parser.h"
#include <iostream>

bool Parser::peek(TokenType type) {
    return m_iter->type == type;
}

std::optional<Token> Parser::consume(TokenType type) {
    if (m_iter->type == type) {
        return *m_iter++;
    }
    return {};
}

NodePtr Parser::parse_num() {
    auto tok = consume(TkNum);
    if (!tok.has_value()) {
        m_errors.push_back({ *m_iter++, "Expected a number literal" });
        return nullptr;
    }
    std::string value(tok.value().start, tok.value().end);
    return std::make_unique<NumLiteral>(std::stoi(value));
}

static const BinOpType bin_types[] = {
    Add,
    Sub,
};

NodePtr Parser::parse_add() {
    auto lhs = parse_num();
    if (!lhs) return nullptr;
    while (peek(TkPlus) || peek(TkMinus)) {
        auto type = (m_iter++)->type;
        auto rhs = parse_num();
        if (!rhs) return nullptr;
        lhs = std::make_unique<BinExpr>(lhs, rhs, bin_types[type]);
    }
    return lhs;
}

NodePtr Parser::parse(const Tokenizer& t) {
    m_iter = t.iter();
    auto top = parse_add();
    if (!top) return nullptr;
    if (m_iter->type != TkEof) {
        m_errors.push_back({ *m_iter, "Expected an end of file" });
        return nullptr;
    }
    return top;
}

void Parser::dump_errors() {
    for (auto e : m_errors) {
        std::cerr << e.tok.line << ':' << e.tok.col << ' ' << e.mesg << '\n';
    }
}
