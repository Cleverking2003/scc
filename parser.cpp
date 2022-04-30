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
    Mul,
    Div,
    Mod,
};

NodePtr Parser::parse_mul() {
    auto lhs = parse_num();
    if (!lhs) return nullptr;
    while (peek(TkStar) || peek(TkSlash) || peek(TkPercent)) {
        auto type = (m_iter++)->type;
        auto rhs = parse_num();
        if (!rhs) return nullptr;
        lhs = std::make_unique<BinExpr>(lhs, rhs, bin_types[type]);
    }
    return lhs;
}

NodePtr Parser::parse_add() {
    auto lhs = parse_mul();
    if (!lhs) return nullptr;
    while (peek(TkPlus) || peek(TkMinus)) {
        auto type = (m_iter++)->type;
        auto rhs = parse_mul();
        if (!rhs) return nullptr;
        lhs = std::make_unique<BinExpr>(lhs, rhs, bin_types[type]);
    }
    return lhs;
}

NodePtr Parser::parse_decl() {
    if (!peek(TkInt)) return nullptr;
    consume(TkInt);
    auto ident = consume(TkIdent);
    if (!ident.has_value()) {
        m_errors.push_back({ *m_iter, "Expected an identifier" });
        return nullptr;
    }
    auto name = std::string(ident.value().start, ident.value().end);
    NodePtr var = std::make_unique<VarDecl>(name);
    if (peek(TkEqual)) {
        consume(TkEqual);
        auto expr = parse_assign_expr();
        if (!expr) {
            m_errors.push_back({ *m_iter, "Expected an expression"});
            return nullptr;
        }
        var = std::make_unique<BinExpr>(var, expr, Assign);
    }
    if (!consume(TkSemicolon).has_value()) {
        m_errors.push_back({ *m_iter, "Expected a semicolon"});
        return nullptr;
    }
    return var;
}

NodePtr Parser::parse_assign_expr() {
    auto lhs = consume(TkIdent);
    if (!lhs.has_value()) {
        return parse_add();
    }
    std::string name(lhs.value().start, lhs.value().end);
    NodePtr ref = std::make_unique<VarRef>(name);
    if (peek(TkEqual)) {
        NodePtr rhs = parse_assign_expr();
        return std::make_unique<BinExpr>(ref, rhs, Assign);
    }
    return ref;
}

NodePtr Parser::parse_expr_stmt() {
    auto stmt = parse_assign_expr();
    if (!consume(TkSemicolon).has_value()) {
        m_errors.push_back({ *m_iter, "Expected a semicolon"});
        return nullptr;
    }
    return stmt;
}

NodePtr Parser::parse_stmt() {
    if (auto decl = parse_decl()) {
        return decl;
    }
    else if (auto expr = parse_expr_stmt()) {
        return expr;
    }
    return nullptr;
}

NodePtr Parser::parse_compound_stmt() {
    std::unique_ptr<CompoundStmt> stmt = std::make_unique<CompoundStmt>();
    while (m_iter->type != TkEof) {
        stmt->stmts.push_back(parse_stmt());
    }
    return stmt;
}

NodePtr Parser::parse(const Tokenizer& t) {
    m_iter = t.iter();
    auto top = parse_compound_stmt();
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
