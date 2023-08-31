import os, sys

_, f1, f2, gen, iters = sys.argv

for i in range(int(iters)):
    print('Test', i + 1)
    os.system(f'python3 {gen} > test-input')
    v1 = os.popen(f'./{f1} < test-input').read()
    v2 = os.popen(f'./{f2} < test-input').read()
    if v1 != v2:
        print("Failed test:")
        print(open("test-input").read())
        print(f'Output of {f1}:')
        print(v1)
        print(f'Output of {f2}:')
        print(v2)
        break