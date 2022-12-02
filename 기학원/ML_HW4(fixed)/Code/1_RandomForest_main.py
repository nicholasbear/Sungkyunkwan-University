import os.path
import numpy as np
from model.DecisionTree import DecisionTree
from utils import *
from model.BaggingSampler import BaggingSampler
import pandas as pd

np.random.seed(1)
random.seed(1)


def main():
    data_name = 'TicTacToe'
    tree_depth = 3
    num_features = 3
    # =============================== EDIT HERE ===============================
    sampling_ratio = 0.6
    num_datasets = 50
    # =========================================================================
    
    data_df = pd.read_csv(os.path.join('data', 'TicTacToe.csv'))
    train_df, test_df = train_test_split(data_df, 0.2)

    train_df = train_df.dropna()
    test_df = test_df.dropna()
    x_test, y_test = split_to_x_y(test_df, test_df.columns.values)

    y_test = y_test.values
    y_test[y_test == 'negative'] = 0
    y_test[y_test == 'positive'] = 1

    sampler = BaggingSampler(num_datasets, sampling_ratio)
    datasets = sampler.create_datasets(train_df)

    models = []
    for dataset in datasets:
        Dtree = DecisionTree(tree_depth, feature_select=True, num_features=num_features)
        Dtree.fit(dataset, data_name)
        models.append(Dtree)
    
    preds = []
    for model in models:
        pred = model.predict(x_test)
        preds.append(pred)

    preds = np.array(preds)
    preds[preds == 'negative'] = 0
    preds[preds == 'positive'] = 1

    pred_test = []
    for i in range(len(y_test)):
        temp = preds[:, i]
        pred_not_none = temp[temp != None]
        pred_test.append((pred_not_none.mean(axis=0) > 0.5).astype(float))
    
    pred_test = np.array(pred_test)

    test_accuracy = np.sum((pred_test == y_test)) / len(y_test)
    print('Test accuracy: %.4f' % test_accuracy)


if __name__ == '__main__':
    main()
