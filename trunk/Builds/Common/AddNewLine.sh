echo $1
cat $1 | sed '$a\\n' > $1
