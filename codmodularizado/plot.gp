set term pdf
set out 'P.pdf'
set ylabel 'P(p,L)'
set xlabel 'probabilidad'

plot 'data-1.txt' using 1:2 w lp ps 0.5 title 'L = 32' ,\
     'data-2.txt' using 1:2 w lp ps 0.5 title 'L = 64' ,\
     'data-3.txt' using 1:2 w lp ps 0.5 title 'L = 128' ,\
     'data-4.txt' using 1:2 w lp ps 0.5 title 'L = 256' ,\
     'data-5.txt' using 1:2 w lp ps 0.5 title 'L = 512' ,\