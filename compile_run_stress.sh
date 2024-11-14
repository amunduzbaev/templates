# compile and run name.cpp with input in
# if input empty, print empty in
code=$1
in=$2
set -e
g++ $code.cpp -o run

if [ ! -z "$(cat in)" ]; then 
  ./run < $in > out
  echo "output:"
  cat out
  echo -e
else 
  echo "empyt input file"
fi

#stres test
#need files: 
#           wrong.cpp (solution you want to stres, prints wrong answer)
#           corr.cpp (correct solution, to get the correct answer)
#           gen.cpp (input test generator)
#           no checker for now

set -e
g++ wrong.cpp -o wrong
g++ gen.cpp -o gen
g++ slow.cpp -o slow
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./wrong < input_file > wrongAnswer
    ./corr < input_file > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer
