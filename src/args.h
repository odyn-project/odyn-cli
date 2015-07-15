// Copyright 2015 Greg Prisament
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef ARGS_INCLUDED
#define ARGS_INCLUDED

#include <stdbool.h>
#include <stdint.h>

// Opaque datatype representing the parser and its results.
typedef struct arg_parser_struct * arg_parser_t;

// Create a new Argument Parser object.
arg_parser_t args_new_parser();

// Free resources used by Argument Parser object.
void args_free_parser(arg_parser_t parser);

// Parse commandline arguments and internally store results.
// Returns true on success, false on failure
bool args_parse(arg_parser_t parser, int argc, const char *argv[]);

// Count non-flag arguments.
// Returns 0 if args_parse() hasn't been called yet.
uint32_t args_num_args(arg_parser_t parser);

// Count command-line flags.
// Returns 0 if args_parse() hasn't been called yet.
uint32_t args_num_flags(arg_parser_t parser);

// Get non-flag argument by index.
// Returns NULL if index is out of bounds.
const char * args_arg(arg_parser_t parser, uint32_t idx);

// Lookup flag name and value by index.
// Sets *out_key and *out_value.
// Sets both to NULL if index is out of bounds or args_parser() hasn't been
// called yet.
void args_flag_by_index(
        arg_parser_t parser, 
        uint32_t idx, 
        const char **out_key, 
        const char **out_value);

// Lookup flag value by name.
// <longname> is optional long name that starts with --, such as "--verbose".
// <shortname> is optional short name that starts with -, such as "-v".
// If a flag is set multiple times, returns the last occurance.
// Returns <default_val> if flag is not found or if args_parser() hasn't been
// called yet.
const char * args_flag(
        arg_parser_t parser, 
        const char *longname, 
        const char *shortname, 
        const char *default_val);


#endif // ARGS_INCLUDED
