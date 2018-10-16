#! /bin/sh

FILE=$1
FILE_FLIP="$1_flip.png"

convert $FILE -flip $FILE_FLIP

$KOS_BASE/utils/texconv/texconv --in $FILE_FLIP --format ARGB1555 --preview sprite_prev.png --out spritesheet.dtex

#rm $FILE_FLIP
