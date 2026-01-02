CXXFLAGS = -std=c++17 -I src/include -I imgui -I imgui/backends

LDFLAGS = -L src/lib -lSDL3 -lSDL3_ttf

SRC = main.c \
      app.c \
      init_sdl.c \
      canvas.c \
      pencil.c \
      vector2.c

IMGUI = imgui/imgui.cpp \
	  imgui/imgui_draw.cpp \
	  imgui/imgui_tables.cpp \
	  imgui/imgui_widgets.cpp \
	  imgui/backends/imgui_impl_sdl3.cpp \
        imgui/backends/imgui_impl_sdlrenderer3.cpp \
        gui/gui.cpp \
        gui/menubar.cpp


OUT = main.exe

all:
	g++ $(SRC) $(IMGUI) $(CXXFLAGS) $(LDFLAGS) -o $(OUT)
