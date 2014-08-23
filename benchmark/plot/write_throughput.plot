set xlabel "Rozmiar kroku" font"Verdana Bold, 14"
set xrange [100:5000]
set xtics offset -0.5,0 
set ylabel "Rozmiar rodziny" font"Verdana Bold, 14"
set ytics offset 1.25,-0.25
set yrange [1:16]
set zlabel "MB/s" font"Verdana Bold, 14" offset -3,0
set dgrid3d
set pm3d
set palette rgb 21,3,0
set term svg enhanced size 1024, 600
set output 'write_throughput.svg'
set title "Przepustowość zapisu (MB/s)" font"Verdana Bold, 16"
splot "write_throughput.dat" notitle with lines
