#pragma once

#include <optional>
#include <string>
#include <vector>
#include "ast_visitor.h"

namespace Codegen {
enum InstType {
    Add,
    Sub,
    Push,
    Pop,
    Mov,
};

enum OperandType {
    Reg,
    Imm,
};

enum Regs {
    RAX,
    RBX,
    RCX,
    RDX,
    RSI,
    RDI,
};

struct InstData {
    OperandType type;
    union {
        Regs reg;
        int imm;
    };

    explicit InstData(Regs reg) : type(Reg), reg(reg) {}
    explicit InstData(int imm) : type(Imm), imm(imm) {}
};

struct Inst {
    InstType type;
    std::optional<InstData> src, dest;

    Inst(InstType type, InstData op) : type(type), src(op), dest() {}
    Inst(InstType type, InstData src, InstData dest) : type(type), src(src), dest(dest) {}
};

class Codegen : public ASTVisitor {
public:
    void generate(Node&);
    void emit_text_asm(std::string filename);

    void visit(Node&) override;
    void visit(BinExpr&) override;
    void visit(NumLiteral&) override;

private:
    std::vector<Inst> m_isns;
};

}
