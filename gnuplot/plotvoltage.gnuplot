




set terminal png size 5120,2048 enhanced font "Helvetica,20"
set output ARG2


plot \
    ARG1 using 1:3 with lines lw 1 title 'VCC', \
    '' using 1:7 with lines lw 1 title 'OUT', \
    '' using 1:11 with lines lw 1 title 'INA', \
    '' using 1:15 with lines lw 1 title 'INB'




















