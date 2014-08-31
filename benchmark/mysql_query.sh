ts=$(date +%s%N)

sync && echo 3 > /proc/sys/vm/drop_caches
echo "RESET QUERY CACHE" | mysql -uroot -pbumbum510 tpch > /dev/null
echo $1 | mysql -uroot -pbumbum510 tpch > /dev/null

tt=$((($(date +%s%N) - $ts)/1000000)) ; echo "$tt"
