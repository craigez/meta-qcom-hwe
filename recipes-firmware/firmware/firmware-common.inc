# Common functions used across firmware recipes
def get_matching_machine(d) :
    cmpt_machine = d.getVar('COMPATIBLE_MACHINE')
    if cmpt_machine:
        import re
        available_archs = (d.getVar('MACHINEOVERRIDES') or "").split(":")
        for selected_arch in reversed(available_archs):
            if re.match(cmpt_machine, selected_arch):
                return selected_arch
    return None

def firmware_install(d, firmware, fw_path) :

    import os
    import shutil

    dstdir = d.getVar('WORKDIR')

    # Move content into ${D}
    root = os.path.join(dstdir, firmware)
    for item in os.listdir(root):
        if os.path.isdir(os.path.join(root, item)):
            shutil.copytree(os.path.join(root, item), os.path.join(d.getVar('D'), item))
        elif os.path.isfile(os.path.join(root, item)):
            shutil.copy2(os.path.join(root, item), d.getVar('D'))
