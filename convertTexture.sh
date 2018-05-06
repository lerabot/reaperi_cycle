#!/bin/sh

FOLDER=$1
FILES=$FOLDER/*.png

rm -rf $FOLDER/preview/
mkdir $FOLDER/preview/

for f in $FILES
do
  name=$(basename "$f" .png)
  ../texconv --in $f --out $FOLDER/dtex/$name.png -f ARGB1555 -p $FOLDER/preview/$name.png
  echo "$name converted to .dtex"
done