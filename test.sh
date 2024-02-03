make bin/ast_maker

mkdir -p bin
mkdir -p bin/output

cd ast_tests/

for TEST in *.txt; do 
    ASSEMBLE="${TEST%.txt}"
    OUT_PATH="../bin/output/${ASSEMBLE}_output.json"
    LOG_PATH="../bin/output/${ASSEMBLE}"
    ../bin/ast_maker -S "${TEST}" -o "${OUT_PATH}" 2> "${LOG_PATH}.compiler.stderr.log" > "${LOG_PATH}.compiler.stdout.log"
done

cd ..

echo "DONE"