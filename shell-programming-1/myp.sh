#!/bin/bash

# Functionality 1: Append file sizes to file names
function functionality1 {
    source_folder=$2
    for file in "$source_folder"/*; do
        if [ -f "$file" ]; then
            size=$(wc -c < "$file")
            new_name="${file%.*}${size}.${file##*.}"
            mv "$file" "$new_name"
            echo "Renamed $file to $new_name"
        fi
    done
}

# Functionality 2: Copy files with uncommon names to destination folder
function functionality2 {
    source_folder1=$2
    source_folder2=$3
    destination_folder=$4
    
    # Create destination folder if it doesn't exist
    mkdir -p "$destination_folder"
    
    # Loop through files in source_folder1
    for file1 in "$source_folder1"/*; do
        if [ -f "$file1" ]; then
            filename=$(basename "$file1")
            
            # Check if the same file exists in source_folder2
            found=false
            for file2 in "$source_folder2"/*; do
                if [ -f "$file2" ]; then
                    if [ "$(basename "$file2")" == "$filename" ]; then
                        found=true
                        break
                    fi
                fi
            done

            # If file is not found in source_folder2, copy it to destination_folder
            if [ "$found" == false ]; then
                cp "$file1" "$destination_folder/"
                echo "Copied $file1 to $destination_folder/"
            fi
        fi
    done

    for file2 in "$source_folder2"/*; do
        if [ -f "$file2" ]; then
            filename=$(basename "$file2")

            # Check if the same file exists in source_folder1
            found=false
            for file1 in "$source_folder1"/*; do
                if [ -f "$file1" ]; then
                    if [ "$(basename "$file1")" == "$filename" ]; then
                        found=true
                        break
                    fi
                fi
            done

            # If file is not found in source_folder1, copy it to destination_folder
            if [ "$found" == false ]; then
                cp "$file2" "$destination_folder/"
                echo "Copied $file2 to $destination_folder/"
            fi
        fi
    done
}

# Main script
case "$1" in
    -1)
        functionality1 "$@"
        ;;
    -2)
        functionality2 "$@"
        ;;
    *)
        echo "Invalid option. Usage: myp -1 sourcefolder or myp -2 sourcefolder1 sourcefolder2 destinationfolder"
        ;;
esac

