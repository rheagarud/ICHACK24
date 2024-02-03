make bin/ast_maker >> /dev/null

mkdir -p bin
mkdir -p bin/output

# cd ast_tests/

# for TEST in *.txt; do 
#     ASSEMBLE="${TEST%.txt}"
#     OUT_PATH="../bin/output/${ASSEMBLE}_output.json"
#     LOG_PATH="../bin/output/${ASSEMBLE}"
#     ../bin/ast_maker -S "${TEST}" -o "${OUT_PATH}" 2> "${LOG_PATH}.compiler.stderr.log" > "${LOG_PATH}.compiler.stdout.log"
# done


echo "$1" >> ./ast_tests/woohoo.txt
touch ./bin/output/woohoo.json
chmod a+x ./bin/output/woohoo.json
bin/ast_maker -S "./ast_tests/woohoo.txt" -o "./bin/output/woohoo.json" >> /dev/null
value=`cat "./bin/output/woohoo.json"`; 
echo $value; 
rm -f ./ast_tests/woohoo.txt; 
rm -f ./bin/output/woohoo.json