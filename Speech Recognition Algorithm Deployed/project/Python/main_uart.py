import numpy as np
import os
import sys
import time
from serial_com import open_serial,send_start,send_and_get_msg
import scipy.io.wavfile as wav
import math

def initUart():
    open_serial("COM13", 115200, 10)
    time.sleep(1)
    res = send_start()
    time.sleep(1)
    return res

def readWav(wav_path):
    fs, audio = wav.read(wav_path)
    return audio

if __name__ == "__main__":
    
    if initUart() == False:
        raise ValueError("UART INIT ERROR")
   
    wav_path = "./test2.wav"
    wav_data = readWav(wav_path)
    start_idx = 3000
    wav_data = wav_data[start_idx:start_idx+16000]
    # wav.write("output.wav", 16000, wav_data)

    output_list = []
    for i in range(100):
        input_data = wav_data[i*160:(i+1)*160]
        # print(input_data)
        output = send_and_get_msg(input_data, send_int16=True, receive_int16=False)
        if(output[0]==-128 and output[1]==-128):
            continue
        print("output",i,"   ",output)
        output_list.append(output)
    
    print("OK")