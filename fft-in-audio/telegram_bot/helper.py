import json


def read_file(path):
    with open(path, 'r') as f:
        return f.read()

def get_json(path):
    with open(path, 'r') as f:
        return json.load(f)