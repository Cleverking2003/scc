#pragma once

#include "tokenizer.h"
#include <memory>
#include <vector>

class Node {

};

using NodePtr = std::unique_ptr<Node>;

class Parser {
public:
    NodePtr parse(const Tokenizer& t);

    bool has_errors() { return !m_errors.empty(); }
    void dump_errors();

private:
    struct Error {};
    std::vector<Error> m_errors;
};
