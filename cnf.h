#ifndef __LIBVERILOG_CNF_H__

#define __LIBVERILOG_CNF_H__

#include <string>

#include "../libcnf/libcnf.h"
#include "module.h"

// supported gates: ! & | ^ = > >= < <=

class lib_verilog_parser : public lib_template
{
public:
    lib_verilog_parser()
    {
        // All cells are output-first (verilog-like)
        cells["!"] = cnf(clause(1, 2), clause(-1, -2));
        cells["&"] = cnf(clause(-1, 2), clause(-1, 3), clause(1, -2, -3));
        cells["|"] = cnf(clause(1, -2), clause(1, -3), clause(-1, 2, 3));
        cells["^"] = cnf(clause(1, 2, -3), clause(1, -2, 3), clause(-1, 2, 3), clause(-1, -2, -3));
        cells["#"] = cnf(clause(-1, -2, 3), clause(-1, 2, -3), clause(1, -2, -3), clause(1, 2, 3));
        cells[">"] = cnf(clause(-1, -3), (-1, 2, 3), (1, -2, 3));
        cells[">="]= cnf(clause(1, -2), (1, 2, 3), (-1, 2, -3));
        cells["<"] = cnf(clause(-1, -2), clause(-1, 2, 3), clause(1, 2, -3));
        cells["<="]= cnf(clause(1, -3), clause(-1, -2, 3), clause(1, -2, 3));
        // TODO : check all of these clauses! :'(
    }
};

#endif
