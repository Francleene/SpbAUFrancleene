import hashlib
import os
import sys

def calc_hash(file_name):
    hash_md5 = hashlib.md5()
    with open(file_name, "rb") as f:
        buffer = f.read(65536)
        while (buffer):
            hash_md5.update(buffer)
            buffer = f.read(65536)
    return hash_md5.hexdigest()

def make_dict_from_files(root_path):
    hashes = dict()
    for dirname, _, filenames in os.walk(root_path):
        for filename in filenames:
            path_to_file = os.path.join(dirname, filename)
            if not filename.startswith('.') and not filename.startswith('~') and not os.path.islink(path_to_file):
                hash_file = calc_hash(path_to_file)
                hashes.setdefault(hash_file, []).append(path_to_file)
    return hashes

def print_same_files(root_path):
    hashes = make_dict_from_files(root_path)
    for _, files in hashes.items():
        if len(files) > 1:
            print(":".join(files))

def main():
    if len(sys.argv) != 2:
        print("usage: ./hash.py dir")
        sys.exit(1)
        
    root_path = sys.argv[1]
    
    if os.path.isdir(root_path):
        print_same_files(root_path)
    else:
        print("dir doesn't exist")
        sys.exit(1)
    
if __name__ == '__main__':
    main()
