import numpy as np

import matplotlib.pyplot as plt
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier, RandomForestClassifier
from sklearn.metrics import accuracy_score

from sklearn import datasets
from sklearn.model_selection import train_test_split


np.random.seed(0)

b_cancer = datasets.load_breast_cancer()

data = b_cancer.data
label = b_cancer.target
columns = b_cancer.feature_names

x_train, x_test, y_train, y_test = train_test_split(data, label, test_size=0.2, random_state=0)

depth = 3
num_models = [1, 20, 50, 100]

train_results_DT = []
test_results_DT = []

train_results_RF = []
test_results_RF = []

train_results_AB = []
test_results_AB = []

search_space = num_models
for i, space in enumerate(search_space):
    DecisionTree = DecisionTreeClassifier(criterion='entropy', max_depth=depth, random_state=0)
    RandomForest = RandomForestClassifier(criterion='entropy', max_depth=depth, random_state=0, n_estimators=space)
    AdaBoost = AdaBoostClassifier(DecisionTreeClassifier(criterion='entropy', max_depth=depth, random_state=0), n_estimators=space, random_state=0)

    # fit
    DecisionTree.fit(x_train, y_train)
    RandomForest.fit(x_train, y_train)
    AdaBoost.fit(x_train, y_train)
    
    # predict train
    pred_train = DecisionTree.predict(x_train)
    score_train = accuracy_score(pred_train, y_train)
    train_results_DT.append(score_train)

    pred_train = RandomForest.predict(x_train)
    score_train = accuracy_score(pred_train, y_train)
    train_results_RF.append(score_train)

    pred_train = AdaBoost.predict(x_train)
    score_train = accuracy_score(pred_train, y_train)
    train_results_AB.append(score_train)

    # predict test
    pred_test = DecisionTree.predict(x_test)
    score_test = accuracy_score(pred_test, y_test)
    test_results_DT.append(score_test)

    pred_test = RandomForest.predict(x_test)
    score_test = accuracy_score(pred_test, y_test)
    test_results_RF.append(score_test)

    pred_test = AdaBoost.predict(x_test)
    score_test = accuracy_score(pred_test, y_test)
    test_results_AB.append(score_test)

"""
Draw scatter plot of search results.
- X-axis: search paramter
- Y-axis: RMSE (Train, Test respectively)

Put title, X-axis name, Y-axis name in your plot.

Resources
------------
Official document: https://matplotlib.org/3.2.1/api/_as_gen/matplotlib.pyplot.scatter.html
"Data Visualization in Python": https://medium.com/python-pandemonium/data-visualization-in-python-scatter-plots-in-matplotlib-da90ac4c99f9
"""

num_space = len(search_space)
plt.scatter(search_space, train_results_DT, label='train(DT)')
plt.scatter(search_space, test_results_DT, label='test(DT)')
plt.scatter(search_space, train_results_RF, label='train(RF)')
plt.scatter(search_space, test_results_RF, label='test(RF)')
plt.scatter(search_space, train_results_AB, label='train(AB)')
plt.scatter(search_space, test_results_AB, label='test(AB)')
plt.legend()
plt.title('Search results')
plt.xlabel('# of Estimators')
plt.ylabel('Acc.')
plt.savefig('search_result')
