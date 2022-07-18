import numpy as np
def binary_classification_metrics(prediction, ground_truth):
    '''
    Вычислите метрики для бинарной классификации

    Аргументы:
    prediction, np array of bool (num_samples) - предсказания модели
    ground_truth, np array of bool (num_samples) - эталонные значения

    Возвращает:
    precision, recall, f1, accuracy - метрики классификации
    '''
    precision = 0
    recall = 0
    accuracy = 0
    f1 = 0

    # TODO: реализуйте метрики!
    # Полезные источники:
    # https://en.wikipedia.org/wiki/Precision_and_recall
    # https://en.wikipedia.org/wiki/F1_score
    tp = np.count_nonzero(np.logical_and(prediction, ground_truth))
    fp = np.count_nonzero(np.logical_and(prediction, np.logical_not(ground_truth)))
    fn = np.count_nonzero(np.logical_and(np.logical_not(prediction), ground_truth))
    tn = np.count_nonzero(np.logical_and(np.logical_not(prediction), np.logical_not(ground_truth)))
    if (tp + fp) != 0:
        precision = tp / (tp + fp)
    if (tp + fn) != 0:
        recall = tp / (tp + fn)
    if (tp + tn + fp + fn) != 0:
        accuracy = (tp + tn) / (tp + tn + fp + fn)
    if (fp + fn) != 0:
        f1 = tp / (tp + 0.5 * (fp + fn))
    return precision, recall, f1, accuracy


def multiclass_accuracy(prediction, ground_truth):
    '''
    Вычислите метрики для мультиклассовой классификации

    Аргументы:
    prediction, np array of int (num_samples) - предсказания модели
    ground_truth, np array of int (num_samples) - эталонные значения

    Возвращает:
    accuracy - точность предсказаний
    '''
    # TODO: Реализуйте вычисление точности
    true_labels = 0
    prediction_size = prediction.shape[0]
    for i in range(prediction_size):
        if prediction[i] == ground_truth[i]:
            true_labels += 1
    accuracy = true_labels / prediction_size
    return accuracy
