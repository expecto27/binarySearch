#!/bin/bash

function clang_format() {
    echo "verifying 'clang-format --output-replacements-xml --style=file:clang-format.style $@'"
    if clang-format --output-replacements-xml --style=file:clang-format.style "$@" | grep -q '<replacement '; then
        echo "ERROR:" "$@" "not in C/C++ style defined in clang-format.style"
        echo "To fix formatting run"
        echo "$ clang-format -i --style=file:clang-format.style" "$@"
        return 255
    fi
}

tmpfile="tmpfile.$RANDOM"
find src -iname "*.cpp" -o -iname "*.hpp" > "$tmpfile"
ec=0
while read -r file; do
    if ! clang_format "$file"; then
        ec=255
    fi
done < "$tmpfile"
rm -f "$tmpfile"

exit "$ec"
