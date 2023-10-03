from os import system as exe
from random import randint as rnd


tests_cnt = 24
exe("g++ fast_solve.cpp -o trash/fast -std=c++11")
exe("g++ slow_solve.cpp -o trash/slow -std=c++11")

for i in range(1, tests_cnt + 1):
    now_test = str("tests/test_" + str(i) + ".txt")
    execution_task_1 = str("./trash/fast < " + now_test + " > trash/out1.txt")
    execution_task_2 = str("./trash/slow < " + now_test + " > trash/out2.txt")
    exe(execution_task_1)
    exe(execution_task_2)
    a1 = open("trash/out1.txt", "r").readline().rstrip()
    a2 = open("trash/out2.txt", "r").readline().rstrip()
    if a1 != a2:
        print("WA on test ", i)
        exit(0)

auto_tests = 10 ** 5
for i in range(auto_tests):
    now_test = str("trash/test.txt")
    output = open(now_test, "w")
    
    n_divided_by_50 = rnd(100, 10 ** 3)
    n = 50 * n_divided_by_50

    print(n, file=output)
    output.close()

    execution_task_1 = str("./trash/fast < " + now_test + " > trash/out1.txt")
    execution_task_2 = str("./trash/slow < " + now_test + " > trash/out2.txt")
    exe(execution_task_1)
    exe(execution_task_2)
    a1 = open("trash/out1.txt", "r").readline().rstrip()
    a2 = open("trash/out2.txt", "r").readline().rstrip()
    if a1 != a2:
        print("WA on test ", i)
        exit(0)

print("OK")
