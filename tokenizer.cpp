#include "tokenizer.h"
#include <iostream>

static const std::string token_names[] = {
    "TkPlus",
    "TkMinus",
    "TkNum",
    "TkEof",
};

void Tokenizer::tokenize() {
    auto iter = m_input.cbegin();
    int line = 1, col = 1;
    while (iter != m_input.cend()) {
        if (std::isdigit(*iter)) {
            auto end = iter;
            while (std::isdigit(*++end) && end != m_input.cend());
            m_tokens.push_back({ iter, end, line, col, TkNum });
            col += end - iter;
            iter = end;
        }
        else if (std::ispunct(*iter)) {
            TokenType t;
            switch (*iter) {
            case '+':
                t = TkPlus;
                break;
            case '-':
                t = TkMinus;
                break;
            default:
                m_errors.push_back({ line, col, "Unknown symbol" });
                iter++;
                col++;
                continue;
            }
            m_tokens.push_back({ iter, ++iter, line, col++, t });
        }
        else if (*iter == '\n') {
            line++;
            iter++;
        }
        else if (std::isspace(*iter)) {
            col++;
            iter++;
        }
        else {
            m_errors.push_back({ line, col, "Unknown symbol" });
            iter++;
            col++;
        }
    }
    m_tokens.push_back({ iter, iter, line, col, TkEof });
}

std::string get_data(Token& t) {
    switch (t.type) {
    case TkNum:
        return std::string(t.start, t.end);
    default:
        return "";
    }
}

void Tokenizer::dump_tokens() {
    for (auto t : m_tokens) {
        std::cout << t.line << ':' << t.col << ' ' << token_names[t.type] << ' ' << get_data(t) << '\n';
    }
}

void Tokenizer::dump_errors() {
    for (auto e : m_errors) {
        std::cerr << e.line << ':' << e.col << ' ' << e.mesg << '\n';
    }
}
