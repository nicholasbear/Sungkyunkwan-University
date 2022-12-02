import numpy as np
import torch
from models.PolynomialRegression import PolynomialRegression
from utils import load_data

np.random.seed(530)
torch.random.manual_seed(530)

DATA_NAME = 'Polynomial'

# Load dataset, model and evaluation metric
train_data, test_data = load_data(DATA_NAME)
train_x, train_y = train_data
test_x, test_y = test_data

num_data, _ = train_x.shape

print('# of Training data : %d \n' % num_data)

# ========================= EDIT HERE =========================
"""
e.g.)
degree_list=[1, 3, 5]
"""
# HYPERPARAMETERS
degree_list=[1,3,5]
# =============================================================

## These hyperparameters are fixed, do not change them.
batch_size = 2000 
num_epochs = 100000
learning_rate = 2e-6 

train_results = []
test_results = []

# Build model
for degree in degree_list:
    model = PolynomialRegression(degree=degree)

    model.train(train_x, train_y, batch_size, num_epochs, learning_rate)

    ################### Evaluate on train data
    # Inference
    train_rmse = model.eval(train_x, train_y, batch_size)
    print(f'RMSE on Train Data (degree: {degree}): {train_rmse:.4f}')

    ################### Evaluate on test data
    # Inference
    test_rmse = model.eval(test_x, test_y, batch_size)
    print(f'RMSE on Test Data (degree: {degree}): {test_rmse:.4f}')