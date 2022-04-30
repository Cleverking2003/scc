#pragma once

#include <memory>
#include <string>
#include <vector>

class ASTVisitor;

enum NodeType {
    NdBinExpr,
    NdNum,
    NdVarDecl,
    NdVarRef,
    NdCompoundStmt,
};

class Node {
    friend class ASTVisitor;
public:
    explicit Node(NodeType type) : m_type(type) {}
    NodeType type() { return m_type; }

    virtual void accept_vis(ASTVisitor&) = 0;

private:
    NodeType m_type;
};

using NodePtr = std::unique_ptr<Node>;

enum BinOpType {
    Add,
    Sub,
    Mul,
    Div,
    Mod,
    Assign,
};

class BinExpr : public Node {
public:
    explicit BinExpr(NodePtr& lhs, NodePtr& rhs, BinOpType type)
        : Node(NdBinExpr), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)), m_op_type(type) {}

    void accept_vis(ASTVisitor& vis);

    NodePtr m_lhs, m_rhs;
    BinOpType m_op_type;
};

class NumLiteral : public Node {
public:
    explicit NumLiteral(int value) : Node(NdNum), m_value(value) {}

    void accept_vis(ASTVisitor& vis);

    int m_value;
};

struct Var {
    Var(std::string& name) : name(std::move(name)) {}

    std::string name;
    int offset { 0 };
};

class VarDecl : public Node {
public:
    explicit VarDecl(std::string& name) : Node(NdVarDecl), var(name) {}

    void accept_vis(ASTVisitor& vis);

    Var var;
};

class VarRef : public Node {
public:
    explicit VarRef(std::string& name) : Node(NdVarRef), name(std::move(name)) {}

    void accept_vis(ASTVisitor& vis);

    std::string name;
    Var* var { nullptr };
};

class CompoundStmt : public Node {
public:
    explicit CompoundStmt() : Node(NdCompoundStmt) {}

    void accept_vis(ASTVisitor& vis);

    std::vector<NodePtr> stmts;
};
