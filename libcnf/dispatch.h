#ifndef __LIBCNF_DISPATCH_H__

#define __LIBCNF_DISPATCH_H__

#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <algorithm>

class variable_table
{
private:
    std::vector<std::string> names;
    std::map<std::string,uint32_t> nums;

    void vartab_CTOR() {}
    template <typename...T> void vartab_CTOR (std::string vname, T...args)
    {
        add (vname);
        vartab_CTOR(args...);
    }
public:
    variable_table() {}
    template <typename...T> variable_table(T...args) {vartab_CTOR(args...); }

    int32_t operator [] (std::string name);
    std::string operator [] (int32_t num);

    void add (std::string name)
    {
        // TODO: improve search time complexity
        if (std::find(names.begin(), names.end(), name) == names.end())
        {
            names.push_back(name);
            nums[name] = names.size();
        }
    }

    void dump (const char* filename)
    {
        std::ofstream map_file (filename, std::fstream::out);
        map_file << "# Map of signal names to variable indexes" << std::endl;
        map_file << "# By uv2cnf" << std::endl;
        map_file << "# " << names.size() << " variables" << std::endl;
        for (int i = 0; i < names.size(); i++)
            map_file << names[i] << ' ' << i+1 << std::endl;
        map_file.close();
    }

    unsigned size()
    {
        return names.size();
    }
};

int32_t variable_table::operator [] (std::string name)
{
    if (name.size() == 0)
        return 0;
    if (name[name.size()-1] == '\'' || name[0] == '~')
    {
        return -int32_t(this->nums[name.substr(0, name.size()-1)]);
    }
    return this->nums[name];
}

std::string variable_table::operator [] (int32_t num)
{
    std::string out = names[abs(num) - 1];
    if (num < 0)
        out += "'";
    return out;
}

#endif
