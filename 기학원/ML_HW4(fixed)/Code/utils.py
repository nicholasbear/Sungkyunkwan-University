import random
import numpy as np
import pandas as pd
import os

from random import sample

def set_random_seed(random_seed):
    np.random.seed(random_seed)
    random.seed(random_seed)


def train_test_split(df, ratio):
    n = len(df)
    test_idx = sample(range(n), int(ratio * n))
    train_idx = np.delete(range(n), test_idx)

    train = df.loc[train_idx]
    test = df.loc[test_idx]

    train.reset_index()
    test.reset_index()

    return train, test


def split_to_x_y(df, feature):

    input_feature = feature[:-1]
    class_label = feature[-1]

    X = df[input_feature]
    Y = df[class_label]

    return X, Y


def load_data(data_name, data_type):
    path = os.path.join('./data', data_type, f'{data_name}.csv')

    x, y = DiabetesData(os.path.join(path), target_at_front=False, normalize=True)

    return x, y


def DiabetesData(filename, target_at_front, normalize=False, shuffle=False):
    fullpath = os.path.join(path, filename)

    with open(fullpath, 'r') as f:
        lines = f.readlines()
    lines = [s.strip().split(',') for s in lines]

    data = lines[1:]

    data = np.array([[float(f) for f in d] for d in data], dtype=np.float32)
    if target_at_front:
        x, y = data[:, 1:], data[:, 0]
    else:
        x, y = data[:, :-1], data[:, -1]

    num_data = x.shape[0]
    if normalize:
        mins = np.expand_dims(np.min(x, axis=0), 0).repeat(num_data, 0)
        maxs = np.expand_dims(np.max(x, axis=0), 0).repeat(num_data, 0)
        x = (x - mins) / maxs

    if shuffle:
        perm = np.random.permutation(num_data)
        x = x[perm]
        y = y[perm]

    return x, y