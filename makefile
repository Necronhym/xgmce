IN=main.c
OUT=xgmce
LINK=-lX11 -lXtst
CC=gcc
target:
	$(CC) $(IN) -o $(OUT) $(LINK)
