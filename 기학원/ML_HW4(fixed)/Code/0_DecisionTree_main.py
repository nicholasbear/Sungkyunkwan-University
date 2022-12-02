import os.path
import numpy as np
from model.DecisionTree import DecisionTree
from utils import *

np.random.seed(1)
random.seed(1)


def main():
    data_name = 'TicTacToe'
    # =============================== EDIT HERE ===============================
    tree_depth = 5
    # =========================================================================
    
    print(f"> data_name: {data_name}")
    print(f"> tree_depth: {tree_depth}")
    
    data_df = pd.read_csv(os.path.join('data', 'TicTacToe.csv'))
    train_df, test_df = train_test_split(data_df, 0.2)

    train_df = train_df.dropna()
    test_df = test_df.dropna()
    x_test, y_test = split_to_x_y(test_df, test_df.columns.values)

    Dtree = DecisionTree(max_depth=tree_depth)
    Dtree.fit(train_df, data_name)

    pred_test = Dtree.predict(x_test)
    y_test = y_test.values
    test_accuracy = np.sum((pred_test == y_test)) / len(y_test)
    print('Test accuracy: %.4f' % test_accuracy)


if __name__ == '__main__':
    main()
