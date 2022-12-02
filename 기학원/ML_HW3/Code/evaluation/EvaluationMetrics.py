class EvaluationMetric:
    def __init__(self, num_class, method='macro'):
        self.num_class = num_class
        self.method = method
        self.c_m_c = [{'TP': 0, 'FP': 0, 'FN': 0, 'TN': 0} for _ in range(self.num_class)] # confusion matrix for all class

    def _set_confusion_matrix(self, pred, true):
        """
        self.c_m_c is a list of confusion matrices, 
        and the n-th element(single dictionary) represents single confusion matrix for class n. 
        """
        # ========================= EDIT HERE =========================
        for class_num in range(self.num_class):
            for i in range(pred.shape[0]):
                if true[i] == pred[i]:
                    if pred[i] == class_num:
                        self.c_m_c[class_num]['TP'] +=1
                    else :
                        self.c_m_c[class_num]['TN'] +=1
                else :
                    if pred[i] == class_num:
                        self.c_m_c[class_num]['FP'] +=1
                    else :
                        self.c_m_c[class_num]['FN'] +=1


        # =============================================================

    def precision(self, TP, FP, FN, TN):
        # ========================= EDIT HERE =========================
        #print("TP is: ",TP)
        #print("FP is: ",FP)
        out = TP/(TP+FP)
       
        # =============================================================

        return out

    def recall(self, TP, FP, FN, TN):
        # ========================= EDIT HERE =========================
        out = TP/(TP+FN)
        # =============================================================
        return out

    def f_measure(self, precision, recall, beta=1.0):
        # ========================= EDIT HERE =========================
       
        out = (beta ** 2 + 1)*precision*recall / ((beta ** 2)*precision + recall)
        
        # =============================================================
        return out

    def multiclass_f_measure(self, pred, true):
        f_measure_, precision_, recall_ = [], [], []

        for class_idx in range(self.num_class):
            confusion_matrix_ = self.c_m_c[class_idx]
            
            precision = self.precision(confusion_matrix_['TP'], confusion_matrix_['FP'], confusion_matrix_['FN'], confusion_matrix_['TN'])
            recall = self.recall(confusion_matrix_['TP'], confusion_matrix_['FP'], confusion_matrix_['FN'], confusion_matrix_['TN'])

            f_measure_.append(self.f_measure(precision, recall))
            precision_.append(precision)
            recall_.append(recall)

        for class_idx in range(self.num_class):
            print(f'For class {class_idx}, precision: {precision_[class_idx]:.4f}\trecall: {recall_[class_idx]:.4f}\tf-measure: {f_measure_[class_idx]:.4f}')
        print()

        if self.method == 'macro':
            out = {'f_measure': 0.0, 'precision': 0.0, 'recall': 0.0}
        # ========================= EDIT HERE =========================
            f_m = sum(f_measure_)/self.num_class
            pre = sum(precision_)/self.num_class
            rec = sum(recall_)/self.num_class
            out['f_measure'] = f_m
            out['precision'] = pre
            out['recall'] = rec

        # =============================================================
        else:
            raise ValueError('Method should be macro.')

        return out
            
