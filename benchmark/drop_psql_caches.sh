set -e
sudo service postgresql stop
sudo sync
echo 3 | sudo tee /proc/sys/vm/drop_caches
sudo service postgresql start
