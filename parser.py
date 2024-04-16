import sys
import os

import zipfile
import py7zr
import tarfile

import json

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

def parse_zip(path):
    extract_path = path[:-4]

    with zipfile.ZipFile(path, 'r') as zip_ref:
        zip_ref.extractall(extract_path)

    archive_struct = [ [root, [subdir for subdir in subdirs], [filename for filename in files]] for root, subdirs, files in os.walk(extract_path) ]

    return archive_struct, extract_path

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

def parse_7z(path):
    extract_path = path[:-3]

    archive = py7zr.SevenZipFile(path, mode='r')
    archive.extractall(path=extract_path)
    archive.close()

    archive_struct = [ [root, [subdir for subdir in subdirs], [filename for filename in files]] for root, subdirs, files in os.walk(extract_path) ]

    return archive_struct, extract_path

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

def parse_tar(path):
    extract_path = path[:-4]

    archive = tarfile.open(path, mode='r')
    archive.extractall(extract_path)
    archive.close()

    archive_struct = [ [root, [subdir for subdir in subdirs], [filename for filename in files]] for root, subdirs, files in os.walk(extract_path) ]

    return archive_struct, extract_path

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

def parse_readme(path):

    print(path)

    file = open(path, "r")

    script_path = []
    pkg_path = []
    ip_list = []
    password_list = []
    role_list = []
    miscdir_list = []

    try:

        lines = file.readlines()

    except:

        file.close()
        return (script_path, pkg_path, ip_list, password_list, role_list, miscdir_list)

    for line in lines:
        split_line = line.replace("\n", "").split(" ")

        if split_line[0] == "": continue

        script_path.append(split_line[0])

        for i in range(len(split_line)):
            if (-1 != split_line[i].find("--ip="))\
                    & ("ip_address" != split_line[i][5:].lower())\
                    & ("ipaddress" != split_line[i][5:].lower())\
                    & ("address" != split_line[i][5:].lower()):
                ip_list.append(split_line[i][5:])

            if (-1 != split_line[i].find("--password=")) & ("password" != split_line[i][11:].lower()):
                password_list.append(split_line[i][11:])


            if -1 != split_line[i].find("--role="):
                role_list.append(split_line[i][7:])

            if -1 != split_line[i].find("--pkg="):
                pkg_path.append(split_line[i][6:])

            if -1 != split_line[i].find("--miscdir="):
                miscdir_list.append(split_line[i][10:])


    file.close()

    script_path     =   list(set(script_path))    if  script_path     != [] else []
    pkg_path        =   list(set(pkg_path))       if  pkg_path        != [] else []
    ip_list         =   list(set(ip_list))        if  ip_list         != [] else []
    password_list   =   list(set(password_list))  if  password_list   != [] else []
    role_list       =   list(set(role_list))      if  role_list       != [] else []
    miscdir_list    =   list(set(miscdir_list))   if  miscdir_list    != [] else []

    return (script_path, pkg_path, ip_list, password_list, role_list, miscdir_list)

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

def edit_config(script_path, archive_path, master_files, slave_files, password):

    json_file = open("./config.json", "r")

    json_data = json.loads(json_file.read())

    json_file.close()

    json_file = open("./config.json", "w")

    json_data['InstallArchivePath'] = archive_path
    json_data['InstallScriptPath'] = script_path

    json_data['MasterFiles'] = master_files
    json_data['SlaveFiles'] = slave_files

    json_data['InstallPassword'] = password

    json_data['StartCycleInstallValue'] = (True, True, True, True)

    json_file.write(json.dumps(json_data, indent=4, ensure_ascii=False))

    json_file.close()

    return

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

def patch_install_script(script_path):
    script = open(script_path, 'a')

    script.write("\nexit 0")

    script.close()

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

def main():
    args = sys.argv[1:]

    archive_path = ""
    archive_type = ""

    extract_path = ""

    print("PARSER ", sys.argv)

    for index in range(len(args)):
        if args[index] == "--arch_path":
            archive_path = args[index + 1]

            archive_type = archive_path.split(".")[-1]

            if archive_type == "zip":
                archive_struct, extract_path = parse_zip(archive_path)
            elif archive_type == "7z":
                archive_struct, extract_path = parse_7z(archive_path)
            elif archive_type == "tar":
                archive_struct, extract_path = parse_tar(archive_path)
            else:
                print("Unknown archive format")
                return


    master_files = ""
    slave_files = ""
    install_script_path = ""
    install_archive_path = ""
    readme_path = ""

    standart_password = "mesdk059"

    for line in archive_struct:
        for subdir in line[1]:
            if -1 != subdir.lower().find("master_file"):
#                print("MASTER!!!")
                master_files = subdir
            if -1 != subdir.lower().find("slave_file"):
#                print("SLAVE!!!")
                slave_files = subdir


        for file in line[2]:
            if -1 != file.lower().find("install"):
#                print("INSTALL!!!")
                install_script_path = line[0] + "/" + file


            if file.lower().endswith(".tar"):
#                print("ARCHIVE .tar !!!")
                install_archive_path = file
            if file.lower().endswith(".tar.gz"):
#                print("ARCHIVE .tar.gz !!!")
                install_archive_path = file
            if file.lower().endswith(".tar.gz2"):
#                print("ARCHIVE .tar.gz2 !!!")
                install_archive_path = file
            if file.lower().endswith(".tar.bz"):
#                print("ARCHIVE .tar.bz !!!")
                install_archive_path = file
            if file.lower().endswith(".tar.bz2"):
#                print("ARCHIVE .tar.bz2 !!!")
                install_archive_path = file


            if -1 != file.lower().find("read.me"):
                print("README!!!")
                readme_path = line[0] + "/" + file
            elif -1 != file.lower().find("readme"):
                print("README!!!")
                readme_path = line[0] + "/" + file

#        print(line)

#    print(master_files)
#    print(slave_files)
#    print(install_script_path)
#    print(install_archive_path)
#    print(readme_path)

    readme_script_path = []
    readme_archive_path = []
    readme_ip_list = []
    readme_password_list = []
    readme_role_list = []
    readme_miscdir_list = []

    if readme_path != "":
        readme_script_path, readme_archive_path, readme_ip_list, readme_password_list, readme_role_list, readme_miscdir_list = parse_readme(readme_path)

#    print("archive data:", master_files, slave_files, install_script_path, install_archive_path, readme_path)
#    print("readme data:", readme_script_path, readme_archive_path, readme_ip_list, readme_password_list, readme_role_list, readme_miscdir_list)

    finish_script_path = ("/".join(readme_path.split("/")[:-1]) + readme_script_path[0] if readme_script_path[0][:2] != "./" else "/".join(readme_path.split("/")[:-1]) + "/" + readme_script_path[0][2:]) if readme_script_path != [] else install_script_path
    finish_archive_path = install_archive_path

    finish_master_files = master_files
    finish_slave_files = slave_files

    finish_password = readme_password_list[0] if readme_password_list != [] else standart_password

    print(extract_path)
    print("finish data:", finish_script_path, finish_archive_path, finish_master_files, finish_slave_files)

    os.chmod(finish_script_path, 0o755)

    edit_config(finish_script_path, finish_archive_path, finish_master_files, finish_slave_files, finish_password)

    patch_install_script(finish_script_path)

    return

# ---------------------------------------------------------------------------------------------------------------------------------------------------------

if __name__ == '__main__':
    main()
