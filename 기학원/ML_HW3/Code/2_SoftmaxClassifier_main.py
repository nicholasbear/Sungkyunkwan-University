import torch
import numpy as np
from models.SoftmaxClassification import SoftmaxClassification
from utils import load_data

np.random.seed(530)
torch.random.manual_seed(530)

DATA_NAME = 'Wine'

# Load dataset, model and evaluation metric
train_data, test_data = load_data(DATA_NAME)
train_x, train_y = train_data
test_x, test_y = test_data

num_data, num_features = train_x.shape
num_label = int(train_y.max()) + 1

print('# of Training data : %d \n' % num_data)

# ========================= EDIT HERE =========================
"""
e.g.)
reg_lambda_list=[0.0, 0.01, 0.1, 1.0]
"""
# HYPERPARAMETERS
reg_lambda_list=[0.0, 0.01, 0.1, 1.0]
# =============================================================

## These hyperparameters are fixed, do not change them.
batch_size = 64
num_epochs = 4000 
learning_rate = 0.0001

for reg_lambda in reg_lambda_list:
    model = SoftmaxClassification(num_features, num_label)

    model.train(train_x, train_y, batch_size, num_epochs, learning_rate, reg_lambda)

    ################### Evaluate on train data
    # Inference
    train_acc, _ = model.eval(train_x, train_y, batch_size)
    print(f'Accuracy on Train Data : {train_acc:.4f}%')

    ################### Evaluate on test data
    # Inference
    test_acc, _ = model.eval(test_x, test_y, batch_size)
    print(f'Accuracy on Test Data: {test_acc:.4f}%')