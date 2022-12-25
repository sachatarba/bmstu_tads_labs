from random import randint


def make_test(size):
    # lst = [int(x) for x in range()]
    with open(f"../test{size}.txt") as test:
        for i in range(size):
            test.write(str(f"{randint(0, 1000)}\n"))

def main():
    make_test(100)
    make_test(500)
    make_test(1000)

if __name__ == "__main__":
    main()
