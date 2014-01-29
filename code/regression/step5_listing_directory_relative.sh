NACHOS_DIR=../build/

cd $NACHOS_DIR

#format disk
./nachos-step5 -f

#create file structure
./nachos-step5 -cp ../Makefile a
./nachos-step5 -md dir1
./nachos-step5 -md dir1/dir2
./nachos-step5 -cp ../Makefile dir1/test
./nachos-step5 -md dir3
./nachos-step5 -md dir3/dir4
./nachos-step5 -md dir3/dir4/dir5

# Test case
./nachos-step5 -l /dir3/../dir2/../dir3/dir4/./
OUTPUT=$(./nachos-step5 -l /dir3/../dir2/../dir3/dir4/./ | head -n -10 | tr "\n" "|")
EXPECTED_OUTPUT="d - dir5|"

if [ "$OUTPUT" = "$EXPECTED_OUTPUT" ]; then
    RETURN=0
else
    echo "$OUTPUT"
    RETURN=-1
fi

#Clean up test
./nachos-step5 -f

#return test result
exit $RETURN