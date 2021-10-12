#ifndef __LIBVERILOG_PARSE_ASSIGN_H__

#define __LIBVERILOG_PARSE_ASSIGN_H__

#include <string>
#include <vector>
#include <cassert>
#include <stack>

#include "libcnf/libcnf.h"

#include "tokens.h"
#include "utilities.h"
#include "verilog.h"
#include "cnf.h"
#include "logicset.h"

// The subset implemented here assumes all operations are single-bit.

void traverser (logicset::node* v)
{
    assert (v != nullptr);
}

void prioritized_search (logicset::node* v, void(*func)(logicset::node*) = &traverser, bool after = false)
{
    if (!after)
        func(v);
    if (v->l != nullptr)
        prioritized_search(v->l, func);
    if (v->r != nullptr)
        prioritized_search(v->r, func);
    if (after)
        func(v);
}

void prioritized_search (logicset::node* v, void (*func)(logicset::node*, auto&), auto& arg, bool after = false)
{
    if (!after)
        func(v, arg);
    if (v->l != nullptr)
        prioritized_search(v->l, func, arg, after);
    if (v->r != nullptr)
        prioritized_search(v->r, func, arg, after);
    if (after)
        func(v, arg);
}

void unify_operators (logicset::node* v)
{
    std::cerr << "<" << v->value << ":";
    v->value = unify_op_symbol (v->value);
    std::cerr << v->value << ">" << std::endl;
}

void fix_assignment (logicset::node* root)
{
    logicset::node* node = root;
    while (node != nullptr && node->value != "=")
        node = node->r;
    assert (node != nullptr);
    assert (node->l != nullptr);
    std::string outputid = node->l->id;
    while (!is_op(node->r->value))
        node = node->r;
    std::cerr << "altered " << node->r->value << " : " << node->r->id << " to " << outputid << std::endl;
    node->r->id = outputid;
}

void fix_nodeid (logicset::node* node, int& cid)
{
    if (is_op(node->value))
    {
        node->id = op2str(node->value) + uint2str(cid);
        cid++;
    }
    else
        node->id = node->value;
}

void switch_childs (logicset::node* node)     // move left child to right if right is empty
{
    if (node->r == nullptr && node->l != nullptr)
    {
        node->r = node->l;
        node->l = nullptr;
    }
}

logicset::node* parse_assign_statement (std::string str)
{
    logicset::clausestring clause, ops;
    clause.push_back (str);
    logicset::expandtokenset (ops, "[", "]", "(", ")", "!", "~", "&", "|", "~&", "~|", "^", "~^", "^~", 
                                   "+", "-", "*", "/", "%", "<<", ">>", ">", ">=", "<", "<=", "==", "!=", 
                                   "===", "!==", "&&", "||", "?", ":", "=", "{", "}", ",");
    for (int i = 0; i < ops.size(); i++)
        clause = logicset::tokenize (clause, ops[i]);
    logicset::node* tree = new logicset::node;
    tree = logicset::createtree (clause, "(", ")");
    for (int i = 0; i < ops.size(); i++)
        logicset::restructtree (tree, ops[i]);
    
    prioritized_search(tree, unify_operators);
    int id1 = 1;
    prioritized_search(tree, fix_nodeid, id1);
    prioritized_search(tree, switch_childs);

    return tree;
}

void addclause (logicset::node* node, cnf_express& expression)
{
    if (is_op(node->value))
    {
        lib_verilog_parser lut;
        std::string out = "", in1 = "", in2 = "";
        out = node->id;
        std::cerr << node->value << ' ' << node->id << std::endl;
        if (node->r == nullptr)
            assert (node->l != nullptr);
        assert (node->r != nullptr);
        in2 = node->r->id;
        if (node->l != nullptr)
            in1 = node->l->id;
        if (node->value == "!")
        {
            variable_list list(out, in2);
            expression &= express_cnf(lut["!"], list);
        }
        else
        {
            assert (in1 != "");
            variable_list list(out, in1, in2);
            expression &= express_cnf(lut[node->value], list);
        }
    }
}

cnf_express verilogexp_to_cnf_express (logicset::node* root)
{
    cnf_express out;
    prioritized_search(root, addclause, out);
    return out;
}

cnf_express module2cnf (vmodule_t& module, lib_template& library)
{
    cnf_express output;
    for (int i = 0; i < module.functions(); i++)
    {
        std::string cfunc = module.function(i);
        if (cfunc.find('=') == cfunc.npos)
        {
            output &= parse_instantiation_statement (module.function_tok(i), library);
        }
        else
        {
            std::cerr << "WARNING: Assign statement support is incomplete and buggy and may fail." << std::endl;
            output &= verilogexp_to_cnf_express (parse_assign_statement (cfunc));
        }
    }
    return output;
}

variable_table module_variable_table (vmodule_t& module)
{
    variable_table output;
    for (int i = 0; i < module.inputs(); i++)
        output.add(module.input(i));
    for (int i = 0; i < module.outputs(); i++)
        output.add(module.output(i));
    for (int i = 0; i < module.wires(); i++)
        output.add(module.wire(i));
    return output;
}

#endif
