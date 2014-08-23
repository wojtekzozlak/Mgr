#!/bin/bash
for i in `find images -name "*.svg" | rev | cut -c 5- | rev`;
do
  inkscape -z -D --file=$i.svg --export-pdf=$i.pdf
done

for i in `find images -name "*.png" | rev | cut -c 5- | rev`;
do
  convert $i.png $i.pdf
done
