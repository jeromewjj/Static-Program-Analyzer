#!/bin/bash

cd $(dirname $0)
../../../../Code25/cmake-build-release/src/autotester/autotester  affects_store_basic_tests_source.txt affects_store_basic_tests_queries.txt affects_store_basic_tests_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester  next_star_store_basic_source.txt next_star_store_basic_queries.txt next_star_store_basic_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester  next_store_basic_tests_source.txt next_store_basic_tests_queries.txt next_store_basic_tests_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester  not_clause_basic_tests_source.txt not_clause_basic_tests_queries.txt not_clause_basic_tests_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester  with_clause_basic_tests_source.txt with_clause_basic_tests_queries.txt with_clause_basic_tests_out.xml