#include "ast_dumper.h"
#include <iostream>

void print_spaces(int depth) {
    for (int i = 0; i < depth; i++) std::cout << ' ';
}

void ASTDumper::visit(Node& node) {
    node.accept_vis(*this);
}

static const std::string op_str[] = {
    "+",
    "-",
};

void ASTDumper::visit(BinExpr& expr) {
    print_spaces(m_depth);
    std::cout << "BinExpr: " << op_str[expr.m_op_type] << '\n';
    m_depth++;
    expr.m_lhs->accept_vis(*this);
    expr.m_rhs->accept_vis(*this);
    m_depth--;
}

void ASTDumper::visit(NumLiteral& literal) {
    print_spaces(m_depth);
    std::cout << "NumLiteral: " << literal.m_value << '\n';
}
