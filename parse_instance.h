#ifndef __LIBVERILOG_PARSE_INSTANCE_H__

#define __LIBVERILOG_PARSE_INSTANCE_H__

#include <iostream>
#include <map>
#include <algorithm>

#include "../libcnf/libcnf.h"
#include "../uverilog2cnf/cells.h"

#include "module.h"
#include "logicset.h"
#include "tokens.h"

// currently only single output cells are supported
cnf_express parse_instantiation_statement (libverilog_tokens line, lib_template& library)
{
    variable_list vl;
    std::string inst_type = line[0];
    std::string inst_name = line[1];
    assert (line[2] == "(");
    assert (line[line.size()-1] == ")");
    line = line.range(3, line.size() - 1);
    bool byposition = true;
    if (line.exist("("))
        byposition = false;
    libverilog_tokens ctok;
    std::map<std::string,std::string> ports;
    unsigned comma;
    while (line.size() > 0)
    {
        comma = line.find(",");
        ctok = line.range(0, comma);
        line = line.range(comma+1, line.size());
        if (byposition)
        {
            assert (ctok.size() == 1);
            vl.add(ctok[0]);
        }
        else
        {
            assert (ctok.size() == 5);
            ports[ctok[1]] = ctok[3];
        }
    }
    if (!byposition)
    {
        if (!(ports.size() == library.portnum[inst_type]))
            std::cerr << library.portnum[inst_type] << ":" << ports.size() << std::endl;
        assert (ports.size() == library.portnum[inst_type]);
        for (int i = 0; i < library.portnum[inst_type]; i++)
        {
            vl.add(ports[library(inst_type)[i]]);
        }
    }
    return express_cnf(library[inst_type], vl);
}

#endif
