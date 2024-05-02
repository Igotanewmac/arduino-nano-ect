



set terminal png size 5120,2048 enhanced font "Helvetica,20"
set output ARG2



plot \
    ARG1 using 1:4 with lines lw 1 title 'VCC', \
    '' using 1:8 with lines lw 1 title 'OUT', \
    '' using 1:12 with lines lw 1 title 'INA', \
    '' using 1:16 with lines lw 1 title 'INB'




















