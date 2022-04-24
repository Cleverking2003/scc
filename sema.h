#pragma once

#include "ast_visitor.h"
#include <vector>

class Sema : public ASTVisitor {
public:
    void analyze(Node&);

    void visit(Node&) override {}
    void visit(BinExpr&) override {}
    void visit(NumLiteral&) override {}

    bool has_errors() { return !m_errors.empty(); }
    void dump_errors();

private:
    struct Error {};
    std::vector<Error> m_errors;
};
