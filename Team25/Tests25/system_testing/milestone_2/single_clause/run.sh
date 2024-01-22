#!/bin/bash

cd $(dirname $0)
../../../../Code25/cmake-build-release/src/autotester/autotester calls_clause_basic_tests_source.txt calls_clause_basic_tests_queries.txt calls_clause_basic_tests_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester calls_star_basic_tests_source.txt calls_star_basic_tests_queries.txt calls_star_basic_tests_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester if_and_while_pattern_tests_source.txt if_and_while_pattern_tests_queries.txt if_and_while_pattern_tests_out.xml