#!/usr/bin/env bash

files=$(find . -name "*.cpp" -or -name "*.hpp" | grep -v "./tools/*")
filter=-build/c++11,-readability/casting,-runtime/references,-whitespace/braces,-whitespace/indent,-whitespace/comments,-build/include_order,-build/header_guard,-build/include_subdir
echo $files | xargs cpplint --filter=$filter

