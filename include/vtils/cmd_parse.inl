/*
 *  author: Suhas Vittal
 *  date:   29 December 2023
 * */

namespace vtils {

inline bool
CmdParser::option_set(std::string opt, bool e) const {
    if (e && !option_pool.count(opt)) {
        std::cerr << help << std::endl;
        exit(1);
    }
    return option_pool.count(opt); 
}

inline bool
CmdParser::get(std::string opt, std::string& out, bool e) const {
    if (!option_set(opt, e)) return false;
    out = option_to_arg.at(opt); 
    return true;
}

template <class T> inline bool
CmdParser::get(std::string opt, T& out, bool e) const {
    std::string tmp;
    if (!get(opt, tmp, e)) return false;
    out = conv<T>(tmp);
    return true;
}

inline void
CmdParser::print_all_set_options(std::ostream& out) const {
    for (std::string opt : option_pool) {
        out << opt;
        if (option_to_arg.count(opt)) {
            out << ": " << option_to_arg.at(opt);
        }
        out << "\n";
    }
}

}   // vtils
