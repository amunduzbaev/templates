# compile and run
# if input empty, print empty in
set -e
g++ a.cpp -o run

if [ ! -z "$(cat in)" ]; then 
  ./run < in > out
  echo "output:"
  cat out
  echo -e
else 
  echo "empyt in"
fi

#stres test
#need files: 
#           fast.cpp (solution you want to stres, prints wrong answer)
#           slow.cpp (correct solution, to get the correct answer)
#           gen.cpp (input test generator)
#           no checker for now

set -e
g++ fast.cpp -o fast
g++ gen.cpp -o gen
g++ slow.cpp -o slow
for((i = 1; ; ++i)); do
    ./gen $i > input_file
    ./fast < input_file > myAnswer
    ./slow < input_file > correctAnswer
    diff -Z myAnswer correctAnswer > /dev/null || break
    echo "Passed test: "  $i
done
echo "WA on the following test:"
cat input_file
echo "Your answer is:"
cat myAnswer
echo "Correct answer is:"
cat correctAnswer
