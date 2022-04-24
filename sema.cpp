#include "sema.h"

void Sema::analyze(Node& top) {
    visit(top);
}

void Sema::dump_errors() {

}
