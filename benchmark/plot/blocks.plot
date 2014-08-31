set xlabel "Rozmiar kroku" font"Verdana Bold, 14"
set xrange [0:10000]
set xtics offset -0.5,0 
set ylabel "Rozmiar rodziny" font"Verdana Bold, 14"
set ytics offset 1.25,-0.25
set logscale y 2
set zlabel "Liczba stron" font"Verdana Bold, 14" offset -3,0 rotate by 90
#set dgrid3d
set pm3d
set palette rgb 21,3,0
set term svg enhanced size 1024, 600

set output 'blocks.svg'
splot "blocks.dat" notitle with lines
