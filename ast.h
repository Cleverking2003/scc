#pragma once

#include <memory>

class ASTVisitor;

enum NodeType {
    NdBinExpr,
    NdNum,
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
