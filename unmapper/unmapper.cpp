#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstdint>
#include <utility>
#include <vector>

using namespace std;

#define ISWHITESPACE(x) (x<=32)

// Maps solver output to original variable names and generates human-readable csv

bool fileexists (const char* file)
{
    ifstream fin(file);
    if (fin.fail())
        return false;
    fin.close();
    return true;
}

void printusage()
{
    cerr << "Usage: " << endl;
    cerr << "   mapper <solver-output> <uv2cnf.map> [cardinality.card]" << endl;
}

vector<string> split (string str)
{
    vector<string> output;
    bool isfirst = true;
    str += " ";
    string ctok = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (ISWHITESPACE(str[i]))
        {
            if (ctok.size() > 0)
            {
                output.push_back(ctok);
                ctok = "";
            }
        }
        else
            ctok += str[i];
    }
    return output;
}

int main (int argc, char* argv[])
{
    bool has_card = (argc == 4);
    if (argc >= 3 && argc <= 4)
    {
        bool valid = true;
        for (int i = 1; i < argc; i++)
            if (!fileexists(argv[i]))
            {
                cerr << "Invalid file name: " << argv[i] << endl;
                valid = false;
            }
        if (valid)
        {
            map<int64_t,string> varname;
            map<string,int64_t> cardvarname;
            map<int64_t,short> solution;
            vector<string> cardinality;
            ifstream mapin (argv[2]);
            string line;
            while (!mapin.eof())
            {
                getline(mapin, line);
                if (line.size() > 0)
                    if (line[0] != '#')     // ignore comments
                    {
                        vector<string> linev = split(line);
                        varname[atoi(linev[1].c_str())] = linev[0];
                        cardvarname[linev[0]] = atoi(linev[1].c_str());
                        //cerr << linev[0] << " == " << cardvarname[linev[0]] << " ; " << atoi(linev[1].c_str());
                        //cerr << " == " << varname[atoi(linev[1].c_str())] << endl;
                    }
            }
            mapin.close();

            if (has_card)
            {
                int64_t num, buf;
                string var;
                ifstream cardin (argv[3]);
                cardin >> num >> buf;
                if (buf != 1)
                    cerr << "Warning: Second token in card file should be `1`, not `" << num << "`" << endl;
                for (int i = 0; i < num; i++)
                {
                    cardin >> var;
                    cardinality.push_back(var);
                }
                cardin.close();
            }

            ifstream solin (argv[1]);
            line = "";
            while (!solin.eof())
            {
                getline(solin, line);
                if (line.size() > 0)
                {
                    // intended to support SAT and MaxSAT solver outputs simultaneously
                    if (line[0] == 'v' || (line[0] == '-') || ((line[0] >= '0') && (line[0] <= '9')))
                    {
                        // Found the solution line!
                        //cerr << "Line is " << line << endl;
                        break;
                    }
                }
            }
            solin.close();

            if (line == "")
                cerr << "Invalid solution file. Stopping" << endl;
            else
            {
                vector<string> toks = split(line);
                vector<int64_t> varlist;
                int shift = 0;
                if (toks[0] == "v")
                    shift = 1;
                for (int i = shift; i + 1 - shift < toks.size(); i++)
                {
                    int64_t cvar = atoi(toks[i].c_str());
                    varlist.push_back(abs(cvar));
                    solution[abs(cvar)] = (cvar > 0);
                    //cerr << cvar << " <= " << solution[abs(cvar)] << endl;
                }
                
                // print output to stdout
                for (int i = 0; i < varlist.size(); i++)
                {
                    cout << varname[abs(varlist[i])] << "," << solution[varlist[i]] << ";\n";
                }

                // generate subset of output corresponding to cardinality variables
                if (has_card)
                    for (int i = 0; i < cardinality.size(); i++)
                    {
                        string var = cardinality[i];
                        if (solution[cardvarname[var]])
                            cerr << var << " = " << solution[cardvarname[var]] << endl;
                    }
            }
        }
        else
            printusage();
    }
    else
        printusage();
    return 0;
}