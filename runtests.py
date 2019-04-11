import os
from compile import compile

pmain = compile()
for f1 in os.listdir("tests/"):
    if os.path.isdir("tests/"+f1):
        for f2 in os.listdir("tests/"+f1):
            f2_ = "tests/"+f1+"/"+f2
            if f2[-3:] != ".in": continue
            assert os.system("%s < %s"%(pmain, f2_)) == 0
