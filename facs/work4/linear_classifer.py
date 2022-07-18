import numpy as np


def softmax(predictions):
    '''
    Computes probabilities from scores

    Arguments:
      predictions, np array, shape is either (N) or (batch_size, N) -
        classifier output

    Returns:
      probs, np array of the same shape as predictions - 
        probability for every class, 0..1
    '''
    assert predictions.ndim == 1 or predictions.ndim == 2
    if predictions.ndim == 1:
        predictions_norm = predictions - np.max(predictions)
        probs = np.zeros_like(predictions_norm)
        probs = np.divide(np.exp(predictions_norm), np.sum(np.exp(predictions_norm)))
    elif predictions.ndim == 2:
        predictions_norm = predictions - np.max(predictions, axis=1)[:,None]
        probs = np.zeros_like(predictions_norm)
        probs = np.divide(np.exp(predictions_norm), np.sum(np.exp(predictions_norm), axis=1)[:,None])
    return probs


def cross_entropy_loss(probs, target_index):
    '''
    Computes cross-entropy loss

    Arguments:
      probs, np array, shape is either (N) or (batch_size, N) -
        probabilities for every class
      target_index: np array of int, shape is (1) or (batch_size) -
        index of the true class for given sample(s)

    Returns:
      loss: single value
    '''
    assert probs.ndim == 1 or probs.ndim == 2
    if probs.ndim == 1:
        loss = -np.log(probs[target_index])
    elif probs.ndim == 2:
        loss = -np.sum(np.log(np.take_along_axis(probs, target_index, 1)))
    return loss


def softmax_with_cross_entropy(predictions, target_index):
    '''
    Computes softmax and cross-entropy loss for model predictions,
    including the gradient

    Arguments:
      predictions, np array, shape is either (N) or (batch_size, N) -
        classifier output
      target_index: np array of int, shape is (1) or (batch_size) -
        index of the true class for given sample(s)

    Returns:
      loss, single value - cross-entropy loss
      dprediction, np array same shape as predictions - gradient of predictions by loss value
    '''
    assert predictions.ndim == 1 or predictions.ndim == 2
    probs = softmax(predictions)
    loss = cross_entropy_loss(probs, target_index)
    dprediction = probs
    if predictions.ndim == 1:
        dprediction[target_index] -= 1
    elif predictions.ndim == 2:
        np.put_along_axis(dprediction, target_index, np.take_along_axis(probs, target_index, 1) - 1, 1)
    return loss, dprediction


def l2_regularization(W, reg_strength):
    '''
    Computes L2 regularization loss on weights and its gradient

    Arguments:
      W, np array - weights
      reg_strength - float value

    Returns:
      loss, single value - l2 regularization loss
      gradient, np.array same shape as W - gradient of weight by l2 loss
    '''
    loss = reg_strength * np.sum(np.square(W))
    grad = reg_strength * 2 * W
    return loss, grad
    

def linear_softmax(X, W, target_index):
    '''
    Performs linear classification and returns loss and gradient over W

    Arguments:
      X, np array, shape (num_batch, num_features) - batch of images
      W, np array, shape (num_features, classes) - weights
      target_index, np array, shape (num_batch) - index of target classes

    Returns:
      loss, single value - cross-entropy loss
      gradient, np.array same shape as W - gradient of weight by loss

    '''
    predictions = np.dot(X, W)
    loss, grad = softmax_with_cross_entropy(predictions, target_index[:,np.newaxis])
    dW = np.dot(X.T, grad)
    
    return loss, dW


class LinearSoftmaxClassifier():
    def __init__(self):
        self.W = None

    def fit(self, X, y, batch_size=100, learning_rate=1e-7, reg=1e-5,
            epochs=1):
        '''
        Trains linear classifier
        
        Arguments:
          X, np array (num_samples, num_features) - training data
          y, np array of int (num_samples) - labels
          batch_size, int - batch size to use
          learning_rate, float - learning rate for gradient descent
          reg, float - L2 regularization strength
          epochs, int - number of epochs
        '''

        num_train = X.shape[0]
        num_features = X.shape[1]
        num_classes = np.max(y) + 1
        if self.W is None:
            self.W = 0.001 * np.random.randn(num_features, num_classes)

        loss_history = np.zeros(epochs)
        for epoch in range(epochs):
            shuffled_indices = np.arange(num_train)
            np.random.shuffle(shuffled_indices)
            sections = np.arange(batch_size, num_train, batch_size)
            batches_indices = np.array_split(shuffled_indices, sections)

            batches = np.take(X, batches_indices, axis=0)
            target_indx = np.take(y, batches_indices, axis=0)
            loss = np.zeros(batches.shape[0])
            grad = np.zeros([batches.shape[0], num_features, num_classes])
            loss_l2 = np.zeros(batches.shape[0])
            grad_l2 = np.zeros([batches.shape[0], num_features, num_classes])
            for i in range(batches.shape[0]):
                loss[i], grad[i] = linear_softmax(batches[i], self.W, target_indx[i])
                loss_l2[i], grad_l2[i] = l2_regularization(self.W, reg)
            grad_sum = np.sum(grad, axis=0) / batches.shape[0]
            grad_sum_l2 = np.sum(grad_l2, axis=0) / batches.shape[0]
            loss_sum = np.sum(loss, axis=0) / batches.shape[0] 
            self.W += -grad_sum * learning_rate - grad_sum_l2 * learning_rate
            
            # end
            loss_history[epoch] = loss_sum
        return loss_history

    def predict(self, X):
        '''
        Produces classifier predictions on the set
       
        Arguments:
          X, np array (test_samples, num_features)

        Returns:
          y_pred, np.array of int (test_samples)
        '''
        y_pred = np.zeros(X.shape[0], dtype=np.int)
        y_pred = np.argmax(np.dot(X, self.W), axis=1)
        
        return y_pred



                
                                                          

            

                
