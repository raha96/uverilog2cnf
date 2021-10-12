#ifndef __LIBVERILOG_LOGICSET_H__

#define __LIBVERILOG_LOGICSET_H__

#include <vector>
#include <string>
#include <stack>
#include <map>
#include <queue>
#include <sstream>
#include <cassert>
#include <algorithm>

//logicset::clausestring logicset::tokenize (clausestring& invec, std::string delim);
//logicset::node* logicset::createtree (logicset::clausestring str, std::string opening, std::string closing);
//void logicset::restructtree (logicset::node* head, std::string op);
//template <typename...T> void expandtokenset (tokenset& set, std::string token, T...arg);

namespace logicset
{
    typedef std::vector<std::string> clausestring;
    typedef std::vector<std::string> tokenset;
    typedef std::vector<clausestring> functionstring;
    typedef std::map<std::string,unsigned> clausedic;

    struct node
    {
        std::string value, id;
        node *l = nullptr, *r = nullptr, *p = nullptr;
        // lest, right, parent
    };

    void attachtokens (tokenset& set1, tokenset set2)
    {
        for (int i = 0; i < set2.size(); i++)
            set1.push_back(set2[i]);
    }

    tokenset expandtokenset (tokenset& set)
    {
        return tokenset();
    }
    template <typename...T> void expandtokenset (tokenset& set, std::string token, T...arg)
    {
        set.push_back (token);
        expandtokenset (set, arg...);
    }

    clausestring tokenize (clausestring& invec, std::string delim)
    {
        clausestring outvec;
        for (int i = 0; i < invec.size(); i++)
        {
            std::string str = invec[i];
            auto pos = str.find(delim);
            while (pos != str.npos)
            {
                outvec.push_back (str.substr(0, pos));
                outvec.push_back(delim);
                str = str.substr (pos + delim.size());
                pos = str.find(delim);
            }
            outvec.push_back(str);
        }
        return outvec;
    }

    template<typename T> bool member (T item, std::vector<T> set)
    {
        for (int i = 0; i < set.size(); i++)
            if (set[i] == item)
                return true;
        return false;
    }

    std::string namestring (std::string name, int num)
    {
        std::stringstream ss(name);
        ss << num;
        return ss.str();
    }

    //functionstring embrace (clausestring str, std::string basename, std::string opening, std::string closing, clausedic& dic)
    node* embrace (clausestring str, std::string opening, std::string closing)
    {
        node* root = new node;
        std::stack<node*> parent;
        node* cnode = root;
        assert (str.size() > 0);
        // assuming the first token is not a brace of any kind
        cnode->value = str[0];
        bool isempty = false;
        for (int i = 1; i < str.size(); i++)
        {
            if (str[i] == opening)
            {
                cnode->l = new node;
                cnode->l->p = cnode;
                parent.push(cnode);
                cnode = cnode->l;
                isempty = true;
            }
            else if (str[i] == closing)
            {
                cnode = parent.top();
                parent.pop();
                isempty = (cnode->value == "");
            }
            else
            {
                if (!isempty)
                {
                    cnode->r = new node;
                    cnode->r->p = cnode;
                    cnode = cnode->r;
                }
                cnode->value = str[i];
                isempty = false;
            }
        }
        return root;
    }
    /*{
        functionstring out;
        if (str.size() > 0)
        {
            std::stack<std::string> sstack;
            int clausenum = 0;
            for (int i = 0; i < str.size(); i++)
            {
                if (str[i] == closing || i == str.size() - 1)
                {
                    clausestring clause;
                    while (sstack.top() != opening)
                    {
                        clause.push_back(sstack.top());
                        sstack.pop();
                    }
                    sstack.pop();
                    std::reverse(clause.begin(), clause.end());
                    if (clause.size() > 0)
                    {
                        std::string cname = namestring(basename, clausenum);
                        sstack.push(cname);
                        dic[cname] = out.size();
                        out.push_back(clause);
                    }
                }
                else
                    sstack.push(str[i]);
            }
        }
        return out;
    }*/
    //unneeded
    void branch (node* root, node* vertex)
    {
        //assert (root->l == nullptr);
        assert (vertex->l == nullptr);
        assert (root != vertex);

        node* tmp = vertex, *swp = vertex->p;
        while (swp != root)
        {
            tmp = swp;
            swp = tmp->p;
            tmp->p = tmp->r;
            tmp->r = swp;
        }
        tmp->p = tmp->r;
        tmp->r = nullptr;

        vertex->l = vertex->p;
        vertex->l->p = vertex;
        
        root->r = vertex;
        vertex->p = root;
    }
    // unneeded
    /*
    node* attachfunctionstring (functionstring fstr, clausedic& dic)
    {
        assert(fstr.size() > 0);
        std::queue<clausestring&> q;
        node* root = new node;
        node* head = root;
        q.push(fstr[0]);
        while (q.size() > 0)
        {
        }
    }
    */

    /*{
        node* root = new node;
        node* head = root;
        for (int i = 0; i < fstr.size(); i++)
        {
            node* child = head;
            assert(fstr[i].size() > 0);
            child->value = fstr[i][0];
            for (int j = 1; j < fstr[i].size(); j++)
            {
                child->r = new node;
                child->r->p = child;
                child = child->r;
                child->value = fstr[i][j];
            }
            if (i < fstr.size() - 1)
            {
                head->l = new node;
                head->l->p = head;
                head = head->l;
            }
        }
        return root;
    }*/

    //node* createtree (clausestring str, std::string basename, std::string opening, std::string closing)
    node* createtree (clausestring str, std::string opening, std::string closing)
    {
        //clausedic dic;
        //return attachfunctionstring (embrace(str, basename, opening, closing, dic), dic);
        return embrace(str, opening, closing);
    }

    void restructtree (node* head, std::string op)
    {
        //assert (head->l == nullptr);
        if (head->l != nullptr)
            restructtree (head->l, op);
        
        node *newhead = head, *temp, *mainhead = head;
        bool first = true;
        while (newhead->r != nullptr)
        {
            while (newhead->value != op && newhead->r != nullptr)
            {
                newhead = newhead->r;
            }
            if (newhead->r == nullptr)  // found no operator
                break;
            if (first)
            {
                mainhead = head;
                first = false;
            }
            branch(head, newhead);
            head = newhead;
            newhead = newhead->r;
        }
        head = mainhead;
    }
};

#endif
