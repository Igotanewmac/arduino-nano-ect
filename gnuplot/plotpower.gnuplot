



set terminal png size 5120,2048 enhanced font "Helvetica,20"
set output ARG2




plot \
    ARG1 using 1:5 with lines lw 1 title 'VCC', \
    '' using 1:9 with lines lw 1 title 'OUT', \
    '' using 1:13 with lines lw 1 title 'INA', \
    '' using 1:17 with lines lw 1 title 'INB'




















