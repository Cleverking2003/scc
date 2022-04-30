#include "ast.h"
#include "ast_visitor.h"

void BinExpr::accept_vis(ASTVisitor& vis) {
    vis.visit(*this);
}

void NumLiteral::accept_vis(ASTVisitor& vis) {
    vis.visit(*this); 
}

void VarDecl::accept_vis(ASTVisitor& vis) {
    vis.visit(*this); 
}

void VarRef::accept_vis(ASTVisitor& vis) {
    vis.visit(*this); 
}

void CompoundStmt::accept_vis(ASTVisitor& vis) {
    vis.visit(*this); 
}
