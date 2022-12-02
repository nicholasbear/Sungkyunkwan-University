import random
import numpy as np
import pandas as pd


class BaggingSampler:
    def __init__(self, m, r):
        self.num_datasets = m
        self.sampling_ratio = r
        self.models = None

    def create_datasets(self, df):
        header = df.columns

        df_values = df.values
        datasets = []
        n_samples = np.round(len(df) * self.sampling_ratio)

        for _ in range(self.num_datasets):
            sampled_df = []
            # =============================== EDIT HERE ===============================
            for i in range(int(n_samples)):
                sampled_df.append(random.choice(df_values))
            #print(sampled_df)
            # =========================================================================

            datasets.append(pd.DataFrame(data=np.array(sampled_df), columns=header))
        #print(datasets[0])
        
        return datasets
