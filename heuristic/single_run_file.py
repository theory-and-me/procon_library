# ファイル出力を採点するタイプの問題の，単一テストケースのスコア計算スクリプト

import sys
import os
import subprocess

program_name = sys.argv[1]
test_name = sys.argv[2]
print(program_name)

subprocess.run("g++ -O3 -std=c++17  -I $HOME/Work/procon/lib/ac-library ../src/{0}.cpp -o ../src/{0}".format(program_name), shell=True, check=True)
filename = "../score/{}.txt".format(program_name)

subprocess.run("rm {}".format(filename), shell=True, check=False)
subprocess.run("mkdir ../output/{}".format(program_name), shell=True, check=False)

subprocess.run("../src/{0} < in/{1}.txt > ../output/{0}/{1}.txt ".format(program_name, test_name), shell=True, check=False)
res = subprocess.run("cargo run --release --bin vis in/{0}.txt ../output/{1}/{0}.txt".format(test_name, program_name), shell=True, check=False, capture_output=True)
# print(res)
score = int(res.stdout.decode().split('\n')[0].split(' ')[2])
print(score)