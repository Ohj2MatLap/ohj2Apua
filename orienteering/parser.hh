/*  TIE-02201 Ohjelmointi 2, K2019 / TIE-02207 Programming 2, S2019
 *  Project 3: Orienteering
 *  File: parser.hh
 *  Description: Module that handles parsing of the input file
 *      into a Routes object.
 *  Notes:
 *      * Students' shouldn't make changes to this module.
 * */
#ifndef PARSER_HH
#define PARSER_HH
#include <memory>
#include "routes.hh"

bool read_input_from_file(std::string file, std::shared_ptr<Routes> routes);

#endif // PARSER_HH
