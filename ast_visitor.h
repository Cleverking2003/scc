#pragma once

#include "parser.h"

class ASTVisitor {
public:
    virtual void visit(Node&) = 0;
};
