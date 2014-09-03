
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

set key box opaque
set output 'read_queries_hdd.svg'
plot 'read_queries_hdd.dat' using 2:xtic(2) title col lc rgb "#FAA43A", \
  '' using 3:xtic(1) title col lc rgb "#60BD68", \
  '' using 4:xtic(1) title col lc rgb "#5DA5DA", \
  '' using 5:xtic(1) title col lc rgb "#F15854", \
  '' using 6:xtic(1) title col lc rgb "#B2912F"

set output 'read_queries_ssd.svg'
plot 'read_queries_ssd.dat' using 2:xtic(2) title col lc rgb "#FAA43A", \
  '' using 3:xtic(1) title col lc rgb "#60BD68", \
  '' using 4:xtic(1) title col lc rgb "#5DA5DA", \
  '' using 5:xtic(1) title col lc rgb "#F15854", \
  '' using 6:xtic(1) title col lc rgb "#B2912F"


