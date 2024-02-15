#!/bin/bash

folder_path="$1"  # Replace with the actual path to your folder

cd "$folder_path" || exit 1  # Change to the folder directory, exit if unsuccessful

count=1

for file in *.txt; do
    new_name="$1put$count.txt"
    mv "$file" "$new_name"
    ((count++))
done

echo "Files renamed successfully."
