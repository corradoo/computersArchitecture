prevnet=0;
jumps=0;
col=0;
x=0;
rm chart 2>/dev/null;
while sleep 1 
do 
    tput clear;
    czas=$(cat /proc/uptime | head -n1 | awk '{print $1}'); #pobiera czas
    seconds=${czas%.*}; #obcina ułamek
    
    sec=$((seconds%60));
    if (( sec < 10 )); then sec=0$sec; fi;

    minutes=$((seconds/60%60));
    if (( minutes < 10 )); then minutes=0$minutes; fi;
    
    hours=$((seconds/3600%24));
    if ((hours < 10 )); then hours=0$hours; fi;

    days=$((seconds/3600/24));
   
    net=$(cat /proc/net/dev);
    net=$(echo "${net##*ens33: }" | head -n1 | awk '{print $1}');

    current=$((net-prevnet));
    avgNet=$((net/$seconds));
    #Ustawia odpowiednią jednostkę dla obecnej prędkości
    if ((current<1024)); then current="$current B/s";
    else if ((current<1024*1024)); then current="$((current/1024)) KB/s";
    else current="$((current/1024/1024)) MB/s" ;
    fi; fi;

    #Ustawia odpowiednią jednostkę dla prędkości średniej
    if ((avgNet<1024)); then avgNet="$avgNet B/s";
    else if ((avgNet<1024*1024)); then avgNet="$((avgNet/1024)) KB/s";
    else avgNet="$((avgNet/1024/1024)) MB/s" ;
    fi; fi;

    cpu=$(cat /proc/loadavg | head -n1 | awk '{print $1}');
    
    tput bold
    tput cup 0 0
    echo "PC uptime: "$days days $hours:$minutes:$sec ;
    tput cup 2 0
    echo AVG: $avgNet  CURRENT: $current;
    tput cup 3 0
    echo CPU: $cpu
    echo $x $cpu >> chart
    printf "\033[0m"
    let x++;
    cat chart | gnuplot -p -e "set terminal dumb size 120, 30; set autoscale; plot '-' using 1:2 with lines notitle";

    prevnet=$net;
done
