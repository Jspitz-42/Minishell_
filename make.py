import pathlib
from pprint import pprint as pp
import subprocess


def retrieve_commit():
    proc = subprocess.Popen(
        "git rev-parse HEAD".split(), stdout=subprocess.PIPE
    )
    _out, _ = proc.communicate()
    return _out.decode().strip()


def pending_modifications():
    proc = subprocess.Popen("git status -s".split(), stdout=subprocess.PIPE)
    _out, _ = proc.communicate()
    if len(_out.decode()) == 0:
        return ""
    return ".PENDING"


VERSIONING = retrieve_commit()
TARGET_NAME = f"minishell"
COMP = "clang"
DEBUG = True
COMP_FLAGS = "-Wall -Werror -Wextra -I./includes/ -I/usr/include/ "
COMP_FLAGS += "-O0 -ggdb" if DEBUG else "-O3"
COMP_FLAGS += " -Wno-enum-compare"

LIBS = [("libft", "ft")]
LIBS_DIR = "./libs/"
LIBS_PATH = [f"{LIBS_DIR}{lib[0]}" for lib in LIBS]
LINK_PATHS = " ".join([f"-L{path}" for path in LIBS_PATH])
LINK_NAMES = " ".join([f"-l{lib[1]}" for lib in LIBS])
LINK = f"{LINK_PATHS} {LINK_NAMES} -lreadline"


cwd = pathlib.Path(".")
dirs = {}
for file in cwd.glob("**/*.c"):
    path_parts = str(file).split("/")
    file_name = path_parts[-1]
    if path_parts[0] in ["libs", "__tests__"]:
        continue
    trunc_path_parts = path_parts[:-1]
    if len(path_parts) == 1:
        var_name = "CWD"
    else:
        var_name = "_".join([part.upper() for part in trunc_path_parts])
    if var_name not in dirs.keys():
        dirs[var_name] = dict()
        dirs[var_name]["path"] = "/".join(trunc_path_parts)
        dirs[var_name]["files"] = []
    path_dict = {"name": file_name, "relative_path": "/".join(path_parts[1:])}
    dirs[var_name]["files"].append(path_dict)


path_str = ""
files_str = ""
full_path_str = ""
obj_str = ""
obj_vars = []

for key in dirs:
    entry = dirs[key]
    end_char = "/" if len(entry["path"]) else ""
    path_str += f"{key}_SRC_PATH=./{entry['path']}{end_char}\n"
    files_str_part = f"{key}_SRC_FILES="
    for i, file in enumerate(entry["files"]):
        if i > 0:
            files_str_part += "\t"
        files_str_part += file["name"]
        if i < len(entry["files"]) - 1:
            files_str_part += " \\\n"
    files_str += files_str_part + "\n\n"
    full_path_str += (
        f"{key}_FULL_PATH=$(addprefix $({key}_SRC_PATH), $({key}_SRC_FILES))\n"
    )
    obj_vars.append(f"{key}_OBJ")
    obj_str += f"{key}_OBJ=$({key}_FULL_PATH:.c=.o)\n"

makefile_head = f"""#This makefile was auto generated, ain't no way I'm writing all that by hand
NAME={TARGET_NAME}
CC={COMP}
CFLAGS={COMP_FLAGS}
LINK={LINK}
"""
obj_vars_formatted = " ".join([f"$({var})" for var in obj_vars])
clean_rule = "\n\t".join([f"rm -f $({var})" for var in obj_vars])
libs_cc_rules = "\n".join(["\tmake -C " + lib_path for lib_path in LIBS_PATH])
libs_clean_rules = "\n".join(
    ["\tmake clean -C " + lib_path for lib_path in LIBS_PATH]
)
libs_fclean_rules = "\n".join(
    ["\tmake fclean -C " + lib_path for lib_path in LIBS_PATH]
)
rules = f"""
$(NAME): {obj_vars_formatted}
{libs_cc_rules}
\t$(CC) $(CFLAGS) -o $@ $^ $(LINK)

all: $(NAME)

clean:
\t{clean_rule}
{libs_clean_rules}

fclean: clean
\trm -f $(NAME)
{libs_fclean_rules}

re: fclean all

default: all

.PHONY: default all re fclean clean"""
makefile_content = "\n".join(
    [makefile_head, path_str, files_str, full_path_str, obj_str, rules]
)
with open("Makefile", "w") as file:
    file.write(makefile_content)
