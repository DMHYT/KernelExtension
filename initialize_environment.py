'''
YOU HAVE TO RUN THIS SCRIPT WHEN YOU HAVE JUST
INITIALIZED THE PROJECT OR CLONED YOUR PROJECT'S
GITHUB REPOSITORY. WITHOUT RUNNING IT, NONE OF
THE BUILD TASKS WILL WORK.
AFTER RUNNING THIS SCRIPT, PRESS CTRL+SHIFT+B AND
RUN `Initialize Environment` TASK,
FOR ALL OTHER NEEDED FILES TO DOWNLOAD
'''


from urllib.request import urlretrieve
from zipfile import ZipFile
from os import remove, getcwd, listdir, mkdir
from os.path import join, exists, isfile, isdir
from shutil import copy2, rmtree
from time import time


def copytree(src, dst, symlinks=False, ignore=None):
    if not exists(src) or isfile(src):
        raise Exception()
    for item in listdir(src):
        s = join(src, item)
        d = join(dst, item)
        if isdir(s):
            if not exists(d):
                mkdir(d)
            copytree(s, d, symlinks, ignore)
        else:
            copy2(s, d)


print("Initializing development environment...")
start = time()


url = "https://codeload.github.com/DMHYT/innercore-mod-toolchain/zip/gitignored-toolchain"
cwd = getcwd()
toolchain_path = join(cwd, "toolchain")
archive_path = join(toolchain_path, "archive.zip")


urlretrieve(url=url, filename=archive_path)
with ZipFile(archive_path, 'r') as archive:
    archive.extractall(toolchain_path)
remove(archive_path)


shit = join(toolchain_path, "innercore-mod-toolchain-gitignored-toolchain")
copytree(shit, toolchain_path)
rmtree(shit)


root_zip = join(toolchain_path, "root.zip")
if exists(root_zip):
    with ZipFile(root_zip, 'r') as root:
        root.extractall(cwd)
    remove(root_zip)


end = time()
print("done in " + str(round((end - start) * 1000)) + " ms")