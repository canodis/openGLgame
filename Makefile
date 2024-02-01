NAME        =   game
GLADLIB     =   glad/libglad.a

SRCS        =   $(wildcard src/*.cpp)
SRCS        +=  $(wildcard src/GameObject/*.cpp)
SRCS        +=  $(wildcard src/Managers/*.cpp)
SRCS        +=  $(wildcard src/Component/*.cpp)
SRCS        +=  $(wildcard src/ServerSide/*.cpp)
SRCS        +=  $(wildcard src/Map/*.cpp)
SRCS        +=  $(wildcard src/Global/*.cpp)
# SRCS        +=  $(wildcard imgui/*.cpp)

OBJS        =   $(SRCS:src/%.cpp=obj/%.o)

CC          =   c++ -g
CFLAGS = -std=c++11
FRMPATH     =   -I./GLFW/
GLADPATH    =   -I./glad/
FRMWK       =   -I/usr/include/GL
LINKER      =   -L./lib
INCLUDE_DIR =   $(shell find ./inc/ -type d)
CXXFLAGS    +=  -I/$(HOME)/goinfre/.brew/opt/freetype/include/freetype2 -I/$HOME/goinfre/.brew/opt/libpng/include/libpng16
LDFLAGS += -framework OpenGL -L/$(HOME)/goinfre/.brew/opt/freetype/lib -lfreetype -lglfw
INCLUDE_FLAGS = $(addprefix -I, $(INCLUDE_DIR))
GLM_DIR     =   -I./glm/
IMGUIDIR    =   -I./imgui/

CG = \033[92m
CY = \033[93m
CE = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@ $(CC) $(OBJS) glad/glad.c $(CFLAGS) $(CXXFLAGS) $(GLADPATH) $(FRMPATH) $(INCLUDE_FLAGS) $(GLM_DIR) $(IMGUIDIR) $(LINKER) -o $@ $(LDFLAGS) -Wno-deprecated
	@ echo "\n\033[92m---> Game Created ✓\033[0m";

obj/%.o: src/%.cpp
	@ mkdir -p $(@D)
	@ $(CC) $(CFLAGS) $(CXXFLAGS) $(GLADPATH) $(FRMPATH) $(INCLUDE_FLAGS) $(GLM_DIR) $(IMGUIDIR) -c $< -o $@
	@ echo "\033[K$(CY)[DIS] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:
	@ /bin/rm -rf obj/
	@ echo "\033[1;33m---> All .o files cleared\033[0m \033[92m✓\033[0m";

fclean:     clean
	@ /bin/rm -f $(NAME)
	@ echo "\n\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\033[0m";

re : fclean all

a: re
	./game map.txt

aa: all
	./game map.txt

.PHONY: all, clean, fclean, re, a
