SHELL = /bin/sh

# 运行目录
BIN_DIR := ../bin

# 项目列表
PROJ := lzhcore lzhtank lzhadttest

ifeq ($(MAKECMDGOALS),)
all: $(PROJ)
else ifeq ($(MAKECMDGOALS),mkdir)
all: mkdir
else
$(MAKECMDGOALS): $(PROJ)
endif

# 项目依赖
lzhtank: lzhcore

$(PROJ): FORCE
	@make -C $@ $(MAKECMDGOALS)
FORCE:

.PHONY: mkdir
mkdir: $(PROJ)
