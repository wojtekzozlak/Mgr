CC = clang++
#CC_FLAGS = --std=c++11  -I/home/yellow/local_mgr_old/include -I/home/yellow/Studia/wojtekzozlak-supersonic3 -L/home/yellow/local_mgr_old/lib -lglog -lsupersonic -lprotobuf -lboost_timer -lgflags -o2

CC_FLAGS = --std=c++11  -I/home/yellow/local_mgr/include -I/home/yellow/Studia/wojtekzozlak-supersonic -L/home/yellow/local_mgr/lib -lglog -lsupersonic -lprotobuf -lboost_timer -lgflags -o2 -lboost_system

#%2:
#	export LD_PATH=/home/yellow/local_mgr/lib
#	export LD_LIBRARY_PATH=/home/yellow/local_mgr/lib
#	$(CC) $@.cc $(CC_FLAGS2) -o $@
%:
	export LD_PATH=/home/yellow/local_mgr_old/lib
	export LD_LIBRARY_PATH=/home/yellow/local_mgr_old/lib
	$(CC) $@.cc $(CC_FLAGS) -o $@
