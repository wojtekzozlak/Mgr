set -e


sudo service postgresql stop &> /dev/null
sudo sync
echo 3 | sudo tee /proc/sys/vm/drop_caches &> /dev/null
sudo service postgresql start &> /dev/null

ts=$(date +%s%N)
echo "set enable_seqscan=false; " $1 | psql tpch > /dev/null
tt=$((($(date +%s%N) - $ts)/1000000)) ; echo -n "$tt"
