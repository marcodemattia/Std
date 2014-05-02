import os
import subprocess

def speed_test(case):
    average_real = 0
    average_user = 0
    average_sys = 0

    print "Testing case:", case
    os.system("g++ -std=c++11 "+case)
    # process = subprocess.Popen(['g++', '-std=c++11', case], stdout=subprocess.PIPE)
    for i in range(1, 11):
        process = subprocess.Popen(['time', './a.out'], stderr=subprocess.PIPE)
        out, err = process.communicate()
        # print err
        real = float(err.split()[0])
        user = float(err.split()[2])
        sys = float(err.split()[4])

        average_real = (average_real*(i-1) + real)/i
        average_user = (average_user*(i-1) + user)/i
        average_sys = (average_sys*(i-1) + sys)/i

    print "<real> =", average_real
    print "<user> =", average_user
    print "<sys> =", average_sys



# cases = ["Array_looping.cpp", "Vector_looping.cpp", "Vector_looping_safer.cpp", "Vector_iterating.cpp", "Vector_iterating_opt.cpp", "Vector_iterating_c11.cpp"]

cases = ["map_insert.cpp", "unordered_map_insert.cpp", "map_find.cpp", "unordered_map_find.cpp", "map_iterate.cpp", "unordered_map_iterate.cpp", "map_iterate_opt.cpp", "unordered_map_iterate_opt.cpp"]


for case in cases:
    speed_test(case)
