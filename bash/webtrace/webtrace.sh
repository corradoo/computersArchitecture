git init
lynx -dump $1 > site
git add site
git commit site -m "First"
changes = 0
while sleep $2
do
    lynx -dump $1 > new
    DIFF=$(diff new site)
    if [ "$DIFF" != "" ] ; then
        echo "Site has been modified!"
	changes=$((changes + 1))
        diff new site
        cat new > site
        git add site
        git commit -m "$changes"
        else echo "Site has not been changed"
    fi

done

