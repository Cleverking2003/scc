#pragma once

#include <string>
#include <vector>

using Index = std::string::const_iterator;

enum TokenType {
    TkPlus,
    TkMinus,
    TkStar,
    TkSlash,
    TkPercent,
    TkNum,
    TkEof,
};

struct Token {
    Index start, end;
    int line, col;
    TokenType type;
};

using TokenIter = std::vector<Token>::const_iterator;

class Tokenizer {
public:
    Tokenizer(std::string input) : m_input(input) {}
    void tokenize();

    bool has_errors() { return !m_errors.empty(); }
    void dump_errors();

    void dump_tokens();

    TokenIter iter() const { return m_tokens.cbegin(); }

private:
    struct Error {
        int line, col;
        std::string mesg;
    };

    std::string m_input;
    std::vector<Token> m_tokens;
    std::vector<Error> m_errors;
};
