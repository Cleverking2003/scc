#pragma once

#include "tokenizer.h"
#include <vector>

class Node {

};

class Parser {
public:
    explicit Parser(Tokenizer& t) : m_tokenizer(t) {}
    Node parse();

    bool has_errors() { return !m_errors.empty(); }
    void dump_errors();

private:
    Tokenizer& m_tokenizer;

    struct Error {};
    std::vector<Error> m_errors;
};
