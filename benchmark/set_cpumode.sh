MODE=$1

for CPUFREQ in /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor; do [ -f $CPUFREQ ] || continue; echo -n $MODE > $CPUFREQ; cat $CPUFREQ; done 


