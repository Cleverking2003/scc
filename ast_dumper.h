#pragma once

#include "ast_visitor.h"
#include "parser.h"

class ASTDumper : public ASTVisitor {
public:
    void dump(Node& node) { visit(node); }

    void visit(Node&) override;
    void visit(BinExpr&) override;
    void visit(NumLiteral&) override;

private:
    int m_depth { 0 };
};
