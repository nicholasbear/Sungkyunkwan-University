import torch
import numpy as np
from models.SoftmaxClassification import SoftmaxClassification
from utils import load_data, draw_confusion_matrix
from evaluation.EvaluationMetrics import EvaluationMetric

np.random.seed(530)
torch.random.manual_seed(530)

DATA_NAME = 'Wine'

# Load dataset, model and evaluation metric
train_data, test_data = load_data(DATA_NAME)
train_x, train_y = train_data
test_x, test_y = test_data

num_data, num_features = train_x.shape
num_label = len(np.unique(train_y))

print('# of Training data : %d \n' % num_data)

batch_size = 64
num_epochs = 4000 
learning_rate = 0.0001

train_results = []
test_results = []

# Build model
model = SoftmaxClassification(num_features, num_label)

model.train(train_x, train_y, batch_size, num_epochs, learning_rate)

################### Evaluate on test data
# Inference
test_acc, test_y_pred = model.eval(test_x, test_y, batch_size)
print(f'Accuracy on Test Data: {test_acc:.4f}%\n')

# evaluation (for test data)
pred, true = test_y_pred, test_y
metric = EvaluationMetric(num_label)

metric._set_confusion_matrix(pred, true)
draw_confusion_matrix(metric.c_m_c)

scores = metric.multiclass_f_measure(pred, true)

for key in scores.keys():
    print(f"{key}: {scores[key]:.4f}")