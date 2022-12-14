import numpy as np


class SoftmaxClassifier:
    def __init__(self, num_features, num_label):
        self.num_features = num_features
        self.num_label = num_label
        self.W = np.zeros((self.num_features, self.num_label))

    def train(self, x, y, epochs, batch_size, lr, optimizer):
        """
        N : # of training data
        D : # of features
        C : # of classes

        Inputs:
        x : (N, D), input data
        y : (N, ), label
        epochs : (int), # of training epoch to execute
        batch_size : (int), # of minibatch size
        lr : (float), learning rate
        optimizer : (Class), optimizer to use

        Returns:
        None

        Description:
        Given training data, hyperparameters and optimizer, execute training procedure.
        Weight should be updated by minibatch (not the whole data at a time)

        The procedure for one epoch is as follows:
        - For each minibatch
            - Compute the probability of each class for data and softmax loss
            - Compute the gradient of weight
            - Update weight using optimizer

        * loss of one epoch = refer to the loss function in the instruction.
        """

        num_data, num_feat = x.shape
        num_batches = int(np.ceil(num_data / batch_size))

        for epoch in range(1, epochs + 1):
            epoch_loss = 0.0
            
            for b in range(num_batches):
                ed = min(num_data, (b + 1) * batch_size)
                batch_x = x[b * batch_size: ed]
                batch_y = y[b * batch_size: ed]
                
                prob, softmax_loss = self.forward(batch_x, batch_y)

                grad = self.compute_grad(batch_x, batch_y, self.W, prob)

                self.W = optimizer.update(self.W, grad, lr)

                epoch_loss += softmax_loss
                

    def forward(self, x, y):
        """
        N : # of minibatch data
        D : # of features

        Inputs:
        x : (N, D), input data 
        y : (N, ), label

        Returns:
        prob: (N, C), probability distribution over classes for N data
        softmax_loss : (float), softmax loss for N input

        Description:
        Given N data and their labels, compute softmax probability distribution and loss.
        """

        num_data, num_feat = x.shape
        _, num_label = self.W.shape
        
        prob = None
        softmax_loss = 0.0

        # ========================= EDIT HERE ========================
        prob = x@self.W
        y_hat = self._softmax(prob)
        y_hat = np.log(y_hat)
        for i in range(0,num_data):
            target = y[i]
            for j in range(0,num_label):
                if j != target:
                    y_hat[i][j] = 0

        softmax_loss = -1/num_data * (y_hat).sum()

        # ============================================================

        return prob, softmax_loss

    def compute_grad(self, x, y, weight, prob):
        """
        N : # of minibatch data
        D : # of features
        C : # of classes

        Inputs:
        x : (N, D), input data
        y : (N, ), label for each data. (0 <= c < C for c in label)
        weight : (D, C), Weight matrix of classifier
        prob : (N, C), a probability distribution over classes for N data

        Returns:
        the gradient of weight: (D, C), Gradient of weight to be applied (dL/dW)

        Description:
        Given input (x), weight, probability, and label, compute the gradient of weight.
        """

        num_data, num_feat = x.shape
        _, num_classes = weight.shape

        grad_weight = np.zeros_like(weight)
        
        for j in range(num_data):
            xx = x[j, :]

            # ========================= EDIT HERE ========================
            h = self._softmax(prob)
            for i in range(0,num_data):
                target = y[i]
                h[i][target] -= 1
            grad_weight = x.T@h
            # ============================================================

        grad_weight /= num_data

        return grad_weight

    def _softmax(self, x):
        """
        Inputs:
        x : (N, C), score before softmax

        Returns:
        softmax : (same shape with x), softmax distribution over axis 1

        Description:
        Given an input x, apply softmax funciton over axis 1.
        """

        softmax = None

        # ========================= EDIT HERE ========================
        max = np.max(x,axis=1,keepdims=True)
        e_x = np.exp(x - max)
        sum = np.sum(e_x,axis=1,keepdims=True)
        softmax = e_x / sum 


        # ============================================================

        return softmax
    
    def eval(self, x):
        """
        Inputs:
        x : (N, D), input data

        Returns:
        pred : (N, ), predicted label for N test data
        prob : (N, C), predicted logit for N test data

        Description:
        Given N test data, compute the probability and make predictions for each data.
        """

        pred = None
        prob = None

        # ========================= EDIT HERE ========================
        prob = x@self.W
        pred = np.argmax(prob, axis = 1)

        # ============================================================

        return pred, prob