#------------------------------------------------------------------------------
# c/c++ 编译脚本：生成执行文件、创建静态库、创建共享库

SHELL = /bin/sh

#------------------------------------------------------------------------------

# 发布版本 (make build=debug or build=release)
build ?= debug

# 编译时是否将所有字符串常量的编码方式由 gbk 转换为 UTF-8
toutf ?= yes

# 项目设置
PROJ := lzhcore

# 主版本
VMAJ := 1

# 次版本
VMIN := 0.0

# 项目类型
EXEC :=
TYPE := so
TYPES := exe ar so

#编译器配置
CC	 := gcc
CCPP := g++
LK	 := g++

# 目录设置
REL_DIR := ../..
BIN_DIR := $(REL_DIR)/bin
LIB_DIR := $(REL_DIR)/lib
INC_DIR := . ../include box2d
SRC_DIR := . component container log math mem scene tool object engine graphic graphic/glad \
			box2d box2d/collision box2d/common box2d/dynamics box2d/rope

OBJ_DIR := $(REL_DIR)/obj/$(PROJ)

#------------------------------------------------------------------------------
# 输出文件名称设置

REAL_NAME :=

# 检查项目类型
ifeq ($(findstring $(TYPE),$(TYPES)),)
$(error --- 请指定目标类型：$(TYPES) ---)
endif

# 应用程序
ifeq ($(TYPE),exe)
REAL_NAME := $(PROJ).$(VMAJ).$(VMIN)
endif

# 静态库
ifeq ($(TYPE),ar)
REAL_NAME := lib$(PROJ).a
endif

# 共享库
ifeq ($(TYPE),so)
# 输出文件、soname 设置
LINK_NAME := lib$(PROJ).so
SO_NAME   := $(LINK_NAME).$(VMAJ)
REAL_NAME := $(SO_NAME).$(VMIN)
endif

#------------------------------------------------------------------------------

# 预定义宏
DEF := LZH_MEMORY_DEBUG LZH_EXP LZH_ENABLE_TRACE

CPP_FILES := $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.cpp))
C_FILES := $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c))

#------------------------------------------------------------------------------

# 编译选项
# fPIC 指定编译器生成位置独立的代码
# Wformat 不检查针对 printf 格式字符匹配的问题
# Wall 打开全部警告
# -Wno-unused-function 不显示定义后未使用（函数）的警告
# c 语言支持 c99 标准和特性， c++ 则保持默认
# -fvisibility=hidden 隐藏其他无关的符号
FLG := -fPIC -Wall -Wformat=0 -Wno-unused-function -fvisibility=hidden
CFLG := -fPIC -Wall -Wformat=0 -Wno-unused-function -std=c99 -fvisibility=hidden

# 调试选项 debug:-g -O0 / release: -O2
DBG := -g -O0

# debug 和 release 不同的编译选项
ifeq ($(build),debug)
	FLG += $(DBG)
	CFLG += $(DBG)
else ifeq ($(build),release)
	FLG += -O2
	CFLG += -O2
endif

# -finput-charset 指令指定当前源文件的编码方式
# -fexec-charset 指令指定最终可执行文件的输出编码方式
ifeq ($(toutf),yes)
	FLG += -finput-charset=gbk
	FLG += -fexec-charset=utf-8
	CFLG += -finput-charset=gbk
	CFLG += -fexec-charset=utf-8
endif

#------------------------------------------------------------------------------

# 导出符号控制
#EXP_MAP := -Wl,--retain-symbols-file=hal/whsm.sym -Wl,--version-script=hal/whsm.map

# 链接选项
# -Wl,-Bsymbolic 强制采用本地的全局变量定义
#LNK := $(EXP_MAP) -Wl,-Bsymbolic,-rpath=.
LNK := -Wl,-Bsymbolic

# 链接库列表
LIB := dl m SDL2

# 共享库
ifeq ($(TYPE),so)
# -shared 生成共享库
# -Wl,-soname,$(SO_NAME) 指定当前动态库的 soname 为 $(SO_NAME)
LNK += -shared -Wl,-soname,$(SO_NAME)
endif

#------------------------------------------------------------------------------

# 预定义宏
DEF := $(foreach def,$(DEF),-D$(def))

