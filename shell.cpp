#include "shell.hpp"

extern ast::np<ast::Program> program;
cplus::shell shell;

namespace cplus {

shell::shell() : l(*this), p(l, *this) {}

int shell::parse_program() {
    return p.parse();
}

void shell::readFrom(std::istream *is) {
    l.switch_streams(is, nullptr);
}

void shell::show_help() {
    std::cout << "usage: cplus [options] infile\n";
    std::cout << "\tinfile\t\t\tpath to the source code file (*.cp) to compile.\n\n";
    std::cout << "options:\n";
    std::cout << "\t-h, --help\t\tshow this help message and exit.\n";
    std::cout << "\t-d, --debug\t\tshow debug messages.\n";
    std::cout << "\t-o, --outfile outfile\texecutable file name.\n";
    std::exit(1);
}

int shell::parse_args(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--help" || arg == "-h") {
            show_help();
        }
        else if (arg == "-d" || arg == "--debug") {
            debug = true;
        }
        else if (arg == "-o" || arg == "--outfile") {
            outfile = argv[++i];
            continue;
        }
        else {
            infile.open(arg);
            if (!infile.good())
            {
                std::cout << "Error: no such file: " << arg << '\n';
                return 1;
            }
            readFrom(&infile);
        }
    }
    if (!infile.is_open()) {
        show_help();
    }
    return 0;
}

} // namespace cplus
