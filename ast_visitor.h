#pragma once

#include "ast.h"

class ASTVisitor {
public:
    virtual void visit(Node&) = 0;
    virtual void visit(BinExpr&) = 0;
    virtual void visit(NumLiteral&) = 0;
    virtual void visit(VarDecl&) = 0;
    virtual void visit(VarRef&) = 0;
    virtual void visit(CompoundStmt&) = 0;
};
