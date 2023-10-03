now_test_number = 1


def create_test(n):
    global now_test_number
    output = open("tests/test_" + str(now_test_number) + ".txt", "w")
    now_test_number += 1
    print(n, file=output)
    output.close()


create_test(0)
create_test(10)
create_test(25)
create_test(36)
for i in range(1, 21):
    create_test(i * 50)
# for i in range(1, 21):
#     create_test(i * 50)


create_test(1030)
create_test(1403243)