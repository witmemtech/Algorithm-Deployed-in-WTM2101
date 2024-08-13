from torch.utils.data import Dataset
from utils.feature_tools import get_fbank
import numpy as np
import random
from torch.utils.data import DataLoader
import scipy.io.wavfile as wav
import torch
    
class SpeechCommandDataset(Dataset):
    def __init__(self, pos_path, neg_path, is_train = True):
        super(SpeechCommandDataset, self).__init__()
        self.is_train = is_train
        with open(pos_path,'r', encoding="utf-8") as f:
            pos_lines = f.readlines()
        with open(neg_path,'r', encoding="utf-8") as f:
            neg_lines = f.readlines()
        self.pos_data_list = []
        self.pos_label_list = []
        self.neg_data_list = []
        self.neg_label_list = []
        for line in pos_lines:
            if line.strip().split(' ')[0].endswith('wav'):
                self.pos_data_list.append(line.strip().split(' ')[0])
                self.pos_label_list.append(line.strip().split(' ')[1])
        for line in neg_lines:
            if line.strip().split(' ')[0].endswith('wav'):
                self.neg_data_list.append(line.strip().split(' ')[0])
                self.neg_label_list.append(line.strip().split(' ')[1])

    def run_one_wav(self, waveform):
        fbank = get_fbank(waveform)
        fbank = np.array(fbank,dtype=np.uint8)
        fbank = fbank.tolist()        
        return fbank
    
    def __len__(self):
        return len(self.pos_label_list)*2

    def __getitem__(self, index):
        if index < len(self.pos_label_list):
            wav_path = self.pos_data_list[index]
            label = int(self.pos_label_list[index])

            fs, waveform = wav.read(wav_path)
            while(waveform.shape[0] < 16000):
                ind = random.randint(0, len(self.pos_label_list) - 1)
                fs, waveform = wav.read(self.pos_data_list[ind])

            random_ratio = random.uniform(0.7, 0.75)
            clip_left = int(np.round((waveform.shape[0] - 16000)*random_ratio))
        else:
            index = index % len(self.neg_label_list)
            wav_path = self.neg_data_list[index]
            label = int(self.neg_label_list[index])
            
            fs, waveform = wav.read(wav_path)           
            while(waveform.shape[0] < 16000):
                ind = random.randint(0, len(self.neg_label_list) - 1)
                fs, waveform = wav.read(self.neg_data_list[ind])
            if self.is_train:
                clip_left = random.randint(0, waveform.shape[0] - 16000)    
            else:
                clip_left = waveform.shape[0] - 16000     

        waveform = waveform[clip_left : clip_left + 16000]
        input = self.run_one_wav(waveform)
        input = input[:20]
        input = np.array(input)
        input = np.reshape(input, newshape = (1, input.shape[0] * input.shape[1]))
        input = torch.tensor(input, dtype=torch.float32)
       
        return input, label#, wav_path

class SpeechCommand_uart_Dataset(Dataset):
    def __init__(self, pos_path, neg_path, is_train = True):
        super(SpeechCommand_uart_Dataset, self).__init__()
        self.is_train = is_train
        with open(pos_path,'r', encoding="utf-8") as f:
            pos_lines = f.readlines()
        with open(neg_path,'r', encoding="utf-8") as f:
            neg_lines = f.readlines()
        self.pos_data_list = []
        self.pos_label_list = []
        self.neg_data_list = []
        self.neg_label_list = []
        for line in pos_lines:
            if line.strip().split(' ')[0].endswith('wav'):
                self.pos_data_list.append(line.strip().split(' ')[0])
                self.pos_label_list.append(line.strip().split(' ')[1])
        for line in neg_lines:
            if line.strip().split(' ')[0].endswith('wav'):
                self.neg_data_list.append(line.strip().split(' ')[0])
                self.neg_label_list.append(line.strip().split(' ')[1])

    def run_one_wav(self, waveform):
        fbank = get_fbank(waveform)
        fbank = np.array(fbank,dtype=np.uint8)
        fbank = fbank.tolist()        
        return fbank
    
    def __len__(self):
        return len(self.pos_label_list)*2

    def __getitem__(self, index):
        
        if index < len(self.pos_label_list):
            wav_path = self.pos_data_list[index]
            label = int(self.pos_label_list[index])

            fs, waveform = wav.read(wav_path)
            while(waveform.shape[0] < 16000):
                ind = random.randint(0, len(self.pos_label_list) - 1)
                fs, waveform = wav.read(self.pos_data_list[ind])

            random_ratio = random.uniform(0.7, 0.75)
            clip_left = int(np.round((waveform.shape[0] - 16000)*random_ratio))
        else:
            index = index % len(self.neg_label_list)
            wav_path = self.neg_data_list[index]
            if wav_path == 'D:/code/speechcommand_demo_ver1.0/python/data/background/wav/free-sound/noise-free-sound-0745.wav':
                stop = 1
            stop = 1
            label = int(self.neg_label_list[index])
            
            fs, waveform = wav.read(wav_path)           
            while(waveform.shape[0] < 16000):
                ind = random.randint(0, len(self.neg_label_list) - 1)
                fs, waveform = wav.read(self.neg_data_list[ind])
                clip_left = waveform.shape[0] - 16000     
            clip_left = waveform.shape[0] - 16000    
        waveform = waveform[clip_left : clip_left + 16000]
        # input = self.run_one_wav(waveform)
        # input = input[:20]
        # input = np.array(input)
        # input = np.reshape(input, newshape = (1, input.shape[0] * input.shape[1]))
        # input = torch.tensor(input, dtype=torch.float32)
        input = torch.tensor(waveform)
       
        return input, label#, wav_path
    
