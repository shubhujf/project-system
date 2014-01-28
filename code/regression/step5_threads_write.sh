NACHOS_DIR=../build/

cd $NACHOS_DIR

#format disk
./nachos-step5 -f

rm /tmp/test
touch /tmp/test
./nachos-step5 -cp /tmp/test test
./nachos-step5 -cp step5_threads_write run

./nachos-step5 -x run -rs 1
OUTPUT=$(./nachos-step5 -p test | head -1 | sed 's/Machine halting!//' | sed -e "s/.\{300\}/&\n/g" | sort | tr -d "\n")

for i in {1..300}; do
    echo -n "a" >> /tmp/test
done
for i in {1..300}; do
    echo -n "b" >> /tmp/test
done
for i in {1..300}; do
    echo -n "c" >> /tmp/test
done
for i in {1..300}; do
    echo -n "d" >> /tmp/test
done
for i in {1..300}; do
    echo -n "e" >> /tmp/test
done
for i in {1..300}; do
    echo -n "f" >> /tmp/test
done
for i in {1..300}; do
    echo -n "g" >> /tmp/test
done
for i in {1..300}; do
    echo -n "h" >> /tmp/test
done
for i in {1..300}; do
    echo -n "i" >> /tmp/test
done
EXPECTED_OUTPUT=$(cat /tmp/test)

#Clean up test
./nachos-step5 -f
if [ "$OUTPUT" = "$EXPECTED_OUTPUT" ]; then
    exit 0
else
    exit -1
fi
