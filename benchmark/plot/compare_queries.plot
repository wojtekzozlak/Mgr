
set style data histogram
set style histogram cluster gap 1

set style fill solid border rgb "black"
set auto x
set xtics rotate by 30 center offset -1,-1
set yrange [0:*]
set xlabel "Numer zapytania (liczba atrybutów)" font"Verdana Bold, 14" offset 0,-1
set ylabel "Czas wykonania (s)" font"Verdana Bold, 14" rotate by 90

set term svg enhanced size 1024, 500
#set output 'read_queries_ssd.svg'
#splot "read_queries_ssd.dat" notitle with lines

#set key outside top
set key box opaque
set output 'compare_queries.svg'
plot 'compare_queries.dat' using 2:xtic(2) title col lc rgb "#0b5394", \
  '' using 3:xtic(1) title col lc rgb "#f1c232", \
  '' using 4:xtic(1) title col lc rgb "#a61c00", \
  '' using 5:xtic(1) title col lc rgb "#6fa8dc", \
  '' using 6:xtic(1) title col lc rgb "#ffe599", \
  '' using 7:xtic(1) title col lc rgb "#dd7e6b"


