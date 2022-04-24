#pragma once

#include <string>
#include "ast_visitor.h"

class Codegen : public ASTVisitor {
public:
    void generate(Node&);
    void emit_text_asm(std::string filename);

    void visit(Node&) override {}
    void visit(BinExpr&) override {}
    void visit(NumLiteral&) override {}
};
