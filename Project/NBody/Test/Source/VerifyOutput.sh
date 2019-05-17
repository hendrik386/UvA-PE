#!/usr/bin/env bash

# Configuration
EXECUTABLE="$1"
RESOURCES_IMAGES="$2"

# Run the simulation
${EXECUTABLE}

# Check if the output is identical to the reference output
SUCCESS=true
if [[ $(diff -rq ${RESOURCES_IMAGES} ./images/) ]]; then
	SUCCESS=false
fi

# Remove temporary image files
rm -r ./images/

# Output result and exit with the correct status code
if [[ ${SUCCESS} = true ]]; then
	printf "The output is identical."

	exit
else
	printf "The output differs! Something is wrong."

	exit 1
fi