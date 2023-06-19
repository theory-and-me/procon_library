import sys
import os
import subprocess

program_name = sys.argv[1]
test_id = sys.argv[2]
print(program_name)
print(test_id)

subprocess.run("g++ -O3 -std=c++17 -I $HOME/Work/procon/lib/ac-library ../src/{0}.cpp -o ../src/{0}".format(program_name), shell=True, check=True)

res = subprocess.run("cargo run --release --bin tester ../src/{0} < in/{1}.txt > ../output/{0}/{1}.txt 2>err.txt".format(program_name, test_id), shell=True, check=False, capture_output=True)
# print(res)
score = int(res.stderr.decode().split('\n')[2].split(' ')[2])
print(score)