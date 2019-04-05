import os
import platform
import time

w_lst =    ["-Wpedantic",\
            "-Wall",\
            "-Wextra",\
            "-Wcast-align",\
            "-Wcast-qual",\
            "-Wctor-dtor-privacy",\
            "-Wdisabled-optimization",\
            #"-Wformat=2",\
            "-Winit-self",\
            "-Wlogical-op",\
            "-Wmissing-declarations",\
            "-Wmissing-include-dirs",\
            "-Wnoexcept",\
            #"-Wold-style-cast",\
            "-Woverloaded-virtual",\
            "-Wredundant-decls",\
            "-Wshadow",\
            "-Wsign-conversion",\
            "-Wsign-promo",\
            "-Wstrict-null-sentinel",\
            "-Wstrict-overflow=5",\
            "-Wswitch-default",\
            "-Wundef",\
            #"-Werror",\
            "-Wno-unused"]
w_str = " ".join(w_lst)

now = time.time()

if platform.system() == "Linux":
    pmain = "build/linux/bin/main.app"
    fobj = "build/linux/obj/"
    fbin = "build/linux/bin/"

    print("Create", fobj)
    os.makedirs(fobj)
    print('Done')
    print("Creating .o files...")
    lst = os.listdir("src/")
    N = max(len(s) for s in lst)+1;
    for f in lst:
        ffrom = "src/"+f
        fto   = ("%s%s.o"%(fobj, f.split("/")[-1])[:-4])
        if f[-4:] != ".cpp": continue
        if (not os.path.isfile(fto)) or os.path.getmtime(ffrom) < os.path.getmtime(fmain): continue #DEV, recompile when needed
        print("    compiling", f)
        cmd = "g++ " + w_str + " -std=c++11 -c " + ffrom.ljust(N+4) + " -o " + fto.ljust(N+14) + " -I./include/"
        assert os.system(cmd) == 0
    print('Done')
    print("Create %s, link .o files..."%fbin)
    os.makedirs(fbin)
    assert os.system("g++ -o %s %s*.o"%(pmain, fobj)) == 0
    print("Done")

"""
elif platform.system() == "Windows":
    print("Create ./msw/obj/, remove all content")
    if not os.path.exists("msw\\obj"):
        os.mkdir("msw")
        os.mkdir("msw\\obj")
    for f in os.listdir(".\\msw\\obj"):
        os.remove(f)
    print("Creating .o files...")
    for f in os.listdir("src"):
        if f[-4:] != ".cpp": continue
        print("g++ -Wall -std==c++11 -c src\\%s -o msw\\obj\\%s -I.\\include\\"%(f, f))
        os.system("g++ -Wall -std==c++11 -c src\\%s -o msw\\obj\\%s -I.\\include\\"%(f, f))
"""
