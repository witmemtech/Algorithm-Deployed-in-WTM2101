import numpy as np
from dataset import SpeechCommandDataset
from torch.utils.data import DataLoader
from tqdm import tqdm
import torch

# import os
# os.environ['KMP_DUPLICATE_LIB_OK'] = 'True'


def gen_dnn_mapper_valid_data(val_file, save_path):
    test_dataset = SpeechCommandDataset(val_file[0], val_file[1], is_train = False)
    test_loader = DataLoader(dataset = test_dataset, batch_size= 1, shuffle = True)
    quant_data_npy = []
    c = 0
    neg = 0
    for data in tqdm(test_loader):
        inputs, labels = data
        # print(inputs)
        if int(labels) == torch.tensor([0]):
            neg += 1
        inputs = inputs.squeeze()
        inputs = np.array(inputs)
        quant_data_npy.append(inputs)
        c += 1
        if c == 100:
            break
    np.save(save_path, quant_data_npy)




if __name__ == "__main__":

    val_file = ["D:/code/speechcommand_demo_ver1.0/python/data/test_pos_temp.txt", "D:/code/speechcommand_demo_ver1.0/python/data/test_neg.txt"]

    gen_dnn_mapper_valid_data(val_file, 'test_data_0_100.npy')
