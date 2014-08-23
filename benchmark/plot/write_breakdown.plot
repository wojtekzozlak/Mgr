set style data histograms
set style histogram rowstacked
set boxwidth 1 relative
set style fill solid 1.0 border -1
set ytics 0.1
set yrange [0:1]
set xtics rotate 90
set palette rgb 21,3,0
set term svg enhanced size 1024, 600
set output 'write_breakdown.svg'
plot 'write_breakdown.dat' using 2 t "Bbb" lt rgb "#f6b26b", '' using 3:xticlabels(1) t "Aaa"lt rgb "#b6d7a8"
