#include "sema.h"

void Sema::analyze(Node& top) {
    visit(top);
}

void Sema::visit(Node& n) {
    (void)n;
}

void Sema::dump_errors() {

}
