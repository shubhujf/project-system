NACHOS_DIR=../build/

cd $NACHOS_DIR

RESULT_STRING="0{20}-2"

OUTPUT=$(./nachos-step4 -rs 2 -x thread_max_limit | grep -P "$RESULT_STRING")

if [ -n "$OUTPUT" ]; then
    exit 0
else
    exit -1
fi