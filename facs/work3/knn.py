import numpy as np


class KNN:
    """
    Классификатор K-ближайших-соседей на основе метрики L1
    """
    def __init__(self, k=1):
        self.k = k

    def fit(self, X, y):
        self.train_X = X
        self.train_y = y

    def predict(self, X, num_loops=0):
        '''
        Использует модель KNN для предсказания классов принятого набора данных
        
        Аргументы:
        X, np array (num_samples, num_features) - набор данных для предсказания
        num_loops, int - какую вариацию расчета расстояний использовать

        Возвращает:
        predictions, np array of ints (num_samples) - предсказания классов для
            набора данных
        '''
        if num_loops == 0:
            dists = self.compute_distances_no_loops(X)
        elif num_loops == 1:
            dists = self.compute_distances_one_loop(X)
        else:
            dists = self.compute_distances_two_loops(X)

        if self.train_y.dtype == np.bool:
            return self.predict_labels_binary(dists)
        else:
            return self.predict_labels_multiclass(dists)

    def compute_distances_two_loops(self, X):
        '''
        Вычисляет расстояния L1 от каждой выборки X до каждой тренировочной выборки
        Использует простейшую реализацию с двумя циклами

        Аргументы:
        X, np array (num_test_samples, num_features) - выборки данных
        
        Возвращает:
        dists, np array (num_test_samples, num_train_samples) - массив
           расстояний между каждой тестовой и тренировочной выборкой
        '''

        num_train = self.train_X.shape[0]
        num_test = X.shape[0]
        dists = np.zeros((num_test, num_train), np.float32)
        for i_test in range(num_test):
            for i_train in range(num_train):
                dists[i_test][i_train] = np.sum(np.fabs(self.train_X[i_train] - X[i_test]))
        return dists

    def compute_distances_one_loop(self, X):
        '''
        Вычисляет расстояния L1 от каждой выборки X до каждой тренировочной выборки
        Одно из вычислений производится в виде вектора, поэтому только 1 цикл используется

        Аргументы:
        X, np array (num_test_samples, num_features) - выборки данных
        
        Возвращает:
        dists, np array (num_test_samples, num_train_samples) - массив
           расстояний между каждой тестовой и тренировочной выборкой
        '''
        num_train = self.train_X.shape[0]
        num_test = X.shape[0]
        dists = np.zeros((num_test, num_train), np.float32)
        for i_test in range(num_test):
            dists[i_test] = np.sum(np.fabs(self.train_X - X[i_test, :]), axis=1)
        return dists

    def compute_distances_no_loops(self, X):
        '''
        Вычисляет расстояния L1 от каждой выборки X до каждой тренировочной выборки
        Полностью векторные вычисления используя numpy, без циклов

        Аргументы:
        X, np array (num_test_samples, num_features) - выборки данных
        
        Возвращает:
        dists, np array (num_test_samples, num_train_samples) - массив
           расстояний между каждой тестовой и тренировочной выборкой
        '''
        num_train = self.train_X.shape[0]
        num_test = X.shape[0]
        # Используется float32, для сохранения в память - по умолчанию используется float64
        dists = np.zeros((num_test, num_train), np.float32)
        dists = abs(X[:,None] - self.train_X).sum(axis=2)
        return dists

    def predict_labels_binary(self, dists):
        '''
        Возвращает предсказания модели для случая бинарной классификации
        
        Аргументы:
        dists, np array (num_test_samples, num_train_samples) - массив
           расстояний между каждой тестовой и тренировочной выборкой

        Возвращает:
        pred, np array of bool (num_test_samples) - бинарные предсказания
            для каждой тестовой выборки
        '''
        num_test = dists.shape[0]
        pred = np.zeros(num_test, np.bool)
        for i in range(num_test):
            min_dist = np.argpartition(-1 * dists[i], kth=self.k)
            if np.sum(self.train_y[min_dist[:self.k]]) >= (self.k / 2):
                pred[i] = True
            else:
                pred[i] = False
        return pred

    def predict_labels_multiclass(self, dists):
        '''
        Возвращает предсказания модели для случая мультиклассовой классификации
        
        Аргументы:
        dists, np array (num_test_samples, num_train_samples) - массив
           расстояний между каждой тестовой и тренировочной выборкой

        Возвращает:
        pred, np array of int (num_test_samples) - предсказания
            для каждой тестовой выборки
        '''
        num_test = dists.shape[0]
        pred = np.zeros(num_test, np.int)
        for i in range(num_test):
            index_k_nearest_x = np.argsort(dists[i])[:self.k]
            k_nearest_x_y = [self.train_y[x] for x in index_k_nearest_x]
            pred[i] = max(set(k_nearest_x_y), key=k_nearest_x_y.count)
        return pred
