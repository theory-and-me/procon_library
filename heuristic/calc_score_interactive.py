import sys
import os
import subprocess

program_name = sys.argv[1]
print(program_name)

subprocess.run("g++ -O3 -std=c++17 -I $HOME/Work/procon/lib/ac-library ../src/{0}.cpp -o ../src/{0}".format(program_name), shell=True, check=True)
filename = "../score/{}.txt".format(program_name)

subprocess.run("rm {}".format(filename), shell=True, check=False)
subprocess.run("mkdir ../output/{}".format(program_name), shell=True, check=False)

in_list = os.listdir("in/")
in_list.sort()
total_score = 0
for test in in_list:
    # print(test)
    test_id = test.split(".")[0]
    # print("cargo run --release --bin tester ../src/{1} < in/{0} > ../output/{1}/{2}.txt".format(test, program_name, test_id))
    res = subprocess.run("cargo run --release --bin tester ../src/{1} < in/{0} > ../output/{1}/{2}.txt".format(test, program_name, test_id), shell=True, check=False, capture_output=True)
    # print(res)
    score = int(res.stderr.decode().split('\n')[2].split(' ')[2])
    print(test_id, score)
    total_score += score
print(total_score)