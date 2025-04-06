#!/bin/bash

# File with user presets
USER_PRESETS="CMakeUserPresets.json"

# Verify that jq is installed
if ! command -v jq &> /dev/null; then
    echo "Error: jq is not installed. Install it using 'dnf install jq' (Fedora) or 'apt install jq' (Debian)."
    exit 1
fi

# Load the list of included preset files
PRESET_FILES=$(jq -r '.include[]' "$USER_PRESETS")

# Iterate through all preset files
for FILE in $PRESET_FILES; do
    if [[ -f "$FILE" ]]; then
        # Extract build presets
        PRESETS=$(jq -r '.buildPresets[].name' "$FILE")
        
        # Perform build for each preset
        for PRESET in $PRESETS; do
            echo "Building preset: $PRESET from $FILE"
            cmake --build --preset "$PRESET"
        done
    else
        echo "File $FILE does not exist, skipped."
    fi
done
