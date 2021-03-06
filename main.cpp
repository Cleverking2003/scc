#include <iostream>

#include "ast_dumper.h"
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
    t.dump_tokens();
    Parser p;
    NodePtr top = p.parse(t);
    if (p.has_errors()) {
        p.dump_errors();
        return 1;
    }
    if (top) {
        ASTDumper d;
        d.dump(*top);
        Sema s;
        s.analyze(*top);
        if (s.has_errors()) {
            s.dump_errors();
            return 1;
        }
        Codegen::Codegen c;
        c.generate(*top);
        c.emit_text_asm("out.s");
    }
    return 0;
}