class SpeechCommand_gru_Dataset(Dataset):
    def __init__(self, pos_path, neg_path, is_train = True):
        super(SpeechCommand_gru_Dataset, self).__init__()
        self.is_train = is_train
        with open(pos_path,'r', encoding="utf-8") as f:
            pos_lines = f.readlines()
        with open(neg_path,'r', encoding="utf-8") as f:
            neg_lines = f.readlines()
        self.pos_data_list = []
        self.pos_label_list = []
        self.neg_data_list = []
        self.neg_label_list = []
        for line in pos_lines:
            if line.strip().split(' ')[0].endswith('wav'):
                self.pos_data_list.append(line.strip().split(' ')[0])
                self.pos_label_list.append(line.strip().split(' ')[1])
        for line in neg_lines:
            if line.strip().split(' ')[0].endswith('wav'):
                self.neg_data_list.append(line.strip().split(' ')[0])
                self.neg_label_list.append(line.strip().split(' ')[1])

    def run_one_wav(self, waveform):
        fbank = get_fbank(waveform)
        fbank = np.array(fbank,dtype=np.uint8)
        fbank = fbank.tolist()        
        return fbank
    
    def __len__(self):
        return len(self.pos_label_list)*2

    def __getitem__(self, index):
        if index < len(self.pos_label_list):
            wav_path = self.pos_data_list[index]
            label = int(self.pos_label_list[index])

            fs, waveform = wav.read(wav_path)
            while(waveform.shape[0] < 16000):
                ind = random.randint(0, len(self.pos_label_list) - 1)
                fs, waveform = wav.read(self.pos_data_list[ind])

            random_ratio = random.uniform(0.7, 0.75)
            clip_left = int(np.round((waveform.shape[0] - 16000)*random_ratio))
        else:
            index = index % len(self.neg_label_list)
            wav_path = self.neg_data_list[index]
            label = int(self.neg_label_list[index])
            
            fs, waveform = wav.read(wav_path)           
            while(waveform.shape[0] < 16000):
                ind = random.randint(0, len(self.neg_label_list) - 1)
                fs, waveform = wav.read(self.neg_data_list[ind])
            if self.is_train:
                clip_left = random.randint(0, waveform.shape[0] - 16000)    
            else:
                clip_left = waveform.shape[0] - 16000     

        waveform = waveform[clip_left : clip_left + 16000]
        input = self.run_one_wav(waveform)
        input = input[:20]
        input = np.array(input)
        # input = np.reshape(input, newshape = (1, input.shape[0] * input.shape[1]))
        input = torch.tensor(input, dtype=torch.float32)
       
        return input, label#, wav_path
if __name__ == '__main__':
    train_dataset = SpeechCommandDataset(pos_path = "D:/code/speechcommand_demo_ver1.0/python/data/train_pos.txt", neg_path = "D:/code/speechcommand_demo_ver1.0/python/data/train_neg.txt")
    train_loader = DataLoader(dataset = train_dataset, batch_size = 1, shuffle = True)
    # for batch, (inputs, labels, path) in enumerate(tqdm(train_loader)):
    #     print(path, inputs.shape)

    neg = 0
    pos = 0
    for input, label in train_loader:
        # print(input)
        if label == 0:
            neg += 1
        else:
            pos += 1
        # if len(input) != 21:
        #     c += 1
        # if c % 1000 == 0:
        #     print(c, total)
        print(neg, pos)