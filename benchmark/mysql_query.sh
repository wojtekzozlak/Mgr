sudo sync
echo 3 | sudo tee /proc/sys/vm/drop_caches &> /dev/null
echo "RESET QUERY CACHE" | mysql -uroot -pbumbum510 tpch > /dev/null

ts=$(date +%s%N)
echo $1 | mysql -uroot -pbumbum510 tpch > /dev/null
tt=$((($(date +%s%N) - $ts)/1000000)) ; echo -n "$tt"
