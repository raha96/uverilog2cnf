#ifndef __LIBVERILOG_MODULE_H__

#define __LIBVERILOG_MODULE_H__

#include <string>
#include <map>
#include <vector>

#include "../libmodule/libmodule.h"
#include "tokens.h"
#include "cnf.h"
#include "parse_instance.h"
#include "parse_assign.h"

class vmodule_t : public module_t
{
private:
    std::vector<std::string> portlist;
    std::map<std::string,unsigned> portmap;
    std::vector<libverilog_tokens> function_toks;
public:
    std::string operator [] (unsigned portnum) const;
    unsigned operator [] (std::string portname);
    void addinput(std::string inputname);
    void addoutput(std::string outputname);
    libverilog_tokens function_tok (unsigned num) { return function_toks[num]; }
    std::string portnames (unsigned num) { return portlist[num]; }
    unsigned ports() {return portlist.size(); }
    void addfunction_toks (libverilog_tokens func) {function_toks.push_back(func); }
};

std::string vmodule_t::operator [] (unsigned portnum) const
{
    return portlist[portnum];
}

unsigned vmodule_t::operator [] (std::string portname)
{
    return portmap[portname];
}

void vmodule_t::addinput (std::string inputname)
{
    input_list.push_back(inputname);
    portlist.push_back(inputname);
    portmap[inputname] = portlist.size() - 1;
}

void vmodule_t::addoutput (std::string outputname)
{
    input_list.push_back(outputname);
    portlist.push_back(outputname);
    portmap[outputname] = portlist.size() - 1;
}

#endif
