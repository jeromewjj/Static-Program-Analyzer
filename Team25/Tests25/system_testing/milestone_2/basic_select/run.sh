#!/bin/bash

cd $(dirname $0)
../../../../Code25/cmake-build-release/src/autotester/autotester select_BOOLEAN_basic_tests_source.txt select_BOOLEAN_basic_tests_queries.txt select_BOOLEAN_basic_tests_out.xml