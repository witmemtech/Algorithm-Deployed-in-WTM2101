
import serial
import string
import binascii
import os
import time
import wave
import struct
import copy
import serial.tools.list_ports
import sys
import json
import getopt

import numpy as np
#from utils import *

#from nnet import nnet_init,nnet_run_all,logsoftmax
#import config as cfg
#from decoder import decoder_init,decode_nnet_frm,decode_when_final,get_key_words

ser_com = None
#global ser_com


def open_serial(uart_port_name, uart_baud_rate, time_out):
    global ser_com
    ser_com = None
    ser_com = serial.Serial()
    ser_com.port=uart_port_name
    ser_com.baudrate = uart_baud_rate   #设置波特率
    ser_com.bytesize = 8        #设置数据位
    ser_com.stopbits = 1        #设置停止位
    ser_com.parity = "N"        #设置校验位
    # ser_com.set_buffer_size(tx_size=1024,rx_size=1024)
    ser_com.timeout=time_out
    #ser_com.timeout=0.5
    ser_com.open()              #打开串口,要找到对的串口号才会成功
    if(ser_com.isOpen()):
        print("%s 串口打开成功" %(uart_port_name))
    else:
        print("%s 串口打开失败" %(uart_port_name))
        exit()
    #return ser_com

def send_start():
    global ser_com
    if ser_com is None:
        print("ERR: serial is not open")
        exit(1)
    ser_com.write(b'\xcc')
    #time.sleep(0.5)
    ack=ser_com.read(1)
    if len(ack) == 0:
        print("slaver not give ack quickly,wait for 0.5S and check again")
        time.sleep(0.5)
        ack=ser_com.read(1)
        if len(ack) == 0:
            print("slaver not give ack after 0.5S!!! is slaver run OK????")
            return False
    if(ack[0] == 0xcd):
        print("slaver return OK!!")
        return True
    else:
        print("slaver not return 0xcd,but return ",ack[0])
        return False

def send_end():
    global ser_com
    if ser_com is None:
        print("ERR: serial is not open")
        exit(1)
    ser_com.write(b'\xdd')

    ack = ser_com.read(1)
    print(ack)
    if len(ack) == 0:
        print("slaver not give ack quickly,wait for 0.5S and check again")
        time.sleep(0.5)
        ack=ser_com.read(1)
        if len(ack) == 0:
            print("slaver not give ack after 0.5S!!! is slaver run OK????")
            return False
    if(ack[0] == 0xde):
        print("slaver return 0xde, OK!!",ack[0])
        return True

def send_end_msg():
    send_typ = b"bye_"
    send_len =b'\x00\x00\x00\x01'
    b = bytes(8)
    send_msg_pack(send_typ, send_len, b)
    time.sleep(0.5)

def caculateCheckValue(data):
    sum = 0
    for item in data:
        sum = sum +item
    return sum

def receive_feedback():
    typ,lenth,data,status = recv_msg_pack()
    if typ == b'f_bk':
        feedback = struct.unpack('<L', bytes(data))[0]
        if feedback == 1000:
            return  False
        elif feedback == 7000:
            return  True
    return False


def send_msg_pack_with_repeat(btype, blen, bdata,repeat_time=10):
    reSendCount = repeat_time
    while reSendCount > 0:
        send_msg_pack(btype, blen, bdata)
        if receive_feedback():
            return True
        else:
            reSendCount = reSendCount -1
    return False

def send_msg_pack(btype, blen, bdata):
    global ser_com
    if ser_com is None:
        print("ERR: serial is not open")
        exit(1)
    #print("-------------- send msg!!",btype,blen)
    ser_com.write(btype)
    ser_com.write(blen)
    ser_com.write(bdata)
    checksum=caculateCheckValue(bdata).to_bytes(4,"little")
    # print("checksum:",checksum)
    ser_com.write(checksum)

    
def send_feedback(isOk):
    value = 1000;
    if isOk > 0:
        value = 7000
    send_len = b'\x00\x00\x00\x04'
    send_value = value.to_bytes(4,byteorder="little")
    send_msg_pack(b"f_bk",send_len,send_value)

def recv_msg_pack_with_repeat(repeat_time=20, receive_int16=False):
    recv_count = repeat_time
    while recv_count > 0:
        typ,lenth,data,status=recv_msg_pack(receive_int16)
        # print("out ",typ,lenth,status)
        if status == True:
            return typ,lenth,data,status
        else:
            raise ValueError("status is False")
        recv_count = recv_count - 1
    return None,None,None,None

def recv_msg_pack(is_int16=False):
    global ser_com
    if ser_com is None:
        print("ERR: serial is not open")
        exit(1)
    typ = ser_com.read(4)
    lenth = ser_com.read(4)
    if len(lenth) <= 0:
        return  None,None,None,False
    lenth = struct.unpack('<L', bytes(lenth))[0]
    data = ser_com.read(lenth)
    checkSum = ser_com.read(4)
    if len(checkSum) != 4:
        return None, None, None, False
    checkSum = struct.unpack('<I', bytes(checkSum))[0]
    status = True
    if checkSum != caculateCheckValue(data):
        raise ValueError("CheckSumERROR")
    if is_int16:
        data = struct.unpack('<'+str(lenth//2)+'h', data)
    else:
        data = struct.unpack('<'+str(lenth)+'b', data)
    return typ,lenth,data,status

def send_and_get_msg(i_data, send_int16=True, receive_int16=False):
    
    if send_int16:
        send_type = b"r_mc"      #### int16
        send_len = struct.pack('>L', 2*len(i_data))
    else:
        send_type = b"r_fb"        #### uint8
        send_len = struct.pack('>L', len(i_data))
    b = bytes(i_data)
    
    send_msg_pack(send_type,send_len,b)
    recv_type,recv_lenth,bmsg,status = recv_msg_pack_with_repeat(repeat_time = 20, receive_int16=receive_int16)
    return bmsg

def rcv_Int16():
    recv_type,recv_lenth,bmsg,status = recv_msg_pack_with_repeat(repeat_time = 20)
    return bmsg

if __name__ == "__main__":
    pass
