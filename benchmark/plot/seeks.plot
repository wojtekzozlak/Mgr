set xlabel "Rozmiar kroku" font"Verdana Bold, 14"
set xrange [0:10000]
set xtics offset -0.5,0 
set ylabel "Rozmiar rodziny" font"Verdana Bold, 14"
set ytics offset 1.25,-0.25
set logscale y 2
set zlabel "liczba operacji seek" font"Verdana Bold, 14" offset -3,0 rotate by -90
set pm3d
set palette rgb 21,3,0
set term svg enhanced size 1024, 600

set output 'seeks.svg'
splot "seeks.dat" notitle with lines
