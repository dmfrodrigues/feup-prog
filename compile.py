import os
import platform

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

if platform.system() == "Linux":
    print("Create build/linux/obj/, remove all content")
    os.system("mkdir -p build/linux/obj/")
    for f in os.listdir("build/linux/obj/"):
        os.remove("build/linux/obj/"+f)
    print('Done')
    print("Creating .o files...")
    lst = os.listdir("src/")
    N = max(len(s) for s in lst)+1;
    for f in lst:
        if f[-4:] != ".cpp": continue
        print("    compiling", f)
        cmd = "g++ " + w_str + " -std=c++11 -c " + ("src/%s"%f).ljust(N+4) + " -o " + ("build/linux/obj/%s.o"%(f.split("/")[-1])[:-4]).ljust(N+14) + " -I./include/"
        assert os.system(cmd) == 0
    print('Done')
    print("Create build/linux/bin/, link .o files...")
    os.system("mkdir -p build/linux/bin/")
    assert os.system("g++ -o build/linux/bin/main.app build/linux/obj/*.o") == 0
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
