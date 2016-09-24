import hashlib
import os
import sys

def calc_hash(file_name):
    hash_md5 = hashlib.md5()
    with open(file_name, "rb") as f:
        buffer = f.read(65536)
        while (len(buffer) > 0):
            hash_md5.update(buffer)
            buffer = f.read(65536)
    return hash_md5.hexdigest()

def make_dict_from_files(root_path):
    hashes = dict()
    for dirname, curdirs, filenames in os.walk(root_path):
        curdirs[:] = [d for d in curdirs if not d.startswith('.') and not d.startswith('~')]
        for filename in filenames:
            if not filename.startswith('.') and not filename.startswith('~'):
                path_to_file = os.path.join(dirname, filename)
                hash_file = calc_hash(path_to_file)
                hashes.setdefault(hash_file, []).append(path_to_file)
    return hashes

def print_same_files(root_path):
    hashes = make_dict_from_files(root_path)
    for _, files in hashes.items():
        if (len(files) > 1):
            print(":".join(files))

def main():
    root_path = sys.argv[1]
    print_same_files(root_path)
    
if __name__ == '__main__':
    main()
