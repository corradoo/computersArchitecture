cd /proc
echo -e PID: '\t' PPID: '\t' Opened Desc.:
for p in [0-9]*
do
    proc=$(cat /proc/$p/status)
    ppid=$(echo "${proc##*PPid:}" | head -n1 | awk '{print $1}')
    files=$(lsof -p $p | wc -l)
    let files--
    echo -e $p'\t |'$ppid'\t |'$files 
done;



