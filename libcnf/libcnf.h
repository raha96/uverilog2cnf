#ifndef __LIBCNF_H__

#define __LIBCNF_H__

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <map>
#include <cstdarg>
#include <sstream>

// TODO: remove extraneous includes

#include "dispatch.h"

#define VERBOSE
#ifdef VERBOSE
#define LOG(x) std::cerr<<"Passed line "<<__LINE__<<" @ file "<< __FILE__<<": "<<x<<std::endl;
#else
#define LOG(x) ;
#endif

#define abs(x) (x>=0?x:(-x))

template <typename T> class __cnf_temp_class
{
protected:
    std::vector<T> things;
public:
    void __CTOR () {}
    template <typename...X> void __CTOR (T item, X...args)
    {
        things.push_back(item);
        __CTOR (args...);
    }

    __cnf_temp_class() {}
    template <typename...X> __cnf_temp_class (T item, X...args)
    {
        __CTOR (item, args...);
    }

    T& operator [] (int num)
    {
        return things[num];
    }

    int size()
    {
        return things.size();
    }

    void resize (unsigned size)
    {
        things.resize(size);
    }

    void add (T item)
    {
        things.push_back (item);
    }
};

template <typename T> std::ostream& operator << (std::ostream& stream, __cnf_temp_class<T>& obj)
{
    for (int i = 0; i < obj.size(); i++)
        stream << obj[i] << ' ';
    return stream;
}

class assignment : public __cnf_temp_class<unsigned short> {using __cnf_temp_class::__cnf_temp_class; };
class clause : public __cnf_temp_class<int32_t>
{
    using __cnf_temp_class::__cnf_temp_class;
public: 
    bool eval (assignment& value)
    {
        int index;
        bool condition;
        for (int i = 0; i < size(); i++)
        {
            index = abs((*this)[i])-1;
            condition = ((*this)[i] > 0);
            if (value[index] == condition)
                return true;
        }
        return false;
    }
    void add (int v)
    {
        things.push_back(v);
    }
};

class cnf_express;
class cnf : public __cnf_temp_class<clause>
{
    using __cnf_temp_class::__cnf_temp_class;
    std::vector<bool> clauseissoft;
public:
    bool eval (assignment& value)
    {
        for (int i = 0; i < size(); i++)
            if (!(*this)[i].eval(value))
                return false;
        return true;
    }

    int varnum()
    {
        int out = 0;
        for (int i = 0; i < size(); i++)
            for (int j = 0; j < things[i].size(); j++)
                out = out > abs(things[i][j]) ? out : abs(things[i][j]);
        return out;
    }

    void add (clause cc)
    {
        clauseissoft.resize(things.size());
        things.push_back(cc);
        clauseissoft.push_back(false);
    }

    void addhard (clause cc)
    {
        clauseissoft.resize(things.size());
        things.push_back(cc);
        clauseissoft.push_back(true);
    }

    std::string wcnf()
    {
        std::stringstream stream;
        int maxweight = 2;
        clauseissoft.resize(things.size());
        stream << "c uv2cnf (Upgraded Verilog to CNF), wcnf file tailored for partial maxsat\n";
        stream << "p wcnf " << varnum() << ' ' << size() << ' ' << maxweight << '\n';
        for (int i = 0; i < size(); i++)
        {
            if (!clauseissoft[i])
                stream << maxweight;
            else
                stream << 1;
            stream << ' ';
            for (int j = 0; j < (*this)[i].size(); j++)
                stream << (*this)[i][j] << ' ';
            stream << "0\n";
        }
        return stream.str();
    }

    friend cnf cnf_express_to_cnf (cnf_express&, variable_table&);
};

class portlist : public __cnf_temp_class<std::string> {using __cnf_temp_class::__cnf_temp_class; };
typedef std::map<std::string,cnf> celllib_t;

class lib_template
{
    // assuming all gates are single output and the output variable is 1
public:
    celllib_t cells;
    std::map<std::string,portlist> portlists;
    std::map<std::string,std::string> output;
    std::map<std::string,unsigned> portnum;
    cnf& operator [] (std::string name)
    {
        return cells[name];
    }
    portlist& operator () (std::string name)
    {
        return portlists[name];
    }
    void addcell (std::string name, cnf function, portlist ports, unsigned portnum)
    {
        cells[name] = function;
        portlists[name] = ports;
        this->portnum[name] = portnum;
    }
};

