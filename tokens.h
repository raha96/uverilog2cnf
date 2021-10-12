#ifndef __LIBVERILOG_TOKENS_H__

#define __LIBVERILOG_TOKENS_H__

#include <vector>
#include <string>
#include <cassert>

#include "utilities.h"

class libverilog_tokens
{
private:
    std::vector<std::string> tokens;

    void add (std::string tok) {tokens.push_back (tok); }
public:
    libverilog_tokens () {}
    libverilog_tokens (std::string str);

    void operator += (libverilog_tokens& tokenlist)
    {
        for (int i = 0; i < tokenlist.size(); i++)
            if (tokenlist.tokens[i] != "")
                tokens.push_back (tokenlist.tokens[i]);
    }

    std::string& operator [] (unsigned num) {return tokens[num]; }

    std::string str (int first)
    {
        std::string out = "";
        for (int i = first; i < tokens.size(); i++)
            out += tokens[i];
        return out;
    }
    std::string str () {return str(0); }

    std::string str_function()
    {
        if (tokens[0] == "assign")
            return str(1);
        return str(0);
    }

    libverilog_tokens range (unsigned begin, unsigned end)
    {
        //assert (begin <= size());
        //assert (end <= size());
        libverilog_tokens output;
        for (unsigned i = begin; i < end && i < size(); i++)
            output.add (tokens[i]);
        return output;
    }

    unsigned size() {return tokens.size(); }
    void clear() {tokens.clear(); }

    unsigned find (std::string tok, unsigned begin)
    {
        //assert (begin < size());
        int i;
        for (i = begin < size() ? begin : size(); i < size(); i++)
            if (tokens[i] == tok)
                break;
        assert (i <= size());
        return i;
    }
    unsigned find (std::string tok) {return find(tok, 0); }
    bool exist (std::string tok) {return (find(tok) < size()); }
};

libverilog_tokens::libverilog_tokens (std::string str)
{
    // TODO : add comment removal
    std::string ctok = "";
    str += " ";
    for (int i = 0; i < str.size(); i++)
    {
        if (is_op(str[i]))
        {
            //std::cerr << ctok << std::endl;
            if (ctok != "")
            {
                //std::cout << " ~" << ctok << "~ ";
                tokens.push_back(ctok);
            }
            if (!is_whitespace(str[i]))
            {
                ctok = str[i];
                tokens.push_back(ctok);
            }
            ctok = "";
        }
        else
            ctok += str[i];
    }
}

#endif
