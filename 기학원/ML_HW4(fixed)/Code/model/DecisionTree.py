import numpy as np
import random


def compute_entropy(labels):
    entropy = None
    # =============================== EDIT HERE ===============================
    positive = 0
    negative = 0
    for i in labels:
        if i == 'positive':
            positive += 1
        if i == 'negative' :
            negative += 1
    
    all = positive + negative
    positive = positive/all
    negative = negative/all
    if positive == 0 or negative == 0:
        entropy = 0
    else:
        entropy = -(positive*np.log2(positive) + negative*np.log2(negative))  
    # =========================================================================
    return entropy


class Node():
    def __init__(self, dataFrame, depth, split_feature=''):
        self.df = dataFrame
        self.depth = depth
        self.split_feature = split_feature

        self.entropy = compute_entropy(self.df.values[:, -1])
        self.child = {}
        self.is_leaf = False
        self.label = None


class DecisionTree():
    def __init__(self, max_depth, feature_select=False, num_features=3, verbose=0):
        self.max_depth = max_depth
        self.threshold = 0
        self.verbose = verbose
        self.feature_select = feature_select
        self.num_features = num_features

    def fit(self, train_df, data_name):
        self.root = Node(train_df, 0)

        self.branch_name = '(Root)'
        self.data_name = data_name
        
        self.generate_tree(self.root)
    
    def is_reached_max_depth(self, node: Node):
        if node.depth == self.max_depth:
            return True
        else:
            return False

    def is_reached_single_class(self, node: Node):
        if node.entropy == 0:
            return True
        else:
            return False

    def is_reached_stopping_criteria(self, node):
        """
        (when tree_depth == maximum_depth or impurity == 0), Set current node to leaf_node
        and decide class label.
        """
        if self.is_reached_max_depth(node) or self.is_reached_single_class(node):
            node.is_leaf = True
            labels = node.df.values[:, -1]
            node.label = 'positive' if (np.sum(labels == 'positive') > np.sum(labels == 'negative')) else 'negative'

            if self.verbose:
                print('\t'*node.depth, 'p:', np.sum(labels == 'positive'), 'n:', np.sum(labels == 'negative'))
                print('\t'*node.depth, 'Parent:', self.branch_name)
                print('\t'*node.depth, f'\__Depth \033[32m{node.depth}\033[0m | \033[95mLeaf node\033[0m | \033[95mLabel: {node.label}\033[0m')

            return True

        return False

    def selection_criteria(self, df):
        if self.feature_select:
            data_df = self.random_feature_selection(df, self.num_features)
        else:
            data_df = df

        input_features = data_df.columns.values[:-1]
        labels = data_df.values[:, -1]

        max_gain = -np.inf
        best_feature = None

        for feature in input_features:
            feature_data = data_df[feature].values
            
            # # categorical features
            distinct_values, counts = np.unique(feature_data, return_counts=True)
            entropy = None
            conditional_entropy = None
            information_gain = None
            
            # =============================== EDIT HERE ===============================
            n = 0
            x_num = 0
            o_num = 0
            b_num = 0

            for i in distinct_values:
                if i == 'x':
                    x_num = counts[n]
                if i == 'o':
                    o_num = counts[n]
                if i == 'b':
                    b_num = counts[n]
                n += 1

            all = x_num + o_num + b_num

            x_label = []
            o_label = []
            b_label = []

            num = len(feature_data)
            #print(feature)
            #print(feature_data)
            for i in range(0,num):
                #print(feature_data[i])
                if labels[i] == 'positive':
                    if feature_data[i] == 'x':
                        x_label.append('positive')
                    if feature_data[i] == 'o':
                        o_label.append('positive')
                    if feature_data[i] == 'b':
                        b_label.append('positive')
                else :
                    if feature_data[i] == 'x':
                        x_label.append('negative')
                    if feature_data[i] == 'o':
                        o_label.append('negative')
                    if feature_data[i] == 'b':
                        b_label.append('negative')
            
            entropy = compute_entropy(labels)
            conditional_entropy = 0
            if x_num != 0:
                conditional_entropy += (x_num/all)*(compute_entropy(x_label))
            if o_num != 0:
                conditional_entropy += (o_num/all)*(compute_entropy(o_label))
            if b_num != 0:
                conditional_entropy += (b_num/all)*(compute_entropy(b_label))
            
            information_gain = entropy - conditional_entropy
            # =========================================================================

            if information_gain > max_gain:
                max_gain = information_gain
                best_feature = feature

        return best_feature

    def random_feature_selection(self, df, num_features):
        feature_list = np.array(df.columns[:-1])
        label_col = np.array(df.columns[-1])
        random_features = None
        
        # =============================== EDIT HERE ===============================
        random_features = np.random.choice(feature_list,num_features,replace=False)
        # =========================================================================

        return df[np.append(random_features, label_col)]

    def generate_tree(self, node: Node):
        df = node.df

        if self.is_reached_stopping_criteria(node):
            return

        """
        For the feature that has the highest information gain,
        split the dataset and construct the child node
        """
        best_feature = self.selection_criteria(df)
        node.split_feature = best_feature

        feature_data = df[best_feature]

        if self.verbose:
            print('\t'*node.depth, 'Parent:', self.branch_name)

        distinct_values = np.unique(feature_data)

        for i, value in enumerate(distinct_values):
            if self.verbose:
                print('\t'*node.depth, f'\__Depth \033[32m{node.depth}\033[0m | Best Feature: \033[32m{node.split_feature}\033[0m | {i}th branch: \033[32m{value}\033[0m')
            
            child_df = df[feature_data == value].copy()
            child_node = Node(child_df, node.depth + 1, '%s = %s' % (best_feature, value))
            node.child[value] = child_node

            self.branch_name = f'({best_feature}/{str(value)})'
            self.generate_tree(node.child[value])

    def predict(self, x):
        pred = np.full(len(x), None)

        for i, idx in enumerate(x.index):
            cur_node = self.root
            x_pred = x.loc[idx]
            
            while True:
                if cur_node.is_leaf:
                    pred[i] = cur_node.label
                    break

                value = x_pred[cur_node.split_feature]

                try:
                    cur_node = cur_node.child[value]
                except:
                    break

        return pred

