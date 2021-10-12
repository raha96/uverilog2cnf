#include <iostream>
#include <fstream>
#include <cstring>

#include "libverilog.h"

#define VERBOSE
#ifndef LOG
    #ifdef VERBOSE
    #define LOG(x) cerr<<"Passed line "<<__LINE__<<" @ file "<< __FILE__<<": "<<x<<endl;
    #else
    #define LOG(x) ;
    #endif
#endif

using namespace std;

bool fileexists (const char* file)
{
    ifstream fin(file);
    if (fin.fail())
        return false;
    fin.close();
    return true;
}

int main (int argc, char* argv[])
{
    if (argc == 1)
    {
        cout << "Usage: " << endl;
        cout << "   uverilog2cnf <parameters>" << endl;
        cout << "Parameters: " << endl;
        cout << "   Mandatory: " << endl;
        cout << "       -v [input.v]                                " << endl;
        cout << "       -l [library.cnflib]                         " << endl;
        cout << "   Optional: " << endl;
        cout << "       -c cnf output prefix (default=outcnf_)      " << endl;
        cout << "       -m map output prefix (default=outmap_)      " << endl;
        cout << "       -s [solution.sol]                           " << endl;
        cout << "       -d [cardinality.card]                       " << endl;
        cout << "" << endl;
        cout << "       -x Generate cardinality constraints in terms of MaxSAT constraints (requires " << endl;
        cout << "          cardinality constraints file)" << endl;
    }
    else
    {
        char *path_verilog, *path_cnflib, *path_card, *path_sol;
        char* path_cnfout = new char[8];
        char* path_mapout = new char[8];
        bool has_card = false, has_sol = false;
        bool valid_v = false, valid_cnflib = false;
        bool maxsat = false;

        strcpy (path_cnfout, "outcnf_");
        strcpy (path_mapout, "outmap_");

        for (int i = 1; i < argc; i++)
        {
            LOG("");
            if (strcmp(argv[i], "-v") == 0)
            {
                LOG("");
                if (argc <= (i+1) || (!fileexists(argv[i+1])))
                    cerr << "Invalid verilog file path." << endl;
                else
                {
                    LOG("");
                    valid_v = true;
                    path_verilog = argv[i+1];
                }
                i++;
            }
            else if (strcmp(argv[i], "-l") == 0)
            {
                LOG("");
                if (argc <= (i+1) || (!fileexists(argv[i+1])))
                    cerr << "Invalid cnflib file path." << endl;
                else
                {
                    LOG("");
                    valid_cnflib = true;
                    path_cnflib = argv[i+1];
                }
                i++;
            }
            else if (strcmp(argv[i], "-d") == 0)
            {
                LOG("");
                if (argc <= (i+1) || (!fileexists(argv[i+1])))
                    cerr << "Invalid card file path." << endl;
                else
                {
                    LOG("");
                    has_card = true;
                    path_card = argv[i+1];
                }
                i++;
            }
            else if (strcmp(argv[i], "-s") == 0)
            {
                LOG("");
                if (argc <= (i+1) || (!fileexists(argv[i+1])))
                    cerr << "Invalid sol file path." << endl;
                else
                {
                    LOG("");
                    has_sol = true;
                    path_sol = argv[i+1];
                }
                i++;
            }
            else if (strcmp(argv[i], "-x") == 0)
                maxsat = true;
            else if (strcmp(argv[i], "-c") == 0)
            {
                if (argc <= i+1)
                    cerr << "Expected output cnf prefix." << endl;
                else
                {
                    path_cnfout = argv[i+1];
                    i++;
                }
            }
            else if (strcmp(argv[i], "-m") == 0)
            {
                if (argc <= i+1)
                    cerr << "Expected output map prefix." << endl;
                else
                {
                    path_mapout = argv[i+1];
                    i++;
                }
            }
            else
                cerr << "Invalid argument: " << argv[i] << endl;
            LOG("");
        }

        if ((!valid_cnflib) || (!valid_v))
            cerr << "Invalid arguments. Stopping" << endl;
        else if (maxsat && (!has_card))
            cerr << "Cannot generate MaxSAT constraints without cardinality file. Stopping" << endl;
        else
        {
            module_parser mp;
            cnflib library (path_cnflib);
            mp.process_file(path_verilog);
            for (int num = 0; num < mp.size(); num++)
            {
                vmodule_t mod;
                mp.export_module(&mod, num);

                cout << "MODULE: " << mod.name << endl;

                cout << "Parsing content..." << endl;
                cnf_express func = module2cnf(mod, library);
                variable_table vartab = module_variable_table(mod);
                if (has_sol)
                {
                    cout << "Using solution in " << path_sol << endl;
                    func &= loadsolutionfile (path_sol);
                }
                if (has_card)
                {
                    cout << "Using cardinality constraints defined in " << path_card << endl;
                    func &= loadcardinalityfile(path_card, maxsat);
                }
                //cout << func << endl;
                
                LOG("");
                cnf output = cnf_express_to_cnf (func, vartab);
                LOG("");
                string cnfpath = string(path_cnfout) + mod.name, mappath = string(path_mapout) + mod.name + ".map";
                LOG("");
                if (maxsat)
                {
                    cnfpath +=  + ".wcnf";
                    ofstream cnfout(cnfpath);
                    cnfout << output.wcnf() << endl;
                    cnfout.close();
                }
                else
                {
                    cnfpath +=  + ".cnf";
                    ofstream cnfout(cnfpath);
                    cnfout << output << endl;
                    cnfout.close();
                }
                LOG("");
                vartab.dump(mappath.c_str());
                cout << "Output CNF saved to " << cnfpath << " and variable map to " << mappath << "." << endl;
            }
        }
    }
    return 0;
}
