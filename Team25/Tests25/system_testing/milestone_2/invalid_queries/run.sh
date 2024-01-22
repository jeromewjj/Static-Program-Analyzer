#!/bin/bash

cd $(dirname $0)
../../../../Code25/cmake-build-release/src/autotester/autotester invalid_semantic_queries_source.txt invalid_semantic_queries.txt invalid_semantic_queries_out.xml
../../../../Code25/cmake-build-release/src/autotester/autotester invalid_syntax_queries_source.txt invalid_syntax_queries.txt invalid_syntax_queries_out.xml