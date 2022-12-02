from doctest import OutputChecker
import numpy as np

import torch
import torch.nn as nn
import torch.nn.functional as F
from torch.optim import SGD

class SoftmaxClassification(nn.Module):
    def __init__(self, n_features, n_classes):
        super(SoftmaxClassification, self).__init__()
        self.linear = nn.Linear(n_features, n_classes)

    def train(self, x, y, batch_size, epochs, lr, reg_lambda=0.1):
        '''
        ** Implement L2 regularization with reg_lambda **

        N : # of training data
        D : # of features
        C : # of classes

        Inputs:
        x : (N, D), input data
        y : (N, )
        batch_size : (int) # of minibatch size
        epochs : (int) # of training epoch to execute
        lr : (float), learning rate
        reg_lambda : (float), regularization strength

        Returns:
        None

        Description:
        Given training data, hyperparameters and optimizer, execute training procedure.
        Weight should be updated by minibatch (not the whole data at a time)
        The procedure for one epoch is as follows:
        - For each minibatch
            - Compute the probability of each class for data and the loss
            - Compute the gradient of weight
            - Update weight using optimizer

        * loss of one epoch = refer to the loss function in the instruction.
        '''
        self.optimizer = SGD(self.parameters(), lr=lr)
        num_data, _ = x.shape
        num_batches = int(np.ceil(num_data / batch_size))

        for epoch in range(1, epochs + 1):
            epoch_loss = 0.0

            for b in range(num_batches):
                ed = min(num_data, (b + 1) * batch_size)
                batch_x = x[b * batch_size: ed]
                batch_y = y[b * batch_size: ed]

                batch_x = torch.tensor(batch_x)
                batch_y = torch.tensor(batch_y).long().squeeze()


                # ========================= EDIT HERE =========================
                self.optimizer.zero_grad()
                pred = self.forward(batch_x)
                loss = F.cross_entropy(pred, batch_y) + reg_lambda*(self.linear.weight**2).sum()
                loss.backward()
                self.optimizer.step()

                # =============================================================
                
                
                epoch_loss += loss.item()
            
            if epoch % 500 == 0:
                print(f"[Epoch {epoch}] Total loss: {epoch_loss:.4f}")

    def forward(self, x, softmax=False):
        '''
        input: (N, D), N data with D features
        output: (N, C), N data with C classes (logits if softmax=False, probability if softmax=True)
        It is free to use softmax function or not.
        '''
        # ========================= EDIT HERE =========================
        if softmax == False:
            pred = self.linear(x)
        else :
            pred = F.softmax(self.linear(x))

        # =============================================================

        return pred

    def eval(self, x, y, batch_size):
        """
        Inputs:
        x : (N, D), input data

        Returns:
        pred : (N, ), predicted label for N test data

        Description:
        Given N test data, compute logits and make predictions for each data with the given threshold.
        """
        num_data, _ = x.shape
        num_batches = int(np.ceil(num_data / batch_size))

        preds = []
        for b in range(num_batches):
            ed = min(num_data, (b + 1) * batch_size)
            batch_x = x[b * batch_size: ed]

            batch_x = torch.tensor(batch_x)
            pred = self.forward(batch_x)

            preds.append(pred.argmax(dim=1))

        preds = torch.cat(preds)

        # ========================= EDIT HERE =========================
        acc = 0
        for i in range(0,num_data):
            if preds[i] == y[i]:
                acc+=1
        acc = acc / num_data
        # =============================================================

        return acc * 100, preds