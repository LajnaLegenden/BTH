#import to show what code does
from dis import dis

def main():
        
    n = 101
    s = 100000000
    a = 0
    t = 0

    while n > 0:
        if t == 0:
            d = n
            t = 1
        else:
            d = -n
            t = 0
        a = a + s / d
        print a
        n = n - 2
    print(a / (s / 100000) * 4)

main()

print(dis(main))
