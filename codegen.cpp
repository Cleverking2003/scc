#include "codegen.h"

void Codegen::generate(Node& top) {
    visit(top);
}

void Codegen::emit_text_asm(std::string) {

}
