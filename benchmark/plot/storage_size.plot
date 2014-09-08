set style fill solid border rgb "black"
set auto x
set xlabel "Typ składu" font"Verdana Bold, 16" offset 0,-0.5
set ylabel "Rozmiar (MB)" font"Verdana Bold, 16" rotate by 90

set term svg enhanced size 800, 500
set nokey
set xtics font"Verdana, 15"

set boxwidth 0.5
set output 'storage_size.svg'
plot 'storage_size.dat' using 2:xtic(1) with boxes
