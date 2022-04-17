#include <iostream>

#include "codegen.h"
#include "parser.h"
#include "sema.h"
#include "tokenizer.h"

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Usage: scc <input string>\n";
        return 1;
    }
    std::string input(argv[1]);
    Tokenizer t(input);
    t.tokenize();
    if (t.has_errors()) {
        t.dump_errors();
        return 1;
    }
    Parser p(t);
    Node top = p.parse();
    if (p.has_errors()) {
        p.dump_errors();
        return 1;
    }
    Sema s;
    s.analyze(top);
    if (s.has_errors()) {
        s.dump_errors();
        return 1;
    }
    Codegen c;
    c.generate(top);
    c.emit_text_asm("out.asm");
    return 0;
}