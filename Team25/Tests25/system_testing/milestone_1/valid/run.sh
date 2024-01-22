#!/bin/bash

cd $(dirname $0)
../../../../Code25/cmake-build-release/src/autotester/autotester basic_source.txt basic_query.txt basic_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester deep_nesting_source.txt deep_nesting_query.txt deep_nesting_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester odd_source.txt odd_query.txt odd_out.xml