cd; cd $1
for f in *
do if [ -f "$f" ]; then
        mv -- "$f" "`echo "$f" | tr 'A-Z' 'a-z' `"
    fi
done
