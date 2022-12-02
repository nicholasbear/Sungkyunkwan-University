import numpy as np


class LinearRegression:
    def __init__(self, num_features):
        self.num_features = num_features
        self.W = np.zeros((self.num_features+1, 1))

    def numerical_solution(self, x, y, epochs, batch_size, lr, optim, batch_gradient=False):

        """
        The numerical solution of Linear Regression
        Train the model for 'epochs' times with minibatch size of 'batch_size' using gradient descent.
        (TIP : if the dataset size is 10, and the minibatch size is set to 3, corresponding minibatch size should be 3, 3, 3, 1)

        [Inputs]
            x : input for linear regression. Numpy array of (N, D)
            y : label of data x. Numpy array of (N, )
            epochs : epochs.
            batch_size : size of the batch.
            lr : learning rate.
            optim : optimizer. (fixed to 'stochastic gradient descent' for this assignment.)

        [Output]
            None

        """
        x_new = self.add_bias(x)

        self.W = self.W.reshape(-1)
        num_data = len(x)
        num_batch = int(np.ceil(num_data / batch_size))

        for epoch in range(epochs):
            if batch_gradient:
                # batch gradient descent

                # ========================= EDIT HERE ========================      
                y_hat = x_new @ self.W
                y_new = (y - y_hat) ** 2
                loss_vector = (1/(2*num_data)) * y_new.sum()
                grad = -(1/num_data)* x_new.T @ (y - y_hat)
                # ============================================================

                self.W = optim.update(self.W, grad, lr)
            else:
                # mini-batch stochastic gradient descent
                for batch_index in range(num_batch):
                    batch_x = x_new[batch_index*batch_size:(batch_index+1)*batch_size]
                    batch_y = y[batch_index*batch_size:(batch_index+1)*batch_size]

                    num_samples_in_batch = len(batch_x)

                    # ========================= EDIT HERE ========================
                    y_hat = batch_x @ self.W
                    y_new = (batch_y - y_hat) ** 2
                    loss_vector = 1/(2*num_samples_in_batch) * ((batch_y - y_new)).sum()
                    grad = -(1/num_samples_in_batch)* batch_x.T @ (batch_y - y_hat)
                    # ============================================================

                    self.W = optim.update(self.W, grad, lr)

    def analytic_solution(self, x, y):
        """
        The analytic solution of Linear Regression
        Train the model using the analytic solution.

        [Inputs]
            x : input for linear regression. Numpy array of (N, D)
            y : label of data x. Numpy array of (N, )

        [Output]
            None

        [Hints]
            1. Use np.transpose for transposing a matrix.
            2. Use np.linalg.inv for making a inverse matrix.
            3. Use np.dot for performing a dot product between two matrices.
        """
        x_new = self.add_bias(x)
        
        # ========================= EDIT HERE ========================
        
        self.W = np.linalg.inv(x_new.T @ x_new) @ x_new.T @ y
        # ============================================================
    
    def add_bias(self, x):
        # ========================= EDIT HERE ========================
        # You should add column of ones for bias after the last column of x
        row , col = x.shape
        bias = np.ones(row)
        x_new = np.c_[x,bias]
        # ========================= EDIT HERE ========================

        return x_new

    def eval(self, x):
        """
        Evaluation Function
        [Input]
            x : input for linear regression. Numpy array of (N, D)

        [Outputs]
            pred : prediction for 'x'. Numpy array of (N, )
        """
        x_new = self.add_bias(x)

        pred = np.dot(x_new, self.W)

        return pred
