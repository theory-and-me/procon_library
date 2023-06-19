# ファイル出力を採点するタイプの問題の，全テストケースのスコア計算スクリプト

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
    test_id = test.split(".")[0]
    subprocess.run("../src/{0} < in/{1} > ../output/{0}/{2}.txt ".format(program_name, test, test_id), shell=True, check=False)
    res = subprocess.run("cargo run --release --bin vis in/{0} ../output/{1}/{2}.txt".format(test, program_name, test_id), shell=True, check=False, capture_output=True)
    # print(res)
    score = int(res.stdout.decode().split('\n')[0].split(' ')[2])
    print(test_id, score)
    total_score += score
print(total_score)