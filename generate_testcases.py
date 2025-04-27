import os

def make(path):
    print(f"Creating: {path}")
    os.makedirs(path, exist_ok=True)

def main():
    base = "testdata"

    make(f"testdata1/case1/a/x/y")
    make(f"testdata1/case1/a/z")
    make(f"testdata1/case1/b/x/y")
    make(f"testdata1/case1/b/z")

    make(f"testdata2/case2/a/x/y")
    make(f"testdata2/case2/a/z")
    make(f"testdata2/case2/b/x/y")
    make(f"testdata2/case2/b/z")
    make(f"testdata2/case2/b/extra")

    make(f"testdata3/case3/a/b/c")
    make(f"testdata3/case3/d/b/c")

    make(f"testdata4/case4/a/empty")
    make(f"testdata4/case4/b/empty")

    make(f"testdata5/case5/a/x")
    make(f"testdata5/case5/b/x")
    make(f"testdata5/case5/c/x")

    make(f"testdata6/case6/a/x")
    make(f"testdata6/case6/b/y")

    make(f"testdata7/case7/a/x/y")
    make(f"testdata7/case7/b/x/z")

    make(f"testdata8/case8/a/b/c")
    make(f"testdata8/case8/x/c")

    make(f"testdata9/sample/a/x/y")
    make(f"testdata9/sample/a/z")
    make(f"testdata9/sample/b/x/y")
    make(f"testdata9/sample/b/z")
    make(f"testdata9/sample/c/something")
    make(f"testdata9/sample/d/other")

if __name__ == "__main__":
    main()