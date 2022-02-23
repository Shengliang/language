DIR=$(dirname $0)
FOUT=${1:-"${DIR}/git_version.cc"}
echo 'const char * mysql_git_version =  ' > $FOUT
git log  --pretty="\"GIT.HASH:%H\"" | head -n 1  >> $FOUT
echo ";" >> $FOUT

echo 'const char * mysql_compile_time = ' >> $FOUT
date +"\"COMPILE.TIME[%F %T]\"" >> $FOUT
echo ";" >> $FOUT
echo $FOUT is created.
