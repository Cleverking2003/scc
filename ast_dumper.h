#pragma once

#include "ast_visitor.h"
#include "parser.h"

class ASTDumper : public ASTVisitor {
public:
    void dump(Node& node) { visit(node); }

    void visit(Node&) override;
    void visit(BinExpr&) override;
    void visit(NumLiteral&) override;
    void visit(VarDecl&) override;
    void visit(VarRef&) override;
    void visit(CompoundStmt&) override;

private:
    int m_depth { 0 };
};
