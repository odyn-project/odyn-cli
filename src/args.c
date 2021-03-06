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

#include "args.h"

#include <stdlib.h>
#include <string.h>

#define MAX_ARG_SIZE 1024

typedef struct { 
    char *key;
    char *value;
} arg_parser_flag_t;

typedef struct arg_parser_struct {
    // Dynamic array of flags
    arg_parser_flag_t * flags;
    uint32_t num_flags;

    // Dynamic array of arguments
    char **args;
    uint32_t num_args;
} arg_parser_struct;

arg_parser_t args_new_parser() {
    return calloc(1, sizeof(arg_parser_struct));
}

void args_free_parser(arg_parser_t parser) {
    free(parser);
}

bool args_parse(arg_parser_t parser, int argc, const char *argv[]) {
    int i;
    for (i = 0; i < argc; i++) {
        // Does it start with - or --
        if (argv[i][0] == '-') {
            // Add to flags array
            parser->num_flags++;
            parser->flags = realloc(
                    parser->flags, 
                    parser->num_flags*sizeof(arg_parser_flag_t));
            if (!parser->flags) {
                return false;
            }
            parser->flags[parser->num_flags - 1].key = "foobar";
            // TODO: Grab next argument if = sign is present
        } else {
            // Add to args array
            parser->num_args++;
            parser->args = realloc(
                    parser->args, 
                    parser->num_args*sizeof(char *));
            if (!parser->flags) {
                return false;
            }
            parser->args[parser->num_args - 1] = strndup(argv[i], MAX_ARG_SIZE);
            if (!parser->args[parser->num_args - 1]) {
                return false;
            }
        }
    }

    return true;
}


uint32_t args_num_args(arg_parser_t parser) {
    return parser->num_args;
}

uint32_t args_num_flags(arg_parser_t parser) {
    return parser->num_flags;
}

const char * args_arg(arg_parser_t parser, uint32_t idx) {
    if (idx >= parser->num_args) {
        return NULL;
    }
    return parser->args[idx];
}

void args_flag_by_index(
        arg_parser_t parser, 
        uint32_t idx, 
        const char **out_key, 
        const char **out_value) {

    if (idx >= parser->num_flags) {
        *out_key = NULL;
        *out_value = NULL;
        return;
    }

    *out_key = parser->flags[idx].key;
    *out_value = parser->flags[idx].value;
    return;
}

const char * args_flag(
        arg_parser_t parser, 
        const char *longname, 
        const char *shortname, 
        const char *default_val) {

    uint32_t i;

    // Run backwards through list to hit last occurance first.
    for (i = parser->num_flags - 1; i >= 0; i--) {
        if (!strcmp(parser->flags[i].key, shortname) ||
            !strcmp(parser->flags[i].key, longname)) {

            return parser->flags[i].value;
        }
    }

    return default_val;
}
