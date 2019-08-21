#!/bin/sh -e
# Script used to generate the sources.mk files and then build the project.


# iterate over every lib
for libDir in *; do
    for d in `find libfftw-* -type d`; do
        # Find all .c files, extract filename, sort them and replace new line with space
        sources=$(find "$d" -maxdepth 1 -type f -name '*.c' | rev | cut -f1 -d'/' | rev | sort | tr '\n' ' ')
        if [ -n "$sources" ]; then # No sources found in directory
            echo "\nDirectory: $d"
            echo "Sources: $sources"
            echo "# autoregenerated sources makefile. DO NOT EDIT, EDITS WILL BE OVERWRITTEN" > $d/sources.mk
            echo "sources := $sources" >> $d/sources.mk
            echo "LOCAL_SRC_FILES += \$(addprefix $(echo $d | cut -f1- -d'/')/, \$(sources))" >> $d/sources.mk
        fi;
    done
done