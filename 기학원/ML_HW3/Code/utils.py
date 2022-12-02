import os
import seaborn as sn
import numpy as np
import pandas as pd
from matplotlib import pyplot as plt

from sklearn.model_selection import train_test_split


def draw_confusion_matrix(confusion_matrix):
    LABELS = ["POSITIVE", "NEGATIVE"]
    for i, cm in enumerate(confusion_matrix):
        plt.figure()
        cm_array = np.array(list(cm.values())).reshape(2, 2)
        sn.heatmap(cm_array, annot=True, xticklabels=LABELS, yticklabels=LABELS, fmt='d', cmap='Reds', linewidths=0.5)
        plt.title(f"CONFUSION MATRIX: {i}")
        plt.xlabel('True label')
        plt.ylabel('Predicted Label')

        plt.savefig(f'confusion_matrix_{i}.png')
        plt.clf()

    return None

def Polynomial(path, filename):
    df = pd.read_csv(os.path.join(path, filename))
    
    x = df.values[:, 0].astype(np.float32).reshape(-1, 1)
    y = df.values[:, 1].astype(np.float32).reshape(-1, 1)
    
    return x, y

def Wine(path, filename): 
    data = pd.read_csv(os.path.join(path, filename), header=None)
    x = data.values[:, 1:].astype(np.float32)
    y = data.values[:, 0].astype(np.int64) - 1 # for zero start

    train_x, test_x, train_y, test_y = train_test_split(x, y, test_size=0.2, random_state=42)
    
    return train_x, train_y, test_x, test_y

def MNIST(data_path, filename):
    # read train and test data from train.csv and test.csv
    df = pd.read_csv(os.path.join(data_path, filename))

    x = df.values[:, 1:].astype(np.float32)
    y = df.values[:, 0].astype(np.int64)

    return x, y


data_dir = {
    'Polynomial': 'polynomial',
    'Wine': 'wine',
    'MNIST': 'mnist',
}


def load_data(data_name):
    dir_name = data_dir[data_name]
    path = os.path.join('./data', dir_name)

    if data_name == 'Polynomial':
        train_x, train_y = Polynomial(path, 'train.csv')
        test_x, test_y = Polynomial(path, 'test.csv')
    elif data_name == 'Wine':
        train_x, train_y, test_x, test_y = Wine(path, 'wine.data')
    elif data_name == 'MNIST':
        train_x, train_y = MNIST(path, 'train.csv')
        test_x, test_y = MNIST(path, 'test.csv')
    else:
        raise NotImplementedError

    return (train_x, train_y), (test_x, test_y)
