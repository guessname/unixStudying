#######################################################
#���ļ�����ָ�����������ÿ��Makefile�ж���������ļ�
#######################################################

#ָ��������
CC=gcc

#ָ���鵵��������������̬��
AR=ar

#ָ��ͷ�ļ�·��
INCDIR=$(ROOT)/include

#ָ�����ļ�·��
LDDIR=$(ROOT)/lib
#LDDIR=$(ROOT)/sigdbug

#ָ������
LIB=common
#LIB=sigsegv

#ָ������ѡ��

CFLAGS=-Wall  -I$(INCDIR)
#CFLAGS=-Wall -rdynamic -ldl -I$(INCDIR)

#ָ������ѡ��
LDFLAGS=-lpthread

#�������ɵ��м��ļ�������make clean����
TEMPFILES=core core.* *.o temp.* *.out
