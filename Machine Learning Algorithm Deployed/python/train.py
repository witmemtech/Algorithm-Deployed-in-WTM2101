import os
import sys
import cv2
import random
import numpy as np
import torch
import torch.nn as nn
from tqdm import tqdm
from torch.utils.data import DataLoader, Dataset
from net import WitmemDemoNet

class DemoDataset(Dataset):
    def __init__(self, label_path):
        super(DemoDataset, self).__init__()
        with open(label_path,'r') as f:
            lines = f.readlines()
        self.label_list = []
        self.img_list = []
        for line in lines:
            line = line.strip().split()
            img_path = line[0]
            label = int(line[1])
            self.img_list.append(img_path)
            self.label_list.append(label)

    def __len__(self):
        return len(self.label_list)

    def _crop(self, image, cut_nums=2):
        h, w = image.shape
        img_patch_list = []
        edge_len = int(h / cut_nums)
        for i in range(cut_nums):
            img_patch = image[edge_len*i:edge_len*(i+1), ...]
            img_patch = torch.Tensor(img_patch.reshape(1,-1))
            img_patch_list.append(img_patch)
        return torch.cat(img_patch_list,dim=0)

    def __getitem__(self, index):
        '''
        mnist gray image shape is [28,28]
        '''
        img = cv2.imread(self.img_list[index], cv2.IMREAD_GRAYSCALE)
        img = img/255.0
        data = self._crop(img, cut_nums=2)
        label = self.label_list[index]
        return data, label

def setRandomSeed(seed):
    random.seed(seed)
    os.environ['PYTHONHASHSEED'] = str(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)

if __name__ == "__main__":

    setRandomSeed(20240629)

    train_dataset = DemoDataset(label_path="label/mnist_train.txt")
    test_dataset = DemoDataset(label_path="label/mnist_val.txt")

    train_loader = DataLoader(dataset = train_dataset, batch_size = 64, shuffle = True)
    test_loader = DataLoader(dataset = test_dataset, batch_size= 64, shuffle = False )

    model = WitmemDemoNet()

    loss_func = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=5e-4)

    print("model start train")
    for epoch in range(2):
        ## model train
        model.train()
        sum_loss = 0.0
        train_correct = 0
        print("\n\n********* train *********  epoch:", str(epoch))
        for batch, (inputs, labels) in enumerate(tqdm(train_loader)):
            
            outputs = model(inputs)
            outputs = outputs.squeeze()
            loss = loss_func(outputs, labels)

            optimizer.zero_grad()
            loss.backward()
            optimizer.step()
            
            _, id = torch.max(outputs.data, 1)
            sum_loss += loss.data
            train_correct += torch.sum(id == labels.data)

        print('train loss:%.03f' % (sum_loss / len(train_loader)))
        print('train correct:%.03f%%' % (100 * train_correct / len(train_dataset)))

        ## model val
        model.eval()
        test_correct = 0
        print("********* val *********  epoch", str(epoch))
        for data in tqdm(test_loader):
            inputs, labels = data
            outputs = model(inputs)
            outputs = outputs.squeeze()
            _, id = torch.max(outputs.data, 1)
            test_correct += torch.sum(id == labels.data)
        eval_correct_ratio = 100 * test_correct / len(test_dataset)
        print("val correct:%.3f%%" % (100 * test_correct / len(test_dataset)))

    if not os.path.exists('models/'):
        os.makedirs('models/')
    torch.save(model.state_dict(), "models/bestModel.pth")

    print("---train finished---")