def compile():
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
        fobj  = "build/linux/obj/"
        fbin  = "build/linux/bin/"
    elif platform.system() == "Windows":
        pmain = "build\\msw\\bin\\main.exe"
        fobj  = "build\\msw\\obj\\"
        fbin  = "build\\msw\\bin\\"


    print("Create", fobj)
    if not os.path.isdir(fobj): os.makedirs(fobj)
    print('Done')
    print("Creating .o files...")
    lst = os.listdir("src/")
    N = max(len(s) for s in lst)+1;
    for f in lst:
        pfrom = "src/"+f
        pto   = fobj+(f.split("/")[-1])[:-4]+".o"
        if f[-4:] != ".cpp": continue
        #if os.path.isfile(pto):
        #    if os.path.getmtime(pfrom) < os.path.getmtime(pmain):
        #        continue #DEV, recompile when needed
        print("    compiling", f)
        cmd = "g++ " + w_str + " -std=c++11 -c " + pfrom.ljust(N+4) + " -o " + pto.ljust(N+14) + " -I./include/"
        assert os.system(cmd) == 0
    print('Done')
    print("Create %s, link .o files..."%fbin)
    if not os.path.isdir(fbin): os.makedirs(fbin)
    assert os.system("g++ -o %s %s"%(pmain, ' '.join([fobj+s for s in os.listdir(fobj) if s[-2:] == ".o"]))) == 0
    print("Done")
    return pmain

def main():
    compile()

if __name__ == "__main__":
    main()
