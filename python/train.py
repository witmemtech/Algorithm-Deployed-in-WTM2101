import os
import random
from tqdm import tqdm
import numpy as np
import torch
import torch.nn as nn
from torch.utils.data import DataLoader
import torch.optim as optim
from torch.optim.lr_scheduler import MultiStepLR
import torch.optim.lr_scheduler as lr_scheduler

from net.net_dnn import DnnNet, DnnNetDeep
from dataset import SpeechCommandDataset
from config import witin_config

# os.environ['KMP_DUPLICATE_LIB_OK'] = 'True'
    
def train_main(net_type, train_epoch, lr, batch_size, data_len = None, train_file = [None, None], val_file = [None, None]):
    if net_type == 'DNN':
        model = DnnNet(data_len = data_len)
    elif net_type == 'DNN_DEEP':
        model = DnnNetDeep(data_len = data_len)
    else:
        raise NameError  
    train_dataset = SpeechCommandDataset(train_file[0], train_file[1], is_train = True)
    test_dataset = SpeechCommandDataset(val_file[0], val_file[1], is_train = False)
    train_loader = DataLoader(dataset = train_dataset, batch_size = batch_size, shuffle = True)
    test_loader = DataLoader(dataset = test_dataset, batch_size= batch_size, shuffle = False)

    loss_func = nn.CrossEntropyLoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=lr)
    scheduler = lr_scheduler.StepLR(optimizer, step_size=1, gamma=0.9)

    print("model start train")
    max_eval_correct_ratio = -1
    for epoch in range(train_epoch):
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
            
            ## 权重范围约束, 约束至[-0.125, 0.125]
            for p in model.parameters():
                p.data.clamp_(-0.125, 0.125)

            _, id = torch.max(outputs.data, 1)
            sum_loss += loss.data
            train_correct += torch.sum(id == labels.data)

        print('[%d,%d] loss:%.03f' % (epoch + 1, train_epoch, sum_loss / (batch*batch_size)))
        print('train correct:%.03f%%' % (100 * train_correct / (batch*batch_size)))
        print('lr:%.06f%%' % (scheduler.get_lr()[0]))

        ## model val
        model.eval()
        test_correct = 0
        test_quant_correct = 0
        print("********* val *********  epoch", str(epoch))
        for data in tqdm(test_loader):
            inputs, labels = data
            outputs = model(inputs)
            outputs = outputs.squeeze()

            outputs_quant = model.forward_quant(inputs)
            # outputs_quant = outputs_quant.squeeze()

            _, id = torch.max(outputs.data, 1)
            # _, id_quant = torch.max(outputs_quant.data, 1)
            test_correct += torch.sum(id == labels.data)
            # test_quant_correct += torch.sum(id_quant == labels.data)
        eval_correct_ratio = 100 * test_correct / len(test_dataset)
        print("val correct:%.3f%%" % (100 * test_correct / len(test_dataset)))
        # print("val quant correct:%.3f%%" % (100 * test_quant_correct / len(test_dataset)))

        # model save
        if max_eval_correct_ratio < eval_correct_ratio:
            max_eval_correct_ratio = eval_correct_ratio
            if not os.path.exists('models/'+net_type):
                os.makedirs('models/'+net_type)
            torch.save(model.state_dict(), 'models/'+net_type+"/bestModel.pth")
            print(epoch,"-- Best model success ratio:",max_eval_correct_ratio)
        torch.save(model.state_dict(), 'models/'+net_type+"/"+str(epoch)+'_'+str(eval_correct_ratio)+".pth")            
        
        scheduler.step()
    print("---train finished---")

def setRandomSeed(seed):
    random.seed(seed)
    os.environ['PYTHONHASHSEED'] = str(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)

if __name__ == "__main__":
    setRandomSeed(witin_config['train_seed'])
    train_epoch = witin_config['epoch']
    lr = witin_config['lr']
    batch = witin_config['batch_size']
    net_type = witin_config['net_type']  

    train_file = ["data/train_pos_mini.txt", "data/train_neg.txt"]
    val_file = ["data/test_pos.txt", "data/test_neg.txt"]
    train_main(net_type, train_epoch, lr, batch, data_len=20*40, train_file = train_file, val_file = val_file)
    
    