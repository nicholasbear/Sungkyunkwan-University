import torch
import numpy as np
from torch.optim import SGD

class PolynomialRegression:
    def __init__(self, degree):
        self.degree = degree
        self.W = torch.zeros((self.degree + 1, 1), requires_grad=True)

    def train(self, x, y, batch_size, epochs, lr):
        """
        N : # of training data
        D : # of features
        C : # of classes

        Inputs:
        x : (N, 1), input data
        y : (N, )
        batch_size : (int) # of minibatch size
        epochs : (int) # of training epoch to execute
        lr : (float), learning rate

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
        """

        self.optimizer = SGD([self.W], lr=lr)
        num_data, _ = x.shape
        num_batches = int(np.ceil(num_data / batch_size))
        
        x = self.PolynomialFeatures(x)
        
        for epoch in range(1, epochs + 1):
            epoch_loss = 0.0
            
            for b in range(num_batches):
                ed = min(num_data, (b + 1) * batch_size)
                batch_x = x[b * batch_size: ed]
                batch_y = y[b * batch_size: ed]

                batch_x = torch.tensor(batch_x)
                batch_y = torch.tensor(batch_y)

                pred = self.forward(batch_x)
                
                # ========================= EDIT HERE =========================
                self.optimizer.zero_grad()
                n, _ = batch_x.shape
                mse_loss = 1/(2*n) * ((batch_y - pred) ** 2).sum()
                mse_loss.backward()
                self.optimizer.step()

                # =============================================================
                
                epoch_loss += mse_loss.item()

            if epoch % 20000 == 0:
                print(f'[Epoch {epoch}] Total loss = {epoch_loss:.4f}')

    def PolynomialFeatures(self, x):
        """
        Convert input data x to polynomial features
        Inputs:
        x : (N, 1), input data

        Outputs:
        features : (N, degree + 1), polynomial features + bias

        """

        # ========================= EDIT HERE =========================

        row, col = x.shape
        features = np.zeros((row,self.degree + 1))
        
        for i in range(0,row):
            for j in range(0,self.degree + 1):
                features[i][j] = np.power(x[i],j)
        features = features.astype(np.float32)
        # =============================================================
        
        return features

    def forward(self, x):
        
        return torch.matmul(x, self.W)

    def eval(self, x, y, batch_size):
        """
        Inputs:
        x : (N, D), input data

        Returns:
        rmse : (float), root mean squared error

        Description:
        Given N test data, compute the root mean squared error for the test data.
        """

        num_data, _ = x.shape
        num_batches = int(np.ceil(num_data / batch_size))
        
        x = self.PolynomialFeatures(x)
        
        pred = np.zeros((num_data, 1))
        
        for b in range(num_batches):
            ed = min(num_data, (b + 1) * batch_size)
            batch_x = x[b * batch_size: ed]
            batch_x = torch.tensor(batch_x)
            pred[b * batch_size: ed] = self.forward(batch_x).detach().numpy()

        rmse = np.sqrt(np.mean((y - pred)**2))
        return rmse