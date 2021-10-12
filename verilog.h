#ifndef __LIBVERILOG_VERILOG_H__

#define __LIBVERILOG_VERILOG_H__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>

#include "../libmodule/libmodule.h"

#include "utilities.h"
#include "tokens.h"
#include "module.h"

typedef std::vector<std::string> module_text;

class module_parser
{
private:
    std::vector<module_text> all_modules;
    module_text current_module;

    libverilog_tokens current_module_tokens;
    std::vector<libverilog_tokens> all_tokens;

    bool current_module_has_process = false;
    void seperate_modules (std::string line);
public:
    void process_file (const char* filename);
    void debug_print_module (int num);
    void export_module (vmodule_t* module, int num);
    
    int size()
    {
        return all_tokens.size();
    }
};

void module_parser::export_module (vmodule_t* module, int num)
{
    constexpr short IN = 1, OUT = 2, WIRE = 3, FUNC = 4;
    std::vector<std::string> things;
    std::map<std::string,short> thingtype;

    libverilog_tokens subrange;

    //std::cerr << all_tokens.size() << std::endl;
    assert(num < all_tokens.size());
    assert(all_tokens[num].exist("module"));
    module->name = all_tokens[num][all_tokens[num].find("module")+1];

    // process ports in the declaration
    libverilog_tokens portdecl, line;
    portdecl = all_tokens[num].range(all_tokens[num].find("(")+1, all_tokens[num].find(")"));
    
    int ind = 0;
    while (ind < portdecl.size())
    {
        subrange.clear();
        int newi = portdecl.find(",", ind);
        subrange = portdecl.range(ind, newi);
        //std::cerr << subrange.str() << std::endl;
        ind = newi+1;
        if (subrange.size() == 1)
            things.push_back(subrange[0]);
        else if (subrange.size() > 1)
        {
            things.push_back (subrange[1]);
            if (subrange[0] == "output")
                thingtype[subrange[1]] = OUT;
            else
                thingtype[subrange[1]] = IN;
        }
    }
    //std::cerr << "CHECKPOINT" << std::endl;

    ind = all_tokens[num].find(";") + 1;
    while (ind < all_tokens[num].size()-1)  // won't reach endmodule
    {
        line.clear();
        int newind = all_tokens[num].find(";", ind);
        line = all_tokens[num].range(ind, newind);
        ind = newind+1;
        //std::cerr << line.str() << " -> {" << line[0] << "}\n";
        short linetype;
        if (line[0] == "input")
            linetype = IN;
        else if (line[0] == "output")
            linetype = OUT;
        else if (line[0] == "wire" || line[0] == "reg") // assuming reg and wire are the same for our purposes
            linetype = WIRE;
        else
            linetype = FUNC;
        
        if (linetype == FUNC)
        {
            things.push_back(line.str_function());
            module->addfunction_toks(line);
            thingtype[things[things.size()-1]] = FUNC;
        }
        else
        {
            for (int i = 1; i < line.size(); i++)
                if (line[i] != ",")
                {
                    if (std::find(things.begin(), things.end(), line[i]) == things.end())
                        things.push_back(line[i]);
                    thingtype[line[i]] = linetype;
                }
        }
    }
    //std::cerr << "CHECKPOINT" << std::endl;

    for (int i = 0; i < things.size(); i++)
    {
        switch (thingtype[things[i]])
        {
            case IN: 
                module->addinput(things[i]);
                break;
            case OUT:
                module->addoutput(things[i]);
                break;
            case WIRE: 
                module->addoutput(things[i]);
                break;
            case FUNC:
                module->addfunction(things[i]);
                break;
            default:
                std::cerr << "Error: unrecognized token type at `" << things[i] << "`" << std::endl;
        }
    }
}

void module_parser::debug_print_module (int num)
{
    for (int i = 0; i < all_tokens[num].size(); i++)
        std::cerr << all_tokens[num][i] << ' ';
    std::cerr << std::endl;
}

void module_parser::seperate_modules (std::string line)
{
    libverilog_tokens line_tokens(line);
    if (line_tokens.exist("endmodule"))
    {
        current_module_tokens += line_tokens;
        all_tokens.push_back(current_module_tokens);
        current_module_tokens.clear();
    }
    else if (line_tokens.exist("module"))
    {
        current_module_tokens.clear();
        current_module_tokens += line_tokens;
    }
    else
    {
        if (line_tokens.size() > 0)
            current_module_tokens += line_tokens;
    }
}

void module_parser::process_file (const char* filename)
{
    std::ifstream verilog(filename);
    std::string line;

    while (!verilog.eof())
    {
        getline(verilog, line);
        line = compact_whitespaces(line);
        if (line != "")
        {
            seperate_modules (line);
        }
    }

    verilog.close();

    std::cerr << "Found " << all_tokens.size() << " module" << (all_tokens.size() == 1 ? "" : "s") << "." << std::endl;
}

#endif
