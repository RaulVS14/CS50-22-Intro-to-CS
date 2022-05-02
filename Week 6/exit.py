import sys

if len(sys.argv) != 2:
    print("Missing command-line argument!")
    sys.exit(1)
else:
    print("hello, world")
sys.exit(0)