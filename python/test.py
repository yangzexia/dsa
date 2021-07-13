
import sys

def main(argv):
    if argv[1] == '1':
        print ("argv = 1")
        print(argv)
    else:
        print(argv[1])

if __name__ == "__main__":
    main(sys.argv)