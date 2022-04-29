#include "codegen.h"

#include <fstream>

namespace Codegen {

void Codegen::generate(Node& top) {
    visit(top);
}

void Codegen::visit(Node& node) {
    node.accept_vis(*this);
}

void Codegen::visit(BinExpr& expr) {
    visit(*expr.m_rhs);
    m_isns.push_back(Inst(Push, InstData(RAX)));
    visit(*expr.m_lhs);
    m_isns.push_back(Inst(Pop, InstData(RDI)));
    switch (expr.m_op_type) {
    case BinOpType::Add:
        m_isns.push_back(Inst(Add, InstData(RDI), InstData(RAX)));
        break;
    case BinOpType::Sub:
        m_isns.push_back(Inst(Sub, InstData(RDI), InstData(RAX)));
        break;
    case BinOpType::Mul:
        m_isns.push_back(Inst(Imul, InstData(RDI), InstData(RAX)));
        break;
    case BinOpType::Div:
        m_isns.push_back(Inst(Cqo));
        m_isns.push_back(Inst(Idiv, InstData(RDI)));
        break;
    case BinOpType::Mod:
        m_isns.push_back(Inst(Cqo));
        m_isns.push_back(Inst(Idiv, InstData(RDI)));
        m_isns.push_back(Inst(Mov, InstData(RDX), InstData(RAX)));
        break;
    }
}

void Codegen::visit(NumLiteral& literal) {
    m_isns.push_back(Inst(Mov, InstData(literal.m_value), InstData(RAX)));
}

static const std::string inst_names[] = {
    "add",
    "sub",
    "imul",
    "idiv",
    "push",
    "pop",
    "mov",
    "cqo",
};

static const std::string reg_names[] = {
    "rax",
    "rbx",
    "rcx",
    "rdx",
    "rsi",
    "rdi",
};

static std::string data_to_str(InstData& data) {
    switch (data.type) {
    case Reg:
        return "%" + reg_names[data.reg];
    case Imm:
        return "$" + std::to_string(data.imm);
    }
}

static std::string emit_inst(Inst& inst) {
    auto res = inst_names[inst.type];
    if (inst.type != Cqo) 
        res += "q";
    if (inst.src.has_value()) {
        res += " " + data_to_str(inst.src.value());
    }
    if (inst.dest.has_value()) {
        res += ", " + data_to_str(inst.dest.value());
    }
    return res;
}

void Codegen::emit_text_asm(std::string filename) {
    std::ofstream file(filename, std::ios_base::out);
    file << ".globl main\nmain:\n";
    for (auto i : m_isns) {
        file << emit_inst(i) << '\n';
    }
    file << "ret\n";
}

}
