# ============================================================
#  Makefile для Windows (MinGW / mingw32-make)
# ============================================================

# --- Компилятор и утилиты ---
CXX      := g++
CC       := gcc
MKDIR    := mkdir -p
RM       := rm -rf

# --- Директории ---
SRC_DIR      := source
INC_DIR      := include
LIB_DIR      := lib
LIB_INC_DIR  := lib_include
BUILD_DIR    := build
OBJ_DIR      := $(BUILD_DIR)/obj

# --- Поиск файлов ---
# Все .cpp из source (рекурсивно)
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

SRCS := $(call rwildcard,$(SRC_DIR),*.cpp)

# Преобразуем пути source/... -> build/obj/... .o
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Все .a из lib (рекурсивно)
LIBS := $(wildcard $(LIB_DIR)/*.a)

# --- Флаги ---
# Директивы поиска заголовков
INCLUDES := -I$(INC_DIR) -I$(LIB_INC_DIR)

# Флаги компиляции (C++17, предупреждения)
CXXFLAGS := -std=c++17 -Wall -Wextra -O2 $(INCLUDES)

# Флаги линковки: библиотеки из lib + системные (GLFW/GLEW/OpenGL/GDI)
LDFLAGS  := -L$(LIB_DIR) \
            $(LIBS) \
            -lglew32 -lglfw3 -lopengl32 -lgdi32

# Имя исполняемого файла
TARGET := $(BUILD_DIR)/app.exe

# ============================================================
#  Цели
# ============================================================

.PHONY: all clean run dirs

all: dirs $(TARGET)

# Создание нужных директорий
dirs:
	@if not exist "$(OBJ_DIR)" mkdir "$(OBJ_DIR)"
	@if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"

# Линковка
$(TARGET): $(OBJS)
	@echo "==> Linking: $@"
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# Компиляция каждого .cpp -> .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "==> Compiling: $<"
	@if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Запуск
run: all
	@$(TARGET)

# Очистка
clean:
	@echo "==> Cleaning build"
	@$(RM) $(BUILD_DIR)

# ============================================================