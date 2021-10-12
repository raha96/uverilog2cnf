#ifndef __LIBVERILOG_UTILITIES_H__

#define __LIBVERILOG_UTILITIES_H__

#include <string>

enum brackettype {nonbracket, openbracket, closebracket};

const std::string operators[36] = {"[", "]", "(", ")", "!", "~", "&", "|", "~&", "~|", "^", "~^", "^~", 
                                   "+", "-", "*", "/", "%", "<<", ">>", ">", ">=", "<", "<=", "==", "!=", 
                                   "===", "!==", "&&", "||", "?", ":", "=", "{", "}", ","};

std::string unify_op_symbol (std::string op)
{
    // intended for single bit use
    if (op == "!" || op == "~")
        return "!";
    if (op == "&" || op == "*" || op == "&&")
        return "&";
    if (op == "|" || op == "+" || op == "||")
        return "|";
    if (op == "^" || op == "!=" || op == "!==")
        return "^";
    if (op == "~^" || op == "^~" || op == "==" || op == "===")
        return "#";
    return op;
}

std::string op2str (std::string str)
{
    if (str == "!")
        return "not";
    if (str == "&")
        return "and";
    if (str == "|")
        return "or";
    if (str == "^")
        return "xor";
    if (str == "=")
        return "xnor";
    return str;
}

bool is_op (std::string str)
{
    if (str == "!" || str == "&" || str == "|" || str == "^" || str == "=")
        return true;
    if (str == ">" || str == ">=" || str == "<" || str == "<=")
        return true;
    return false;
}

inline bool is_whitespace (char ch)
{
    return (ch <= 32);
}

inline bool is_op (char ch)
{
    if (ch >= '0' && ch <= '9')
        return false;
    if (ch >= 'a' && ch <= 'z')
        return false;
    if (ch >= 'A' && ch <= 'Z')
        return false;
    if (ch == '_')
        return false;
    return true;
}

std::string uint2str (unsigned num)
{
    std::string out = "", buf;
    while (num)
    {
        buf = char('0' + (num % 10));
        out = buf + out;
        num /= 10;
    }
    return out;
}

inline brackettype is_bracket (char ch)
{
    if (ch == '(' || ch == '[' || ch == '{')
        return openbracket;
    if (ch == ')' || ch == ']' || ch == '}')
        return closebracket;
    return nonbracket;
}

std::string compact_whitespaces (std::string exp)
{
    if (exp.size() == 0)
         return "";
	std::string out;
	int first = 0, last = exp.size() - 1;
	while (is_whitespace(exp[first]) && first < exp.size()-1) first++;
	while (is_whitespace(exp[last] ) && last  > 0) last--;
    //std::cout << exp << " ~ " << first << " ~ " << last-first << std::endl;
	out = exp.substr(first, last-first+1);
    //std::cout << out << std::endl;

    int i = 0;
    if (out.size() > 1)
        while (i>0)
        {
            if (is_whitespace(out[i]) && (is_op(out[i+1])))
                out.erase(out.begin() + i);
            else if (is_op(out[i]) && is_whitespace(out[i+1]))
                out.erase(out.begin() + i + 1);
            else
                i++;
            if (i >= out.size() - 1)
                break;
        }
    //std::cout << out.size() << std::endl;
    for (int i = 0; i < out.size(); i++)
        if (is_whitespace(out[i]))
            out[i] = ' ';
	return out;
}

#endif
