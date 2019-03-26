import os
import platform

if platform.system() == "Linux":
    print("Create ./build/linux/obj/, remove all content")
    os.system("mkdir -p build/linux/obj")
    for f in os.listdir("build/linux/obj"):
        os.remove(f)

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
