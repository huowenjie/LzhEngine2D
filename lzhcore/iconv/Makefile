#------------------------------------------------------------------------------
# c/c++ 编译脚本：生成执行文件、创建静态库、创建共享库

SHELL = /bin/sh

#------------------------------------------------------------------------------

# 项目设置
PROJ := smwiconv
EXEC :=
TYPE := so
TYPES := exe ar so

# 目录设置
REL_DIR = ../..
BIN_DIR = $(REL_DIR)/bin
LIB_DIR = $(REL_DIR)/lib
INC_DIR = . ../include/iconv
SRC_DIR = .
OBJ_DIR = $(REL_DIR)/obj/$(PROJ)

#------------------------------------------------------------------------------

# c++ 文件列表
CPP_FILES := $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.cpp))

# c 文件列表
C_FILES := $(foreach dir,$(SRC_DIR),$(wildcard $(dir)/*.c))

# 预定义宏
DEF :=

# 调试选项 debug:-g -O0 / release: -g -O2
DBG := -O2

# 编译选项
FLG = $(RLS) -fPIC -Wall
CFLG = $(RLS) -fPIC -Wall
#FLG := $(DBG) -fPIC -Wall -std=c++11

# 连接选项
#LNK := -shared
LNK := -shared -Wl,-Bsymbolic

# 链接库列表
LIB :=

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

# 检查项目类型
ifeq ($(findstring $(TYPE),$(TYPES)),)
$(error --- 请指定目标类型：$(TYPES) ---)
endif

# 生成执行文件
ifeq ($(TYPE),exe)
TARGET := $(BIN_DIR)/$(PROJ)
$(TARGET): $(OBJ_FILES)
	@echo
	@echo "> $@"
	@g++ -o $@ $(LNK) $(addprefix $(OBJ_DIR)/,$(notdir $^)) $(LIB)
endif

# 创建静态库
ifeq ($(TYPE),ar)
TARGET := $(BIN_DIR)/lib$(PROJ).a
$(TARGET): $(OBJ_FILES)
	@echo
	@echo "> $@"
	@ar -r $@ $(addprefix $(OBJ_DIR)/,$(notdir $^))
endif

# 创建共享库
ifeq ($(TYPE),so)
TARGET := $(BIN_DIR)/lib$(PROJ).so
$(TARGET): $(OBJ_FILES)
	@echo
	@echo "> $@"
	@g++ -o $@ $(LNK) $(addprefix $(OBJ_DIR)/,$(notdir $^)) $(LIB)
endif

#------------------------------------------------------------------------------

# 编译 C++ 源文件
%.obj: %.cpp %.dep
	@echo "> $<"
	@g++ -c $< -o $(OBJ_DIR)/$@ $(DEF) $(FLG) $(INC)

# 生成 C++ 依赖文件
$(OBJ_DIR)/%.dep: %.cpp
	@g++ -MM -MD $< -MF $@ $(DEF) $(FLG) $(INC) -MT $(patsubst %.cpp,%.obj,$(notdir $<))

# 编译 C 源文件
%.o: %.c %.d
	@echo "> $<"
	@gcc -c $< -o $(OBJ_DIR)/$@ $(DEF) $(CFLG) $(INC)

# 生成 C 依赖文件
$(OBJ_DIR)/%.d: %.c
	@gcc -MM -MD $< -MF $@ $(DEF) $(CFLG) $(INC)

# 包含依赖文件
ifeq ($(MAKECMDGOALS),)
-include $(addprefix $(OBJ_DIR)/,$(DEP_FILES))
endif

#------------------------------------------------------------------------------

# 伪目标
.PHONY: cfg clean mkdir rmdir run help

ifeq ($(TYPE),exe)
EXEC := ./$(PROJ)
endif

# 执行目标
run:
	@cd $(BIN_DIR); export LD_LIBRARY_PATH=./; $(EXEC)

# 配置信息
cfg:
	@echo --------------------------------------------------
	@echo " 项目名称        $(PROJ)"
	@echo " 执行命令        $(EXEC)"
	@echo " 目标文件        $(TARGET)"
	@echo " 项目类型        $(TYPE)"
	@echo " 类型列表        $(TYPES)"
	@echo --------------------------------------------------
	@echo " 相对路径        $(REL_DIR)"
	@echo " 执行文件路径    $(BIN_DIR)"
	@echo " 库文件路径      $(LIB_DIR)"
	@echo " 头文件路径      $(INC_DIR)"
	@echo " 源文件路径      $(SRC_DIR)"
	@echo " 中间文件路径    $(OBJ_DIR)"
	@echo --------------------------------------------------
	@echo " 预定义宏        $(DEF)"
	@echo " 编译选项        $(FLG)"
	@echo " 连接选项        $(LNK)"
	@echo " 头文件引用      $(INC)"
	@echo " 库文件引用      $(LIB)"
	@echo --------------------------------------------------
	@echo -e " 源文件列表   $(foreach file,$(SRC_FILES),\n\t$(file))"
	@echo --------------------------------------------------
	@echo -e " 中间文件列表 $(foreach file,$(OBJ_FILES),\n\t$(file))"
	@echo --------------------------------------------------
	@echo -e " 依赖文件列表 $(foreach file,$(DEP_FILES),\n\t$(file))"
	@echo --------------------------------------------------

# 删除目标
clean:
	@rm -f $(TARGET)
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

# 帮助信息
help:
	@echo --------------------------------------------------
	@echo " make                生成目标"
	@echo " make run            执行目标"
	@echo " make cfg            配置信息"
	@echo " make clean          删除目标"
	@echo " make mkdir          创建目录"
	@echo " make rmdir          删除目录"
	@echo " make help           帮助信息"
	@echo --------------------------------------------------
