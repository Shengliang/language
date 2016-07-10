#!/bin/bash
read N
if [ $N -eq 0 ];then echo "0.000"; exit 0; fi
S=0
while read l
do 
  S=$(( $S + $l ))
done
x=$((10000*$S/$N - 10*(1000*$S/$N) ))
c=0
if [ "$x" -ge "5" ]; then 
c=1
fi
printf "%d.%03d\n" $(($S/$N)) $((1000*$S/$N - 1000*($S/$N) + $c ))
python -c "print '%.3f' % (1.0*$S/$N)"
python -c "print '%.3f' % 0.07450"
python -c "print '%.3f' % 0.07550"
python -c "print '%.3f' % 0.07451"
python -c "print '%.3f' % 0.07551"
python -c "print '%.7f' % (1.0/7) "
python -c "print '%.6f' % (1.0/7) "
python -c "print '%.5f' % (1.0/7) "
python -c "print '%.4f' % (1.0/7) "
python -c "print '%.3f' % (1.0/7) "
python -c "print '%.2f' % (1.0/7) "
python -c "print '%.3f' % 0.0745555555"
