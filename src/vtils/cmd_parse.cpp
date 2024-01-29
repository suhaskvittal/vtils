/*
 *  author: Suhas Vittal
 *  date:   29 May 2023
 * */

#include "vtils/cmd_parse.h"

#include <regex>

namespace vtils {

const std::regex no_arg_opt("-([1-9A-Za-z_-]+)");
const std::regex w_arg_opt("--([1-9A-Za-z_-]+)");

CmdParser::CmdParser(int argc, char* argv[], int from)
    :option_pool(),
    option_to_arg()
{
    argv = argv + from;
    argc -= from;

    int ptr = 1;
    while (ptr < argc) {
        std::string s(argv[ptr]);
        std::smatch m;
        if (std::regex_match(s, m, w_arg_opt)) {
            option_pool.insert(m[1]);
            option_to_arg[m[1]] = argv[++ptr];
        } else if (std::regex_match(s, m, no_arg_opt)) {
            option_pool.insert(m[1]);
        }
        ptr++;
    }
}

}   // vtils
