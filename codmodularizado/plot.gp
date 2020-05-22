set term pdf
set out 'P.pdf'
set ylabel 'P(p,L)'
set xlabel 'probabilidad'

plot for [i=1:5] 'data-'.i.'.txt' using 1:2 w lp ps 0.5 title 'data'.i