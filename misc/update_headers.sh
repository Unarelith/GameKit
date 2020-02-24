#!/bin/bash

if [ ! -f "misc/header_cpp.txt" ];
then
	echo "Failed to find header file. Aborting."
	exit
fi

for file in $(find include source examples -name "*.*pp");
do
	sed -i '1,26d' $file
	cat misc/header_cpp.txt $file > $file.new && mv $file.new $file
done

