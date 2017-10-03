import re
from os import listdir
from os import path
from sys import argv

if len(argv) < 2:
    cc = "g++ -Wall -std=c++14"
else:
    cc = argv[1]

if len(argv) < 3:
    libs = "-lsfml-graphics -lsfml-audio -lsfml-network -lsfml-window -lsfml-system"
else:
    libs = argv[2]
if len(argv) < 4:
    etc = "clean:\n\trm -rf *.o happyRUN\n\nformat:\n\t-astyle --style=kr --unpad-paren --indent=tab --align-reference=name --align-pointer=name *.cpp *.hpp\n\t-rm -rf *.orig"    
class makefile:
    name = ""
    etc = ""
    units = []
    dependencies = []
    cc = ""
    libs = ""
    def __init__(self, c, l, n, e):
        self.cc = c
        self.libs = l
        self.name = n
        self.etc = e
    def append_units(self, f):
        self.units.append(f)
    def append_dependencies(self, l):
        self.dependencies.append(l)
    def string_units(self):
        return str(self.units)
    def string_dependencies(self):
        return str(self.dependencies)
    def make_string(self):
        ret = self.name + ":"
        for unit in self.units:
            ret = ret + " " + unit + ".o"
        ret += "\n\t"
        ret += cc
        ret += " -o " + self.name
        for unit in self.units:
            ret = ret + " " + unit + ".o"
        ret += " " + self.libs + "\n\n"
        i = 0
        for unit in self.units:
            ret += unit + ".o :"
            for dep in self.dependencies[i]:
                ret += " " + dep
            ret += "\n\t"
            ret += cc + " -c "
            ret += unit + ".cpp"
            ret += "\n\n"
            i = i + 1
            
        ret += etc
        return ret
        
files = [f for f in listdir('.') if path.isfile(f)]

include = re.compile(r"#include \"([\w\.]+)\"")
cpp = re.compile(r"(\w+)\.cpp")

def read_includes_from(path):
    f = open(path, "r")
    includes = []
    for line in f:
        match = include.match(line)
        if match is not None:
            includes.append(match.groups()[0])
    f.close()        
    return includes

project = makefile(cc, libs, "happyRUN", etc)
for f in files:
    match = cpp.match(f)
    if match is not None:
        project.append_units(match.groups()[0])
        includes = read_includes_from(f)
        tmp_list = []
        for inc in includes:
            tmp_list = tmp_list + read_includes_from(inc)
        includes = includes + tmp_list
        includes.append(match.group())
        includes = list(set(includes))
        project.append_dependencies(includes)



outp = open("Makefile", "w")
outp.write(project.make_string())
