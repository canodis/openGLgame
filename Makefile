NAME		= 	game
GLADLIB		=	glad/libglad.a

SRCS		= 	$(wildcard src/*.cpp)
SRCS		+=  $(wildcard src/GameObject/*.cpp)
SRCS		+=  $(wildcard src/Managers/*.cpp)
SRCS		+=  $(wildcard src/Component/*.cpp)
# SRCS		+=  $(wildcard imgui/*.cpp)

OBJS		= 	$(patsubst srcs/%.cpp,objs/%.o,$(SRCS))

CC			= 	c++ -g
CFLAGS		= 	-framework OpenGl -std=c++11
FRMPATH		=	-I./GLFW/
GLADPATH	=	-I./glad/
FRMWK		=	-I/usr/include/GL
LINKER		= 	-L./lib
INCLUDE_DIR = 	$(shell find ./inc/ -type d)
INCLUDE_FLAGS = $(addprefix -I, $(INCLUDE_DIR))
# INCLUDE_FLAGS = -I./inc/ -I./inc/GameObject -I./inc/Managers -I./inc/Data -I./inc/Components
GLM_DIR		= 	-I./glm/
IMGUIDIR	=	-I./imgui/

CG = \033[92m
CY = \033[93m
CE = \033[0m

all:		$(NAME)

$(NAME):	$(OBJS)
			 $(CC) $(CFLAGS) $(GLADPATH) $(FRMPATH) $(LINKER) $(INCLUDE_FLAGS) $(GLM_DIR) $(IMGUIDIR) -o $@ $^ glad/glad.c -lglfw -Wno-deprecated
			 echo "\n\033[92m---> Game Created ✓\033[0m";

objs/%.o:	srcs/%.cpp
			@ mkdir -p objs
		 	@ $(CC) -c $< -o $@
		 	@ echo "\033[K$(CY)[RT] :$(CE) $(CG)Compiling $<$(CE) \033[1A";

clean:		
			@ /bin/rm -rf objs/
			@ echo "\033[1;33m---> All .o files cleared\033[0m \033[92m✓\033[0m";

fclean:		clean
			@ /bin/rm -f $(NAME)
			@ echo "\n\033[1;33m---> Everything cleared\033[2;00m \033[92m✓\033[0m";

re : fclean all

a: re
	./game map.txt

.PHONY: all, clean, fclean, re, a


# g++ -I./glad/ -I./GLFW/ -L./lib ./lib/libglfw.so.3 main.cpp Screen.cpp ShaderProgram.cpp glad/glad.c -lglfw -o scop