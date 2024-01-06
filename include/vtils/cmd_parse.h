/*
 *  author: Suhas Vittal
 *  date:   29 May 2023
 * */

#ifndef VTILS_CMD_PARSE_h
#define VTILS_CMD_PARSE_h

#include <iostream>
#include <map>
#include <set> 
#include <string>

#include <stdint.h>

namespace vtils {

class CmdParser {
public:
    CmdParser(int argc, char* argv[]);

    bool option_set(std::string);
    
    bool get_string(std::string, std::string&);
    bool get_float(std::string, double&);
    bool get_int32(std::string, int32_t&);
    bool get_int64(std::string, int64_t&);
    bool get_uint32(std::string, uint32_t&);
    bool get_uint64(std::string, uint64_t&);
    
    void print_all_set_options(std::ostream&);
private:
    std::set<std::string>               option_pool;
    std::map<std::string, std::string>  option_to_arg;
};

}   // vtils

#include "cmd_parse.inl"

#endif  // VTILS_CMD_PARSE_h