std::ostream& operator << (std::ostream& stream, cnf func)
{
    stream << "c uv2cnf (Upgraded Verilog to CNF)\n";
    stream << "p cnf " << func.varnum() << ' ' << func.size() << '\n';
    for (int i = 0; i < func.size(); i++)
    {
        for (int j = 0; j < func[i].size(); j++)
            stream << func[i][j] << ' ';
        stream << "0\n";
    }
    return stream;
}

class variable_list : public __cnf_temp_class<std::string>
{
    using __cnf_temp_class::__cnf_temp_class;
public:
    std::string operator [] (int index)
    {
        std::string out = things[abs(index)-1];
        if (index < 0)
            out += "'";
        return out;
    }
};

std::ostream& operator << (std::ostream& stream, variable_list& list)
{       // TODO: fix
    if (list.size() == 0)
        return stream;
    stream << '{' << list[1];
    for (int i = 2; i <= list.size(); i++)
        stream << ", " << list[i];
    stream << '}';
    return stream;
}

class clause_express : public __cnf_temp_class<std::string>
{
    using __cnf_temp_class::__cnf_temp_class;
};
class hardclause_express : public __cnf_temp_class<std::string>
{
    using __cnf_temp_class::__cnf_temp_class;
};

std::ostream& operator << (std::ostream& stream, clause_express cle)
{
    if (cle.size() == 0)
        return stream;
    stream << cle[0];
    for (int i = 1; i < cle.size(); i++)
        stream << '+' << cle[i];
    return stream;
}

class cnf_express : public __cnf_temp_class<clause_express>
{
    using __cnf_temp_class::__cnf_temp_class;
    std::vector<bool> clauseissoft;
public: 
    void operator &= (cnf_express param)
    {
        clauseissoft.resize(size());
        param.clauseissoft.resize(param.size());
        for (int i = 0; i < param.size(); i++)
        {
            this->add(param[i]);
            clauseissoft.push_back(param.clauseissoft[i]);
        }
    }

    void addsoft (clause_express clause)
    {
        clauseissoft.resize(size());
        add(clause);
        clauseissoft.push_back(true);
    }

    void setlastashard ()
    {
        clauseissoft.resize(size());
        clauseissoft[size()-1] = false;
    }
    void setlastassoft ()
    {
        clauseissoft.resize(size());
        clauseissoft[size()-1] = true;
        LOG((*this)[size()-1] << " was marked as soft");
    }

    friend cnf cnf_express_to_cnf (cnf_express&, variable_table&);
};

std::ostream& operator << (std::ostream& stream, cnf_express cnfe)
{
    for (int i = 0; i < cnfe.size(); i++)
        stream << '(' << cnfe[i] << ')';
    return stream;
}

void dump_cnf (cnf func, variable_table& lut)
{
    for (int i = 0; i < func.size(); i++)
    {
        std::cout << "(" << lut[func[i][0]];
        for (int j = 0; j < func[i].size(); j++)
            std::cout << "+" << lut[func[i][j]];
        std::cout << ")";
    }
}

cnf_express express_cnf (cnf& func, variable_table& vars)
{
    cnf_express out;
    out.resize(func.size());
    for (int i = 0; i < func.size(); i++)
    {
        out[i].resize(func[i].size());
        for (int j = 0; j < func[i].size(); j++)
            out[i][j] = vars[func[i][j]];
    }
    return out;
}

cnf_express express_cnf (cnf& func, variable_list varlist)
{
    cnf_express out;
    out.resize(func.size());
    for (int i = 0; i < func.size(); i++)
    {
        out[i].resize(func[i].size());
        for (int j = 0; j < func[i].size(); j++)
        {
            out[i][j] = varlist[func[i][j]];
        }
    }
    return out;
}

cnf cnf_express_to_cnf (cnf_express& func, variable_table& vars)
{
    LOG("");
    cnf out;
    out.resize(func.size());
    for (int i = 0; i < func.size(); i++)
    {
        out[i].resize(func[i].size());
        for (int j = 0; j < func[i].size(); j++)
            out[i][j] = vars[func[i][j]];
    }
    LOG("");
    func.clauseissoft.resize(func.size());
    out.clauseissoft.resize(out.size());
    LOG("");
    for (int i = 0; i < out.size(); i++)
    {
        out.clauseissoft[i] = func.clauseissoft[i];
        if (func.clauseissoft[i])
            LOG(func[i] << " is soft");
    }
    LOG("");
    return out;
}

#endif
