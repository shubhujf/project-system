NACHOS_DIR=../build/

cd $NACHOS_DIR
./nachos-final -cp test_exit_1 run
OUTPUT=$(./nachos-final -x run -d m| grep "Exit program, return code exit(1)")

if [ -n "$OUTPUT" ]; then
    exit 0
else
    exit -1
fi