# gcc 头文件搜索路径
INC := $(foreach dir,$(INC_DIR),-I$(dir))

# gcc 库文件链接及搜索路径
LIB := $(foreach lib,$(LIB),-l$(lib))
LIB += -L$(BIN_DIR) -L$(LIB_DIR)

# 过滤源文件路径
CPP_FILES := $(notdir $(CPP_FILES))
C_FILES := $(notdir $(C_FILES))

# 源文件列表
SRC_FILES := $(CPP_FILES)
SRC_FILES += $(C_FILES)

# 中间文件列表
OBJ_FILES := $(patsubst %.cpp,%.obj,$(CPP_FILES))
OBJ_FILES += $(patsubst %.c,%.o,$(C_FILES))

# 依赖文件列表
DEP_FILES := $(patsubst %.cpp,%.dep,$(CPP_FILES))
DEP_FILES += $(patsubst %.c,%.d,$(C_FILES))

# make 搜索路径
vpath %.h		$(INC_DIR)
vpath %.cpp		$(SRC_DIR)
vpath %.c		$(SRC_DIR)
vpath %.obj		$(OBJ_DIR)
vpath %.o		$(OBJ_DIR)
vpath %.dep		$(OBJ_DIR)
vpath %.d		$(OBJ_DIR)

#------------------------------------------------------------------------------

TARGET := $(BIN_DIR)/$(REAL_NAME)

# 生成执行文件
ifeq ($(TYPE),exe)
$(TARGET): $(OBJ_FILES)
	@echo
	@echo "> $@"
	@$(LK) -o $@ $(LNK) $(addprefix $(OBJ_DIR)/,$(notdir $^)) $(LIB)
endif

# 创建静态库
ifeq ($(TYPE),ar)
$(TARGET): $(OBJ_FILES)
	@echo
	@echo "> $@"
	@ar -r $@ $(addprefix $(OBJ_DIR)/,$(notdir $^))
endif

# 创建共享库
ifeq ($(TYPE),so)
$(TARGET): $(OBJ_FILES)
	@echo
	@echo "> $@"
	@$(LK) -o $@ $(LNK) $(addprefix $(OBJ_DIR)/,$(notdir $^)) $(LIB)
	@ln -sf $(REAL_NAME) $(BIN_DIR)/$(SO_NAME)
	@ln -sf $(SO_NAME) $(BIN_DIR)/$(LINK_NAME)
endif

#------------------------------------------------------------------------------

# 编译 C++ 源文件
%.obj: %.cpp %.dep
	@echo "> $<"
	@$(CCPP) -c $< -o $(OBJ_DIR)/$@ $(DEF) $(FLG) $(INC)

# 生成 C++ 依赖文件
$(OBJ_DIR)/%.dep: %.cpp
	@$(CCPP) -MM -MD $< -MF $@ $(DEF) $(FLG) $(INC) -MT $(patsubst %.cpp,%.obj,$(notdir $<))

# 编译 C 源文件
%.o: %.c %.d
	@echo "> $<"
	@$(CC) -c $< -o $(OBJ_DIR)/$@ $(DEF) $(CFLG) $(INC)

# 生成 C 依赖文件
$(OBJ_DIR)/%.d: %.c
	@$(CC) -MM -MD $< -MF $@ $(DEF) $(CFLG) $(INC)

# 包含依赖文件
ifeq ($(MAKECMDGOALS),)
-include $(addprefix $(OBJ_DIR)/,$(DEP_FILES))
endif

#------------------------------------------------------------------------------

# 待删除文件
DEL_NAMES := $(TARGET)

ifeq ($(TYPE),so)
DEL_NAMES += $(BIN_DIR)/$(LINK_NAME) $(BIN_DIR)/$(SO_NAME)
endif

ifeq ($(TYPE),exe)
EXEC := ./$(PROJ)
endif

#------------------------------------------------------------------------------

# 伪目标
.PHONY: clean mkdir rmdir

# 删除目标
clean:
	@rm -f $(DEL_NAMES)
	@rm -f $(OBJ_DIR)/*

# 创建目录
mkdir:
	@mkdir -p $(LIB_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

# 删除目录
rmdir:
	@rm -rf $(LIB_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -rf $(BIN_DIR)
