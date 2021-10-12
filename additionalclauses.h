#ifndef __LIBVERILOG_ADDITIONALCLAUSES_H__
#define __LIBVERILOG_ADDITIONALCLAUSES_H__

#include <fstream>
#include <vector>
#include <utility>

#include "../libcnf/libcnf.h"

typedef std::vector<std::pair<std::string,bool>> cnfsolution;

cnf solutionclause (cnfsolution& sol, variable_table vartab)
{
    cnf output;
    for (int i = 0; i < sol.size(); i++)
    {
        if (sol[i].second)
            output.add(clause(vartab[sol[i].first], 0));
        else
            output.add(clause(-vartab[sol[i].first], 0));
    }
    return output;
}

cnf_express loadsolutionfile (const char* filename)
{
    // Solution file format: 
    // <number of solutions (ensuing lines)>
    // for each solution: 
    // <number of variables in solution> <name #1> [0|1] <name #2> [0|1] ...
    cnf_express output;
    std::ifstream file (filename);
    int num;
    file >> num;
    for (int i = 0; i < num; i++)
    {
        cnf_express solution;
        int vars;
        file >> vars;
        for (int j = 0; j < vars; j++)
        {
            std::string var;
            bool val;
            file >> var >> val;
            solution.add(clause_express(var + (val ? "" : "'")));
        }
        output &= solution;
    }
    return output;
}

cnf_express loadcardinalityfile (const char* filename, bool maxsat = false)
{
    cnf_express output;
    std::ifstream file (filename);
    int num, cond;
    file >> num >> cond;
    if (cond != 1)
    {
        std::cerr << "Currently only 1-hot cardinality is supported, as the algorithm used is inefficient for";
        std::cerr << " greated values." << std::endl;
    }
    else
    {
        std::vector<std::string> vars;
        vars.resize(num);
        for (int i = 0; i < num; i++)
            file >> vars[i];
        if (maxsat)
        {
            for (int i = 0; i < num; i++)
            {
                output &= clause_express(vars[i] + "'");
                output.setlastassoft();
            }
        }
        else
        {
            for (int i = 0; i < num; i++)
                for (int j = i + 1; j < num; j++)
                    output &= clause_express(vars[i] + "'", vars[j] + "'");
            clause_express atleastone;
            for (int i = 0; i < num; i++)
                atleastone.add(vars[i]);
            output &= atleastone;
        }
    }
    file.close();
    return output;
}

#endif
