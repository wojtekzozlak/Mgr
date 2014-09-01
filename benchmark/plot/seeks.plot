set xlabel "Rozmiar rodziny" font"Verdana Bold, 14"
set ylabel "Liczba operacji seek" font"Verdana Bold, 14" offset -2,0 rotate by 90
#set palette rgb 21,3,0
set term svg enhanced size 800, 480
set style fill solid
set boxwidth 0.5

set output 'seeks.svg'
plot "seeks.dat" using 1:3:xtic(2) notitle with boxes
