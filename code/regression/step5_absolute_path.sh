NACHOS_DIR=../build/

cd $NACHOS_DIR

#format disk
./nachos-step5 -f

#create file structure
echo -n "1" > /tmp/test1
echo -n "2" > /tmp/test2
./nachos-step5 -cp /tmp/test1 test
./nachos-step5 -md a
./nachos-step5 -cp /tmp/test2 a/test
./nachos-step5 -cp step5_absolute_path run

# Test case
OUTPUT=$(./nachos-step5 -x run | grep "1212")

#Clean up test
./nachos-step5 -f

if [ -n "$OUTPUT" ]; then
    exit 0
else
    exit -1
fi