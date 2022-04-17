#pragma once

#include <string>
#include <vector>

struct Token {

};

class Tokenizer {
public:
    Tokenizer(std::string input) : m_input(input) {}
    void tokenize();

    bool has_errors() { return !m_errors.empty(); }
    void dump_errors();

private:
    struct Error {};

    std::string m_input;
    std::vector<Token> m_tokens;
    std::vector<Error> m_errors;
};
