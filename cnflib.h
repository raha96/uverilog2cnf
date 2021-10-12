#ifndef __LIBVERILOG_CNFLIB_H__

#define __LIBVERILOG_CNFLIB_H__

#include <string>
#include <fstream>

#include "../libcnf/libcnf.h"
#include "module.h"

// supported gates: ! & | ^ = > >= < <=

class cnflib : public lib_template
{
public:
    cnflib() {}
    cnflib (const char* filename) {loadfile(filename); }

    void loadfile (const char* cnflibfile)
    {
        // Format:
        // <number of cells>
        // for each cell: 
        // <name> <number-of-ports> <number-of-clauses>
        // <port1-name> <port2-name> ...
        // clause lines use the standard cnf format.
        std::ifstream file (cnflibfile);
        int n;
        file >> n;
        for (int i = 0; i < n; i++)
        {
            cnf cellfunc;
            portlist ports;
            std::string name;
            int clauses, vars;
            file >> name >> vars >> clauses;
            for (int j = 0; j < vars; j++)
            {
                std::string name;
                file >> name;
                ports.add(name);
            }
            for (int j = 0; j < clauses; j++)
            {
                int vnum;
                clause cclause;
                file >> vnum;
                while (vnum != 0)
                {
                    cclause.add(vnum);
                    file >> vnum;
                }
                cellfunc.add(cclause);
            }
            addcell(name, cellfunc, ports, vars);
        }
        file.close();
    }
};

#endif
