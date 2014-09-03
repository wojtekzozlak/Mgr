set xlabel "Rozmiar rodziny" font"Verdana Bold, 14"
set ylabel "Część odczytywanych wierszy" font"Verdana Bold, 14" offset 0,-2
set ytics offset 1.25,-0.25
set logscale x 2
set zlabel "Czas odczytu (s)" font"Verdana Bold, 14" offset -1,0 rotate by 90
set pm3d
set palette rgb 21,3,0
set term svg enhanced size 1024, 600

set output 'read_offset_ssd.svg'
splot "read_offset_ssd.dat" notitle with lines

set output 'read_offset_hdd.svg'
splot "read_offset_hdd.dat" notitle with lines
